//+------------------------------------------------------------------+
//| Polynominal Regression Analysis.                                 |
//| Sometimes this implementation's visual structure is              |
//| identified as the Center of Gravity, or COG, indicator           |
//| Original Publication may be: https://www.mql5.com/en/code/8417   |
//| "boris", 2008.09.12 06:16                                        |
//+------------------------------------------------------------------+
#property copyright "https://www.forexfactory.com/lukeb"
#property link      "https://www.forexfactory.com/showthread.php?t=651904"
#property version   "1.07"
#property strict
//*******************************************
#property indicator_chart_window
#property indicator_buffers 10
enum ENUM_COG_BUFFS { COG_CNTR,     COG_HIGH_SQ,   COG_LOW_SQ,    COG_HIGH_STD,   COG_LOW_STD,  endCOGBuffs};
enum ENUM_SAV_BUFFS { CNTR_SAV,     SQ_HIGH_SAVE,  SQ_LOW_SAVE,   STD_HIGH_SAVE,  STD_LOW_SAVE, endSaveBuffs};
color cogColor[] =  { clrRoyalBlue, clrLimeGreen,  clrLimeGreen,  clrGoldenrod,   clrGoldenrod};
color saveColor[] = { clrLightBlue, clrLightGreen, clrLightGreen, clrGoldenrod,   clrGoldenrod};
string cogName[]  = { "COG_CNTR",   "COG_HIGH_SQ", "COG_LOW_SQ",  "COG_HIGH_STD", "COG_LOW_STD"};
string saveName[] = { "CNTR_SAV",   "SQ_HIGH_SAVE","SQ_LOW_SAVE", "STD_HIGH_SAVE","STD_LOW_SAVE"};
ENUM_LINE_STYLE cogStyle = STYLE_SOLID;
ENUM_LINE_STYLE saveStyle = STYLE_DOT;
struct IndiStruct
 {
   double indiBuff[];
 } cogBuff[endCOGBuffs], saveBuff[endSaveBuffs];
//-----------------------------------
input uint     uniqueID = 733;
input int     bars_back = 125;
input int    twoDefault = 2;
//
input double       kstd = 2.0;
input bool      HideOld = false;  // Hide old bar display
input bool ShowCogHistory = true; // show history of COG values at the creation of each bar
//-----------------------
double ai[10][10], b[10], x[10], sx[20];
int    cogBars;
int    threeDefault;
//----------------~---
const string shortName = IntegerToString(uniqueID)+"COG";
const int CHARTWINDOW = 0;
enum ENUM_COG_BAR { NEW_BAR, FIXED_BAR } cogSource=NEW_BAR;  // new bar is to draw from Bar Zero, Fixed bar is to allow input of a bar to draw from.
datetime  cogTime;
const string cogLabel = IntegerToString(uniqueID)+"COGLABEL";
const string cogBox   = IntegerToString(uniqueID)+"COGBOX";
string msg="";
//*******************************************
//+------------------------------------------------------------------+
//| Custom indicator initialization function                         |
//+------------------------------------------------------------------+
int OnInit()
 {
   EventSetTimer(3);
   int initSuccess = INIT_SUCCEEDED;
   IndicatorShortName(shortName);
   if( Bars<(bars_back+2) )
    {
      initSuccess = INIT_FAILED;
      Print("Insufficient History, ", IntegerToString(Bars)," bars found, ",IntegerToString(bars_back+2)," bars required.");
    }
   else
    {
      for( ENUM_COG_BUFFS buffNum = 0; buffNum < endCOGBuffs; buffNum++)
       {
         setIndiParms(cogBuff[buffNum], cogColor[buffNum], cogName[buffNum], cogStyle, buffNum);  
       }
      for( ENUM_SAV_BUFFS buffNum = 0; buffNum < endSaveBuffs; buffNum++)
       {
         setIndiParms(saveBuff[buffNum], saveColor[buffNum], saveName[buffNum], saveStyle, buffNum + endCOGBuffs);
       }
      cogBars = bars_back;
      threeDefault = twoDefault + 1;
      //--- load globally saved values ------------------------------------------------------------
      cogTime = getCogBarGlobalValue(cogBox);
      datetime oldestValidTime = Time[(Bars-(bars_back+2))];
      if( (cogTime < oldestValidTime) || (cogTime > Time[0]) )
       {
         cogTime = Time[0];
       }
      cogSource = getCogSourceGlobalValue(cogLabel);
      //----------------------sx-------------------------------------------------------------------
      setSX_aryValues(sx, cogBars, threeDefault);
      displayControl(cogSource);
    }
   return(initSuccess);
 }
void setIndiParms(IndiStruct& buffStruct, const color& indiColor, const string& indiName,  const ENUM_LINE_STYLE& indiStyle, const int buffNum)
 {
   const static int width = 1;
   SetIndexBuffer(buffNum, buffStruct.indiBuff);
   SetIndexLabel(buffNum, indiName);
   SetIndexStyle(buffNum,DRAW_LINE, indiStyle,width,indiColor);
   SetIndexEmptyValue(buffNum, EMPTY_VALUE);
   SetIndexDrawBegin(buffNum,0);
 }
//+------------------------------------------------------------------+
//| Expert Exit Function                                             |
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
 {
   EventKillTimer();
   ObjectDelete(cogLabel);
   ObjectDelete(cogBox);
   if( msg != "" )
      Comment("");
 }
//+------------------------------------------------------------------+
//| Timer function                                                   |
//+------------------------------------------------------------------+
void OnTimer()
 {
   // int runBar = 0;
   // runIndicator(Bars, runBar);
 }
//+------------------------------------------------------------------+
//| ChartEvent function                                              |
//+------------------------------------------------------------------+
void OnChartEvent(const int id, const long &lparam, const double &dparam, const string &sparam)
 {
   if(id==CHARTEVENT_OBJECT_CLICK)  // Detect when objects are clicked
    {
      if( sparam==cogLabel )  // Clicked to change the COG Display Bar
       {          
         cogSource = (cogSource==NEW_BAR)?FIXED_BAR:NEW_BAR;   // toggle cogSource

         switch (cogSource)
          {
            case NEW_BAR:
               runIndicator(cogTime, Time[0]);
               break;
            default:
               runIndicator(cogTime, cogTime);
               break;
          }
         GlobalVariableSet(getGlobalName(cogLabel), cogSource);
         displayControl(cogSource);
       }
    }
   else if( id==CHARTEVENT_OBJECT_ENDEDIT )
    {
      if( sparam==cogBox )    // Accept new fixedCogBar value
       {
         datetime newValue = StringToTime(ObjectGetString(ChartID(),cogBox,OBJPROP_TEXT,0));
         datetime oldestValidTime = Time[(Bars-(bars_back+2))];
         if( (oldestValidTime <= newValue) && (newValue <= Time[0]) )
          {
            cogTime=newValue;
            GlobalVariableSet(getGlobalName(cogBox), cogTime);
          }
         runIndicator(cogTime, cogTime);
         displayControl(cogSource);
       }
    }
 }
//+------------------------------------------------------------------+
//| Custom indicator iteration function                              |
//+------------------------------------------------------------------+
int OnCalculate(const int rates_total, const int prev_calculated, const datetime &time[], const double &open[], const double &high[],
                const double &low[], const double &close[], const long &tick_volume[], const long &volume[], const int &spread[])
 {
   if( cogSource == NEW_BAR )
    {
      runIndicator( cogTime, Time[0] );
    }
   else  // cogSourc == FIXED_BAR
    {
      runIndicator(cogTime, cogTime);
    }
   return(rates_total);
 }
//+------------------------------------------------------------------+
//| Run the indicator                                                |
//+------------------------------------------------------------------+
void runIndicator( const datetime& drawStartTime, const datetime& newestDrawTime )
 {
   static uint callCount = 0; callCount++;
   int oldestDrawBar = iBarShift(Symbol(),Period(),drawStartTime);
   int newestDrawBar = iBarShift(Symbol(),Period(),newestDrawTime);
   int range = oldestDrawBar-newestDrawBar;
   // msg = StringConcatenate("Draw from Start: ",TimeToStr(drawStartTime,TIME_DATE|TIME_MINUTES),", to End: ",TimeToStr(newestDrawTime,TIME_DATE|TIME_MINUTES),", Bars: ",IntegerToString(oldestDrawBar)," to: ",IntegerToString(newestDrawBar),", Bar Time: ",TimeToStr(Time[newestDrawBar],TIME_DATE|TIME_MINUTES),".");
   // Comment(msg);
   //
   for( int workBar = oldestDrawBar; workBar>=newestDrawBar; workBar-- )
    { 
      if( ShowCogHistory && (range>0) ) // this is a new bar calculation
       {
         loadCogHistories(workBar);
       }
      load_b_aryValues(b,cogBars, workBar, threeDefault);
      initializeAI_ary(ai,sx, threeDefault);
      //===============Gauss===========================================
      calculateGause(ai,b,threeDefault);
      //
      loadX_ary(x, b, ai, threeDefault);
      //
      loadCOG_Center( cogBuff[COG_CNTR].indiBuff, x, workBar, cogBars, twoDefault);
      //-----------------------------------Std-------------------------------------
      double sq = getSQ(workBar, cogBars, cogBuff[COG_CNTR].indiBuff, kstd);
      double std = iStdDev(NULL, 0, cogBars, MODE_SMA, 0, PRICE_CLOSE, workBar) * kstd;
      loadSideBands(workBar, cogBars, sq, std);
      //---------------------------------------------------------------------------
      if( (HideOld == true)  && (cogSource == NEW_BAR) )
       {  // // Sets the bar number (from the data beginning) from which the drawing of the given indicator line must start.
         setDrawStart( Bars - (workBar + (bars_back + 1)) );
       } // setDrawStart(Bars - (cogBars + bars_back + 1) );
      else
       {
         setDrawStart(0);
       }
    }
 }
//+------------------------------------------------------------------+
//| Indicator Routines                                               |
//+------------------------------------------------------------------+
void setSX_aryValues(double& ary_SX[], const int& lookBack, const int& calcLimit)
 {  // These values never change once calcuatled, only needs to be caluculated once. 
   ary_SX[1] = lookBack + 1;
   for(int outer = 1; outer <= ((calcLimit*2) - 2); outer++)         // calclimit is three by default
    {
      double total = 0.0;
      for(int inner = 0; inner <= lookBack; inner++)    // startBar is 0 by default; cogBars is 125 by default
       {
         total += MathPow(inner, outer);
       }
      ary_SX[outer + 1] = total;
    }
 }
//+------------------------------------------------------------------+
void load_b_aryValues(double& ary_b[], const int& lookBack, const int& workBar, const int& calcLimit)
 {  // this is the utility (only one) in the calculaion that aquires chart prices - others are dependent on the 'b' array values.
   for(int outer = 1; outer <= calcLimit; outer++)
    {
      double total = 0.0;
      for(int inner = workBar; inner <= workBar + lookBack; inner++)   // startBar is 0 by default; cogBars is 125 by default
       {
         int powerNum = inner-workBar;
         if(outer == 1)
            total += Close[inner];
         else
            total += Close[inner] * MathPow(powerNum, outer - 1);
       }
      ary_b[outer] = total;
    }
 }
//+------------------------------------------------------------------+
void initializeAI_ary(double& ary_AI[][],double& ary_SX[], const int& calcLimit)
 {
   for(int outer = 1; outer <= calcLimit; outer++)
    {
      for(int inner = 1; inner <= calcLimit; inner++)
       {
         int position = inner + outer - 1;
         ary_AI[inner][outer] = ary_SX[position];
       }
    }
 }
//+------------------------------------------------------------------+
void calculateGause(double& ary_ai[][],double& ary_b[],const int& calcLimit)
 {
   for(int outer = 1; outer <= calcLimit - 1; outer++)
    {
      int ai_idx = findAI_idx(ary_ai, outer, calcLimit);
      if(ai_idx == 0)
       {
         return;
       }
      if(ai_idx != outer)
       {
         tradePositions(ary_ai,ary_b, ai_idx, outer, calcLimit);
       }
      loadGause(ary_ai, ary_b, outer, calcLimit);
    }
 }
int findAI_idx(double& ary_ai[][], const int& outer, const int& calcLimit)
 {
   int ai_idx = 0; double largestVal = 0.0;
   for(int inner = outer; inner <= calcLimit; inner++)
    {
      if(MathAbs(ai[inner][outer]) > largestVal)
       {
         largestVal = MathAbs(ary_ai[inner][outer]);
         ai_idx = inner;
       }
    }
   return(ai_idx);
 }
void tradePositions(double& ary_ai[][], double& ary_b[], const int& ai_idx, const int& outer, const int& calcLimit)
 {
   double outerVal;
   for(int idx = 1; idx <= calcLimit; idx++)
    {
      outerVal = ary_ai[outer][idx];
      ary_ai[outer][idx] = ary_ai[ai_idx][idx];
      ary_ai[ai_idx][idx] = outerVal;
    }
   outerVal  = b[outer];
   b[outer]  = b[ai_idx];
   b[ai_idx] = outerVal;
 }
void loadGause(double& ary_ai[][], double& ary_b[], const int& outer, const int& calcLimit)
 {
   for(int range = outer + 1; range <= calcLimit; range++)
    {
      double aiQuotient = ary_ai[range][outer] / ary_ai[outer][outer];
      for(int idx = 1; idx <= calcLimit; idx++)
       {
         if(idx == outer)
            ary_ai[range][idx] = 0;
         else
            ary_ai[range][idx] = ary_ai[range][idx] - aiQuotient * ary_ai[outer][idx];
       }
      ary_b[range] = ary_b[range] - aiQuotient * ary_b[outer];
    }
 }
//+------------------------------------------------------------------+
void loadX_ary( double& x_ary[], double& b_ary[], double& ai_ary[][], const int& calcLimit)
 {
   x[calcLimit] = b[calcLimit] / ai[calcLimit][calcLimit];
   for(int outer = calcLimit - 1; outer >= 1; outer--)
    {
      double total = 0;
      for(int inner = 1; inner <= calcLimit - outer; inner++)
       {
         total        = total + ai_ary[outer][outer + inner] * x_ary[outer + inner];
         x_ary[outer] = (1 / ai_ary[outer][outer]) * (b_ary[outer] - total);
       }
    }
 }
//+------------------------------------------------------------------+
void loadCOG_Center( double& cogCenter[], double& x_ary[], const int& workBar, const int& lookBack, const int& calcLimit)
 {
   for(int outer = workBar; outer <= workBar + lookBack; outer++)  // drawBar == startBar is 0 by default; cogBars is 125 by default
    {
      double total = 0;
      int powerNum = outer-workBar;
      for(int inner = 1; inner <= calcLimit; inner++)
       {
         total += x_ary[inner + 1] * MathPow(powerNum, inner);
       }
      cogCenter[outer] = x_ary[1] + total;
    } 
 }
//+------------------------------------------------------------------+
double getSQ( const int& workBar, const int& lookBack, double& cogCntr[], const double& sqMultiplier)
 {
   double squares = 0.0;
   for(int idx = workBar; idx <= workBar + lookBack; idx++)  // drawBar is 0 by default; lookBack is is 125 by default
    {
      squares += MathPow(Close[idx] - cogCntr[idx], 2);  // why to the 2nd power, is it related to sqMultiplier being 2?
    }
   squares = MathSqrt(squares / (lookBack + 1)) * sqMultiplier;
   return(squares);
 }
//+------------------------------------------------------------------+
void loadSideBands( const int& workBar, const int& lookBack, const double& square, const double& deviation)
 {
   for(int idx = workBar; idx <= workBar + lookBack; idx++)  // drawBar == startBar is 0 by default; cogBars is 125 by default
    {
      cogBuff[COG_HIGH_SQ].indiBuff[idx]  = cogBuff[COG_CNTR].indiBuff[idx] + square;
      cogBuff[COG_LOW_SQ].indiBuff[idx]   = cogBuff[COG_CNTR].indiBuff[idx] - square;
      cogBuff[COG_HIGH_STD].indiBuff[idx] = cogBuff[COG_CNTR].indiBuff[idx] + deviation;
      cogBuff[COG_LOW_STD].indiBuff[idx]  = cogBuff[COG_CNTR].indiBuff[idx] - deviation;
    }
 }
//+------------------------------------------------------------------+
void setDrawStart(const int drawStart)
 {
   // enum ENUM_COG_BUFFS { COG_CNTR,     COG_HIGH_SQ,   COG_LOW_SQ,    COG_HIGH_STD,   COG_LOW_STD, endCOGBuffs};
   for( ENUM_COG_BUFFS i = 0; i < endCOGBuffs; i++)
    { // Sets the bar number (from the data beginning) from which the drawing of the given indicator line must start.
      SetIndexDrawBegin(i, drawStart);
    }
   msg = StringConcatenate("First draw bar: ",IntegerToString(drawStart),", Time: ",TimeToStr(Time[drawStart],TIME_DATE|TIME_MINUTES),".");
   Comment(msg);
 }
//+------------------------------------------------------------------+
void loadCogHistories(const int& idx)
 {  // enum ENUM_SAV_BUFFS { CNTR_SAV,     SQ_HIGH_SAVE,  SQ_LOW_SAVE,   STD_HIGH_SAVE,  STD_LOW_SAVE, endSaveBuffs};
   saveBuff[CNTR_SAV].indiBuff[idx]      = cogBuff[COG_CNTR].indiBuff[idx+1];
   saveBuff[SQ_HIGH_SAVE].indiBuff[idx]  = cogBuff[COG_HIGH_SQ].indiBuff[idx+1];
   saveBuff[SQ_LOW_SAVE].indiBuff[idx]   = cogBuff[COG_LOW_SQ].indiBuff[idx+1];
   saveBuff[STD_HIGH_SAVE].indiBuff[idx] = cogBuff[COG_HIGH_STD].indiBuff[idx+1];
   saveBuff[STD_LOW_SAVE].indiBuff[idx]  = cogBuff[COG_LOW_STD].indiBuff[idx+1];
 }
//+------------------------------------------------------------------+
//| End Indicator Routines                                           |
//+------------------------------------------------------------------+
void displayControl(const ENUM_COG_BAR& drawType)
 {  // enum ENUM_COG_BAR { NEW_BAR, FIXED_BAR } cogSource=NEW_BAR; 
   string dispString;
   switch (drawType)
    {
      case NEW_BAR:
         dispString = "Real-Time COG";
         ObjectDelete(cogBox);
         makeAlabel(cogLabel,dispString,20,20);
         break;
      default:  // is FIXED_BAR
         dispString = "Draw COG at Bar "+IntegerToString(iBarShift(Symbol(),Period(),cogTime))+":";
         makeAlabel(cogLabel,dispString,20,20);
         makeAnEditBox(cogBox,TimeToString(cogTime,TIME_DATE|TIME_MINUTES), 220, 40);
         break;
    }
 }
//+------------------------------------------------------------------+
void makeAlabel(const string& objName, const string dispText, const int xPos, const int yPos)
 {
   static long chartID = ChartID();
   int windowNum = WindowFind(shortName);
   if ( ObjectFind(chartID,objName) < 0 )
    {
      ObjectCreate(chartID, objName, OBJ_LABEL,             CHARTWINDOW, 0, 0);
      ObjectSetInteger(chartID, objName, OBJPROP_FONTSIZE,  14);
      ObjectSetString (chartID, objName, OBJPROP_FONT,      "Calibri");
      ObjectSetInteger(chartID, objName, OBJPROP_COLOR,     clrOrangeRed);
      ObjectSetInteger(chartID, objName, OBJPROP_CORNER,    CORNER_LEFT_LOWER);
      ObjectSetInteger(chartID, objName, OBJPROP_ANCHOR,    ANCHOR_LEFT_LOWER);
      ObjectSetInteger(chartID, objName, OBJPROP_BACK,      false);
      ObjectSetInteger(chartID, objName, OBJPROP_SELECTABLE,false);
      ObjectSetInteger(chartID, objName, OBJPROP_SELECTED,  false);
      ObjectSetInteger(chartID, objName, OBJPROP_HIDDEN,    true);
    }
   ObjectSetInteger(chartID, objName, OBJPROP_XDISTANCE,    xPos );
   ObjectSetInteger(chartID, objName, OBJPROP_YDISTANCE,    yPos );
   ObjectSetString (chartID, objName, OBJPROP_TEXT,         dispText );
}
//+------------------------------------------------------------------+
void makeAnEditBox(const string& objName, const string dispText, const int xPos, const int yPos)
 {
   static long chart_ID = ChartID();
   int windowNum = WindowFind(shortName);
   if( ObjectFind(chart_ID,objName)<0 )
    {
      ObjectCreate    (chart_ID, objName, OBJ_EDIT,            CHARTWINDOW, 0, 0);
      ObjectSetInteger(chart_ID, objName, OBJPROP_FONTSIZE,    10);
      ObjectSetString (chart_ID, objName, OBJPROP_FONT,        "Calibri");
      ObjectSetInteger(chart_ID, objName, OBJPROP_XSIZE,       120);
      ObjectSetInteger(chart_ID, objName, OBJPROP_YSIZE,       18);
      ObjectSetInteger(chart_ID, objName, OBJPROP_COLOR,       clrBlack);
      ObjectSetInteger(chart_ID, objName, OBJPROP_BORDER_COLOR,clrBlack);
      ObjectSetInteger(chart_ID, objName, OBJPROP_BGCOLOR,     clrWhite);
      ObjectSetInteger(chart_ID, objName, OBJPROP_ALIGN,       ALIGN_CENTER);
      ObjectSetInteger(chart_ID, objName, OBJPROP_CORNER,      CORNER_LEFT_LOWER);
      ObjectSetInteger(chart_ID, objName, OBJPROP_ANCHOR,      ANCHOR_LEFT_LOWER);
      ObjectSetInteger(chart_ID, objName, OBJPROP_READONLY,    false);
      ObjectSetInteger(chart_ID, objName, OBJPROP_BACK,        false);
      ObjectSetInteger(chart_ID, objName, OBJPROP_SELECTABLE,  false);
      ObjectSetInteger(chart_ID, objName, OBJPROP_SELECTED,    false);
      ObjectSetInteger(chart_ID, objName, OBJPROP_HIDDEN,      true);
    }
   ObjectSetInteger(chart_ID, objName, OBJPROP_XDISTANCE,      xPos);
   ObjectSetInteger(chart_ID, objName, OBJPROP_YDISTANCE,      yPos);
   ObjectSetString (chart_ID, objName, OBJPROP_TEXT,           dispText);
 }
//--------------------------------------------------------------------
datetime getCogBarGlobalValue(string editBoxName)
 {
   datetime globalValue;
   string globalName = getGlobalName(editBoxName);
   if( GlobalVariableCheck(globalName) )
    {
      globalValue = (int) NormalizeDouble(GlobalVariableGet(globalName),0);
    }
   else
    {
      int theBar = ((Bars-(bars_back+2))>1000)?1000:(Bars-(bars_back+2));
      globalValue = Time[theBar];
    }
   return(globalValue);
 }
string getGlobalName(const string& objName )
 {
   return(objName+IntegerToString(Period())+Symbol());
 }
//--------------------------------------------------------------------
ENUM_COG_BAR getCogSourceGlobalValue(string cogLabelName)
 {
   ENUM_COG_BAR globalValue;
   string globalName = getGlobalName(cogLabelName);
   if( GlobalVariableCheck(globalName) )
    {
      globalValue = (ENUM_COG_BAR) NormalizeDouble(GlobalVariableGet(globalName),0);
    }
   else
    {
      globalValue = NEW_BAR;
    }
   return(globalValue);
 }
//--------------------------------------------------------------------