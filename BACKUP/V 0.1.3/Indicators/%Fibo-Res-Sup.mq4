/*
   Generated by EX4-TO-MQ4 decompiler V4.0.224.1 []
   Website: http://purebeam.biz
   E-mail : purebeam@gmail.com
*/
#property copyright "Copyright � 2009, eBay ID - fx237  "
#property link      "eBay ID - fx237"

#property indicator_chart_window
#property indicator_buffers 1
#property indicator_color1 CLR_NONE

extern bool pivots = FALSE;
extern bool camarilla = TRUE;
extern bool midpivots = FALSE;
extern int MyPeriod = 1440;
double gd_92 = 0.0;
double HighPrice2 = 0.0;
double LowPrice2 = 0.0;
double HighPrice = 0.0;
double OpenPrice = 0.0;
double LowPrice = 0.0;
double ClosePrice = 0.0;
double OpenPrice2 = 0.0;
double gd_156 = 0.0;
double gd_164 = 0.0;
double gd_172 = 0.0;
double gd_180 = 0.0;
double gd_188 = 0.0;
double gd_196 = 0.0;
double gd_204 = 0.0;
double gd_212 = 0.0;
double gd_220 = 0.0;
double gd_228 = 0.0;
double gd_236 = 0.0;
double gd_244;
double gd_252;
double gd_260;
double gd_268;
double gd_276;
double gd_284;
double gd_292;
double gd_300;
double gd_308;
double gd_316;
double gd_324;
double gd_332;
double gd_340;
double gd_348;
double gd_356;
double gd_364;
double gd_372 = 0.0;
double gd_380 = 0.0;
double gd_388 = 0.0;
double gda_396[2][6];
double gda_400[];

int init() {
   IndicatorBuffers(4);
   SetIndexStyle(0, DRAW_ARROW);
   SetIndexArrow(0, 159);
   SetIndexBuffer(0, gda_400);
   gd_244 = 0;
   gd_252 = 0;
   gd_260 = 0;
   gd_268 = 0;
   gd_276 = 0;
   gd_284 = 0;
   gd_292 = 0;
   gd_300 = 0;
   gd_308 = 0;
   gd_316 = 0;
   gd_324 = 0;
   gd_332 = 0;
   gd_340 = 0;
   gd_348 = 0;
   gd_356 = 0;
   gd_364 = 0;
   gd_172 = 0;
   gd_180 = 0;
   gd_188 = 0;
   gd_196 = 0;
   gd_204 = 0;
   gd_212 = 0;
   gd_220 = 0;
   return (0);
}

int deinit() {
   ObjectDelete("r1 Label");
   ObjectDelete("r1 Line");
   ObjectDelete("r2 Label");
   ObjectDelete("r2 Line");
   ObjectDelete("r3 Label");
   ObjectDelete("r3 Line");
   ObjectDelete("r1 Label");
   ObjectDelete("r1 Line");
   ObjectDelete("r2 Label");
   ObjectDelete("r2 Line");
   ObjectDelete("r3 Label");
   ObjectDelete("r3 Line");
   ObjectDelete("R1 Label");
   ObjectDelete("R1 Line");
   ObjectDelete("R2 Label");
   ObjectDelete("R2 Line");
   ObjectDelete("R3 Label");
   ObjectDelete("R3 Line");
   ObjectDelete("S1 Label");
   ObjectDelete("S1 Line");
   ObjectDelete("S2 Label");
   ObjectDelete("S2 Line");
   ObjectDelete("S3 Label");
   ObjectDelete("S3 Line");
   ObjectDelete("P Label");
   ObjectDelete("P Line");
   ObjectDelete("H4 Label");
   ObjectDelete("H4 Line");
   ObjectDelete("H3 Label");
   ObjectDelete("H3 Line");
   ObjectDelete("L3 Label");
   ObjectDelete("L3 Line");
   ObjectDelete("L4 Label");
   ObjectDelete("L4 Line");
   ObjectDelete("M5 Label");
   ObjectDelete("M5 Line");
   ObjectDelete("M4 Label");
   ObjectDelete("M4 Line");
   ObjectDelete("M3 Label");
   ObjectDelete("M3 Line");
   ObjectDelete("M2 Label");
   ObjectDelete("M2 Line");
   ObjectDelete("M1 Label");
   ObjectDelete("M1 Line");
   ObjectDelete("M0 Label");
   ObjectDelete("M0 Line");
   return (0);
}

int start() {
   if (Period() > PERIOD_D1) {
      Print("Error - Chart period is greater than 1 day.");
      return (-1);
   }
   ArrayCopyRates(gda_396, Symbol(), MyPeriod);
   ClosePrice = iClose(NULL,MyPeriod,1);
   OpenPrice = iOpen(NULL,MyPeriod,1);
   OpenPrice2 = gda_396[0][1];
   HighPrice = iHigh(NULL,MyPeriod,1);
   LowPrice = iLow(NULL,MyPeriod,1);
   HighPrice2 = iHigh(NULL,MyPeriod,0);
   LowPrice2 = iLow(NULL,MyPeriod,0);
   gd_92 = HighPrice - LowPrice;
   gd_188 = (HighPrice + LowPrice + ClosePrice) / 3.0;
   gd_180 = gd_188 + 0.38 * gd_92;
   gd_172 = gd_188 + 0.62 * gd_92;
   gd_220 = gd_188 + 0.99 * gd_92;
   gd_196 = gd_188 - 0.38 * gd_92;
   gd_204 = gd_188 - 0.62 * gd_92;
   gd_212 = gd_188 - 0.99 * gd_92;
   gd_388 = HighPrice2 - LowPrice2;
   gd_236 = HighPrice - LowPrice;
   gd_228 = (HighPrice + LowPrice + ClosePrice) / 3.0;
   gd_244 = 2.0 * gd_228 - LowPrice;
   gd_316 = 2.0 * gd_228 - HighPrice;
   gd_252 = gd_228 + (HighPrice - LowPrice);
   gd_324 = gd_228 - (HighPrice - LowPrice);
   gd_260 = 2.0 * gd_228 + (HighPrice - 2.0 * LowPrice);
   gd_308 = (gd_252 + gd_260) / 2.0;
   gd_300 = (gd_244 + gd_252) / 2.0;
   gd_292 = (gd_228 + gd_244) / 2.0;
   gd_284 = (gd_228 + gd_316) / 2.0;
   gd_276 = (gd_316 + gd_324) / 2.0;
   gd_332 = 2.0 * gd_228 - (2.0 * HighPrice - LowPrice);
   gd_268 = (gd_324 + gd_332) / 2.0;
   if (gd_236 > 5.0) gd_372 = gd_236;
   else gd_372 = 10000.0 * gd_236;
   if (gd_388 > 5.0) gd_380 = gd_388;
   else gd_380 = 10000.0 * gd_388;
   Comment("High= ", HighPrice, " Previous DaysRange= ", gd_372, 
      "\nLow= ", LowPrice, " Current DaysRange= ", gd_380, 
      "\nClose= ", ClosePrice, 
      "\n       R3.0=", gd_220, 
      "\n    R2.0=", gd_172, 
      "\n  R1.0=", gd_180, 
      "\nPivot=", gd_188, 
      "\n  S1.0=", gd_196, 
      "\n    S2.0=", gd_204, 
   "\n      S3.0=", gd_212);
   if (pivots == TRUE) {
      if (ObjectFind("R1 label") != 0) {
         ObjectCreate("R1 label", OBJ_TEXT, 0, Time[0], gd_244);
         ObjectSetText("R1 label", " R1", 8, "Arial", CLR_NONE);
      } else ObjectMove("R1 label", 0, Time[0], gd_244);
      if (ObjectFind("R2 label") != 0) {
         ObjectCreate("R2 label", OBJ_TEXT, 0, Time[20], gd_252);
         ObjectSetText("R2 label", " R2", 8, "Arial", CLR_NONE);
      } else ObjectMove("R2 label", 0, Time[20], gd_252);
      if (ObjectFind("R3 label") != 0) {
         ObjectCreate("R3 label", OBJ_TEXT, 0, Time[20], gd_260);
         ObjectSetText("R3 label", " R3", 8, "Arial", CLR_NONE);
      } else ObjectMove("R3 label", 0, Time[20], gd_260);
      if (ObjectFind("P label") != 0) {
         ObjectCreate("P label", OBJ_TEXT, 0, Time[0], gd_228);
         ObjectSetText("P label", "Pivot " + DoubleToStr(gd_228, 4), 8, "Arial", CLR_NONE);
      } else ObjectMove("P label", 0, Time[0], gd_228);
      if (ObjectFind("S1 label") != 0) {
         ObjectCreate("S1 label", OBJ_TEXT, 0, Time[0], gd_316);
         ObjectSetText("S1 label", "S1", 8, "Arial", CLR_NONE);
      } else ObjectMove("S1 label", 0, Time[0], gd_316);
      if (ObjectFind("S2 label") != 0) {
         ObjectCreate("S2 label", OBJ_TEXT, 0, Time[20], gd_324);
         ObjectSetText("S2 label", "S2", 8, "Arial", CLR_NONE);
      } else ObjectMove("S2 label", 0, Time[20], gd_324);
      if (ObjectFind("S3 label") != 0) {
         ObjectCreate("S3 label", OBJ_TEXT, 0, Time[20], gd_332);
         ObjectSetText("S3 label", "S3", 8, "Arial", CLR_NONE);
      } else ObjectMove("S3 label", 0, Time[20], gd_332);
      if (ObjectFind("S1 line") != 0) {
         ObjectCreate("S1 line", OBJ_HLINE, 0, Time[40], gd_316);
         ObjectSet("S1 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("S1 line", OBJPROP_COLOR, MidnightBlue);
      } else ObjectMove("S1 line", 0, Time[40], gd_316);
      if (ObjectFind("S2 line") != 0) {
         ObjectCreate("S2 line", OBJ_HLINE, 0, Time[40], gd_324);
         ObjectSet("S2 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("S2 line", OBJPROP_COLOR, MidnightBlue);
      } else ObjectMove("S2 line", 0, Time[40], gd_324);
      if (ObjectFind("S3 line") != 0) {
         ObjectCreate("S3 line", OBJ_HLINE, 0, Time[40], gd_332);
         ObjectSet("S3 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("S3 line", OBJPROP_COLOR, MidnightBlue);
      } else ObjectMove("S3 line", 0, Time[40], gd_332);
      if (ObjectFind("P line") != 0) {
         ObjectCreate("P line", OBJ_HLINE, 0, Time[40], gd_228);
         ObjectSet("P line", OBJPROP_STYLE, STYLE_DOT);
         ObjectSet("P line", OBJPROP_COLOR, YellowGreen);
      } else ObjectMove("P line", 0, Time[40], gd_228);
      if (ObjectFind("R1 line") != 0) {
         ObjectCreate("R1 line", OBJ_HLINE, 0, Time[40], gd_244);
         ObjectSet("R1 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("R1 line", OBJPROP_COLOR, FireBrick);
      } else ObjectMove("R1 line", 0, Time[40], gd_244);
      if (ObjectFind("R2 line") != 0) {
         ObjectCreate("R2 line", OBJ_HLINE, 0, Time[40], gd_252);
         ObjectSet("R2 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("R2 line", OBJPROP_COLOR, FireBrick);
      } else ObjectMove("R2 line", 0, Time[40], gd_252);
      if (ObjectFind("R3 line") != 0) {
         ObjectCreate("R3 line", OBJ_HLINE, 0, Time[40], gd_260);
         ObjectSet("R3 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("R3 line", OBJPROP_COLOR, FireBrick);
      } else ObjectMove("R3 line", 0, Time[40], gd_260);
   }
   if (camarilla == TRUE) {
      if (ObjectFind("H4 label") != 0) {
         ObjectCreate("H4 label", OBJ_TEXT, 0, Time[20], gd_340);
         ObjectSetText("H4 label", " H4", 8, "Arial", CLR_NONE);
      } else ObjectMove("H4 label", 0, Time[20], gd_340);
      if (ObjectFind("H3 label") != 0) {
         ObjectCreate("H3 label", OBJ_TEXT, 0, Time[20], gd_348);
         ObjectSetText("H3 label", " H3", 8, "Arial", CLR_NONE);
      } else ObjectMove("H3 label", 0, Time[20], gd_348);
      if (ObjectFind("R1 label") != 0) {
         ObjectCreate("R1 label", OBJ_TEXT, 0, Time[20], gd_180);
         ObjectSetText("R1 label", "Fib R1", 8, "Arial", White);
      } else ObjectMove("R1 label", 0, Time[20], gd_180);
      if (ObjectFind("R2 label") != 0) {
         ObjectCreate("R2 label", OBJ_TEXT, 0, Time[20], gd_172);
         ObjectSetText("R2 label", "Fib R2", 8, "Arial", White);
      } else ObjectMove("R2 label", 0, Time[20], gd_172);
      if (ObjectFind("R3 label") != 0) {
         ObjectCreate("R3 label", OBJ_TEXT, 0, Time[20], gd_220);
         ObjectSetText("R3 label", "Fib R3", 8, "Arial", White);
      } else ObjectMove("R3 label", 0, Time[20], gd_220);
      if (ObjectFind("P label") != 0) {
         ObjectCreate("P label", OBJ_TEXT, 0, Time[20], gd_188);
         ObjectSetText("P label", "Pivot", 8, "Arial", White);
      } else ObjectMove("P label", 0, Time[20], gd_188);
      if (ObjectFind("S1 label") != 0) {
         ObjectCreate("S1 label", OBJ_TEXT, 0, Time[20], gd_196);
         ObjectSetText("S1 label", "Fib S1", 8, "Arial", White);
      } else ObjectMove("S1 label", 0, Time[20], gd_196);
      if (ObjectFind("S2 label") != 0) {
         ObjectCreate("S2 label", OBJ_TEXT, 0, Time[20], gd_204);
         ObjectSetText("S2 label", "Fib S2", 8, "Arial", White);
      } else ObjectMove("S2 label", 0, Time[20], gd_204);
      if (ObjectFind("S3 label") != 0) {
         ObjectCreate("S3 label", OBJ_TEXT, 0, Time[20], gd_212);
         ObjectSetText("S3 label", "Fib S3", 8, "Arial", White);
      } else ObjectMove("S3 label", 0, Time[20], gd_212);
      if (ObjectFind("S1 line") != 0) {
         ObjectCreate("S1 line", OBJ_HLINE, 0, Time[40], gd_196);
         ObjectSet("S1 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("S1 line", OBJPROP_COLOR, Aqua);
      } else ObjectMove("S1 line", 0, Time[40], gd_196);
      if (ObjectFind("S2 line") != 0) {
         ObjectCreate("S2 line", OBJ_HLINE, 0, Time[40], gd_204);
         ObjectSet("S2 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("S2 line", OBJPROP_COLOR, DodgerBlue);
      } else ObjectMove("S2 line", 0, Time[40], gd_204);
      if (ObjectFind("S3 line") != 0) {
         ObjectCreate("S3 line", OBJ_HLINE, 0, Time[40], gd_212);
         ObjectSet("S3 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("S3 line", OBJPROP_COLOR, Blue);
      } else ObjectMove("S3 line", 0, Time[40], gd_212);
      if (ObjectFind("P line") != 0) {
         ObjectCreate("P line", OBJ_HLINE, 0, Time[40], gd_188);
         ObjectSet("P line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("P line", OBJPROP_COLOR, YellowGreen);
      } else ObjectMove("P line", 0, Time[40], gd_188);
      if (ObjectFind("R1 line") != 0) {
         ObjectCreate("R1 line", OBJ_HLINE, 0, Time[40], gd_180);
         ObjectSet("R1 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("R1 line", OBJPROP_COLOR, Aqua);
      } else ObjectMove("R1 line", 0, Time[40], gd_180);
      if (ObjectFind("R2 line") != 0) {
         ObjectCreate("R2 line", OBJ_HLINE, 0, Time[40], gd_172);
         ObjectSet("R2 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("R2 line", OBJPROP_COLOR, DodgerBlue);
      } else ObjectMove("R2 line", 0, Time[40], gd_172);
      if (ObjectFind("R3 line") != 0) {
         ObjectCreate("R3 line", OBJ_HLINE, 0, Time[40], gd_220);
         ObjectSet("R3 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("R3 line", OBJPROP_COLOR, Blue);
      } else ObjectMove("R3 line", 0, Time[40], gd_220);
      if (ObjectFind("L3 label") != 0) {
         ObjectCreate("L3 label", OBJ_TEXT, 0, Time[20], gd_364);
         ObjectSetText("L3 label", " L3", 8, "Arial", CLR_NONE);
      } else ObjectMove("L3 label", 0, Time[20], gd_364);
      if (ObjectFind("L4 label") != 0) {
         ObjectCreate("L4 label", OBJ_TEXT, 0, Time[20], gd_356);
         ObjectSetText("L4 label", " L4", 8, "Arial", CLR_NONE);
      } else ObjectMove("L4 label", 0, Time[20], gd_356);
      if (ObjectFind("H4 line") != 0) {
         ObjectCreate("H4 line", OBJ_HLINE, 0, Time[40], gd_340);
         ObjectSet("H4 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("H4 line", OBJPROP_COLOR, MediumBlue);
      } else ObjectMove("H4 line", 0, Time[40], gd_340);
      if (ObjectFind("H3 line") != 0) {
         ObjectCreate("H3 line", OBJ_HLINE, 0, Time[40], gd_348);
         ObjectSet("H3 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("H3 line", OBJPROP_COLOR, MediumBlue);
      } else ObjectMove("H3 line", 0, Time[40], gd_348);
      if (ObjectFind("L3 line") != 0) {
         ObjectCreate("L3 line", OBJ_HLINE, 0, Time[40], gd_364);
         ObjectSet("L3 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("L3 line", OBJPROP_COLOR, MediumBlue);
      } else ObjectMove("L3 line", 0, Time[40], gd_364);
      if (ObjectFind("L4 line") != 0) {
         ObjectCreate("L4 line", OBJ_HLINE, 0, Time[40], gd_356);
         ObjectSet("L4 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("L4 line", OBJPROP_COLOR, MediumBlue);
      } else ObjectMove("L4 line", 0, Time[40], gd_356);
   }
   if (midpivots == TRUE) {
      if (ObjectFind("M5 label") != 0) {
         ObjectCreate("M5 label", OBJ_TEXT, 0, Time[20], gd_308);
         ObjectSetText("M5 label", " M5", 8, "Arial", CLR_NONE);
      } else ObjectMove("M5 label", 0, Time[20], gd_308);
      if (ObjectFind("M4 label") != 0) {
         ObjectCreate("M4 label", OBJ_TEXT, 0, Time[20], gd_300);
         ObjectSetText("M4 label", " M4", 8, "Arial", CLR_NONE);
      } else ObjectMove("M4 label", 0, Time[20], gd_300);
      if (ObjectFind("M3 label") != 0) {
         ObjectCreate("M3 label", OBJ_TEXT, 0, Time[20], gd_292);
         ObjectSetText("M3 label", " M3", 8, "Arial", CLR_NONE);
      } else ObjectMove("M3 label", 0, Time[20], gd_292);
      if (ObjectFind("M2 label") != 0) {
         ObjectCreate("M2 label", OBJ_TEXT, 0, Time[20], gd_284);
         ObjectSetText("M2 label", " M2", 8, "Arial", CLR_NONE);
      } else ObjectMove("M2 label", 0, Time[20], gd_284);
      if (ObjectFind("M1 label") != 0) {
         ObjectCreate("M1 label", OBJ_TEXT, 0, Time[20], gd_276);
         ObjectSetText("M1 label", " M1", 8, "Arial", CLR_NONE);
      } else ObjectMove("M1 label", 0, Time[20], gd_276);
      if (ObjectFind("M0 label") != 0) {
         ObjectCreate("M0 label", OBJ_TEXT, 0, Time[20], gd_268);
         ObjectSetText("M0 label", " M0", 8, "Arial", CLR_NONE);
      } else ObjectMove("M0 label", 0, Time[20], gd_268);
      if (ObjectFind("M5 line") != 0) {
         ObjectCreate("M5 line", OBJ_HLINE, 0, Time[40], gd_308);
         ObjectSet("M5 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("M5 line", OBJPROP_COLOR, DimGray);
      } else ObjectMove("M5 line", 0, Time[40], gd_308);
      if (ObjectFind("M4 line") != 0) {
         ObjectCreate("M4 line", OBJ_HLINE, 0, Time[40], gd_300);
         ObjectSet("M4 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("M4 line", OBJPROP_COLOR, DimGray);
      } else ObjectMove("M4 line", 0, Time[40], gd_300);
      if (ObjectFind("M3 line") != 0) {
         ObjectCreate("M3 line", OBJ_HLINE, 0, Time[40], gd_292);
         ObjectSet("M3 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("M3 line", OBJPROP_COLOR, DimGray);
      } else ObjectMove("M3 line", 0, Time[40], gd_292);
      if (ObjectFind("M2 line") != 0) {
         ObjectCreate("M2 line", OBJ_HLINE, 0, Time[40], gd_284);
         ObjectSet("M2 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("M2 line", OBJPROP_COLOR, DimGray);
      } else ObjectMove("M2 line", 0, Time[40], gd_284);
      if (ObjectFind("M1 line") != 0) {
         ObjectCreate("M1 line", OBJ_HLINE, 0, Time[40], gd_276);
         ObjectSet("M1 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("M1 line", OBJPROP_COLOR, DimGray);
      } else ObjectMove("M1 line", 0, Time[40], gd_276);
      if (ObjectFind("M0 line") != 0) {
         ObjectCreate("M0 line", OBJ_HLINE, 0, Time[40], gd_268);
         ObjectSet("M0 line", OBJPROP_STYLE, STYLE_DASHDOTDOT);
         ObjectSet("M0 line", OBJPROP_COLOR, DimGray);
      } else ObjectMove("M0 line", 0, Time[40], gd_268);
   }
   return (0);
}