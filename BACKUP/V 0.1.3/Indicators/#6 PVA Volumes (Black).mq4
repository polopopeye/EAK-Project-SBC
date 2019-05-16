//+-------------------------------------------------------------------------------------------+
//|                                                                                           |
//|                                      Volumes Suite.mq4                                    |
//|                                                                                           |
//+-------------------------------------------------------------------------------------------+
#property copyright "Copyright © 2015 traderathome and qFish"
#property link      "email:   traderathome@msn.com"

/*---------------------------------------------------------------------------------------------
User Notes:

This indicator is coded to run on MT4 Builds 600+.  It draws a PVA (Price-Volume Analysis)
volumes histogram in the first chart subwindow.  An alert option signals when a "Climax"
situation exists.  Specific details follow.

The PVA Volumes Histogram -
   PVA volume is used together with PVA bars and PVA candlesticks for easy recognition of
   when special price and volume situations occur.  The special situations, or requirements
   for the the colors used are as follows.

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

The Alert -
   This indicator includes a sound-text alert that triggers once per TF at the first
   qualification of the TF bar as a "Climax" situation.  Set "Alert_On" to "true"
   to activate the alert.  Enter your "Broker_Name_In_Alert" to avoid confusion if
   simultaneously using multiple platforms.  If also using the PVA Candles indicator,
   be sure the two alert inputs in that indicator are set to "false".

                                                                    - Traderathome, 08-01-2015
-----------------------------------------------------------------------------------------------
Acknowledgements:
BetterVolume.mq4 - for initial "climax" candle code definition (BetterVolume_v1.4).

----------------------------------------------------------------------------------------------
Suggested Colors            White Chart        Black Chart        Remarks

indicator_color1            White              C'010,010,010'     Background
indicator_color2            C'119,146,179'     C'102,099,163'     Normal Thin
indicator_color2            C'207,207,207'     C'048,055,118'     Normal Wide
indicator_color3            C'096,096,238'     C'017,136,255'     Bull Rising
indicator_color4            C'187,050,233'     C'184,051,255'     Bear Rising
indicator_color5            C'000,166,100'     C'031,192,071'     Bull Climax
indicator_color6            C'214,012,083'     C'224,001,006'     Bear Climax

Note: Suggested colors coincide with the colors of the PVA Prices indicator.
---------------------------------------------------------------------------------------------*/


//+-------------------------------------------------------------------------------------------+
//| Indicator Global Inputs                                                                   |                                                  
//+-------------------------------------------------------------------------------------------+
#property indicator_separate_window
#property indicator_buffers 6
#property indicator_minimum 0

//Global External Inputs
extern string   Part_1                        = "Main Settings:";
extern bool     Indicator_On                  = true;
extern bool     Color_Default_vs_Custom       = true;
extern bool     Normal_Bars_Thin_vs_Wide      = true;
extern bool     Alert_On                      = true;
extern string   Broker_Name_In_Alert          = "";
extern color    Chart_Background_Color        = C'010,010,010';

extern string   __                            = "";
extern string   Part_2                        = "Custom Colors:";
extern color    Custom_Normal_Thin_Bar        = C'102,099,163';
extern color    Custom_Normal_Wide_Bar        = C'048,055,118';
extern color    Custom_Bull_Rising            = C'017,136,255';
extern color    Custom_Bear_Rising            = C'184,051,255';
extern color    Custom_Bull_Climax            = C'031,192,071';
extern color    Custom_Bear_Climax            = C'224,001,006';


//Global Buffers and Variables
bool            Deinitialized;
color           Normal_Bar,Bull_Rising,Bear_Rising,Bull_Climax,Bear_Climax;
int             Chart_Scale,i,j,Bar_Width,counted_bars,limit,va;
double          Phantom[],Normal[],RisingBull[],RisingBear[],ClimaxBull[],ClimaxBear[],
                av,Range,Value2,HiValue2,tempv2;             
string          ShortName;

//Default PVA Colors
color           PVA_Normal_Thin_Bar = C'102,099,163';
color           PVA_Normal_Wide_Bar = C'048,055,118';
color           PVA_Bull_Rising  = C'017,136,255';
color           PVA_Bear_Rising  = C'184,051,255';
color           PVA_Bull_Climax  = C'031,192,071';
color           PVA_Bear_Climax  = C'224,001,006';

//Alert
bool            Alert_Allowed;
static bool     allow = true;
static bool     disallow = false;

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
    if(Normal_Bars_Thin_vs_Wide) {Normal_Bar = PVA_Normal_Thin_Bar;}
    else {Normal_Bar = PVA_Normal_Wide_Bar;}
    Bull_Rising = PVA_Bull_Rising;
    Bear_Rising = PVA_Bear_Rising;
    Bull_Climax = PVA_Bull_Climax;
    Bear_Climax = PVA_Bear_Climax;    
    }
  else
    {
    if(Normal_Bars_Thin_vs_Wide) {Normal_Bar = Custom_Normal_Thin_Bar;}
    else {Normal_Bar = Custom_Normal_Wide_Bar;}
    Bull_Rising = Custom_Bull_Rising;
    Bear_Rising = Custom_Bear_Rising;
    Bull_Climax = Custom_Bull_Climax;
    Bear_Climax = Custom_Bear_Climax;
    }

  //Indicators 
  //Phantom Volume
  SetIndexBuffer(0,Phantom);
  SetIndexStyle(0,DRAW_HISTOGRAM,0,Bar_Width,Chart_Background_Color);
  //Normal Volume Bars
  SetIndexBuffer(1,Normal);
  if(Normal_Bars_Thin_vs_Wide) 
    {SetIndexStyle(1,DRAW_HISTOGRAM, 0, 1, Normal_Bar);}
  else 
    {SetIndexStyle(1,DRAW_HISTOGRAM, 0, Bar_Width, Normal_Bar);}
  //Rising Volume Bars
  SetIndexBuffer(2,RisingBull);
  SetIndexStyle(2,DRAW_HISTOGRAM, 0, Bar_Width, Bull_Rising);
  SetIndexBuffer(3,RisingBear);
  SetIndexStyle(3,DRAW_HISTOGRAM, 0, Bar_Width, Bear_Rising);
  //Climax Volume Bars
  SetIndexBuffer(4,ClimaxBull);
  SetIndexStyle(4,DRAW_HISTOGRAM, 0, Bar_Width, Bull_Climax);
  SetIndexBuffer(5,ClimaxBear);
  SetIndexStyle(5,DRAW_HISTOGRAM, 0, Bar_Width, Bear_Climax);

  //Alert
  if(Alert_On) {Alert_Allowed = true;}

  //Indicator ShortName, Index Digits & Labels
  IndicatorDigits(0);
  SetIndexLabel(0, NULL);
  ShortName= "Broker Tick PVA:    ";
  if(Alert_On) {ShortName= ShortName + "Alert On,  Count ";}
  else {ShortName= ShortName + "Count ";}
  SetIndexLabel(1, IntegerToString(0));   
  SetIndexLabel(2, NULL);
  SetIndexLabel(3, NULL);
  SetIndexLabel(4, NULL);
  SetIndexLabel(5, NULL);
  SetIndexLabel(6, NULL);
  IndicatorShortName (ShortName);

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
    //Define Phantom volume larger than Normal, which displayed without color
    //assures Normal volume will occupy only the lower 75% of the volume window
    Phantom[i]= Volume[i]/0.75;
    
    //Define Normal volume
    Normal[i] = int(Volume[i]);
 
    //Clear buffers
    RisingBull[i] = 0;
    RisingBear[i] = 0;
    ClimaxBull[i] = 0;
    ClimaxBear[i] = 0;
    av            = 0;
    va            = 0;

    //Rising Volume
    for(j = i+1; j <= i+10; j++) {av = av + int(Volume[j]);}
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

    //Apply Correct Color to bars
    if(va==1)
      {
      //Bull Candle
      if(Close[i] > Open[i])
        {
        ClimaxBull[i] = int(Volume[i]);
        }
      //Bear Candle
      else if (Close[i] <= Open[i])
        {
        ClimaxBear[i] = int(Volume[i]);
        }
      //Sound & Text Alert
      if(i == 0 && Alert_Allowed && Alert_On)
        {
        Alert_Allowed = false;
        Alert(Broker_Name_In_Alert,":  ",Symbol(),"-",Period(),"   PVA alert!");
        }
      }
    else if(va==2)
      {
      if(Close[i] > Open[i]) {RisingBull[i] = int(Volume[i]);}
      if(Close[i] <= Open[i]) {RisingBear[i] = int(Volume[i]);}
      }        
    }//End "for i" loop

  return(0);
  }

//+-------------------------------------------------------------------------------------------+
//| Subroutine:  Set up to get the chart scale number                                         |
//+-------------------------------------------------------------------------------------------+
void OnChartEvent(const int id, const long &lparam, const double &dparam, const string &sparam)
  {
  Chart_Scale = ChartScaleGet();
  if(Alert_Allowed == allow)
    {
    init();
    Alert_Allowed = allow;
    }
  else
    {
    init();
    Alert_Allowed = disallow;
    }
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
