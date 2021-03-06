//+------------------------------------------------------------------+
//|                                      HurstExponent_v1.0 600+.mq4 |
//|                                Copyright © 2017, TrendLaboratory |
//|            http://finance.groups.yahoo.com/group/TrendLaboratory |
//|                                   E-mail: igorad2003@yahoo.co.uk |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2017, TrendLaboratory"
#property link      "http://finance.groups.yahoo.com/group/TrendLaboratory"
#property link      "http://newdigital-world.com/forum.php"

#property indicator_separate_window
#property indicator_buffers 2

#property indicator_color1  clrDeepSkyBlue
#property indicator_width1  2
#property indicator_color2  clrGold
#property indicator_style2  2  


//---- input parameters
input ENUM_TIMEFRAMES   TimeFrame      = PERIOD_CURRENT;    // Timeframe
input string            Periods        = "10;20;25;40;50;100;125;200;250;500;1000";   
input int               CountBars      = 0;                 // Number of bars counted: 0-all bars 

#define pi 3.14159265358979323846

double hurst[];
double betae[];
double logreturns[];


int      timeframe, size, cBars, draw_begin, maxperiod;
double   periods[], logRS[], e[], evalue;
string   TF, IndicatorName, short_name;
//+------------------------------------------------------------------+
//| Custom indicator initialization function                         |
//+------------------------------------------------------------------+
int OnInit()
{
   timeframe = TimeFrame;
   if(timeframe <= Period()) timeframe = Period(); 
   TF = tf(timeframe);
   
   IndicatorDigits(5);
//---- 
   IndicatorBuffers(3);
   SetIndexBuffer(0,     hurst); SetIndexStyle(0,DRAW_LINE);
   SetIndexBuffer(1,     betae); SetIndexStyle(1,DRAW_LINE);
   SetIndexBuffer(2,logreturns); 
   
   IndicatorName = WindowExpertName(); 
   short_name    =  IndicatorName+"["+TF+"]";
   IndicatorShortName(short_name);
   SetIndexLabel(0,"Hurst Exponent");   
   SetIndexLabel(1,"Beta E");    
   
   
   size = StrToDoubleArray(Periods,periods,";"); 
   ArrayResize(logRS,size);
   ArrayResize(    e,size);
   
   maxperiod = 0;
   
   for(int i=0;i<size;i++) 
   {
   maxperiod = MathMax(maxperiod,periods[i]);
   e[i]      = MathLog(calcERS(periods[i]));
   }
      
   if(CountBars == 0) cBars = timeframe/Period()*(iBars(NULL,TimeFrame) - maxperiod); else cBars = CountBars*timeframe/Period();
  
   draw_begin = Bars - cBars;
   
   SetIndexDrawBegin(0,draw_begin);
   SetIndexDrawBegin(1,draw_begin);
   
   evalue = calcReg(e); 
  
   return(INIT_SUCCEEDED);
}
//+------------------------------------------------------------------+
//| Custom indicator iteration function                              |
//+------------------------------------------------------------------+
int start()
{
   int   i, j, shift, limit, counted_bars = IndicatorCounted();
   
   if(counted_bars > 0) limit = Bars - counted_bars - 1;
   if(counted_bars < 0) return(0);
   if(counted_bars < 1)
   { 
   if(CountBars == 0) limit = Bars - 2; else limit = MathMin(Bars - 2,CountBars + maxperiod);  
      for(i=Bars-1;i>=0;i--) 
      {
      hurst[i] = EMPTY_VALUE;
      betae[i] = EMPTY_VALUE;
      }
   }
   
   if(timeframe != Period())
	{
   limit = MathMax(limit,timeframe/Period());   
      
      for(shift=0;shift<limit;shift++) 
      {	
      int y = iBarShift(NULL,TimeFrame,Time[shift]);
      
      hurst[shift] = iCustom(NULL,TimeFrame,IndicatorName,0,Periods,CountBars,0,y);
      betae[shift] = iCustom(NULL,TimeFrame,IndicatorName,0,Periods,CountBars,1,y); 
      } 
	
	return(0);
	}
	
   
   
   for(shift=limit;shift>=0;shift--) 
   {
   logreturns[shift] = MathLog(Close[shift]/Close[shift+1]);
   
   if(shift > cBars) continue;
         
      for(i=0;i<size;i++)
      {
      double rssum = 0;
         for(j=0;j<maxperiod/periods[i];j++) rssum += calcRS(periods[i]*j,periods[i]*(j + 1),periods[i],shift);
      logRS[i] = MathLog(rssum/(maxperiod/periods[i]));
      }
 
   hurst[shift] = calcReg(logRS);
   betae[shift] = evalue;   
   }
   
   if(CountBars > 0)
   {
   SetIndexDrawBegin(0,Bars - cBars);   
   SetIndexDrawBegin(1,Bars - cBars);
   }
   
   return(0);
}   


double calcRS(int begin,int end,int period,int bar)
{
   double sum = 0;                                              

   for(int i=begin;i<end;i++) sum += logreturns[bar+i];   
  
   double avg = sum/period;
   
   double devsum = 0, minvalue = EMPTY_VALUE, maxvalue =-EMPTY_VALUE, devaccum, stddevmas, prevdev = 0;
   
   for(i=begin;i<end;i++)
   {
   devaccum  = logreturns[bar+i] - avg + prevdev;
   stddevmas = MathPow((logreturns[bar+i] - avg),2);
   devsum   += stddevmas;               
   if(devaccum > maxvalue) maxvalue = devaccum; 
   if(devaccum < minvalue) minvalue = devaccum;
   prevdev = devaccum; 
   } 

   double R = maxvalue - minvalue;
   double S = MathSqrt(devsum/period);
//--- 
   if(S > 0) return(R/S); else return(0);                            
}   



double calcReg(double& y[])
{
   double sumy = 0, sumx = 0, sumyx = 0, sumxx = 0;

   for(int i=0;i<size;i++)
   {
   double n = MathLog(periods[i]);     
   sumx  += (n);
   sumy  += y[i];
   sumxx += n*n;
   sumyx += y[i]*n;
   }
   
   double beta = (size*sumyx - sumy*sumx)/(size*sumxx - sumx*sumx);
   
   return(beta);
}


double calcERS(double period)
{
   double sum = 0;
   
   for(int i=1;i<period;i++) sum += MathPow(((period - i)/i),0.5);
     
   return(MathPow((period*pi/2),-0.5)*sum);
}


//+------------------------------------------------------------------+
int StrToDoubleArray(string str, double &a[], string delim=",", int _init=0)  
//+------------------------------------------------------------------+
//  Breaks down a single string into double array 'a' (elements delimited by 'delim')
//  e.g. string is "1,2,3,4,5";  if delim is "," then the result will be
//  a[0]=1.0   a[1]=2.0   a[2]=3.0   a[3]=4.0   a[4]=5.0
//  Unused array elements are initialized by value in 'init' (default is 0)
{  
   int z1=-1, z2=0;
   
   if(str == "") return(0);  
   if(StringRight(str,1) != delim) str = str + delim;
   
   int strcnt = StringFindCount(str,delim);
   
   ArrayResize(a,strcnt);
   
   for(int i=0;i<strcnt;i++) a[i] = _init;
   
   for(i=0;i<strcnt;i++)  
   {
   z2 = StringFind(str,delim,z1+1);
   if(z2 > z1 + 1) a[i] = StrToNumber(StringSubstr(str,z1 + 1,z2 - z1 - 1));
   if(z2 >= StringLen(str) - 1) break;
   z1 = z2;
   }
  
   return(strcnt);
}

string StringRight(string str, int n=1)
//+------------------------------------------------------------------+
// Returns the rightmost N characters of STR, if N is positive
// Usage:    string x=StringRight("ABCDEFG",2)  returns x = "FG"
//
// Returns all but the leftmost N characters of STR, if N is negative
// Usage:    string x=StringRight("ABCDEFG",-2)  returns x = "CDEFG"
{
   if (n > 0)  return(StringSubstr(str,StringLen(str) - n,n));
   if (n < 0)  return(StringSubstr(str,-n,StringLen(str) - n));
  
   return("");
}

double StrToNumber(string str)  
//+------------------------------------------------------------------+
// Usage: strips all non-numeric characters out of a string, to return a numeric (double) value
// valid numeric characters are digits 0,1,2,3,4,5,6,7,8,9, decimal point (.) and minus sign (-)
// Example: StrToNumber("the balance is $-34,567.98") returns the numeric value -34567.98
{  
   int    dp    = -1;
   int    sgn   = 1;
   double snum  = 0.0;
  
   for (int i=0; i<StringLen(str); i++)  
   {
   string s = StringSubstr(str,i,1);
    if (s == "-")  sgn = -sgn;   else
    if (s == ".")  dp = 0;       else
      if (s >= "0" && s <= "9")  
      {
      if (dp >= 0)  dp++;
      if (dp > 0) snum = snum + StrToInteger(s)/MathPow(10,dp);
      else
      snum = snum*10 + StrToInteger(s);
      }
   }
   
   return(snum*sgn);
}

int StringFindCount(string str, string str2)
//+------------------------------------------------------------------+
// Returns the number of occurrences of STR2 in STR
// Usage:   int x = StringFindCount("ABCDEFGHIJKABACABB","AB")   returns x = 3
{
   int c = 0;
   for (int i=0; i<StringLen(str); i++)
      if (StringSubstr(str,i,StringLen(str2)) == str2)  c++;
   return(c);
}

  
string tf(int itimeframe)
{
   string result = "";
   
   switch(itimeframe)
   {
   case PERIOD_M1:   result = "M1" ;
   case PERIOD_M5:   result = "M5" ;
   case PERIOD_M15:  result = "M15";
   case PERIOD_M30:  result = "M30";
   case PERIOD_H1:   result = "H1" ;
   case PERIOD_H4:   result = "H4" ;
   case PERIOD_D1:   result = "D1" ;
   case PERIOD_W1:   result = "W1" ;
   case PERIOD_MN1:  result = "MN1";
   default:          result = "N/A";
   }
   
   if(result == "N/A")
   {
   if(itimeframe <  PERIOD_H1 ) result = "M"  + itimeframe;
   if(itimeframe >= PERIOD_H1 ) result = "H"  + itimeframe/PERIOD_H1;
   if(itimeframe >= PERIOD_D1 ) result = "D"  + itimeframe/PERIOD_D1;
   if(itimeframe >= PERIOD_W1 ) result = "W"  + itimeframe/PERIOD_W1;
   if(itimeframe >= PERIOD_MN1) result = "MN" + itimeframe/PERIOD_MN1;
   }
   
   return(result); 
}
