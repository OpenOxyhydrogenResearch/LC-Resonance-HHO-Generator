// file      : cult/cli/options.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_CLI_OPTIONS_HXX
#define CULT_CLI_OPTIONS_HXX

#include <cult/types.hxx>

#include <cassert>

namespace Cult
{
  namespace CLI
  {
    namespace Bits
    {
      template <Boolean t, typename X, typename Y>
      struct if_;

      template <typename X, typename Y>
      struct if_<true, X, Y>
      {
        typedef X Type;
      };

      template <typename X, typename Y>
      struct if_<false, X, Y>
      {
        typedef Y Type;
      };

      template <Char const* x, Char const* y>
      struct same
      {
        static Boolean const r = false;
      };

      template <Char const* x>
      struct same<x, x>
      {
        static Boolean const r = true;
      };

      template <Char const* x>
      struct Tag
      {
      };

      //@@ should end up in Cult::Meta
      //
      struct Null {};
      extern Char const null[];

#include <cult/cli/mapper.hxx>

    }

    template <Char const* k01, typename T01,
              Char const* k02 = Bits::null, typename T02 = Bits::Null,
              Char const* k03 = Bits::null, typename T03 = Bits::Null,
              Char const* k04 = Bits::null, typename T04 = Bits::Null,
              Char const* k05 = Bits::null, typename T05 = Bits::Null,
              Char const* k06 = Bits::null, typename T06 = Bits::Null,
              Char const* k07 = Bits::null, typename T07 = Bits::Null,
              Char const* k08 = Bits::null, typename T08 = Bits::Null,
              Char const* k09 = Bits::null, typename T09 = Bits::Null,
              Char const* k10 = Bits::null, typename T10 = Bits::Null,
              Char const* k11 = Bits::null, typename T11 = Bits::Null,
              Char const* k12 = Bits::null, typename T12 = Bits::Null,
              Char const* k13 = Bits::null, typename T13 = Bits::Null,
              Char const* k14 = Bits::null, typename T14 = Bits::Null,
              Char const* k15 = Bits::null, typename T15 = Bits::Null,
              Char const* k16 = Bits::null, typename T16 = Bits::Null,
              Char const* k17 = Bits::null, typename T17 = Bits::Null,
              Char const* k18 = Bits::null, typename T18 = Bits::Null,
              Char const* k19 = Bits::null, typename T19 = Bits::Null,
              Char const* k20 = Bits::null, typename T20 = Bits::Null,
              Char const* k21 = Bits::null, typename T21 = Bits::Null,
              Char const* k22 = Bits::null, typename T22 = Bits::Null,
              Char const* k23 = Bits::null, typename T23 = Bits::Null,
              Char const* k24 = Bits::null, typename T24 = Bits::Null,
              Char const* k25 = Bits::null, typename T25 = Bits::Null,
              Char const* k26 = Bits::null, typename T26 = Bits::Null,
              Char const* k27 = Bits::null, typename T27 = Bits::Null,
              Char const* k28 = Bits::null, typename T28 = Bits::Null,
              Char const* k29 = Bits::null, typename T29 = Bits::Null,
              Char const* k30 = Bits::null, typename T30 = Bits::Null,
              Char const* k31 = Bits::null, typename T31 = Bits::Null,
              Char const* k32 = Bits::null, typename T32 = Bits::Null,
              Char const* k33 = Bits::null, typename T33 = Bits::Null,
              Char const* k34 = Bits::null, typename T34 = Bits::Null,
              Char const* k35 = Bits::null, typename T35 = Bits::Null,
              Char const* k36 = Bits::null, typename T36 = Bits::Null,
              Char const* k37 = Bits::null, typename T37 = Bits::Null,
              Char const* k38 = Bits::null, typename T38 = Bits::Null,
              Char const* k39 = Bits::null, typename T39 = Bits::Null,
              Char const* k40 = Bits::null, typename T40 = Bits::Null,
              Char const* k41 = Bits::null, typename T41 = Bits::Null,
              Char const* k42 = Bits::null, typename T42 = Bits::Null,
              Char const* k43 = Bits::null, typename T43 = Bits::Null,
              Char const* k44 = Bits::null, typename T44 = Bits::Null,
              Char const* k45 = Bits::null, typename T45 = Bits::Null,
              Char const* k46 = Bits::null, typename T46 = Bits::Null,
              Char const* k47 = Bits::null, typename T47 = Bits::Null,
              Char const* k48 = Bits::null, typename T48 = Bits::Null,
              Char const* k49 = Bits::null, typename T49 = Bits::Null,
              Char const* k50 = Bits::null, typename T50 = Bits::Null,
              Char const* k51 = Bits::null, typename T51 = Bits::Null,
              Char const* k52 = Bits::null, typename T52 = Bits::Null,
              Char const* k53 = Bits::null, typename T53 = Bits::Null,
              Char const* k54 = Bits::null, typename T54 = Bits::Null,
              Char const* k55 = Bits::null, typename T55 = Bits::Null,
              Char const* k56 = Bits::null, typename T56 = Bits::Null,
              Char const* k57 = Bits::null, typename T57 = Bits::Null,
              Char const* k58 = Bits::null, typename T58 = Bits::Null,
              Char const* k59 = Bits::null, typename T59 = Bits::Null,
              Char const* k60 = Bits::null, typename T60 = Bits::Null,
              Char const* k61 = Bits::null, typename T61 = Bits::Null,
              Char const* k62 = Bits::null, typename T62 = Bits::Null,
              Char const* k63 = Bits::null, typename T63 = Bits::Null,
              Char const* k64 = Bits::null, typename T64 = Bits::Null,
              Char const* k65 = Bits::null, typename T65 = Bits::Null,
              Char const* k66 = Bits::null, typename T66 = Bits::Null,
              Char const* k67 = Bits::null, typename T67 = Bits::Null,
              Char const* k68 = Bits::null, typename T68 = Bits::Null,
              Char const* k69 = Bits::null, typename T69 = Bits::Null,
              Char const* k70 = Bits::null, typename T70 = Bits::Null,
              Char const* k71 = Bits::null, typename T71 = Bits::Null,
              Char const* k72 = Bits::null, typename T72 = Bits::Null,
              Char const* k73 = Bits::null, typename T73 = Bits::Null,
              Char const* k74 = Bits::null, typename T74 = Bits::Null,
              Char const* k75 = Bits::null, typename T75 = Bits::Null,
              Char const* k76 = Bits::null, typename T76 = Bits::Null,
              Char const* k77 = Bits::null, typename T77 = Bits::Null,
              Char const* k78 = Bits::null, typename T78 = Bits::Null,
              Char const* k79 = Bits::null, typename T79 = Bits::Null,
              Char const* k80 = Bits::null, typename T80 = Bits::Null,
              Char const* k81 = Bits::null, typename T81 = Bits::Null,
              Char const* k82 = Bits::null, typename T82 = Bits::Null,
              Char const* k83 = Bits::null, typename T83 = Bits::Null,
              Char const* k84 = Bits::null, typename T84 = Bits::Null,
              Char const* k85 = Bits::null, typename T85 = Bits::Null,
              Char const* k86 = Bits::null, typename T86 = Bits::Null,
              Char const* k87 = Bits::null, typename T87 = Bits::Null,
              Char const* k88 = Bits::null, typename T88 = Bits::Null,
              Char const* k89 = Bits::null, typename T89 = Bits::Null,
              Char const* k90 = Bits::null, typename T90 = Bits::Null,
              Char const* k91 = Bits::null, typename T91 = Bits::Null,
              Char const* k92 = Bits::null, typename T92 = Bits::Null,
              Char const* k93 = Bits::null, typename T93 = Bits::Null,
              Char const* k94 = Bits::null, typename T94 = Bits::Null,
              Char const* k95 = Bits::null, typename T95 = Bits::Null,
              Char const* k96 = Bits::null, typename T96 = Bits::Null,
              Char const* k97 = Bits::null, typename T97 = Bits::Null,
              Char const* k98 = Bits::null, typename T98 = Bits::Null,
              Char const* k99 = Bits::null, typename T99 = Bits::Null,
              Char const* k100 = Bits::null, typename T100 = Bits::Null>
    class Options
    {
      typedef Bits::Mapper<k01, T01,
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
                           k100, T100> Mapper;

    public:
      Options ()
          : i01_ (),
            i02_ (),
            i03_ (),
            i04_ (),
            i05_ (),
            i06_ (),
            i07_ (),
            i08_ (),
            i09_ (),
            i10_ (),
            i11_ (),
            i12_ (),
            i13_ (),
            i14_ (),
            i15_ (),
            i16_ (),
            i17_ (),
            i18_ (),
            i19_ (),
            i20_ (),
            i21_ (),
            i22_ (),
            i23_ (),
            i24_ (),
            i25_ (),
            i26_ (),
            i27_ (),
            i28_ (),
            i29_ (),
            i30_ (),
            i31_ (),
            i32_ (),
            i33_ (),
            i34_ (),
            i35_ (),
            i36_ (),
            i37_ (),
            i38_ (),
            i39_ (),
            i40_ (),
            i41_ (),
            i42_ (),
            i43_ (),
            i44_ (),
            i45_ (),
            i46_ (),
            i47_ (),
            i48_ (),
            i49_ (),
            i50_ (),
            i51_ (),
            i52_ (),
            i53_ (),
            i54_ (),
            i55_ (),
            i56_ (),
            i57_ (),
            i58_ (),
            i59_ (),
            i60_ (),
            i61_ (),
            i62_ (),
            i63_ (),
            i64_ (),
            i65_ (),
            i66_ (),
            i67_ (),
            i68_ (),
            i69_ (),
            i70_ (),
            i71_ (),
            i72_ (),
            i73_ (),
            i74_ (),
            i75_ (),
            i76_ (),
            i77_ (),
            i78_ (),
            i79_ (),
            i80_ (),
            i81_ (),
            i82_ (),
            i83_ (),
            i84_ (),
            i85_ (),
            i86_ (),
            i87_ (),
            i88_ (),
            i89_ (),
            i90_ (),
            i91_ (),
            i92_ (),
            i93_ (),
            i94_ (),
            i95_ (),
            i96_ (),
            i97_ (),
            i98_ (),
            i99_ (),
            i100_ ()
      {
      }

      template <Char const* k>
      typename Mapper::template Selector<k>::Type&
      value ()
      {
        typedef
	typename Mapper::template Selector<k>::Type
	Type;

        return *reinterpret_cast<Type*> (value (k));
      }

      template <Char const* k>
      typename Mapper::template Selector<k>::Type const&
      value () const
      {
        typedef
	typename Mapper::template Selector<k>::Type
	Type;

        return *reinterpret_cast<Type const*> (value (k));
      }

    private:
      Void*
      value (Char const*) const;

    private:
      T01 i01_;
      T02 i02_;
      T03 i03_;
      T04 i04_;
      T05 i05_;
      T06 i06_;
      T07 i07_;
      T08 i08_;
      T09 i09_;
      T10 i10_;
      T11 i11_;
      T12 i12_;
      T13 i13_;
      T14 i14_;
      T15 i15_;
      T16 i16_;
      T17 i17_;
      T18 i18_;
      T19 i19_;
      T20 i20_;
      T21 i21_;
      T22 i22_;
      T23 i23_;
      T24 i24_;
      T25 i25_;
      T26 i26_;
      T27 i27_;
      T28 i28_;
      T29 i29_;
      T30 i30_;
      T31 i31_;
      T32 i32_;
      T33 i33_;
      T34 i34_;
      T35 i35_;
      T36 i36_;
      T37 i37_;
      T38 i38_;
      T39 i39_;
      T40 i40_;
      T41 i41_;
      T42 i42_;
      T43 i43_;
      T44 i44_;
      T45 i45_;
      T46 i46_;
      T47 i47_;
      T48 i48_;
      T49 i49_;
      T50 i50_;
      T51 i51_;
      T52 i52_;
      T53 i53_;
      T54 i54_;
      T55 i55_;
      T56 i56_;
      T57 i57_;
      T58 i58_;
      T59 i59_;
      T60 i60_;
      T61 i61_;
      T62 i62_;
      T63 i63_;
      T64 i64_;
      T65 i65_;
      T66 i66_;
      T67 i67_;
      T68 i68_;
      T69 i69_;
      T70 i70_;
      T71 i71_;
      T72 i72_;
      T73 i73_;
      T74 i74_;
      T75 i75_;
      T76 i76_;
      T77 i77_;
      T78 i78_;
      T79 i79_;
      T80 i80_;
      T81 i81_;
      T82 i82_;
      T83 i83_;
      T84 i84_;
      T85 i85_;
      T86 i86_;
      T87 i87_;
      T88 i88_;
      T89 i89_;
      T90 i90_;
      T91 i91_;
      T92 i92_;
      T93 i93_;
      T94 i94_;
      T95 i95_;
      T96 i96_;
      T97 i97_;
      T98 i98_;
      T99 i99_;
      T100 i100_;
    };
  }
}

#include <cult/cli/options.ixx>
#include <cult/cli/options.txx>

#endif  // CULT_CLI_OPTIONS_HXX
