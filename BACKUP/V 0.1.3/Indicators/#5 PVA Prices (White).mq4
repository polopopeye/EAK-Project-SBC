//+-------------------------------------------------------------------------------------------+
//|                                                                                           |
//|                                      Candles Suite.mq4                                    |
//|                                                      				                         |
//+-------------------------------------------------------------------------------------------+
#property copyright "Copyright @ 2015 traderathome and qFish"
#property link      "email: traderathome@msn.com"

/*---------------------------------------------------------------------------------------------
User Notes:

This indicator is coded to run on MT4 Build 600+.  It draws PVA (Price-Volume Analysis) bar
and candlestick price charts.

PVA Bars & Candlesticks -
   The PVA bars and PVA candlesticks are used together with PVA volume for easy recognition of
   when special price and volume situations occur.  The special situations, or requirements for
   the colors used are as follows.

   Situation "Climax"
   Bars with volume >= 200% of the average volume of the 10 previous chart TFs, or bars
   where the product of candle spread x candle volume is >= the highest for the 10 previous
   chart time TFs.
   Default Colors:  Bull bars are green and bear bars are red.

   Situation "Volume Rising Above Average"
   Bars with volume >= 150% of the average volume of the 10 previous chart TFs.
   Default Colors:  Bull bars are blue and bear are blue-violet.

   PVA Color Options -
   There are two PVA color options provided by "Color_Custom_Default_12".
     1. Custom:  Use this option for the multi-color PVA display where you can change colors.
        This option is to help those suffering from color blindness or with other reasons for
        needing different colors that better suit them.
     2. Default:  There are no inputs.  The traditional multi-color PVA display is hard coded.
        You can easily return to this display anytime while preserving those changes made to
        the Custom display.

Selecting the Type of PVA Price Display -
   To show PVA bars set "Style_Bars_Candles_12" to "1".  To show PVA candlesticks input "2".
   These bars and candlesticks display on top of the solid color Trend.  A proper display
   requires the MT4 price display be "Line chart" with CLR_NONE" as color, and not be set to
   foreground.  Be sure that chart Properties/Common tab/Chart on foreground is NOT checked!

                                                                    - Traderathome, 08-01-2015
-----------------------------------------------------------------------------------------------
Acknowledgements:
BetterVolume.mq4 - for initial "climax" candle code definition (BetterVolume_v1.4).

----------------------------------------------------------------------------------------------
Suggested Colors            White Chart        Black Chart        Remarks

indicator_color1            C'006,000,079'     C'128,137,153'     Candlewicks Up
indicator_color2            C'006,000,079''    C'128,137,153'     Candlewicks Dn
indicator_color3            C'159,160,162'     C'159,159,177'     Bull STD Candle
indicator_color4            C'106,106,117'     C'106,106,117'     Bear STD Candle
indicator_color5            C'096,096,238'     C'017,136,255'     Bull Rising
indicator_color6            C'187,050,233'     C'184,051,255'     Bear Rising
indicator_color7            C'000,166,100'     C'031,192,071'     Bull Climax
indicator_color8            C'214,012,083'     C'224,001,006'     Bear Climax

Note: Suggested colors coincide with the colors of the PVA Volumes indicator.
---------------------------------------------------------------------------------------------*/


//+-------------------------------------------------------------------------------------------+
//| Indicator Global Inputs                                                                   |
//+-------------------------------------------------------------------------------------------+
#property indicator_chart_window
#property indicator_buffers 8

//Global External Inputs
extern string   Part_1                        = "Main Settings:";
extern bool     Indicator_On                  = true;
extern bool     Price_Candles_vs_Bars         = true;
extern bool     Color_Default_vs_Custom       = true;

extern string   __                            = "";
extern string   Part_2                        = "Custom Colors:";
extern color    Custom_Wicks                  = C'006,000,079';
extern color    Custom_Bull                   = C'159,160,162';
extern color    Custom_Bear                   = C'106,106,117';
extern color    Custom_Bull_Rising            = C'096,096,238';
extern color    Custom_Bear_Rising            = C'187,050,233';
extern color    Custom_Bull_Climax            = C'000,166,100';
extern color    Custom_Bear_Climax            = C'214,012,083';

//Global Buffers and Variables
bool            Deinitialized;
color           Bull_Wick,Bear_Wick,Bull_Candle,Bear_Candle,
                Bull_Rising,Bear_Rising,Bull_Climax,Bear_Climax;
double          Bar1[],Bar2[],Candle1[],Candle2[],bodyHigh,bodyLow,
                RisingBull[],RisingBear[],ClimaxBull[],ClimaxBear[],
                av,Range,Value2,HiValue2,tempv2,high,low,open,close;
int             Chart_Scale,Bar_Width,va,i,j,counted_bars,limit;

//Default PVA Colors
color           PVA_Normal_Wick  = C'006,000,079';
color           PVA_Normal_Bull  = C'159,160,162';
color           PVA_Normal_Bear  = C'106,106,117';
color           PVA_Bull_Rising  = C'096,096,238';
color           PVA_Bear_Rising  = C'187,050,233';
color           PVA_Bull_Climax  = C'000,166,100';
color           PVA_Bear_Climax  = C'214,012,083';

//+-------------------------------------------------------------------------------------------+
//| Custom indicator deinitialization function                                                |
//+-------------------------------------------------------------------------------------------+
int deinit()
  {
  return(0);
  }

//+-------------------------------------------------------------------------------------------+
//| Custom indicator initialization function                                                  |
//+-------------------------------------------------------------------------------------------+
int init()
  {
  Deinitialized = false;

  //Determine the current chart scale (chart scale number should be 0-5)
  Chart_Scale = ChartScaleGet();

  //Set bar widths
        if(Chart_Scale == 0) {Bar_Width = 1;}
  else {if(Chart_Scale == 1) {Bar_Width = 2;}
  else {if(Chart_Scale == 2) {Bar_Width = 2;}
  else {if(Chart_Scale == 3) {Bar_Width = 3;}
  else {if(Chart_Scale == 4) {Bar_Width = 6;}
  else {Bar_Width = 13;} }}}}

  //Colors Selection for PVA
  if(Color_Default_vs_Custom)
    {
    Bull_Wick   = PVA_Normal_Wick;
    Bear_Wick   = PVA_Normal_Wick;
    Bull_Candle = PVA_Normal_Bull;
    Bear_Candle = PVA_Normal_Bear;
    Bull_Rising = PVA_Bull_Rising;
    Bear_Rising = PVA_Bear_Rising;
    Bull_Climax = PVA_Bull_Climax;
    Bear_Climax = PVA_Bear_Climax;
    }
  else
    {
    Bull_Wick   = Custom_Wicks;
    Bear_Wick   = Custom_Wicks;
    Bull_Candle = Custom_Bull;
    Bear_Candle = Custom_Bear;
    Bull_Rising = Custom_Bull_Rising;
    Bear_Rising = Custom_Bear_Rising;
    Bull_Climax = Custom_Bull_Climax;
    Bear_Climax = Custom_Bear_Climax;
    }

  //Indicators
  //Wicks
  SetIndexBuffer(0,Bar1);
  SetIndexStyle(0,DRAW_HISTOGRAM, 0, 1, Bull_Wick);
  SetIndexBuffer(1,Bar2);
  SetIndexStyle(1,DRAW_HISTOGRAM, 0, 1, Bear_Wick);
  if(Price_Candles_vs_Bars)
    {
    //Normal Bodies
    SetIndexBuffer(2,Candle1);
    SetIndexStyle(2,DRAW_HISTOGRAM, 0, Bar_Width, Bull_Candle);
    SetIndexBuffer(3,Candle2);
    SetIndexStyle(3,DRAW_HISTOGRAM, 0, Bar_Width, Bear_Candle);
    }
  //PVA Rising Volume Bodies
  SetIndexBuffer(4,RisingBull);
  SetIndexStyle(4,DRAW_HISTOGRAM, 0, Bar_Width, Bull_Rising);
  SetIndexBuffer(5,RisingBear);
  SetIndexStyle(5,DRAW_HISTOGRAM, 0, Bar_Width, Bear_Rising);
  //PVA Climax Volume Bodies
  SetIndexBuffer(6,ClimaxBull);
  SetIndexStyle(6,DRAW_HISTOGRAM, 0, Bar_Width, Bull_Climax);
  SetIndexBuffer(7,ClimaxBear);
  SetIndexStyle(7,DRAW_HISTOGRAM, 0, Bar_Width, Bear_Climax);  

  //Indicator ShortName
  IndicatorShortName("PVA Prices");

  return(0);
  }

//+-------------------------------------------------------------------------------------------+
//| Custom indicator iteration function                                                       |
//+-------------------------------------------------------------------------------------------+
int start()
  {
  //If Indicator is "Off" deinitialize only once, not every tick
  if (!Indicator_On)
    {
    if (!Deinitialized) {deinit(); Deinitialized = true;}
    return(0);
    }

  //Confirm range of chart bars for calculations
  //check for possible errors
  counted_bars = IndicatorCounted();
  if(counted_bars < 0)  return(-1);
  //last counted bar will be recounted
  if(counted_bars > 0) counted_bars--;
  limit = Bars - counted_bars;

  //Begin the loop of calculations for the range of chart bars.
  for(i = limit - 1; i >= 0; i--)
    {
    //Define standard candle bodies & wicks
	 high    = iHigh(NULL,NULL,i);
    low     = iLow(NULL,NULL,i);
	 open    = iOpen(NULL,NULL,i);
	 close   = iClose(NULL,NULL,i);
	 bodyHigh= MathMax(open,close);
	 bodyLow = MathMin(open,close);
	 if(close>open)
		{
	   Bar1[i] = high;
	   Bar2[i] = low;
	   Candle1[i] = bodyHigh;
	   Candle2[i] = bodyLow;
		}
	 else if(close<open)
		{
	 	Bar1[i] = low;
		Bar2[i] = high;
		Candle1[i] = bodyLow;
		Candle2[i] = bodyHigh;
		}
	 else //(close==open)
	   {
		Bar1[i] = low;
		Bar2[i] = high;
		Candle1[i] = close;
		Candle2[i] = open-0.000001;
      }

    //Clear buffers
    RisingBull[i] = 0;
    RisingBear[i] = 0;
    ClimaxBull[i] = 0;
    ClimaxBear[i] = 0;
    av            = 0;
    va            = 0;

    //Rising Volume
    for(j = i+1; j <= i+10; j++) {av = av + Volume[j];}
    av = av / 10;

    //Climax Volume
    Range = (High[i]-Low[i]);
    Value2 = Volume[i]*Range;
    HiValue2 = 0;
    for(j = i+1; j <= i+10; j++)
      {
      tempv2 = Volume[j]*((High[j]-Low[j]));
      if (tempv2 >= HiValue2) {HiValue2 = tempv2;}
      }
    if((Value2 >= HiValue2) || (Volume[i] >= av * 2)) {va = 1;}

    //Rising Volume
    if(va == 0)
      {
      if(Volume[i] >= av * 1.5) {va= 2;}
      }

    //Apply Correct Color to PVA Candle
    if (va==1)
      {
      ClimaxBull[i]=iClose(NULL,NULL,i);
      ClimaxBear[i]=iOpen(NULL,NULL,i);
      if(iClose(NULL,NULL,i) == iOpen(NULL,NULL,i)) {ClimaxBear[i]=iOpen(NULL,NULL,i)+0.000001;}
      }
    else if (va==2)
      {
      RisingBull[i]=iClose(NULL,NULL,i);
      RisingBear[i]=iOpen(NULL,NULL,i);
      if(iClose(NULL,NULL,i) == iOpen(NULL,NULL,i)) {RisingBear[i]=iOpen(NULL,NULL,i)+0.000001;}
      }
  }//End "i" loop

  return(0);
  }

//+-------------------------------------------------------------------------------------------+
//| Subroutine:  Set up to get the chart scale number                                         |
//+-------------------------------------------------------------------------------------------+
void OnChartEvent(const int id, const long &lparam, const double &dparam, const string &sparam)
  {
  Chart_Scale = ChartScaleGet();
  init();
  }

//+-------------------------------------------------------------------------------------------+
//| Subroutine:  Get the chart scale number                                                   |
//+-------------------------------------------------------------------------------------------+
int ChartScaleGet()
  {
  long result = -1;
  ChartGetInteger(0,CHART_SCALE,0,result);
  return((int)result);
  }

//+-------------------------------------------------------------------------------------------+
//|Custom indicator end                                                                       |
//+-------------------------------------------------------------------------------------------+
         