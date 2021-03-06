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
extern double lotesinicial=2.0;
extern double minlotes=2.0;
extern double multiplicador = 1.0;
//+------------------------------------------------------------------+
//    ADVANCED CONFIGURATION
//+------------------------------------------------------------------+
extern int TrailingStop=0;
extern int MagicNumber=10001;
extern int Slippage=3;


datetime next_candle;
//+------------------------------------------------------------------+
//    EAMufasa start function
//+------------------------------------------------------------------+
int init()
  {
//   next_candle=Time[0]+Period();
   next_candle=Time[0]+30;
   ObjectCreate(Symbol()+1,OBJ_LABEL,0,0,0,0); // Rojo Momentum
   ObjectCreate(Symbol()+2,OBJ_LABEL,0,0,0,0); // Verde Momentum
   ObjectCreate(Symbol()+3,OBJ_LABEL,0,0,0,0); // MA_Mirror
   ObjectCreate(Symbol()+4,OBJ_LABEL,0,0,0,0); // MA_Mirror
   ObjectCreate(Symbol()+5,OBJ_LABEL,0,0,0,0); //Contador de operaciones



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

//Si tendenciasar==1 y tendenciamirror==1 y tendenciamirror2==1 y optimocompra==1 compra
//Si tendenciasar==2 y tendenciamirror==2 y tendenciamirror2==2 y optimoventa==1 venta
//+------------------------------------------------------------------+
//    Tendencia Corto
//+------------------------------------------------------------------+

double verdema = iMA(Symbol(),5,50,0,1,4,0);
double amarilloma = iMA(Symbol(),5,100,0,1,4,0);
double rojoma = iMA(Symbol(),5,200,0,1,4,0);

double verdema30 = iMA(Symbol(),60,50,0,1,4,0);
double amarilloma30 = iMA(Symbol(),60,100,0,1,4,0);
double rojoma30 = iMA(Symbol(),60,200,0,1,4,0);
int matend = 0;
int matend30 = 0;
if(rojoma<amarilloma&&amarilloma<verdema){
  matend = 1;
}
if(rojoma>amarilloma&&amarilloma>verdema){
  matend = 2;
}
if(rojoma30<amarilloma30&&amarilloma30<verdema30){
  matend30 = 1;
}
if(rojoma30>amarilloma30&&amarilloma30>verdema30){
  matend30 = 2;
}

double osma = iOsMA(Symbol(),5,50,100,200,4,0);
double xsuper5= iCustom(Symbol(),5,"xSuperTrend-Candles",10,10,4,0); //Compra Azul
double xsuper30= iCustom(Symbol(),30,"xSuperTrend-Candles",10,10,4,0); //Compra Azul
double xsuper60= iCustom(Symbol(),60,"xSuperTrend-Candles",10,10,4,0); //Compra Azul

double price = iMA(Symbol(),1,1,0,0,4,0);
int tendsuper =0;
int tendsuper30 =0;
 int tendsuper60 =0;
if(xsuper5>price){
  tendsuper=2;
}
if(xsuper5<price){
  tendsuper=1;
}
if(xsuper30>price){
  tendsuper30=2;
}
if(xsuper30<price){
  tendsuper30=1;
}
if(xsuper60>price){
  tendsuper60=2;
}
if(xsuper60<price){
  tendsuper60=1;
}


ObjectSetText(Symbol()+4,"2: "+price,9,"Verdana",Red);
ObjectSet(Symbol()+4,OBJPROP_CORNER,0);
ObjectSet(Symbol()+4,OBJPROP_XDISTANCE,120);
ObjectSet(Symbol()+4,OBJPROP_YDISTANCE,80);





//-------------------------------------------------------------------
//CONDICIONES COMPRA Y CIERRE DE OPERACIONES
//-------------------------------------------------------------------
int operacionabrir=0;
int operacioncerrar=0;

if(tendsuper==1&&matend==1&&osma>0&&matend30==1&&tendsuper30==1&&tendsuper60==1){//permitirop==1
  operacionabrir=1;
}
if(tendsuper==2&&matend==2&&osma<0&&matend30==2&&tendsuper30==2&&tendsuper60==1){//permitirop==2
  operacionabrir=2;
}

if(tendsuper==2&&matend30==2){//tendencialineas==2||||permitirop==2
  operacioncerrar=1;//cerrar compras
}
if(tendsuper==1&&matend30==1){//tendencialineas==1||||permitirop==1
  operacioncerrar=2;//cerrar ventas;
}

//VALORES DE TAKEPROFIT Y STOPLOSS (RESTOP Y RESBOT)
//------------------------------------------------------------------
// double stoplossp1v = iCustom(Symbol(),15,"SL_BW",1,0);








   if(next_candle<=Time[0])
      {
         next_candle=Time[0]+Period();
         // New candle. Your trading functions here


          double MyPoint=Point;
   //if(Digits==3 || Digits==5) MyPoint=Point*10;



   if(TotalOrdersCount()>=0&&TotalOrdersCount()<199)
     {


     int result=0;
     double resistenciabot=0;
     double resistenciatop=0;




     int posicionesabiertas =0;
     int posicionesabiertasc=0;
     int posicionesabiertasv=0;

              for(int cnt=0;cnt<OrdersTotal();cnt++)
          {

           OrderSelect(cnt,SELECT_BY_POS,MODE_TRADES);
int timeorder = TimeCurrent()-OrderOpenTime();

              if(OrderType()==OP_SELL&&OrderSymbol()==Symbol())
                {
                  posicionesabiertas++;//contador de operaciones en mercado actual
                  posicionesabiertasv++;
                 if(operacioncerrar==2&&OrderProfit()>0){//&&OrderProfit()>0
                  OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
                 }
                 if(timeorder>172800){
                  OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
                 }
                }
              if(OrderType()==OP_BUY&&OrderSymbol()==Symbol())
                  {
                    posicionesabiertas++;//contador de operaciones en mercado actual
                    posicionesabiertasc++;
                   if(operacioncerrar==1&&OrderProfit()>0){
                    OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
                   }
                   if(timeorder>172800){
                    OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
                   }
                  }

          }

               ObjectSetText(Symbol()+5,"PA: "+posicionesabiertas+" Comp: "+posicionesabiertasc+" Vent: "+posicionesabiertasv,9,"Verdana",Red);
               ObjectSet(Symbol()+5,OBJPROP_CORNER,0);
               ObjectSet(Symbol()+5,OBJPROP_XDISTANCE,20);
               ObjectSet(Symbol()+5,OBJPROP_YDISTANCE,120);
//+------------------------------------------------------------------+
//   Lotes gestion
//+------------------------------------------------------------------+
          double lotesfinal = lotesinicial*posicionesabiertas*multiplicador;
          if(lotesfinal<minlotes){
            lotesfinal= minlotes;
          }else{
            lotesfinal = lotesinicial*posicionesabiertas*multiplicador;
          }
//+------------------------------------------------------------------+
//   APERTURA CONDICIONES - condiciones para establecer operaciones
//+------------------------------------------------------------------+
if(posicionesabiertasc==0&&operacionabrir==1){
    OrderSend(Symbol(),OP_BUY,lotesfinal,Ask,Slippage,0,0,0,MagicNumber,0,Blue); //Compra
}

if(posicionesabiertasv==0&&operacionabrir==2){
  OrderSend(Symbol(),OP_SELL,lotesfinal,Bid,Slippage,0,0,0,MagicNumber,0,Red); //Venta
}













}





     }//FIN COND TOTAL ORDERS COUNT

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
