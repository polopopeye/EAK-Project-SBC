//+------------------------------------------------------------------+
//|                                                  MA Cross EA.mq4 |
//|                       Copyright 2018-2019, Aldridge Software P/L |
//|                                             tel: +61 416 096 217 |
//|                               email: aldridge.infotech@gmail.com |
//+------------------------------------------------------------------+
#property copyright "Copyright 2018, Aldridge Software P/L"
#property link      "https:"
#property version   "1.00"
#property strict

enum ENUM_TESTER_SPEED {SUPER_FAST=0, FAST=25, MEDIUM=50, SLOW=75, SUPER_SLOW=200};
//#include <visualtestingtools.mq4>

extern double buy_target=0.01;     //Set buy target 
extern double sell_target=0.01;    //Sell target 

input double _risk=0.2;         //Max % of account to risk

input double max_lots=1;      //Max lot size for trade
input bool auto_close=true;   //Auto close trades 

input int _magic=123;            //EA Magic Number
extern int max_orders=1;         //Max active orders
extern int rsioma_min=25;
extern int rsioma_max=75;

extern int expire_in_minutes=15;
extern int sf=5;              //Osma smoothing factor
extern double max_dd=0.5; //Max % drawdown


// control amount of time that order will be active in -ve
// avoid having orders open for weeks but we don't want to close with large negative
extern double close_after=1440; //Close order if -ve after n hours
extern double close_neg=0.05; //-ve must be *LT this for close to be activated
extern bool new_code_activated=true; //run with new code activated?

extern double stddev_multi=2;
extern double fixed_tp;
extern ENUM_TESTER_SPEED speed=MEDIUM;
extern double lot_control=0.5;

bool NewsTime;
double pipdigits, sl, tp, sellstoploss, buystoploss, target_percent;
bool cross_dn, cross_up;
bool exit_con, result;
static int buyorders, sellorders, bars, _orders[13];
double qmp1, qmp2, rsioma1, rsioma2, rsioma5_1, rsioma5_2, sum1, smma1, smma2, smma;
static bool first_pass=true;
static double dd=0; //max $ drawdown
static double open_hours=0;
static double profit[13], square[13];

//-----------
int OnInit()
//-----------
{
//  vTerminalInit(); 
//  vHistoryInit(); 
//---
  double digits=MarketInfo(Symbol(),MODE_DIGITS);
  if(digits==2||digits==3) pipdigits=0.01;
  else if(digits==4||digits==5) pipdigits=0.0001;

// initialise _orders, profit and square arrays
   for(int i=0; i<=12; i++)
   {
      _orders[i]=0;
      profit[i] =0;
      square[i] =0;
   }
// calculate initial osma average
   calc_smma2();
//---
   return(INIT_SUCCEEDED);
}

//----------------
void calc_smma2()
//----------------
{
   int i=1;
   sum1=0;
   do
   {
      i++;
      sum1=sum1+iOsMA(NULL,0,12,26,9,PRICE_CLOSE,i);
   }
   while(i<=sf);
   smma1=sum1/sf;  
}

//------------------------------
void OnDeinit(const int reason)
//------------------------------
{

}

//------------
void OnTick()
//------------
{
 if(IsTesting()==true && IsVisualMode()==true) {
  for(int counter = speed; counter >0; counter--) {
   Comment(counter);
  }
 }
   
  if(Volume[0]<=1 && first_pass==false)
  {
  if(smma==0) 
    calc_smma2();
  smma2=smma;
  smma=(sum1-smma1+iOsMA(NULL,0,12,26,9,PRICE_CLOSE,1))/sf;
  }
  first_pass=false;

//process open orders
  if(Orders()>0)
  {
   if(exit()==true) close_open_order();
  }

//if no open orders check for entry condition
//--but not largest candle in last 20
   double big_bar=0;
   for(int i=0; i<20; i++)
   { 
      if(High[i]-Low[i]>big_bar) big_bar=High[i]-Low[i]; 
   }
   if(High[1]-Low[1]!=big_bar) 
   {  
      if(OrdersTotal()<max_orders && entry()==true) open_order(); 
   }
}

//-----------
int Orders()
//-----------
{
//Print("Orders");
   int num=0; 
    for(int i=OrdersTotal()-1;i>=0;i--)
    {
       if(OrderSelect(i,SELECT_BY_POS,MODE_TRADES))
       {
         if(OrderMagicNumber() == _magic && OrderProfit()!=0)
         {
            if(OrderType()==OP_BUY || OrderType()==OP_SELL) 
            {
               num++;
            } 
         }
      }
   }
  return(num);
} 

//----------
bool exit()
//----------
{
   // delete any pending orders this pair
   for(int i=OrdersTotal()-1; i>=0; i--)
   {
   if(OrderSelect(i,SELECT_BY_POS,MODE_TRADES))
   {
   if(OrderSymbol()==Symbol())
   {
   if(OrderType()==OP_SELLSTOP || OrderType()==OP_BUYSTOP)
   OrderDelete(OrderTicket());
   }
   }
   }
   if(Volume[0]<=1) 
   {
   double target_profit=calc_profit_stddev();

//vTerminalRefresh();
//vHistoryRefresh();   
   bars++;
   exit_con=false; 
   qmp1=iCustom(NULL,0,"QMP Filter",0,12,26,9,1,1,8,3,0,0,0,1); 
   qmp2=iCustom(NULL,0,"QMP Filter",0,12,26,9,1,1,8,3,0,0,1,1);
// Condition 1 - Profit target reached
    for(int i=OrdersTotal()-1;i>=0;i--)
    {
       if(OrderSelect(i,SELECT_BY_POS,MODE_TRADES))
       {
       if(OrderSymbol()==Symbol() && OrderMagicNumber() == _magic)
	      {
	      if(OrderType()==OP_BUY) target_percent=buy_target; else target_percent=sell_target;
   	   double val_percent=AccountBalance()*target_percent;
   	   double risk=_risk*AccountBalance();

         if(OrderProfit()>target_profit && target_profit!=0) return(true);
   	   if(OrderProfit()>=val_percent) return(true);
   	   if(OrderProfit()<0) {if(OrderProfit()*-1>dd) {//Print("Exit Drawdown"); 
   	   return(true); }}
   	   RefreshRates();
         double spread=ND((Ask-Bid)*(OrderLots()*100));
         int loop_count=1;
   	   if(OrderProfit()>0 && OrderType()==OP_BUY && smma<smma2) 
   	      {
//   	       Print("Exit SMMA - Profit=",OrderProfit()," Spread=",spread);
//   	       while(OrderTakeProfit()==0 && loop_count<10)
//   	         {
//   	          RefreshRates();
//   	          result=OrderModify(OrderTicket(),0,ND(OrderOpenPrice()+((Ask-Bid)*loop_count)),ND(OrderOpenPrice()+((Ask-Bid)*loop_count)),0,clrNONE);
//   	          loop_count++;
//   	         }
   	       return(true);
   	       }
   	   if(OrderProfit()>0 && OrderType()==OP_SELL && smma>smma2) 
   	      {
//   	       Print("Exit SMMA - Profit=",OrderProfit()," Spread=",spread);
//   	       while(OrderTakeProfit()==0 && loop_count<10)
//   	         {
//   	          RefreshRates();
//   	          result=OrderModify(OrderTicket(),0,ND(OrderOpenPrice()-((Ask-Bid)*loop_count)),ND(OrderOpenPrice()-((Ask-Bid)*loop_count)),0,clrNONE);
//   	          loop_count++;
//   	         }
             return(true);
            }
   	   if(OrderProfit()>(AccountBalance()*fixed_tp)) {//Print("Exit % account profit");
   	    return(true);}
   	   
// if order open *GT max time and -ve 
         open_hours=open_hours+(Period()/60);
//         Print("Open hours=",open_hours);
         if(open_hours>close_after && OrderProfit()<0) {
//         Print("max hrs & -ve profit");
// calculate % -ve
         double neg_profit=MathAbs(OrderProfit()*-1);
         double neg_percent=(MathAbs(OrderProfit()*-1))/AccountFreeMargin();
//         Print("neg profit:",neg_profit," neg percent:",neg_percent," close:",close_neg); 
         if(neg_percent<=close_neg) 
         { //Print("Open time of ",open_hours," hours exceeded and -ve profit of ",neg_percent,"% *LE trigger of ",close_neg,"% - close order");
         return(true);}  
         }
  	   

   	   if(OrderType()==OP_BUY && qmp2!=2147483647 && OrderProfit()<0 && (bars<=2) && OrderTakeProfit()==0) // && bars<=2) 
   	   { 
   	      RefreshRates();
   	      OrderModify(OrderTicket(),0,0,ND(OrderOpenPrice()+(Ask-Bid)),0,clrNONE);
 	      }

   	   if(OrderType()==OP_SELL && qmp1!=2147483647 && OrderProfit()<0 && (bars<=2) && OrderTakeProfit()==0) // && bars<=2) 
   	   { 
   	      RefreshRates();
   	      OrderModify(OrderTicket(),0,0,ND(OrderOpenPrice()-(Ask-Bid)),0,clrNONE);
   	      }

         } 
       } 
     }
 }
return(exit_con);
} 
   
//----------------------
void close_open_order()
//----------------------
{
   bars=0; open_hours=0;
    for(int i=OrdersTotal()-1;i>=0;i--)
    {
       if(OrderSelect(i,SELECT_BY_POS,MODE_TRADES))
       {
       if(OrderSymbol()==Symbol() && OrderMagicNumber() == _magic)
   	      {
   	      string msg=("Close Order Alert: "+Symbol());
   	      if(!IsTesting() && auto_close!=true) {
   	      SendNotification(msg);
   	      SendMail(msg,msg); } else {
   	      RefreshRates();
   	      if(OrderType()==OP_BUY) result = OrderClose(OrderTicket(),OrderLots(),Bid,10,clrBlue);
   	      if(OrderType()==OP_SELL) result = OrderClose(OrderTicket(),OrderLots(),Ask,10,clrRed);
   	      if(!result) //Print("Error in OrderClose (exit_con). Error code=",GetLastError())
   	      ;
   	       }
              }
       }
    }
}

//-----------
bool entry()
//-----------
{
   if(Orders()==0) {
   cross_up=false; cross_dn=false;
   
   if(Volume[0]<=1 && !IsFriday())
   {
   qmp1=iCustom(NULL,0,"QMP Filter",0,12,26,9,1,1,8,3,0,0,0,1); 
   qmp2=iCustom(NULL,0,"QMP Filter",0,12,26,9,1,1,8,3,0,0,1,1); 
   rsioma1=iCustom(NULL,0,"RSIOMA",0,1);
   rsioma2=iCustom(NULL,0,"RSIOMA",0,2);
//   fxr_ob=iCustom(NULL,0,"FXR",1,1);
//   fxr_os=iCustom(NULL,0,"FXR",2,1);
      
   string qmp="X", buy="B", sell="S";
   if(qmp1!=2147483647) qmp="B";
   if(qmp2!=2147483647) qmp="S";
   if(qmp=="B"
     && (rsioma1>rsioma_min && rsioma1<rsioma_max)
//     && smma>smma2
//      && Ask>moving_avg
//      && fxr_ob!=0
	   )
	{

	cross_up=true;
	}
	   
	if(qmp=="S"
     && (rsioma1>rsioma_min && rsioma1<rsioma_max) 
//     && smma<smma2 
//      && Bid<moving_avg  
//      && fxr_os!=0 
	   )
	{
	cross_dn=true;
   }
	}

	if(cross_up) return(true); 
	if(cross_dn) return(true); 
	
   }
return(false);
}

//----------------
void open_order()
//----------------
{
   
   datetime et = TimeCurrent()+(expire_in_minutes*60);

    double ask=High[1]; //+ (MarketInfo(Symbol(), MODE_SPREAD)*pipdigits);
    double bid=Low[1]; //-(MarketInfo(Symbol(), MODE_SPREAD)*pipdigits);
    double spread=Ask-Bid;
    int count=0;
//   if(cross_up) 
//   {
    tp=0; sl=0;
    RefreshRates();
    int tketb=OrderSend(Symbol(),OP_BUYSTOP,ND(Lot()),ND(ask),20,sl,tp,"MA Cross EA",_magic,et,clrBlue);
    if(tketb<=0) // OrderSend error - probably due to ask price being >= previous high. Add spread and try again
    {
      //Print("OrderSend Buy failed with error #",GetLastError());
      count=1;
      while(tketb<=0 && count<10)
      {
         RefreshRates();
         spread=Ask-Bid;
         ask=ask+spread;
         tketb=OrderSend(Symbol(),OP_BUYSTOP,ND(Lot()),ND(ask),20,sl,tp,"MA Cross EA",_magic,et,clrBlue);
         count++;
         if(tketb<=0) //Print("OrderSend BUY failed ",count," times with error #",GetLastError())
         ;
      } 
    } 
//   if(cross_dn) 
//   {
    tp=0; sl=0;
    RefreshRates();
    int tkets=OrderSend(Symbol(),OP_SELLSTOP,ND(Lot()),ND(bid),20,sl,tp,"Gurumarra FX",_magic,et,clrRed);
    if(tkets<=0) // OrderSend error - probably due to price being too close to bid. Subtract spread and try again
    {
     // Print("OrderSend Sell failed with error #",GetLastError());
      count=1;
      while(tkets<=0 && count<10)
      {
         RefreshRates();
         spread=Ask-Bid;
         bid=bid-spread;
         tkets=OrderSend(Symbol(),OP_SELLSTOP,ND(Lot()),ND(bid),20,sl,tp,"Gurumarra FX",_magic,et,clrRed);
         count++;
         if(tkets<=0) //Print("OrderSend SELL failed ",count," times with error #",GetLastError())
         ; 
      }
    }

    if(tketb<=0 || tkets<=0) close_pending_order();
}
//-----------
double Lot()
//-----------  
{
   string Symb   =Symbol();                    
   double One_Lot=MarketInfo(Symb,MODE_MARGINREQUIRED);
   double Min_Lot=MarketInfo(Symb,MODE_MINLOT);
   double Step   =MarketInfo(Symb,MODE_LOTSTEP);
   double Free   =AccountFreeMargin();
   double Lots_New=Min_Lot;
   
   static bool lotfirst_pass;
   if(lotfirst_pass!=true)
   {
      //Print("Symbol:",Symb," Free:$",Free," Lot:$",One_Lot," Min Lot:",Min_Lot," Step:",Step," Risk:",_risk);
      lotfirst_pass=true;
   }
            
   Lots_New=NormalizeDouble(MathFloor(Free*_risk/One_Lot/Step)*Step,2);
   Lots_New=ND(Lots_New*lot_control);
   if (Lots_New < Min_Lot) Lots_New=Min_Lot;
//   double _max_lots=AccountBalance()/10000;
//   if(_max_lots>20) _max_lots=20;
   if(Lots_New>max_lots) Lots_New=max_lots;

   dd=max_dd*Free; // Print("Drawdown=",dd);
 
   return(Lots_New);                               
}

//--------------
bool IsFriday()
//--------------
   {
      if (DayOfWeek()==5 && Hour()>=5) return(true);        //no trades after 12:00 Friday
      if (DayOfWeek()==1 && Hour()<=2) return(true);         //and let market settle first hour Monday
      
      return(false);
   }

//-------------------------
void close_pending_order()
//-------------------------
{
   // delete any pending orders this pair
   for(int i=OrdersTotal()-1; i>=0; i--)
   {
   if(OrderSelect(i,SELECT_BY_POS,MODE_TRADES))
   {
   if(OrderSymbol()==Symbol())
   {
   if(OrderType()==OP_SELLSTOP || OrderType()==OP_BUYSTOP)
   OrderDelete(OrderTicket());
   }
   }
   }
}

//--------------------
double ND(double val)
//--------------------
{
   return(NormalizeDouble(val, Digits));
}

//-----------------------------
double calc_profit_stddev()
//-----------------------------
{   
   double average_profit=0, squared_average=0, target_profit=0;
   int i=0;
   
// populate orders and profit array
   populate_orders();
   
   for(i=0; i<=12; i++)
   {
//      Print("Index=",i);
//      Print("Orders[i]=",_orders[i]);
      if(_orders[i]==0) break;
      if(OrderSelect(_orders[i],SELECT_BY_TICKET,MODE_HISTORY)==true)
      {
         profit[i]=OrderProfit();
      }
   }

// get average profit last 13 orders

   for(i=0; i<=12; i++)
   {
      if(profit[i] == 0) {if(i>0) i--; break;}
      average_profit = average_profit+profit[i];
   }

   int divisor=i+1;
   if(divisor>13) divisor--;
//   Print("Divisor=",divisor);
   average_profit=average_profit/divisor;    //we have the average
//   Print("Average Profit:$",average_profit);
// calc the squares
   for(i=0; i<=12; i++)
   {
      if(profit[i] == 0) break;
      square[i] = profit[i]-average_profit;
      square[i] = square[i]*square[i];
   }
   
// calc average of the squares
   
   for(i=0; i<=12; i++)
   {
      if(profit[i] == 0) break;
      squared_average=squared_average+square[i];
   }
   divisor=i+1;
   squared_average=squared_average/divisor;
   
// calc standard deviation & target profit
   double std_dev=MathSqrt(squared_average);
   target_profit=average_profit+(stddev_multi*std_dev);
   
return(target_profit);
}

//-----------------
void roll_arrays()
//-----------------
{
   for(int i=1; i<=12; i++)
   {
      _orders[i-1]=_orders[i];
      profit[i-1]=profit[i];
      square[i-1]=square[i];
   }
   _orders[12]=0;
   profit[12] =0;
   square[12] =0;
}

//---------------------
void populate_orders()
//---------------------
{
   for(int i=1;i<=OrdersHistoryTotal();i++)
   {
      if(OrderSelect(i,SELECT_BY_POS,MODE_HISTORY)
      && OrderSymbol()==Symbol()
      && OrderMagicNumber()==_magic
      && OrderProfit()!=0)
      {
         add_history(OrderTicket());   
      }
   }
}

//---------------------------
void add_history(int ticket)
//---------------------------
{
   int i=0;
//   Print("Ticket=",ticket);
// get 1st empty array element
   for(i=0;i<=12;i++)
   {
//      Print("Index=",i," Ticket=",_orders[i]);
      if(_orders[i]==0 || _orders[i]==ticket) break;
   }
   if(i==13) i--;                 // No empty bucket
   if(i==12 && _orders[i]!=0) roll_arrays();
//   Print("Add History - Index:",i);
   _orders[i]=ticket;   
}