//+-------------------------------------------------------------------------------------------+
//|                                                                                           |
//|                                    Trade Levels.mq4                                       |
//|                                                                                           |
//+-------------------------------------------------------------------------------------------+
#property copyright "Copyright @ 2015 traderathome and qFish"
#property link      "email: traderathome@msn.com"
#property strict
/*---------------------------------------------------------------------------------------------
User Notes:

This indicator is coded to run on MT4 Build 600+.  It shows Trade Levels lines and labels for
trade entries (EP), for the average of entries (AV), and for selected take profit (TP) and
stop loss (SL), and it displays Profit/Loss labels for open and closed trades.  Everything is
based on MT4 orders executed.  A Summary follows.  Details are further below.

//+-------------------------------------------------------------------------------------------+
//|                                                                                           |
//|    - All trade datum is automatically obtained from MT4 orders, no manual inputs of       |
//|      price or quantity are provided except to display a trial TP and SL.                  |
//|    - Exacting line and label placements for all time frame charts is fully automated      |
//|      using new MQL4 "Chart_Scale" tracking.                                               |
//|    - Permits single side variable size entries.  These entries can then be closed at      |
//|      different times and at different prices.                                             |
//|    - Open and closed trades can be displayed on the same chart concurrently.              |
//|    - Displays can be based on micro-lots, mini-lots, or full lots with a simple "1-2-3"   |
//|      unit type input, making this applicable across the entire spectrum of forex          |
//|      traders, and can be used to protect privacy of trade/account true size.              |
//|    - The labels for EP Levels lines can be turned on/off for a cleaner chart when not     |
//|      needed.  When displayed, they include the number of units (of the units size         |
//|      input selection) traded at each EP.                                                  |
//|    - EP/AV/TP/SL lines can individually be full lines, or just tabs for a cleaner chart.  |
//|    - Price Dots at trade entries and exits improve visibility and can be resized.         |
//|    - Connecting lines can be shown between EPs and the current bid/ask price of open      |
//|      trades, and between the EPs and close prices of closed trades.  These lines are      |
//|      color coded to show if each specific trade is in profit or loss.                     |
//|    - PL Labels for open & closed trades show number of EPs, number of traded units,       |
//|      average pips and total pips.  PL account pct. and PL total money can be included.    |
//|    - The "yyyy.mm.dd hh:mm" start and end inputs can precisely define the time span       |
//|      for showing closed trades, either as a single group, or as separate groups.          |
//|    - Within the defined time span for showing closed trades, they can be shown as         |
//|      one single group of trades with one PL label, or as separate groups of trades with   |
//|      separate PL labels.                                                                  |
//|                                                                                           |
//+-------------------------------------------------------------------------------------------+

Displaying EP Levels -
   You can select to show EP Levels lines and labels.  The Levels lines span the chart to the
   current candle, followed by the Levels labels which include the EP number, price and
   quantity of units of the lot type input.  If you show the labels for the EP Levels lines,
   the AV, TP and SL lines will shift to the right to maintain good visibility.  You can show
   the EP Levels line a full line,or as a short mini-line or "tab".

Displaying Price Dots and Lines -
   For open trades you can show lines connecting the EPs to the current appropriate bid/ask
   price, color coded to represent if the trade is in profit or loss.  You can show at each
   entry price a Dot color coded to represent if the trade is long or short.  When the trade
   is closed the Dot is ringed with the color selected for closed trade rings.  This enables
   you to easily see, if a number of trade components remain active but some have been closed,
   which are the closed ones and which remain open.  The input "Dot_Size_12345" provides 5 Dot
   sizes to select from.

Displaying the AV Line -
   For open trades an AV Line is displayed.  It shows the rounded off average price for all
   open orders (even if varying in size), the number of open orders (separate EP events), and
   the number of open units of the type input.  You can show the AV Levels line as a full line,
   or as a short mini-line or "tab".

Displaying TP and SL Lines -
   For open trades the TP and SL lines associated with the MT4 orders are displayed.  You can
   override these values by putting other values into the External Inputs.  You might do this
   to temporarily to help you decide the values to place with your MT4 orders.  An asterisk
   appears in the TP and SL labels when you are displaying your override values as a reminder
   they are not the values derived from the MT4 orders.  You can show the TP/SL Levels line as
   full line, or as a short mini-line or "tab".  The pips displayed at TP/SL are the rounded
   off total pips of all the open units of your EPs of the type unit selected.  When the TP/SL
   is reached and the trade closes, the closed trade P/L might display differently from what
   the open trade PL label showed due to the rounding of the final average price which can
   involve some units closing at different, and sometimes better prices than intended.

Displaying Open Trade PL Label -
   The open trades PL Label is displayed in the lower right corner of the main chart window.
   It numbers the discrete EPs made, the total of open units of the type unit selected, the
   average pips PL for each of the open units, and the total pips PL for the units.  You can
   also include the PL Money Total and PL Account Percent.  The text changes colors between
   green and red for profit/loss in pips, not in money.  You can have a green text label with
   a few pips profit, but still be down in money due to commissions/swaps.....

       Be advised that the MT4 account "Profit" shown under the MT4 "Trade" tab might or might
       not already include adjustments for commissions and/or swaps (which can be positive or
       negative).  Contact your broker and learn what their MT4 account "Profit" consists of.

       It seems customary that brokers show gross "Profit", i.e., excluding adjustments for
       commissionos and swaps.  If this is the case, you can show net profit by setting the
       inputs "Include_Commissions_Adjustment" and "Include_Swaps_Adjustment" both to "true".
       This is their default setting.  If the broker already includes commission and swaps in
       "Profit", then these two inputs should be set to "false".

       The prime question is whether or not the broker MT4 Account "Profit" is gross profit
       (no adusjtments for commissions and swaps) or is net profit (after all adjustments
       for commissions and swaps).  Again, call your broker and learn what their MT4 account
       "Profit" consists of so you can set these two inputs correctly.

Displaying a Closed Trade -
   Just as with open trades, closed trades can be shown with Price Dots at entries and closes
   with connecting lines colored to show if closed with profit or loss.  The PL Label displays
   numbers of EPs closed, the total number of closed units of the type you input, the average
   pips PL for the unit type, and the total pips PL for the unit type.  You can also include
   PL Money Total and PL Account Percent, with or without adjusting for commissions and swaps.

   PL Labels appear above or below the last close price of a trade unit in the trade group
   based on whether the unit was closed below or above its' entry price.  You can raise or
   lower the PL label by increasing or decreasing the default offset input of "30" pips.

   There are five label height inputs allowing adjustment of PL labels for five separate
   trade groups.  The sequence 1-2-3-5-5 starts with the oldest trade group.  If more than
   five trade groups are to be shown, only the oldest five trade groups can have their PL
   labels adusted in offset.  The more recent trade groups will have PL labels the same
   height as the oldest trade group.  Obviously, it is better to limit the display of closed
   trade groups to no more than five, and best to just show one closed trade group at a time.

   Whether you intend to show all closed trades as a single group with one PL label, or as
   multiple groups with labels, you must specify the number of minutes backwards from current
   time within which all closed trades will display.  There are two way to do this:
   1. The simple way is to input the number of minutes to "Simple_Lookback_Time_Span", which
      by default is already set for one hour, an input of "60" minutes.  After one hour the
      display of a closed trade will disappear from your chart.  To continue to display it,
      simply increase this input, say from "60" to "600", to continue the display for a total
      of ten hours from the time the trade closed.
   2. The exacting method is to set the year/month/day/hour/minutes for the start or end, or
      both the start and end of the period for which you want closed trades to display.  This
      method takes precedence over any value entered for the "Simple_Lookback_Time_Span".
      These start/end inputs must be in their default state (yyyy.mm.dd hh:mm) for the simple
      method to work.  You can copy & paste the "yyyy.mm.dd hh:mm" (provided in the External
      Inputs) to these start/end inputs to return them to their default state.

   All the trades closed within the set time span will be displayed.  As mentioned already,
   you can display them either of two ways, as a single group or as multiple groups:
   1. To show trades as one group with one PL label, set "Show_Separate_Trade_Groups" to
      "false" (it is "false" by default).
   2. To show trades separately grouped with each group having its own PL label, then set
      "Show_Separate_Trade_Groups" to "true".  Now you must also define how to separate the
      individual groups using the input "__Min_Minutes_Btwn_Groups".  You do this is by
      specifying a minimum time span between the last closed trade of one group and the first
      closed trade of the next following group.  For all the groups to be shown, the time span
      to use is the one between the two groups with the shortest time between those last/first
      close events.  Specify the time in minutes slightly less than that minimum time span.

Selecting the Unit Type Input -
   The External Inputs start with "Show_Micro_Mini_Full_123" to input the unit type number
   that will determine how the units traded and the pips involved are displayed:
      1. Select "1":  Displays are in terms of micro-lots and micro-lot pips ($0.10 MOL).
      2. Select "2":  Displays are in terms of mini-lots and mini-lot pips ($1.00 MOL).
      3. Select "3":  Displays are in terms of full lots and full lot pips ($10.00 MOL).

   For example, if you input "3" for standard lots, but make an entry of a half lot
   (5 mini-lots), and price moves in your favor 10 pips, then your gain is 5 standard lot
   pips, not 10.  As another example, if you input "1" for micro-lots but make a entry of
   one mini-lot (equivalent to 10 micro-lots), and price moves 10 pips in your favor, then
   your gain is 100 micro-lot pips, not 10.

   Protecting your privacy is another feature of the unit type input.  For example, suppose
   there are three traders:
      1. This trader makes a single micro-lot trade and selects unit type "1".
      2. This trader makes a single mini-lot trade and selects unit type "2".
      3. This trader makes a single full lot trade and selects unit type "3".
   Due to the unit types selected, the three charts will display identical data, all being
   based on "1" unit traded of the unit type selected.  Anyone viewing all three charts
   will see nothing that identifies the actual unit type being traded, only that "1" unit
   has been traded. Units displayed can only be viewed as generic units because they are not
   revealed as being based on micro, mini or full lots traded.  The only way a viewer of the
   chart can know the unit type of the units shown is for the user to select to display
   PL Money Total in the PL Labels for open and closed trades.  Without this information, a
   viewer cannot know if units are lots with $10 pips, or mini-lots with $1.00 pips, or
   micro-lots with $0.10 pips (MOL, depending on each forex pair).

Setting Time Frames for Display of Indicator -
   The indicator can be turned on/off without removing it from the chart.  Also, you can
   select a chart TF above which this indicator will automatically not display.

Chart Properties Settings -
   For this indicator to properly display Chart properties/Common tab/chart on foreground
   must be uncheck!  If checked, then MT4 candles are on top of, and can partially or
   totally obscure the Price Dots and other things drawn by this indicator.

Changes from intitial release 05-30-2015 to second release 06-28-2015:
* Improved open trade PL label placement code for background and text within, and allowing
  left side placement in subwindow.
* Improved/expanded User Notes.
* Modified External Inputs for additonal clarity.

Changes from second release 06-28-2015 to third release 08-01-2015:
* Expanded User Notes on PL label profit.
* Limits placement of open trade PL label to lower right of main window.

                                                                    - Traderathome, 08-01-2015
-----------------------------------------------------------------------------------------------
Acknowlegements:

St3ve -        For intiating the change from manually filled datum to an MT4 orders driven
               product.  This was a milestone influence and effort, which transitioned the
               indicator from a enhancement for educational charts into a tool for traders.

qFish -        For generously devoting his time and programming skills to overhaul the core
               code of this indicator that handles the retrieval of MT4 orders for open and
               closed trades, to expand the "lookback" feature that identifies the closed
               trades to display, and to provide other indispensable features to this very
               sophisticated and complex indicator.

traderathome - For initating the Trade Levels indicator as an aid to presenting clear trade
               charts for educational purposes, and for tailoring the upgrades to maintain
               an easy to use, eye appealing product.

----------------------------------------------------------------------------------------------
Suggested Settings:           White Chart        Black Chart

EP_Level_Label                MediumBlue         C'094,150,253'
EP_Level_Line_                MediumBlue         C'064,133,208'
AV_Level_Label                DarkOrchid         C'205,072,238'
AV_Level_Line                 DarkOrchid         MediumOrchid
SL_Level_Label                C'213,000,000'     C'255,032,032'
SL_Level_Line                 C'052,160,101'     C'226,035,035'
TP_Level_Label                C'040,123,078'     C'046,186,046'
TP_Level_Line                 C'040,123,078'     C'015,168,084'
EP_Dot_Long                   C'008,084,223'     C'028,199,255'
EP_Dot_Short                  C'232,000,000'     C'255,128,128'
EP_Dot_Center                 White              Black
EP_Dot_Closed                 Black              White
CP_Dot_Center                 Yellow             Black
CP_Dot_Closed                 Black              Yellow
PL_Line_Trade_Positive        CornflowerBlue     C'028,199,255'
PL_Line_Trade_Negative        Salmon             C'255,128,128'
PL_Label_Background           C'255,255,185'     C'230,227,138'
PL_Label_Text_Positive        C'040,123,078'     C'040,123,078'
PL_Label_Text_Negative        C'213,000,000'     C'213,000,000'

---------------------------------------------------------------------------------------------*/


//+-------------------------------------------------------------------------------------------+
//| Indicator Global Inputs                                                                   |
//+-------------------------------------------------------------------------------------------+
#property indicator_chart_window

//User External Input Globals
extern string  Part_1                        = "Main Settings:";
extern bool    Indicator_On                  = true;
extern int     Show_Micro_Mini_Full_123      = 1;
extern bool    Show_Open_Trades              = true;
extern bool    Show_Closed_Trades            = true;
extern int     Display_Max_TF                = 1440;
extern string  TF_Choices                    = "1-5-15-30-60-240-1440-10080-43200";

extern string  __                            = "";
extern string  Part_2                        = "PL Label Settings:";
extern bool    Show_PL_Account_Percent       = false;
extern bool    Show_PL_Money_Total           = false;
extern bool    Include_Comissions_Adjustment = true;
extern bool    Include_Swaps_Adjustment      = true;

extern string  ___                           = "";
extern string  Part_3                        = "Open Trade Settings:";
extern bool    Show_EP_Labels                = true;
extern bool    Show_EP_Price_Dots            = true;
extern bool    Show_EP_PL_Lines              = true;
extern bool    __Subordinate_PL_Lines        = false;
extern bool    Show_Full_EP_Level_lines      = false;
extern bool    Show_Full_AV_Level_lines      = false;
extern bool    Show_Full_SL_Level_lines      = true;
extern bool    Show_Full_TP_Level_lines      = true;
extern double  Show_Trial_SL                 = 0;
extern double  Show_Trial_TP                 = 0;

extern string  ____                          = "";
extern string  Part_4                        = "Closed Trade Settings:";
extern bool    Show_Price_Dots               = true;
extern bool    Show_Price_Lines              = true;
extern bool    __Subordinate_Lines           = false;
extern int     Simple_Lookback_Time_Span     = 60;
extern string  Lookback_Exact_Start_Time     = "yyyy.mm.dd hh:mm";
extern string  Lookback_Exact_End_Time       = "yyyy.mm.dd hh:mm";
extern string  __Reset_via_Copy_Paste        = "yyyy.mm.dd hh:mm";
extern bool    Show_Separate_Trade_Groups    = false;
extern int     __Min_Minutes_Btwn_Groups     = 60;
extern int     __PL_Label_1_Adjust_Height    = 30;
extern int     __PL_Label_2_Adjust_Height    = 30;
extern int     __PL_Label_3_Adjust_Height    = 30;
extern int     __PL_Label_4_Adjust_Height    = 30;
extern int     __PL_Label_5_Adjust_Height    = 30;

extern string  _____                         = "";
extern string  Part_5                        = "Color Settings:";
extern color   EP_Level_Label                = MediumBlue;
extern color   EP_Level_Line                 = MediumBlue;
extern color   AV_Level_Label                = DarkOrchid;
extern color   AV_Level_Line                 = DarkOrchid;
extern color   SL_Level_Label                = C'213,000,000';
extern color   SL_Level_Line                 = C'228,089,082';
extern color   TP_Level_Label                = C'040,123,078';
extern color   TP_Level_Line                 = C'052,160,101';
extern color   EP_Dot_Long                   = C'008,084,223';
extern color   EP_Dot_Short                  = C'232,000,000';
extern color   EP_Dot_Center                 = White;
extern color   EP_Dot_Closed                 = Black;
extern color   CP_Dot_Center                 = Yellow;
extern color   CP_Dot_Closed                 = Black;
extern int     Dot_Size_12345                = 2;
extern color   PL_Line_Trade_Positive        = CornflowerBlue;
extern color   PL_Line_Trade_Negative        = Salmon;
extern color   PL_Label_Background           = C'255,255,185';
extern color   PL_Label_Text_Positive        = C'040,123,078';
extern color   PL_Label_Text_Negative        = C'213,000,000';

//Private Globals
bool     Deinitialized;
int      ordersTotal          = -1; //-1 = indy start and guarantees drawing at least once
double   Poin;                      //defined in init() to accommodate varying Point digits
string   Label_Style          = "Arial Narrow";
int      Label_Size           = 8;
string   Label_Style2         = "Courier New";
int      Label_Size2          = 9;
int      Chart_Scale;
datetime T0,T1,T2,T3,Ts,Ts1,Ts2,Tf,Tf1,Tf2;
int      cnr,x,y,W;
int      Price_Dot_Center_Size, Price_Dot_Normal_Size, Price_Dot_Ring_Size;
int      openEPs, orderType;
double   openMicroLots;
double   openTotalPips;
double   openProfit;
double   openComm,openSwap;
double   openSize;
double   openAvgPips;
double   openAvgPrice;
double   tpPrice,slPrice;
string   LOTstr,side;

//+-------------------------------------------------------------------------------------------+
//| Indicator De-initialization                                                               |
//+-------------------------------------------------------------------------------------------+
int deinit()
{
   int obj_total= ObjectsTotal();
   for(int k= obj_total; k>=0; k--)
   {
      string name= ObjectName(k);
      if(StringSubstr(name,0,7)=="[Trade]") {ObjectDelete(name);}
   }
   return(0);

}

//+-------------------------------------------------------------------------------------------+
//| Indicator Initialization                                                                  |
//+-------------------------------------------------------------------------------------------+
int init()
{
   // determine the current chart scale (chart scale number should be 0-5)
   Chart_Scale = ChartScaleGet();

   if(Show_Micro_Mini_Full_123 <1 || Show_Micro_Mini_Full_123 >3)
   {Show_Micro_Mini_Full_123 = 1;}

   // determine "Poin" used for proper decimal placement in open trade calculations
   Poin = Point*10;
   if((StringSubstr(Symbol(),0,6)=="XAUUSD")||(StringSubstr(Symbol(),0,4)=="GOLD")) {Poin=0.01;}
   else {if (StringSubstr(Symbol(),0,6) == "EURTRY") {Poin = 0.001;}
   else {if (StringSubstr(Symbol(),0,6) == "USDTRY") {Poin = 0.001;}
   else {if (StringSubstr(Symbol(),0,6) == "USDMXN") {Poin = 0.001;}
   else {if (StringSubstr(Symbol(),0,6) == "USDCZK") {Poin = 0.001;} }}}}

   Deinitialized = false;

   // initialze Dot size
   if(Dot_Size_12345<1 || Dot_Size_12345>5) {Dot_Size_12345= 1;}
   if(Dot_Size_12345== 1)
   {
      Price_Dot_Center_Size= 4;
      Price_Dot_Normal_Size= 8;
      Price_Dot_Ring_Size= 12;
   }
   else if(Dot_Size_12345== 2)
   {
      Price_Dot_Center_Size= 5;
      Price_Dot_Normal_Size= 10;
      Price_Dot_Ring_Size= 13;
   }
   else if(Dot_Size_12345== 3)
   {
      Price_Dot_Center_Size= 6;
      Price_Dot_Normal_Size= 11;
      Price_Dot_Ring_Size= 15;
   }
   else if(Dot_Size_12345== 4)
   {
      Price_Dot_Center_Size= 8;
      Price_Dot_Normal_Size= 15;
      Price_Dot_Ring_Size= 22;
   }
   else if(Dot_Size_12345== 5)
   {
      Price_Dot_Center_Size= 16;
      Price_Dot_Normal_Size= 31;
      Price_Dot_Ring_Size= 46;
   }
   
   return(0);
}

//+-------------------------------------------------------------------------------------------+
//| Indicator Start                                                                           |
//+-------------------------------------------------------------------------------------------+
int start()
{
   // If indicator "Off" or chart TF out of range, deinitialize only once, not every tick.
   if(!Indicator_On || Period() > Display_Max_TF)
   {
      if (!Deinitialized) {deinit(); Deinitialized = true;}
      return(0);
   }

   //If indicator is "ON" clear objects
   int obj_total= ObjectsTotal();
   for(int k= obj_total; k>=0; k--)
   {
      string name= ObjectName(k);
      if(StringSubstr(name,0,7)=="[Trade]") {ObjectDelete(name);}
   }

   // calculate every tick here
   if(Show_Open_Trades)
   {
      if(selectOpenFirstOrder())
      {
         applyChartScale();
         drawOpenTradeEPs();
         drawOpenTradeTPSL();
         drawOpenTradeAV();
         drawOpenTradePL();
      }
      else
      {
         deinit();
      }
   }
   if(Show_Closed_Trades)
   {
      applyChartScale();
      drawClosedTradeEPs();
   }

   return(0);
}

//+-------------------------------------------------------------------------------------------+
//| Subroutine: Returns true/false that first trade order for symbol is found                 |
//+-------------------------------------------------------------------------------------------+
bool selectOpenFirstOrder()
{
   bool selected = false;

   // find the first order of this symbol
   for(int i=0; i<OrdersTotal(); i++)
   {
      if(OrderSelect(i, SELECT_BY_POS, MODE_TRADES))
      {
         if(Symbol()==OrderSymbol() && (OrderType()==OP_BUY || OrderType()==OP_SELL)
         && OrderCloseTime()==0)
         {
            selected = true;
            tpPrice = OrderTakeProfit();
            slPrice = OrderStopLoss();
            orderType = OrderType();
            break;
         }
      }
   }

   return(selected);
}

//+-------------------------------------------------------------------------------------------+
//| Subroutine: Set line parameters based on Chart_Scale                                      |
//+-------------------------------------------------------------------------------------------+
void applyChartScale()
{
   //Set stop/start values for trade lines
   //With EP Levels lines & labels displayed
   //T1= EP lines stop/labels start
   //T2= TP/SL/AV lines stop/labels start (shifted right)
   //Without EP Levels lines & labels displayed
   //T3= TP/SL/AV lines stop/labels start (no right shift)
   //Ts= start of partial EP Levels line
   //Tf= end of partial EP Levels line
   //Ts2= start of partial AV/TP/SL line
   //Tf2= end of partial AV/TP/SL line

   T0=Time[0]; //all lines (anchor point)
   if(Chart_Scale == 0)
   {
      T1=Time[0]+(Period()*60*14);
      T2=Time[0]+(Period()*60*110);
      T3=Time[0]+(Period()*60*14);
      Ts= Time[0]+(Period()*60*15);
      Tf= Time[0]+(Period()*60*26);
      Ts2= Time[0]+(Period()*60*114);
      Tf2= Time[0]+(Period()*60*127);
   }
   else if(Chart_Scale == 1)
   {
      T1=Time[0]+(Period()*60*7);
      T2=Time[0]+(Period()*60*55);
      T3=Time[0]+(Period()*60*7);
      Ts= Time[0]+(Period()*60*7);
      Tf= Time[0]+(Period()*60*13);
      Ts2= Time[0]+(Period()*60*57);
      Tf2= Time[0]+(Period()*60*65);
   }
   else if(Chart_Scale == 2)
   {
      T1=Time[0]+(Period()*60*5);
      T2=Time[0]+(Period()*60*29);
      T3=Time[0]+(Period()*60*5);
      Ts= Time[0]+(Period()*60*5);
      Tf= Time[0]+(Period()*60*8);
      Ts2= Time[0]+(Period()*60*30);
      Tf2= Time[0]+(Period()*60*34);
   }
   else if(Chart_Scale == 3)
   {
      T1=Time[0]+(Period()*60*3);
      T2=Time[0]+(Period()*60*15);
      T3=Time[0]+(Period()*60*3);
      Ts= Time[0]+(Period()*60*3);
      Tf= Time[0]+(Period()*60*5);
      Ts2= Time[0]+(Period()*60*15);
      Tf2= Time[0]+(Period()*60*18);
   }
   else if(Chart_Scale == 4)
   {
      T1=Time[0]+(Period()*60*2);
      T2=Time[0]+(Period()*60*8);
      T3=Time[0]+(Period()*60*2);
      Ts= Time[0]+(Period()*60*2);
      Tf= Time[0]+(Period()*60*3);
      Ts2= Time[0]+(Period()*60*8);
      Tf2= Time[0]+(Period()*60*9);
   }
   else if(Chart_Scale == 5)
   {
      T1=Time[0]+(Period()*60*2);
      T2=Time[0]+(Period()*60*5);
      T3=Time[0]+(Period()*60*2);
      Ts= Time[0]+(Period()*60*2);
      Tf= Time[0]+(Period()*60*3);
      Ts2= Time[0]+(Period()*60*5);
      Tf2= Time[0]+(Period()*60*6);
   }

   return;
}

//+-------------------------------------------------------------------------------------------+
//| Subroutine: Draws open trades entry point (EP) lines, arrows, and labels.                 |
//+-------------------------------------------------------------------------------------------+
void drawOpenTradeEPs()
{
   openEPs = 0;
   string EPstr;
   int epNum = 1;

   for(int i=0; i<OrdersTotal(); i++)
   {
      if(OrderSelect(i, SELECT_BY_POS, MODE_TRADES))
      {
         if(Symbol()==OrderSymbol() && (OrderType()==OP_BUY || OrderType()==OP_SELL))
         {
            // define text for labels based on trade side
            if(OrderType()==OP_BUY) {side = " Long ";}
            else  {side = " Short";}

            // variables to be used
            double lots = 100* OrderLots();
            string size;
            if(Show_Micro_Mini_Full_123 == 1)
            {
               size = DoubleToStr(lots,2);
            }
            else if(Show_Micro_Mini_Full_123 == 2)
            {
               size = DoubleToStr(lots/10,2);
            }
            else if(Show_Micro_Mini_Full_123 == 3)
            {
               size = DoubleToStr(lots/100,2);
            }
            size = strRepeat("0",6-StringLen(size))+size;

            double openPrice = OrderOpenPrice();
            string zeroPad = ternaryStr(epNum<10,"0","");

            // EP Levels Lines
            if(Show_EP_Labels)
            {
               int R = true;
               string epLine = StringConcatenate("[Trade] EP ",zeroPad,epNum," Level Line");
               if(Show_Full_EP_Level_lines)
               {
                  ObjectCreate(epLine,OBJ_TREND,0,T1,openPrice,T0,openPrice);
               }
               else
               {
                  ObjectCreate(epLine,OBJ_TREND,0,Ts,openPrice,Tf,openPrice);
                  R = false;
               }                                             
            ObjectSet(epLine,OBJPROP_COLOR,EP_Level_Line);
            ObjectSet(epLine,OBJPROP_RAY,R);

            // EP Levels Labels
            string epLabel = StringConcatenate("[Trade] EP ",zeroPad,epNum," Level Label");
            EPstr = DoubleToStr(openPrice,Digits);
            if(StringLen(EPstr)==6) {EPstr= "0"+ EPstr;}
            EPstr = StringConcatenate(zeroPad,IntegerToString(epNum)+": ",EPstr,",  ",size);
            EPstr = StringConcatenate(strRepeat(" ",30),EPstr);
            ObjectCreate(epLabel,OBJ_TEXT,0,T1,openPrice);
            ObjectSetText(epLabel,EPstr,Label_Size,Label_Style,EP_Level_Label);  
            }

            // EP PL lines
            if(Show_EP_PL_Lines) {
            string epTargetLine = StringConcatenate("[Trade] EP ",epNum,
               " line from ",DoubleToStr(openPrice,Digits));
            double closePrice = OrderClosePrice();
            ObjectCreate(epTargetLine,OBJ_TREND,0,OrderOpenTime(),
               openPrice,Time[0],closePrice);
            ObjectSet(epTargetLine,OBJPROP_COLOR,ternaryColor(OrderProfit()<0,
               PL_Line_Trade_Negative,PL_Line_Trade_Positive));
            ObjectSet(epTargetLine,OBJPROP_STYLE,STYLE_DOT);
            if(__Subordinate_PL_Lines) {ObjectSet(epTargetLine, OBJPROP_BACK, true);}
            else {ObjectSet(epTargetLine,OBJPROP_BACK,false);}
            ObjectSet(epTargetLine,OBJPROP_RAY,false); }

            // EP Price Dots
            if(Show_EP_Price_Dots) {
            // Dots
            string epPriceDot1 = StringConcatenate("[Trade] EP ",epNum," dot");
            ObjectCreate(epPriceDot1,OBJ_TREND,0,OrderOpenTime(),openPrice,
               OrderOpenTime(),openPrice);
            ObjectSet(epPriceDot1,OBJPROP_STYLE,0);
            ObjectSet(epPriceDot1,OBJPROP_COLOR,ternaryInt(OrderType()==OP_BUY,
               EP_Dot_Long,EP_Dot_Short));
            ObjectSet(epPriceDot1,OBJPROP_WIDTH, Price_Dot_Normal_Size);
            // Centers
            string epPriceDot2 = StringConcatenate("[Trade] EP ",epNum," center");
            ObjectCreate(epPriceDot2, OBJ_TREND,0,OrderOpenTime(),openPrice,
               OrderOpenTime(),openPrice);
            ObjectSet(epPriceDot2, OBJPROP_STYLE, 0);
            ObjectSet(epPriceDot2, OBJPROP_WIDTH, Price_Dot_Center_Size);
            ObjectSet(epPriceDot2, OBJPROP_COLOR, EP_Dot_Center); }

            // bump counters
            epNum++;
            openEPs++;
         }
      }
   }

   return;
}

//+-------------------------------------------------------------------------------------------+
//| Subroutine: Draws open trade tp and sl                                                    |
//+-------------------------------------------------------------------------------------------+
void drawOpenTradeTPSL()
{
   // draw TP
   double tpPips;
   string TPstr1;
   string TPstr2;
   string TPstr3;
   string tpLine = "[Trade] TP Level";
   string tpLabel = "[Trade] TP Label";

   if(Show_Trial_TP!=0) {tpPrice = Show_Trial_TP;}

   if(tpPrice > 0)
   {
      tpPips= (NormalizeDouble((getAvgPriceOfOpenOrders()-tpPrice)/Poin,0))*openSize;
      tpPips= ternaryDbl(orderType==OP_BUY,-tpPips,tpPips);

      // draw TP line
      datetime Tx, Ty;
      int R = true;
      if(Show_EP_Labels)
      {
         if(Show_Full_TP_Level_lines)
         {
            Tx = T2; Ty = T0;
         }
         else
         {
            Tx = Ts2; Ty = Tf2;
            R = false;
         }
      }
      else
      {
         if(Show_Full_TP_Level_lines)
         {
            Tx = T3; Ty = T0;
         }
         else
         {
            Tx = Ts; Ty = Tf;
            R = false;
         }
      }
      ObjectCreate(tpLine,OBJ_TREND,0,Tx,tpPrice,Ty,tpPrice);
      ObjectSet(tpLine,OBJPROP_WIDTH,1);
      ObjectSet(tpLine,OBJPROP_COLOR,TP_Level_Line);
      ObjectSet(tpLine,OBJPROP_RAY,R);

      // draw TP label
      TPstr1 = DoubleToStr(tpPrice,Digits);
      if(StringLen(TPstr1)==6) {TPstr1 = "0"+ TPstr1;}
      TPstr2 = DoubleToStr(tpPips,0);
      if(Show_Trial_TP!=0) {TPstr2 = TPstr2 + "*";}
      if(tpPips > 0) {TPstr2 = "+" + TPstr2;}
      if(Show_EP_Labels)
      {
         ObjectCreate(tpLabel,OBJ_TEXT,0,T2,tpPrice);
         TPstr3 = StringConcatenate("TP: ",TPstr1,", p",TPstr2);
         TPstr3 = StringConcatenate(strRepeat(" ",28),TPstr3,strRepeat(" ",27-StringLen(TPstr3)));
         ObjectSetText(tpLabel,TPstr3,Label_Size2,Label_Style2,TP_Level_Label);
      }
      else
      {
         ObjectCreate(tpLabel,OBJ_TEXT,0,T3,tpPrice);
         TPstr3 = StringConcatenate("TP: ",TPstr1,", p",TPstr2);
         TPstr3 = StringConcatenate(strRepeat(" ",28),TPstr3,strRepeat(" ",27-StringLen(TPstr3)));
         ObjectSetText(tpLabel,TPstr3,Label_Size2,Label_Style2,TP_Level_Label);
      }
   }

   // draw SL
   double slPips;
   string SLstr1;
   string SLstr2;
   string SLstr3;
   string slLine = "[Trade] SL Level";
   string slLabel = "[Trade] SL Label";

   if(Show_Trial_SL!=0) {slPrice = Show_Trial_SL;}

   if(slPrice > 0)
   {
      slPips= (NormalizeDouble((getAvgPriceOfOpenOrders()-slPrice)/Poin,0))*openSize;
      slPips= ternaryDbl(orderType==OP_BUY,-slPips,slPips);

      // draw SL line
      datetime Tx, Ty;
      int R = true;
      if(Show_EP_Labels)
      {
         if(Show_Full_SL_Level_lines)
         {
            Tx = T2; Ty = T0;
         }
         else
         {
            Tx = Ts2; Ty = Tf2;
            R = false;
         }
      }
      else
      {
         if(Show_Full_SL_Level_lines)
         {
            Tx = T3; Ty = T0;
         }
         else
         {
            Tx = Ts; Ty = Tf;
            R = false;
         }
      }
      ObjectCreate(slLine,OBJ_TREND,0,Tx,slPrice,Ty,slPrice);
      ObjectSet(slLine,OBJPROP_WIDTH,1);
      ObjectSet(slLine,OBJPROP_COLOR,SL_Level_Line);
      ObjectSet(slLine,OBJPROP_RAY,R);

      // draw SL label
      SLstr1 = DoubleToStr(slPrice,Digits);
      if(StringLen(SLstr1)==6) {SLstr1 = "0"+ SLstr1;}
      SLstr2 = DoubleToStr(slPips,0);
      if(Show_Trial_SL!=0) {SLstr2 = SLstr2 + "*";}
      if(slPips > 0) {SLstr2 = "+" + SLstr2;}
      if(Show_EP_Labels)
      {
         ObjectCreate(slLabel,OBJ_TEXT,0,T2,slPrice);
         SLstr3 = StringConcatenate("SL: ",SLstr1,", p",SLstr2);
         SLstr3 = StringConcatenate(strRepeat(" ",28),SLstr3,strRepeat(" ",27-StringLen(SLstr3)));
         ObjectSetText(slLabel,SLstr3,Label_Size2,Label_Style2,SL_Level_Label);
      }
      else
      {
         ObjectCreate(slLabel,OBJ_TEXT,0,T3,slPrice);
         SLstr3 = StringConcatenate("SL: ",SLstr1,", p",SLstr2);
         SLstr3 = StringConcatenate(strRepeat(" ",28),SLstr3,strRepeat(" ",27-StringLen(SLstr3)));
         ObjectSetText(slLabel,SLstr3,Label_Size2,Label_Style2,SL_Level_Label);
      }
   }

   return;
}

//+-------------------------------------------------------------------------------------------+
//| Subroutine: Draws the average line and label positioned to the right of the ep labels     |
//+-------------------------------------------------------------------------------------------+
void drawOpenTradeAV()
{
   string AVstr1;
   string AVstr2;
   string AVstr3;
   double Avg_Price = getAvgPriceOfOpenOrders();
   string avLine = "[Trade] Av Level";
   string avLabel = "[Trade] Av Label";
   string fix = ", ";

   // draw AV line
   datetime Tx, Ty;
   int R = true;
   if(Show_EP_Labels)
   {
      if(Show_Full_AV_Level_lines)
      {
         Tx = T2; Ty = T0;
      }
      else
      {
         Tx = Ts2; Ty = Tf2;
         R = false;
      }
   }
   else
   {
      if(Show_Full_AV_Level_lines)
      {
         Tx = T3; Ty = T0;
      }
      else
      {
         Tx = Ts; Ty = Tf;
         R = false;
      }
   }
   ObjectCreate(avLine,OBJ_TREND,0,Tx,Avg_Price,Ty,Avg_Price);
   ObjectSet(avLine,OBJPROP_WIDTH,1);
   ObjectSet(avLine,OBJPROP_COLOR,AV_Level_Line);
   ObjectSet(avLine,OBJPROP_RAY,R);

   // draw AV label
   AVstr1 = DoubleToStr(Avg_Price,Digits);
   AVstr1 = strRepeat("0",7-StringLen(AVstr1))+ AVstr1;
   AVstr2 = StringConcatenate(openEPs,"<",LOTstr);

   if(Show_EP_Labels)
   {
      ObjectCreate(avLabel,OBJ_TEXT,0,T2,Avg_Price);
      AVstr3 = StringConcatenate("AV: ",AVstr1,fix,openEPs,"<",LOTstr,side);
      AVstr3 = StringConcatenate(strRepeat(" ",28),AVstr3,strRepeat(" ",27-StringLen(AVstr3)));
      ObjectSetText(avLabel,AVstr3,Label_Size2,Label_Style2,AV_Level_Label);
   }
   else//Show Without EP_Labels
   {
      ObjectCreate(avLabel,OBJ_TEXT,0,T3,Avg_Price);
      AVstr3 = StringConcatenate("AV: ",AVstr1,fix,openEPs,"<",LOTstr,side);
      AVstr3 = StringConcatenate(strRepeat(" ",28),AVstr3,strRepeat(" ",27-StringLen(AVstr3)));
      ObjectSetText(avLabel,AVstr3,Label_Size2,Label_Style2,AV_Level_Label);
   }

   return;
}

//+-------------------------------------------------------------------------------------------+
//| Subroutine: Draws open trade current P/L (with monies & percentage options)               |
//+-------------------------------------------------------------------------------------------+
void drawOpenTradePL ()
{
   // preclude "zero divide" error for closed trade
   if(AccountBalance() == 0) return;

   string PD=DoubleToStr(openAvgPips,1);
   if(openAvgPips >= 0) {PD = "+"+PD;}
   string PT=DoubleToStr(openTotalPips,1);
   if(openTotalPips >= 0) {PT = "+"+PT;}
   string PLstr;

   if(!Show_PL_Money_Total && !Show_PL_Account_Percent)
   {
      PLstr = StringConcatenate("PL: ",openEPs,"<",LOTstr," avg p",PD," = p",PT);
   }
   else //show pips together with $ or % or both
   {
      string A = StringConcatenate("PL: ",openEPs,"<",LOTstr," avg p",PD," = p",PT);
      string PR = DoubleToStr(openProfit,2);
      if(openProfit >= 0) {PR = "+"+PR;}
      string B = StringConcatenate(", $",PR);
      string C;
      string D;
      double pct = (openProfit/AccountBalance())*100;
      if(pct<0) {D= ", ";}
      else {D= ", +";}
      if(pct < 10) {C = StringConcatenate(D+DoubleToStr(pct,2),"%");}
      else {C = StringConcatenate(D+DoubleToStr(pct,1),"%");}
      if(Show_PL_Money_Total && !Show_PL_Account_Percent)
         {
            PLstr = A+B;
         }
      else if(!Show_PL_Money_Total && Show_PL_Account_Percent)
         {
            PLstr = A+C;
         }
      else if(Show_PL_Money_Total && Show_PL_Account_Percent)
         {
            PLstr = A+B+C;
         }
   }

   // show open trade PL label
   string open_BG = "[Trade] Open PL Label";
   ObjectCreate(open_BG,OBJ_LABEL,0,0,0);
   ObjectSet(open_BG,OBJPROP_CORNER,3);
   ObjectSet(open_BG,OBJPROP_XDISTANCE,0);
   ObjectSet(open_BG,OBJPROP_YDISTANCE,-5);
   ObjectSetText(open_BG,strRepeat("g",int(StringLen(PLstr)/2.7)),16,
     "Webdings",PL_Label_Background);

   // display P/L text
   string open_TX = "[Trade] Open PL Text";
   ObjectCreate(open_TX,OBJ_LABEL,0,0,0);
   ObjectSet(open_TX,OBJPROP_CORNER,3);
   ObjectSet(open_TX,OBJPROP_XDISTANCE,4);
   ObjectSet(open_TX,OBJPROP_YDISTANCE,2);
   ObjectSet(open_TX,OBJPROP_COLOR,ternaryColor(openTotalPips<0,
      PL_Label_Text_Negative,PL_Label_Text_Positive));
   ObjectSetText(open_TX,PLstr,Label_Size2,Label_Style2);

   return;
}

//+-------------------------------------------------------------------------------------------+
//| Subroutine: Returns the average price of all buy/sell entries, factoring in variable sizes|
//+-------------------------------------------------------------------------------------------+
// Takes into account the micro-lot size of each trade of all executed open buy/sell orders.
// Trade orders for the pair must be either all buy or all sell.
double getAvgPriceOfOpenOrders()
{  
   openMicroLots = 0;
   openTotalPips = 0;
   openProfit = 0;
   openComm = 0;
   openSwap = 0;
   openSize = 0;
   openAvgPips = 0;
   openAvgPrice = 0;
   double openpriceLotProduct = 0;

   for(int i=0; i<OrdersTotal(); i++)
   {
      if(OrderSelect(i, SELECT_BY_POS, MODE_TRADES))
      {
         if (Symbol() == OrderSymbol() && (OrderType() == OP_BUY || OrderType() == OP_SELL))
         {
            openMicroLots += OrderLots()*100;
            openpriceLotProduct += OrderOpenPrice()*(OrderLots()*100);
            if(OrderType()==OP_BUY) {openTotalPips += OrderLots()*100*(Bid-OrderOpenPrice())/Poin;}
            if(OrderType()==OP_SELL) {openTotalPips += OrderLots()*100*(OrderOpenPrice()-Ask)/Poin;}
            openProfit += OrderProfit();
            openComm += OrderCommission();
            openSwap += OrderSwap();
         }
      }
   }

   // apply selected adjustments to open trade PL
   if(Include_Comissions_Adjustment)  {openProfit += openComm;}
   if(Include_Swaps_Adjustment)  {openProfit += openSwap;}

   // use input lot type to get open trade size factors ("openSize" and "os") determining
   // for the PL label, the factored trade size and avg/total pips displayed
   // for the TP/SL labels, the factored pips at TP/SL displayed
   int os = 0;  if(Show_Micro_Mini_Full_123 == 1) {os=1;}
   else {if(Show_Micro_Mini_Full_123 == 2) {os=10;}
   else {if(Show_Micro_Mini_Full_123 == 3) {os=100;} }}
   openSize= openMicroLots/os;

   // use "openSize" to determine qty of units (LOTstr) to display in PL label
   // first, get the digits to the right of the decimal
   int lot0 = int (100 * openSize);
   int lot2 = lot0%10;
   int lot1 = lot0%100 - lot2;
   // next, use digits info to determine how many digits to display
   if((lot1==0) && (lot2==0)) {LOTstr=DoubleToStr(openSize,0);}
   else if (lot2==0) {LOTstr=DoubleToStr(openSize,1);}
   else {LOTstr=DoubleToStr(openSize,2);}

   // use "openSize" and "os" factors to get avg/total pips for PL label
   openTotalPips = openTotalPips/os;
   openAvgPips = openTotalPips/openSize;

   // get average price of open trade for PL label
   openAvgPrice = openpriceLotProduct/openMicroLots;

   // return the avg. price of the open trade
   if(openSize >0) {return(openAvgPrice);}

   else {return(0);}
}

//+-------------------------------------------------------------------------------------------+
//| Subroutine: Draws closed trade lines connecting EPs to closed bid/ask price               |
//+-------------------------------------------------------------------------------------------+
void drawClosedTradeEPs()
{
   int epNum = 1;
   int trNum = 0;
   int closedEPs = 0;
   double closedTotalPips = 0;
   double closedProfit = 0;
   double closedMicroLots = 0;
   datetime lastClosedTime = -1;
   double lastClosedPrice = -1;
   double openPrice =0;
   double closePrice =0;
   datetime openTime =0;
   datetime closeTime =0;

   for(int i=0; i<OrdersHistoryTotal(); i++)
   {
      if(OrderSelect(i, SELECT_BY_POS, MODE_HISTORY))
      {
         // calculate the time flag algorithm to display depending on what's filled
         bool tradeHistoryTimeFlag = EMPTY_VALUE;
         bool cst = StringFind(Lookback_Exact_Start_Time,"yyyy.mm.dd hh:mm")>=0;
         bool cet = StringFind(Lookback_Exact_End_Time,"yyyy.mm.dd hh:mm")>=0;
         if(cst && cet)    // if they are both not used
            tradeHistoryTimeFlag = ((TimeCurrent()-OrderCloseTime())/60)<Simple_Lookback_Time_Span;
         if(!cst && cet)   // if start only is used
            tradeHistoryTimeFlag = OrderCloseTime()>StrToTime(Lookback_Exact_Start_Time);
         if(!cst && !cet)  // if start and end is used
            tradeHistoryTimeFlag = OrderCloseTime()>StrToTime(Lookback_Exact_Start_Time)
            && OrderCloseTime()<StrToTime(Lookback_Exact_End_Time);
         if(Symbol()==OrderSymbol() && (OrderType()==OP_BUY || OrderType()==OP_SELL)
            && tradeHistoryTimeFlag)
         {
            // start the draw of a trade (group of components)
            orderType = OrderType();
            openPrice = OrderOpenPrice();
            closePrice = OrderClosePrice();
            openTime = OrderOpenTime();
            closeTime = OrderCloseTime();
            // determine if all trades to be displayed within the selected Lookback time
            // are to be displayed as one trade group (of various EPs) with one P/L label
            if(!Show_Separate_Trade_Groups)
            {
               lastClosedTime = closeTime;
               lastClosedPrice = closePrice;
               trNum = 1;
            }
            // determine if all trades to be displayed within the selected Lookback time
            // are to be displayed as separate trade groups (each of various EPs) with
            // separate group P/L labels
            else
            {
               // if the first trade close time for a trade group is more than the time
               // selected ("___Min_Minutes_Btwn_Groups") after the last trade close time
               // for the previous trade group, or if the trade side is opposite from the
               // previous trade, start the draw as a new trade group
               if((lastClosedTime < closeTime - 60*__Min_Minutes_Btwn_Groups) ||
                  (orderType != OrderType()))
               {
                  // draw the P/L label for the preceding trade (group of components)
                  if(closedMicroLots != 0)
                     drawClosedTradePL(lastClosedTime,lastClosedPrice,openPrice,closedEPs,
                        closedMicroLots,closedTotalPips,closedProfit,trNum);
                  // reset variables for new trade draw
                  lastClosedTime = closeTime;
                  lastClosedPrice = closePrice;
                  closedEPs = 0;
                  closedTotalPips = 0;
                  closedProfit = 0;
                  closedMicroLots = 0;
                  epNum=1;
                  trNum++;
               }
            }

            // configure "zeroPad" for use in string names
            string zeroPad = ternaryStr(epNum<10,"0","");

           // Price Lines
            if(Show_Price_Lines) {
            string cpLine = StringConcatenate("[Trade] EP ",zeroPad,epNum,
               " line begins ",DoubleToStr(openPrice,Digits),
               ", line ends ",DoubleToStr(closePrice,Digits),", trade ",trNum);
            ObjectCreate(cpLine,OBJ_TREND,0,datetime(openTime),openPrice,
               datetime(closeTime),closePrice);
            ObjectSet(cpLine,OBJPROP_COLOR,ternaryColor(OrderProfit()<0,
               PL_Line_Trade_Negative,PL_Line_Trade_Positive));
            ObjectSet(cpLine,OBJPROP_STYLE,STYLE_DOT);
            if(__Subordinate_Lines) {ObjectSet(cpLine, OBJPROP_BACK, true);}
            else {ObjectSet(cpLine, OBJPROP_BACK, false);}
            ObjectSet(cpLine,OBJPROP_RAY,false); }

            // Price Dots
            if(Show_Price_Dots) {
            // EP Closed Rings
            string epDot1 = StringConcatenate("[Trade] EP ",zeroPad,epNum,
               ", ring, trade ",trNum);
            ObjectCreate(epDot1, OBJ_TREND,0,OrderOpenTime(),openPrice,
               OrderOpenTime(),openPrice);
            ObjectSet(epDot1, OBJPROP_STYLE, 0);
            ObjectSet(epDot1, OBJPROP_WIDTH, Price_Dot_Ring_Size);
            ObjectSet(epDot1, OBJPROP_COLOR, EP_Dot_Closed);
            // EP Dots
            string epDot2 = StringConcatenate("[Trade] EP ",zeroPad,epNum,
               ", Dot, trade ", trNum);
            ObjectCreate(epDot2, OBJ_TREND, 0, OrderOpenTime(), openPrice,
               OrderOpenTime(), openPrice);
            ObjectSet(epDot2, OBJPROP_STYLE, 0);
            ObjectSet(epDot2, OBJPROP_WIDTH, Price_Dot_Normal_Size);
            ObjectSet(epDot2, OBJPROP_COLOR, ternaryInt(OrderType()==OP_BUY,
               EP_Dot_Long,EP_Dot_Short));
            // EP Centers
            string epDot3 = StringConcatenate("[Trade] EP ",zeroPad,epNum,
               ", ",DoubleToStr(openPrice,Digits),", trade ",trNum);
            ObjectCreate(epDot3, OBJ_TREND,0,OrderOpenTime(),openPrice,
               OrderOpenTime(),openPrice);
            ObjectSet(epDot3, OBJPROP_STYLE, 0);
            ObjectSet(epDot3, OBJPROP_WIDTH, Price_Dot_Center_Size);
            ObjectSet(epDot3, OBJPROP_COLOR, EP_Dot_Center);
            // CP Closed Rings
            string cpDot1 = StringConcatenate("[Trade] CP ",zeroPad,epNum,
               ", Dot, trade ", trNum);
            ObjectCreate(cpDot1, OBJ_TREND,0,datetime(closeTime),closePrice,
               datetime(closeTime), closePrice);
            ObjectSet(cpDot1, OBJPROP_STYLE, 0);
            ObjectSet(cpDot1, OBJPROP_WIDTH, Price_Dot_Ring_Size);
            ObjectSet(cpDot1, OBJPROP_COLOR, CP_Dot_Closed);
            // CP_Centers
            string cpDot2 = StringConcatenate("[Trade] CP ",zeroPad,epNum,
               ", ",DoubleToStr(closePrice,Digits),", trade ", trNum);
            ObjectCreate(cpDot2, OBJ_TREND,0,datetime(closeTime),closePrice,
               datetime(closeTime),closePrice);
            ObjectSet(cpDot2, OBJPROP_STYLE, 0);
            ObjectSet(cpDot2, OBJPROP_WIDTH, Price_Dot_Center_Size+2);
            ObjectSet(cpDot2, OBJPROP_COLOR, CP_Dot_Center); }

            // bump counters
            epNum++;
            closedEPs++;
            closedMicroLots += OrderLots()*100;
            if(closedMicroLots == 0) {return;}
            if(OrderType()==OP_BUY)
            {
               closedTotalPips +=((OrderClosePrice()-OrderOpenPrice())/Poin)*(OrderLots()*100);
            }
            else
            {       
               closedTotalPips +=((OrderOpenPrice()-OrderClosePrice())/Poin)*(OrderLots()*100);
            }
            closedProfit += OrderProfit();
            if(Include_Comissions_Adjustment)  {closedProfit += OrderCommission();}
            if(Include_Swaps_Adjustment)  {closedProfit += OrderSwap();}
         }
      }
   }
   if(closedMicroLots == 0) {return;}

   // since there are no more orders in history to parse, draw PL for current trade drawn
   drawClosedTradePL(lastClosedTime, lastClosedPrice, openPrice, closedEPs, closedMicroLots,
      closedTotalPips, closedProfit, trNum);

   return;
}

//+-------------------------------------------------------------------------------------------+
//| Subroutine: Draws closed trade P/L (with monies & percentage options)                     |
//+-------------------------------------------------------------------------------------------+
void drawClosedTradePL (double t, double priceClosed, double priceOpened, int closedEPs,
   double closedMicroLots, double closedTotalPips, double closedProfit, int trNum)
{
   // preclude "zero divide" error for closed trade
   if(AccountBalance() == 0) return;

   // requirements for label
   double closedSize;
   string closedLOT;
   string PLstr;
   string PT;
   string PA=DoubleToStr(closedTotalPips/closedMicroLots,1);
   if(closedTotalPips/closedMicroLots >= 0) {PA = "+"+PA;}

   if(Show_Micro_Mini_Full_123 == 1)
   {
      closedSize = closedMicroLots;
      PT=DoubleToStr(closedTotalPips,1);
   }
   if(Show_Micro_Mini_Full_123 == 2)
   {
      closedSize = closedMicroLots/10;
      PT=DoubleToStr(closedTotalPips/10,1);
   }
   else if(Show_Micro_Mini_Full_123 == 3)
   {
      closedSize = closedMicroLots/100;
      PT=DoubleToStr(closedTotalPips/100,1);
   }
   if(StrToDouble(PT) >= 0) {PT = "+"+PT;}

   // get the "closedSize" digits to the right of the decimal
   int lot0 = int (100 * closedSize);
   int lot2 = lot0%10;
   int lot1 = lot0%100 - lot2;

   // use digits info to determine how many digits to display
   if((lot1==0) && (lot2==0)) {closedLOT=DoubleToStr(closedSize,0);}
   else if (lot2==0) {closedLOT=DoubleToStr(closedSize,1);}
   else {closedLOT=DoubleToStr(closedSize,2);}

   if(!Show_PL_Money_Total && !Show_PL_Account_Percent)
   {
      //Show EPs, lot factored units, average pips, & resultant P/L total pips
      PLstr= StringConcatenate("PL: ",closedEPs,"<",closedLOT," avg p",PA," = p",PT);
   }
   else //show pips together with $ or % or both
   {
      string A = StringConcatenate("PL: ",closedEPs,"<",closedLOT," avg p",PA," = p",PT);
      string PR = DoubleToStr(closedProfit,2);
      if(closedProfit >= 0) {PR = "+"+PR;}
      string B = StringConcatenate(", $",PR);  
      string C;
      string D;
      double pct = closedProfit/AccountBalance()*100;
      if(pct<0) {D= ", ";}
      else {D= ", +";}
      if(pct < 10) {C = StringConcatenate(D+DoubleToStr(pct,2),"%");}
      else {C = StringConcatenate(D+DoubleToStr(pct,1),"%");}
      if(Show_PL_Money_Total && !Show_PL_Account_Percent) {PLstr = A+B;}
      else if(!Show_PL_Money_Total && Show_PL_Account_Percent) {PLstr = A+C;}
      else if(Show_PL_Money_Total && Show_PL_Account_Percent) {PLstr = A+B+C;}
   }

   // shift label up/dn based on "Adjust_Label" input
   double labelprice;
   double adjustHeight;
   if(trNum<2 || trNum>3) {adjustHeight = __PL_Label_1_Adjust_Height;}
   else if(trNum == 2) {adjustHeight = __PL_Label_2_Adjust_Height;}
   else if(trNum == 3) {adjustHeight = __PL_Label_3_Adjust_Height;}
   else if(trNum == 4) {adjustHeight = __PL_Label_4_Adjust_Height;}
   else if(trNum == 5) {adjustHeight = __PL_Label_5_Adjust_Height;}
   if(Digits == 2) {adjustHeight= __PL_Label_1_Adjust_Height/10;}
   if(priceClosed > priceOpened)
      {labelprice = priceClosed + (adjustHeight*10*Point);}
   else {labelprice = priceClosed - (adjustHeight*10*Point);}

   // set P/L background to accomdate length of P/L text
   string closed_BG = StringConcatenate("[Trade] Closed PL Label ",priceClosed);
   ObjectCreate(closed_BG,OBJ_TEXT,0,datetime(t),labelprice);
   ObjectSetText(closed_BG,strRepeat("g",StringLen(PLstr)/2),11,
      "Webdings",PL_Label_Background);

   // display P/L text
   string closed_TX = StringConcatenate("[Trade] Closed PL Text ",priceClosed);
   ObjectCreate(closed_TX,OBJ_TEXT,0,datetime(t),labelprice);
   ObjectSet(closed_TX,OBJPROP_COLOR,ternaryColor(closedTotalPips<0,
      PL_Label_Text_Negative,PL_Label_Text_Positive));
   ObjectSetText(closed_TX,PLstr,Label_Size2,Label_Style2);

   return;
}

//+-------------------------------------------------------------------------------------------+
//| Subroutine: Returns decided upon string expression (2 or 3) to use                        |
//+-------------------------------------------------------------------------------------------+
string ternaryStr(bool expression1, string expression2, string expression3)
{
   string result = expression2;
   if(!expression1) {result = expression3;}
   return(result);
}

//+-------------------------------------------------------------------------------------------+
//| Subroutine: Returns decided upon integer expression (2 or 3) to use                       |
//+-------------------------------------------------------------------------------------------+
int ternaryInt(bool expression1, int expression2, int expression3)
{
   int result = expression2;
   if(!expression1) {result = expression3;}
   return(result);
}

//+-------------------------------------------------------------------------------------------+
//| Subroutine: Returns decided upon double expression (2 or 3) to use                        |
//+-------------------------------------------------------------------------------------------+
double ternaryDbl(bool expression1, double expression2, double expression3)
{
   double result = expression2;
   if(!expression1) {result = expression3;}   
   return(result);
}

//+-------------------------------------------------------------------------------------------+
//| Subroutine: Returns decided upon color expression (2 or 3) to use                         |
//+-------------------------------------------------------------------------------------------+
double ternaryColor(bool expression1, color expression2, color expression3)
{
   color result = expression2;
   if(!expression1) {result = expression3;}   
   return(result);
}

//+-------------------------------------------------------------------------------------------+
//| Subroutine: Returns string expression (s) repeated (n) times                              |
//+-------------------------------------------------------------------------------------------+
string strRepeat(string s, int n)
{
   string result = "";
   for(int i=0; i<n; i++) {result = result + s;}    
   return(result);
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