// file      : cult/cli/options-spec.txx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace Cult
{
  namespace CLI
  {
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
    Void*
    OptionsSpec<Options<k01, T01,
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
                        k100, T100> >::
    option (Char const* k) const
    {
      Void* r (0);

      if (k == k01) r = (Void*) (&o01_); else
      if (k == k02) r = (Void*) (&o02_); else
      if (k == k03) r = (Void*) (&o03_); else
      if (k == k04) r = (Void*) (&o04_); else
      if (k == k05) r = (Void*) (&o05_); else
      if (k == k06) r = (Void*) (&o06_); else
      if (k == k07) r = (Void*) (&o07_); else
      if (k == k08) r = (Void*) (&o08_); else
      if (k == k09) r = (Void*) (&o09_); else
      if (k == k10) r = (Void*) (&o10_); else
      if (k == k11) r = (Void*) (&o11_); else
      if (k == k12) r = (Void*) (&o12_); else
      if (k == k13) r = (Void*) (&o13_); else
      if (k == k14) r = (Void*) (&o14_); else
      if (k == k15) r = (Void*) (&o15_); else
      if (k == k16) r = (Void*) (&o16_); else
      if (k == k17) r = (Void*) (&o17_); else
      if (k == k18) r = (Void*) (&o18_); else
      if (k == k19) r = (Void*) (&o19_); else
      if (k == k20) r = (Void*) (&o20_); else
      if (k == k21) r = (Void*) (&o21_); else
      if (k == k22) r = (Void*) (&o22_); else
      if (k == k23) r = (Void*) (&o23_); else
      if (k == k24) r = (Void*) (&o24_); else
      if (k == k25) r = (Void*) (&o25_); else
      if (k == k26) r = (Void*) (&o26_); else
      if (k == k27) r = (Void*) (&o27_); else
      if (k == k28) r = (Void*) (&o28_); else
      if (k == k29) r = (Void*) (&o29_); else
      if (k == k30) r = (Void*) (&o30_); else
      if (k == k31) r = (Void*) (&o31_); else
      if (k == k32) r = (Void*) (&o32_); else
      if (k == k33) r = (Void*) (&o33_); else
      if (k == k34) r = (Void*) (&o34_); else
      if (k == k35) r = (Void*) (&o35_); else
      if (k == k36) r = (Void*) (&o36_); else
      if (k == k37) r = (Void*) (&o37_); else
      if (k == k38) r = (Void*) (&o38_); else
      if (k == k39) r = (Void*) (&o39_); else
      if (k == k40) r = (Void*) (&o40_); else
      if (k == k41) r = (Void*) (&o41_); else
      if (k == k42) r = (Void*) (&o42_); else
      if (k == k43) r = (Void*) (&o43_); else
      if (k == k44) r = (Void*) (&o44_); else
      if (k == k45) r = (Void*) (&o45_); else
      if (k == k46) r = (Void*) (&o46_); else
      if (k == k47) r = (Void*) (&o47_); else
      if (k == k48) r = (Void*) (&o48_); else
      if (k == k49) r = (Void*) (&o49_); else
      if (k == k50) r = (Void*) (&o50_); else
      if (k == k51) r = (Void*) (&o51_); else
      if (k == k52) r = (Void*) (&o52_); else
      if (k == k53) r = (Void*) (&o53_); else
      if (k == k54) r = (Void*) (&o54_); else
      if (k == k55) r = (Void*) (&o55_); else
      if (k == k56) r = (Void*) (&o56_); else
      if (k == k57) r = (Void*) (&o57_); else
      if (k == k58) r = (Void*) (&o58_); else
      if (k == k59) r = (Void*) (&o59_); else
      if (k == k60) r = (Void*) (&o60_); else
      if (k == k61) r = (Void*) (&o61_); else
      if (k == k62) r = (Void*) (&o62_); else
      if (k == k63) r = (Void*) (&o63_); else
      if (k == k64) r = (Void*) (&o64_); else
      if (k == k65) r = (Void*) (&o65_); else
      if (k == k66) r = (Void*) (&o66_); else
      if (k == k67) r = (Void*) (&o67_); else
      if (k == k68) r = (Void*) (&o68_); else
      if (k == k69) r = (Void*) (&o69_); else
      if (k == k70) r = (Void*) (&o70_); else
      if (k == k71) r = (Void*) (&o71_); else
      if (k == k72) r = (Void*) (&o72_); else
      if (k == k73) r = (Void*) (&o73_); else
      if (k == k74) r = (Void*) (&o74_); else
      if (k == k75) r = (Void*) (&o75_); else
      if (k == k76) r = (Void*) (&o76_); else
      if (k == k77) r = (Void*) (&o77_); else
      if (k == k78) r = (Void*) (&o78_); else
      if (k == k79) r = (Void*) (&o79_); else
      if (k == k80) r = (Void*) (&o80_); else
      if (k == k81) r = (Void*) (&o81_); else
      if (k == k82) r = (Void*) (&o82_); else
      if (k == k83) r = (Void*) (&o83_); else
      if (k == k84) r = (Void*) (&o84_); else
      if (k == k85) r = (Void*) (&o85_); else
      if (k == k86) r = (Void*) (&o86_); else
      if (k == k87) r = (Void*) (&o87_); else
      if (k == k88) r = (Void*) (&o88_); else
      if (k == k89) r = (Void*) (&o89_); else
      if (k == k90) r = (Void*) (&o90_); else
      if (k == k91) r = (Void*) (&o91_); else
      if (k == k92) r = (Void*) (&o92_); else
      if (k == k93) r = (Void*) (&o93_); else
      if (k == k94) r = (Void*) (&o94_); else
      if (k == k95) r = (Void*) (&o95_); else
      if (k == k96) r = (Void*) (&o96_); else
      if (k == k97) r = (Void*) (&o97_); else
      if (k == k98) r = (Void*) (&o98_); else
      if (k == k99) r = (Void*) (&o99_); else
      if (k == k100) r = (Void*) (&o100_); else
      assert (false);

      return r;
    }
  }
}
