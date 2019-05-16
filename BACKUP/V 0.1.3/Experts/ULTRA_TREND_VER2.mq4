//+------------------------------------------------------------------+
//|                                             ULTRA_TREND_VER2.mq4 |
//|                      Copyright © 2008, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005, FxCompas Project."
#property link      "http://www.fxcompas.com"

#property indicator_separate_window
#property indicator_buffers 2
#property indicator_color1 Aqua
#property indicator_color2 Red

double g_ibuf_76[];
extern int key = 8763765;
extern double Smooth = 1.0;
extern int bars = 300;
extern int X_Filtr = 20;
extern int Progression = 10;
extern int Len = 12;
extern int Sensitivity = 30;
int gi_112 = 1;
double gd_116 = 100.0;
int gi_124 = 0;
int gi_128 = 0;
double gd_132 = 0.0;
double gd_140;
double gd_148;
double gd_156;
double gd_164;
double gd_172;
double gd_180;
double gd_188;
double gd_196;
double gd_204 = 0.0;
int gi_212;
int gi_216;
int gi_220;
int gi_224;
int gi_228;
int gi_232;
int gi_236;
int gi_240;
int gi_244;
int gi_248;
int gi_252;
int gi_256;
int gi_260 = 0;
double gd_264;
double gd_272;
double gd_280;
double gd_288;
double gd_296;
double gd_304;
double gd_312;
double gd_320;
double gd_328;
double gd_336;
double gd_344;
double gd_352;
double gd_360;
double gd_368;
double gd_376;
double gd_384;
double gd_392;
double gd_400;
double gd_408;
double gd_416;
double gd_424;
double gd_432;
double gd_440;
double gd_448;
double gd_456;
double gd_464 = 0.0;
bool gi_472;
int gi_476;
int gi_480;
int gi_484;
int gi_488;
int gi_492 = 0;
double gda_496[128];
double gda_500[128];
double gda_504[11];
double gda_508[62];
double gda_unused_512[300];
int gi_unused_516;
int g_index_520;
int gi_524;
int gi_532;
double g_ibuf_560[];
double gda_564[15000];
double gda_568[15000];
double g_icustom_572;
double g_icustom_580 = 0.0;
int g_count_588;
int g_count_592;
int g_bars_596 = 0;

int init() {
   SetIndexStyle(0, DRAW_LINE);
   SetIndexBuffer(0, g_ibuf_76);
   SetIndexStyle(1, DRAW_LINE);
   SetIndexBuffer(1, g_ibuf_560);
   return (0);
}
/*
int start() {
   int li_16;
   int li_unused_20;
   int li_unused_0 = 10049;
   int li_4 = 15410;
   int li_8 = 398961;
   int li_12 = 31823;
   if (AccountNumber() != li_4 + 5 && AccountNumber() != li_8 + 2 && AccountNumber() != li_12 + 2) {
      Comment("Внимание! Индикатору запрещено работать на этом счете!");
      return (-1);
   }
   if (AccountNumber() != 15415 && AccountNumber() != 398963 && AccountNumber() != 31825) {
      Comment("Внимание! Индикатору запрещено работать на этом счете!");
      return (-1);
   } else {
      li_16 = key;
      if (li_16 != 34562458) {
      } else {
         loadJMAJMA();
      }
      if (Bars > g_bars_596) {
         g_bars_596 = Bars;
         li_unused_20 = 0;
         for (int l_index_24 = 0; l_index_24 < bars; l_index_24++) {
            g_count_588 = 0;
            g_count_592 = 0;
            for (int li_28 = Len; li_28 <= Len + Progression * Sensitivity; li_28 += Progression) {
               g_icustom_572 = iCustom(NULL, 0, "ULTRA_TREND_VER2", 34562458, li_28, bars, X_Filtr, 0, l_index_24);
               g_icustom_580 = iCustom(NULL, 0, "ULTRA_TREND_VER2", 34562458, li_28, bars, X_Filtr, 0, l_index_24 + 1);
               if (g_icustom_572 > g_icustom_580) g_count_588++;
               else g_count_592++;
            }
            gda_564[l_index_24] = g_count_588;
            gda_568[l_index_24] = g_count_592;
         }
         lenars(gda_564, 1);
         lenars(gda_568, 2);
         return (0);
      }
   }
   return (0);
}
*/
int start() {

   switch (key)
      {
      case 34562458: loadJMAJMA(); break;
     default: if (Bars > g_bars_596) {
         g_bars_596 = Bars;
         for (int l_index_24 = 0; l_index_24 < bars; l_index_24++) {
            g_count_588 = 0;
            g_count_592 = 0;
            for (int li_28 = Len; li_28 <= Len + Progression * Sensitivity; li_28 += Progression) {
               g_icustom_572 = iCustom(NULL, 0, "ULTRA_TREND_VER2", 34562458, li_28, bars, X_Filtr, 0, l_index_24);
               g_icustom_580 = iCustom(NULL, 0, "ULTRA_TREND_VER2", 34562458, li_28, bars, X_Filtr, 0, l_index_24 + 1);
               if (g_icustom_572 > g_icustom_580) g_count_588++;
               else g_count_592++;
            }
            gda_564[l_index_24] = g_count_588;
            gda_568[l_index_24] = g_count_592;
         }
         lenars(gda_564, 1);
         lenars(gda_568, 2);
         return (0);
      }
   }
   return (0);
}
void loadJMAJMA() {
   double ld_0;
   loadJMA(X_Filtr);
   gi_224 = 63;
   gi_228 = 64;
   if (gi_112 == TRUE) {
      for (gi_212 = 1; gi_212 < gi_224 + 1; gi_212++) gda_496[gi_212] = -1000000;
      for (gi_212 = gi_228; gi_212 < 128; gi_212++) gda_496[gi_212] = 1000000;
      gi_112 = FALSE;
   }
   gi_472 = TRUE;
   if (Smooth <= 1.0) gd_384 = 0.0000000001;
   else gd_384 = (Smooth - 1.0) / 2.0;
   if (gd_116 < -100.0) gd_272 = 0.5;
   else {
      if (gd_116 > 100.0) gd_272 = 2.5;
      else gd_272 = gd_116 / 100.0 + 1.5;
   }
   gd_148 = MathLog(MathSqrt(gd_384));
   gd_156 = gd_148;
   if (gd_148 / MathLog(2.0) + 2.0 < 0.0) gd_164 = 0;
   else gd_164 = gd_156 / MathLog(2.0) + 2.0;
   gd_408 = gd_164;
   if (gd_408 - 2.0 >= 0.5) gd_392 = gd_408 - 2.0;
   else gd_392 = 0.5;
   gd_376 = MathSqrt(gd_384) * gd_408;
   gd_400 = gd_376 / (gd_376 + 1.0);
   gd_384 = 0.9 * gd_384;
   gd_336 = gd_384 / (gd_384 + 2.0);
   gi_472 = TRUE;
   if (bars == 0) bars = Bars;
   for (gi_128 = bars + 1000; gi_128 >= 0; gi_128--) {
      ld_0 = g_ibuf_76[gi_128];
      if (gi_488 < 61) {
         gi_488++;
         gda_508[gi_488] = ld_0;
      }
      if (gi_488 > 30) {
         if (gi_472 != FALSE) {
            gi_472 = FALSE;
            gi_216 = 0;
            for (gi_212 = 1; gi_212 < 30; gi_212++)
               if (gda_508[gi_212 + 1] != gda_508[gi_212]) gi_216 = 1;
            gi_476 = 30 * gi_216;
            if (gi_476 == 0) gd_312 = ld_0;
            else gd_312 = gda_508[1];
            gd_280 = gd_312;
            if (gi_476 > 29) gi_476 = 29;
         } else gi_476 = 0;
         for (gi_212 = gi_476; gi_212 >= 0; gi_212--) {
            if (gi_212 == 0) gd_264 = ld_0;
            else gd_264 = gda_508[31 - gi_212];
            gd_296 = gd_264 - gd_280;
            gd_328 = gd_264 - gd_312;
            if (MathAbs(gd_296) > MathAbs(gd_328)) gd_156 = MathAbs(gd_296);
            else gd_156 = MathAbs(gd_328);
            gd_416 = gd_156;
            gd_140 = gd_416 + 0.0000000001;
            if (gi_240 <= 1) gi_240 = 127;
            else gi_240--;
            if (gi_244 <= 1) gi_244 = 10;
            else gi_244--;
            if (gi_260 < 128) gi_260++;
            gd_180 = gd_180 + gd_140 - gda_504[gi_244];
            gda_504[gi_244] = gd_140;
            if (gi_260 > 10) gd_204 = gd_180 / 10.0;
            else gd_204 = gd_180 / gi_260;
            if (gi_260 == 30) g_index_520 = 0;
            if (gi_260 > 127) {
               gd_188 = gda_500[gi_240];
               gda_500[gi_240] = gd_204;
               gi_256 = 64;
               gi_248 = gi_256;
               gi_unused_516 = gi_248;
               while (gi_256 > 1) {
                  if (gda_496[gi_248] < gd_188) {
                     gi_256 /= 2;
                     gi_248 += gi_256;
                     gi_unused_516 = gi_248;
                  } else {
                     if (gda_496[gi_248] <= gd_188) gi_256 = 1;
                     else {
                        gi_256 /= 2;
                        gi_248 -= gi_256;
                        gi_unused_516 = gi_248;
                     }
                  }
               }
            } else {
               gda_500[gi_240] = gd_204;
               if (gi_224 + gi_228 > 127) {
                  gi_228--;
                  gi_248 = gi_228;
                  gi_unused_516 = gi_248;
               } else {
                  gi_224++;
                  gi_248 = gi_224;
                  gi_unused_516 = gi_248;
               }
               if (gi_224 > 96) gi_232 = 96;
               else gi_232 = gi_224;
               if (gi_228 < 32) gi_236 = 32;
               else gi_236 = gi_228;
            }
            gi_256 = 64;
            gi_252 = gi_256;
            while (gi_256 > 1) {
               if (gda_496[gi_252] >= gd_204) {
                  if (gda_496[gi_252 - 1] <= gd_204) gi_256 = 1;
                  else {
                     gi_256 /= 2;
                     gi_252 -= gi_256;
                  }
               } else {
                  gi_256 /= 2;
                  gi_252 += gi_256;
               }
               if (gi_252 == 127 && gd_204 > gda_496[127]) gi_252 = 128;
            }
            if (gi_260 > 127) {
               if (gi_248 >= gi_252) {
                  if (gi_232 + 1 > gi_252 && gi_236 - 1 < gi_252) gd_196 += gd_204;
                  else
                     if (gi_236 > gi_252 && gi_236 - 1 < gi_248) gd_196 += gda_496[gi_236 - 1];
               } else {
                  if (gi_236 >= gi_252) {
                     if (gi_232 + 1 < gi_252 && gi_232 + 1 > gi_248) gd_196 += gda_496[gi_232 + 1];
                  } else {
                     if (gi_232 + 2 > gi_252) gd_196 += gd_204;
                     else
                        if (gi_232 + 1 < gi_252 && gi_232 + 1 > gi_248) gd_196 += gda_496[gi_232 + 1];
                  }
               }
               if (gi_248 > gi_252) {
                  if (gi_236 - 1 < gi_248 && gi_232 + 1 > gi_248) gd_196 -= gda_496[gi_248];
                  else
                     if (gi_232 < gi_248 && gi_232 + 1 > gi_252) gd_196 -= gda_496[gi_232];
               } else {
                  if (gi_232 + 1 > gi_248 && gi_236 - 1 < gi_248) gd_196 -= gda_496[gi_248];
                  else
                     if (gi_236 > gi_248 && gi_236 < gi_252) gd_196 -= gda_496[gi_236];
               }
            }
            if (gi_248 <= gi_252) {
               if (gi_248 >= gi_252) gda_496[gi_252] = gd_204;
               else {
                  for (g_index_520 = gi_248 + 1; g_index_520 < gi_252; g_index_520++) gda_496[g_index_520 - 1] = gda_496[g_index_520];
                  gda_496[gi_252 - 1] = gd_204;
               }
            } else {
               for (gi_524 = gi_248 - 1; gi_524 >= gi_252; gi_524--) gda_496[gi_524 + 1] = gda_496[gi_524];
               gda_496[gi_252] = gd_204;
            }
            if (gi_260 <= 127) {
               gd_196 = 0;
               for (gi_532 = gi_236; gi_532 < gi_232 + 1; gi_532++) gd_196 += gda_496[gi_532];
            }
            gd_352 = gd_196 / (gi_232 - gi_236 + 1);
            if (gi_492 + 1 > 31) gi_492 = 31;
            else gi_492++;
            if (gi_492 <= 30) {
               if (gd_296 > 0.0) gd_280 = gd_264;
               else gd_280 = gd_264 - gd_296 * gd_400;
               if (gd_328 < 0.0) gd_312 = gd_264;
               else gd_312 = gd_264 - gd_328 * gd_400;
               gd_440 = ld_0;
               if (gi_492 != 30) continue;
               gd_448 = ld_0;
               if (MathCeil(gd_376) >= 1.0) gd_172 = MathCeil(gd_376);
               else gd_172 = 1;
               gi_484 = gd_172;
               if (MathFloor(gd_376) >= 1.0) gd_156 = MathFloor(gd_376);
               else gd_156 = 1;
               gi_480 = gd_156;
               if (gi_484 == gi_480) gd_360 = 1;
               else {
                  gd_172 = gi_484 - gi_480;
                  gd_360 = (gd_376 - gi_480) / gd_172;
               }
               if (gi_480 <= 29) gi_216 = gi_480;
               else gi_216 = 29;
               if (gi_484 <= 29) gi_220 = gi_484;
               else gi_220 = 29;
               gd_424 = (ld_0 - (gda_508[gi_488 - gi_216])) * (1 - gd_360) / gi_480 + (ld_0 - (gda_508[gi_488 - gi_220])) * gd_360 / gi_484;
            } else {
               if (gd_408 >= MathPow(MathAbs(gd_416 / gd_352), gd_392)) gd_148 = MathPow(MathAbs(gd_416 / gd_352), gd_392);
               else gd_148 = gd_408;
               if (gd_148 < 1.0) gd_156 = 1.0;
               else {
                  if (gd_408 >= MathPow(MathAbs(gd_416 / gd_352), gd_392)) gd_164 = MathPow(MathAbs(gd_416 / gd_352), gd_392);
                  else gd_164 = gd_408;
                  gd_156 = gd_164;
               }
               gd_344 = gd_156;
               gd_368 = MathPow(gd_400, MathSqrt(gd_344));
               if (gd_296 > 0.0) gd_280 = gd_264;
               else gd_280 = gd_264 - gd_296 * gd_368;
               if (gd_328 < 0.0) gd_312 = gd_264;
               else gd_312 = gd_264 - gd_328 * gd_368;
            }
         }
         if (gi_492 > 30) {
            gd_304 = MathPow(gd_336, gd_344);
            gd_448 = (1 - gd_304) * ld_0 + gd_304 * gd_448;
            gd_456 = (ld_0 - gd_448) * (1 - gd_336) + gd_336 * gd_456;
            gd_464 = gd_272 * gd_456 + gd_448;
            gd_288 = -2.0 * gd_304;
            gd_320 = gd_304 * gd_304;
            gd_432 = gd_288 + gd_320 + 1.0;
            gd_424 = (gd_464 - gd_440) * gd_432 + gd_320 * gd_424;
            gd_440 += gd_424;
         }
      }
      gd_132 = gd_440;
      g_ibuf_76[gi_128] = gd_132;
   }
}

void loadJMA(int ai_0) {
   double ld_4;
   gi_224 = 63;
   gi_228 = 64;
   if (gi_112 == TRUE) {
      for (gi_212 = 1; gi_212 < gi_224 + 1; gi_212++) gda_496[gi_212] = -1000000;
      for (gi_212 = gi_228; gi_212 < 128; gi_212++) gda_496[gi_212] = 1000000;
      gi_112 = FALSE;
   }
   gi_472 = TRUE;
   if (ai_0 <= 1) gd_384 = 0.0000000001;
   else gd_384 = (ai_0 - 1) / 2;
   gd_272 = 2.5;
   gd_148 = MathLog(MathSqrt(gd_384));
   gd_156 = gd_148;
   if (gd_148 / MathLog(2.0) + 2.0 < 0.0) gd_164 = 0;
   else gd_164 = gd_156 / MathLog(2.0) + 2.0;
   gd_408 = gd_164;
   if (gd_408 - 2.0 >= 0.5) gd_392 = gd_408 - 2.0;
   else gd_392 = 0.5;
   gd_376 = MathSqrt(gd_384) * gd_408;
   gd_400 = gd_376 / (gd_376 + 1.0);
   gd_384 = 0.9 * gd_384;
   gd_336 = gd_384 / (gd_384 + 2.0);
   gi_472 = TRUE;
   if (bars == 0) bars = Bars;
   for (gi_128 = bars + 1000; gi_128 >= 0; gi_128--) {
      switch (gi_124) {
      case 0:
         ld_4 = Close[gi_128];
         break;
      case 1:
         ld_4 = Open[gi_128];
         break;
      case 2:
         ld_4 = (Open[gi_128] + High[gi_128] + Low[gi_128] + Close[gi_128]) / 4.0;
         break;
      case 3:
         ld_4 = High[gi_128];
         break;
      case 4:
         ld_4 = Low[gi_128];
         break;
      default:
         ld_4 = Close[gi_128];
         break;
      }
      if (gi_488 < 61) {
         gi_488++;
         gda_508[gi_488] = ld_4;
      }
      if (gi_488 > 30) {
         if (gi_472 != FALSE) {
            gi_472 = FALSE;
            gi_216 = 0;
            for (gi_212 = 1; gi_212 < 30; gi_212++)
               if (gda_508[gi_212 + 1] != gda_508[gi_212]) gi_216 = 1;
            gi_476 = 30 * gi_216;
            if (gi_476 == 0) gd_312 = ld_4;
            else gd_312 = gda_508[1];
            gd_280 = gd_312;
            if (gi_476 > 29) gi_476 = 29;
         } else gi_476 = 0;
         for (gi_212 = gi_476; gi_212 >= 0; gi_212--) {
            if (gi_212 == 0) gd_264 = ld_4;
            else gd_264 = gda_508[31 - gi_212];
            gd_296 = gd_264 - gd_280;
            gd_328 = gd_264 - gd_312;
            if (MathAbs(gd_296) > MathAbs(gd_328)) gd_156 = MathAbs(gd_296);
            else gd_156 = MathAbs(gd_328);
            gd_416 = gd_156;
            gd_140 = gd_416 + 0.0000000001;
            if (gi_240 <= 1) gi_240 = 127;
            else gi_240--;
            if (gi_244 <= 1) gi_244 = 10;
            else gi_244--;
            if (gi_260 < 128) gi_260++;
            gd_180 = gd_180 + gd_140 - gda_504[gi_244];
            gda_504[gi_244] = gd_140;
            if (gi_260 > 10) gd_204 = gd_180 / 10.0;
            else gd_204 = gd_180 / gi_260;
            if (gi_260 == 30) g_index_520 = 0;
            if (gi_260 > 127) {
               gd_188 = gda_500[gi_240];
               gda_500[gi_240] = gd_204;
               gi_256 = 64;
               gi_248 = gi_256;
               gi_unused_516 = gi_248;
               while (gi_256 > 1) {
                  if (gda_496[gi_248] < gd_188) {
                     gi_256 /= 2;
                     gi_248 += gi_256;
                     gi_unused_516 = gi_248;
                  } else {
                     if (gda_496[gi_248] <= gd_188) gi_256 = 1;
                     else {
                        gi_256 /= 2;
                        gi_248 -= gi_256;
                        gi_unused_516 = gi_248;
                     }
                  }
               }
            } else {
               gda_500[gi_240] = gd_204;
               if (gi_224 + gi_228 > 127) {
                  gi_228--;
                  gi_248 = gi_228;
                  gi_unused_516 = gi_248;
               } else {
                  gi_224++;
                  gi_248 = gi_224;
                  gi_unused_516 = gi_248;
               }
               if (gi_224 > 96) gi_232 = 96;
               else gi_232 = gi_224;
               if (gi_228 < 32) gi_236 = 32;
               else gi_236 = gi_228;
            }
            gi_256 = 64;
            gi_252 = gi_256;
            while (gi_256 > 1) {
               if (gda_496[gi_252] >= gd_204) {
                  if (gda_496[gi_252 - 1] <= gd_204) gi_256 = 1;
                  else {
                     gi_256 /= 2;
                     gi_252 -= gi_256;
                  }
               } else {
                  gi_256 /= 2;
                  gi_252 += gi_256;
               }
               if (gi_252 == 127 && gd_204 > gda_496[127]) gi_252 = 128;
            }
            if (gi_260 > 127) {
               if (gi_248 >= gi_252) {
                  if (gi_232 + 1 > gi_252 && gi_236 - 1 < gi_252) gd_196 += gd_204;
                  else
                     if (gi_236 > gi_252 && gi_236 - 1 < gi_248) gd_196 += gda_496[gi_236 - 1];
               } else {
                  if (gi_236 >= gi_252) {
                     if (gi_232 + 1 < gi_252 && gi_232 + 1 > gi_248) gd_196 += gda_496[gi_232 + 1];
                  } else {
                     if (gi_232 + 2 > gi_252) gd_196 += gd_204;
                     else
                        if (gi_232 + 1 < gi_252 && gi_232 + 1 > gi_248) gd_196 += gda_496[gi_232 + 1];
                  }
               }
               if (gi_248 > gi_252) {
                  if (gi_236 - 1 < gi_248 && gi_232 + 1 > gi_248) gd_196 -= gda_496[gi_248];
                  else
                     if (gi_232 < gi_248 && gi_232 + 1 > gi_252) gd_196 -= gda_496[gi_232];
               } else {
                  if (gi_232 + 1 > gi_248 && gi_236 - 1 < gi_248) gd_196 -= gda_496[gi_248];
                  else
                     if (gi_236 > gi_248 && gi_236 < gi_252) gd_196 -= gda_496[gi_236];
               }
            }
            if (gi_248 <= gi_252) {
               if (gi_248 >= gi_252) gda_496[gi_252] = gd_204;
               else {
                  for (g_index_520 = gi_248 + 1; g_index_520 < gi_252; g_index_520++) gda_496[g_index_520 - 1] = gda_496[g_index_520];
                  gda_496[gi_252 - 1] = gd_204;
               }
            } else {
               for (gi_524 = gi_248 - 1; gi_524 >= gi_252; gi_524--) gda_496[gi_524 + 1] = gda_496[gi_524];
               gda_496[gi_252] = gd_204;
            }
            if (gi_260 <= 127) {
               gd_196 = 0;
               for (gi_532 = gi_236; gi_532 < gi_232 + 1; gi_532++) gd_196 += gda_496[gi_532];
            }
            gd_352 = gd_196 / (gi_232 - gi_236 + 1);
            if (gi_492 + 1 > 31) gi_492 = 31;
            else gi_492++;
            if (gi_492 <= 30) {
               if (gd_296 > 0.0) gd_280 = gd_264;
               else gd_280 = gd_264 - gd_296 * gd_400;
               if (gd_328 < 0.0) gd_312 = gd_264;
               else gd_312 = gd_264 - gd_328 * gd_400;
               gd_440 = ld_4;
               if (gi_492 != 30) continue;
               gd_448 = ld_4;
               if (MathCeil(gd_376) >= 1.0) gd_172 = MathCeil(gd_376);
               else gd_172 = 1;
               gi_484 = gd_172;
               if (MathFloor(gd_376) >= 1.0) gd_156 = MathFloor(gd_376);
               else gd_156 = 1;
               gi_480 = gd_156;
               if (gi_484 == gi_480) gd_360 = 1;
               else {
                  gd_172 = gi_484 - gi_480;
                  gd_360 = (gd_376 - gi_480) / gd_172;
               }
               if (gi_480 <= 29) gi_216 = gi_480;
               else gi_216 = 29;
               if (gi_484 <= 29) gi_220 = gi_484;
               else gi_220 = 29;
               gd_424 = (ld_4 - (gda_508[gi_488 - gi_216])) * (1 - gd_360) / gi_480 + (ld_4 - (gda_508[gi_488 - gi_220])) * gd_360 / gi_484;
            } else {
               if (gd_408 >= MathPow(MathAbs(gd_416 / gd_352), gd_392)) gd_148 = MathPow(MathAbs(gd_416 / gd_352), gd_392);
               else gd_148 = gd_408;
               if (gd_148 < 1.0) gd_156 = 1.0;
               else {
                  if (gd_408 >= MathPow(MathAbs(gd_416 / gd_352), gd_392)) gd_164 = MathPow(MathAbs(gd_416 / gd_352), gd_392);
                  else gd_164 = gd_408;
                  gd_156 = gd_164;
               }
               gd_344 = gd_156;
               gd_368 = MathPow(gd_400, MathSqrt(gd_344));
               if (gd_296 > 0.0) gd_280 = gd_264;
               else gd_280 = gd_264 - gd_296 * gd_368;
               if (gd_328 < 0.0) gd_312 = gd_264;
               else gd_312 = gd_264 - gd_328 * gd_368;
            }
         }
         if (gi_492 > 30) {
            gd_304 = MathPow(gd_336, gd_344);
            gd_448 = (1 - gd_304) * ld_4 + gd_304 * gd_448;
            gd_456 = (ld_4 - gd_448) * (1 - gd_336) + gd_336 * gd_456;
            gd_464 = gd_272 * gd_456 + gd_448;
            gd_288 = -2.0 * gd_304;
            gd_320 = gd_304 * gd_304;
            gd_432 = gd_288 + gd_320 + 1.0;
            gd_424 = (gd_464 - gd_440) * gd_432 + gd_320 * gd_424;
            gd_440 += gd_424;
         }
      }
      gd_132 = gd_440;
      g_ibuf_76[gi_128] = gd_132;
   }
}

void lenars(double ada_0[15000], int ai_4) {
   double ld_8;
   gi_224 = 63;
   gi_228 = 64;
   if (gi_112 == TRUE) {
      for (gi_212 = 1; gi_212 < gi_224 + 1; gi_212++) gda_496[gi_212] = -1000000;
      for (gi_212 = gi_228; gi_212 < 128; gi_212++) gda_496[gi_212] = 1000000;
      gi_112 = FALSE;
   }
   gi_472 = TRUE;
   if (Smooth <= 1.0) gd_384 = 0.0000000001;
   else gd_384 = (Smooth - 1.0) / 2.0;
   if (gd_116 < -100.0) gd_272 = 0.5;
   else {
      if (gd_116 > 100.0) gd_272 = 2.5;
      else gd_272 = gd_116 / 100.0 + 1.5;
   }
   gd_148 = MathLog(MathSqrt(gd_384));
   gd_156 = gd_148;
   if (gd_148 / MathLog(2.0) + 2.0 < 0.0) gd_164 = 0;
   else gd_164 = gd_156 / MathLog(2.0) + 2.0;
   gd_408 = gd_164;
   if (gd_408 - 2.0 >= 0.5) gd_392 = gd_408 - 2.0;
   else gd_392 = 0.5;
   gd_376 = MathSqrt(gd_384) * gd_408;
   gd_400 = gd_376 / (gd_376 + 1.0);
   gd_384 = 0.9 * gd_384;
   gd_336 = gd_384 / (gd_384 + 2.0);
   gi_472 = TRUE;
   if (bars == 0) bars = Bars;
   for (gi_128 = bars + 30; gi_128 >= 0; gi_128--) {
      ld_8 = ada_0[gi_128];
      if (gi_488 < 61) {
         gi_488++;
         gda_508[gi_488] = ld_8;
      }
      if (gi_488 > 30) {
         if (gi_472 != FALSE) {
            gi_472 = FALSE;
            gi_216 = 0;
            for (gi_212 = 1; gi_212 < 30; gi_212++)
               if (gda_508[gi_212 + 1] != gda_508[gi_212]) gi_216 = 1;
            gi_476 = 30 * gi_216;
            if (gi_476 == 0) gd_312 = ld_8;
            else gd_312 = gda_508[1];
            gd_280 = gd_312;
            if (gi_476 > 29) gi_476 = 29;
         } else gi_476 = 0;
         for (gi_212 = gi_476; gi_212 >= 0; gi_212--) {
            if (gi_212 == 0) gd_264 = ld_8;
            else gd_264 = gda_508[31 - gi_212];
            gd_296 = gd_264 - gd_280;
            gd_328 = gd_264 - gd_312;
            if (MathAbs(gd_296) > MathAbs(gd_328)) gd_156 = MathAbs(gd_296);
            else gd_156 = MathAbs(gd_328);
            gd_416 = gd_156;
            gd_140 = gd_416 + 0.0000000001;
            if (gi_240 <= 1) gi_240 = 127;
            else gi_240--;
            if (gi_244 <= 1) gi_244 = 10;
            else gi_244--;
            if (gi_260 < 128) gi_260++;
            gd_180 = gd_180 + gd_140 - gda_504[gi_244];
            gda_504[gi_244] = gd_140;
            if (gi_260 > 10) gd_204 = gd_180 / 10.0;
            else gd_204 = gd_180 / gi_260;
            if (gi_260 == 30) g_index_520 = 0;
            if (gi_260 > 127) {
               gd_188 = gda_500[gi_240];
               gda_500[gi_240] = gd_204;
               gi_256 = 64;
               gi_248 = gi_256;
               gi_unused_516 = gi_248;
               while (gi_256 > 1) {
                  if (gda_496[gi_248] < gd_188) {
                     gi_256 /= 2;
                     gi_248 += gi_256;
                     gi_unused_516 = gi_248;
                  } else {
                     if (gda_496[gi_248] <= gd_188) gi_256 = 1;
                     else {
                        gi_256 /= 2;
                        gi_248 -= gi_256;
                        gi_unused_516 = gi_248;
                     }
                  }
               }
            } else {
               gda_500[gi_240] = gd_204;
               if (gi_224 + gi_228 > 127) {
                  gi_228--;
                  gi_248 = gi_228;
                  gi_unused_516 = gi_248;
               } else {
                  gi_224++;
                  gi_248 = gi_224;
                  gi_unused_516 = gi_248;
               }
               if (gi_224 > 96) gi_232 = 96;
               else gi_232 = gi_224;
               if (gi_228 < 32) gi_236 = 32;
               else gi_236 = gi_228;
            }
            gi_256 = 64;
            gi_252 = gi_256;
            while (gi_256 > 1) {
               if (gda_496[gi_252] >= gd_204) {
                  if (gda_496[gi_252 - 1] <= gd_204) gi_256 = 1;
                  else {
                     gi_256 /= 2;
                     gi_252 -= gi_256;
                  }
               } else {
                  gi_256 /= 2;
                  gi_252 += gi_256;
               }
               if (gi_252 == 127 && gd_204 > gda_496[127]) gi_252 = 128;
            }
            if (gi_260 > 127) {
               if (gi_248 >= gi_252) {
                  if (gi_232 + 1 > gi_252 && gi_236 - 1 < gi_252) gd_196 += gd_204;
                  else
                     if (gi_236 > gi_252 && gi_236 - 1 < gi_248) gd_196 += gda_496[gi_236 - 1];
               } else {
                  if (gi_236 >= gi_252) {
                     if (gi_232 + 1 < gi_252 && gi_232 + 1 > gi_248) gd_196 += gda_496[gi_232 + 1];
                  } else {
                     if (gi_232 + 2 > gi_252) gd_196 += gd_204;
                     else
                        if (gi_232 + 1 < gi_252 && gi_232 + 1 > gi_248) gd_196 += gda_496[gi_232 + 1];
                  }
               }
               if (gi_248 > gi_252) {
                  if (gi_236 - 1 < gi_248 && gi_232 + 1 > gi_248) gd_196 -= gda_496[gi_248];
                  else
                     if (gi_232 < gi_248 && gi_232 + 1 > gi_252) gd_196 -= gda_496[gi_232];
               } else {
                  if (gi_232 + 1 > gi_248 && gi_236 - 1 < gi_248) gd_196 -= gda_496[gi_248];
                  else
                     if (gi_236 > gi_248 && gi_236 < gi_252) gd_196 -= gda_496[gi_236];
               }
            }
            if (gi_248 <= gi_252) {
               if (gi_248 >= gi_252) gda_496[gi_252] = gd_204;
               else {
                  for (g_index_520 = gi_248 + 1; g_index_520 < gi_252; g_index_520++) gda_496[g_index_520 - 1] = gda_496[g_index_520];
                  gda_496[gi_252 - 1] = gd_204;
               }
            } else {
               for (gi_524 = gi_248 - 1; gi_524 >= gi_252; gi_524--) gda_496[gi_524 + 1] = gda_496[gi_524];
               gda_496[gi_252] = gd_204;
            }
            if (gi_260 <= 127) {
               gd_196 = 0;
               for (gi_532 = gi_236; gi_532 < gi_232 + 1; gi_532++) gd_196 += gda_496[gi_532];
            }
            gd_352 = gd_196 / (gi_232 - gi_236 + 1);
            if (gi_492 + 1 > 31) gi_492 = 31;
            else gi_492++;
            if (gi_492 <= 30) {
               if (gd_296 > 0.0) gd_280 = gd_264;
               else gd_280 = gd_264 - gd_296 * gd_400;
               if (gd_328 < 0.0) gd_312 = gd_264;
               else gd_312 = gd_264 - gd_328 * gd_400;
               gd_440 = ld_8;
               if (gi_492 != 30) continue;
               gd_448 = ld_8;
               if (MathCeil(gd_376) >= 1.0) gd_172 = MathCeil(gd_376);
               else gd_172 = 1;
               gi_484 = gd_172;
               if (MathFloor(gd_376) >= 1.0) gd_156 = MathFloor(gd_376);
               else gd_156 = 1;
               gi_480 = gd_156;
               if (gi_484 == gi_480) gd_360 = 1;
               else {
                  gd_172 = gi_484 - gi_480;
                  gd_360 = (gd_376 - gi_480) / gd_172;
               }
               if (gi_480 <= 29) gi_216 = gi_480;
               else gi_216 = 29;
               if (gi_484 <= 29) gi_220 = gi_484;
               else gi_220 = 29;
               gd_424 = (ld_8 - (gda_508[gi_488 - gi_216])) * (1 - gd_360) / gi_480 + (ld_8 - (gda_508[gi_488 - gi_220])) * gd_360 / gi_484;
            } else {
               if (gd_408 >= MathPow(MathAbs(gd_416 / gd_352), gd_392)) gd_148 = MathPow(MathAbs(gd_416 / gd_352), gd_392);
               else gd_148 = gd_408;
               if (gd_148 < 1.0) gd_156 = 1.0;
               else {
                  if (gd_408 >= MathPow(MathAbs(gd_416 / gd_352), gd_392)) gd_164 = MathPow(MathAbs(gd_416 / gd_352), gd_392);
                  else gd_164 = gd_408;
                  gd_156 = gd_164;
               }
               gd_344 = gd_156;
               gd_368 = MathPow(gd_400, MathSqrt(gd_344));
               if (gd_296 > 0.0) gd_280 = gd_264;
               else gd_280 = gd_264 - gd_296 * gd_368;
               if (gd_328 < 0.0) gd_312 = gd_264;
               else gd_312 = gd_264 - gd_328 * gd_368;
            }
         }
         if (gi_492 > 30) {
            gd_304 = MathPow(gd_336, gd_344);
            gd_448 = (1 - gd_304) * ld_8 + gd_304 * gd_448;
            gd_456 = (ld_8 - gd_448) * (1 - gd_336) + gd_336 * gd_456;
            gd_464 = gd_272 * gd_456 + gd_448;
            gd_288 = -2.0 * gd_304;
            gd_320 = gd_304 * gd_304;
            gd_432 = gd_288 + gd_320 + 1.0;
            gd_424 = (gd_464 - gd_440) * gd_432 + gd_320 * gd_424;
            gd_440 += gd_424;
         }
      }
      gd_132 = gd_440;
      if (ai_4 == 1) g_ibuf_76[gi_128] = gd_132;
      else g_ibuf_560[gi_128] = gd_132;
   }
}