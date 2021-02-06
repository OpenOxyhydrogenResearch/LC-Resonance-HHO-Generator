// file      : cult/cli/options.txx
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
    Options<k01, T01,
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
            k100, T100>::
    value (Char const* k) const
    {
      Void* r (0);

      if (k == k01) r = (Void*) (&i01_); else
      if (k == k02) r = (Void*) (&i02_); else
      if (k == k03) r = (Void*) (&i03_); else
      if (k == k04) r = (Void*) (&i04_); else
      if (k == k05) r = (Void*) (&i05_); else
      if (k == k06) r = (Void*) (&i06_); else
      if (k == k07) r = (Void*) (&i07_); else
      if (k == k08) r = (Void*) (&i08_); else
      if (k == k09) r = (Void*) (&i09_); else
      if (k == k10) r = (Void*) (&i10_); else
      if (k == k11) r = (Void*) (&i11_); else
      if (k == k12) r = (Void*) (&i12_); else
      if (k == k13) r = (Void*) (&i13_); else
      if (k == k14) r = (Void*) (&i14_); else
      if (k == k15) r = (Void*) (&i15_); else
      if (k == k16) r = (Void*) (&i16_); else
      if (k == k17) r = (Void*) (&i17_); else
      if (k == k18) r = (Void*) (&i18_); else
      if (k == k19) r = (Void*) (&i19_); else
      if (k == k20) r = (Void*) (&i20_); else
      if (k == k21) r = (Void*) (&i21_); else
      if (k == k22) r = (Void*) (&i22_); else
      if (k == k23) r = (Void*) (&i23_); else
      if (k == k24) r = (Void*) (&i24_); else
      if (k == k25) r = (Void*) (&i25_); else
      if (k == k26) r = (Void*) (&i26_); else
      if (k == k27) r = (Void*) (&i27_); else
      if (k == k28) r = (Void*) (&i28_); else
      if (k == k29) r = (Void*) (&i29_); else
      if (k == k30) r = (Void*) (&i30_); else
      if (k == k31) r = (Void*) (&i31_); else
      if (k == k32) r = (Void*) (&i32_); else
      if (k == k33) r = (Void*) (&i33_); else
      if (k == k34) r = (Void*) (&i34_); else
      if (k == k35) r = (Void*) (&i35_); else
      if (k == k36) r = (Void*) (&i36_); else
      if (k == k37) r = (Void*) (&i37_); else
      if (k == k38) r = (Void*) (&i38_); else
      if (k == k39) r = (Void*) (&i39_); else
      if (k == k40) r = (Void*) (&i40_); else
      if (k == k41) r = (Void*) (&i41_); else
      if (k == k42) r = (Void*) (&i42_); else
      if (k == k43) r = (Void*) (&i43_); else
      if (k == k44) r = (Void*) (&i44_); else
      if (k == k45) r = (Void*) (&i45_); else
      if (k == k46) r = (Void*) (&i46_); else
      if (k == k47) r = (Void*) (&i47_); else
      if (k == k48) r = (Void*) (&i48_); else
      if (k == k49) r = (Void*) (&i49_); else
      if (k == k50) r = (Void*) (&i50_); else
      if (k == k51) r = (Void*) (&i51_); else
      if (k == k52) r = (Void*) (&i52_); else
      if (k == k53) r = (Void*) (&i53_); else
      if (k == k54) r = (Void*) (&i54_); else
      if (k == k55) r = (Void*) (&i55_); else
      if (k == k56) r = (Void*) (&i56_); else
      if (k == k57) r = (Void*) (&i57_); else
      if (k == k58) r = (Void*) (&i58_); else
      if (k == k59) r = (Void*) (&i59_); else
      if (k == k60) r = (Void*) (&i60_); else
      if (k == k61) r = (Void*) (&i61_); else
      if (k == k62) r = (Void*) (&i62_); else
      if (k == k63) r = (Void*) (&i63_); else
      if (k == k64) r = (Void*) (&i64_); else
      if (k == k65) r = (Void*) (&i65_); else
      if (k == k66) r = (Void*) (&i66_); else
      if (k == k67) r = (Void*) (&i67_); else
      if (k == k68) r = (Void*) (&i68_); else
      if (k == k69) r = (Void*) (&i69_); else
      if (k == k70) r = (Void*) (&i70_); else
      if (k == k71) r = (Void*) (&i71_); else
      if (k == k72) r = (Void*) (&i72_); else
      if (k == k73) r = (Void*) (&i73_); else
      if (k == k74) r = (Void*) (&i74_); else
      if (k == k75) r = (Void*) (&i75_); else
      if (k == k76) r = (Void*) (&i76_); else
      if (k == k77) r = (Void*) (&i77_); else
      if (k == k78) r = (Void*) (&i78_); else
      if (k == k79) r = (Void*) (&i79_); else
      if (k == k80) r = (Void*) (&i80_); else
      if (k == k81) r = (Void*) (&i81_); else
      if (k == k82) r = (Void*) (&i82_); else
      if (k == k83) r = (Void*) (&i83_); else
      if (k == k84) r = (Void*) (&i84_); else
      if (k == k85) r = (Void*) (&i85_); else
      if (k == k86) r = (Void*) (&i86_); else
      if (k == k87) r = (Void*) (&i87_); else
      if (k == k88) r = (Void*) (&i88_); else
      if (k == k89) r = (Void*) (&i89_); else
      if (k == k90) r = (Void*) (&i90_); else
      if (k == k91) r = (Void*) (&i91_); else
      if (k == k92) r = (Void*) (&i92_); else
      if (k == k93) r = (Void*) (&i93_); else
      if (k == k94) r = (Void*) (&i94_); else
      if (k == k95) r = (Void*) (&i95_); else
      if (k == k96) r = (Void*) (&i96_); else
      if (k == k97) r = (Void*) (&i97_); else
      if (k == k98) r = (Void*) (&i98_); else
      if (k == k99) r = (Void*) (&i99_); else
      if (k == k100) r = (Void*) (&i100_); else
      assert (false);

      return r;
    }
  }
}
