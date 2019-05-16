//+-------------------------------------------------------------------------------------------+
//|                                                                                           |
//|                                      Solid Trend.mq4                                      |
//|                                                                                           |
//+-------------------------------------------------------------------------------------------+
#property copyright "Copyright @ 2015 traderathome and qFish"
#property link      "email: traderathome@msn.com"

/*---------------------------------------------------------------------------------------------
User Notes:

This indicator is coded to run on MT4 Build 600+.  It displays a 50 EMA moving average (Trend)
using HLC prices.

The solid colored Trend display is intended for use with the PVA Prices indicator and requires
the MT4 price display be "Line chart" with CLR_NONE" as color, and not be set to foreground.
Yes, it obscures MT4 price styles that are not set to foreground, but to set them to forground
interferes with the display of the Trade Levels indicator.  So, for a proper display, be sure
chart Properties/Common tab/Chart on foreground is NOT checked and use the PVA Prices indy.

                                                                   - Traderathome, 08-01-2015
----------------------------------------------------------------------------------------------
Suggested Colors             White Chart        Black Chart        Remarks

Solid Display-
indicator_color1-2           C'217,236,255'     C'034,036,083'     Histo H/L
indicator_color3-4           C'204,230,255'     C'038,043,094'     MA H/L
indicator_color5             C'240,249,255'     C'020,020,020'     Center Area
indicator_color6             C'029,118,226'     C'083,106,200'     Center Line

---------------------------------------------------------------------------------------------*/


//+-------------------------------------------------------------------------------------------+
//| Indicator Global Inputs                                                                   |
//+-------------------------------------------------------------------------------------------+
#property indicator_chart_window
#property indicator_buffers  6

//global external inputs
extern bool     Indicator_On                  = true;
extern color    Trend_Body                    = C'217,236,255';
extern color    Trend_Edges                   = C'204,230,255';
extern color    Center_Area                   = C'240,249,255';
extern color    Center_Line                   = C'029,118,226';

//Global Buffers and Variables
bool            Deinitialized;
int             Chart_Scale,Bar_Width,Bands,cntr,Trend_Period,Trend_Type,
                BarShift,counted_bars,limit;
double          TrendHigh[],TrendLow[],TrendTop[],TrendBot[],TrendCntr1[],TrendCntr2[];              

/*General notes:
MAType  = 0=SMA,1=EMA,2=SMMA,3=LWMA
MAPrice = 0=CLOSE,1=OPEN,2=TrendHigh,3=LOW,4=MEDIAN,5=PP,6=WEIGHT
*/

//+-------------------------------------------------------------------------------------------+
//| Indicator De-initialization                                                               |
//+-------------------------------------------------------------------------------------------+
int deinit()
  {
  return(0);
  }

//+-------------------------------------------------------------------------------------------+
//| Indicator Initialization                                                                  |
//+-------------------------------------------------------------------------------------------+
int init()
  {
  Deinitialized = false;

  //Determine the current chart scale (chart scale number should be 0-5)
  Chart_Scale = ChartScaleGet();

  //Set Bar_Width and Bands per chart zoom selection
      if(Chart_Scale == 0) {Bar_Width = 1; Bands = 1; cntr = 1;}
  else {if(Chart_Scale == 1) {Bar_Width = 2; Bands = 1; cntr = 1;}
  else {if(Chart_Scale == 2) {Bar_Width = 3; Bands = 3; cntr = 5;}
  else {if(Chart_Scale == 3) {Bar_Width = 5; Bands = 7; cntr = 7;}
  else {if(Chart_Scale == 4) {Bar_Width = 9; Bands = 14; cntr = 9;}
  else {if(Chart_Scale == 5) {Bar_Width = 17; Bands = 26; cntr = 11;} }}}}}

  //Trend- set period and type
  Trend_Period = 50; Trend_Type = 1;

  //Indicators
  //Area fill either side of center
  SetIndexBuffer(0, TrendHigh);
  SetIndexStyle(0, DRAW_HISTOGRAM, 0, Bar_Width, Trend_Body);
  SetIndexEmptyValue(0,0);
  SetIndexBuffer(1, TrendLow);
  SetIndexStyle(1, DRAW_HISTOGRAM, 0, Bar_Width, Trend_Body);
  SetIndexEmptyValue(1,0);
  //Area fill top and bottom
  SetIndexBuffer(2, TrendTop);
  SetIndexStyle(2, DRAW_LINE, 0, Bands, Trend_Edges);
  SetIndexEmptyValue(2,0);
  SetIndexBuffer(3, TrendBot);
  SetIndexStyle(3, DRAW_LINE, 0, Bands, Trend_Edges);
  SetIndexEmptyValue(3,0);
  //Center line Area
  SetIndexBuffer(4, TrendCntr1);
  SetIndexStyle(4, DRAW_LINE, 0, cntr, Center_Area);
  SetIndexEmptyValue(4,0);
  //Center line
  SetIndexBuffer(5, TrendCntr2);
  SetIndexStyle(5, DRAW_LINE, 0, 1, Center_Line);
  SetIndexEmptyValue(5,0);

  //Indicator ShortName
  IndicatorShortName ("Solid Trend");

  return(0);
  }

//+-------------------------------------------------------------------------------------------+
//| Indicator Start                                                                           |
//+-------------------------------------------------------------------------------------------+
int start()
  {
  //If indicator is "Off" or chart TF is out of range deinitialize only once, not every tick.
  if(!Indicator_On)
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
  for(int i = limit - 1; i >= 0; i--)
    {    
    BarShift = iBarShift(NULL,NULL,Time[i],true);
    TrendHigh[i]  = iMA(NULL,NULL,Trend_Period,0,Trend_Type,2,BarShift);
    TrendLow[i]   = iMA(NULL,NULL,Trend_Period,0,Trend_Type,3,BarShift);
    TrendTop[i]   = iMA(NULL,NULL,Trend_Period,0,Trend_Type,2,BarShift);
    TrendBot[i]   = iMA(NULL,NULL,Trend_Period,0,Trend_Type,3,BarShift);
    TrendCntr1[i] = iMA(NULL,NULL,Trend_Period,0,Trend_Type,0,BarShift);
    TrendCntr2[i] = iMA(NULL,NULL,Trend_Period,0,Trend_Type,0,BarShift);
    }
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
//| Indicator End                                                                             |
//+-------------------------------------------------------------------------------------------+