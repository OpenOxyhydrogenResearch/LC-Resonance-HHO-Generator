divert(-1)

# file      : cult/cli/mapper.hxx.m4
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2005-2010 Boris Kolpackov
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

define(`N', 100)

define(`forloop',
  `pushdef(`$1', `$2')_forloop(`$1', `$2', `$3', `$4')popdef(`$1')')

define(`_forloop',
  `$4`'ifelse($1, `$3', ,
    `define(`$1', incr($1))_forloop(`$1', `$2', `$3', `$4')')')

define(`specialization',`
template
<
forloop(`i', 1, $1, `  char const* x`'i, typename Y`'i`'ifelse(i, $1, ,`,')
')dnl
>
struct Mapper
<
forloop(`i', 1, $1, `  x`'i, Y`'i,
')dnl
forloop(`i', $1, N, `  null, Null`'ifelse(i, N, ,`,')
')dnl
>
{
`#ifdef __GNUC__'
forloop(`i', 1, $1, `  static Y`'i f (Tag<x`'i>*);
')dnl

  template <char const* x>
  struct Selector
  {
    typedef typeof (Mapper::f ((Tag<x>*) (0))) Type;
  };
`#else'
  template <char const* x>
  struct Selector
  {
    typedef typename if_<same<x, x1>::r, Y1,ifelse($1, 1, ` Void', `
    typename Mapper
    <
forloop(`i', 2, $1, `      x`'i, Y`'i`'ifelse(i, $1, ,`,')
')    >::template Selector<x>::Type')>::Type Type;
  };
`#endif'
};
')

divert(0)dnl

template
<
forloop(`i', 1, incr(N),
  `  char const* x`'i`'ifelse(i, 1, ,`= null'), dnl
typename Y`'i`'ifelse(i, 1, ,`= Null')`'ifelse(i, incr(N), ,`,')
')dnl
>
struct Mapper;

forloop(`n', 1, N, `specialization(n)')
