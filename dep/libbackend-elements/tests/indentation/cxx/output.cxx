if (true)
{
  // Hello there
  //
  a ();
}
else
{
  b ();
}

if (false)
{
  if (true)
  {
    // test
  }
  else
  {
    // test
    b ();
  }
}

namespace a
{
  void f ();
}

#if defined(__HP_aCC) && __HP_aCC <= 39999
#include <foo.h>
#endif

namespace b
{
  void f ();
}

do
  f ();
while (false);

do
{
  f ();
}
while (false);

do
{
  if (f ())
  {
    g ();
  }
}
while (false);

do
{
  do
    f ();
  while (false);
}
while (false);

do
{
  do
  {
    f ();
  }
  while (false);
}
while (false);

