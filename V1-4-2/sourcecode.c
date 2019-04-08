//+------------------------Kenneth Suarez-------------------------------+
//                   Expert Advisor MUFASA V1.2- 2014-2018
//
//Estrategia martingale, con un filtro a los 150 pips, con un multiplicador
//alto para recuperar las perdidas, las resistencias seran las mas bajas posibles.
// basado en el mercado.
//+---------------------------------------------------------------------+
extern double lotesinicial=0.1;
extern double multiplicador=4.0;
extern double gridposition=150; //pips on every new trade
extern double takeprofitpips=30; //pips to take profit
extern int maxposition=20;
extern bool autotakeprofit=False;
extern int TrailingStop=0;
extern int MagicNumber=10001;
extern int Slippage=3;

//+------------------------------------------------------------------+
//    ADVANCED CONFIGURATION
//+------------------------------------------------------------------+
extern int Sizetrade=1000;



datetime next_candle;
//+------------------------------------------------------------------+
//    EAMufasa start function
//+------------------------------------------------------------------+
int init()
  {
//   next_candle=Time[0]+Period();
   next_candle=Time[0]+30;
   ObjectCreate(Symbol()+1,OBJ_LABEL,0,0,0,0); // Tendencia Bands
   ObjectCreate(Symbol()+2,OBJ_LABEL,0,0,0,0); // Pips




   return(0);
  }
  int deinit()
  {
//----

//----
   return(0);
  }

void OnTick()
  {


//+------------------------------------------------------------------+
//    GRID
//+------------------------------------------------------------------+

//selecciona las posiciones que el robot ha abierto
int filter1v=0;
int filter1c=0;
int point_compat=1;
int closeallordersc=0;
int closeallordersv=0;
if(Digits==3||Digits==5)point_compat=10;
for(int pg=0;pg<OrdersTotal();pg++){
OrderSelect(pg,SELECT_BY_POS,MODE_TRADES);
if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()&&OrderComment()=="MUFASA"){

double DiffPipsv = MathAbs((NormalizeDouble(((Bid-OrderOpenPrice())/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);
  //printf(DiffPipsv);
  if(DiffPipsv>gridposition&&OrderProfit()<0){
    filter1v=1;
  }else{
    filter1v=0;
  }

if(DiffPipsv>takeprofitpips&&autotakeprofit==False&&OrderProfit()>0){
  closeallordersv=1;
}else{
  closeallordersv=0;
}


}
if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()&&OrderComment()=="MUFASA"){

  double DiffPipsc = MathAbs((NormalizeDouble(((OrderOpenPrice()-Ask)/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);
    //printf(DiffPipsc);
    //si desde la ultima posicion el precio a bajado y este es mas pequeño que los pips permitidos abrir nueva.
    if(DiffPipsc>gridposition&&OrderProfit()<0){
    filter1c=1;
    }else{
      filter1c=0;
    }

if(DiffPipsc>takeprofitpips&&autotakeprofit==False&&OrderProfit()>0){
  closeallordersc=1;
}else{
  closeallordersc=0;
}

}
ObjectSetText(Symbol()+2,"PipsC: "+DiffPipsc+" PipsV: "+DiffPipsv,9,NULL,Orange);
  ObjectSet(Symbol()+2,OBJPROP_CORNER,0);
  ObjectSet(Symbol()+2,OBJPROP_XDISTANCE,15);
  ObjectSet(Symbol()+2,OBJPROP_YDISTANCE,40);
}

//------------------------------------------------------------------
//VALORES DE TAKEPROFIT Y STOPLOSS (RESTOP Y RESBOT)
//------------------------------------------------------------------
double takeprofitp1v = iCustom(Symbol(),30,"SL_BW",0,0);//15 //30 //60 //240
double takeprofitp1c = iCustom(Symbol(),30,"SL_BW",1,0);//15 //30 //60 //240









   if(next_candle<=Time[0])
      {
         next_candle=Time[0]+Period();
         // New candle. Your trading functions here


          double MyPoint=Point;
   //if(Digits==3 || Digits==5) MyPoint=Point*10;


   if(TotalOrdersCount()>=0&&TotalOrdersCount()<199)
     {


     int result=0;
 //------------------------------------------------------------------
 // CONTADOR POSICIONES ABIERTAS POR ROBOT Y CIERRE
 //------------------------------------------------------------------
int posicionesabiertasrobotc = 0;
int posicionesabiertasrobotv = 0;

for(int cnt1=0;cnt1<OrdersTotal();cnt1++)
{
OrderSelect(cnt1,SELECT_BY_POS,MODE_TRADES);
if(OrderSymbol()==Symbol()&&OrderComment()=="MUFASA")
{
if(OrderType()==OP_SELL){

  if(closeallordersv==1&&autotakeprofit==False)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);//Aqui
  posicionesabiertasrobotv++;

}
}
if(OrderSymbol()==Symbol()&&OrderComment()=="MUFASA")
{
if(OrderType()==OP_BUY){
  if(closeallordersc==1&&autotakeprofit==False)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);//Aqui
  posicionesabiertasrobotc++;
}
}
}

//------------------------------------------------------------------
// GESTION LOTES
//------------------------------------------------------------------
int lotesposicionc=0;
int lotesposicionv=0;

if(posicionesabiertasrobotc==0){
  lotesposicionc=lotesinicial;
}else{
  lotesposicionc=lotesinicial*multiplicador*posicionesabiertasrobotc;
}
if(posicionesabiertasrobotv==0){
  lotesposicionv=lotesinicial;
}else{
  lotesposicionv=lotesinicial*multiplicador*posicionesabiertasrobotv;
}



//------------------------------------------------------------------
// ENVIO OPERACIONES
//------------------------------------------------------------------
if(posicionesabiertasrobotv==0){
  OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
}
if(posicionesabiertasrobotc==0){
  OrderSend(Symbol(),OP_BUY,lotesposicionv,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
}

if(posicionesabiertasrobotv>0&&filter1v==1&&posicionesabiertasrobotv<maxposition){
  OrderSend(Symbol(),OP_SELL,lotesposicionc,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);

}

if(posicionesabiertasrobotc>0&&filter1c==1&&posicionesabiertasrobotc<maxposition){
  OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
}


}//FIN TOTAL ORDERS 0 199






     }

      return(0);


  }


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
