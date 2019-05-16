//+--------------------------------------------------------------------------------------------+
//|   http://www.forexfactory.com/showthread.php?p=9507287#post9507287                         | 
//|                                                                                            |
//+--------------------------------------------------------------------------------------------+ 
//
#property indicator_chart_window
// #property strict
//
extern string _FixedDate = "";
extern int IndiPeriod = 200;
extern int RegressionDegree = 4;
extern double K_N_L_Dev  = 1.27; 
extern double K_N_L_Dev2 = 1.618; 
extern double K_N_L_Dev3 = 2.618; 
extern color StdChannel_Clr = clrGreen;
extern color Regression_Clr1 = C'40,40,40';
extern color Regression_Clr2 = C'0xA0,0x00,0x00';
extern color Regression_Clr3 = C'0xA0,0x00,0x00';
extern color Fill_Clr1 = C'0x00,0x00,0x30';
extern color Fill_Clr2 = C'0x30,0x00,0x00';
extern bool Center_Line = TRUE;
extern bool Future_CenterLine = TRUE;
extern bool UseFixed_Date = FALSE;
double Gd_152;
double Gd_160;
double Gda_168[10][10];
double Gda_172[10];
double Gda_176[10];
double Gda_180[20];
double Gd_184;
double Gd_192;
double Gd_200;
double Gd_208;
double Gd_216;
int Gi_224;
int Gi_228;
int Gi_232;
int Gi_236;
int Gi_240;
int Gi_244;
int Gi_248;
int Gi_252;
int Gi_256;
int Gi_unused_260;
int G_datetime_264;
int G_datetime_268;
string Gs_276;

// E37F0136AA3FFAF149B351F6A4C948E9
int init() {
   int str2time_0;
   if (UseFixed_Date) {
      str2time_0 = StrToTime(_FixedDate);
      IndiPeriod = iBarShift(NULL, Period(), str2time_0, FALSE);
   }
   Gi_224 = IndiPeriod;
   Gs_276 = Gi_224 + "," + RegressionDegree + "," + DoubleToStr(K_N_L_Dev, 3);
   IndicatorShortName("Regression(" + Gs_276 + ")");
   if (Gi_224 > Bars) {
      Comment("\n\n                    ERROR - TOO SMALL HISTORY, RETURN NOW!");
      return (-1);
   }
   Gi_232 = 60 * Period();
   Gi_228 = RegressionDegree + 1;
   Gi_256 = Time[0];
   Gi_236 = iBarShift(Symbol(), Period(), Gi_256);
   Gi_240 = Gi_236 + Gi_224;
   Gi_unused_260 = Time[Gi_240];
   Gi_244 = Gi_224;
   ObjectCreate("_stdDev(" + Gs_276 + ")", OBJ_STDDEVCHANNEL, 0, Time[0], 0, Time[0], 0);
   ObjectSet("_stdDev(" + Gs_276 + ")", OBJPROP_RAY, FALSE);
   for (int Li_4 = (-Gi_224) / 2; Li_4 < Gi_224; Li_4++) {
      ObjectCreate("_ar(" + Gs_276 + ")" + Li_4, OBJ_TREND, 0, Time[Gi_236 + 1 + Li_4], 0, Time[Gi_236 + Li_4], 0);
      ObjectSet("_ar(" + Gs_276 + ")" + Li_4, OBJPROP_RAY, FALSE);
      ObjectSet("_ar(" + Gs_276 + ")" + Li_4, OBJPROP_STYLE, STYLE_DOT);
      ObjectCreate("_arH(" + Gs_276 + ")" + Li_4, OBJ_TREND, 0, Time[Gi_236 + 1 + Li_4], 0, Time[Gi_236 + Li_4], 0);
      ObjectSet("_arH(" + Gs_276 + ")" + Li_4, OBJPROP_RAY, FALSE);
      ObjectCreate("_arL(" + Gs_276 + ")" + Li_4, OBJ_TREND, 0, Time[Gi_236 + 1 + Li_4], 0, Time[Gi_236 + Li_4], 0);
      ObjectSet("_arL(" + Gs_276 + ")" + Li_4, OBJPROP_RAY, FALSE);
      ObjectCreate("_arL2(" + Gs_276 + ")" + Li_4, OBJ_TREND, 0, Time[Gi_236 + 1 + Li_4], 0, Time[Gi_236 + Li_4], 0);
      ObjectSet("_arL2(" + Gs_276 + ")" + Li_4, OBJPROP_RAY, FALSE);
      ObjectCreate("_arH2(" + Gs_276 + ")" + Li_4, OBJ_TREND, 0, Time[Gi_236 + 1 + Li_4], 0, Time[Gi_236 + Li_4], 0);
      ObjectSet("_arH2(" + Gs_276 + ")" + Li_4, OBJPROP_RAY, FALSE);
      ObjectCreate("_arL3(" + Gs_276 + ")" + Li_4, OBJ_TREND, 0, Time[Gi_236 + 1 + Li_4], 0, Time[Gi_236 + Li_4], 0);
      ObjectSet("_arL3(" + Gs_276 + ")" + Li_4, OBJPROP_RAY, FALSE);
      ObjectCreate("_arH3(" + Gs_276 + ")" + Li_4, OBJ_TREND, 0, Time[Gi_236 + 1 + Li_4], 0, Time[Gi_236 + Li_4], 0);
      ObjectSet("_arH3(" + Gs_276 + ")" + Li_4, OBJPROP_RAY, FALSE);
      ObjectCreate("_arLF1_1(" + Gs_276 + ")" + Li_4, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li_4], 0, Time[Gi_236 + Li_4], 0, Time[Gi_236 + Li_4], 0);
      ObjectSet("_arLF1_1(" + Gs_276 + ")" + Li_4, OBJPROP_RAY, FALSE);
      ObjectSet("_arLF1_1(" + Gs_276 + ")" + Li_4, OBJPROP_BACK, TRUE);
      ObjectCreate("_arHF1_1(" + Gs_276 + ")" + Li_4, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li_4], 0, Time[Gi_236 + Li_4], 0, Time[Gi_236 + Li_4], 0);
      ObjectSet("_arHF1_1(" + Gs_276 + ")" + Li_4, OBJPROP_RAY, FALSE);
      ObjectSet("_arHF1_1(" + Gs_276 + ")" + Li_4, OBJPROP_BACK, TRUE);
      ObjectCreate("_arLF1_2(" + Gs_276 + ")" + Li_4, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li_4], 0, Time[Gi_236 + Li_4], 0, Time[Gi_236 + Li_4], 0);
      ObjectSet("_arLF1_2(" + Gs_276 + ")" + Li_4, OBJPROP_RAY, FALSE);
      ObjectSet("_arLF1_2(" + Gs_276 + ")" + Li_4, OBJPROP_BACK, TRUE);
      ObjectCreate("_arHF1_2(" + Gs_276 + ")" + Li_4, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li_4], 0, Time[Gi_236 + Li_4], 0, Time[Gi_236 + Li_4], 0);
      ObjectSet("_arHF1_2(" + Gs_276 + ")" + Li_4, OBJPROP_RAY, FALSE);
      ObjectSet("_arHF1_2(" + Gs_276 + ")" + Li_4, OBJPROP_BACK, TRUE);
      ObjectCreate("_arLF2_1(" + Gs_276 + ")" + Li_4, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li_4], 0, Time[Gi_236 + Li_4], 0, Time[Gi_236 + Li_4], 0);
      ObjectSet("_arLF2_1(" + Gs_276 + ")" + Li_4, OBJPROP_RAY, FALSE);
      ObjectSet("_arLF2_1(" + Gs_276 + ")" + Li_4, OBJPROP_BACK, TRUE);
      ObjectCreate("_arHF2_1(" + Gs_276 + ")" + Li_4, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li_4], 0, Time[Gi_236 + Li_4], 0, Time[Gi_236 + Li_4], 0);
      ObjectSet("_arHF2_1(" + Gs_276 + ")" + Li_4, OBJPROP_RAY, FALSE);
      ObjectSet("_arHF2_1(" + Gs_276 + ")" + Li_4, OBJPROP_BACK, TRUE);
      ObjectCreate("_arLF2_2(" + Gs_276 + ")" + Li_4, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li_4], 0, Time[Gi_236 + Li_4], 0, Time[Gi_236 + Li_4], 0);
      ObjectSet("_arLF2_2(" + Gs_276 + ")" + Li_4, OBJPROP_RAY, FALSE);
      ObjectSet("_arLF2_2(" + Gs_276 + ")" + Li_4, OBJPROP_BACK, TRUE);
      ObjectCreate("_arHF2_2(" + Gs_276 + ")" + Li_4, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li_4], 0, Time[Gi_236 + Li_4], 0, Time[Gi_236 + Li_4], 0);
      ObjectSet("_arHF2_2(" + Gs_276 + ")" + Li_4, OBJPROP_RAY, FALSE);
      ObjectSet("_arHF2_2(" + Gs_276 + ")" + Li_4, OBJPROP_BACK, TRUE);
   }
   return (0);
}

// 52D46093050F38C27267BCE42543EF60
int deinit() {
   ObjectDelete("_stdDev(" + Gs_276 + ")");
   for (int Li_0 = Gi_224; Li_0 >= (-Gi_224) / 2; Li_0--) {
      ObjectDelete("_ar(" + Gs_276 + ")" + Li_0);
      ObjectDelete("_arH(" + Gs_276 + ")" + Li_0);
      ObjectDelete("_arL(" + Gs_276 + ")" + Li_0);
      ObjectDelete("_arL2(" + Gs_276 + ")" + Li_0);
      ObjectDelete("_arH2(" + Gs_276 + ")" + Li_0);
      ObjectDelete("_arL3(" + Gs_276 + ")" + Li_0);
      ObjectDelete("_arH3(" + Gs_276 + ")" + Li_0);
      ObjectDelete("_arLF1_1(" + Gs_276 + ")" + Li_0);
      ObjectDelete("_arHF1_1(" + Gs_276 + ")" + Li_0);
      ObjectDelete("_arLF1_2(" + Gs_276 + ")" + Li_0);
      ObjectDelete("_arHF1_2(" + Gs_276 + ")" + Li_0);
      ObjectDelete("_arLF2_1(" + Gs_276 + ")" + Li_0);
      ObjectDelete("_arHF2_1(" + Gs_276 + ")" + Li_0);
      ObjectDelete("_arLF2_2(" + Gs_276 + ")" + Li_0);
      ObjectDelete("_arHF2_2(" + Gs_276 + ")" + Li_0);
   }
   Comment("");
   return (0);
}

// EA2B2676C28C0DB26D39331A336C6B92
int start() {
   int Li3_16;
   int ind_counted_0 = IndicatorCounted();
   if (Bars - ind_counted_0 > 1) {
      ObjectDelete("_stdDev(" + Gs_276 + ")");
      for (int Li_4 = Gi_224; Li_4 >= (-Gi_224) / 2; Li_4--) {
         ObjectDelete("_ar(" + Gs_276 + ")" + Li_4);
         ObjectDelete("_arH(" + Gs_276 + ")" + Li_4);
         ObjectDelete("_arL(" + Gs_276 + ")" + Li_4);
         ObjectDelete("_arL2(" + Gs_276 + ")" + Li_4);
         ObjectDelete("_arH2(" + Gs_276 + ")" + Li_4);
         ObjectDelete("_arL3(" + Gs_276 + ")" + Li_4);
         ObjectDelete("_arH3(" + Gs_276 + ")" + Li_4);
         ObjectDelete("_arLF1_1(" + Gs_276 + ")" + Li_4);
         ObjectDelete("_arHF1_1(" + Gs_276 + ")" + Li_4);
         ObjectDelete("_arLF1_2(" + Gs_276 + ")" + Li_4);
         ObjectDelete("_arHF1_2(" + Gs_276 + ")" + Li_4);
         ObjectDelete("_arLF2_1(" + Gs_276 + ")" + Li_4);
         ObjectDelete("_arHF2_1(" + Gs_276 + ")" + Li_4);
         ObjectDelete("_arLF2_2(" + Gs_276 + ")" + Li_4);
         ObjectDelete("_arHF2_2(" + Gs_276 + ")" + Li_4);
      }
      Sleep(5000);
      init();
   }
   if (Gi_248 != Gi_236 || Gi_252 != Gi_240) {
      Gi_224 = Gi_240 - Gi_236;
      Gi_248 = Gi_240;
      Gi_252 = Gi_240;
      if (Gi_244 < Gi_224) {
         ObjectCreate("_stdDev(" + Gs_276 + ")", OBJ_STDDEVCHANNEL, 0, Time[0], 0, Time[0], 0);
         ObjectSet("_stdDev(" + Gs_276 + ")", OBJPROP_RAY, FALSE);
         for (int Li8_20 = Gi_244; Li8_20 <= Gi_224; Li8_20++) {
            ObjectCreate("_ar(" + Gs_276 + ")" + Li8_20, OBJ_TREND, 0, Time[Gi_236 + 1 + Li8_20], 0, Time[Gi_236 + Li8_20], 0);
            ObjectSet("_ar(" + Gs_276 + ")" + Li8_20, OBJPROP_RAY, FALSE);
            ObjectSet("_ar(" + Gs_276 + ")" + Li8_20, OBJPROP_STYLE, STYLE_DOT);
            ObjectCreate("_arH(" + Gs_276 + ")" + Li8_20, OBJ_TREND, 0, Time[Gi_236 + 1 + Li8_20], 0, Time[Gi_236 + Li8_20], 0);
            ObjectSet("_arH(" + Gs_276 + ")" + Li8_20, OBJPROP_RAY, FALSE);
            ObjectCreate("_arL(" + Gs_276 + ")" + Li8_20, OBJ_TREND, 0, Time[Gi_236 + 1 + Li8_20], 0, Time[Gi_236 + Li8_20], 0);
            ObjectSet("_arL(" + Gs_276 + ")" + Li8_20, OBJPROP_RAY, FALSE);
            ObjectCreate("_arL2(" + Gs_276 + ")" + Li8_20, OBJ_TREND, 0, Time[Gi_236 + 1 + Li8_20], 0, Time[Gi_236 + Li8_20], 0);
            ObjectSet("_arL2(" + Gs_276 + ")" + Li8_20, OBJPROP_RAY, FALSE);
            ObjectCreate("_arH2(" + Gs_276 + ")" + Li8_20, OBJ_TREND, 0, Time[Gi_236 + 1 + Li8_20], 0, Time[Gi_236 + Li8_20], 0);
            ObjectSet("_arH2(" + Gs_276 + ")" + Li8_20, OBJPROP_RAY, FALSE);
            ObjectCreate("_arL3(" + Gs_276 + ")" + Li8_20, OBJ_TREND, 0, Time[Gi_236 + 1 + Li8_20], 0, Time[Gi_236 + Li8_20], 0);
            ObjectSet("_arL3(" + Gs_276 + ")" + Li8_20, OBJPROP_RAY, FALSE);
            ObjectCreate("_arH3(" + Gs_276 + ")" + Li8_20, OBJ_TREND, 0, Time[Gi_236 + 1 + Li8_20], 0, Time[Gi_236 + Li8_20], 0);
            ObjectSet("_arH3(" + Gs_276 + ")" + Li8_20, OBJPROP_RAY, FALSE);
            ObjectCreate("_arLF1_1(" + Gs_276 + ")" + Li8_20, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li8_20], 0, Time[Gi_236 + Li8_20], 0, Time[Gi_236 + Li8_20], 0);
            ObjectSet("_arLF1_1(" + Gs_276 + ")" + Li8_20, OBJPROP_RAY, FALSE);
            ObjectSet("_arLF1_1(" + Gs_276 + ")" + Li8_20, OBJPROP_BACK, TRUE);
            ObjectCreate("_arHF1_1(" + Gs_276 + ")" + Li8_20, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li8_20], 0, Time[Gi_236 + Li8_20], 0, Time[Gi_236 + Li8_20], 0);
            ObjectSet("_arHF1_1(" + Gs_276 + ")" + Li8_20, OBJPROP_RAY, FALSE);
            ObjectSet("_arHF1_1(" + Gs_276 + ")" + Li8_20, OBJPROP_BACK, TRUE);
            ObjectCreate("_arLF1_2(" + Gs_276 + ")" + Li8_20, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li8_20], 0, Time[Gi_236 + Li8_20], 0, Time[Gi_236 + Li8_20], 0);
            ObjectSet("_arLF1_2(" + Gs_276 + ")" + Li8_20, OBJPROP_RAY, FALSE);
            ObjectSet("_arLF1_2(" + Gs_276 + ")" + Li8_20, OBJPROP_BACK, TRUE);
            ObjectCreate("_arHF1_2(" + Gs_276 + ")" + Li8_20, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li8_20], 0, Time[Gi_236 + Li8_20], 0, Time[Gi_236 + Li8_20], 0);
            ObjectSet("_arHF1_2(" + Gs_276 + ")" + Li8_20, OBJPROP_RAY, FALSE);
            ObjectSet("_arHF1_2(" + Gs_276 + ")" + Li8_20, OBJPROP_BACK, TRUE);
            ObjectCreate("_arLF2_1(" + Gs_276 + ")" + Li8_20, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li8_20], 0, Time[Gi_236 + Li8_20], 0, Time[Gi_236 + Li8_20], 0);
            ObjectSet("_arLF2_1(" + Gs_276 + ")" + Li8_20, OBJPROP_RAY, FALSE);
            ObjectSet("_arLF2_1(" + Gs_276 + ")" + Li8_20, OBJPROP_BACK, TRUE);
            ObjectCreate("_arHF2_1(" + Gs_276 + ")" + Li8_20, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li8_20], 0, Time[Gi_236 + Li8_20], 0, Time[Gi_236 + Li8_20], 0);
            ObjectSet("_arHF2_1(" + Gs_276 + ")" + Li8_20, OBJPROP_RAY, FALSE);
            ObjectSet("_arHF2_1(" + Gs_276 + ")" + Li8_20, OBJPROP_BACK, TRUE);
            ObjectCreate("_arLF2_2(" + Gs_276 + ")" + Li8_20, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li8_20], 0, Time[Gi_236 + Li8_20], 0, Time[Gi_236 + Li8_20], 0);
            ObjectSet("_arLF2_2(" + Gs_276 + ")" + Li8_20, OBJPROP_RAY, FALSE);
            ObjectSet("_arLF2_2(" + Gs_276 + ")" + Li8_20, OBJPROP_BACK, TRUE);
            ObjectCreate("_arHF2_2(" + Gs_276 + ")" + Li8_20, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li8_20], 0, Time[Gi_236 + Li8_20], 0, Time[Gi_236 + Li8_20], 0);
            ObjectSet("_arHF2_2(" + Gs_276 + ")" + Li8_20, OBJPROP_RAY, FALSE);
            ObjectSet("_arHF2_2(" + Gs_276 + ")" + Li8_20, OBJPROP_BACK, TRUE);
         }
         for (int Li1_20 = (-Gi_244) / 2; Li1_20 >= (-Gi_224) / 2; Li1_20--) {
            ObjectCreate("_ar(" + Gs_276 + ")" + Li1_20, OBJ_TREND, 0, Time[Gi_236 + 1 + Li1_20], 0, Time[Gi_236 + Li1_20], 0);
            ObjectSet("_ar(" + Gs_276 + ")" + Li1_20, OBJPROP_RAY, FALSE);
            ObjectSet("_ar(" + Gs_276 + ")" + Li1_20, OBJPROP_STYLE, STYLE_DOT);
            ObjectCreate("_arH(" + Gs_276 + ")" + Li1_20, OBJ_TREND, 0, Time[Gi_236 + 1 + Li1_20], 0, Time[Gi_236 + Li1_20], 0);
            ObjectSet("_arH(" + Gs_276 + ")" + Li1_20, OBJPROP_RAY, FALSE);
            ObjectCreate("_arL(" + Gs_276 + ")" + Li1_20, OBJ_TREND, 0, Time[Gi_236 + 1 + Li1_20], 0, Time[Gi_236 + Li1_20], 0);
            ObjectSet("_arL(" + Gs_276 + ")" + Li1_20, OBJPROP_RAY, FALSE);
            ObjectCreate("_arL2(" + Gs_276 + ")" + Li1_20, OBJ_TREND, 0, Time[Gi_236 + 1 + Li1_20], 0, Time[Gi_236 + Li1_20], 0);
            ObjectSet("_arL2(" + Gs_276 + ")" + Li1_20, OBJPROP_RAY, FALSE);
            ObjectCreate("_arH2(" + Gs_276 + ")" + Li1_20, OBJ_TREND, 0, Time[Gi_236 + 1 + Li1_20], 0, Time[Gi_236 + Li1_20], 0);
            ObjectSet("_arH2(" + Gs_276 + ")" + Li1_20, OBJPROP_RAY, FALSE);
            ObjectCreate("_arL3(" + Gs_276 + ")" + Li1_20, OBJ_TREND, 0, Time[Gi_236 + 1 + Li1_20], 0, Time[Gi_236 + Li1_20], 0);
            ObjectSet("_arL3(" + Gs_276 + ")" + Li1_20, OBJPROP_RAY, FALSE);
            ObjectCreate("_arH3(" + Gs_276 + ")" + Li1_20, OBJ_TREND, 0, Time[Gi_236 + 1 + Li1_20], 0, Time[Gi_236 + Li1_20], 0);
            ObjectSet("_arH3(" + Gs_276 + ")" + Li1_20, OBJPROP_RAY, FALSE);
            ObjectCreate("_arLF1_1(" + Gs_276 + ")" + Li1_20, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li1_20], 0, Time[Gi_236 + Li1_20], 0, Time[Gi_236 + Li1_20], 0);
            ObjectSet("_arLF1_1(" + Gs_276 + ")" + Li1_20, OBJPROP_RAY, FALSE);
            ObjectSet("_arLF1_1(" + Gs_276 + ")" + Li1_20, OBJPROP_BACK, TRUE);
            ObjectCreate("_arHF1_1(" + Gs_276 + ")" + Li1_20, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li1_20], 0, Time[Gi_236 + Li1_20], 0, Time[Gi_236 + Li1_20], 0);
            ObjectSet("_arHF1_1(" + Gs_276 + ")" + Li1_20, OBJPROP_RAY, FALSE);
            ObjectSet("_arHF1_1(" + Gs_276 + ")" + Li1_20, OBJPROP_BACK, TRUE);
            ObjectCreate("_arLF1_2(" + Gs_276 + ")" + Li1_20, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li1_20], 0, Time[Gi_236 + Li1_20], 0, Time[Gi_236 + Li1_20], 0);
            ObjectSet("_arLF1_2(" + Gs_276 + ")" + Li1_20, OBJPROP_RAY, FALSE);
            ObjectSet("_arLF1_2(" + Gs_276 + ")" + Li1_20, OBJPROP_BACK, TRUE);
            ObjectCreate("_arHF1_2(" + Gs_276 + ")" + Li1_20, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li1_20], 0, Time[Gi_236 + Li1_20], 0, Time[Gi_236 + Li1_20], 0);
            ObjectSet("_arHF1_2(" + Gs_276 + ")" + Li1_20, OBJPROP_RAY, FALSE);
            ObjectSet("_arHF1_2(" + Gs_276 + ")" + Li1_20, OBJPROP_BACK, TRUE);
            ObjectCreate("_arLF2_1(" + Gs_276 + ")" + Li1_20, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li1_20], 0, Time[Gi_236 + Li1_20], 0, Time[Gi_236 + Li1_20], 0);
            ObjectSet("_arLF2_1(" + Gs_276 + ")" + Li1_20, OBJPROP_RAY, FALSE);
            ObjectSet("_arLF2_1(" + Gs_276 + ")" + Li1_20, OBJPROP_BACK, TRUE);
            ObjectCreate("_arHF2_1(" + Gs_276 + ")" + Li1_20, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li1_20], 0, Time[Gi_236 + Li1_20], 0, Time[Gi_236 + Li1_20], 0);
            ObjectSet("_arHF2_1(" + Gs_276 + ")" + Li1_20, OBJPROP_RAY, FALSE);
            ObjectSet("_arHF2_1(" + Gs_276 + ")" + Li1_20, OBJPROP_BACK, TRUE);
            ObjectCreate("_arLF2_2(" + Gs_276 + ")" + Li1_20, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li1_20], 0, Time[Gi_236 + Li1_20], 0, Time[Gi_236 + Li1_20], 0);
            ObjectSet("_arLF2_2(" + Gs_276 + ")" + Li1_20, OBJPROP_RAY, FALSE);
            ObjectSet("_arLF2_2(" + Gs_276 + ")" + Li1_20, OBJPROP_BACK, TRUE);
            ObjectCreate("_arHF2_2(" + Gs_276 + ")" + Li1_20, OBJ_TRIANGLE, 0, Time[Gi_236 + 1 + Li1_20], 0, Time[Gi_236 + Li1_20], 0, Time[Gi_236 + Li1_20], 0);
            ObjectSet("_arHF2_2(" + Gs_276 + ")" + Li1_20, OBJPROP_RAY, FALSE);
            ObjectSet("_arHF2_2(" + Gs_276 + ")" + Li1_20, OBJPROP_BACK, TRUE);
         }
         Gi_244 = Gi_224;
      }
      if (Gi_244 > Gi_224) {
         ObjectDelete("_stdDev(" + Gs_276 + ")");
         for (int Li2_20 = Gi_244; Li2_20 >= Gi_224; Li2_20--) {
            ObjectDelete("_ar(" + Gs_276 + ")" + Li2_20);
            ObjectDelete("_arH(" + Gs_276 + ")" + Li2_20);
            ObjectDelete("_arL(" + Gs_276 + ")" + Li2_20);
            ObjectDelete("_arL2(" + Gs_276 + ")" + Li2_20);
            ObjectDelete("_arH2(" + Gs_276 + ")" + Li2_20);
            ObjectDelete("_arL3(" + Gs_276 + ")" + Li2_20);
            ObjectDelete("_arH3(" + Gs_276 + ")" + Li2_20);
            ObjectDelete("_arLF1_1(" + Gs_276 + ")" + Li2_20);
            ObjectDelete("_arHF1_1(" + Gs_276 + ")" + Li2_20);
            ObjectDelete("_arLF1_2(" + Gs_276 + ")" + Li2_20);
            ObjectDelete("_arHF1_2(" + Gs_276 + ")" + Li2_20);
            ObjectDelete("_arLF2_1(" + Gs_276 + ")" + Li2_20);
            ObjectDelete("_arHF2_1(" + Gs_276 + ")" + Li2_20);
            ObjectDelete("_arLF2_2(" + Gs_276 + ")" + Li2_20);
            ObjectDelete("_arHF2_2(" + Gs_276 + ")" + Li2_20);
         }
         for (int Li3_20 = (-Gi_224) / 2; Li3_20 >= (-Gi_244) / 2; Li3_20--) {
            ObjectDelete("_ar(" + Gs_276 + ")" + Li3_20);
            ObjectDelete("_arH(" + Gs_276 + ")" + Li3_20);
            ObjectDelete("_arL(" + Gs_276 + ")" + Li3_20);
            ObjectDelete("_arL2(" + Gs_276 + ")" + Li3_20);
            ObjectDelete("_arH2(" + Gs_276 + ")" + Li3_20);
            ObjectDelete("_arL3(" + Gs_276 + ")" + Li3_20);
            ObjectDelete("_arH3(" + Gs_276 + ")" + Li3_20);
            ObjectDelete("_arLF1_1(" + Gs_276 + ")" + Li3_20);
            ObjectDelete("_arHF1_1(" + Gs_276 + ")" + Li3_20);
            ObjectDelete("_arLF1_2(" + Gs_276 + ")" + Li3_20);
            ObjectDelete("_arHF1_2(" + Gs_276 + ")" + Li3_20);
            ObjectDelete("_arLF2_1(" + Gs_276 + ")" + Li3_20);
            ObjectDelete("_arHF2_1(" + Gs_276 + ")" + Li3_20);
            ObjectDelete("_arLF2_2(" + Gs_276 + ")" + Li3_20);
            ObjectDelete("_arHF2_2(" + Gs_276 + ")" + Li3_20);
         }
         Gi_244 = Gi_224;
      }
   }
   Gda_180[1] = Gi_224 + 1;
   for (int Li_8 = 1; Li_8 <= Gi_228 * 2 - 2; Li_8++) {
      Gd_184 = 0.0;
      for (int shift5_12 = Gi_236; shift5_12 <= Gi_236 + Gi_224; shift5_12++) Gd_184 += MathPow(shift5_12, Li_8);
      Gda_180[Li_8 + 1] = Gd_184;
   }
   for (int Li1_8 = 1; Li1_8 <= Gi_228; Li1_8++) {
      Gd_184 = 0.0;
      for (int shift1_12 = Gi_236; shift1_12 <= Gi_236 + Gi_224; shift1_12++) {
         if (Li1_8 == 1) Gd_184 += Close[shift1_12];
         else Gd_184 += Close[shift1_12] * MathPow(shift1_12, Li1_8 - 1);
      }
      Gda_172[Li1_8] = Gd_184;
   }
   for ( int Li4_20 = 1; Li4_20 <= Gi_228; Li4_20++) {
      for ( int Li2_8 = 1; Li2_8 <= Gi_228; Li2_8++) {
         Li3_16 = Li2_8 + Li4_20 - 1;
         Gda_168[Li2_8][Li4_20] = Gda_180[Li3_16];
      }
   }
   f0_0(Gi_228, Gda_168, Gda_172, Gda_176);
   Gd_200 = 0.0;
   for ( int shift2_12 = Gi_224; shift2_12 >= 0; shift2_12--) {
      Gd_184 = 0.0;
      for (int Li5_16 = 1; Li5_16 <= RegressionDegree; Li5_16++) {
         Gd_184 += (Gda_176[Li5_16 + 1]) * MathPow(Gi_236 + shift2_12, Li5_16);
         Gd_192 += (Gda_176[Li5_16 + 1]) * MathPow(Gi_236 + shift2_12 + 1, Li5_16);
      }
      Gd_152 = Gda_176[1] + Gd_184;
      Gd_200 += MathPow(Close[shift2_12 + Gi_236] - Gd_152, 2);
   }
   Gd_216 = K_N_L_Dev3 * MathSqrt(Gd_200 / (Gi_224 + 1));
   Gd_208 = K_N_L_Dev2 * MathSqrt(Gd_200 / (Gi_224 + 1));
   Gd_200 = K_N_L_Dev * MathSqrt(Gd_200 / (Gi_224 + 1));
   ObjectMove("_stdDev(" + Gs_276 + ")", 0, Time[Gi_236], 0);
   ObjectMove("_stdDev(" + Gs_276 + ")", 1, Time[0], 0);
   for ( int shift3_12 = Gi_224; shift3_12 >= (-Gi_224) / 2; shift3_12--) {
      Gd_184 = 0.0;
      Gd_192 = 0.0;
      for (int Li6_16 = 1; Li6_16 <= RegressionDegree; Li6_16++) {
         Gd_184 += (Gda_176[Li6_16 + 1]) * MathPow(Gi_236 + shift3_12, Li6_16);
         Gd_192 += (Gda_176[Li6_16 + 1]) * MathPow(Gi_236 + shift3_12 + 1, Li6_16);
      }
      Gd_152 = Gda_176[1] + Gd_184;
      Gd_160 = Gda_176[1] + Gd_192;
      if (shift3_12 >= 0 && shift3_12 < Gi_224) {
         if (Center_Line) {
            ObjectMove("_ar(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160);
            ObjectMove("_ar(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152);
         }
         ObjectMove("_arH(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 + Gd_200);
         ObjectMove("_arH(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 + Gd_200);
         ObjectMove("_arL(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 - Gd_200);
         ObjectMove("_arL(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 - Gd_200);
         ObjectMove("_arL2(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 - Gd_208);
         ObjectMove("_arL2(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 - Gd_208);
         ObjectMove("_arH2(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 + Gd_208);
         ObjectMove("_arH2(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 + Gd_208);
         ObjectMove("_arL3(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 - Gd_216);
         ObjectMove("_arL3(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 - Gd_216);
         ObjectMove("_arH3(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 + Gd_216);
         ObjectMove("_arH3(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 + Gd_216);
         ObjectMove("_arLF1_1(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 - Gd_200);
         ObjectMove("_arLF1_1(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 - Gd_200);
         ObjectMove("_arLF1_1(" + Gs_276 + ")" + shift3_12, 2, Time[shift3_12 + Gi_236 + 1], Gd_160 - Gd_208);
         ObjectMove("_arLF1_2(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 - Gd_208);
         ObjectMove("_arLF1_2(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 - Gd_208);
         ObjectMove("_arLF1_2(" + Gs_276 + ")" + shift3_12, 2, Time[shift3_12 + Gi_236], Gd_152 - Gd_200);
         ObjectMove("_arHF1_1(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 + Gd_200);
         ObjectMove("_arHF1_1(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 + Gd_200);
         ObjectMove("_arHF1_1(" + Gs_276 + ")" + shift3_12, 2, Time[shift3_12 + Gi_236 + 1], Gd_160 + Gd_208);
         ObjectMove("_arHF1_2(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 + Gd_208);
         ObjectMove("_arHF1_2(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 + Gd_208);
         ObjectMove("_arHF1_2(" + Gs_276 + ")" + shift3_12, 2, Time[shift3_12 + Gi_236], Gd_152 + Gd_200);
         ObjectMove("_arLF2_1(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 - Gd_208);
         ObjectMove("_arLF2_1(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 - Gd_208);
         ObjectMove("_arLF2_1(" + Gs_276 + ")" + shift3_12, 2, Time[shift3_12 + Gi_236 + 1], Gd_160 - Gd_216);
         ObjectMove("_arLF2_2(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 - Gd_216);
         ObjectMove("_arLF2_2(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 - Gd_216);
         ObjectMove("_arLF2_2(" + Gs_276 + ")" + shift3_12, 2, Time[shift3_12 + Gi_236], Gd_152 - Gd_208);
         ObjectMove("_arHF2_1(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 + Gd_208);
         ObjectMove("_arHF2_1(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 + Gd_208);
         ObjectMove("_arHF2_1(" + Gs_276 + ")" + shift3_12, 2, Time[shift3_12 + Gi_236 + 1], Gd_160 + Gd_216);
         ObjectMove("_arHF2_2(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 + Gd_216);
         ObjectMove("_arHF2_2(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 + Gd_216);
         ObjectMove("_arHF2_2(" + Gs_276 + ")" + shift3_12, 2, Time[shift3_12 + Gi_236], Gd_152 + Gd_208);
         if (Center_Line) ObjectSet("_ar(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Regression_Clr1);
         ObjectSet("_arH(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Regression_Clr1);
         ObjectSet("_arL(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Regression_Clr1);
         ObjectSet("_arL2(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Regression_Clr2);
         ObjectSet("_arH2(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Regression_Clr2);
         ObjectSet("_arL3(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Regression_Clr3);
         ObjectSet("_arH3(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Regression_Clr3);
         ObjectSet("_arLF1_1(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Fill_Clr1);
         ObjectSet("_arLF1_2(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Fill_Clr1);
         ObjectSet("_arHF1_1(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Fill_Clr1);
         ObjectSet("_arHF1_2(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Fill_Clr1);
         ObjectSet("_arLF2_1(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Fill_Clr2);
         ObjectSet("_arLF2_2(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Fill_Clr2);
         ObjectSet("_arHF2_1(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Fill_Clr2);
         ObjectSet("_arHF2_2(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Fill_Clr2);
      }
      if (shift3_12 < 0) {
         if (shift3_12 + Gi_236 >= 0) {
            if (Center_Line) {
               ObjectMove("_ar(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160);
               ObjectMove("_ar(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152);
            }
            ObjectMove("_arH(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 + Gd_200);
            ObjectMove("_arH(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 + Gd_200);
            ObjectMove("_arL(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 - Gd_200);
            ObjectMove("_arL(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 - Gd_200);
            ObjectMove("_arL2(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 - Gd_208);
            ObjectMove("_arL2(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 - Gd_208);
            ObjectMove("_arH2(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 + Gd_208);
            ObjectMove("_arH2(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 + Gd_208);
            ObjectMove("_arL3(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 - Gd_216);
            ObjectMove("_arL3(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 - Gd_216);
            ObjectMove("_arH3(" + Gs_276 + ")" + shift3_12, 0, Time[shift3_12 + Gi_236 + 1], Gd_160 + Gd_216);
            ObjectMove("_arH3(" + Gs_276 + ")" + shift3_12, 1, Time[shift3_12 + Gi_236], Gd_152 + Gd_216);
         }
         if (shift3_12 + Gi_236 < 0) {
            G_datetime_264 = Time[0] - (shift3_12 + Gi_236) * Gi_232;
            G_datetime_268 = Time[0] - (shift3_12 + Gi_236 + 1) * Gi_232;
            if (Future_CenterLine) {
               ObjectMove("_ar(" + Gs_276 + ")" + shift3_12, 0, G_datetime_268, Gd_160);
               ObjectMove("_ar(" + Gs_276 + ")" + shift3_12, 1, G_datetime_264, Gd_152);
            }
            ObjectMove("_arH(" + Gs_276 + ")" + shift3_12, 0, G_datetime_268, Gd_160 + Gd_200);
            ObjectMove("_arH(" + Gs_276 + ")" + shift3_12, 1, G_datetime_264, Gd_152 + Gd_200);
            ObjectMove("_arL(" + Gs_276 + ")" + shift3_12, 0, G_datetime_268, Gd_160 - Gd_200);
            ObjectMove("_arL(" + Gs_276 + ")" + shift3_12, 1, G_datetime_264, Gd_152 - Gd_200);
            ObjectMove("_arL2(" + Gs_276 + ")" + shift3_12, 0, G_datetime_268, Gd_160 - Gd_208);
            ObjectMove("_arL2(" + Gs_276 + ")" + shift3_12, 1, G_datetime_264, Gd_152 - Gd_208);
            ObjectMove("_arH2(" + Gs_276 + ")" + shift3_12, 0, G_datetime_268, Gd_160 + Gd_208);
            ObjectMove("_arH2(" + Gs_276 + ")" + shift3_12, 1, G_datetime_264, Gd_152 + Gd_208);
            ObjectMove("_arL3(" + Gs_276 + ")" + shift3_12, 0, G_datetime_268, Gd_160 - Gd_216);
            ObjectMove("_arL3(" + Gs_276 + ")" + shift3_12, 1, G_datetime_264, Gd_152 - Gd_216);
            ObjectMove("_arH3(" + Gs_276 + ")" + shift3_12, 0, G_datetime_268, Gd_160 + Gd_216);
            ObjectMove("_arH3(" + Gs_276 + ")" + shift3_12, 1, G_datetime_264, Gd_152 + Gd_216);
         }
         ObjectMove("_arLF1_1(" + Gs_276 + ")" + shift3_12, 0, G_datetime_268, Gd_160 - Gd_200);
         ObjectMove("_arLF1_1(" + Gs_276 + ")" + shift3_12, 1, G_datetime_264, Gd_152 - Gd_200);
         ObjectMove("_arLF1_1(" + Gs_276 + ")" + shift3_12, 2, G_datetime_268, Gd_160 - Gd_208);
         ObjectMove("_arLF1_2(" + Gs_276 + ")" + shift3_12, 0, G_datetime_268, Gd_160 - Gd_208);
         ObjectMove("_arLF1_2(" + Gs_276 + ")" + shift3_12, 1, G_datetime_264, Gd_152 - Gd_208);
         ObjectMove("_arLF1_2(" + Gs_276 + ")" + shift3_12, 2, G_datetime_264, Gd_152 - Gd_200);
         ObjectMove("_arHF1_1(" + Gs_276 + ")" + shift3_12, 0, G_datetime_268, Gd_160 + Gd_200);
         ObjectMove("_arHF1_1(" + Gs_276 + ")" + shift3_12, 1, G_datetime_264, Gd_152 + Gd_200);
         ObjectMove("_arHF1_1(" + Gs_276 + ")" + shift3_12, 2, G_datetime_268, Gd_160 + Gd_208);
         ObjectMove("_arHF1_2(" + Gs_276 + ")" + shift3_12, 0, G_datetime_268, Gd_160 + Gd_208);
         ObjectMove("_arHF1_2(" + Gs_276 + ")" + shift3_12, 1, G_datetime_264, Gd_152 + Gd_208);
         ObjectMove("_arHF1_2(" + Gs_276 + ")" + shift3_12, 2, G_datetime_264, Gd_152 + Gd_200);
         ObjectMove("_arLF2_1(" + Gs_276 + ")" + shift3_12, 0, G_datetime_268, Gd_160 - Gd_208);
         ObjectMove("_arLF2_1(" + Gs_276 + ")" + shift3_12, 1, G_datetime_264, Gd_152 - Gd_208);
         ObjectMove("_arLF2_1(" + Gs_276 + ")" + shift3_12, 2, G_datetime_268, Gd_160 - Gd_216);
         ObjectMove("_arLF2_2(" + Gs_276 + ")" + shift3_12, 0, G_datetime_268, Gd_160 - Gd_216);
         ObjectMove("_arLF2_2(" + Gs_276 + ")" + shift3_12, 1, G_datetime_264, Gd_152 - Gd_216);
         ObjectMove("_arLF2_2(" + Gs_276 + ")" + shift3_12, 2, G_datetime_264, Gd_152 - Gd_208);
         ObjectMove("_arHF2_1(" + Gs_276 + ")" + shift3_12, 0, G_datetime_268, Gd_160 + Gd_208);
         ObjectMove("_arHF2_1(" + Gs_276 + ")" + shift3_12, 1, G_datetime_264, Gd_152 + Gd_208);
         ObjectMove("_arHF2_1(" + Gs_276 + ")" + shift3_12, 2, G_datetime_268, Gd_160 + Gd_216);
         ObjectMove("_arHF2_2(" + Gs_276 + ")" + shift3_12, 0, G_datetime_268, Gd_160 + Gd_216);
         ObjectMove("_arHF2_2(" + Gs_276 + ")" + shift3_12, 1, G_datetime_264, Gd_152 + Gd_216);
         ObjectMove("_arHF2_2(" + Gs_276 + ")" + shift3_12, 2, G_datetime_264, Gd_152 + Gd_208);
         if (Future_CenterLine) ObjectSet("_ar(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Regression_Clr1);
         ObjectSet("_arH(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Regression_Clr1);
         ObjectSet("_arL(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Regression_Clr1);
         ObjectSet("_arL2(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Regression_Clr2);
         ObjectSet("_arH2(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Regression_Clr2);
         ObjectSet("_arL3(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Regression_Clr3);
         ObjectSet("_arH3(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Regression_Clr3);
         ObjectSet("_arLF1_1(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Fill_Clr1);
         ObjectSet("_arHF1_1(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Fill_Clr1);
         ObjectSet("_arLF1_2(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Fill_Clr1);
         ObjectSet("_arHF1_2(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Fill_Clr1);
         ObjectSet("_arLF2_1(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Fill_Clr2);
         ObjectSet("_arHF2_1(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Fill_Clr2);
         ObjectSet("_arLF2_2(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Fill_Clr2);
         ObjectSet("_arHF2_2(" + Gs_276 + ")" + shift3_12, OBJPROP_COLOR, Fill_Clr2);
      }
   }
   Sleep(5000);
   return (0);
}

// F1704F98D36E2118065B26704D8A3717
void f0_0(int Ai_0, double &Ada_4[10][10], double &Ada_8[10], double &Ada_12[10]) {
   int Li_28;
   double Ld_32;
   double Ld_40;
   double Ld_48;
   for (int Li_24 = 1; Li_24 <= Ai_0 - 1; Li_24++) {
      Li_28 = 0;
      Ld_40 = 0;
      for (int Li6_16 = Li_24; Li6_16 <= Ai_0; Li6_16++) {
         if (MathAbs(Ada_4[Li6_16][Li_24]) > Ld_40) {
            Ld_40 = MathAbs(Ada_4[Li6_16][Li_24]);
            Li_28 = Li6_16;
         }
      }
      if (Li_28 == 0) return;
      if (Li_28 != Li_24) {
         for (int Li5_20 = 1; Li5_20 <= Ai_0; Li5_20++) {
            Ld_48 = Ada_4[Li_24][Li5_20];
            Ada_4[Li_24][Li5_20] = Ada_4[Li_28][Li5_20];
            Ada_4[Li_28][Li5_20] = Ld_48;
         }
         Ld_48 = Ada_8[Li_24];
         Ada_8[Li_24] = Ada_8[Li_28];
         Ada_8[Li_28] = Ld_48;
      }
      for ( int Li1_16 = Li_24 + 1; Li1_16 <= Ai_0; Li1_16++) {
         Ld_32 = Ada_4[Li1_16][Li_24] / Ada_4[Li_24][Li_24];
         for ( int Li6_20 = 1; Li6_20 <= Ai_0; Li6_20++) {
            if (Li6_20 == Li_24) Ada_4[Li1_16][Li6_20] = 0;
            else Ada_4[Li1_16][Li6_20] = Ada_4[Li1_16][Li6_20] - Ld_32 * Ada_4[Li_24][Li6_20];
         }
         Ada_8[Li1_16] = Ada_8[Li1_16] - Ld_32 * Ada_8[Li_24];
      }
   }
   Ada_12[Ai_0] = Ada_8[Ai_0] / Ada_4[Ai_0][Ai_0];
   for ( int Li2_16 = Ai_0 - 1; Li2_16 >= 1; Li2_16--) {
      Ld_48 = 0;
      for ( int Li7_20 = 1; Li7_20 <= Ai_0 - Li2_16; Li7_20++) {
         Ld_48 += (Ada_4[Li2_16][Li2_16 + Li7_20]) * (Ada_12[Li2_16 + Li7_20]);
         Ada_12[Li2_16] = 1 / Ada_4[Li2_16][Li2_16] * (Ada_8[Li2_16] - Ld_48);
      }
   }
}
