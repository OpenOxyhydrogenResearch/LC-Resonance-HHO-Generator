// file      : cult/cli/options-spec.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_CLI_OPTIONS_SPEC_HXX
#define CULT_CLI_OPTIONS_SPEC_HXX

#include <cult/types.hxx>

#include <cult/cli/options.hxx>

namespace Cult
{
  namespace CLI
  {
    template <Char const* k, typename T>
    class OptionSpec
    {
    public:
      static Char const* const key;
      typedef T Type;

    public:
      ~OptionSpec ()
      {
      }

      OptionSpec ()
          : default_value_ (),
            name_ ("--")
      {
        name_ += k;
      }

      T const&
      default_value () const
      {
        return default_value_;
      }

      Void
      default_value (T const& value)
      {
        default_value_ = value;
      }

      //@@ bad name
      //
      Char const*
      name () const
      {
        return name_.c_str ();
      }

    private:
      T default_value_;
      String name_;
    };

    template <Char const* k, typename T>
    struct OptionSpecType
    {
      typedef OptionSpec<k, T> Type;
    };

    template <>
    struct OptionSpecType<Bits::null, Bits::Null>
    {
      typedef Bits::Null Type;
    };


    template <Char const* k, typename T>
    Char const* const OptionSpec<k, T>::key = k;

    template <typename>
    class OptionsSpec;

    template <Char const* k01, typename T01,
              Char const* k02, typename T02,
              Char const* k03, typename T03,
              Char const* k04, typename T04,
              Char const* k05, typename T05,
              Char const* k06, typename T06,
              Char const* k07, typename T07,
              Char const* k08, typename T08,
              Char const* k09, typename T09,
              Char const* k10, typename T10,
              Char const* k11, typename T11,
              Char const* k12, typename T12,
              Char const* k13, typename T13,
              Char const* k14, typename T14,
              Char const* k15, typename T15,
              Char const* k16, typename T16,
              Char const* k17, typename T17,
              Char const* k18, typename T18,
              Char const* k19, typename T19,
              Char const* k20, typename T20,
              Char const* k21, typename T21,
              Char const* k22, typename T22,
              Char const* k23, typename T23,
              Char const* k24, typename T24,
              Char const* k25, typename T25,
              Char const* k26, typename T26,
              Char const* k27, typename T27,
              Char const* k28, typename T28,
              Char const* k29, typename T29,
              Char const* k30, typename T30,
              Char const* k31, typename T31,
              Char const* k32, typename T32,
              Char const* k33, typename T33,
              Char const* k34, typename T34,
              Char const* k35, typename T35,
              Char const* k36, typename T36,
              Char const* k37, typename T37,
              Char const* k38, typename T38,
              Char const* k39, typename T39,
              Char const* k40, typename T40,
              Char const* k41, typename T41,
              Char const* k42, typename T42,
              Char const* k43, typename T43,
              Char const* k44, typename T44,
              Char const* k45, typename T45,
              Char const* k46, typename T46,
              Char const* k47, typename T47,
              Char const* k48, typename T48,
              Char const* k49, typename T49,
              Char const* k50, typename T50,
              Char const* k51, typename T51,
              Char const* k52, typename T52,
              Char const* k53, typename T53,
              Char const* k54, typename T54,
              Char const* k55, typename T55,
              Char const* k56, typename T56,
              Char const* k57, typename T57,
              Char const* k58, typename T58,
              Char const* k59, typename T59,
              Char const* k60, typename T60,
              Char const* k61, typename T61,
              Char const* k62, typename T62,
              Char const* k63, typename T63,
              Char const* k64, typename T64,
              Char const* k65, typename T65,
              Char const* k66, typename T66,
              Char const* k67, typename T67,
              Char const* k68, typename T68,
              Char const* k69, typename T69,
              Char const* k70, typename T70,
              Char const* k71, typename T71,
              Char const* k72, typename T72,
              Char const* k73, typename T73,
              Char const* k74, typename T74,
              Char const* k75, typename T75,
              Char const* k76, typename T76,
              Char const* k77, typename T77,
              Char const* k78, typename T78,
              Char const* k79, typename T79,
              Char const* k80, typename T80,
              Char const* k81, typename T81,
              Char const* k82, typename T82,
              Char const* k83, typename T83,
              Char const* k84, typename T84,
              Char const* k85, typename T85,
              Char const* k86, typename T86,
              Char const* k87, typename T87,
              Char const* k88, typename T88,
              Char const* k89, typename T89,
              Char const* k90, typename T90,
              Char const* k91, typename T91,
              Char const* k92, typename T92,
              Char const* k93, typename T93,
              Char const* k94, typename T94,
              Char const* k95, typename T95,
              Char const* k96, typename T96,
              Char const* k97, typename T97,
              Char const* k98, typename T98,
              Char const* k99, typename T99,
              Char const* k100, typename T100>

    class OptionsSpec<Options<k01, T01,
                              k02, T02,
                              k03, T03,
                              k04, T04,
                              k05, T05,
                              k06, T06,
                              k07, T07,
                              k08, T08,
                              k09, T09,
                              k10, T10,
                              k11, T11,
                              k12, T12,
                              k13, T13,
                              k14, T14,
                              k15, T15,
                              k16, T16,
                              k17, T17,
                              k18, T18,
                              k19, T19,
                              k20, T20,
                              k21, T21,
                              k22, T22,
                              k23, T23,
                              k24, T24,
                              k25, T25,
                              k26, T26,
                              k27, T27,
                              k28, T28,
                              k29, T29,
                              k30, T30,
                              k31, T31,
                              k32, T32,
                              k33, T33,
                              k34, T34,
                              k35, T35,
                              k36, T36,
                              k37, T37,
                              k38, T38,
                              k39, T39,
                              k40, T40,
                              k41, T41,
                              k42, T42,
                              k43, T43,
                              k44, T44,
                              k45, T45,
                              k46, T46,
                              k47, T47,
                              k48, T48,
                              k49, T49,
                              k50, T50,
                              k51, T51,
                              k52, T52,
                              k53, T53,
                              k54, T54,
                              k55, T55,
                              k56, T56,
                              k57, T57,
                              k58, T58,
                              k59, T59,
                              k60, T60,
                              k61, T61,
                              k62, T62,
                              k63, T63,
                              k64, T64,
                              k65, T65,
                              k66, T66,
                              k67, T67,
                              k68, T68,
                              k69, T69,
                              k70, T70,
                              k71, T71,
                              k72, T72,
                              k73, T73,
                              k74, T74,
                              k75, T75,
                              k76, T76,
                              k77, T77,
                              k78, T78,
                              k79, T79,
                              k80, T80,
                              k81, T81,
                              k82, T82,
                              k83, T83,
                              k84, T84,
                              k85, T85,
                              k86, T86,
                              k87, T87,
                              k88, T88,
                              k89, T89,
                              k90, T90,
                              k91, T91,
                              k92, T92,
                              k93, T93,
                              k94, T94,
                              k95, T95,
                              k96, T96,
                              k97, T97,
                              k98, T98,
                              k99, T99,
                              k100, T100> >
    {
    public:
      typedef CLI::Options<k01, T01,
                           k02, T02,
                           k03, T03,
                           k04, T04,
                           k05, T05,
                           k06, T06,
                           k07, T07,
                           k08, T08,
                           k09, T09,
                           k10, T10,
                           k11, T11,
                           k12, T12,
                           k13, T13,
                           k14, T14,
                           k15, T15,
                           k16, T16,
                           k17, T17,
                           k18, T18,
                           k19, T19,
                           k20, T20,
                           k21, T21,
                           k22, T22,
                           k23, T23,
                           k24, T24,
                           k25, T25,
                           k26, T26,
                           k27, T27,
                           k28, T28,
                           k29, T29,
                           k30, T30,
                           k31, T31,
                           k32, T32,
                           k33, T33,
                           k34, T34,
                           k35, T35,
                           k36, T36,
                           k37, T37,
                           k38, T38,
                           k39, T39,
                           k40, T40,
                           k41, T41,
                           k42, T42,
                           k43, T43,
                           k44, T44,
                           k45, T45,
                           k46, T46,
                           k47, T47,
                           k48, T48,
                           k49, T49,
                           k50, T50,
                           k51, T51,
                           k52, T52,
                           k53, T53,
                           k54, T54,
                           k55, T55,
                           k56, T56,
                           k57, T57,
                           k58, T58,
                           k59, T59,
                           k60, T60,
                           k61, T61,
                           k62, T62,
                           k63, T63,
                           k64, T64,
                           k65, T65,
                           k66, T66,
                           k67, T67,
                           k68, T68,
                           k69, T69,
                           k70, T70,
                           k71, T71,
                           k72, T72,
                           k73, T73,
                           k74, T74,
                           k75, T75,
                           k76, T76,
                           k77, T77,
                           k78, T78,
                           k79, T79,
                           k80, T80,
                           k81, T81,
                           k82, T82,
                           k83, T83,
                           k84, T84,
                           k85, T85,
                           k86, T86,
                           k87, T87,
                           k88, T88,
                           k89, T89,
                           k90, T90,
                           k91, T91,
                           k92, T92,
                           k93, T93,
                           k94, T94,
                           k95, T95,
                           k96, T96,
                           k97, T97,
                           k98, T98,
                           k99, T99,
                           k100, T100> Options;

      typedef typename OptionSpecType<k01, T01>::Type o01;
      typedef typename OptionSpecType<k02, T02>::Type o02;
      typedef typename OptionSpecType<k03, T03>::Type o03;
      typedef typename OptionSpecType<k04, T04>::Type o04;
      typedef typename OptionSpecType<k05, T05>::Type o05;
      typedef typename OptionSpecType<k06, T06>::Type o06;
      typedef typename OptionSpecType<k07, T07>::Type o07;
      typedef typename OptionSpecType<k08, T08>::Type o08;
      typedef typename OptionSpecType<k09, T09>::Type o09;
      typedef typename OptionSpecType<k10, T10>::Type o10;
      typedef typename OptionSpecType<k11, T11>::Type o11;
      typedef typename OptionSpecType<k12, T12>::Type o12;
      typedef typename OptionSpecType<k13, T13>::Type o13;
      typedef typename OptionSpecType<k14, T14>::Type o14;
      typedef typename OptionSpecType<k15, T15>::Type o15;
      typedef typename OptionSpecType<k16, T16>::Type o16;
      typedef typename OptionSpecType<k17, T17>::Type o17;
      typedef typename OptionSpecType<k18, T18>::Type o18;
      typedef typename OptionSpecType<k19, T19>::Type o19;
      typedef typename OptionSpecType<k20, T20>::Type o20;
      typedef typename OptionSpecType<k21, T21>::Type o21;
      typedef typename OptionSpecType<k22, T22>::Type o22;
      typedef typename OptionSpecType<k23, T23>::Type o23;
      typedef typename OptionSpecType<k24, T24>::Type o24;
      typedef typename OptionSpecType<k25, T25>::Type o25;
      typedef typename OptionSpecType<k26, T26>::Type o26;
      typedef typename OptionSpecType<k27, T27>::Type o27;
      typedef typename OptionSpecType<k28, T28>::Type o28;
      typedef typename OptionSpecType<k29, T29>::Type o29;
      typedef typename OptionSpecType<k30, T30>::Type o30;
      typedef typename OptionSpecType<k31, T31>::Type o31;
      typedef typename OptionSpecType<k32, T32>::Type o32;
      typedef typename OptionSpecType<k33, T33>::Type o33;
      typedef typename OptionSpecType<k34, T34>::Type o34;
      typedef typename OptionSpecType<k35, T35>::Type o35;
      typedef typename OptionSpecType<k36, T36>::Type o36;
      typedef typename OptionSpecType<k37, T37>::Type o37;
      typedef typename OptionSpecType<k38, T38>::Type o38;
      typedef typename OptionSpecType<k39, T39>::Type o39;
      typedef typename OptionSpecType<k40, T40>::Type o40;
      typedef typename OptionSpecType<k41, T41>::Type o41;
      typedef typename OptionSpecType<k42, T42>::Type o42;
      typedef typename OptionSpecType<k43, T43>::Type o43;
      typedef typename OptionSpecType<k44, T44>::Type o44;
      typedef typename OptionSpecType<k45, T45>::Type o45;
      typedef typename OptionSpecType<k46, T46>::Type o46;
      typedef typename OptionSpecType<k47, T47>::Type o47;
      typedef typename OptionSpecType<k48, T48>::Type o48;
      typedef typename OptionSpecType<k49, T49>::Type o49;
      typedef typename OptionSpecType<k50, T50>::Type o50;
      typedef typename OptionSpecType<k51, T51>::Type o51;
      typedef typename OptionSpecType<k52, T52>::Type o52;
      typedef typename OptionSpecType<k53, T53>::Type o53;
      typedef typename OptionSpecType<k54, T54>::Type o54;
      typedef typename OptionSpecType<k55, T55>::Type o55;
      typedef typename OptionSpecType<k56, T56>::Type o56;
      typedef typename OptionSpecType<k57, T57>::Type o57;
      typedef typename OptionSpecType<k58, T58>::Type o58;
      typedef typename OptionSpecType<k59, T59>::Type o59;
      typedef typename OptionSpecType<k60, T60>::Type o60;
      typedef typename OptionSpecType<k61, T61>::Type o61;
      typedef typename OptionSpecType<k62, T62>::Type o62;
      typedef typename OptionSpecType<k63, T63>::Type o63;
      typedef typename OptionSpecType<k64, T64>::Type o64;
      typedef typename OptionSpecType<k65, T65>::Type o65;
      typedef typename OptionSpecType<k66, T66>::Type o66;
      typedef typename OptionSpecType<k67, T67>::Type o67;
      typedef typename OptionSpecType<k68, T68>::Type o68;
      typedef typename OptionSpecType<k69, T69>::Type o69;
      typedef typename OptionSpecType<k70, T70>::Type o70;
      typedef typename OptionSpecType<k71, T71>::Type o71;
      typedef typename OptionSpecType<k72, T72>::Type o72;
      typedef typename OptionSpecType<k73, T73>::Type o73;
      typedef typename OptionSpecType<k74, T74>::Type o74;
      typedef typename OptionSpecType<k75, T75>::Type o75;
      typedef typename OptionSpecType<k76, T76>::Type o76;
      typedef typename OptionSpecType<k77, T77>::Type o77;
      typedef typename OptionSpecType<k78, T78>::Type o78;
      typedef typename OptionSpecType<k79, T79>::Type o79;
      typedef typename OptionSpecType<k80, T80>::Type o80;
      typedef typename OptionSpecType<k81, T81>::Type o81;
      typedef typename OptionSpecType<k82, T82>::Type o82;
      typedef typename OptionSpecType<k83, T83>::Type o83;
      typedef typename OptionSpecType<k84, T84>::Type o84;
      typedef typename OptionSpecType<k85, T85>::Type o85;
      typedef typename OptionSpecType<k86, T86>::Type o86;
      typedef typename OptionSpecType<k87, T87>::Type o87;
      typedef typename OptionSpecType<k88, T88>::Type o88;
      typedef typename OptionSpecType<k89, T89>::Type o89;
      typedef typename OptionSpecType<k90, T90>::Type o90;
      typedef typename OptionSpecType<k91, T91>::Type o91;
      typedef typename OptionSpecType<k92, T92>::Type o92;
      typedef typename OptionSpecType<k93, T93>::Type o93;
      typedef typename OptionSpecType<k94, T94>::Type o94;
      typedef typename OptionSpecType<k95, T95>::Type o95;
      typedef typename OptionSpecType<k96, T96>::Type o96;
      typedef typename OptionSpecType<k97, T97>::Type o97;
      typedef typename OptionSpecType<k98, T98>::Type o98;
      typedef typename OptionSpecType<k99, T99>::Type o99;
      typedef typename OptionSpecType<k100, T100>::Type o100;


    private:
      typedef Bits::Mapper<k01, o01,
                           k02, o02,
                           k03, o03,
                           k04, o04,
                           k05, o05,
                           k06, o06,
                           k07, o07,
                           k08, o08,
                           k09, o09,
                           k10, o10,
                           k11, o11,
                           k12, o12,
                           k13, o13,
                           k14, o14,
                           k15, o15,
                           k16, o16,
                           k17, o17,
                           k18, o18,
                           k19, o19,
                           k20, o20,
                           k21, o21,
                           k22, o22,
                           k23, o23,
                           k24, o24,
                           k25, o25,
                           k26, o26,
                           k27, o27,
                           k28, o28,
                           k29, o29,
                           k30, o30,
                           k31, o31,
                           k32, o32,
                           k33, o33,
                           k34, o34,
                           k35, o35,
                           k36, o36,
                           k37, o37,
                           k38, o38,
                           k39, o39,
                           k40, o40,
                           k41, o41,
                           k42, o42,
                           k43, o43,
                           k44, o44,
                           k45, o45,
                           k46, o46,
                           k47, o47,
                           k48, o48,
                           k49, o49,
                           k50, o50,
                           k51, o51,
                           k52, o52,
                           k53, o53,
                           k54, o54,
                           k55, o55,
                           k56, o56,
                           k57, o57,
                           k58, o58,
                           k59, o59,
                           k60, o60,
                           k61, o61,
                           k62, o62,
                           k63, o63,
                           k64, o64,
                           k65, o65,
                           k66, o66,
                           k67, o67,
                           k68, o68,
                           k69, o69,
                           k70, o70,
                           k71, o71,
                           k72, o72,
                           k73, o73,
                           k74, o74,
                           k75, o75,
                           k76, o76,
                           k77, o77,
                           k78, o78,
                           k79, o79,
                           k80, o80,
                           k81, o81,
                           k82, o82,
                           k83, o83,
                           k84, o84,
                           k85, o85,
                           k86, o86,
                           k87, o87,
                           k88, o88,
                           k89, o89,
                           k90, o90,
                           k91, o91,
                           k92, o92,
                           k93, o93,
                           k94, o94,
                           k95, o95,
                           k96, o96,
                           k97, o97,
                           k98, o98,
                           k99, o99,
                           k100, o100> Mapper;

    public:
      template <Char const* k>
      typename Mapper::template Selector<k>::Type&
      option ()
      {
        typedef
        typename Mapper::template Selector<k>::Type
        Type;

        return *reinterpret_cast<Type*> (option (k));
      }

      template <Char const* k>
      typename Mapper::template Selector<k>::Type const&
      option () const
      {
        typedef
        typename Mapper::template Selector<k>::Type
        Type;

        return *reinterpret_cast<Type const*> (option (k));
      }

    private:
      Void*
      option (Char const*) const;

    private:
      o01 o01_;
      o02 o02_;
      o03 o03_;
      o04 o04_;
      o05 o05_;
      o06 o06_;
      o07 o07_;
      o08 o08_;
      o09 o09_;
      o10 o10_;
      o11 o11_;
      o12 o12_;
      o13 o13_;
      o14 o14_;
      o15 o15_;
      o16 o16_;
      o17 o17_;
      o18 o18_;
      o19 o19_;
      o20 o20_;
      o21 o21_;
      o22 o22_;
      o23 o23_;
      o24 o24_;
      o25 o25_;
      o26 o26_;
      o27 o27_;
      o28 o28_;
      o29 o29_;
      o30 o30_;
      o31 o31_;
      o32 o32_;
      o33 o33_;
      o34 o34_;
      o35 o35_;
      o36 o36_;
      o37 o37_;
      o38 o38_;
      o39 o39_;
      o40 o40_;
      o41 o41_;
      o42 o42_;
      o43 o43_;
      o44 o44_;
      o45 o45_;
      o46 o46_;
      o47 o47_;
      o48 o48_;
      o49 o49_;
      o50 o50_;
      o51 o51_;
      o52 o52_;
      o53 o53_;
      o54 o54_;
      o55 o55_;
      o56 o56_;
      o57 o57_;
      o58 o58_;
      o59 o59_;
      o60 o60_;
      o61 o61_;
      o62 o62_;
      o63 o63_;
      o64 o64_;
      o65 o65_;
      o66 o66_;
      o67 o67_;
      o68 o68_;
      o69 o69_;
      o70 o70_;
      o71 o71_;
      o72 o72_;
      o73 o73_;
      o74 o74_;
      o75 o75_;
      o76 o76_;
      o77 o77_;
      o78 o78_;
      o79 o79_;
      o80 o80_;
      o81 o81_;
      o82 o82_;
      o83 o83_;
      o84 o84_;
      o85 o85_;
      o86 o86_;
      o87 o87_;
      o88 o88_;
      o89 o89_;
      o90 o90_;
      o91 o91_;
      o92 o92_;
      o93 o93_;
      o94 o94_;
      o95 o95_;
      o96 o96_;
      o97 o97_;
      o98 o98_;
      o99 o99_;
      o100 o100_;
    };
  }
}

#include <cult/cli/options-spec.ixx>
#include <cult/cli/options-spec.txx>

#endif  // CULT_CLI_OPTIONS_SPEC_HXX
