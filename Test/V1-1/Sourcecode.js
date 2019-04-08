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
extern double Lots=0.10;

extern int TrailingStop=0;
extern int MagicNumber=10001;
extern int Slippage=3;

//+------------------------------------------------------------------+
//    ADVANCED CONFIGURATION
//+------------------------------------------------------------------+
extern int Sizetrade=1000;
extern double Lotemin=0.10;

//+------------------------------------------------------------------+
//    ADVANCED CONFIGURATION
//+------------------------------------------------------------------+

extern int Valcom=600;
extern int Valven=-600;

extern int Valcercom=350;
extern int Valcerven=-350;

extern int limitc=80; //200
extern int limitv=-80;
extern int limitca=1; //600
extern int limitva=-1; //aqui el lio de al revez antes estaba a 0
extern int limitcb=-60; //1200
extern int limitvb=+60;



extern int limitcaa=250; //1200 (300)
extern int limitvaa=-250;
extern int limitcab=200; //600 (200)
extern int limitvab=-200;
extern int limitcac=100; //200 (100)
extern int limitvac=-100;


datetime next_candle;
//+------------------------------------------------------------------+
//    EAMufasa start function
//+------------------------------------------------------------------+
int init()
  {
//   next_candle=Time[0]+Period();
   next_candle=Time[0]+30;
   ObjectCreate(Symbol()+1,OBJ_LABEL,0,0,0,0); // Tendencia Bands
   ObjectCreate(Symbol()+2,OBJ_LABEL,0,0,0,0); //CCI Diario
   ObjectCreate(Symbol()+3,OBJ_LABEL,0,0,0,0); // Resistencia Top
   ObjectCreate(Symbol()+4,OBJ_LABEL,0,0,0,0); // Resistencia Bot
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


//+------------------------------------------------------------------+
//    Periodos a ajustar
//+------------------------------------------------------------------+

    int periodo1m15 = 1200;
    int periodo2m15 = 600;
    int periodo3m15 = 300;

    int periodo1m1 = 1200;
    int periodo2m1 = 600;
    int periodo3m1 = 100; //abrir operaciones a corto plazo

    int periodo1m5 = 1200;
    int periodo2m5 = 600;
    int periodo3m5 = 300;
//+------------------------------------------------------------------+
//    Variables Bollinger que definen la tendencia a largo plazo de 1d a 15d
//+------------------------------------------------------------------+

 double Bandamedio1m15 = iBands(Symbol(),15,periodo1m15,2.0,0,PRICE_MEDIAN,0,0);
 double Bandamedio2m15 = iBands(Symbol(),15,periodo2m15,2.0,0,PRICE_MEDIAN,0,0);
 double Bandamedio3m15 = iBands(Symbol(),15,periodo3m15,2.0,0,PRICE_MEDIAN,0,0);

 double Bandabajo1m15 = iBands(Symbol(),15,periodo1m15,2.0,0,PRICE_MEDIAN,2,0);
 double Bandabajo2m15 = iBands(Symbol(),15,periodo2m15,2.0,0,PRICE_MEDIAN,2,0);
 double Bandabajo3m15 = iBands(Symbol(),15,periodo3m15,2.0,0,PRICE_MEDIAN,2,0);

 double Bandaalto1m15 = iBands(Symbol(),15,periodo1m15,2.0,0,PRICE_MEDIAN,1,0);
 double Bandaalto2m15 = iBands(Symbol(),15,periodo2m15,2.0,0,PRICE_MEDIAN,1,0);
 double Bandaalto3m15 = iBands(Symbol(),15,periodo3m15,2.0,0,PRICE_MEDIAN,1,0);


//+------------------------------------------------------------------+
//   Variables que establecen la apertura m1 aperturas 1 h a 12h
//+------------------------------------------------------------------+

 double Bandamedio1m1 = iBands(Symbol(),1,periodo1m1,2.0,0,PRICE_MEDIAN,0,0);
 double Bandamedio2m1 = iBands(Symbol(),1,periodo2m1,2.0,0,PRICE_MEDIAN,0,0);
 double Bandamedio3m1 = iBands(Symbol(),1,periodo3m1,2.0,0,PRICE_MEDIAN,0,0);

 double Bandabajo1m1 = iBands(Symbol(),1,periodo1m1,2.0,0,PRICE_MEDIAN,2,0);
 double Bandabajo2m1 = iBands(Symbol(),1,periodo2m1,2.0,0,PRICE_MEDIAN,2,0);
 double Bandabajo3m1 = iBands(Symbol(),1,periodo3m1,2.0,0,PRICE_MEDIAN,2,0);

 double Bandaalto1m1 = iBands(Symbol(),1,periodo1m1,2.0,0,PRICE_MEDIAN,1,0);
 double Bandaalto2m1 = iBands(Symbol(),1,periodo2m1,2.0,0,PRICE_MEDIAN,1,0);
 double Bandaalto3m1 = iBands(Symbol(),1,periodo3m1,2.0,0,PRICE_MEDIAN,1,0);


//+------------------------------------------------------------------+
//   Variables que establecen la apertura m1 aperturas 6h a 1d
//+------------------------------------------------------------------+

 double Bandamedio1m5 = iBands(Symbol(),5,periodo1m5,2.0,0,PRICE_MEDIAN,0,0);
 double Bandamedio2m5 = iBands(Symbol(),5,periodo2m5,2.0,0,PRICE_MEDIAN,0,0);
 double Bandamedio3m5 = iBands(Symbol(),5,periodo3m5,2.0,0,PRICE_MEDIAN,0,0);

 double Bandabajo1m5 = iBands(Symbol(),5,periodo1m5,2.0,0,PRICE_MEDIAN,2,0);
 double Bandabajo2m5 = iBands(Symbol(),5,periodo2m5,2.0,0,PRICE_MEDIAN,2,0);
 double Bandabajo3m5 = iBands(Symbol(),5,periodo3m5,2.0,0,PRICE_MEDIAN,2,0);

 double Bandaalto1m5 = iBands(Symbol(),5,periodo1m5,2.0,0,PRICE_MEDIAN,1,0);
 double Bandaalto2m5 = iBands(Symbol(),5,periodo2m5,2.0,0,PRICE_MEDIAN,1,0);
 double Bandaalto3m5 = iBands(Symbol(),5,periodo3m5,2.0,0,PRICE_MEDIAN,1,0);

 //+------------------------------------------------------------------+
 //   CCI diario que detecta las posibles tendencias a largo plazo
 //+------------------------------------------------------------------+

  double CCIdiario = iCCI(Symbol(),1440,100,PRICE_MEDIAN,0);

  //+------------------------------------------------------------------+
  //   Resistances importante para fijar stoploss y takeprofit
  //+------------------------------------------------------------------+

double resbot = iCustom(Symbol(),60,"RES-SUP",1,0);
double restop = iCustom(Symbol(),60,"RES-SUP",3,0);

   // for(int cnt=0;cnt<OrdersTotal();cnt++)
    // {
     // OrderSelect(cnt,SELECT_BY_POS,MODE_TRADES);
//         if(OrderType()==OP_SELL)
 //          {
  //           if(iCCI(Symbol(),0,200,PRICE_MEDIAN,0)>100) //here is the close sell rule
   //           {
             //  OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
   //           }
//           }else{
//            if(iCCI(Symbol(),0,200,PRICE_MEDIAN,0)>limitc&&iCCI(Symbol(),0,600,PRICE_MEDIAN,0)>limitca&&iCCI(Symbol(),0,1200,PRICE_MEDIAN,0)>limitcb&&iBands(Symbol(),0,200,2.0,0,PRICE_MEDIAN,MODE_UPPER,0)<Ask&&iBands(Symbol(),0,100,2.0,0,PRICE_MEDIAN,MODE_UPPER,0)<Ask) // here is the close buy rule
 //             {
           //   OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);
//              }
//           }
//     }

   if(next_candle<=Time[0])
      {
         next_candle=Time[0]+Period();
         // New candle. Your trading functions here


          double MyPoint=Point;
   //if(Digits==3 || Digits==5) MyPoint=Point*10;


   ObjectSetText(Symbol()+3,"Resistencia Top"+restop,9,"Verdana",Green);
   ObjectSet(Symbol()+3,OBJPROP_CORNER,0);
   ObjectSet(Symbol()+3,OBJPROP_XDISTANCE,20);
   ObjectSet(Symbol()+3,OBJPROP_YDISTANCE,70);

   ObjectSetText(Symbol()+4,"Resistencia Bot"+resbot,9,"Verdana",Red);
   ObjectSet(Symbol()+4,OBJPROP_CORNER,0);
   ObjectSet(Symbol()+4,OBJPROP_XDISTANCE,20);
   ObjectSet(Symbol()+4,OBJPROP_YDISTANCE,90);

   if(TotalOrdersCount()>=0)
     {

     int result=0;
     int sentimientobandas=0;
     int sentimientocci=0;
     double resistenciabot=0;
     double resistenciatop=0;
// if(resbot<Ask){
//   resistenciabot=resbot;
// }else{
//   resistenciabot=0;
// }
// if(restop>Ask){
//   resistenciatop=restop;
// }else{
//   resistenciatop=0;
// }
    if(Bandamedio1m15<Bandamedio2m15&&Bandamedio2m15<Bandamedio3m15)//&&Ask>Bandamedio200) // Here is your open BUY rule
        {
   ObjectSetText(Symbol()+1,"Tendencia actual: ALCISTA",9,"Verdana",Blue);
   ObjectSet(Symbol()+1,OBJPROP_CORNER,0);
   ObjectSet(Symbol()+1,OBJPROP_XDISTANCE,20);
   ObjectSet(Symbol()+1,OBJPROP_YDISTANCE,20);

    sentimientobandas=1;//1 Compra


  }else{
    if(Bandamedio1m15>Bandamedio2m15&&Bandamedio2m15>Bandamedio3m15)//&&Ask<Bandamedio200) // Here is your open Sell rule
       {
    ObjectSetText(Symbol()+1,"Tendencia actual BAJISTA",9,"Verdana",Red);
    ObjectSet(Symbol()+1,OBJPROP_CORNER,0);
    ObjectSet(Symbol()+1,OBJPROP_XDISTANCE,20);
    ObjectSet(Symbol()+1,OBJPROP_YDISTANCE,20);
    sentimientobandas=2;//2 Venta

  }else{
    ObjectSetText(Symbol()+1,"Tendencia actual NEUTRAL",9,"Verdana",Orange);
    ObjectSet(Symbol()+1,OBJPROP_CORNER,0);
    ObjectSet(Symbol()+1,OBJPROP_XDISTANCE,20);
    ObjectSet(Symbol()+1,OBJPROP_YDISTANCE,20);

    sentimientobandas=0;//2 Venta
  }

  }

if(CCIdiario>99){
  ObjectSetText(Symbol()+2,"CCI Bloqueo: COMPRA",9,"Verdana",Blue);
  ObjectSet(Symbol()+2,OBJPROP_CORNER,0);
  ObjectSet(Symbol()+2,OBJPROP_XDISTANCE,20);
  ObjectSet(Symbol()+2,OBJPROP_YDISTANCE,40);
  sentimientocci=1;//Precio bajo se acerca compra
}else{
  if(CCIdiario<99){
    ObjectSetText(Symbol()+2,"CCI Bloqueo: VENTA",9,"Verdana",Red);
    ObjectSet(Symbol()+2,OBJPROP_CORNER,0);
    ObjectSet(Symbol()+2,OBJPROP_XDISTANCE,20);
    ObjectSet(Symbol()+2,OBJPROP_YDISTANCE,40);
    sentimientocci=2;//Precio alto se acerca venta
  }
}
if(sentimientobandas==1&&sentimientocci==1){
  if(Ask<Bandabajo3m1){
  OrderSend(Symbol(),OP_BUY,Lots,Ask,Slippage,0,restop,"V1",MagicNumber,0,Blue); //Compra
  }
}
if(sentimientobandas==2&&sentimientocci==2){
  if(Ask>Bandaalto3m1){
  OrderSend(Symbol(),OP_SELL,Lots,Bid,Slippage,0,resbot,"V1",MagicNumber,0,Red); //Venta
  }
}

ObjectSetText(Symbol()+5,"Posiciones Abiertas: "+OrdersTotal(),9,"Verdana",Red);
ObjectSet(Symbol()+5,OBJPROP_CORNER,0);
ObjectSet(Symbol()+5,OBJPROP_XDISTANCE,20);
ObjectSet(Symbol()+5,OBJPROP_YDISTANCE,120);

         for(int cnt=0;cnt<OrdersTotal();cnt++)
     {

      OrderSelect(cnt,SELECT_BY_POS,MODE_TRADES);

         if(OrderType()==OP_SELL)
           {
             if(sentimientocci==1&&sentimientobandas==1)//&&Ask>Bandaalto1200) //here is the close sell rule
              {
               OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
              }

           }else{
            if(sentimientocci==2&&sentimientobandas==2)//&&Ask<Bandabajo1200) // here is the close buy rule
              {
              OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);
              }

           }
     }

     }//FIN COND TOTAL ORDERS COUNT

      return(0);


  }

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
