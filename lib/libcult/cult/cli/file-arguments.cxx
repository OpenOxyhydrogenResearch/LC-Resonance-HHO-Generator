// file      : cult/cli/file-arguments.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cstring> // strcmp
#include <fstream>

#include <cult/cli/file-arguments.hxx>

namespace Cult
{
  namespace CLI
  {
    FileArguments::
    ~FileArguments ()
    {
    }

    FileArguments::
    FileArguments (Int argc, Char const* const* argv, Char const* op)
    {
      using namespace std;

      if (argc == 0)
        return;

      args_.push_back (argv[0]);

      Boolean skip (false);

      for (Int i (1); i < argc; ++i)
      {
        if (!skip)
        {
          if (strcmp (argv[i], "--") == 0)
          {
            skip = true;
          }
          else if (strcmp (argv[i], op) == 0)
          {
            ++i;

            if (i >= argc)
              throw OptionFile ("missing file name");

            ifstream is (argv[i]);

            if (!is.is_open ())
              throw OptionFile (argv[i], "unable to open in read mode");

            while (!is.eof ())
            {
              String line;
              getline (is, line);

              if (is.fail () && !is.eof ())
                throw OptionFile (argv[i], "read failure");

              Size size (line.size ());

              // Trim the line from leading and trailing whitespaces.
              //
              if (size != 0)
              {
                const Char* f (line.data ());
                const Char* l (f + size);

                const Char* of (f);
                while (f < l && (*f == ' ' || *f == '\t' || *f == '\r'))
                  ++f;

                --l;

                const Char* ol (l);
                while (l > f && (*l == ' ' || *l == '\t' || *l == '\r'))
                  --l;

                if (f != of || l != ol)
                  line = f <= l ? String (f, l - f + 1) : String ();
              }

              if (line.empty () || line[0] == '#')
                continue; // Ignore empty lines, those that start with #

              Size pos (line.find (' '));

              if (pos == String::npos)
                args_.push_back (line);
              else
              {
                Size size (line.size ());

                args_.push_back (String (line, 0, pos));

                // Skip leading whitespaces in the argument.
                //
                for (pos++; pos < size; pos++)
                {
                  Char c (line[pos]);

                  if (c != ' ' && c != '\t' && c != '\r')
                    break;
                }

                args_.push_back (String (line, pos));
              }
            }

            continue;
          }
        }

        args_.push_back (argv[i]);
      }
    }
  }
}
