//+------------------------Kenneth Suarez----------------------------+
//                   Expert Advisor MUFASA V2.1 - 2014
//                                                 
//                                                  
//                                                    Kenneth Suarez |
//+------------------------------------------------------------------+
#property copyright "Kenneth Suarez"
#property link      "hardmokeypc.hol.es"
#property version   "2.1"
#property strict

//Parametros editables
extern string text1="------EAR-Emufasa 2.1-------";
extern string text2="____________________________";
extern double Lots=0.11;
extern double StopLoss=350;
extern double TakeProfit=350;
extern string text30="Requisitos para abrir posiciones";
extern string text3="---------------------------------";
extern string text23="Es el valor minimo aceptado";
extern string text4="para una compra";
extern int RSIMaximo=69;
extern string text5="Es el valor maximo aceptado";
extern string text6="para una venta";
extern int RSIMinimo=32;
extern string text7="Es el valor minimo aceptado";
extern string text8="para una venta";

extern int FactorPossTicks=1; 
extern string text15="OTROS PARAMETROS";
extern int TrailingStop=0;
extern int MagicNumber=10001;
extern int Slippage=3;


datetime next_candle;

//+------------------------------------------------------------------+
//| expert initialization function                                   |
//+------------------------------------------------------------------+
int init()
  {
//----
   next_candle=Time[0]+Period();
//----
   return(0);
  }
//+------------------------------------------------------------------+
//| expert deinitialization function                                 |
//+------------------------------------------------------------------+
int deinit()
  {
//----
   
//----
   return(0);
  }
//+------------------------------------------------------------------+
//| expert start function                                            |
//+------------------------------------------------------------------+
int start()
  {
//----
   
   if(next_candle<=Time[0])
      {
         next_candle=Time[0]+Period();
         // New candle. Your trading functions here
         
         
          double MyPoint=Point;
   if(Digits==3 || Digits==5) MyPoint=Point*10;

   double TheStopLoss=0;
   double TheTakeProfit=0;
   if(TotalOrdersCount()>=0)
     {
     int result=0;     
       if((iBands(NULL,PERIOD_M30,19,2,0,PRICE_CLOSE,MODE_LOW,0)>Open[0])) // Here is your open Sell rule
        {
         result=OrderSend(Symbol(),OP_BUY,Lots,Ask,Slippage,0,0,"EAMUFASA - Kenneth Suarez",MagicNumber,0,Blue);
         if(result>0)
           {
            TheStopLoss=0;
            TheTakeProfit=0;
            if(TakeProfit>0) TheTakeProfit=Ask+TakeProfit*MyPoint;
            if(StopLoss>0) TheStopLoss=Ask-StopLoss*MyPoint;
            OrderSelect(result,SELECT_BY_POS);
            OrderModify(OrderTicket(),OrderOpenPrice(),NormalizeDouble(TheStopLoss,Digits),NormalizeDouble(TheTakeProfit,Digits),0,Green);
           }
        }   
      if((iMA(NULL,0,18,0,MODE_SMA,PRICE_CLOSE,0)<iMA(NULL,0,5,0,MODE_SMA,PRICE_CLOSE,0)) && (iDeMarker(NULL,0,14,0)>0.69) && (iRSI(NULL,0,14,PRICE_CLOSE,0)>69) && (iMA(NULL,0,1,0,MODE_SMA,PRICE_CLOSE,0)>iBands(NULL,0,17,2,0,PRICE_CLOSE,MODE_UPPER,0))) // Here is your open Sell rule
        {
         result=OrderSend(Symbol(),OP_SELL,Lots,Bid,Slippage,0,0,"EAMUFASA - Kenneth Suarez",MagicNumber,0,Red);
         if(result>0)
           {
            TheStopLoss=0;
            TheTakeProfit=0;
            if(TakeProfit>0) TheTakeProfit=Bid-TakeProfit*MyPoint;
            if(StopLoss>0) TheStopLoss=Bid+StopLoss*MyPoint;
            OrderSelect(result,SELECT_BY_POS);
            OrderModify(OrderTicket(),OrderOpenPrice(),NormalizeDouble(TheStopLoss,Digits),NormalizeDouble(TheTakeProfit,Digits),0,Green);
           }
        }
     }
   for(int cnt=0;cnt<OrdersTotal();cnt++)
     {
      OrderSelect(cnt,SELECT_BY_TICKET,MODE_TRADES);
      if(OrderType()<=OP_SELL && 
         OrderSymbol()==Symbol() && 
         OrderMagicNumber()==MagicNumber
         )
        {
         if(OrderType()==OP_BUY)
           {
            if((iMA(NULL,0,1,0,MODE_SMA,PRICE_CLOSE,0)>iBands(NULL,PERIOD_H2,18,2,0,PRICE_CLOSE,MODE_UPPER,0))) //here is the close buy rule
              {
               OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
              }
            if(TrailingStop>0)
              {
               if(Bid-OrderOpenPrice()>MyPoint*TrailingStop)
                 {
                  if(OrderStopLoss()<Bid-MyPoint*TrailingStop)
                    {
                     OrderModify(OrderTicket(),OrderOpenPrice(),Bid-TrailingStop*MyPoint,OrderTakeProfit(),0,Green);
                  
                    }
                 }
              }
           }
         else
           {
            if((iMA(NULL,0,1,0,MODE_SMA,PRICE_OPEN,0)<iBands(NULL,PERIOD_H1,15,2,0,PRICE_CLOSE,MODE_LOWER,0))) // here is the close sell rule
              {
               OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
              }
            
           }
        }
     }
  }
         
      
  
  
  // Contador de ordenes totales                                                |
int TotalOrdersCount()
  {
   int result=0;
   for(int i=0;i<OrdersTotal();i++)
     {
      OrderSelect(i,SELECT_BY_POS,MODE_TRADES);
      if(OrderMagicNumber()==MagicNumber) result++;

     }
   return (result);
  }
//+------------------------------------------------------------------+