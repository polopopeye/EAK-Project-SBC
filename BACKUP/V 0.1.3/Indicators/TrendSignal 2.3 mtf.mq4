//------------------------------------------------------------------
//
//------------------------------------------------------------------
#property copyright "www.forex-station.com"
#property link      "www.forex-station.com"

#property indicator_chart_window
#property indicator_buffers 2
#property indicator_color1 DarkOrange
#property indicator_color2 LightBlue
#property indicator_width1 1
#property indicator_width2 1

//
//
//
//
//

extern ENUM_TIMEFRAMES TimeFrame = PERIOD_CURRENT;
extern double x1                 = 67;
extern double x2                 = 33;
extern int    WprPrice           = 0; 
extern int    Risk               = 3;
extern double ArrowsGap          = 1.0;
extern bool   ArrowOnFirst       = true;         // Arrow on first bars

extern bool   alertsOn           = false;
extern bool   alertsOnCurrent    = true;
extern bool   alertsMessage      = true;
extern bool   alertsSound        = false;
extern bool   alertsEmail        = false;
extern bool   alertsNotify       = false;
//
//
//
//
//

double arrDn[];
double arrUp[];
double wpr[];
double price[];
string indicatorFileName;
bool   returnBars;

//------------------------------------------------------------------
//
//------------------------------------------------------------------
//
//
//
//
//

int init()
{
   IndicatorBuffers(4);
   SetIndexBuffer(0,arrDn); SetIndexStyle(0,DRAW_ARROW); SetIndexArrow(0,234);
   SetIndexBuffer(1,arrUp); SetIndexStyle(1,DRAW_ARROW); SetIndexArrow(1,233);
   SetIndexBuffer(2,wpr);
   SetIndexBuffer(3,price);
      indicatorFileName = WindowExpertName();
      returnBars        = TimeFrame == -99;
      TimeFrame         = MathMax(TimeFrame,_Period);
   return(0);
}

//
//
//
//
//

int start()
{
   int counted_bars=IndicatorCounted();
      if (counted_bars<0) return(-1);
      if(counted_bars>0) counted_bars--;
         int limit = MathMin(Bars-counted_bars,Bars-1);
         if (returnBars) { arrDn[0] = limit+1; return(0); }
         if (TimeFrame!=Period())
         {
            limit = (int)MathMax(limit,MathMin(Bars-1,iCustom(NULL,TimeFrame,indicatorFileName,-99,0,0)*TimeFrame/Period()));
            for (int i=limit; i>=0; i--)
            {
               int y = iBarShift(NULL,TimeFrame,Time[i]);
               int x = y;
               if (ArrowOnFirst)
                     {  if (i<Bars-1) x = iBarShift(NULL,TimeFrame,Time[i+1]);               }
               else  {  if (i>0)      x = iBarShift(NULL,TimeFrame,Time[i-1]); else x = -1;  }
               arrDn[i] = EMPTY_VALUE;
               arrUp[i] = EMPTY_VALUE;
               if (y!=x)
               {
                  arrDn[i] = iCustom(NULL,TimeFrame,indicatorFileName,PERIOD_CURRENT,x1,x2,WprPrice,Risk,ArrowsGap,alertsOn,alertsOnCurrent,alertsMessage,alertsSound,alertsEmail,alertsNotify,0,y);
                  arrUp[i] = iCustom(NULL,TimeFrame,indicatorFileName,PERIOD_CURRENT,x1,x2,WprPrice,Risk,ArrowsGap,alertsOn,alertsOnCurrent,alertsMessage,alertsSound,alertsEmail,alertsNotify,1,y);
               }    
            }
            return(0);                  
         }
         
         //
         //
         //
         //
         //

   //
   //
   //
   //
   //

   for (i=limit; i>=0 ; i--)
   {
      int    period = 3 + Risk * 2;
      double range  = 0; for (int k = 0; k < 10; k++) range += High[i+k] - Low[i+k]; range /= 10.0;
      bool   found1 = false; for (k = 0; k < 6 && !found1; k++) found1 = (MathAbs(Open[i+k]    - Close[i+k+1])>= range * 2.0);
      bool   found2 = false; for (k = 0; k < 9 && !found2; k++) found2 = (MathAbs(Close[i+k+3] - Close[i+k])  >= range * 4.6);
             if (found1) period = 3;
             if (found2) period = 4;
             price[i]    = getPrice(WprPrice,i); 
             double hi   = High[iHighest(NULL,0, MODE_HIGH,period,i)];
             double lo   =  Low[iLowest(NULL, 0, MODE_LOW, period,i)];
             if (hi!=lo)      
                  wpr[i] = 100+(-100)*(hi - price[i]) / (hi - lo);
             else wpr[i] = 0;   

      //
      //
      //
      //
      //
               
      arrDn[i] = EMPTY_VALUE;
      arrUp[i] = EMPTY_VALUE;
      if (wpr[i]<x2-Risk) { for (k=1; i+k<Bars && wpr[i+k]>=x2-Risk && wpr[i+k]<=x1+Risk;) k++; if (wpr[i+k]>x1+Risk) arrDn[i] = High[i]+range*ArrowsGap; }
      if (wpr[i]>x1+Risk) { for (k=1; i+k<Bars && wpr[i+k]>=x2-Risk && wpr[i+k]<=x1+Risk;) k++; if (wpr[i+k]<x2-Risk) arrUp[i] = Low[i] -range*ArrowsGap; }
   }
manageAlerts();   
return(0);           
}

//-------------------------------------------------------------------
//                                                                  
//-------------------------------------------------------------------
//
//
//
//
//

void manageAlerts()
{
   if (alertsOn)
   {
      if (alertsOnCurrent)
           int whichBar = 0;
      else     whichBar = 1;
      if (arrDn[whichBar] != EMPTY_VALUE || arrUp[whichBar] != EMPTY_VALUE)
      {
         if (arrUp[whichBar] != EMPTY_VALUE) doAlert(whichBar,"up");
         if (arrDn[whichBar] != EMPTY_VALUE) doAlert(whichBar,"down");
      }
   }
}

//
//
//
//
//

void doAlert(int forBar, string doWhat)
{
   static string   previousAlert="nothing";
   static datetime previousTime;
   string message;
   
   if (previousAlert != doWhat || previousTime != Time[forBar]) {
       previousAlert  = doWhat;
       previousTime   = Time[forBar];

       //
       //
       //
       //
       //

       message =  StringConcatenate(Symbol()," at ",TimeToStr(TimeLocal(),TIME_SECONDS)," Trend signal trend changed to ",doWhat);
          if (alertsMessage) Alert(message);
          if (alertsNotify)  SendNotification(message);
          if (alertsEmail)   SendMail(StringConcatenate(Symbol()," Trend Signal"),message);
          if (alertsSound)   PlaySound("alert2.wav");
   }
}

//+------------------------------------------------------------------
//|                                                                  
//+------------------------------------------------------------------
//
//
//
//
//
//

double getPrice(int type, int i)
{
   switch (type)
   {
      case 7:     return((Open[i]+Close[i])/2.0);
      case 8:     return((Open[i]+High[i]+Low[i]+Close[i])/4.0);
      default :   return(iMA(NULL,0,1,0,MODE_SMA,type,i));
   }      
}