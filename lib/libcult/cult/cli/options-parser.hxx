// file      : cult/cli/options-parser.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_CLI_OPTIONS_PARSER_HXX
#define CULT_CLI_OPTIONS_PARSER_HXX

#include <cult/types.hxx>

#include <cult/containers/map.hxx>
#include <cult/containers/vector.hxx>

#include <cult/trace/stream.hxx>

#include <cult/cli/exceptions.hxx>
#include <cult/cli/scanner.hxx>
#include <cult/cli/options-spec.hxx>

#include <sstream>

//@! which types should be NonCopyable

namespace Cult
{
  namespace CLI
  {
    struct UnknownMode
    {
      enum Value
      {
        skip,
        stop,
        fail
      };
    };

    template <typename T>
    struct OptionParserBase
    {
      T
      parse (Char const* o, Scanner& s);
    };

    template <typename Spec>
    struct OptionParser: OptionParserBase<typename Spec::Type>
    {
      OptionParser (Spec const&)
      {
      }
    };

    template<Char const* o, typename T>
    class OptionParser<OptionSpec<o, Containers::Vector<T> > >
    {
    public:
      OptionParser (OptionSpec<o, Containers::Vector<T> > const&)
          : impl_ (OptionSpec<o, T> ())
      {
      }

      T
      parse (Char const* k, Scanner& s)
      {
        return impl_.parse (k, s);
      }

    private:
      OptionParser<OptionSpec<o, T> > impl_;
    };

    struct OptionParserBooleanBase
    {
      Boolean
      parse (Char const*, Scanner& s);
    };

    template<Char const* o>
    struct OptionParser<OptionSpec<o, Boolean> >: OptionParserBooleanBase
    {
      OptionParser (OptionSpec<o, Boolean> const&)
      {
      }
    };

    struct OptionParserStringBase
    {
      String
      parse (Char const*, Scanner& s);
    };

    template<Char const* o>
    struct OptionParser<OptionSpec<o, String> >: OptionParserStringBase
    {
      OptionParser (OptionSpec<o, String> const&)
      {
      }
    };

    //
    //
    //

    class OptionsParserBase
    {
    protected:
      struct GlueBase
      {
        // I am using Void* here to (significantly) reduce the length
        // on the object file symbols.
        //
        virtual Void
        operator() (Char const*, Scanner&, Void* options) = 0;
      };

      static Trace::Stream tout;
    };

    template <typename Spec>
    class OptionsParser : OptionsParserBase
    {
      typedef
      Containers::Map<String, Evptr<GlueBase> >
      Map;

      template <typename>
      struct Glue;

      template <Char const* k, typename T>
      struct Glue<OptionSpec<k, T> > : GlueBase
      {
        Glue (OptionSpec<k, T> const& spec)
            : parser_ (spec)
        {
        }

        virtual Void
        operator() (Char const* o, Scanner& scan, Void* options)
        {
          typedef typename Spec::Options Options;

          Options& ops (*reinterpret_cast<Options*> (options));

          ops.template value<k> () = parser_.parse (o, scan);
        }

      private:
        OptionParser<OptionSpec<k, T> > parser_;
      };

      //@@ It's bad that I also have to specialize Glue. Need to redesign
      //   this.
      //
      template <Char const* k, typename T>
      struct Glue<OptionSpec<k, Containers::Vector<T> > > : GlueBase
      {
        Glue (OptionSpec<k, Containers::Vector<T> > const& spec)
            : parser_ (spec)
        {
        }

        virtual Void
        operator() (Char const* o, Scanner& scan, Void* options)
        {
          typedef typename Spec::Options Options;

          Options& ops (*reinterpret_cast<Options*> (options));

          ops.template value<k> ().push_back (parser_.parse (o, scan));
        }

      private:
        OptionParser<OptionSpec<k, Containers::Vector<T> > > parser_;
      };


      // Option-specific specializations of some functions.
      //
      template <typename>
      struct S_
      {
        // This is a "specialization" for when type is Bits::Null.
        //
        static Void
        add_parser (Spec const&, Map&)
        {
        }

        static Void
        set_default (typename Spec::Options&, Spec const&)
        {
        }
      };

      template <Char const* k, typename T>
      struct S_<OptionSpec<k, T> >
      {
        static Void
        add_parser (Spec const& spec, Map& map)
        {
          if (k[0] != '\0')
          {
            OptionSpec<k, T> const& os (spec.template option<k> ());
            map[os.name ()] = new Glue<OptionSpec<k, T> > (os);
          }
        }

        static Void
        set_default (typename Spec::Options& o, Spec const& s)
        {
          o.template value<k> () = s.template option<k> ().default_value ();
        }
      };

    public:

      OptionsParser (Spec const& spec)
          : spec_ (spec)
      {
        S_<typename Spec::o01>::add_parser (spec_, map_);
        S_<typename Spec::o02>::add_parser (spec_, map_);
        S_<typename Spec::o03>::add_parser (spec_, map_);
        S_<typename Spec::o04>::add_parser (spec_, map_);
        S_<typename Spec::o05>::add_parser (spec_, map_);
        S_<typename Spec::o06>::add_parser (spec_, map_);
        S_<typename Spec::o07>::add_parser (spec_, map_);
        S_<typename Spec::o08>::add_parser (spec_, map_);
        S_<typename Spec::o09>::add_parser (spec_, map_);
        S_<typename Spec::o10>::add_parser (spec_, map_);
        S_<typename Spec::o11>::add_parser (spec_, map_);
        S_<typename Spec::o12>::add_parser (spec_, map_);
        S_<typename Spec::o13>::add_parser (spec_, map_);
        S_<typename Spec::o14>::add_parser (spec_, map_);
        S_<typename Spec::o15>::add_parser (spec_, map_);
        S_<typename Spec::o16>::add_parser (spec_, map_);
        S_<typename Spec::o17>::add_parser (spec_, map_);
        S_<typename Spec::o18>::add_parser (spec_, map_);
        S_<typename Spec::o19>::add_parser (spec_, map_);
        S_<typename Spec::o20>::add_parser (spec_, map_);
        S_<typename Spec::o21>::add_parser (spec_, map_);
        S_<typename Spec::o22>::add_parser (spec_, map_);
        S_<typename Spec::o23>::add_parser (spec_, map_);
        S_<typename Spec::o24>::add_parser (spec_, map_);
        S_<typename Spec::o25>::add_parser (spec_, map_);
        S_<typename Spec::o26>::add_parser (spec_, map_);
        S_<typename Spec::o27>::add_parser (spec_, map_);
        S_<typename Spec::o28>::add_parser (spec_, map_);
        S_<typename Spec::o29>::add_parser (spec_, map_);
        S_<typename Spec::o30>::add_parser (spec_, map_);
        S_<typename Spec::o31>::add_parser (spec_, map_);
        S_<typename Spec::o32>::add_parser (spec_, map_);
        S_<typename Spec::o33>::add_parser (spec_, map_);
        S_<typename Spec::o34>::add_parser (spec_, map_);
        S_<typename Spec::o35>::add_parser (spec_, map_);
        S_<typename Spec::o36>::add_parser (spec_, map_);
        S_<typename Spec::o37>::add_parser (spec_, map_);
        S_<typename Spec::o38>::add_parser (spec_, map_);
        S_<typename Spec::o39>::add_parser (spec_, map_);
        S_<typename Spec::o40>::add_parser (spec_, map_);
        S_<typename Spec::o41>::add_parser (spec_, map_);
        S_<typename Spec::o42>::add_parser (spec_, map_);
        S_<typename Spec::o43>::add_parser (spec_, map_);
        S_<typename Spec::o44>::add_parser (spec_, map_);
        S_<typename Spec::o45>::add_parser (spec_, map_);
        S_<typename Spec::o46>::add_parser (spec_, map_);
        S_<typename Spec::o47>::add_parser (spec_, map_);
        S_<typename Spec::o48>::add_parser (spec_, map_);
        S_<typename Spec::o49>::add_parser (spec_, map_);
        S_<typename Spec::o50>::add_parser (spec_, map_);
        S_<typename Spec::o51>::add_parser (spec_, map_);
        S_<typename Spec::o52>::add_parser (spec_, map_);
        S_<typename Spec::o53>::add_parser (spec_, map_);
        S_<typename Spec::o54>::add_parser (spec_, map_);
        S_<typename Spec::o55>::add_parser (spec_, map_);
        S_<typename Spec::o56>::add_parser (spec_, map_);
        S_<typename Spec::o57>::add_parser (spec_, map_);
        S_<typename Spec::o58>::add_parser (spec_, map_);
        S_<typename Spec::o59>::add_parser (spec_, map_);
        S_<typename Spec::o60>::add_parser (spec_, map_);
        S_<typename Spec::o61>::add_parser (spec_, map_);
        S_<typename Spec::o62>::add_parser (spec_, map_);
        S_<typename Spec::o63>::add_parser (spec_, map_);
        S_<typename Spec::o64>::add_parser (spec_, map_);
        S_<typename Spec::o65>::add_parser (spec_, map_);
        S_<typename Spec::o66>::add_parser (spec_, map_);
        S_<typename Spec::o67>::add_parser (spec_, map_);
        S_<typename Spec::o68>::add_parser (spec_, map_);
        S_<typename Spec::o69>::add_parser (spec_, map_);
        S_<typename Spec::o70>::add_parser (spec_, map_);
        S_<typename Spec::o71>::add_parser (spec_, map_);
        S_<typename Spec::o72>::add_parser (spec_, map_);
        S_<typename Spec::o73>::add_parser (spec_, map_);
        S_<typename Spec::o74>::add_parser (spec_, map_);
        S_<typename Spec::o75>::add_parser (spec_, map_);
        S_<typename Spec::o76>::add_parser (spec_, map_);
        S_<typename Spec::o77>::add_parser (spec_, map_);
        S_<typename Spec::o78>::add_parser (spec_, map_);
        S_<typename Spec::o79>::add_parser (spec_, map_);
        S_<typename Spec::o80>::add_parser (spec_, map_);
        S_<typename Spec::o81>::add_parser (spec_, map_);
        S_<typename Spec::o82>::add_parser (spec_, map_);
        S_<typename Spec::o83>::add_parser (spec_, map_);
        S_<typename Spec::o84>::add_parser (spec_, map_);
        S_<typename Spec::o85>::add_parser (spec_, map_);
        S_<typename Spec::o86>::add_parser (spec_, map_);
        S_<typename Spec::o87>::add_parser (spec_, map_);
        S_<typename Spec::o88>::add_parser (spec_, map_);
        S_<typename Spec::o89>::add_parser (spec_, map_);
        S_<typename Spec::o90>::add_parser (spec_, map_);
        S_<typename Spec::o91>::add_parser (spec_, map_);
        S_<typename Spec::o92>::add_parser (spec_, map_);
        S_<typename Spec::o93>::add_parser (spec_, map_);
        S_<typename Spec::o94>::add_parser (spec_, map_);
        S_<typename Spec::o95>::add_parser (spec_, map_);
        S_<typename Spec::o96>::add_parser (spec_, map_);
        S_<typename Spec::o97>::add_parser (spec_, map_);
        S_<typename Spec::o98>::add_parser (spec_, map_);
        S_<typename Spec::o99>::add_parser (spec_, map_);
        S_<typename Spec::o100>::add_parser (spec_, map_);
      }


      typename Spec::Options
      parse (Scanner& scan,
             UnknownMode::Value option_mode = UnknownMode::fail,
             UnknownMode::Value argument_mode = UnknownMode::stop)
      {
        typename Spec::Options ops;

        S_<typename Spec::o01>::set_default (ops, spec_);
        S_<typename Spec::o02>::set_default (ops, spec_);
        S_<typename Spec::o03>::set_default (ops, spec_);
        S_<typename Spec::o04>::set_default (ops, spec_);
        S_<typename Spec::o05>::set_default (ops, spec_);
        S_<typename Spec::o06>::set_default (ops, spec_);
        S_<typename Spec::o07>::set_default (ops, spec_);
        S_<typename Spec::o08>::set_default (ops, spec_);
        S_<typename Spec::o09>::set_default (ops, spec_);
        S_<typename Spec::o10>::set_default (ops, spec_);
        S_<typename Spec::o11>::set_default (ops, spec_);
        S_<typename Spec::o12>::set_default (ops, spec_);
        S_<typename Spec::o13>::set_default (ops, spec_);
        S_<typename Spec::o14>::set_default (ops, spec_);
        S_<typename Spec::o15>::set_default (ops, spec_);
        S_<typename Spec::o16>::set_default (ops, spec_);
        S_<typename Spec::o17>::set_default (ops, spec_);
        S_<typename Spec::o18>::set_default (ops, spec_);
        S_<typename Spec::o19>::set_default (ops, spec_);
        S_<typename Spec::o20>::set_default (ops, spec_);
        S_<typename Spec::o21>::set_default (ops, spec_);
        S_<typename Spec::o22>::set_default (ops, spec_);
        S_<typename Spec::o23>::set_default (ops, spec_);
        S_<typename Spec::o24>::set_default (ops, spec_);
        S_<typename Spec::o25>::set_default (ops, spec_);
        S_<typename Spec::o26>::set_default (ops, spec_);
        S_<typename Spec::o27>::set_default (ops, spec_);
        S_<typename Spec::o28>::set_default (ops, spec_);
        S_<typename Spec::o29>::set_default (ops, spec_);
        S_<typename Spec::o30>::set_default (ops, spec_);
        S_<typename Spec::o31>::set_default (ops, spec_);
        S_<typename Spec::o32>::set_default (ops, spec_);
        S_<typename Spec::o33>::set_default (ops, spec_);
        S_<typename Spec::o34>::set_default (ops, spec_);
        S_<typename Spec::o35>::set_default (ops, spec_);
        S_<typename Spec::o36>::set_default (ops, spec_);
        S_<typename Spec::o37>::set_default (ops, spec_);
        S_<typename Spec::o38>::set_default (ops, spec_);
        S_<typename Spec::o39>::set_default (ops, spec_);
        S_<typename Spec::o40>::set_default (ops, spec_);
        S_<typename Spec::o41>::set_default (ops, spec_);
        S_<typename Spec::o42>::set_default (ops, spec_);
        S_<typename Spec::o43>::set_default (ops, spec_);
        S_<typename Spec::o44>::set_default (ops, spec_);
        S_<typename Spec::o45>::set_default (ops, spec_);
        S_<typename Spec::o46>::set_default (ops, spec_);
        S_<typename Spec::o47>::set_default (ops, spec_);
        S_<typename Spec::o48>::set_default (ops, spec_);
        S_<typename Spec::o49>::set_default (ops, spec_);
        S_<typename Spec::o50>::set_default (ops, spec_);
        S_<typename Spec::o51>::set_default (ops, spec_);
        S_<typename Spec::o52>::set_default (ops, spec_);
        S_<typename Spec::o53>::set_default (ops, spec_);
        S_<typename Spec::o54>::set_default (ops, spec_);
        S_<typename Spec::o55>::set_default (ops, spec_);
        S_<typename Spec::o56>::set_default (ops, spec_);
        S_<typename Spec::o57>::set_default (ops, spec_);
        S_<typename Spec::o58>::set_default (ops, spec_);
        S_<typename Spec::o59>::set_default (ops, spec_);
        S_<typename Spec::o60>::set_default (ops, spec_);
        S_<typename Spec::o61>::set_default (ops, spec_);
        S_<typename Spec::o62>::set_default (ops, spec_);
        S_<typename Spec::o63>::set_default (ops, spec_);
        S_<typename Spec::o64>::set_default (ops, spec_);
        S_<typename Spec::o65>::set_default (ops, spec_);
        S_<typename Spec::o66>::set_default (ops, spec_);
        S_<typename Spec::o67>::set_default (ops, spec_);
        S_<typename Spec::o68>::set_default (ops, spec_);
        S_<typename Spec::o69>::set_default (ops, spec_);
        S_<typename Spec::o70>::set_default (ops, spec_);
        S_<typename Spec::o71>::set_default (ops, spec_);
        S_<typename Spec::o72>::set_default (ops, spec_);
        S_<typename Spec::o73>::set_default (ops, spec_);
        S_<typename Spec::o74>::set_default (ops, spec_);
        S_<typename Spec::o75>::set_default (ops, spec_);
        S_<typename Spec::o76>::set_default (ops, spec_);
        S_<typename Spec::o77>::set_default (ops, spec_);
        S_<typename Spec::o78>::set_default (ops, spec_);
        S_<typename Spec::o79>::set_default (ops, spec_);
        S_<typename Spec::o80>::set_default (ops, spec_);
        S_<typename Spec::o81>::set_default (ops, spec_);
        S_<typename Spec::o82>::set_default (ops, spec_);
        S_<typename Spec::o83>::set_default (ops, spec_);
        S_<typename Spec::o84>::set_default (ops, spec_);
        S_<typename Spec::o85>::set_default (ops, spec_);
        S_<typename Spec::o86>::set_default (ops, spec_);
        S_<typename Spec::o87>::set_default (ops, spec_);
        S_<typename Spec::o88>::set_default (ops, spec_);
        S_<typename Spec::o89>::set_default (ops, spec_);
        S_<typename Spec::o90>::set_default (ops, spec_);
        S_<typename Spec::o91>::set_default (ops, spec_);
        S_<typename Spec::o92>::set_default (ops, spec_);
        S_<typename Spec::o93>::set_default (ops, spec_);
        S_<typename Spec::o94>::set_default (ops, spec_);
        S_<typename Spec::o95>::set_default (ops, spec_);
        S_<typename Spec::o96>::set_default (ops, spec_);
        S_<typename Spec::o97>::set_default (ops, spec_);
        S_<typename Spec::o98>::set_default (ops, spec_);
        S_<typename Spec::o99>::set_default (ops, spec_);
        S_<typename Spec::o100>::set_default (ops, spec_);

        for (Char const* s (scan.peek ()); s != Scanner::eos; s = scan.peek ())
        {
          tout << "looking at \"" << s << "\"";

          //@@ Std::
          //
          if (strcmp (s, "--") == 0)
          {
            // We don't want to remove '--' if our option mode is skip.
            //
            if (option_mode == UnknownMode::skip)
              scan.skip ();
            else
              scan.next ();

            break;
          }

          typename Map::ConstIterator it (map_.find (s));

          if (it != map_.end ())
          {
            tout << "found parser for \"" << s << "\"";

            s = scan.next ();
            (*(it->second)) (s, scan, &ops);
          }
          else if (s[0] == '-')
          {
            // Unknown option.
            //
            switch (option_mode)
            {
            case UnknownMode::skip:
              {
                scan.skip ();
                continue;
              }
            case UnknownMode::stop:
              {
                break;
              }
            case UnknownMode::fail:
              {
                throw UnexpectedOption (s);
              }
            }

            break; // stop case
          }
          else
          {
            // Something else.
            //
            switch (argument_mode)
            {
            case UnknownMode::skip:
              {
                scan.skip ();
                continue;
              }
            case UnknownMode::stop:
              {
                break;
              }
            case UnknownMode::fail:
              {
                throw UnexpectedArgument (s);
              }
            }

            break; // stop case
          }
        }

        return ops;
      }

    private:
      Map map_;
      Spec spec_;
    };

    //
    //
    //

    template <typename Spec>
    typename Spec::Options
    parse (Spec const& s,
           Arguments& args,
           UnknownMode::Value option_mode = UnknownMode::fail,
           UnknownMode::Value argument_mode = UnknownMode::stop)
    {
      Scanner scan (args, Scanner::Action::erase);
      OptionsParser<Spec> parser (s);

      return parser.parse (scan, option_mode, argument_mode);
    }

    template <typename Options>
    Options
    parse (Arguments& args,
           UnknownMode::Value option_mode = UnknownMode::fail,
           UnknownMode::Value argument_mode = UnknownMode::stop)
    {
      OptionsSpec<Options> spec;
      return parse (spec, args, option_mode, argument_mode);
    }

    template <typename Spec>
    typename Spec::Options
    parse (Spec const& s,
           Int& argc,
           Char** argv,
           UnknownMode::Value option_mode = UnknownMode::fail,
           UnknownMode::Value argument_mode = UnknownMode::stop)
    {
      BasicArguments args (argc, argv);
      return parse (s, args, option_mode, argument_mode);
    }

    template <typename Options>
    Options
    parse (Int& argc,
           Char** argv,
           UnknownMode::Value option_mode = UnknownMode::fail,
           UnknownMode::Value argument_mode = UnknownMode::stop)
    {
      OptionsSpec<Options> spec;

      return parse (spec, argc, argv, option_mode, argument_mode);
    }
  }
}

#include <cult/cli/options-parser.ixx>
#include <cult/cli/options-parser.txx>

#endif  // CULT_CLI_OPTIONS_PARSER_HXX
