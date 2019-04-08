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
   ObjectCreate(Symbol()+6,OBJ_LABEL,0,0,0,0); //Texto takeprofit
   ObjectCreate(Symbol()+7,OBJ_LABEL,0,0,0,0); //ordenes abiertas en mercado actual
//   ObjectCreate(Symbol()+7,OBJ_LABEL,0,0,0,0); //resistencia bot a corto plazo



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


//    int periodo1m15 = 1200;
//    int periodo2m15 = 600;
//    int periodo3m15 = 300;

//    int periodo1m1 = 1200;
//    int periodo2m1 = 600;
//    int periodo3m1 = 100; //abrir operaciones a corto plazo

//    int periodo1m5 = 100;//
//    int periodo2m5 = 5;//
//    int periodo3m5 = 25;//



    int periodo1m15 = 1200;
    int periodo2m15 = 600;
    int periodo3m15 = 300;

    int periodo1m1 = 600;
    int periodo2m1 = 300;
    int periodo3m1 = 200; //abrir operaciones a corto plazo

    int periodo1m5 = 200;//
    int periodo2m5 = 100;//
    int periodo3m5 = 50;//
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
//   Variables que establecen la apertura m5 aperturas 6h a 1d
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
//1440 = 1dia - 240=4horas - 60=1Hora -
//double resbot = iCustom(Symbol(),240,"SL_BW",0,0);

//-------------------------------------Order positions--------------
double orderv1 = iCustom(Symbol(),1,"SL_BW",0,0);
double orderv2 = iCustom(Symbol(),5,"SL_BW",0,0);
double orderv3 = iCustom(Symbol(),15,"SL_BW",0,0);

double orderc1 = iCustom(Symbol(),1,"SL_BW",1,0);
double orderc2 = iCustom(Symbol(),5,"SL_BW",1,0);
double orderc3 = iCustom(Symbol(),15,"SL_BW",1,0);
double ventaoperacion = 0;
double compraoperacion = 0;

if(orderv1==EMPTY_VALUE||orderv1==EMPTY||orderv1==NULL||orderv1==WRONG_VALUE){
  if(orderv2==EMPTY_VALUE||orderv2==EMPTY||orderv2==NULL||orderv2==WRONG_VALUE){
    if(orderv3==EMPTY_VALUE||orderv3==EMPTY||orderv3==NULL||orderv3==WRONG_VALUE){
       ventaoperacion = 0;
    }else{
       ventaoperacion = orderv3;
    }
  }else{
    ventaoperacion = orderv2;
  }
}else{
  ventaoperacion = orderv1;
}

if(orderc1==EMPTY_VALUE||orderc1==EMPTY||orderc1==NULL||orderc1==WRONG_VALUE){
  if(orderc2==EMPTY_VALUE||orderc2==EMPTY||orderc2==NULL||orderc2==WRONG_VALUE){
    if(orderc3==EMPTY_VALUE||orderc3==EMPTY||orderc3==NULL||orderc3==WRONG_VALUE){
       compraoperacion = 0;
    }else{
       compraoperacion = orderc3;
    }
  }else{
    compraoperacion = orderc2;
  }
}else{
  compraoperacion = orderc1;
}


//------------------------------------------------------------------
double takeprofitp1v = iCustom(Symbol(),15,"SL_BW",0,0);
double takeprofitp2v = iCustom(Symbol(),30,"SL_BW",0,0);
double takeprofitp3v = iCustom(Symbol(),60,"SL_BW",0,0);
double takeprofitp4v = iCustom(Symbol(),240,"SL_BW",0,0);
double resbot = 0;
if(takeprofitp1v==EMPTY_VALUE||takeprofitp1v==EMPTY||takeprofitp1v==NULL||takeprofitp1v==WRONG_VALUE){
 if(takeprofitp2v==EMPTY_VALUE||takeprofitp2v==EMPTY||takeprofitp2v==NULL||takeprofitp2v==WRONG_VALUE){
   if(takeprofitp3v==EMPTY_VALUE||takeprofitp3v==EMPTY||takeprofitp3v==NULL||takeprofitp3v==WRONG_VALUE){
if(takeprofitp4v==EMPTY_VALUE||takeprofitp4v==EMPTY||takeprofitp4v==NULL||takeprofitp4v==WRONG_VALUE){
  resbot = 0;
}else{
  resbot = takeprofitp4v;
}
   }else{
    resbot = takeprofitp3v;
   }
 }else{
  resbot = takeprofitp2v;
 }
}else{
  resbot = takeprofitp1v;
}

//double restop = iCustom(Symbol(),240,"SL_BW",1,0);
double restop = 0;
double takeprofitp1c = iCustom(Symbol(),60,"SL_BW",1,0);
double takeprofitp2c = iCustom(Symbol(),120,"SL_BW",1,0);
double takeprofitp3c = iCustom(Symbol(),180,"SL_BW",1,0);
double takeprofitp4c = iCustom(Symbol(),240,"SL_BW",1,0);

if(takeprofitp1c==EMPTY_VALUE||takeprofitp1c==EMPTY||takeprofitp1c==NULL||takeprofitp1c==WRONG_VALUE){
 if(takeprofitp2c==EMPTY_VALUE||takeprofitp2c==EMPTY||takeprofitp2c==NULL||takeprofitp2c==WRONG_VALUE){
   if(takeprofitp3c==EMPTY_VALUE||takeprofitp3c==EMPTY||takeprofitp3c==NULL||takeprofitp3c==WRONG_VALUE){
if(takeprofitp4c==EMPTY_VALUE||takeprofitp4c==EMPTY||takeprofitp4c==NULL||takeprofitp4c==WRONG_VALUE){
  restop = 0;
}else{
  restop = takeprofitp4c;
}
   }else{
    restop = takeprofitp3c;
   }
 }else{
  restop = takeprofitp2c;
 }
}else{
  restop = takeprofitp1c;
}

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




   if(TotalOrdersCount()>=0&&TotalOrdersCount()<199)
     {


     int result=0;
     int sentimientobandas=0;
     int sentimientocci=0;
     double resistenciabot=0;
     double resistenciatop=0;

     //+------------------------------------------------------------------+
     //   CIERRE CONDICIONES - condiciones para establecer el cierre de operaciones
     //+------------------------------------------------------------------+

     ObjectSetText(Symbol()+5,"Posiciones Abiertas: "+OrdersTotal(),9,"Verdana",Red);
     ObjectSet(Symbol()+5,OBJPROP_CORNER,0);
     ObjectSet(Symbol()+5,OBJPROP_XDISTANCE,20);
     ObjectSet(Symbol()+5,OBJPROP_YDISTANCE,120);


     int posicionesabiertas =0;
              for(int cnt=0;cnt<OrdersTotal();cnt++)
          {

           OrderSelect(cnt,SELECT_BY_POS,MODE_TRADES);

           string fileNamecierre = cnt+".txt";
            string fileHandlecierre = FileOpen(fileNamecierre,FILE_CSV|FILE_READ | FILE_WRITE);
             if(fileHandlecierre==INVALID_HANDLE){
           printf("Handle Invalido, apertura error");
            }else{
                string cierreposicion = FileReadString(fileHandlecierre); //string archivoventa =
               FileClose(fileHandlecierre);

               }
     //printf(cierreposicion); //DEBUGEO
       // printf("cierre"+comprafile);



              if(OrderType()==OP_SELL&&OrderSymbol()==Symbol())
                {
                  posicionesabiertas++;//contador de operaciones en mercado actual

                 // double takeprofitc=OrderComment();
                  if(Ask<=cierreposicion){
                     OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
                  }
                  if(sentimientocci==1&&sentimientobandas==1)//&&Ask>Bandaalto1200) //here is the close sell rule
                   {
                    OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
                   }

                }
                if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()){
     posicionesabiertas++;
                 // double takeprofitc=OrderComment();
                  if(Ask>=cierreposicion){
                   OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);
                  }
                 if(sentimientocci==2&&sentimientobandas==2)//&&Ask<Bandabajo1200) // here is the close buy rule
                   {
                   OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);
                   }

                }
          }







//+------------------------------------------------------------------+
//   APERTURA CONDICIONES - condiciones para establecer operaciones
//+------------------------------------------------------------------+

    if(Bandamedio1m15<Bandamedio2m15&&Bandamedio2m15<Bandamedio3m15)//&&Ask>Bandamedio200) // Here is your open BUY rule
        {
sentimientobandas=1;//1 Compra
   ObjectSetText(Symbol()+1,"Tendencia actual: ALCISTA",9,"Verdana",Blue);
   ObjectSet(Symbol()+1,OBJPROP_CORNER,0);
   ObjectSet(Symbol()+1,OBJPROP_XDISTANCE,20);
   ObjectSet(Symbol()+1,OBJPROP_YDISTANCE,20);




  }else{
    if(Bandamedio1m15>Bandamedio2m15&&Bandamedio2m15>Bandamedio3m15)//&&Ask<Bandamedio200) // Here is your open Sell rule
       {
         sentimientobandas=2;//2 Venta
    ObjectSetText(Symbol()+1,"Tendencia actual BAJISTA",9,"Verdana",Red);
    ObjectSet(Symbol()+1,OBJPROP_CORNER,0);
    ObjectSet(Symbol()+1,OBJPROP_XDISTANCE,20);
    ObjectSet(Symbol()+1,OBJPROP_YDISTANCE,20);

  }else{
    sentimientobandas=0;//2 Venta

    ObjectSetText(Symbol()+1,"Tendencia actual NEUTRAL",9,"Verdana",Orange);
    ObjectSet(Symbol()+1,OBJPROP_CORNER,0);
    ObjectSet(Symbol()+1,OBJPROP_XDISTANCE,20);
    ObjectSet(Symbol()+1,OBJPROP_YDISTANCE,20);

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

ObjectSetText(Symbol()+7,"Numero de posiciones abiertas actuales"+posicionesabiertas,9,"Verdana",Red);
ObjectSet(Symbol()+7,OBJPROP_CORNER,0);
ObjectSet(Symbol()+7,OBJPROP_XDISTANCE,20);
ObjectSet(Symbol()+7,OBJPROP_YDISTANCE,190);


if(posicionesabiertas<=0){

//  if(sentimientobandas==2&&sentimientocci==2&&Bid>Bandaalto3m1&&Bid>Bandaalto3m5&&Bid>Bandaalto2m5&&Bid>Bandaalto1m5){
    if(sentimientobandas==2&&sentimientocci==2&&Bid>Bandaalto3m1&&Bid>Bandaalto3m5&&Bid>Bandaalto2m5&&Bid>Bandaalto1m5){
if(ventaoperacion==0){
  //buena para vender
}else{
  string operacionpendientev = Symbol()+"venta.txt";
  string operacionpendienteabrirv = FileOpen(operacionpendientev,FILE_CSV|FILE_READ | FILE_WRITE);
  string dataoperacionv = ventaoperacion;
             FileWrite(operacionpendienteabrirv,dataoperacionv);
             FileClose(operacionpendienteabrirv);
}

      //+------------------------------------------------------------------+
      //   CICLO FOR para nuevo take profit por nueva operacion VENTA
      //+------------------------------------------------------------------+
      for(int cnt1=0;cnt1<OrdersTotal();cnt1++)
      {
      OrderSelect(cnt1,SELECT_BY_POS,MODE_TRADES);
      if(OrderType()==OP_SELL&&OrderSymbol()==Symbol())
        {
      string fileNamenuevov1 = cnt1+".txt";
      string fileHandlenuevov1 = FileOpen(fileNamenuevov1,FILE_CSV|FILE_READ | FILE_WRITE);
                string datanuevov1 = resbot;
                FileWrite(fileHandlenuevov1,datanuevov1);
                FileClose(fileHandlenuevov1);

        }

      }
  }

     if(sentimientobandas==1&&sentimientocci==1&&Ask<Bandabajo3m1&&Ask<Bandabajo3m5&&Ask<Bandabajo2m5&&Ask<Bandabajo1m5){

       if(compraoperacion==0){
         //buena para vender
       }else{
         string operacionpendientec = Symbol()+"compra.txt";
         string operacionpendienteabrirc = FileOpen(operacionpendientec,FILE_CSV|FILE_READ | FILE_WRITE);
         string dataoperacionc = compraoperacion;
                    FileWrite(operacionpendienteabrirc,dataoperacionc);
                    FileClose(operacionpendienteabrirc);
       }



         //+------------------------------------------------------------------+
         //   CICLO FOR para nuevo take profit por nueva operacion COMPRA
         //+------------------------------------------------------------------+

         for(int cnt2=0;cnt2<OrdersTotal();cnt2++)
         {
         OrderSelect(cnt2,SELECT_BY_POS,MODE_TRADES);

         if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()){

         string fileNamenuevoc1 = cnt2+".txt";
         string fileHandlenuevoc1 = FileOpen(fileNamenuevoc1,FILE_CSV|FILE_READ | FILE_WRITE);
                 string datanuevoc1 = resbot;
                 FileWrite(fileHandlenuevoc1,datanuevoc1);
                 FileClose(fileHandlenuevoc1);
         }
         }
     }
}else{


  int permitirabrirv=0;
  int permitirabrirc=0;

      for(int cnt4=0;cnt4<OrdersTotal();cnt4++)
      {

      OrderSelect(cnt4,SELECT_BY_POS,MODE_TRADES);
 if(OrderSymbol()==Symbol()){
   string fileNamecierre4 = cnt4+".txt";
   string fileHandlecierre4 = FileOpen(fileNamecierre4,FILE_CSV|FILE_READ | FILE_WRITE);
   if(fileHandlecierre4==INVALID_HANDLE){
   printf("Handle Invalido, apertura error");
   }else{
     string cierreposicion4 = FileReadString(fileHandlecierre4); //string archivoventa =
    FileClose(fileHandlecierre4);
    }
 }

 ObjectSetText(Symbol()+6,"Takeprofit "+Symbol()+" : "+cierreposicion4,9,"Verdana",Red);
 ObjectSet(Symbol()+6,OBJPROP_CORNER,0);
 ObjectSet(Symbol()+6,OBJPROP_XDISTANCE,20);
 ObjectSet(Symbol()+6,OBJPROP_YDISTANCE,170);

      if(cierreposicion4<resbot)//modelo
      {
       permitirabrirv=2;//No permitir
      }else{
      permitirabrirv=1;//Permitir
      }
      if(cierreposicion4>restop)//modelo
      {
       permitirabrirc=2;//No permitir
      }else{
      permitirabrirc=1;//Permitir
      }
      //printf(cierreposicion4);//DEBUGEO

      }
//printf("permitir abrir v"+permitirabrirv);//DEBUGEO
//printf("permitir abrir c"+permitirabrirc);//DEBUGEO
  if(sentimientobandas==2&&sentimientocci==2&&Bid>Bandaalto3m1&&Bid>Bandaalto3m5&&Bid>Bandaalto2m5&&Bid>Bandaalto1m5&&permitirabrirv==1){

    if(ventaoperacion==0){
      //buena para vender
    }else{
      string operacionpendientev = Symbol()+"venta.txt";
      string operacionpendienteabrirv = FileOpen(operacionpendientev,FILE_CSV|FILE_READ | FILE_WRITE);
      string dataoperacionv = ventaoperacion;
                 FileWrite(operacionpendienteabrirv,dataoperacionv);
                 FileClose(operacionpendienteabrirv);
    }


      //+------------------------------------------------------------------+
      //   CICLO FOR para nuevo take profit por nueva operacion VENTA
      //+------------------------------------------------------------------+
      for(int cnt11=0;cnt11<OrdersTotal();cnt11++)
      {
      OrderSelect(cnt11,SELECT_BY_POS,MODE_TRADES);
      if(OrderType()==OP_SELL&&OrderSymbol()==Symbol())
        {
      string fileNamenuevov11 = cnt11+".txt";
      string fileHandlenuevov11 = FileOpen(fileNamenuevov11,FILE_CSV|FILE_READ | FILE_WRITE);
                string datanuevov11 = resbot;
                FileWrite(fileHandlenuevov11,datanuevov11);
                FileClose(fileHandlenuevov11);

        }

      }
  }

  if(sentimientobandas==1&&sentimientocci==1&&Ask<Bandabajo3m1&&Ask<Bandabajo3m5&&Ask<Bandabajo2m5&&Ask<Bandabajo1m5&&permitirabrirc==1){

           if(compraoperacion==0){
             //buena para vender
           }else{
             string operacionpendientec = Symbol()+"compra.txt";
             string operacionpendienteabrirc = FileOpen(operacionpendientec,FILE_CSV|FILE_READ | FILE_WRITE);
             string dataoperacionc = compraoperacion;
                        FileWrite(operacionpendienteabrirc,dataoperacionc);
                        FileClose(operacionpendienteabrirc);
           }

      //+------------------------------------------------------------------+
      //   CICLO FOR para nuevo take profit por nueva operacion COMPRA
      //+------------------------------------------------------------------+

      for(int cnt22=0;cnt22<OrdersTotal();cnt22++)
      {
      OrderSelect(cnt22,SELECT_BY_POS,MODE_TRADES);

      if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()){

      string fileNamenuevoc11 = cnt2+".txt";
      string fileHandlenuevoc11 = FileOpen(fileNamenuevoc11,FILE_CSV|FILE_READ | FILE_WRITE);
              string datanuevoc11 = resbot;
              FileWrite(fileHandlenuevoc11,datanuevoc11);
              FileClose(fileHandlenuevoc11);
      }
      }
  }

}

string fileNamecierre10 = Symbol()+"venta.txt";
string fileHandlecierre10 = FileOpen(fileNamecierre10,FILE_CSV|FILE_READ | FILE_WRITE);
if(fileHandlecierre10==INVALID_HANDLE){
printf("Handle Invalido, apertura error");
}else{
  string cierreposicion10 = FileReadString(fileHandlecierre10); //string archivoventa =
 FileClose(fileHandlecierre10);
 }
 if(cierreposicion10>Ask){
   OrderSend(Symbol(),OP_SELL,Lots,ventaoperacion,Slippage,0,0,0,MagicNumber,0,Red); //Venta resbot
  string fileNamev = OrderTicket()+".txt";
  string fileHandlev = FileOpen(fileNamev,FILE_CSV|FILE_READ | FILE_WRITE);
  string datav = resbot;
             FileWrite(fileHandlev,datav);
             FileClose(fileHandlev);

  string fileNamev10 = Symbol()+"venta.txt";
  string fileHandlev10 = FileOpen(fileNamev10,FILE_CSV|FILE_READ | FILE_WRITE);
  string datav10 = 0;
      FileWrite(fileHandlev10,datav10);
    FileClose(fileHandlev10);
 }


 string fileNamecierre11 = Symbol()+"compra.txt";
 string fileHandlecierre11 = FileOpen(fileNamecierre11,FILE_CSV|FILE_READ | FILE_WRITE);
 if(fileHandlecierre11==INVALID_HANDLE){
 printf("Handle Invalido, apertura error");
 }else{
   string cierreposicion11 = FileReadString(fileHandlecierre11); //string archivoventa =
  FileClose(fileHandlecierre11);
  }
  if(cierreposicion11<Bid){
    OrderSend(Symbol(),OP_BUY,Lots,compraoperacion,Slippage,0,0,0,MagicNumber,0,Blue); //Compra restop
    string fileNamec = OrderTicket()+".txt";

    string fileHandlec = FileOpen(fileNamec,FILE_CSV|FILE_READ | FILE_WRITE);
    string datac = restop;

      FileWrite(fileHandlec,datac);
      FileClose(fileHandlec);

      string fileNamec10 = Symbol()+"compra.txt";
      string fileHandlec10 = FileOpen(fileNamec10,FILE_CSV|FILE_READ | FILE_WRITE);
      string datac10 = 0;
          FileWrite(fileHandlec10,datac10);
        FileClose(fileHandlec10);
  }



//if(posicionesabiertas==0){
  //APERTURA QUE VA ABAJO

  //FIN

//}else{
//  printf("aqui ya seria mas de una operacion", );
//}








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
