//------------------------------------------------------------------
#property copyright "� mladen, 2016, MetaQuotes Software Corp."
#property link      "www.forex-tsd.com, www.mql5.com"
//------------------------------------------------------------------
#property indicator_chart_window
#property indicator_buffers  4
#property indicator_color1   clrLimeGreen
#property indicator_color2   clrOrange
#property indicator_color3   clrOrange
#property indicator_color4   clrRed
#property indicator_width1   3
#property indicator_width2   3
#property indicator_width3   3
#property indicator_style4   STYLE_DOT
#property strict

//
//
//
//
//

enum enPrices
{
   pr_close,      // Close
   pr_open,       // Open
   pr_high,       // High
   pr_low,        // Low
   pr_median,     // Median
   pr_typical,    // Typical
   pr_weighted,   // Weighted
   pr_average,    // Average (high+low+open+close)/4
   pr_medianb,    // Average median body (open+close)/2
   pr_tbiased,    // Trend biased price
   pr_tbiased2,   // Trend biased (extreme) price
   pr_haclose,    // Heiken ashi close
   pr_haopen ,    // Heiken ashi open
   pr_hahigh,     // Heiken ashi high
   pr_halow,      // Heiken ashi low
   pr_hamedian,   // Heiken ashi median
   pr_hatypical,  // Heiken ashi typical
   pr_haweighted, // Heiken ashi weighted
   pr_haaverage,  // Heiken ashi average
   pr_hamedianb,  // Heiken ashi median body
   pr_hatbiased,  // Heiken ashi trend biased price
   pr_hatbiased2  // Heiken ashi trend biased (extreme) price
};
extern double   estimatePeriod  = 14.33;     // Estimate period
extern double   trendPeriod     = 10;        // Trend period
extern enPrices Price           = pr_close;  // Price
extern int      ForecastBars    = 15;        // Forecast bars (horizon)
input bool      AlertsOn        = false;     // Turn alerts on?
input bool      AlertsOnCurrent = true;      // Alert on current bar?
input bool      AlertsMessage   = true;      // Display messageas on alerts?
input bool      AlertsSound     = false;     // Play sound on alerts?
input bool      AlertsEmail     = false;     // Send email on alerts?
input bool      AlertsNotify    = false;     // Send push notification on alerts?

double emaBuffer[],emaBufferda[],emaBufferdb[],wrkBuffer[],forecast[],slope[];

//------------------------------------------------------------------
//
//------------------------------------------------------------------
//
//
//
//
//

int OnInit()
{
   IndicatorBuffers(6);
   SetIndexBuffer(0,emaBuffer);
   SetIndexBuffer(1,emaBufferda);
   SetIndexBuffer(2,emaBufferdb);
   SetIndexBuffer(3,forecast); SetIndexShift(3,ForecastBars); 
   SetIndexBuffer(4,wrkBuffer);
   SetIndexBuffer(5,slope);
      estimatePeriod = MathMax(estimatePeriod,1);
      trendPeriod    = MathMax(trendPeriod,1);
      IndicatorShortName("Holt's des ("+DoubleToStr(estimatePeriod,2)+","+DoubleToStr(trendPeriod,2)+")");
   return(0);
}
void OnDeinit(const int reason) { }
int OnCalculate(const int rates_total,
                const int prev_calculated,
                const datetime& time[],
                const double& open[],
                const double& high[],
                const double& low[],
                const double& close[],
                const long& tick_volume[],
                const long& volume[],
                const int& spread[])
{
   int counted_bars = prev_calculated;
      if(counted_bars < 0) return(-1);
      if(counted_bars > 0) counted_bars--;
           int limit=MathMin(rates_total-counted_bars,rates_total-1);
   
   //
   //
   //
   //
   //

   double alpha=2.0 /(1.0+estimatePeriod),beta=2.0 /(1.0+trendPeriod);
   if (slope[limit]==2) CleanPoint(limit,emaBufferda,emaBufferdb);
   for (int i=limit; i>=0 && !_StopFlag; i--)
   {
      double price = getPrice(Price,open,close,high,low,i);
         emaBuffer[i]   = (i<Bars-1) ? alpha*price+(1-alpha)*(emaBuffer[i+1]+wrkBuffer[i+1])      : price;
         wrkBuffer[i]   = (i<Bars-1) ? beta*(emaBuffer[i]-emaBuffer[i+1])+(1-beta)*wrkBuffer[i+1] : 0;
         emaBufferda[i] = EMPTY_VALUE;
         emaBufferdb[i] = EMPTY_VALUE;
         slope[i]       = (i<Bars-1) ? (emaBuffer[i]>emaBuffer[i+1]) ? 1 : (emaBuffer[i]<emaBuffer[i+1]) ? 2 : slope[i+1] : 0;
            if (slope[i]==2) PlotPoint(i,emaBufferda,emaBufferdb,emaBuffer);
   }
   forecast[ForecastBars]=emaBuffer[0]; for (int i = ForecastBars-1; i>=0; i--) forecast[i] = emaBuffer[0]+(ForecastBars-i)*wrkBuffer[0];
   manageAlerts(time,slope);      
   
   //
   //
   //
   //
   //
   
   SetIndexDrawBegin(3,Bars-ForecastBars-1);
   return(0);
}


//------------------------------------------------------------------
//
//------------------------------------------------------------------
//
//
//
//
//

void manageAlerts(const datetime& time[], double& ttrend[])
{
   if (!AlertsOn) return;
      int whichBar = 0; if (!AlertsOnCurrent) whichBar = 1; datetime time1 = time[0];
      if (ttrend[whichBar] != ttrend[whichBar+1])
      {
         if (ttrend[whichBar] == 1) doAlert(time1,"up");
         if (ttrend[whichBar] == 2) doAlert(time1,"down");
      }         
}   

//
//
//
//
//

void doAlert(datetime forTime, string doWhat)
{
   static string   previousAlert="nothing";
   static datetime previousTime;
   string message;
   
   if (previousAlert != doWhat || previousTime != forTime) 
   {
      previousAlert  = doWhat;
      previousTime   = forTime;

      //
      //
      //
      //
      //

      message = _Symbol+" at "+TimeToString(TimeLocal(),TIME_SECONDS)+" Holt's double exponential smoothing state changed to "+doWhat;
         if (AlertsMessage) Alert(message);
         if (AlertsEmail)   SendMail(_Symbol+" Holt's double exponential smoothing",message);
         if (AlertsNotify)  SendNotification(message);
         if (AlertsSound)   PlaySound("alert2.wav");
   }
}

//------------------------------------------------------------------
//
//------------------------------------------------------------------
//
//
//
//
//
//

#define _priceInstances 1
#define _priceSize 4
double workHa[][_priceInstances*_priceSize];
double getPrice(int tprice, const double& open[], const double& close[], const double& high[], const double& low[], int i, int instanceNo=0)
{
  if (tprice>=pr_haclose)
   {
      if (ArrayRange(workHa,0)!= Bars) ArrayResize(workHa,Bars); instanceNo*=_priceSize; int r = Bars-i-1;
         
         //
         //
         //
         //
         //
         
         double haOpen;
         if (r>0)
                haOpen  = (workHa[r-1][instanceNo+2] + workHa[r-1][instanceNo+3])/2.0;
         else   haOpen  = (open[i]+close[i])/2;
         double haClose = (open[i] + high[i] + low[i] + close[i]) / 4.0;
         double haHigh  = MathMax(high[i], MathMax(haOpen,haClose));
         double haLow   = MathMin(low[i] , MathMin(haOpen,haClose));

         if(haOpen  <haClose) { workHa[r][instanceNo+0] = haLow;  workHa[r][instanceNo+1] = haHigh; } 
         else                 { workHa[r][instanceNo+0] = haHigh; workHa[r][instanceNo+1] = haLow;  } 
                                workHa[r][instanceNo+2] = haOpen;
                                workHa[r][instanceNo+3] = haClose;
         //
         //
         //
         //
         //
         
         switch (tprice)
         {
            case pr_haclose:     return(haClose);
            case pr_haopen:      return(haOpen);
            case pr_hahigh:      return(haHigh);
            case pr_halow:       return(haLow);
            case pr_hamedian:    return((haHigh+haLow)/2.0);
            case pr_hamedianb:   return((haOpen+haClose)/2.0);
            case pr_hatypical:   return((haHigh+haLow+haClose)/3.0);
            case pr_haweighted:  return((haHigh+haLow+haClose+haClose)/4.0);
            case pr_haaverage:   return((haHigh+haLow+haClose+haOpen)/4.0);
            case pr_hatbiased:
               if (haClose>haOpen)
                     return((haHigh+haClose)/2.0);
               else  return((haLow+haClose)/2.0);        
            case pr_hatbiased2:
               if (haClose>haOpen)  return(haHigh);
               if (haClose<haOpen)  return(haLow);
                                    return(haClose);        
         }
   }
   
   //
   //
   //
   //
   //
   
   switch (tprice)
   {
      case pr_close:     return(close[i]);
      case pr_open:      return(open[i]);
      case pr_high:      return(high[i]);
      case pr_low:       return(low[i]);
      case pr_median:    return((high[i]+low[i])/2.0);
      case pr_medianb:   return((open[i]+close[i])/2.0);
      case pr_typical:   return((high[i]+low[i]+close[i])/3.0);
      case pr_weighted:  return((high[i]+low[i]+close[i]+close[i])/4.0);
      case pr_average:   return((high[i]+low[i]+close[i]+open[i])/4.0);
      case pr_tbiased:   
               if (close[i]>open[i])
                     return((high[i]+close[i])/2.0);
               else  return((low[i]+close[i])/2.0);        
      case pr_tbiased2:   
               if (close[i]>open[i]) return(high[i]);
               if (close[i]<open[i]) return(low[i]);
                                     return(close[i]);        
   }
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

void CleanPoint(int i,double& first[],double& second[])
{
   if (i>=Bars-3) return;
   if ((second[i]  != EMPTY_VALUE) && (second[i+1] != EMPTY_VALUE))
        second[i+1] = EMPTY_VALUE;
   else
      if ((first[i] != EMPTY_VALUE) && (first[i+1] != EMPTY_VALUE) && (first[i+2] == EMPTY_VALUE))
          first[i+1] = EMPTY_VALUE;
}

void PlotPoint(int i,double& first[],double& second[],double& from[])
{
   if (i>=Bars-2) return;
   if (first[i+1] == EMPTY_VALUE)
      if (first[i+2] == EMPTY_VALUE) 
            { first[i]  = from[i];  first[i+1]  = from[i+1]; second[i] = EMPTY_VALUE; }
      else  { second[i] =  from[i]; second[i+1] = from[i+1]; first[i]  = EMPTY_VALUE; }
   else     { first[i]  = from[i];                           second[i] = EMPTY_VALUE; }
}