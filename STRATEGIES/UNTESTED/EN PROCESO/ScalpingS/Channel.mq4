//+------------------------------------------------------------------+
//|                                  TriangularMA centered bands.mq4 |
//|                                                           mladen |
//|                                                                  |
//|                                  multiple bands mod          eni |
//+------------------------------------------------------------------+
#property copyright "Fxtrader"
#property link      "mladenfx@gmail.com"

#property indicator_chart_window
#property indicator_buffers    9
#property indicator_color1     clrNONE// clrBlack
#property indicator_color2     clrBrown
#property indicator_color3     clrRoyalBlue // first upper band//C'92,106,120' //clrAqua
#property indicator_color4     clrRed  // first lower band//clrNONE// clrRed  //C'255,40,40'
#property indicator_color5     clrRoyalBlue //clrNONE//clrRoyalBlue
#property indicator_color6     clrRed //clrNONE// clrRed
#property indicator_color7     clrRoyalBlue //clrNONE// clrRoyalBlue
#property indicator_color8     clrYellow //C'92,106,120' //RIPT
#property indicator_color9     clrYellow //C'92,106,120' //RIPT
#property indicator_style1     STYLE_DOT
#property indicator_style2     STYLE_DOT
#property indicator_style3     STYLE_DOT
#property indicator_style4     STYLE_SOLID
#property indicator_style5     STYLE_SOLID
#property indicator_style6     STYLE_SOLID
#property indicator_style7     STYLE_SOLID
#property indicator_style8     STYLE_SOLID
#property indicator_style9     STYLE_SOLID
#property indicator_width1     1
#property indicator_width2     1
#property indicator_width3     1
#property indicator_width4     1
#property indicator_width5     1
#property indicator_width6     1
#property indicator_width7     1
#property indicator_width8     1 //RIPT
#property indicator_width9     1 //RIPT

//
//
//
//
//

extern string TimeFrame          = "Current";
extern int    HalfLength         = 55;    // 55
extern int    Price              = PRICE_CLOSE;
extern double ATRMultiplier1     = 2.8;   // 2.1
extern double ATRMultiplier2     = 3.5;   // 3.4
extern double ATRMultiplier3     = 4.2;   // 5.5
extern double ATRMultiplier4     = .9;   // 1.0

extern int    ATRPeriod          = 100;
extern bool   Interpolate        = true;

extern bool   alertsOn           = false;
extern bool   alertsOnCurrent    = false;
extern bool   alertsOnHighLow    = false;
extern int    alertsTMAnumber    = 2;
extern bool   alertsMessage      = false;
extern bool   alertsNotification = false;
extern bool   alertsEmail        = false;
extern bool   alertsSound        = false;

//
//
//
//
//

double buffer1[];
double buffer2[];
double buffer3[];
double buffer4[];
double buffer5[];
double buffer6[];
double buffer7[];
double buffer8[];
double buffer9[];
double trend[];
double slope[];

//
//
//
//
//

string indicatorFileName;
bool   calculateValue;
bool   returnBars;
int    timeFrame;

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
//
//
//
//

int init()
{
   IndicatorBuffers(11);
   HalfLength=MathMax(HalfLength,1);
      SetIndexBuffer( 0,buffer1); SetIndexEmptyValue( 0,EMPTY_VALUE); SetIndexDrawBegin(0,HalfLength);
      SetIndexBuffer( 1,buffer2); SetIndexEmptyValue( 1,EMPTY_VALUE); SetIndexDrawBegin(1,HalfLength);
      SetIndexBuffer( 2,buffer3); SetIndexEmptyValue( 2,EMPTY_VALUE); SetIndexDrawBegin(2,HalfLength);
      SetIndexBuffer( 3,buffer4); SetIndexEmptyValue( 3,EMPTY_VALUE); SetIndexDrawBegin(3,HalfLength);
      SetIndexBuffer( 4,buffer5); SetIndexEmptyValue( 4,EMPTY_VALUE); SetIndexDrawBegin(4,HalfLength);
      SetIndexBuffer( 5,buffer6); SetIndexEmptyValue( 5,EMPTY_VALUE); SetIndexDrawBegin(5,HalfLength);
      SetIndexBuffer( 6,buffer7); SetIndexEmptyValue( 6,EMPTY_VALUE); SetIndexDrawBegin(6,HalfLength);
      SetIndexBuffer( 7,buffer8); SetIndexEmptyValue( 7,EMPTY_VALUE); SetIndexDrawBegin(7,HalfLength);
      SetIndexBuffer( 8,buffer9); SetIndexEmptyValue( 8,EMPTY_VALUE); SetIndexDrawBegin(8,HalfLength);
      SetIndexBuffer( 9,trend  );
      SetIndexBuffer(10,slope  ); SetIndexEmptyValue(10,EMPTY_VALUE);

      //
      //
      //
      //
      //
   
      indicatorFileName = WindowExpertName();
      returnBars        = TimeFrame=="returnBars";     if (returnBars)     return(0);
      calculateValue    = TimeFrame=="calculateValue"; if (calculateValue) return(0);
      timeFrame         = stringToTimeFrame(TimeFrame);
      
      //
      //
      //
      //
      //
      
   IndicatorShortName(timeFrameToString(timeFrame)+" TMA bands )"+HalfLength+")");
   return(0);
}
int deinit() { return(0); }




//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
//
//
//
//
//

int start()
{
   int counted_bars=IndicatorCounted();
   int i,j,k,limit;

   if(counted_bars<0) return(-1);
   if(counted_bars>0) counted_bars--;
           limit=MathMin(Bars-1,Bars-counted_bars+HalfLength);
            if (returnBars)  { buffer1[0] = limit+1; return(0); }

   //
   //
   //
   //
   //
   
   if (calculateValue || timeFrame==Period())
   {
      double range = 0.0;
      
      for (i=limit; i>=0; i--)
      {
         double sum  = (HalfLength+1)*iMA(NULL,0,1,0,MODE_SMA,Price,i);
         double sumw = (HalfLength+1);
         
         for(j=1, k=HalfLength; j<=HalfLength; j++, k--)
         {
            sum  += k*iMA(NULL,0,1,0,MODE_SMA,Price,i+j);
            sumw += k;

            if (j<=i)
            {
               sum  += k*iMA(NULL,0,1,0,MODE_SMA,Price,i-j);
               sumw += k;
            }
         }

         //
         //
         //
         //
         //
      
         range = iATR ( NULL, 0, ATRPeriod, i + 10 ) * ATRMultiplier1;
         buffer1[i] = sum/sumw;
         buffer2[i] = buffer1[i]+range;
         buffer3[i] = buffer1[i]-range;
         
         slope  [i] = slope[i+1];
         
         if ( buffer1[i] != 0.0 )  
            { 
              slope[i] = ( ( buffer1[i] - buffer1[i+1] )  / buffer1[i] ) * 100000;
            }
            
         if ( ATRMultiplier2 != 0.0 )
            {
              range = iATR ( NULL, 0, ATRPeriod, i + 10 ) * ATRMultiplier2;
              buffer4[i] = buffer1[i]+range;
              buffer5[i] = buffer1[i]-range;
            }
            
         if ( ATRMultiplier3 != 0.0 )
            {
              range = iATR ( NULL, 0, ATRPeriod, i + 10 ) * ATRMultiplier3;
              buffer6[i] = buffer1[i]+range;
              buffer7[i] = buffer1[i]-range;
            }
            
         if ( ATRMultiplier4 != 0.0 )
            {
              range = iATR ( NULL, 0, ATRPeriod, i + 10 ) * ATRMultiplier4;
              buffer8[i] = buffer1[i]+range;
              buffer9[i] = buffer1[i]-range;
            }

         //
         //
         //
         //
         //
          
         trend[i] = 0;                     
            if (alertsOnHighLow)       
            {
               if ( alertsTMAnumber == 1 && High[i] > buffer2[i] ) trend[i] =  1;
               if ( alertsTMAnumber == 1 && Low [i] < buffer3[i] ) trend[i] = -1;
               if ( alertsTMAnumber == 2 && High[i] > buffer4[i] ) trend[i] =  1;
               if ( alertsTMAnumber == 2 && Low [i] < buffer5[i] ) trend[i] = -1;
               if ( alertsTMAnumber == 3 && High[i] > buffer6[i] ) trend[i] =  1;
               if ( alertsTMAnumber == 3 && Low [i] < buffer7[i] ) trend[i] = -1;
               if ( alertsTMAnumber == 4 && High[i] > buffer8[i] ) trend[i] =  1;
               if ( alertsTMAnumber == 4 && Low [i] < buffer9[i] ) trend[i] = -1;
            }
            else
            {
               if ( alertsTMAnumber == 1 && Close[i] > buffer2[i] ) trend[i] =  1;
               if ( alertsTMAnumber == 1 && Close[i] < buffer3[i] ) trend[i] = -1;
               if ( alertsTMAnumber == 2 && Close[i] > buffer4[i] ) trend[i] =  1;
               if ( alertsTMAnumber == 2 && Close[i] < buffer5[i] ) trend[i] = -1;
               if ( alertsTMAnumber == 3 && Close[i] > buffer6[i] ) trend[i] =  1;
               if ( alertsTMAnumber == 3 && Close[i] < buffer7[i] ) trend[i] = -1;
               if ( alertsTMAnumber == 4 && Close[i] > buffer8[i] ) trend[i] =  1;
               if ( alertsTMAnumber == 4 && Close[i] < buffer9[i] ) trend[i] = -1;
            }
      }
      if (!calculateValue) manageAlerts();
      return(0);            
   }
   
   //
   //
   //
   //
   //

   limit = MathMax(limit,MathMin( Bars-1, iCustom ( NULL, timeFrame, indicatorFileName, "returnBars", HalfLength, Price, ATRMultiplier1, ATRMultiplier2, ATRMultiplier3, ATRMultiplier4, ATRPeriod, Interpolate, alertsOn, alertsOnCurrent, alertsOnHighLow, alertsTMAnumber, alertsMessage, alertsNotification, alertsEmail, alertsSound, 0, 0 ) * timeFrame / Period() ) );
   for(i=limit; i>=0; i--)
   {
      int y = iBarShift(NULL,timeFrame,Time[i]);
      buffer1[i] = iCustom ( NULL, timeFrame, indicatorFileName, "calculateTma", HalfLength, Price, ATRMultiplier1, ATRMultiplier2, ATRMultiplier3, ATRMultiplier4, ATRPeriod, Interpolate, alertsOn, alertsOnCurrent, alertsOnHighLow, alertsTMAnumber, alertsMessage, alertsNotification, alertsEmail, alertsSound, 0, y );
      buffer2[i] = iCustom ( NULL, timeFrame, indicatorFileName, "calculateTma", HalfLength, Price, ATRMultiplier1, ATRMultiplier2, ATRMultiplier3, ATRMultiplier4, ATRPeriod, Interpolate, alertsOn, alertsOnCurrent, alertsOnHighLow, alertsTMAnumber, alertsMessage, alertsNotification, alertsEmail, alertsSound, 1, y );
      buffer3[i] = iCustom ( NULL, timeFrame, indicatorFileName, "calculateTma", HalfLength, Price, ATRMultiplier1, ATRMultiplier2, ATRMultiplier3, ATRMultiplier4, ATRPeriod, Interpolate, alertsOn, alertsOnCurrent, alertsOnHighLow, alertsTMAnumber, alertsMessage, alertsNotification, alertsEmail, alertsSound, 2, y );
      trend[i]   = iCustom ( NULL, timeFrame, indicatorFileName, "calculateTma", HalfLength, Price, ATRMultiplier1, ATRMultiplier2, ATRMultiplier3, ATRMultiplier4, ATRPeriod, Interpolate, alertsOn, alertsOnCurrent, alertsOnHighLow, alertsTMAnumber, alertsMessage, alertsNotification, alertsEmail, alertsSound, 3, y );

      //
      //
      //
      //
      //
       
      if (timeFrame <= Period() || y==iBarShift(NULL,timeFrame,Time[i-1])) continue;
      if (!Interpolate) continue;

      //
      //
      //
      //
      //

      datetime time = iTime(NULL,timeFrame,y);
         for(int n = 1; i+n < Bars && Time[i+n] >= time; n++) continue;	
         for(k = 1; k < n; k++)
         {
            buffer1[i+k] = buffer1[i]  +(buffer1[i+n]-buffer1[i])*k/n;
            buffer2[i+k] = buffer2[i]  +(buffer2[i+n]-buffer2[i])*k/n;
            buffer3[i+k] = buffer3[i]  +(buffer3[i+n]-buffer3[i])*k/n;
         }               
   }

   //
   //
   //
   //
   //
      
   manageAlerts();
   return(0);
}

//+-------------------------------------------------------------------
//|                                                                  
//+-------------------------------------------------------------------
//
//
//
//
//

void manageAlerts()
{
   if (alertsOn)
   {
      if (alertsOnCurrent)
           int whichBar = 0;
      else     whichBar = 1; whichBar = iBarShift(NULL,0,iTime(NULL,timeFrame,whichBar));
      if (trend[whichBar] != trend[whichBar+1])
      {
         if (trend[whichBar] == 1) doAlert(whichBar,"up");
         if (trend[whichBar] ==-1) doAlert(whichBar,"down");
      }         
   }
}

//
//
//
//
//

void doAlert(int forBar, string doWhat)
{
   static string   previousAlert="nothing";
   static datetime previousTime;
   string message;
   
   if (previousAlert != doWhat || previousTime != Time[forBar]) {
       previousAlert  = doWhat;
       previousTime   = Time[forBar];

       //
       //
       //
       //
       //

       message =  StringConcatenate(Symbol()," at ",TimeToStr(TimeLocal(),TIME_SECONDS)," "+timeFrameToString(timeFrame)+" TMA bands price penetrated ",doWhat," band");
          if (alertsMessage)      Alert(message);
          if (alertsNotification) SendNotification(message);
          if (alertsEmail)        SendMail(StringConcatenate(Symbol(),"TMA bands "),message);
          if (alertsSound)        PlaySound("alert2.wav");
   }
}

//+-------------------------------------------------------------------
//|                                                                  
//+-------------------------------------------------------------------
//
//
//
//
//

string sTfTable[] = {"M1","M5","M15","M30","H1","H4","D1","W1","MN"};
int    iTfTable[] = {1,5,15,30,60,240,1440,10080,43200};

//
//
//
//
//

int stringToTimeFrame(string tfs)
{
   tfs = StringUpperCase(tfs);
   for (int i=ArraySize(iTfTable)-1; i>=0; i--)
         if (tfs==sTfTable[i] || tfs==""+iTfTable[i]) return(MathMax(iTfTable[i],Period()));
                                                      return(Period());
}
string timeFrameToString(int tf)
{
   for (int i=ArraySize(iTfTable)-1; i>=0; i--) 
         if (tf==iTfTable[i]) return(sTfTable[i]);
                              return("");
}

//
//
//
//
//

string StringUpperCase(string str)
{
   string   s = str;

   for (int length=StringLen(str)-1; length>=0; length--)
   {
      int ichar = StringGetChar(s, length);
         if((ichar > 96 && ichar < 123) || (ichar > 223 && ichar < 256))
                     s = StringSetChar(s, length, ichar - 32);
         else if(ichar > -33 && ichar < 0)
                     s = StringSetChar(s, length, ichar + 224);
   }
   return(s);
}