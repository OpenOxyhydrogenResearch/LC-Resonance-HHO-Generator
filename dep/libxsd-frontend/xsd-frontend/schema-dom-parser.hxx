// file      : xsd-frontend/schema-dom-parser.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_SCHEMA_DOM_PARSER_HXX
#define XSD_FRONTEND_SCHEMA_DOM_PARSER_HXX

#include <xercesc/parsers/XercesDOMParser.hpp>

#include <xercesc/dom/DOMElement.hpp>

#include <xercesc/validators/schema/XSDLocator.hpp>
#include <xercesc/validators/schema/XSDErrorReporter.hpp>

namespace XSDFrontend
{
  namespace XML
  {
    namespace Xerces = xercesc;

    extern const XMLCh line_key[2];
    extern const XMLCh column_key[2];

    class SchemaDOMParser: public Xerces::XercesDOMParser
    {
    public :
      SchemaDOMParser (
        Xerces::MemoryManager* = Xerces::XMLPlatformUtils::fgMemoryManager);

      // Callbacks.
      //
      virtual void
      startElement (const Xerces::XMLElementDecl&,
                    const unsigned int url_id,
                    const XMLCh* const prefix,
                    const Xerces::RefVectorOf<Xerces::XMLAttr>& attributes,
#if _XERCES_VERSION >= 30000
                    const XMLSize_t attribute_count,
#else
                    const unsigned int attribute_count,
#endif
                    const bool empty,
                    const bool root);

      virtual void
      endElement (const Xerces::XMLElementDecl&,
                  const unsigned int url_id,
                  const bool root,
                  const XMLCh* const prefix);

      virtual void
      docCharacters (const XMLCh* const,
#if _XERCES_VERSION >= 30000
                     const XMLSize_t length,
#else
                     const unsigned int length,
#endif
                     const bool cdata);

      virtual void
      docComment (const XMLCh* const);

      virtual void
      startEntityReference (const Xerces::XMLEntityDecl&);

      virtual void
      endEntityReference (const Xerces::XMLEntityDecl&);

      virtual void
      ignorableWhitespace (const XMLCh* const,
#if _XERCES_VERSION >= 30000
                           const XMLSize_t length,
#else
                           const unsigned int length,
#endif
                           const bool cdata);
    private:
      SchemaDOMParser (SchemaDOMParser const&);
      SchemaDOMParser&
      operator=(SchemaDOMParser const&);

    private:
      int depth_;
      int ann_depth_;
      int inner_ann_depth_;
      Xerces::XSDLocator locator_;
      Xerces::XSDErrorReporter error_reporter_;
    };
  }
}

#endif // XSD_FRONTEND_SCHEMA_DOM_PARSER_HXX
