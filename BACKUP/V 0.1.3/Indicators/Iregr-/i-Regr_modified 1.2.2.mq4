//+------------------------------------------------------------------+
//|                                        i-Regr_modified 1.2.3.mq4 |
//|                                            Copyright © 2009, alx |
//|                  with important pieces of code from other authors|
//+------------------------------------------------------------------+
#property copyright "Copyright © 2009, alx@novusorsa.pl"
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
extern bool 	Show1st = true; // show 1st deviation
extern bool 	Show2nd = true; // show 2nd deviation
extern bool 	Show3rd = true; // show 3rd deviation
extern double 	kstd = 1.0; 	// 1st deviation
extern double 	kstd2 = 2.0;	// 2nd deviation
extern double 	kstd3 = 3.0;	// 3rd deviation


int shift = 0; // for compatibility with older code reasons
int startBar = 0; // for compatibility with older code reasons

int 		degree = 3;

//-----
double fx[],sqh[],sql[],sqh2[],sql2[],sqh3[],sql3[];

#import "Extratrend.dll"
void iRegrV1(int bars, int startBar, int degree, double Prices[], double& Curve[]);
void sigma3Bands(int bars, double std1, double std2, double std3, double priceArray[], double& curveArray[], double& firstHigh[], double& firstLow[], double& secondHigh[], double& secondLow[], double& thirdHigh[], double& thirdLow[]);
#import

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
	
	SetIndexShift(0, shift);
	SetIndexShift(1, shift);
	SetIndexShift(2, shift);
	SetIndexShift(3, shift);
	SetIndexShift(4, shift);
	SetIndexShift(5, shift);
	SetIndexShift(6, shift);
	//SetIndexShift(7, shift);
  
  int timeFrame = Period();
  
  if (AdjustToDailyCycle && dayCycle > 0)
  	{
		if (timeFrame <= PERIOD_D1) bars = dayCycle * PERIOD_D1/Period();
		else
			{
				Alert(Symbol(), " ", timeFrame, " Cannot adjust to daily cycles on this time frame");
				Print (Symbol()," ", timeFrame, " Cannot adjust to daily cycles on this time frame");
			}
	}
  
	return(0);
}
//-------------------------------------------------------------------------------------------
int deinit()
{
	//clear();
	return(0);
}
//-------------------------------------------------------------------------------------------
int start()
{
	if (Bars < startBar+bars+1) return;
	SetIndexDrawBegin(0, Bars-bars-1);

	double output[];
	ArrayResize(output, startBar+bars);
	ArrayInitialize(output, EMPTY_VALUE);
	double prices[];
	ArrayResize(prices, startBar+bars+1);
	ArrayCopy(prices, Close, 0,0, startBar+bars+1);
	
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

	return(0);
}