// file      : cult/types/string.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_TYPES_STRING_HXX
#define CULT_TYPES_STRING_HXX

#include <cult/types/fundamental.hxx>
#include <cult/eh/exception.hxx>

//@@ Dependency on 'containers'. Maybe move iterator to 'types'?
//
#include <cult/containers/iterator.hxx>

#include <string>
#include <cstdlib> // mbstowcs

namespace Cult
{
  namespace Types
  {
    //@@ Maybe create StringFwd.hxx
    //

    namespace Bits
    {
      struct None {};

      template <typename C>
      struct NarrowerChar
      {
        typedef None Type;
      };


      template <>
      struct NarrowerChar<WideChar>
      {
        typedef Char Type;
      };
    }

    template <typename C,
              typename NarrowerChar = typename Bits::NarrowerChar<C>::Type>
    class StringTemplate;

    template <>
    class StringTemplate<Bits::None, Bits::None>
    {
    };


    template <typename C, typename NarrowerChar>
    class StringTemplate : public std::basic_string<C>
    {
      typedef std::basic_string<C> Base;
      typedef std::basic_string<NarrowerChar> NarrowerBase;

      Base&
      base ()
      {
        return *this;
      }

      Base const&
      base () const
      {
        return *this;
      }

    public:
      typedef typename Base::value_type Value;

      /*
      typedef traits traits_type;
      typedef typename traits::char_type value_type;
      typedef Allocator allocator_type;
      typedef typename Allocator::size_type size_type;
      typedef typename Allocator::difference_type difference_type;
      typedef typename Allocator::reference reference;
      typedef typename Allocator::const_reference const_reference;
      typedef typename Allocator::pointer pointer;
      typedef typename Allocator::const_pointer const_pointer;
      */

      typedef
      Containers::IteratorAdapter<typename Base::iterator>
      Iterator;

      typedef
      Containers::IteratorAdapter<typename Base::const_iterator>
      ConstIterator;


      typedef
      Containers::IteratorAdapter<typename Base::reverse_iterator>
      ReverseIterator;

      typedef
      Containers::IteratorAdapter<typename Base::const_reverse_iterator>
      ConstReverseIterator;


      using Base::npos;
      using Base::empty;

    public:
      explicit
      StringTemplate ()
      {
      }

      StringTemplate (StringTemplate const& str, Size pos, Size n = npos)
          : Base (str, pos, n)
      {
      }

      StringTemplate (Value const* s, Size n)
          : Base (s, n)
      {
      }

      StringTemplate (Value const* s)
          : Base (s)
      {
      }

      StringTemplate (Size n, Value c)
          : Base (n, c)
      {
      }

      template <typename InputIterator>
      StringTemplate(InputIterator begin, InputIterator end)
          : Base (begin, end)
      {
      }

      StringTemplate (StringTemplate const& other)
          : Base (other)
      {
      }

      // Conversion from Base.
      //
      StringTemplate (Base const& str)
          : Base (str)
      {
      }

      // Conversion from the Narrower type. Experimental.
      //
      StringTemplate (NarrowerChar const* s)
      {
        from_narrow (s);
      }

      StringTemplate (StringTemplate<NarrowerChar> const& other)
      {
        from_narrow (other.c_str ());
      }

      StringTemplate (NarrowerBase const& other)
      {
        from_narrow (other.c_str ());
      }

      // Conversion to the Narrower type. Experimental.
      //
      struct NonRepresentable: virtual EH::Exception {};

      StringTemplate<NarrowerChar>
      to_narrow () const;

      // Assignment.
      //
      StringTemplate&
      operator= (StringTemplate const& str)
      {
        base () = str;
        return *this;
      }

      StringTemplate&
      operator= (Value const* s)
      {
        base () = s;
        return *this;
      }

      StringTemplate&
      operator= (Value c)
      {
        base () = c;
        return *this;
      }

      // Assignment from Base.
      //
      StringTemplate&
      operator= (Base const& str)
      {
        base () = str;
        return *this;
      }

    public:
      StringTemplate&
      operator+= (StringTemplate const& str)
      {
        base () += str;
        return *this;
      }

      StringTemplate&
      operator+= (Value const* s)
      {
        base () += s;
        return *this;
      }

      StringTemplate&
      operator+= (Value c)
      {
        base () += c;
        return *this;
      }


    public:
      Iterator
      begin ()
      {
        return Iterator (base ().begin ());
      }

      Iterator
      end ()
      {
        return Iterator (base ().end ());
      }


      ConstIterator
      begin () const
      {
        return ConstIterator (base ().begin ());
      }

      ConstIterator
      end () const
      {
        return ConstIterator (base ().end ());
      }

      //
      //

      ReverseIterator
      rbegin ()
      {
        return ReverseIterator (base ().rbegin ());
      }

      ReverseIterator
      rend ()
      {
        return ReverseIterator (base ().rend ());
      }


      ConstReverseIterator
      rbegin () const
      {
        return ConstReverseIterator (base ().rbegin ());
      }

      ConstReverseIterator
      rend () const
      {
        return ConstReverseIterator (base ().rend ());
      }


      // Conversion to Boolean.
      //
    private:
      typedef Void (StringTemplate::*BooleanConvertable)();

      void
      true_ ()
      {
      }

    public:
      operator BooleanConvertable () const
      {
        return empty () ? 0 : &StringTemplate::true_;
      }

    private:
      Void
      from_narrow (NarrowerChar const* s);
    };


    template<typename C>
    StringTemplate<C>
    operator+ (StringTemplate<C> const& lhs, StringTemplate<C> const& rhs)
    {
      return StringTemplate<C> (lhs) += rhs;
    }

    template<typename C>
    StringTemplate<C>
    operator+ (C const* lhs, StringTemplate<C> const& rhs)
    {
      return StringTemplate<C> (lhs) += rhs;
    }

    template<typename C>
    StringTemplate<C>
    operator+ (StringTemplate<C> const& lhs, C const* rhs)
    {
      return StringTemplate<C> (lhs) += rhs;
    }

    template<typename C>
    StringTemplate<C>
    operator+ (C lhs, StringTemplate<C> const& rhs)
    {
      return StringTemplate<C> (1, lhs) += rhs;
    }


    template<typename C>
    StringTemplate<C>
    operator+ (StringTemplate<C> const& lhs, C rhs)
    {
      return StringTemplate<C> (lhs) += rhs;
    }

    //
    //
    typedef StringTemplate<Char> String;
    typedef StringTemplate<Char> NarrowString;
    typedef StringTemplate<WideChar> WideString;

    // Specialization for Char to WideChar conversion.
    //
    template <>
    inline Void StringTemplate<WideChar, Char>::
    from_narrow (Char const* s)
    {
      Size size (std::mbstowcs (0, s, 0) + 1);

      // I dare to change the guts!
      //
      resize (size - 1);

      WideChar* p (const_cast<WideChar*> (data ()));

      std::mbstowcs (p, s, size);
    }

    // Specialization for WideChar to Char conversion.
    //
    template <>
    inline StringTemplate<Char> StringTemplate<WideChar, Char>::
    to_narrow () const
    {
      Size size (std::wcstombs (0, c_str (), 0));

      if (size == Size (-1))
        throw NonRepresentable ();

      // I dare to change the guts!
      //
      StringTemplate<Char> r;
      r.resize (size);

      Char* p (const_cast<Char*> (r.data ()));

      std::wcstombs (p, c_str (), size + 1);

      return r;
    }
  }

  using Types::String;
  using Types::NarrowString;
  using Types::WideString;
  using Types::StringTemplate;
}

#endif  // CULT_TYPES_STRING_HXX
