// file      : xsd-frontend/xml.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_XML_HXX
#define XSD_FRONTEND_XML_HXX

#include <ostream>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>

#include <cult/containers/vector.hxx>

#include <xsd-frontend/types.hxx>
#include <xsd-frontend/schema-dom-parser.hxx>

namespace XSDFrontend
{
  namespace XML
  {
    namespace Xerces = xercesc;

    inline
    String
    transcode (XMLCh const* s, Size length)
    {
      if (sizeof (WideChar) == 4)
      {
        // UTF-32
        //
        XMLCh const* end (s + length);

        // Find what the resulting buffer size will be.
        //
        Size rl (0);
        Boolean valid (true);

        for (XMLCh const* p (s); p < end; ++p)
        {
          rl++;

          if ((*p >= 0xD800) && (*p <= 0xDBFF))
          {
            // Make sure we have one more char and it has a valid
            // value for the second char in a surrogate pair.
            //
            if (++p == end || !((*p >= 0xDC00) && (*p <= 0xDFFF)))
            {
              valid = false;
              break;
            }
          }
        }

        if (!valid)
          return String ();

        String r;
        r.reserve (rl + 1);
        r.resize (rl);
        WideChar* rs (const_cast<WideChar*> (r.c_str ()));

        Size i (0);

        for (XMLCh const* p (s); p < end; ++p)
        {
          XMLCh x (*p);

          if (x < 0xD800 || x > 0xDBFF)
            rs[i++] = WideChar (x);
          else
            rs[i++] = ((x - 0xD800) << 10) + (*++p - 0xDC00) + 0x10000;
        }

        return r;
      }
      else if (sizeof (WideChar) == 2)
      {
        // UTF-16
        //
        return String (reinterpret_cast<const WideChar*> (s), length);
      }
      else
        return String ();
    }

    inline
    String
    transcode (XMLCh const* s)
    {
      return transcode (s,  Xerces::XMLString::stringLen (s));
    }

    inline
    NarrowString
    transcode_to_narrow (XMLCh const* xs)
    {
      Char* s (Xerces::XMLString::transcode (xs));
      NarrowString r (s);
      Xerces::XMLString::release (&s);
      return r;
    }

    inline
    XMLCh*
    transcode (String const& str)
    {
      Size l (str.size ());
      WideChar const* s (str.c_str ());

      if (sizeof (WideChar) == 4)
      {
        // Find what the resulting buffer size will be.
        //
        Size rl (0);

        for (WideChar const* p (s); p < s + l; ++p)
        {
          rl += (*p & 0xFFFF0000) ? 2 : 1;
        }

        XMLCh* r (new XMLCh[rl + 1]);
        XMLCh* ir (r);

        for (WideChar const* p (s); p < s + l; ++p)
        {
          WideChar w (*p);

          if (w & 0xFFFF0000)
          {
            // Surrogate pair.
            //
            *ir++ = static_cast<XMLCh> (((w - 0x10000) >> 10) + 0xD800);
            *ir++ = static_cast<XMLCh> ((w & 0x3FF) + 0xDC00);
          }
          else
            *ir++ = static_cast<XMLCh> (w);
        }

        *ir = XMLCh (0);

        return r;
      }
      else if (sizeof (WideChar) == 2)
      {
        XMLCh* r (new XMLCh[l + 1]);
        XMLCh* ir (r);

        for (Size i (0); i < l; ++ir, ++i)
          *ir = static_cast<XMLCh> (s[i]);

        *ir = XMLCh (0);

        return r;
      }
      else
        return 0;
    }

    class XMLChString
    {
    public :
      XMLChString (String const& s)
          : s_ (transcode (s))
      {
      }

      XMLChString (WideChar const* s)
          : s_ (transcode (String (s)))
      {
      }

      ~XMLChString ()
      {
        delete[] s_;
      }

      XMLCh const*
      c_str () const
      {
        return s_;
      }

    private:
      XMLChString (XMLChString const&);

      XMLChString&
      operator= (XMLChString const&);

    private:
      XMLCh* s_;
    };


    class Element
    {
    public:
      Element (Xerces::DOMElement* e)
          : e_ (e),
            name_ (transcode (e->getLocalName ())),
            namespace__ (transcode (e->getNamespaceURI ()))
      {
      }

      String
      name () const
      {
        return name_;
      }

      String
      namespace_ () const
      {
        return namespace__;
      }

    public:
      UnsignedLong
      line () const
      {
        //@@ cache
        //
        return reinterpret_cast<UnsignedLong> (e_->getUserData (line_key));
      }

      UnsignedLong
      column () const
      {
        //@@ cache
        //
        return reinterpret_cast<UnsignedLong> (e_->getUserData (column_key));
      }

    public:
      Element
      parent () const
      {
        return dynamic_cast<Xerces::DOMElement*>(e_->getParentNode ());
      }

    public:
      // Attribute identified by a name.
      //
      Boolean
      attribute_p (String const& name) const
      {
        return attribute_p ("", name);
      }

      String
      attribute (String const& name) const
      {
        return attribute ("", name);
      }

      String
      operator[] (String const& name) const
      {
        return attribute (name);
      }

      // Attribute identified by namespace and name.
      //

      Boolean
      attribute_p (String const& namespace_, String const& name) const
      {
        Xerces::DOMAttr* a (
          e_->getAttributeNodeNS (
            XMLChString (namespace_).c_str (),
            XMLChString (name).c_str ()));

        return a != 0;
      }

      String
      attribute (String const& namespace_, String const& name) const
      {
        XMLCh const* value (
          e_->getAttributeNS (
            XMLChString (namespace_).c_str (),
            XMLChString (name).c_str ()));

        return transcode (value);
      }

    public:
      Xerces::DOMElement*
      dom_element () const
      {
        return e_;
      }

    private:
      Xerces::DOMElement* e_;

      String name_;
      String namespace__;
    };

    inline String
    prefix (String const& n)
    {
      Size i (0);
      while (i < n.length () && n[i] != L':') ++i;

      //std::wcerr << "prefix " << n << " "
      //           << String (n, i == n.length () ? i : 0, i) << std::endl;

      return String (n, i == n.length () ? i : 0, i);
    }

    inline String
    uq_name (String const& n)
    {
      Size i (0);
      while (i < n.length () && n[i] != L':') ++i;

      return String (n.c_str () + (i == n.length () ? 0 : i + 1));
    }

    struct NoMapping
    {
      NoMapping (String const& prefix)
          : prefix_ (prefix)
      {
      }

      String const&
      prefix () const
      {
        return prefix_;
      }

    private:
      String prefix_;
    };

    // Throws NoMapping if there is no prefix-namespace association.
    //
    inline String
    ns_name (Xerces::DOMElement const* e, String const& prefix)
    {
      // 'xml' prefix requires special handling and Xerces folks refuse
      // to handle this in DOM so I have to do it myself.
      //
      if (prefix == L"xml")
        return L"http://www.w3.org/XML/1998/namespace";

      // 0 means "no prefix" to Xerces.
      //
      XMLCh const* xns (
        e->lookupNamespaceURI (
          prefix.empty () ? 0 : XMLChString (prefix).c_str ()));

      if (xns == 0)
        throw NoMapping (prefix);

      return transcode (xns);
    }

    class NoPrefix {};

    inline String
    ns_prefix (Element const& e, String const& wns)
    {
      XMLChString ns (wns);

#if _XERCES_VERSION >= 30000
      XMLCh const* p (
        e.dom_element ()->lookupPrefix (ns.c_str ()));
#else
      XMLCh const* p (
        e.dom_element ()->lookupNamespacePrefix (ns.c_str (), false));
#endif

      if (p == 0)
      {
        Boolean r (e.dom_element ()->isDefaultNamespace (ns.c_str ()));

        if (r)
          return L"";
        else
        {
          // 'xml' prefix requires special handling and Xerces folks refuse
          // to handle this in DOM so I have to do it myself.
          //
          if (wns == L"http://www.w3.org/XML/1998/namespace")
            return L"xml";

          throw NoPrefix ();
        }
      }

      return transcode (p);
    }

    inline String
    fq_name (Element const& e, String const& n)
    {
      String un (uq_name (n));

      try
      {
        String ns (ns_name (e.dom_element (), prefix (n)));
        return ns + L'#' + un;
      }
      catch (XML::NoMapping const&)
      {
        return un;
      }
    }


    // Simple auto_ptr version that calls release() instead of delete.
    //

    template <typename X>
    struct AutoPtrRef
    {
      X* x_;

      explicit
      AutoPtrRef (X* x)
          : x_ (x)
      {
      }
    };

    template <typename X>
    struct AutoPtr
    {
      ~AutoPtr ()
      {
        reset ();
      }

      explicit
      AutoPtr (X* x = 0)
          : x_ (x)
      {
      }

      AutoPtr (AutoPtr& y)
          : x_ (y.release ())
      {
      }

      AutoPtr (AutoPtrRef<X> r)
          : x_ (r.x_)
      {
      }

      AutoPtr&
      operator= (AutoPtr& y)
      {
        if (this != &y)
        {
          reset (y.release ());
        }

        return *this;
      }

      AutoPtr&
      operator= (AutoPtrRef<X> r)
      {
        if (r.x_ != x_)
        {
          reset (r.x_);
        }

        return *this;
      }

      operator AutoPtrRef<X> ()
      {
        return AutoPtrRef<X> (release ());
      }

    public:
      X&
      operator* () const
      {
        return *x_;
      }

      X*
      operator-> () const
      {
        return x_;
      }

      X*
      get () const
      {
        return x_;
      }

      X*
      release ()
      {
        X* x (x_);
        x_ = 0;
        return x;
      }

      void
      reset (X* x = 0)
      {
        if (x_)
          x_->release ();

        x_ = x;
      }

      // Conversion to bool.
      //
      typedef X* (AutoPtr::*BooleanConvertible)() const;

      operator BooleanConvertible () const throw ()
      {
        return x_ ? &AutoPtr<X>::operator-> : 0;
      }

    private:
      X* x_;
    };

    template <typename X>
    struct PtrVector: Cult::Containers::Vector<X*>
    {
      typedef Cult::Containers::Vector<X*> Base;

      ~PtrVector ()
      {
        for (typename Base::Iterator i (this->begin ()), e (this->end ());
             i != e; ++i)
        {
          if (*i)
            (*i)->release ();
        }
      }

      Void
      push_back (AutoPtr<X>& x)
      {
        Base::push_back (0);
        this->back () = x.release ();
      }
    };
  }
}

// Xerces DOoM.
//
//
inline
std::wostream&
operator<< (std::wostream& o, XMLCh const* s)
{
  return o << XSDFrontend::XML::transcode (s);
}

#endif  // XSD_FRONTEND_XML_HXX
