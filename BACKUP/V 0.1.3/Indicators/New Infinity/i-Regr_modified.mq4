//+------------------------------------------------------------------+
//|                                        i-Regr modified 1.4.1.mq4 |
//|                                            Copyright  2009, alx |
//|                  with important pieces of code from other authors|
//+------------------------------------------------------------------+
#property copyright "Copyright  2009, alx@novusorsa.pl"
#property link      "www.novusorsa.pl/lmt/"
//----
#property indicator_chart_window
#property indicator_buffers 7
#property indicator_color1 LimeGreen
#property indicator_color2 Gold
#property indicator_color3 Gold
#property indicator_color4 Orange
#property indicator_color5 Orange
#property indicator_color6 OrangeRed
#property indicator_color7 OrangeRed

#property  indicator_width1  1
#property  indicator_width2  1
#property  indicator_width3  1
#property  indicator_width4  2
#property  indicator_width5  2
#property  indicator_width6  3
#property  indicator_width7  3

extern bool 	AdjustToDailyCycle = true; // this is a switch to either automatically calculate bar to # days bellow or use bars value directly
extern int 		dayCycle = 2;		// basic market daily cycle is usually 2 days
extern int 		bars = 250;
extern int		barShift = 0;
extern bool		animate	= false;
extern int		step = 1;
extern int 		degree = 3;
extern bool 	Show1st = true; // show 1st deviation
extern bool 	Show2nd = true; // show 2nd deviation
extern bool 	Show3rd = true; // show 3rd deviation
extern double 	kstd = 1.0; 	// 1st deviation
extern double 	kstd2 = 2.0;	// 2nd deviation
extern double 	kstd3 = 3.0;	// 3rd deviation
// PowerSaver
extern int	PowerSaver			= 15; // in seconds - to reduce CPU usage it will calculate every n seconds instead of every tick. 0 = realtime.

int startBar = 0; // for compatibility with older code reasons
int i;

//-----
double fx[],sqh[],sql[],sqh2[],sql2[],sqh3[],sql3[];

#import "Extratrend.dll"
void iRegrV1(int bars, int startBar, int degree, double Prices[], double& Curve[]);
void sigma3Bands(int bars, double std1, double std2, double std3, double priceArray[], double& curveArray[], double& firstHigh[], double& firstLow[], double& secondHigh[], double& secondLow[], double& thirdHigh[], double& thirdLow[]);
#import

int currentCPUtime = 0, previousCPUtime = 0, powerSaverInterval;
//-------------------------------------------------------------------------------------------
int init()
{
	SetIndexBuffer(0, fx);
	SetIndexBuffer(1, sqh);
	SetIndexBuffer(2, sql);
	SetIndexBuffer(3, sqh2);
	SetIndexBuffer(4, sql2);
	SetIndexBuffer(5, sqh3);
	SetIndexBuffer(6, sql3);
	
	SetIndexStyle(0, DRAW_LINE);
	SetIndexStyle(1, DRAW_LINE);
	SetIndexStyle(2, DRAW_LINE);
	SetIndexStyle(3, DRAW_LINE);
	SetIndexStyle(4, DRAW_LINE);
	SetIndexStyle(5, DRAW_LINE);
	SetIndexStyle(6, DRAW_LINE);
	//SetIndexStyle(7, DRAW_LINE);
	
	SetIndexEmptyValue(0, 0.0);
	SetIndexEmptyValue(1, 0.0);
	SetIndexEmptyValue(2, 0.0);
	SetIndexEmptyValue(3, 0.0);
	SetIndexEmptyValue(4, 0.0);
	SetIndexEmptyValue(5, 0.0);
	SetIndexEmptyValue(6, 0.0);
	//SetIndexEmptyValue(7, 0.0);
	
	SetIndexShift(0, -barShift);
	SetIndexShift(1, -barShift);
	SetIndexShift(2, -barShift);
	SetIndexShift(3, -barShift);
	SetIndexShift(4, -barShift);
	SetIndexShift(5, -barShift);
	SetIndexShift(6, -barShift);
	//SetIndexShift(7, -barShift);
  
  int timeFrame = Period();
  
  if (AdjustToDailyCycle && dayCycle > 0)
  	{
		if (timeFrame <= PERIOD_D1) bars = dayCycle * PERIOD_D1/timeFrame;
		else
			{
				Alert(Symbol(), " ", timeFrame, " Cannot adjust to daily cycles on this time frame");
				Print (Symbol()," ", timeFrame, " Cannot adjust to daily cycles on this time frame");
			}
	}
	
	if (step < 1) step = 1;
	if (step > barShift) step = barShift;
	i = barShift;
	
	// PowerSaver
	if (PowerSaver <=0) PowerSaver = 0;
	int timeFrameSeconds = timeFrame*60;
	if (PowerSaver >timeFrameSeconds) PowerSaver = timeFrameSeconds; // it doesn't make sense to calcucate less frequently.
	powerSaverInterval = PowerSaver*1000; // I need miliseconds
	if (animate) PowerSaver = 0;
	
	return(0);
}
//-------------------------------------------------------------------------------------------
int deinit()
{
	return(0);
}
//-------------------------------------------------------------------------------------------
void calculateIndicator(int bar)
{
	SetIndexDrawBegin(0, Bars-bar-bars-1);

	SetIndexEmptyValue(0, 0.0);
	SetIndexEmptyValue(1, 0.0);
	SetIndexEmptyValue(2, 0.0);
	SetIndexEmptyValue(3, 0.0);
	SetIndexEmptyValue(4, 0.0);
	SetIndexEmptyValue(5, 0.0);
	SetIndexEmptyValue(6, 0.0);
	
	SetIndexShift(0, -bar);
	SetIndexShift(1, -bar);
	SetIndexShift(2, -bar);
	SetIndexShift(3, -bar);
	SetIndexShift(4, -bar);
	SetIndexShift(5, -bar);
	SetIndexShift(6, -bar);

	double output[];
	ArrayResize(output, startBar+bars);
	ArrayInitialize(output, EMPTY_VALUE);
	double prices[];
	ArrayResize(prices, startBar+bar+bars+1);
	ArrayCopy(prices, Close, 0,bar, startBar+bars+1);
	
	ArrayInitialize(fx, 0.0);
	ArrayInitialize(sqh, 0.0);
	ArrayInitialize(sql, 0.0);
	ArrayInitialize(sqh2, 0.0);
	ArrayInitialize(sql2, 0.0);
	ArrayInitialize(sqh3, 0.0);
	ArrayInitialize(sql3, 0.0);
  
	iRegrV1(bars, startBar, degree, prices, output);

	ArrayCopy(fx, output, 0, 0, bars);
	
	// stdev //

	if (Show1st || Show2nd || Show3rd)
		{
			double fh[], fl[], sh[], sl[], th[], tl[];
			double firstBand, secondBand, thirdBand;
			
			if(Show1st)
				{
					ArrayResize(fh,bars);
					ArrayResize(fl,bars);
					firstBand = kstd;
				}
			else firstBand = 0;
			
			if(Show2nd)
				{
					ArrayResize(sh,bars);
					ArrayResize(sl,bars);
					secondBand = kstd2;
				}	
			else secondBand = 0;
			
			if(Show3rd)
				{
					ArrayResize(th,bars);
					ArrayResize(tl,bars);
					thirdBand = kstd3;
				}	
			else thirdBand = 0;			
			
			sigma3Bands(bars, firstBand, secondBand, thirdBand, prices, output, fh, fl, sh, sl, th, tl);
			
			if(Show1st)
				{
					ArrayCopy(sqh, fh, 0, 0, bars);
					ArrayCopy(sql, fl, 0, 0, bars);
				}
			
			if(Show2nd)
				{
					ArrayCopy(sqh2, sh, 0, 0, bars);
					ArrayCopy(sql2, sl, 0, 0, bars);
				}

			if(Show3rd)
				{
					ArrayCopy(sqh3, th, 0, 0, bars);
					ArrayCopy(sql3, tl, 0, 0, bars);
				}
		}	
}
//-------------------------------------------------------------------------------------------
int start()
{
	currentCPUtime = GetTickCount();
	if (PowerSaver <=0 || currentCPUtime >= previousCPUtime+powerSaverInterval)
		{
			if (Bars < barShift+bars+1) return;
			int curSec = 0, prevSec = 0;
			if (animate && barShift > 0)
				{
					Print ("Current bar shift ", i);
					calculateIndicator(i);
					i -= step;
					if(i < 0) i = barShift;
				}
			else calculateIndicator(barShift);
				
			previousCPUtime = GetTickCount();
 		}
	return (0);
}

