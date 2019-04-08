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
//linia 404 establecida el resbot como 1500
//Parametros editables
//extern double Lots=0.10;//quitar
extern double lotesinicial=2.0;
extern double minlotes=0.10;
extern double multiplicador = 1.0;
extern int TrailingStop=0;
extern int MagicNumber=10001;
extern int Slippage=3;

//+------------------------------------------------------------------+
//    ADVANCED CONFIGURATION
//+------------------------------------------------------------------+
extern int Sizetrade=1000;

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

//Si tendenciasar==1 y tendenciamirror==1 y tendenciamirror2==1 y optimocompra==1 compra
//Si tendenciasar==2 y tendenciamirror==2 y tendenciamirror2==2 y optimoventa==1 venta
//+------------------------------------------------------------------+
//    Tendencia
//+------------------------------------------------------------------+


//    SAR oscilator 1440 1 dia - 240 4 horas
double sarvalor = iCustom(Symbol(),240,"SAR_oscillator",4,0);
//double sarvalorc = iCustom(Symbol(),240,"SAR_oscillator",0,0);
//double sarvalorv = iCustom(Symbol(),240,"SAR_oscillator",2,0);
double mamirrorrojo = iCustom(Symbol(),15,"MA_Mirror",150,0,0,0); //rojo si esta arriba compra o cerrar ventas
//si rojo esta abajo es venta
double mamirrorazul = iCustom(Symbol(),15,"MA_Mirror",150,0,1,0); //Azul si esta arriba es venta o cerrar compras
//si azul esta abajo es compra
double marojo = iMA(Symbol(),15,600,0,0,PRICE_MEDIAN,0);
double maamarillo = iMA(Symbol(),15,300,0,0,PRICE_MEDIAN,0);
double maverde = iMA(Symbol(),15,100,0,0,PRICE_MEDIAN,0);

int tendenciasar=0;
int tendenciamirror=0;
int tendenciamirror2=0;
int tendencialineas=0;
if(sarvalor>0){
tendenciasar=1; //alcista
}
if(sarvalor<0){
tendenciasar=2; //bajista
}

if(mamirrorrojo>0){
  tendenciamirror=1;//alcista, Compra
}else{
  if(mamirrorrojo<0){
    tendenciamirror=2;//bajista, Vende
  }
}
if(marojo<maamarillo&&maamarillo<maverde&&marojo<maverde){
tendencialineas=1;//alcista
}
if(marojo>maamarillo&&maamarillo>maverde&&marojo>maverde){
tendencialineas=2;//bajista
}

//------------------------------------------------------------------
//MEDIO PLAZO CIERRE
//------------------------------------------------------------------
double marojoc = iMA(Symbol(),5,600,0,0,PRICE_MEDIAN,0);
double maamarilloc = iMA(Symbol(),5,300,0,0,PRICE_MEDIAN,0);
double maverdec = iMA(Symbol(),5,100,0,0,PRICE_MEDIAN,0);

int tendencialineasc=0;
if(marojoc<maamarilloc&&maamarilloc<maverdec&&marojoc<maverdec){
tendencialineasc=1;//alcista
}
if(marojoc>maamarilloc&&maamarilloc>maverdec&&marojoc>maverdec){
tendencialineasc=2;//bajista
}



//MA avarage a largo plazo para apertura y evitar aperturas erroneas
//------------------------------------------------------------------
double largorojo = iMA(Symbol(),30,200,0,0,PRICE_MEDIAN,0);
double largoamarillo = iMA(Symbol(),30,50,0,0,PRICE_MEDIAN,0);
double largoverde = iMA(Symbol(),30,10,0,0,PRICE_MEDIAN,0);
int permitirabrirop2=0;
if(largoverde<largoamarillo&&largorojo<largoverde&&largorojo<largoamarillo){
 permitirabrirop2=1;
}
if(largoverde>largoamarillo&&largorojo>largoverde&&largorojo>largoamarillo){
 permitirabrirop2=2;
}

//MA avarage t ma mirror a corto plazo para ver operaciones
//------------------------------------------------------------------
double cortomirrorrojo = iCustom(Symbol(),1,"MA_Mirror",1200,0,0); //Rojo si esta arriba es compra o cerrar ventas
double cortomirrorazul = iCustom(Symbol(),1,"MA_Mirror",1200,1,0); //Azul si esta arriba es venta o cerrar compras
int permitirop=0;
if(cortomirrorrojo>0){
  permitirop=1;
}
if(cortomirrorrojo<0){
  permitirop=2;
}

double preciomedio = iMA(Symbol(),1,300,0,0,PRICE_MEDIAN,0);
//MA quitado
int optimoventa=0;
int optimocompra=0;
if(preciomedio>Ask){
  optimocompra=1;
}
if(preciomedio<Bid){
  optimoventa=1;
}

//CONDICIONES COMPRA Y CIERRE DE OPERACIONES
//-------------------------------------------------------------------
int operacionabrir=0;
int operacioncerrar=0;
if(tendenciamirror==1&&tendenciasar==1&&tendencialineas==1&&permitirop==1&&optimocompra==1&&permitirabrirop2==1){
  operacionabrir=1;
}
if(tendenciamirror==2&&tendenciasar==2&&tendencialineas==2&&permitirop==2&&optimoventa==1&&permitirabrirop2==2){
  operacionabrir=2;
}

if(tendenciamirror==2||tendencialineas==2||tendenciasar==2){//tendencialineas==2||||permitirop==2
  operacioncerrar=1;//cerrar compras
}
if(tendenciamirror==1||tendencialineas==1||tendenciasar==1){//tendencialineas==1||||permitirop==1
  operacioncerrar=2;//cerrar ventas;
}

//VALORES DE TAKEPROFIT Y STOPLOSS (RESTOP Y RESBOT)
//------------------------------------------------------------------
double takeprofitp1v = iCustom(Symbol(),30,"SL_BW",0,0);//15
double takeprofitp2v = iCustom(Symbol(),60,"SL_BW",0,0);
double takeprofitp3v = iCustom(Symbol(),240,"SL_BW",0,0);
double takeprofitp4v = iCustom(Symbol(),1440,"SL_BW",0,0);
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
double takeprofitp1c = iCustom(Symbol(),30,"SL_BW",1,0);
double takeprofitp2c = iCustom(Symbol(),60,"SL_BW",1,0);
double takeprofitp3c = iCustom(Symbol(),240,"SL_BW",1,0);
double takeprofitp4c = iCustom(Symbol(),1440,"SL_BW",1,0);

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
  string fileNamecierre = "nada.txt";
           if(OrderSymbol()==Symbol())//Añadido
           {
             if(OrderType()==OP_SELL){
                fileNamecierre = OrderSymbol()+"v"+OrderTicket()+".txt";
             }
             if(OrderType()==OP_BUY){
                fileNamecierre = OrderSymbol()+"c"+OrderTicket()+".txt";
             }

            string fileHandlecierre = FileOpen(fileNamecierre,FILE_CSV|FILE_READ);//|FILE_READ| FILE_WRITE
             if(fileHandlecierre==INVALID_HANDLE){
           printf("Handle Invalido, apertura error1 - No puede abrir los archivos donde estan especificados los cierres para leer los");
            }else{
                string cierreposicion = FileReadString(fileHandlecierre); //string archivoventa =
               FileClose(fileHandlecierre);
               }
          }
     //printf(cierreposicion); //DEBUGEO
       // printf("cierre"+comprafile);
 int tiempo2 = TimeCurrent()-OrderOpenTime();
              if(OrderType()==OP_SELL&&OrderSymbol()==Symbol())
                {
                  posicionesabiertas++;//contador de operaciones en mercado actual

                 if(cierreposicion==0){
                  //cierre es 0
                 }else{
                   if(tiempo2>864000){
                     printf("mirar operaciones de venta abiertas para ver si cerrar o no");
                   }else{
                     if(Ask<cierreposicion&&tiempo2>3600){
                        OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
                     }
                   }
                 }
                }
                if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()){
     posicionesabiertas++;
                 // double takeprofitc=OrderComment();
                 if(cierreposicion==0){

                 }else{
                   if(tiempo2>864000){
                      printf("mirar operaciones de compra abiertas para ver si cerrar o no");
                   }else{
                     if(Bid>cierreposicion&&tiempo2>3600){
                      OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);
                     }
                   }



                 }


                }
          }

//+------------------------------------------------------------------+
//   Take profit -69
//+------------------------------------------------------------------+
int takeprofit = 0;
      for(int tkp=0;tkp<OrdersTotal();tkp++){
OrderSelect(tkp,SELECT_BY_POS,MODE_TRADES);
if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()){
if(OrderProfit()>0){
  takeprofit++;
}
if(OrderProfit()<0){
  takeprofit--;
}
}
if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()){
  if(OrderProfit()>0){
    takeprofit++;
  }
  if(OrderProfit()<0){
    takeprofit--;
  }
}
      }



//+------------------------------------------------------------------+
//   APERTURA CONDICIONES - condiciones para establecer operaciones
//+------------------------------------------------------------------+
//Si tendenciasar==2 y tendenciamirror==2 y tendenciamirror2==2 y optimoventa==1 venta
string textosar="nulo - error";
if(tendenciasar==1){
  textosar="compra - alcista";
}
if(tendenciasar==2){
 textosar="venta - bajista";
}
string textomirror="nulo - error";
if(tendenciamirror==1){
  textomirror="compra - alcista";
}
if(tendenciamirror==2){
 textomirror="venta - bajista";
}
string textomirror2="nulo - error";
if(tendenciamirror2==1){
  textomirror2="compra - alcista";
}
if(tendenciamirror2==2){
 textomirror2="venta - bajista";
}
ObjectSetText(Symbol()+1,"SAR: "+textosar+"  Mirror1: "+textomirror+"  Mirror2:"+textomirror2,9,"Verdana",White);
ObjectSet(Symbol()+1,OBJPROP_CORNER,0);
ObjectSet(Symbol()+1,OBJPROP_XDISTANCE,20);
ObjectSet(Symbol()+1,OBJPROP_YDISTANCE,20);
string textooperacion="nulo";
if(optimoventa == 1){
  textooperacion = "Optimo Venta";
}else{
  if(optimocompra==1){
  textooperacion = "Optimo Compra";
}else{
  textooperacion = "No es bueno entrar aún";
}
}
ObjectSetText(Symbol()+2,"Mercado observación: "+textooperacion,9,"Verdana",White);
ObjectSet(Symbol()+2,OBJPROP_CORNER,0);
ObjectSet(Symbol()+2,OBJPROP_XDISTANCE,20);
ObjectSet(Symbol()+2,OBJPROP_YDISTANCE,40);


ObjectSetText(Symbol()+7,"Posiciones abiertas actuales: "+posicionesabiertas,9,"Verdana",Red);
ObjectSet(Symbol()+7,OBJPROP_CORNER,0);
ObjectSet(Symbol()+7,OBJPROP_XDISTANCE,20);
ObjectSet(Symbol()+7,OBJPROP_YDISTANCE,190);

//+------------------------------------------------------------------+
//   Cerrar en caso
//+------------------------------------------------------------------+
//Si tendenciasar==2 y tendenciamirror==2 y tendenciamirror2==2 y optimoventa==1 venta

for(int cntcerrar=0;cntcerrar<OrdersTotal();cntcerrar++)
{
 OrderSelect(cntcerrar,SELECT_BY_POS,MODE_TRADES);
 int tiempo = TimeCurrent()-OrderOpenTime();
 double beneficio = OrderProfit()+OrderCommission();
 //printf("comisiones : "+OrderCommission());
 //printf("Beneficio : "+beneficio);

 if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()){
   //if(tendenciasar==1&&tendenciamirror==1&&tendenciamirror2==1||tendenciamirror==1&&tendenciamirror2==1)//&&Ask>Bandaalto1200) //here is the close sell rule
if(operacioncerrar==2&&beneficio>0.01&&tiempo>21600&&posicionesabiertas==1||tiempo>172800&&beneficio>0.01)//&&Ask>Bandaalto1200) //here is the close sell rule
    {
     OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
    }
if(posicionesabiertas>1&&takeprofit>0&&operacioncerrar==2&&beneficio>0.01&&tiempo>21600){
     OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
    }

 }
 if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()){
  // if(tendenciasar==2&&tendenciamirror==2&&tendenciamirror2==2||tendenciamirror==2&&tendenciamirror2==2)//&&Ask<Bandabajo1200) // here is the close buy rule
   if(operacioncerrar==1&&beneficio>0.01&&tiempo>21600&&posicionesabiertas==1||tiempo>172800&&beneficio>0.01)//&&Ask<Bandabajo1200) // here is the close buy rule
     {
     OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);
     }
   if(posicionesabiertas>1&&takeprofit>0&&operacioncerrar==2&&beneficio>0.01&&tiempo>21600){
          OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
         }
     }
}

//+------------------------------------------------------------------+
//   Lotes gestion
//+------------------------------------------------------------------+


double lotesfinal = lotesinicial*posicionesabiertas*multiplicador;
if(lotesfinal<minlotes){
  lotesfinal= minlotes;
}else{
  lotesfinal = lotesinicial*posicionesabiertas*multiplicador;
}


if(posicionesabiertas==0){

  //Si tendenciasar==2 y tendenciamirror==2 y tendenciamirror2==2 y optimoventa==1 venta

  //  if(tendenciasar==2&&tendenciamirror==2&&tendenciamirror2==2&&optimoventa==1){
      if(operacionabrir==2){

if(resbot==0||resbot>1500){
  //no resistencia bot
}else{
  OrderSend(Symbol(),OP_SELL,lotesfinal,Bid,Slippage,0,0,0,MagicNumber,0,Red); //Venta resbot
  string fileNamev = OrderSymbol()+"v"+OrderTicket()+".txt";
  string fileHandlev = FileOpen(fileNamev,FILE_CSV|FILE_READ | FILE_WRITE);
  if(fileHandlev ==INVALID_HANDLE){
  printf("Handle Invalido 1 Al abrir operacion primera venta, no ha podido escribir bien el takeprofit");
  }else{
    string datav = resbot;
              FileWrite(fileHandlev,datav);
              FileClose(fileHandlev);
   }
   string stopnamev = OrderSymbol()+"vstop"+OrderTicket()+".txt";
   string handlestopv = FileOpen(stopnamev,FILE_CSV|FILE_READ | FILE_WRITE);
   if(handlestopv ==INVALID_HANDLE){
   printf("Handle Invalido 1-1 Al abrir operacion primera venta, no ha podido escribir bien el stoploss");
   }else{
     string datastopv = restop;
               FileWrite(handlestopv,datastopv);
               FileClose(handlestopv);
    }



  //+------------------------------------------------------------------+
  //   CICLO FOR para nuevo take profit por nueva operacion VENTA
  //+------------------------------------------------------------------+
  for(int cnt1=0;cnt1<OrdersTotal();cnt1++)
  {
  OrderSelect(cnt1,SELECT_BY_POS,MODE_TRADES);
  if(OrderType()==OP_SELL&&OrderSymbol()==Symbol())
    {
  string fileNamenuevov1 = OrderSymbol()+"v"+OrderTicket()+".txt";
  string fileHandlenuevov1 = FileOpen(fileNamenuevov1,FILE_CSV|FILE_READ | FILE_WRITE);
  if(fileHandlenuevov1 ==INVALID_HANDLE){
  printf("Error 2 al intentar abrir archivos para establecer nuevos takeprofits de operaciones existentes");
  }else{
    string datanuevov1 = resbot;
    FileWrite(fileHandlenuevov1,datanuevov1);
    FileClose(fileHandlenuevov1);
   }

   string stopnamev1 = OrderSymbol()+"vstop"+OrderTicket()+".txt";
   string handlestopv1 = FileOpen(stopnamev1,FILE_CSV|FILE_READ | FILE_WRITE);
   if(handlestopv1 ==INVALID_HANDLE){
   printf("Handle Invalido 1-1-1 Al abrir operacion primera venta, no ha podido actualizar los stoploss de todas las operaciones");
   }else{
     string datastopv1 = restop;
               FileWrite(handlestopv1,datastopv1);
               FileClose(handlestopv1);
    }



    }
  }
}

  }

  //   if(tendenciasar==1&&tendenciamirror==1&&tendenciamirror2==1&&optimocompra==1){
       if(operacionabrir==1){

if(restop==0||restop>1500){
  //no hay resistencia top
}else{
  OrderSend(Symbol(),OP_BUY,lotesfinal,Ask,Slippage,0,0,0,MagicNumber,0,Blue); //Compra restop
  string fileNamec =  OrderSymbol()+"c"+OrderTicket()+".txt";
  string fileHandlec = FileOpen(fileNamec,FILE_CSV|FILE_READ | FILE_WRITE);
  if(fileHandlec ==INVALID_HANDLE){
  printf("Errir al abrir operacion compra primera no ha podido establecer takeprofit");
  }else{
    string datac = restop;
      FileWrite(fileHandlec,datac);
      FileClose(fileHandlec);
   }
   string stopnamec = OrderSymbol()+"cstop"+OrderTicket()+".txt";
   string handlestopc = FileOpen(stopnamec,FILE_CSV|FILE_READ | FILE_WRITE);
   if(handlestopc ==INVALID_HANDLE){
   printf("Handle Invalido 1-1-1 Al abrir operacion primera venta, no ha podido actualizar los stoploss de todas las operaciones");
   }else{
     string datastopc = restop;
               FileWrite(handlestopc,datastopc);
               FileClose(handlestopc);
    }


    //+------------------------------------------------------------------+
    //   CICLO FOR para nuevo take profit por nueva operacion COMPRA
    //+------------------------------------------------------------------+

    for(int cnt2=0;cnt2<OrdersTotal();cnt2++)
    {
    OrderSelect(cnt2,SELECT_BY_POS,MODE_TRADES);

    if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()){

    string fileNamenuevoc1 = OrderSymbol()+"c"+OrderTicket()+".txt";
    string fileHandlenuevoc1 = FileOpen(fileNamenuevoc1,FILE_CSV|FILE_READ | FILE_WRITE);
    if(fileHandlenuevoc1 ==INVALID_HANDLE){
    printf("error al actualizar las otras operaciones compra con nuevo takeprofit");
    }else{
    string datanuevoc1 = restop;
    FileWrite(fileHandlenuevoc1,datanuevoc1);
    FileClose(fileHandlenuevoc1);
     }
     string stopnamec1 = OrderSymbol()+"cstop"+OrderTicket()+".txt";
     string handlestopc1 = FileOpen(stopnamec1,FILE_CSV|FILE_READ | FILE_WRITE);
     if(handlestopc1 ==INVALID_HANDLE){
     printf("Handle Invalido 1-1-1 Al abrir operacion primera venta, no ha podido actualizar los stoploss de todas las operaciones");
     }else{
       string datastopc1 = restop;
                 FileWrite(handlestopc1,datastopc1);
                 FileClose(handlestopc1);
      }

    }
    }
}

     }
}else{


  int permitirabrirv=0;
  int permitirabrirc=0;
string cierreposicion4 = "0";
      for(int cnt4=0;cnt4<OrdersTotal();cnt4++)
      {

      OrderSelect(cnt4,SELECT_BY_POS,MODE_TRADES);
 if(OrderSymbol()==Symbol()){
 string fileNamecierre4 = "nada.txt";
   if(OrderType()==OP_SELL){
     fileNamecierre4 = OrderSymbol()+"v"+OrderTicket()+".txt";
   }else{
     fileNamecierre4 = OrderSymbol()+"c"+OrderTicket()+".txt";
   }

   string fileHandlecierre4 = FileOpen(fileNamecierre4,FILE_CSV|FILE_READ);// | FILE_WRITE
   if(fileHandlecierre4==INVALID_HANDLE){
   printf("Handle Invalido, apertura error 2 - Error al leer cierre cuando hay mas de una operacion en el mercado actual");
   }else{
    cierreposicion4 = FileReadString(fileHandlecierre4);
    FileClose(fileHandlecierre4);
    }
    string stopname11 = OrderSymbol()+"vstop"+OrderTicket()+".txt";
    string handlestop11 = FileOpen(stopname11,FILE_CSV|FILE_READ | FILE_WRITE);
    if(handlestop11 ==INVALID_HANDLE){
    printf("Handle Invalido 1-1-1 Al abrir operacion primera venta, no ha podido actualizar los stoploss de todas las operaciones");
    }else{
      string datastop11 = restop;
                FileWrite(handlestop11,datastop11);
                FileClose(handlestop11);
     }
 }

 ObjectSetText(Symbol()+6,"Takeprofit "+Symbol()+"  : "+cierreposicion4,9,"Verdana",Red);
 ObjectSet(Symbol()+6,OBJPROP_CORNER,0);
 ObjectSet(Symbol()+6,OBJPROP_XDISTANCE,20);
 ObjectSet(Symbol()+6,OBJPROP_YDISTANCE,170);

      if(resbot>cierreposicion4)//modelo
      {
       permitirabrirv=1;// permitir


      }else{
        permitirabrirv=2;// no permitir

      }

      if(restop<cierreposicion4)//modelo
      {
       permitirabrirc=1;// permitir
      }else{
        permitirabrirc=2;//No permitir


      }
      //printf(cierreposicion4);//DEBUGEO

      }
//printf("permitir abrir v"+permitirabrirv);//DEBUGEO
//printf("permitir abrir c"+permitirabrirc);//DEBUGEO
//  if(tendenciasar==2&&tendenciamirror==2&&tendenciamirror2==2&&optimoventa==1&&permitirabrirv==1){
    if(operacionabrir==2&&permitirabrirv==1){

if(resbot==0||resbot>1500){
  //No hay resbot
}else{
  OrderSend(Symbol(),OP_SELL,lotesfinal,Bid,Slippage,0,0,0,MagicNumber,0,Red); //Venta resbot
 string fileNamev1 = OrderSymbol()+"v"+OrderTicket()+".txt";
 string fileHandlev1 = FileOpen(fileNamev1,FILE_CSV|FILE_READ | FILE_WRITE);
 if(fileHandlev1 ==INVALID_HANDLE){
 printf("No se ha podido abrir operacion 2 o mas venta establecer takeprofit de operacion actual");
 }else{
   string datav1 = resbot;
              FileWrite(fileHandlev1,datav1);
              FileClose(fileHandlev1);
  }



    //+------------------------------------------------------------------+
    //   CICLO FOR para nuevo take profit por nueva operacion VENTA
    //+------------------------------------------------------------------+
    for(int cnt11=0;cnt11<OrdersTotal();cnt11++)
    {
    OrderSelect(cnt11,SELECT_BY_POS,MODE_TRADES);
    if(OrderType()==OP_SELL&&OrderSymbol()==Symbol())
      {
    string fileNamenuevov11 = OrderSymbol()+"v"+OrderTicket()+".txt";
    string fileHandlenuevov11 = FileOpen(fileNamenuevov11,FILE_CSV|FILE_READ | FILE_WRITE);
    if(fileHandlenuevov11 ==INVALID_HANDLE){
    printf("No se ha podido actualizar los takeprofits de las otras operaciones venta");
    }else{
      string datanuevov11 = resbot;
      FileWrite(fileHandlenuevov11,datanuevov11);
      FileClose(fileHandlenuevov11);
     }


      }

    }
}

  }

//  if(tendenciasar==1&&tendenciamirror==1&&tendenciamirror2==1&&optimocompra==1&&permitirabrirc==1){
   if(operacionabrir==1&&permitirabrirc==1){
if(restop==0){
  //No hay restop
}else{
      OrderSend(Symbol(),OP_BUY,lotesfinal,Ask,Slippage,0,0,0,MagicNumber,0,Blue); //Compra restop
      string fileNamec1 = OrderSymbol()+"c"+OrderTicket()+".txt";
      string fileHandlec1 = FileOpen(fileNamec1,FILE_CSV|FILE_READ | FILE_WRITE);
      string datac1 = restop;
      if(fileHandlec1 ==INVALID_HANDLE){
      printf("No se ha podido abrir operacion 2 o mas compra establecer takeprofit de operacion actual");
      }else{
                FileWrite(fileHandlec1,datac1);
                FileClose(fileHandlec1);
       }


        //+------------------------------------------------------------------+
        //   CICLO FOR para nuevo take profit por nueva operacion COMPRA
        //+------------------------------------------------------------------+

        for(int cnt22=0;cnt22<OrdersTotal();cnt22++)
        {
        OrderSelect(cnt22,SELECT_BY_POS,MODE_TRADES);

        if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()){

        string fileNamenuevoc11 = OrderSymbol()+"c"+OrderTicket()+".txt";
        string fileHandlenuevoc11 = FileOpen(fileNamenuevoc11,FILE_CSV|FILE_READ | FILE_WRITE);
        if(fileHandlec1 ==INVALID_HANDLE){
        printf("No se ha podido actualizar las operaciones de compra para establecer nuevo takeprofit");
        }else{
          string datanuevoc11 = resbot;
          FileWrite(fileHandlenuevoc11,datanuevoc11);

          FileClose(fileHandlenuevoc11);
         }

        }
        }
}

  }

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
