//+------------------------------------------------------------------+
//|                                   Main and Side Clock 1.1.20 mq4 |
//|                                alx based on Clock code by Jerome |
//|                                                                  |
//+------------------------------------------------------------------+

#property copyright "alx based on Clock code by Jerome"
#property link      ""
// based on Clock code by Jerome 4xCoder@gmail.com
// and parts of windows time handing code from http://forum.mql4.com/21619
// Completly new London, new York and Tokyo DST handling based on international standards
// Special thanks to Ryan Tee for his great support on DST
// that made me to completly change the GMT time reference :-)

// 1.1.5 - Ryan: I added Sydney time, and active session indicators
// Thanks Ryan for pointing the bug source about automatic clock corner relocation
// 1.1.12 - Alx: time zone wrapping corrected. Timezones range is -11 to +13. Was -12 to +12.
// 1.1.13 - Alx: little improvement about broker TimeZone detection
// 1.1.14 - Alx: workaround a bug causing to remember and apply wrong broker GMT offset when broker feed is incomplete or history not updated.
//               In general this is MT4 limitation. No perfect solution, just another workaround.
//               Plus automatic vertical height adjustment & relocation.
// 1.1.15 - Alx: New York DST offset bug fix.
// 1.1.16 - Alx: Normalized Spread display to standard pips.
// 1.1.17 - Alx: A little workaround to get timezone updates more frequently on discontinued history.
// 1.1.18 - Alx: Another trick to avoid wrong broker TimeZone info - if stored TZ does not agree with calculated one, I force update to verify both.
// 1.1.19 and 20 - Alx: Nothing really important - some code cleanup here or there.

// Change the properties bellow to have Main Clock on main chart or Side Clock on separate indicator window:

// uncomment this pair and comment pair bellow to have it on main chart
#property indicator_chart_window
string ExtName="Main Clock 1.1.20";

// uncomment this pair and comment pair above to have it on any indicator sub-window
//#property indicator_separate_window
//string ExtName="Side Clock 1.1.20";


#property indicator_buffers 0

#import "kernel32.dll"
void GetSystemTime(int& TimeArray[]);
#import

extern int		corner			=3;
extern int		topOff			=80;
extern bool		ShowLocal		=true;
extern bool		ShowGMT			=true;
extern bool		ShowTZ 			=false;
extern bool		ShowTokyo		=true;
extern bool		ShowLondon		=true;
extern bool		ShowNewYork		=true;
extern bool		ShowSydney		=true;
extern bool		ShowSpread		=false;
extern bool		ShowBroker		=true;
extern bool		ShowBar			=false;
extern bool		ShowSessions	=true;
extern bool		SmallClock		=true;
extern color	labelColor		=White;
extern color	clockColor		=White;
extern color	PreActiveSessionColor	=Yellow;	
extern color	ActiveSessionColor		=Lime;
extern color	InactiveSessionColor	=DimGray;


int prevCorner = -1;

#define LondonDefaultTZ		0
#define TokyoDefaultTZ		9
#define NewYorkDefaultTZ	-5
#define SydneyDefaultTZ    10

int localGMTOffset, localDSTOffset, localGMTOffsetInSeconds;
int LondonOffsetHRS, TokyoOffsetHRS, NewYorkOffsetHRS, SydneyOffsetHRS;
datetime USOpen;

int LondonOffset;
int TokyoOffset;
int NewYorkOffset;
int SydneyOffset;
int LocalOffset;
int BrokerOffset;

string GlobalVariableTZname = "Side Clock 1.1 Last known Broker TimeZone";

string localtz;
string londontz;
string newyorktz;
string tokyotz;
string sydneytz;
string brokertz;

bool firstLaunch = true;

int windex, Spread;

datetime timeStamp;
#define dayInSeconds 86400

#define startupPeriod 3 // for the first 3 minutes I will be updating objects every minute as history data may be incomplete
int startupCount = -1;
datetime previousBrokerTime = 0, currentBrokerTime = 0;
double myPoint;
int myDigits,subPipDivider;
int currentBarCount, previousBarCount;
//------------------------------------------------------
bool isLondonOnDST(datetime now)
{
	// Europe DST rule:
	// On from 2:00 AM the last Sunday in March
	// Off to  3:00 AM the last Sunday in October
	
	int StartMonth	=	3;
	int EndMonth	=	10;
	int StartWeekDay=	0;
	int EndWeekDay	=	0;
	int StartHour	=	2;
	int EndHour		=	3;
	
	// the above transition times are local time. That means DST starts at 2AM local London standard time and ends at 3AM local London DST time...
	// I need to readjust it to gmt reference. London is GMT so I only need to adjust the end hour.
	EndHour -= 1;

	datetime pointer;
	int month = TimeMonth(now);
	if (month > StartMonth && month < EndMonth) return (true); // easy filter
	if (month < StartMonth || month > EndMonth) return (false); // same deal
	
	int i;
	int lookedDayNum;
	int currentDayNum = TimeDay(now);
	if (month == StartMonth)
		{
			//now wee need to know the starting day number. This is the last Sunday so lets do a walkthrough backward:
			pointer = StrToTime(StringConcatenate(TimeYear(now),".0",(StartMonth+1),".01")); // 1st April
			pointer -= dayInSeconds;
			
			for (i=6;i>=0;i--)
				{
					if (TimeDayOfWeek(pointer) == StartWeekDay)
						{
							lookedDayNum = TimeDay(pointer);
							if (lookedDayNum < currentDayNum) return (true);
							if (lookedDayNum > currentDayNum) return (false);
							if (lookedDayNum == currentDayNum)
								{
									if (TimeHour(now) >= StartHour) return (true); else return (false);
								}
						}	
					pointer -= dayInSeconds; // day in seconds
				}
			return(false);
		}
	
	if (month == EndMonth)
		{
			//now wee need to know the starting day number. This is the last Sunday so lets do a walkthrough backward:
			pointer = StrToTime(StringConcatenate(TimeYear(now),".0",(EndMonth+1),".01")); // 1st November
			pointer -= dayInSeconds;
			
			for (i=6;i>=0;i--)
				{
					if (TimeDayOfWeek(pointer) == EndWeekDay)
						{
							lookedDayNum = TimeDay(pointer);
							if (lookedDayNum < currentDayNum) return (false);
							if (lookedDayNum > currentDayNum) return (true);
							if (lookedDayNum == currentDayNum)
								{
									if (TimeHour(now) >= StartHour) return (false); else return (true);
								}
						}
					pointer -= dayInSeconds; // day in seconds
				}
			return(true);
		}	
	return (false);
}
//------------------------------------------------------ 
bool isUsOnDST(datetime now)
{
	// US DST rule:
	// On from 2:00 AM the second Sunday in March
	// Off to  2:00 AM the first Sunday in November
	
	// the code is almost the same as above. The only difference is I'm looking for the first and second Sunday.
	// and transition times adjustment..
	// this should be put in some kind of universal function, but i have no time, so copy&paste&edit:
	
	int StartMonth	=	3;
	int EndMonth	=	11;
	int StartWeekDay=	0;
	int EndWeekDay	=	0;
	int StartHour	=	2;
	int EndHour		=	2;
	
	// the above transition times are local time. That means DST starts at 2AM local London standard time and ends at 3AM local London DST time...
	// I need to readjust the gmt reference
	// this time a bit complex as NY is GMT-5...
	// I'm convertig the gmt to EST
	now += NewYorkDefaultTZ * 3600;
	
	datetime pointer;
	int month = TimeMonth(now);
	if (month > StartMonth && month < EndMonth) return (true); // easy filter
	if (month < StartMonth || month > EndMonth) return (false); // same deal

	int i;
	int lookedDayNum;
	int currentDayNum = TimeDay(now);
	if (month == StartMonth)
		{
			//now wee need to know the starting day number. This is the second Sunday so lets go forward:
			pointer = StrToTime(StringConcatenate(TimeYear(now),".0",(StartMonth),".01")); // 1st March
			//pointer -= dayInSeconds;
			bool firstSundaySpot = false;
			for (i=0;i<14;i++)
				{
					if (TimeDayOfWeek(pointer) == StartWeekDay)
						if (!firstSundaySpot) firstSundaySpot = true;
						else
							{
								lookedDayNum = TimeDay(pointer);
								if (lookedDayNum < currentDayNum) return (true);
								if (lookedDayNum > currentDayNum) return (false);
								if (lookedDayNum == currentDayNum)
									{
										if (TimeHour(now) >= StartHour) return (true); else return (false);
									}
							}	
					pointer += dayInSeconds; // day in seconds
				}
			return(false);
		}
	
	if (month == EndMonth)
		{
			//now wee need to know the starting day number. This is the first Sunday so lets go forward:
			pointer = StrToTime(StringConcatenate(TimeYear(now),".0",(EndMonth),".01")); // 1st November
			//pointer -= dayInSeconds;
			
			for (i=0;i<7;i++)
				{
					if (TimeDayOfWeek(pointer) == EndWeekDay)
						{
							lookedDayNum = TimeDay(pointer);
							if (lookedDayNum < currentDayNum) return (false);
							if (lookedDayNum > currentDayNum) return (true);
							if (lookedDayNum == currentDayNum)
								{
									if (TimeHour(now) >= StartHour) return (false); else return (true);
								}
						}
					pointer += dayInSeconds; // day in seconds
				}
			return(true);
		}	
	return (false);
}
//------------------------------------------------------ 
bool isSydneyOnDST(datetime now)
{
	// Sydney DST rule:
	// On from 2:00 AM the last Sunday in October
	// Off to  3:00 AM the last Sunday in March
	
	int StartMonth	=	10;
	int EndMonth	=	3;
	int StartWeekDay=	0;
	int EndWeekDay	=	0;
	int StartHour	=	2;
	int EndHour		=	3;
	
	// the above transition times are local time. That means DST starts at 2AM local Sydney standard time and ends at 3AM local Sydney DST time...
	// I need to readjust it to gmt reference. 
	// Same deal as with New York, shift gmt to make it local Sydney time
	now += SydneyDefaultTZ * 3600;
	//EndHour -= 1;

	datetime pointer;
	int month = TimeMonth(now);
	if (month > StartMonth || month < EndMonth) return (true); // easy filter
	if (month < StartMonth && month > EndMonth) return (false); // same deal
	
	int i;
	int lookedDayNum;
	int currentDayNum = TimeDay(now);
	if (month == StartMonth)
		{
			//now wee need to know the starting day number. This is the last Sunday so lets do a walkthrough backward:
			pointer = StrToTime(StringConcatenate(TimeYear(now),".0",(StartMonth+1),".01")); // 1st November
			pointer -= dayInSeconds;
			
			for (i=6;i>=0;i--)
				{
					if (TimeDayOfWeek(pointer) == StartWeekDay)
						{
							lookedDayNum = TimeDay(pointer);
							if (lookedDayNum < currentDayNum) return (true);
							if (lookedDayNum > currentDayNum) return (false);
							if (lookedDayNum == currentDayNum)
								{
									if (TimeHour(now) >= StartHour) return (true); else return (false);
								}
						}	
					pointer -= dayInSeconds; // day in seconds
				}
			return(false);
		}
	
	if (month == EndMonth)
		{
			//now wee need to know the starting day number. This is the last Sunday so lets do a walkthrough backward:
			pointer = StrToTime(StringConcatenate(TimeYear(now),".0",(EndMonth+1),".01")); // 1st April
			pointer -= dayInSeconds;
			
			for (i=6;i>=0;i--)
				{
					if (TimeDayOfWeek(pointer) == EndWeekDay)
						{
							lookedDayNum = TimeDay(pointer);
							if (lookedDayNum < currentDayNum) return (false);
							if (lookedDayNum > currentDayNum) return (true);
							if (lookedDayNum == currentDayNum)
								{
									if (TimeHour(now) >= StartHour) return (false); else return (true);
								}
						}
					pointer -= dayInSeconds; // day in seconds
				}
			return(true);
		}	
	return (false);
}
//------------------------------------------------------ 
bool isJapanOnDST(datetime now)
{
	// DST rule
	// No rule. No DST support. But maybe one day you can put the rule here...
	return (false);
}
//------------------------------------------------------ 
// the code comes from http://forum.mql4.com/21619
string FormatDateTime(int nYear,int nMonth,int nDay,int nHour,int nMin,int nSec)
{
	string sMonth,sDay,sHour,sMin,sSec = "";
	sMonth=100+nMonth;
	sMonth=StringSubstr(sMonth,1);
	sDay=100+nDay;
	sDay=StringSubstr(sDay,1);
	sHour=100+nHour;
	sHour=StringSubstr(sHour,1);
	sMin=100+nMin;
	sMin=StringSubstr(sMin,1);
	sSec=100+nSec;
	sSec=StringSubstr(sSec,1);
	return(StringConcatenate(nYear,".",sMonth,".",sDay," ",sHour,":",sMin,":",sSec));
}
//------------------------------------------------------ 
// the code comes from http://forum.mql4.com/21619
datetime getGMTime()
{
	/*MS stores time in plain format:	
	typedef struct _SYSTEMTIME {
	  WORD wYear;
	  WORD wMonth;
	  WORD wDayOfWeek;
	  WORD wDay;
	  WORD wHour;
	  WORD wMinute;
	  WORD wSecond;
	  WORD wMilliseconds;
	}SYSTEMTIME, *PSYSTEMTIME;
	*/
	int TimeArray[4];
	int nYear,nMonth,nDay,nHour,nMin,nSec;
	
	GetSystemTime(TimeArray);
	// some bit mask and shif magic to get word walues from dwords..
	nYear=TimeArray[0]&0x0000FFFF;
	nMonth=TimeArray[0]>>16;
	nDay=TimeArray[1]>>16;
	nHour=TimeArray[2]&0x0000FFFF;
	nMin=TimeArray[2]>>16;
	nSec=TimeArray[3]&0x0000FFFF;
	
	// Now, MT4 stores time in second elapsed from the 1st Jan 1970.
	// there are two ways to convert:
	// recalculate the MS time into seconds starting from 1970 or
	// convert it into string MT4 can convert into it's time format.
	// The first method is risky - needs to go around number of February days changing every 4 years...
	// At the moment using method 2.
	
	datetime localTime = TimeLocal();
	int localHour = TimeHour(localTime);
	localGMTOffset = localHour -nHour;
	if (localHour <  nHour) localGMTOffset += 24;
	localGMTOffsetInSeconds = 0-(localGMTOffset*60 + (TimeMinute(localTime)-nMin))*60; // supports half an hour TZ offsets..

	string utc = FormatDateTime(nYear, nMonth, nDay, nHour, nMin, nSec);
	return (StrToTime(utc));
}
//------------------------------------------------------ 
int getBrokerTZ(datetime gmt)
{
	int gmtHour		= TimeHour(gmt);
	int brokerHour	= TimeHour(TimeCurrent());
	int dif = brokerHour - gmtHour;
	if (dif < -11) dif += 24;
	if (dif > 13) dif -= 24;
	return(dif);
}
//------------------------------------------------------ 
int getLondonTZ(datetime gmt)
{
	if (isLondonOnDST(gmt))
		{
			LondonOffsetHRS = localGMTOffsetInSeconds+3600;
			return (LondonDefaultTZ+1);
		}
	else
		{
			LondonOffsetHRS = localGMTOffsetInSeconds;
			return (LondonDefaultTZ);
		}
}
//------------------------------------------------------ 
int getNewYorkTZ(datetime gmt)
{
	if (isUsOnDST(gmt))
		{
			NewYorkOffsetHRS = localGMTOffsetInSeconds+(NewYorkDefaultTZ+1)*3600;
			return (NewYorkDefaultTZ+1);
		}
	else
		{
			NewYorkOffsetHRS = localGMTOffsetInSeconds+(NewYorkDefaultTZ)*3600;
			return (NewYorkDefaultTZ);
		}
}
//------------------------------------------------------ 
int getSydneyTZ(datetime gmt)
{
	if (isSydneyOnDST(gmt))
		{
			SydneyOffsetHRS = localGMTOffsetInSeconds+(SydneyDefaultTZ+1)*3600;
			return (SydneyDefaultTZ+1);
		}
	else
		{
			SydneyOffsetHRS = localGMTOffsetInSeconds+(SydneyDefaultTZ)*3600;
			return (SydneyDefaultTZ);
		}
}
//------------------------------------------------------ 
int getTokyoTZ(datetime gmt)
{
	if (isJapanOnDST(gmt))
		{
			TokyoOffsetHRS = localGMTOffsetInSeconds+(TokyoDefaultTZ+1)*3600;
			return (TokyoDefaultTZ+1);
		}
	else
		{
			TokyoOffsetHRS = localGMTOffsetInSeconds+(TokyoDefaultTZ)*3600;
			return (TokyoDefaultTZ);
		}
}
//------------------------------------------------------
void updateTimeSettings()
{
	datetime gmt	= getGMTime();
	//LocalOffset	= getLocalTZ();
	LocalOffset		= localGMTOffset;
	BrokerOffset	= getBrokerTZ(gmt);
	LondonOffset	= getLondonTZ(gmt);
	NewYorkOffset	= getNewYorkTZ(gmt);
	TokyoOffset		= getTokyoTZ(gmt);
	SydneyOffset	= getSydneyTZ(gmt);
	
	if(ShowSessions) USOpen = StrToTime(StringConcatenate(TimeToStr(TimeLocal() + NewYorkOffsetHRS, TIME_DATE)," 09:30")); // this creates current day timestamp with 9:30:00 AM hours, minutes and seconds parts
	
	if (startupCount < startupPeriod) // this is workaround about incomplete histroy. I assume it will be updated withing 3 minutes. Until then, I'm not going to save Broket GMT offset as it may be inacurate.
		{
			currentBrokerTime = iTime(NULL, PERIOD_M1, 0);
			if (currentBrokerTime >  previousBrokerTime)
				{
					previousBrokerTime = currentBrokerTime;
					startupCount ++;
				}
		}
	int weekDay = TimeDayOfWeek(TimeLocal()); // if weekend, broker TZ will be read from saved Global Variable if any.
	// however it should be checked once the broker feed is active again on Sunday... especially on Sunday!
	// To do: check on Sunday of you have a new bar dated Sudnay and if true, allow calculated offset.
	if ((Hour() >= 22 && weekDay == 5) || weekDay == 0 || weekDay == 6)
		{
			if (GlobalVariableCheck(GlobalVariableTZname))
				{
					BrokerOffset = GlobalVariableGet(GlobalVariableTZname);
				}
			else
				{
					Print ("No data available over weekend. Please wait for the first tick on Monday to update the Broker Time Zone");
					brokertz 	= "n/a";
				}
		}
	else {if (startupCount > startupPeriod-1 && IsConnected()) GlobalVariableSet(GlobalVariableTZname, BrokerOffset);} // this can be only set when broker data is acticve and history updated
	// however, it won't work if communication disrupted for more than an hour during a week...
	
	string gmtName = "GMT";
	if (SmallClock) gmtName = "";

	if (LocalOffset >= 0)	localtz 	= gmtName+"+"+ LocalOffset; 	else localtz 	= gmtName+ LocalOffset;
	if (LondonOffset >= 0)	londontz 	= gmtName+"+"+ LondonOffset; 	else londontz 	= gmtName+ LondonOffset;
	if (NewYorkOffset >= 0)	newyorktz 	= gmtName+"+"+ NewYorkOffset; 	else newyorktz 	= gmtName+ NewYorkOffset;
	if (TokyoOffset >= 0)	tokyotz 	= gmtName+"+"+ TokyoOffset; 	else tokyotz 	= gmtName+ TokyoOffset;
	if (SydneyOffset >= 0)	sydneytz 	= gmtName+"+"+ SydneyOffset; 	else sydneytz 	= gmtName+ SydneyOffset;
	if (BrokerOffset >= 0)	brokertz 	= gmtName+"+"+ BrokerOffset; 	else brokertz 	= gmtName+ BrokerOffset;
}
//------------------------------------------------------ 
int start()
{
  if (!IsDllsAllowed())
	{
		Alert( "Please enable 'Allow DLL Imports' for the indicator to make it work" );
		return(0);
  	}
  	
    if (firstLaunch) 
    	{
			windex = WindowOnDropped();
			if (windex < 1) windex = 0;
    		if (windex > 0) setLabels(); // fixed corner position if Side Clock
    	}
  
  	if (windex == 0) // If the clock is on Main Chart, I need it to check the price plot to go away from it automatically
		{
			prevCorner = corner;
			double priceRange, priceMax, priceMin, currentPrice;
			if (corner == 0 || corner == 2) currentPrice = Close[WindowFirstVisibleBar()];
			else  currentPrice = Bid;
				
			priceMax = WindowPriceMax(windex);
			priceMin = WindowPriceMin(windex);
			priceRange = priceMax - priceMin;

			if (currentPrice < priceMin + priceRange/2)
				{
					if (corner == 3) corner = 1;
					else
					if (corner == 2) corner = 0;
				}
			else
				{
					if(corner == 1) corner = 3;
					else
					if(corner == 0) corner = 2;
				}
				
			if (prevCorner != corner || firstLaunch) setLabels(); // double check actually on the firstLaunch but let it be on the safe side...
		}

	datetime localtime	= TimeLocal();
	datetime gmttime	= getGMTime();
	datetime brokertime = TimeCurrent();

	currentBarCount = Bars;
	bool update = false;
	int newTZ = readGV(GlobalVariableTZname);
	if (newTZ != BrokerOffset)
		{
			if (newTZ > -11 && newTZ < 13)
				{
					Print ("Found new BrokerOffset value: ", newTZ, " while BrokerOffset ", BrokerOffset, "Checking which one is right...");
					update = true;
				}
		}
		
	if (localtime > timeStamp + 3600 || currentBarCount > previousBarCount+1 || update) // check the DST flip evey hour... or more often if history not continuous.
		{
			Print ("Updating updateTimeSettings...");
			updateTimeSettings();
			timeStamp = localtime;
		}
	previousBarCount = currentBarCount;	
		
	datetime london	= localtime + LondonOffsetHRS;
	datetime newyork= localtime + NewYorkOffsetHRS;
	datetime tokyo	= localtime + TokyoOffsetHRS;
	datetime sydney	= localtime + SydneyOffsetHRS;

	string gmtTime		= TimeToStr(gmttime, 	TIME_MINUTES);
	string localTime	= TimeToStr(localtime, 	TIME_MINUTES);
	string brokerTime	= TimeToStr(brokertime,	TIME_MINUTES);
	
	string londonTime 	= TimeToStr(london,		TIME_MINUTES);
	string newyorkTime 	= TimeToStr(newyork,	TIME_MINUTES);
	string tokyoTime 	= TimeToStr(tokyo,		TIME_MINUTES);
	string sydneyTime 	= TimeToStr(sydney,		TIME_MINUTES);
	string barTime 		= TimeToStr(brokertime - Time[0], TIME_MINUTES);

	int digits = Digits-myDigits;
	string spread = DoubleToStr((Ask-Bid)/myPoint,digits);
  //	Spread = MarketInfo(Symbol(),MODE_SPREAD);
  
  
	if(ShowLocal)
		{
			ObjectSetText("loclabel"+windex,"Local:",8,"Arial",labelColor);
			ObjectSetText("loctime"+windex,localTime,8,"Arial",clockColor);
			ObjectSetText("loctz"+windex,localtz,8,"Arial",clockColor);
		}

	if(ShowTZ)
		{
			ObjectSetText("tzlabel"+windex,"TimeZone:",8,"Arial",labelColor);
			ObjectSetText("tzvalue"+windex,localtz,8,"Arial",clockColor);
		}
	
	if(ShowGMT)
		{
			ObjectSetText("gmtlabel"+windex,"UTC:",8,"Arial",labelColor);
			ObjectSetText("gmttime"+windex,gmtTime,8,"Arial",clockColor);
		}
		
	if(ShowNewYork)
		{
			if(ShowSessions)
				{
					if (TimeDayOfWeek(newyork) > 0 && TimeDayOfWeek(newyork) < 6)
						{
							if (TimeHour(newyork) >= 8 && newyork < USOpen) ObjectSetText("nysession" + windex, "l", 8, "Wingdings", PreActiveSessionColor);
							else if (newyork >= USOpen && TimeHour(newyork) <= 16) ObjectSetText("nysession" + windex, "l", 8, "Wingdings", ActiveSessionColor);
							else ObjectSetText("nysession" + windex, "l", 8, "Wingdings", InactiveSessionColor);
						}
					else ObjectSetText("nysession" + windex, "l", 8, "Wingdings", InactiveSessionColor);
				}
			
			ObjectSetText("nylabel"+windex,"New York:",8,"Arial",labelColor);
			ObjectSetText("nytime"+windex,newyorkTime,8,"Arial",clockColor);
			ObjectSetText("nytz"+windex,newyorktz,8,"Arial",clockColor);
		}
	if(ShowLondon)
		{
			if(ShowSessions)
				{
					if (TimeDayOfWeek(london) > 0 && TimeDayOfWeek(london) < 6)
						{				
							if (TimeHour(london) >= 8 && TimeHour(london) < 9) ObjectSetText("lonsession" + windex, "l", 8, "Wingdings", PreActiveSessionColor);
							else if (TimeHour(london) >= 9 && TimeHour(london) <= 16) ObjectSetText("lonsession" + windex, "l", 8, "Wingdings", ActiveSessionColor);
							else ObjectSetText("lonsession" + windex, "l", 8, "Wingdings", InactiveSessionColor);
						}
					else ObjectSetText("lonsession" + windex, "l", 8, "Wingdings", InactiveSessionColor);
				}
			ObjectSetText("lonlabel"+windex,"London:",8,"Arial",labelColor);
			ObjectSetText("lontime"+windex,londonTime,8,"Arial",clockColor);
			ObjectSetText("lontz"+windex,londontz,8,"Arial",clockColor);
		}
		
	if(ShowTokyo)
		{
			if(ShowSessions)
				{		
					if (TimeDayOfWeek(tokyo) > 0 && TimeDayOfWeek(tokyo) < 6)
						{		
							if (TimeHour(tokyo) >= 9 && TimeHour(tokyo) <= 15) ObjectSetText("toksession" + windex, "l", 8, "Wingdings", ActiveSessionColor);
							else ObjectSetText("toksession" + windex, "l", 8, "Wingdings", InactiveSessionColor);
						}
					else ObjectSetText("toksession" + windex, "l", 8, "Wingdings", InactiveSessionColor);
				}
			
			ObjectSetText("toklabel"+windex,"Tokyo:",8,"Arial",labelColor);
			ObjectSetText("toktime"+windex,tokyoTime,8,"Arial",clockColor);
			ObjectSetText("toktz"+windex,tokyotz,8,"Arial",clockColor);
		}
	if(ShowSydney)
		{
			if(ShowSessions)
				{
					if (TimeDayOfWeek(sydney) > 0 && TimeDayOfWeek(sydney) < 6)
						{				
							if (TimeHour(sydney) >= 9 && TimeHour(sydney) <= 16) ObjectSetText("sydsession" + windex, "l", 8, "Wingdings", ActiveSessionColor);
							else ObjectSetText("sydsession" + windex, "l", 8, "Wingdings", InactiveSessionColor);
						}
					else ObjectSetText("sydsession" + windex, "l", 8, "Wingdings", InactiveSessionColor);
				}
				
			ObjectSetText("sydlabel"+windex,"Sydney:",8,"Arial",labelColor);
			ObjectSetText("sydtime"+windex,sydneyTime,8,"Arial",clockColor);
			ObjectSetText("sydtz"+windex,sydneytz,8,"Arial",clockColor);
		}
		
	if(ShowBroker)
		{
			ObjectSetText("brolabel"+windex,"Broker:",8,"Arial",labelColor);
			ObjectSetText("brotime"+windex,brokerTime,8,"Arial",clockColor);
			ObjectSetText("brotz"+windex,brokertz,8,"Arial",clockColor);
		}

	if(ShowBar)
		{		
			ObjectSetText("barlabel"+windex,"Bar:",8,"Arial",labelColor);
			ObjectSetText("bartime"+windex,barTime,8,"Arial",clockColor);
		}
		
	if(ShowSpread)
		{
			ObjectSetText("splabel"+windex,"Spread:",8,"Arial",labelColor);
			ObjectSetText("spvalue"+windex,spread,8,"Arial",clockColor);
		}

//----
return(0);
}
//------------------------------------------------------
int ObjectMakeLabel(string n,int xoff,int yoff)
{
	n = n+windex;
	ObjectCreate(n,OBJ_LABEL,windex,0,0);
	ObjectSet(n,OBJPROP_CORNER,corner);
	ObjectSet(n,OBJPROP_XDISTANCE,xoff);
	ObjectSet(n,OBJPROP_YDISTANCE,yoff);
	ObjectSet(n,OBJPROP_BACK,true);
}
//------------------------------------------------------
void setLabels()
{
	int top=topOff; // this has to be changed to the least offset and row offset.
	int left=90;
	int middle=55;
	int right=10;
	int spacing = 15;	
	if (SmallClock)
		{
			left=70;
			middle=35;
			right=10;
			spacing = 12;
		}
	
	int dot= left + 50;

	int rowCount = 0;

	if(ShowGMT)		rowCount++;
	if(ShowTZ)		rowCount++;
	if(ShowLocal)	rowCount++;
	if(ShowLondon)	rowCount++;
	if(ShowNewYork)	rowCount++;
	if(ShowTokyo)	rowCount++;
	if(ShowSydney)	rowCount++;
	if(ShowBroker)	rowCount++;
	if(ShowBar)		rowCount++;
	if(ShowSpread)	rowCount++;
	top = rowCount*spacing + topOff-80; // this is for compatiblity reasons...
	
	if (corner == 0 || corner == 2)
		{
			int leftColOffset = 55; // thi needs to be addressed - on some systems LED's overlap text
			if (SmallClock) leftColOffset -= 5;
			int middleColWidh	= left - middle;
			left = right;
			middle = left + leftColOffset;
			right = middle + middleColWidh;
		}

	if (corner == 0 || corner == 1)
		{
			top += 18-top;
			spacing = 0-spacing;
		}
		
	int offset = 0;
	if(ShowGMT)
		{
			
			ObjectMakeLabel("gmtlabel",left,top-offset);
			ObjectMakeLabel("gmttime",middle,top-offset);
			//ObjectMakeLabel("gmttz",right,top-offset);
			offset+=spacing;
		}

	if(ShowTZ)
		{				
			ObjectMakeLabel("tzlabel",left,top-offset);
			ObjectMakeLabel("tzvalue",right,top-offset);
			offset+=spacing;
		}

	if(ShowLocal)
		{
			ObjectMakeLabel("loclabel",left,top-offset);
			ObjectMakeLabel("loctime",middle,top-offset);
			ObjectMakeLabel("loctz",right,top-offset);
			offset+=spacing;
		}	
		
	if(ShowLondon)
		{
			if(ShowSessions) ObjectMakeLabel("lonsession",dot,top-offset);
			ObjectMakeLabel("lonlabel",left,top-offset);
			ObjectMakeLabel("lontime",middle,top-offset);
			ObjectMakeLabel("lontz",right,top-offset);
			offset+=spacing;
		}

	if(ShowNewYork)
		{
			if(ShowSessions) ObjectMakeLabel("nysession",dot,top-offset);
			ObjectMakeLabel("nylabel",left,top-offset);
			ObjectMakeLabel("nytime",middle,top-offset);
			ObjectMakeLabel("nytz",right,top-offset);
			offset+=spacing;
		}

	if(ShowTokyo)
		{	
			if(ShowSessions) ObjectMakeLabel("toksession",dot,top-offset);
			ObjectMakeLabel("toklabel",left,top-offset);
			ObjectMakeLabel("toktime",middle,top-offset);
			ObjectMakeLabel("toktz",right,top-offset);
			offset+=spacing;
		}

	if(ShowSydney)
		{	
			if(ShowSessions) ObjectMakeLabel("sydsession",dot,top-offset);
			ObjectMakeLabel("sydlabel",left,top-offset);
			ObjectMakeLabel("sydtime",middle,top-offset);
			ObjectMakeLabel("sydtz",right,top-offset);
			offset+=spacing;
		}
		
	if(ShowBroker)
		{
			ObjectMakeLabel("brolabel",left,top-offset);
			ObjectMakeLabel("brotime",middle,top-offset);
			ObjectMakeLabel("brotz",right,top-offset);
			offset+=spacing;
		}

	if(ShowBar)
		{
			ObjectMakeLabel("barlabel",left,top-offset);
			ObjectMakeLabel("bartime",middle,top-offset);
			//ObjectMakeLabel("gmttime",right,top-offset);
			offset+=spacing;
		}
		
	if(ShowSpread)
		{	
			ObjectMakeLabel("splabel",left,top-offset);
			ObjectMakeLabel("spvalue",middle,top-offset);
			offset+=spacing;
		}
		
	firstLaunch = false;
}

//------------------------------------------------------
int init()
{
	myPoint = Point;
	myDigits = Digits;
	subPipDivider = 1;
	
	if (myDigits == 3 || myDigits == 5) 
		{
			myPoint *= 10;
			myDigits --;
			subPipDivider = 10;
		}
	currentBarCount = Bars;
	previousBarCount = Bars+1;
	updateTimeSettings();
	return(0);
}
//------------------------------------------------------
int deinit()
{
	ObjectDelete("loclabel"+windex);
	ObjectDelete("loctime"+windex);
	ObjectDelete("loctz"+windex);

	ObjectDelete("nysession"+windex);
	ObjectDelete("nylabel"+windex);
	ObjectDelete("nytime"+windex);
	ObjectDelete("nytz"+windex);

	ObjectDelete("gmtlabel"+windex);
	ObjectDelete("gmttime"+windex);
	//ObjectDelete("gmttz"+windex);

	ObjectDelete("lonsession"+windex);
	ObjectDelete("lonlabel"+windex);
	ObjectDelete("lontime"+windex);
	ObjectDelete("lontz"+windex);

	ObjectDelete("toksession"+windex);
	ObjectDelete("toklabel"+windex);
	ObjectDelete("toktime"+windex);
	ObjectDelete("toktz"+windex);

	ObjectDelete("sydsession"+windex);
	ObjectDelete("sydlabel"+windex);
	ObjectDelete("sydtime"+windex);
	ObjectDelete("sydtz"+windex);
	
	ObjectDelete("brolabel"+windex);
	ObjectDelete("brotime"+windex);
	ObjectDelete("brotz"+windex);
	
	ObjectDelete("barlabel"+windex);
	ObjectDelete("bartime"+windex);

	ObjectDelete("splabel"+windex);
	ObjectDelete("spvalue"+windex);

	ObjectDelete("tzlabel"+windex);
	ObjectDelete("tzvalue"+windex);

return(0);
}
// --------------------------------
int readGV(string GvName)
{
	int result = EMPTY_VALUE;
	if (GlobalVariableCheck(GvName))
		{
			result = GlobalVariableGet(GvName);
		}
	return (result);
}