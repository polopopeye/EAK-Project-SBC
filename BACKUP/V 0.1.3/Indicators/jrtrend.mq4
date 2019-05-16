//+------------------------------------------------------------------+
//| 4Hour Vegas Model - Weekly Chart Direction Calculator            |
//|                                                           Spiggy |
//|                                                                  |
//+------------------------------------------------------------------+
#property copyright "Jrich3"
#property link      ""

#property indicator_separate_window
//#property indicator_buffers 4
#property indicator_buffers 6
#property indicator_color1 Yellow
#property indicator_color2 DarkGreen
#property indicator_color3 Maroon

//#property indicator_color4 Red
#property indicator_color5 Lime
#property indicator_color6 Red

//---- input parameters

//---- buffers
double ExtMapBuffer1[];
double ExtMapBuffer2[];
double ExtMapBuffer3[];

double ExtMapBuffer4[];
double ExtMapBuffer5[];

//+------------------------------------------------------------------+
//| Custom indicator initialization function                         |
//+------------------------------------------------------------------+
int init()
  {
//---- indicators
   SetIndexStyle(0,DRAW_LINE);
   SetIndexBuffer(0,ExtMapBuffer1);
   SetIndexStyle(1,DRAW_HISTOGRAM);
   SetIndexBuffer(1,ExtMapBuffer2);
   SetIndexStyle(2,DRAW_HISTOGRAM);
   SetIndexBuffer(2,ExtMapBuffer3);
   
      
   SetIndexStyle(4,DRAW_LINE);
   //SetIndexStyle(4,DRAW_ARROW,STYLE_SOLID,1);
   SetIndexBuffer(4,ExtMapBuffer4);
   SetIndexArrow(4,159);
   
   SetIndexStyle(5,DRAW_LINE);
   //SetIndexStyle(5,DRAW_ARROW,STYLE_SOLID,1);
   SetIndexBuffer(5,ExtMapBuffer5);
   SetIndexArrow(5,159);

//----
   return(0);
  }
//+------------------------------------------------------------------+
//| Custor indicator deinitialization function                       |
//+------------------------------------------------------------------+
int deinit()
  {
//---- 
   
//----
   return(0);
  }
//+------------------------------------------------------------------+
//| Custom indicator iteration function                              |
//+------------------------------------------------------------------+
int start()
{
  int    limit;
  int    i;
  int    counted_bars=IndicatorCounted();
  double EMA21;
  double SMA5;
  double EMA21Prev;
  double SMA5Prev;
  string ValueIndex;
  string Direction;
  string KeyValue;
   
  // Always prepare all of the information for the other indicators
  if(counted_bars<0) return(-1);

  if(counted_bars>0) counted_bars--;
  limit=Bars-counted_bars;
  
  //---- main loop
  for(i=limit; i>=0; i--)
  {
    //---- Calculate the current weekly trend
    EMA21=iMA(NULL,0,21,0,MODE_EMA,PRICE_MEDIAN,i);
    SMA5 =iMA(NULL,0,5,0,MODE_SMA,PRICE_MEDIAN,i);
         
    //---- Calculate the previous weekly trend
    EMA21Prev=iMA(NULL,0,21,0,MODE_EMA,PRICE_MEDIAN,i+1);
    SMA5Prev =iMA(NULL,0,5,0,MODE_SMA,PRICE_MEDIAN,i+1);


    // Calculate the difference of the MAs
    ExtMapBuffer1[i] = SMA5-EMA21;

    // Calculate the difference of the MAs
    if (((SMA5-EMA21) - (SMA5Prev-EMA21Prev)) > 0.0 )
    {
      ExtMapBuffer2[i] = (SMA5-EMA21) - (SMA5Prev-EMA21Prev);
      ExtMapBuffer3[i] = 0.0;
      Direction = "UP";
    }
    
    if (((SMA5-EMA21) - (SMA5Prev-EMA21Prev)) < 0.0 )
    {
      ExtMapBuffer2[i] = 0.0;
      ExtMapBuffer3[i] = (SMA5-EMA21) - (SMA5Prev-EMA21Prev);
      Direction = "DOWN";
    }
    // Calculate the start of the week and publish the value in a global variable
    // Publish this with the previous Sunday as the index
    ValueIndex = TimeToStr(Time[i]-TimeDayOfWeek(Time[i]),TIME_DATE);
    KeyValue = Symbol() + "-ThisWeekDirection-" + ValueIndex;
    if (! GlobalVariableCheck(KeyValue))
    GlobalVariableSet(KeyValue, ((SMA5-EMA21) - (SMA5Prev-EMA21Prev)));
    Print("Key: " + KeyValue + " = " + DoubleToStr(((SMA5-EMA21) - (SMA5Prev-EMA21Prev)),4));
    
    customMethod(SMA5, EMA21, i, Direction );
    
  }

//   Comment("Line = SMA5-EMA21","\n","Histogram = Now - Previous");
         
   return(0);
  }
  
void customMethod(double SMA5, double EMA21, int index, string Direction)
{
   double difference = SMA5-EMA21;
   if (Direction == "DOWN")
   {
      ExtMapBuffer4[index] = EMPTY_VALUE;
      ExtMapBuffer5[index] = difference;
   }
   if (Direction == "UP")
   {
      ExtMapBuffer4[index] = difference;
      ExtMapBuffer5[index] = EMPTY_VALUE;
   }
   //EMPTY_VALUE
}
//+------------------------------------------------------------------+