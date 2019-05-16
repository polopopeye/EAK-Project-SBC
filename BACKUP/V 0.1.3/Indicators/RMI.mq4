//+-------------------------------------------------------------------+
//|                                       Relative Momentum Index.mq4 |
//|                              Original indicator by davinviproject |
//|                  Modified and Corrected by Linuxser for forex TSD |
//|                                                                   |
//| Relative Momentum Index (RMI)                                     |
//| Overview                                                          |
//| The Relative Momentum Index (RMI) was developed by Roger Altman.  |
//| It was first introduced in the February 1993 issue of Technical   |
//| Analysis of Stocks & Commodities magazine.                        |
//| The RMI is a variation of the RSI indicator. The RMI counts up and|
//| down days from the close relative to the close x-days ago (where x|
//| is not limited to 1 as is required by the RSI) instead of counting|
//| up and down days from close to close as the RSI does.             |
//|                                                                   |
//| Note that an RMI with parameters of C, 14, 1 is equivalent to a 14|
//| period RSI of the Close price. This is because the momentum       |
//|parameter is calculating only a 1-day price change (which the RSI  |
//|does by (default).                                                 |
//|As the momentum periods are increased the RMI fluctuations become  |
//|smoother.                                                          |
//| Since the RMI is an oscillator it exhibits the same strengths and |
//| weaknesses of other overbought / oversold indicators.             |
//|During strong trending markets it is likely that the RMI will      | 
//|remain at overbought or oversold levels for an extended period of  |
//|time.                                                              |  
//|However, during non-trending markets the RMI tends to oscillate more 
//|predictably between an overbought level of 70 to 90 and an oversold|
//|level of 10 to 30.                                                 |
//+-------------------------------------------------------------------+
#property copyright ""
#property link ""

#property indicator_separate_window
#property indicator_buffers 1
#property indicator_color1 Peru
#property indicator_minimum 0
#property indicator_maximum 100

//---- input parameters
extern int RMIPeriod=14;
extern int MomPeriod=5;
//---- buffers
double RMIBuffer[];
double PosBuffer[];
double NegBuffer[];
//+------------------------------------------------------------------+
//| Custom indicator initialization function |
//+------------------------------------------------------------------+
int init()
{
//---- indicators
string short_name;
//---- 2 additional buffers are used for counting.
IndicatorBuffers(3);
SetIndexBuffer(1,PosBuffer);
SetIndexBuffer(2,NegBuffer);
//---- indicator line
SetIndexStyle(0,DRAW_LINE);
SetIndexBuffer(0,RMIBuffer);
SetLevelValue(0,30);
SetLevelValue(1,70);
SetLevelStyle(STYLE_SOLID,1,Red);

//---- name for DataWindow and indicator subwindow label
short_name="RMI("+RMIPeriod+","+MomPeriod+")";
IndicatorShortName(short_name);
SetIndexLabel(0,short_name);
//----
SetIndexDrawBegin(0,RMIPeriod);
//----
return(0);
}
//+------------------------------------------------------------------+
//| RMI - Relative Momentum Index |
//+------------------------------------------------------------------+
int start()
{
int i,counted_bars=IndicatorCounted();
double rel,negative,positive;
//----
if(Bars<=RMIPeriod) return(0);
//---- initial zero
if(counted_bars<1)
for(i=1;i<=RMIPeriod;i++) RMIBuffer[Bars-i]=0.0;
//----
i=Bars-RMIPeriod-1;
if(counted_bars>=RMIPeriod) i=Bars-counted_bars-1;
while(i>=0)
{
double sumn=0.0,sump=0.0;
if(i==Bars-RMIPeriod-1)
{
int k=Bars-2;
//---- initial accumulation
while(k>=i)
{
rel=Close[k]-Close[k+MomPeriod];
if(rel>0) sump+=rel;
else sumn-=rel;
k--;
}
positive=sump/RMIPeriod;
negative=sumn/RMIPeriod;
}
else
{
//---- simple moving average
rel=Close[i]-Close[i+MomPeriod];
if(rel>0) sump=rel;
else sumn=-rel;
positive=(PosBuffer[i+1]*(RMIPeriod-1)+sump)/RMIPeriod;
negative=(NegBuffer[i+1]*(RMIPeriod-1)+sumn)/RMIPeriod;
}
PosBuffer[i]=positive;
NegBuffer[i]=negative;
if(negative==0.0) RMIBuffer[i]=0.0;
else RMIBuffer[i]=100.0*positive/(positive+negative);
i--;
}
//----
return(0);
}
//+------------------------------------------------------------------+