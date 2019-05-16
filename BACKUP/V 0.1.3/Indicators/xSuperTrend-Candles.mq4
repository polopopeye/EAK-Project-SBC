/*------------------------------------------------------------------------------------
   Name: xSuperTrend Candles.mq4
   Copyright ©2011, Xaphod, http://wwww.xaphod.com
   
   Description: SuperTrend Candles
	          
   Change log: 
       2014-05-28, Xaphod, v1.600
          - Update for MT4 build 600+
       2011-12-01. Xaphod, v1.00 
          - First Release 
-------------------------------------------------------------------------------------*/
#property copyright "©2011, xaphod.com"
#property link      "http://wwww.xaphod.com"

#property strict
#property version    "1.600"
#property description "xSuperTrend-Candles Indicator"
#property description ""
#property description "SuperTrend Formula:"
#property description "  UpperLevel=(High[i]+Low[i])/2+Multiplier*Atr(Period)"
#property description "  LowerLevel=(High[i]+Low[i])/2-Multiplier*Atr(Period)"

#property indicator_chart_window
#property indicator_buffers 5
#property indicator_color1 Red
#property indicator_color2 LimeGreen
#property indicator_color3 Red
#property indicator_color4 LimeGreen
#property indicator_color5 CLR_NONE
#property indicator_width1 1
#property indicator_width2 1
#property indicator_width3 3
#property indicator_width4 3
#property indicator_width5 1

// Constant definitions
#define INDICATOR_NAME "xSuperTrend-Candles"

// Indicator parameters
extern int    SuperTrend_Period=10;      // SuperTrend ATR Period
extern double SuperTrend_Multiplier=1.7; // SuperTrend Multiplier

//---- buffers
double gdaBearHL[];
double gdaBullHL[];
double gdaBearBuf[];
double gdaBullBuf[];
double gdaSuperTrend[];


//-----------------------------------------------------------------------------
// function: init()
// Description: Custom indicator initialization function.
//-----------------------------------------------------------------------------
int init() {
  //---- indicators
  SetIndexStyle(0,DRAW_HISTOGRAM);
  SetIndexBuffer(0, gdaBearHL);
  SetIndexDrawBegin(0,SuperTrend_Period);
  SetIndexStyle(1,DRAW_HISTOGRAM);
  SetIndexBuffer(1, gdaBullHL);
  SetIndexDrawBegin(1,SuperTrend_Period);
  SetIndexStyle(2,DRAW_HISTOGRAM);
  SetIndexBuffer(2, gdaBearBuf);
  SetIndexDrawBegin(2,SuperTrend_Period);
  SetIndexStyle(3,DRAW_HISTOGRAM);
  SetIndexBuffer(3, gdaBullBuf);
  SetIndexDrawBegin(3,SuperTrend_Period);
  SetIndexStyle(4,DRAW_LINE);
  SetIndexBuffer(4, gdaSuperTrend);
  SetIndexDrawBegin(4,SuperTrend_Period);
  return(0);
}


//-----------------------------------------------------------------------------
// function: deinit()
// Description: Custom indicator deinitialization function.
//-----------------------------------------------------------------------------
int deinit() {
   return (0);
}

//-----------------------------------------------------------------------------
// function: start()
// Description: Custom indicator iteration function.
//-----------------------------------------------------------------------------
int start() {
  int iNewBars, iCountedBars, i;
  double dAtr,dUpperLevel, dLowerLevel;
  
  // Get unprocessed ticks
  iCountedBars=IndicatorCounted();
  if(iCountedBars < 0) return (-1); 
  if(iCountedBars>0) iCountedBars--;
  iNewBars=Bars-iCountedBars;
  
  for(i=iNewBars; i>=0; i--) {
    // Bounds check
    if (i>=Bars-1)
      continue;
      
    // Calc SuperTrend
    dAtr = iATR(NULL, 0, SuperTrend_Period, i);
    dUpperLevel=(High[i]+Low[i])/2+SuperTrend_Multiplier*dAtr;
    dLowerLevel=(High[i]+Low[i])/2-SuperTrend_Multiplier*dAtr;
    
    // Set supertrend levels
    if (Close[i]>gdaSuperTrend[i+1] && Close[i+1]<=gdaSuperTrend[i+1]) {
      gdaSuperTrend[i]=dLowerLevel;
    }
    else if (Close[i]<gdaSuperTrend[i+1] && Close[i+1]>=gdaSuperTrend[i+1]) {
      gdaSuperTrend[i]=dUpperLevel;
    }
    else if (gdaSuperTrend[i+1]<dLowerLevel)
        gdaSuperTrend[i]=dLowerLevel;
    else if (gdaSuperTrend[i+1]>dUpperLevel)
        gdaSuperTrend[i]=dUpperLevel;
    else
      gdaSuperTrend[i]=gdaSuperTrend[i+1];
    
    // Draw Candles
    if (Close[i]>gdaSuperTrend[i] || (Close[i]==gdaSuperTrend[i] && Close[i+1]>gdaSuperTrend[i+1])) {
      gdaBearHL[i]=Low[i];
      gdaBullHL[i]=High[i];
      if (Close[i]>Open[i]) {
        gdaBearBuf[i]=Open[i];
        gdaBullBuf[i]=Close[i];
      }
      else {
        gdaBearBuf[i]=Close[i];
        gdaBullBuf[i]=Open[i];
      }
    }
    else if (Close[i]<gdaSuperTrend[i] || (Close[i]==gdaSuperTrend[i] && Close[i+1]<gdaSuperTrend[i+1])) {
      gdaBearHL[i]=High[i];
      gdaBullHL[i]=Low[i];
      if (Close[i]>Open[i]) {
        gdaBearBuf[i]=Close[i];
        gdaBullBuf[i]=Open[i];
      }
      else {
        gdaBearBuf[i]=Open[i];
        gdaBullBuf[i]=Close[i];
      }
    }
  }
  
  return(0);
}
//+------------------------------------------------------------------+