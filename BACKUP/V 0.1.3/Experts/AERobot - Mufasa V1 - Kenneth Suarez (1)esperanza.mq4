//+------------------------Kenneth Suarez-------------------------------+
//                   Expert Advisor MUFASA V1.2- 2014-2018
//
//Un Robot automatizado para abrir todas las operaciones optimas possibles
//de la grafica, i cerrarlas al nivel mas óptimo possible.
//
//Mufasa aprobecha inestabilidades en el mercado para abrir posiciones 
//optimas, que si se encuentran en tendencia son muy lucrativas.
//
//+---------------------------------------------------------------------+
//
//Parametros editables
extern double Lots=0.1;
extern double StopLoss=150;
extern double TakeProfit=650;

extern int TrailingStop=0;
extern int MagicNumber=10001;
extern int Slippage=3;
//+------------------------------------------------------------------+
//    ADVANCED CONFIGURATION
//+------------------------------------------------------------------+

extern int Valcom=900;
extern int Valven=-900;

extern int Valcercom=200;
extern int Valcerven=-200;

extern int limitc=200;
extern int limitv=-200;
extern int limitca=300;
extern int limitva=-300;

//+------------------------------------------------------------------+
//    EAMufasa start function
//+------------------------------------------------------------------+

void OnTick()
  { 
  
   double MyPoint=Point;
   if(Digits==3 || Digits==5) MyPoint=Point*10;

   double TheStopLoss=0;
   double TheTakeProfit=0;
   int contadorcompra=0;   
   int contadorventa=0;
   int m=TimeMinute(TimeCurrent());
   int Magicid=m;
   if(TotalOrdersCount()>=0)
     {
  
        
     int result=0;     
      if((iCCI(Symbol(),0,200,PRICE_OPEN,0)+iCCI(Symbol(),0,600,PRICE_OPEN,0)+iCCI(Symbol(),0,1200,PRICE_OPEN,0))<Valven&&iCCI(Symbol(),0,200,PRICE_OPEN,0)<limitv&&iCCI(Symbol(),0,600,PRICE_OPEN,0)<limitv&&iCCI(Symbol(),0,1200,PRICE_OPEN,0)<limitv) // Here is your open buy rule
        {
  
      result=OrderSend(Symbol(),OP_BUY,Lots,Ask,Slippage,0,0,"EAMUFASA",MagicNumber,0,Blue);

         if(result>0)
           {
            TheStopLoss=0;
            TheTakeProfit=0;
            if(TakeProfit>0) TheTakeProfit=Ask+TakeProfit*MyPoint;
            if(StopLoss>0) TheStopLoss=Ask-StopLoss*MyPoint;
            OrderSelect(result,SELECT_BY_POS);
            OrderModify(OrderTicket(),OrderOpenPrice(),NormalizeDouble(TheStopLoss,Digits),NormalizeDouble(TheTakeProfit,Digits),0,Green);
           }
         return(0);
         
        }


      if((iCCI(Symbol(),0,200,PRICE_OPEN,0)+iCCI(Symbol(),0,600,PRICE_OPEN,0)+iCCI(Symbol(),0,1200,PRICE_OPEN,0))>Valcom&&iCCI(Symbol(),0,200,PRICE_OPEN,0)>limitc&&iCCI(Symbol(),0,600,PRICE_OPEN,0)>limitc&&iCCI(Symbol(),0,1200,PRICE_OPEN,0)>limitc) // Here is your open Sell rule
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
         return(0);
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
            if((iCCI(Symbol(),0,200,PRICE_CLOSE,0)+iCCI(Symbol(),0,600,PRICE_CLOSE,0)+iCCI(Symbol(),0,1200,PRICE_CLOSE,0))>Valcercom) //here is the close buy rule
              {
               OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
               //OrderClose (OrderTicket(), OrderLots(), MarketInfo (OrderSymbol(), MODE_BID), 3, CLR_NONE);
              }
            if(TrailingStop>0)
              {
               if(Bid-OrderOpenPrice()>MyPoint*TrailingStop)
                 {
                  if(OrderStopLoss()<Bid-MyPoint*TrailingStop)
                    {
                     OrderModify(OrderTicket(),OrderOpenPrice(),Bid-TrailingStop*MyPoint,OrderTakeProfit(),0,Green);
                     
                     return(0);
                    }
                 }
              }
           }
         else
           {
            if((iCCI(Symbol(),0,200,PRICE_CLOSE,0)+iCCI(Symbol(),0,600,PRICE_CLOSE,0)+iCCI(Symbol(),0,1200,PRICE_CLOSE,0))<Valcerven) // here is the close sell rule
              {
              OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
             //  OrderClose (OrderTicket(), OrderLots(), MarketInfo (OrderSymbol(), MODE_ASK), 3, CLR_NONE);
              }
            if(TrailingStop>0)
              {
               if((OrderOpenPrice()-Ask)>(MyPoint*TrailingStop))
                 {
                  if((OrderStopLoss()>(Ask+MyPoint*TrailingStop)) || (OrderStopLoss()==0))
                    {
                     OrderModify(OrderTicket(),OrderOpenPrice(),Ask+MyPoint*TrailingStop,OrderTakeProfit(),0,Red);
                     return(0);
                    }
                 }
              }
           }
       }
     }
   return(0);
  }

//                Total orders Count                                                  |
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