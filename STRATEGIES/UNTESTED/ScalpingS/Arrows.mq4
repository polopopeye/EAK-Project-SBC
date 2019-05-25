//

#property copyright "Copyright � 2010 OOO ����"
#property link      "http://www.forexriches.ru"

#property indicator_chart_window
#property indicator_buffers 4
#property indicator_color1 Blue
#property indicator_color2 Yellow
#property indicator_color3 Aqua
#property indicator_color4 Red

extern int FastEMA = 13;
extern int SlowEMA = 21;
extern int RSIPeriod = 9;
extern bool Alerts = TRUE;
double g_ibuf_92[];
double g_ibuf_96[];
double g_ibuf_100[];
double g_ibuf_104[];
int gi_108 = 0;
int gi_112 = 0;
double gd_116 = 0.0;
double gd_unused_124 = 0.0;

   SetIndexStyle(0, DRAW_LINE);
   SetIndexBuffer(0, g_ibuf_92);
   SetIndexStyle(1, DRAW_LINE);
   SetIndexBuffer(1, g_ibuf_96);
   SetIndexStyle(2, DRAW_ARROW);
   SetIndexArrow(2, 217);
   SetIndexBuffer(2, g_ibuf_100);
   SetIndexEmptyValue(2, 0.0);
   SetIndexStyle(3, DRAW_ARROW);
   SetIndexArrow(3, 218);
   SetIndexBuffer(3, g_ibuf_104);
   SetIndexEmptyValue(3, 0.0);
   return (0);
}

int deinit() {
   return (0);
}

int start() {
   int li_4 = IndicatorCounted();
   double irsi_8 = 0;
   bool li_16 = FALSE;
   double price_20 = 0;
   if (li_4 < 0) return (-1);
   if (li_4 > 0) li_4--;
   int li_0 = Bars - li_4;
   for (int li_28 = 0; li_28 < li_0; li_28++) {
      g_ibuf_92[li_28] = iMA(NULL, 0, FastEMA, 0, MODE_EMA, PRICE_CLOSE, li_28);
      g_ibuf_96[li_28] = iMA(NULL, 0, SlowEMA, 0, MODE_EMA, PRICE_CLOSE, li_28);
      irsi_8 = iRSI(NULL, 0, RSIPeriod, PRICE_CLOSE, li_28);
      gd_116 = g_ibuf_92[li_28] - g_ibuf_96[li_28];
      Comment("pipdiffCurrent = " + gd_116 + " ");
      if (gd_116 > 0.0 && irsi_8 > 50.0) gi_108 = 1;
      else
         if (gd_116 < 0.0 && irsi_8 < 50.0) gi_108 = 2;
      if (gi_108 == 1 && gi_112 == 2) {
         g_ibuf_104[li_28 - 1] = High[li_28 - 1] - 5.0 * Point;
         li_16 = TRUE;
         price_20 = Ask;
      } else {
         if (gi_108 == 2 && gi_112 == 1) {
            g_ibuf_100[li_28 - 1] = Low[li_28 - 1] - 5.0 * Point;
            li_16 = TRUE;
            price_20 = Bid;
         }
      }
      gi_112 = gi_108;
      gd_unused_124 = gd_116;
   }
   if (Alerts && li_16) {
      PlaySound("alert.wav");
      if (gi_112 == 1) MessageBox("Entry point: buy at " + price_20 + "!!", "Entry Point", 0);
      else
         if (gi_112 == 2) MessageBox("Entry point: sell at " + price_20 + "!!", "Entry Point", 0);
      li_16 = FALSE;
   }
   return (0);
}