//+------------------------------------------------------------------+
//|                                                           V2.mq4 |
//|                        Copyright 2018, MetaQuotes Software Corp. |
//|                                             https://www.mql5.com |
//+------------------------------------------------------------------+
#property copyright "Copyright 2018, MetaQuotes Software Corp."
#property link      "https://www.mql5.com"
#property version   "1.00"
#property strict
//+------------------------------------------------------------------+
//| Expert initialization function                                   |
//+------------------------------------------------------------------+

datetime next_candle;

int OnInit()
  {
  
   return(INIT_SUCCEEDED);

  }

 void OnTick()
  {
int limitv = -200;
int Valven =-600;
double Lots = 0.1;
int m=TimeSeconds(TimeCurrent());
if((iCCI(Symbol(),0,200,PRICE_OPEN,0)+iCCI(Symbol(),0,600,PRICE_OPEN,0)+iCCI(Symbol(),0,1200,PRICE_OPEN,0))<Valven&&iCCI(Symbol(),0,200,PRICE_OPEN,0)<limitv&&iCCI(Symbol(),0,600,PRICE_OPEN,0)<limitv&&iCCI(Symbol(),0,1200,PRICE_OPEN,0)<limitv) // Here is your open buy rule
        {
    int order = OrderSend(Symbol(),OP_BUY,Lots,Ask,0,0,0,"EAMUFASA",m,0,Blue);
            OrderSelect(order,SELECT_BY_TICKET);
            OrderModify(OrderTicket(),OrderOpenPrice(),NormalizeDouble(0,Digits),NormalizeDouble(0,Digits),0,Green);
           }  
  }