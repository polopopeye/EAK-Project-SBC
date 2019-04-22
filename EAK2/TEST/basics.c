//+------------------------Kenneth Suarez-------------------------------+
//                   Expert Advisor MUFASA V1.5- 2014-2019
//+---------------------------------------------------------------------+

//  double Extrapolatorgoodop=1.45;
//  double Extrapolatorbadop=0.8;
  double Extrapolatorgoodop=1.10;
  double Extrapolatorbadop=0.75;

  double cogGP=1.45;
  double cogBP=0.9;
  //  double multiplicador=1.5; //Martingale factor to recover bad choices
  //double multiplicador=1.35; //Martingale factor to recover bad choices
  double maxspread=50;

  //+---------------------------------------------------------------------+
bool debugoption=true;
bool advanceddebug=false;
string commentID="error";
 string semaforv2="SEMAFOR V2";
 bool semafor2ind=true;
 string cogindv2t="CENTEROFGRAVITY";
 bool cogindv2=true;

extern string GESTIONLOTES="METODO 1 MARTINGALE, METODO 2 EN CONSTRUCCION --------------";
 int gestionlotesmethod=3;
extern double lotesinicial=0.01; //first lot

 string GRID="POSITION FIJA EN PIPS A PARTIR DE UNA OPERACION ABIERTA";
 bool filternegativeopenorders=false;
 string MAXPOSITION="NUMERO MAXIMO DE OPERACIONES A TENER ABIERTAS";
 int maxposition=100;//Max positions
 string MODIFY="MODIFY ORDER, SI TP FIJO PUEDES FIJARLO CON PIPSMODIFY";
bool ordertpmodify=false;
int pipsmodify=450; //pips to reach in position modify.
 string EXTRAPOLATOR="EXTRAPOLATOR RISK";
 bool Extrapolatorind=true;
 ENUM_TIMEFRAMES Tiempoextrapolator=PERIOD_M5;
 int Methodextrapolator=4;






 string GLOBALORDERPROFIT="FILTRO PARA EVITAR CIERRE CON PERDIDAS";
 bool globalordersprofit=true;
 string GLOBALORDERPROFIT2="FILTRO GLOBAL PARA EVITAR CIERRE MENOS PIPS";
 int minpositionallowedtoclosepipsa=400;//525 - 550
 int minpositionallowedtoclosepipsb=400;
 int minpositionallowedtoclosepipsc=0;
 string OTHEROPTIONS="OTHER OPTIONS-----------------------";
 int TrailingStop=0;
 int MagicNumber=10001;
 int Slippage=10;

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
//ObjectCreate(Symbol()+1,OBJ_LABEL,0,0,0,0); // Tendencia Bands
//OPTIONSDEBUGGER
if(debugoption==true){
  ObjectCreate(Symbol()+2,OBJ_LABEL,0,0,0,0); // Pips
  ObjectCreate(Symbol()+"minlot",OBJ_LABEL,0,0,0,0);
  if(globalordersprofit==true)ObjectCreate(Symbol()+"ordersprofit",OBJ_LABEL,0,0,0,0);
  ObjectCreate(Symbol()+"filter1",OBJ_LABEL,0,0,0,0);
  ObjectCreate(Symbol()+"PR",OBJ_LABEL,0,0,0,0);
  if(cogindv2==true)ObjectCreate(Symbol()+"cog",OBJ_LABEL,0,0,0,0);
  ObjectCreate(Symbol()+"secreco",OBJ_LABEL,0,0,0,0);
  if(advanceddebug==true)ObjectCreate(Symbol()+"Interface1",OBJ_LABEL,0,0,0,0);
  if(advanceddebug==true)ObjectCreate(Symbol()+"Interface2",OBJ_LABEL,0,0,0,0);
  if(advanceddebug==true)ObjectCreate(Symbol()+"Interface3",OBJ_LABEL,0,0,0,0);
  if(advanceddebug==true)ObjectCreate(Symbol()+"Interface4",OBJ_LABEL,0,0,0,0);
  if(advanceddebug==true)ObjectCreate(Symbol()+"channel",OBJ_LABEL,0,0,0,0);
  if(advanceddebug==true)ObjectCreate(Symbol()+"tpmpV",OBJ_LABEL,0,0,0,0);
  if(advanceddebug==true)ObjectCreate(Symbol()+"tpmpC",OBJ_LABEL,0,0,0,0);
  if(Extrapolatorind==true)ObjectCreate(Symbol()+"Extrapolator",OBJ_LABEL,0,0,0,0);
  if(debugoption==true)ObjectCreate(Symbol()+"lotesop",OBJ_LABEL,0,0,0,0);
}


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
int point_compat=1;


double maxlotsG=lotesinicial*30;
double maxlotsB=lotesinicial*5;
double gridposition=15; //pips on every new trade
double minpipsG=35;//30
double minpipsB=3;//10
double minpipsC=10;
int minpos=2;
int lotofpos=7;
ushort sep=StringGetCharacter(":",0);
ushort seprow=StringGetCharacter(";",0);


//if(Digits==3||Digits==5)point_compat=10;
//+------------------------------------------------------------------+
//    INTERFACE
//+------------------------------------------------------------------+
 double minlots = MarketInfo(Symbol(),MODE_MINLOT);
 ObjectSetText(Symbol()+"minlot","Lots (Min: "+minlots+" Max: "+MarketInfo(Symbol(), MODE_MAXLOT)+") Value: "+MarketInfo(Symbol(),MODE_TICKVALUE)+" step:"+MarketInfo(Symbol(), MODE_LOTSTEP),7,NULL,Orange);
  ObjectSet(Symbol()+"minlot",OBJPROP_CORNER,0);
  ObjectSet(Symbol()+"minlot",OBJPROP_XDISTANCE,50);
  ObjectSet(Symbol()+"minlot",OBJPROP_YDISTANCE,15);

int lotround=0;

if(MarketInfo(Symbol(),MODE_LOTSTEP)==0.1){
  lotround=1;
}
if(MarketInfo(Symbol(),MODE_LOTSTEP)==0.01){
  lotround=2;
}
if(MarketInfo(Symbol(),MODE_LOTSTEP)==0.001){
  lotround=3;
}
if(MarketInfo(Symbol(),MODE_LOTSTEP)==0.0001){
  lotround=4;
}

if(advanceddebug==true){
  ObjectSetText(Symbol()+"Interface1","Margen:["+AccountMargin()+"] Margen Libre:["+AccountFreeMargin()+"] Liquidez:["+AccountEquity()+"] ",10,NULL,Yellow);
   ObjectSet(Symbol()+"Interface1",OBJPROP_CORNER,0);
   ObjectSet(Symbol()+"Interface1",OBJPROP_XDISTANCE,300);
   ObjectSet(Symbol()+"Interface1",OBJPROP_YDISTANCE,5);

   ObjectSetText(Symbol()+"Interface3","Rentabilidad:["+AccountProfit()+"] Balance:["+AccountBalance()+"] Credito:["+AccountCredit()+"]",9,NULL,Yellow);
    ObjectSet(Symbol()+"Interface3",OBJPROP_CORNER,0);
    ObjectSet(Symbol()+"Interface3",OBJPROP_XDISTANCE,300);
    ObjectSet(Symbol()+"Interface3",OBJPROP_YDISTANCE,25);


   ObjectSetText(Symbol()+"Interface2",AccountName()+"       Cuenta: "+AccountNumber()+" ("+AccountCurrency()+")",9,NULL,Yellow);
    ObjectSet(Symbol()+"Interface2",OBJPROP_CORNER,0);
    ObjectSet(Symbol()+"Interface2",OBJPROP_XDISTANCE,300);
    ObjectSet(Symbol()+"Interface2",OBJPROP_YDISTANCE,45);

    ObjectSetText(Symbol()+"Interface4","Server: "+AccountServer()+" Empresa: "+AccountCompany(),9,NULL,Yellow);
     ObjectSet(Symbol()+"Interface4",OBJPROP_CORNER,0);
     ObjectSet(Symbol()+"Interface4",OBJPROP_XDISTANCE,300);
     ObjectSet(Symbol()+"Interface4",OBJPROP_YDISTANCE,65);
}



  //------------------------------------------------------------------
  //Global OrdersProfit for bad orders
  //------------------------------------------------------------------
  double profitordersC = 0;
  double profitordersV = 0;
  if(globalordersprofit==true){
    double profitordersV2B=0;
    double profitordersV2S=0;
    double badorderprofit1C=0;
    double badorderprofit2C=0;
    double badorderprofit1V=0;
    double badorderprofit2V=0;
    double badordercommissionC=0;
    double badordercommissionV=0;
    double badorderswapC=0;
    double badorderswapV=0;
    double lastorderopenpriceC=0;
    double lastorderopenpriceV=0;

  for(int gpo=0;gpo<OrdersTotal();gpo++){
    OrderSelect(gpo,SELECT_BY_POS,MODE_TRADES);
    if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()&&OrderComment()==commentID){
      double DiffPipsc1 = MathAbs((NormalizeDouble(((OrderOpenPrice()-Bid)/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);
      badorderswapC=badorderswapC+OrderSwap();
      badordercommissionC=badordercommissionC+OrderCommission();
      profitordersV2B=profitordersV2B+OrderProfit();
      lastorderopenpriceC=OrderOpenPrice();
    }
    if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()&&OrderComment()==commentID){
      double DiffPipsv1 = MathAbs((NormalizeDouble(((Ask-OrderOpenPrice())/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);
      badorderswapV=badorderswapV+OrderSwap();
      badordercommissionV=badordercommissionV+OrderCommission();
      profitordersV2S=profitordersV2S+OrderProfit();
      lastorderopenpriceV=OrderOpenPrice();
    }
  }
  //------------------------------------------------------------------
  //GLOBAL ORDER PROFIT SMALL TO AVOID FAST CLOSE
  //------------------------------------------------------------------
    if(globalordersprofit==true){
        profitordersC = profitordersV2B+badordercommissionC+badorderswapC;
        profitordersV = profitordersV2S+badordercommissionV+badorderswapV;
      ObjectSetText(Symbol()+"ordersprofit","Orders Profit B:"+NormalizeDouble(profitordersC,2)+" S:"+NormalizeDouble(profitordersV,0),8,NULL,Orange);
       ObjectSet(Symbol()+"ordersprofit",OBJPROP_CORNER,0);
       ObjectSet(Symbol()+"ordersprofit",OBJPROP_XDISTANCE,15);
       ObjectSet(Symbol()+"ordersprofit",OBJPROP_YDISTANCE,180);
    }
  }



  //SECRECO
  //----------------------------------------
  double spreadvalue=MarketInfo(Symbol(),MODE_SPREAD);
  double tickvalue=MarketInfo(Symbol(),MODE_TICKVALUE);
  double ddsecreco=0;
  string FsecrecoDD=Symbol()+"DD";
  string SecrecoDDR1[];
  double ddsecreco1=(lotesinicial*tickvalue*45000)*-1;
if(FileIsExist(FsecrecoDD)==true){
    string FRsecreco = FileOpen(FsecrecoDD,FILE_READ);
    if(FRsecreco==INVALID_HANDLE){
    printf("File Read Error 1");
    }else{
    string SecrecoDDR = FileReadString(FRsecreco);
    FileClose(FRsecreco);
    }
    StringSplit(SecrecoDDR,sep,SecrecoDDR1);
    double DDsecrecoValue=SecrecoDDR1[0];
    double DDsecrecoTime=SecrecoDDR1[1];
    if(ddsecreco1<DDsecrecoValue){
      ddsecreco=NormalizeDouble(ddsecreco1,0);
    }else{
      ddsecreco=NormalizeDouble(DDsecrecoValue,0);
    }
}else{
     ddsecreco=NormalizeDouble(ddsecreco1,0);
}


  if(profitordersC<ddsecreco){
    string FsecrecoC1 = FileOpen(FsecrecoDD,FILE_WRITE);
     if(FsecrecoC1==INVALID_HANDLE){
    printf("SecrecoError 1");
    }else{
      string FWsecrecoC1 = profitordersC+":"+TimeCurrent();
              FileWrite(FsecrecoC1,FWsecrecoC1);
              FileClose(FsecrecoC1);
       }
  }
  if(profitordersV<ddsecreco){
    string FsecrecoV1 = FileOpen(FsecrecoDD,FILE_WRITE);
     if(FsecrecoV1==INVALID_HANDLE){
    printf("SECRECOError 2");
    }else{
      string FWsecrecoV1 = profitordersV+":"+TimeCurrent();
              FileWrite(FsecrecoV1,FWsecrecoV1);
              FileClose(FsecrecoV1);
       }
  }

double brsecreco=NormalizeDouble(ddsecreco*1.5,0);
double Bdia=NormalizeDouble((ddsecreco/31)/2,0);
double Bmes=NormalizeDouble(Bdia*21,0);


  ObjectSetText(Symbol()+"secreco","Secreco: BR"+brsecreco+" DD"+ddsecreco+" BD"+Bdia+" BM"+Bmes+" SPR"+spreadvalue,10,NULL,Orange);
   ObjectSet(Symbol()+"secreco",OBJPROP_CORNER,0);
   ObjectSet(Symbol()+"secreco",OBJPROP_XDISTANCE,230);
   ObjectSet(Symbol()+"secreco",OBJPROP_YDISTANCE,240);

//+------------------------------------------------------------------+
//    GRID
//+------------------------------------------------------------------+

//selecciona las posiciones que el robot ha abierto
int filter1v=0;
int filter1c=0;

int closeallordersc=0;
int closeallordersv=0;

double lastorderpS1=0;
double lastorderpB1=0;
int posicionesabiertasrobotc = 0;
int posicionesabiertasrobotv = 0;
if(Digits==3||Digits==5)point_compat=10;
for(int pg=0;pg<OrdersTotal();pg++){
OrderSelect(pg,SELECT_BY_POS,MODE_TRADES);
if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()&&OrderComment()==commentID){
  lastorderpS1=OrderProfit();
  posicionesabiertasrobotv++;
double DiffPipsv = MathAbs((NormalizeDouble(((OrderOpenPrice()-Bid)/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);

}
if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()&&OrderComment()==commentID){
  lastorderpB1=OrderProfit();
  posicionesabiertasrobotc++;

  double DiffPipsc = MathAbs((NormalizeDouble(((Ask-OrderOpenPrice())/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);

}
ObjectSetText(Symbol()+2,"PipsC: "+DiffPipsc+" PipsV: "+DiffPipsv,7,NULL,Orange);
  ObjectSet(Symbol()+2,OBJPROP_CORNER,0);
  ObjectSet(Symbol()+2,OBJPROP_XDISTANCE,15);
  ObjectSet(Symbol()+2,OBJPROP_YDISTANCE,40);
}



     //------------------------------------------------------------------
     // SISTEMAS
     // Ejecutan las operaciones de apertura y cierre
     //------------------------------------------------------------------


// Aquí van a ir los sistemas, con sus condicionales y todo para que funcionen a traves de indicadores
// externos. existe una variable comentario, que es el ID del sistema utilizado, mas abajo existe el triger
// de envio de operacion, donde se envia la operación y se crea el archivo con el sistema utilizado.


//Tienen que cumplir,
//Reglas de apertura, cierre, precio objetivo, probabilidad (expected value),RiesgoInicial,

//Variables sin definir
int op=0;
double expectedvalue1=0;
double expectedvalue2=0;
double interestrates=0;
double crecimiento=0;
double riesgo=0;
double riesgoporcrecimiento=0;
double probabilidad=0;
//Variables Definidas
double inflacion=2;//1+3.14159^0
double priceima = Ask; //double priceima = iMA(Symbol(),PERIOD_M1,1,0,MODE_EMA,PRICE_MEDIAN,0);
int Tiempomedioporoperacion=0;
int Lotesmedioporoperacion=0;
//ESTRATEGIA1 - S1
bool s1=true;
bool s2=true;

//----------- FORMULAS INTERESANTES ----------------//
//double interestrates=expectedvalue1/priceima;
//double interestrates=crecimiento*inflacion*riesgo;
//double riesgo*crecimiento=interestrates/inflacion;
//double RAIZCUADRADA(riesgo*crecimiento)=riesgo (aproximado)
//double expectedvalue1*p+expectedvalue2*(1-p)=priceima;

if(s1==true){
  int Tiempomedioporoperacion=14400;
  double PRcogB=0;
  double PRcogS=0;
  double CcogB = 1;
  double CcogS = 1;

  double cognumbera = iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,3,0);
  double cognumberb = iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,1,0);
  double cognumberc = iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,2,0);
  double cognumberd = iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,4,0);

  if(priceima>cognumbera){
    //venta
    commentID="S1";
  PRcogS=0.60;
  op=2;
  expectedvalue1=cognumberd;
  expectedvalue2=cognumbera*1.1;
  interestrates=expectedvalue1/priceima;
  riesgoporcrecimiento=interestrates/inflacion;
  riesgo=MathSqrt(riesgoporcrecimiento);
  // probabilidad=expectedvalue1*p+expectedvalue2*(1-p)=priceima;
  // expectedvalue1*p+expectedvalue2-expectedvalue2*p=priceima;
  // expectedvalue1-expectedvalue2=priceima-expectedvalue2;
  probabilidad=(priceima-expectedvalue2)/(expectedvalue1-expectedvalue2);
  }else{
  PRcogS=0;
  }
  if(priceima<cognumberd){
    //compra
    commentID="S1";
  PRcogB=0.60;
  op=1;
  expectedvalue1=cognumbera;
  expectedvalue2=cognumberd*1.1;
  interestrates=expectedvalue/priceima;
  riesgoporcrecimiento=interestrates/inflacion;
  riesgo=MathSqrt(riesgoporcrecimiento);
  probabilidad=(priceima-expectedvalue2)/(expectedvalue1-expectedvalue2);
  }else{
  PRcogB=0;
  }
}






//------------------------------------------------------------------
// CUERPO DEL ROBOT
//Aquí se crea el espacio para
//APERTURA - CIERRE - GESTIÓN LOTES - BAHAVIOUR
//------------------------------------------------------------------

// Primero se cataloga una operacion como riesgosa o no, en funcion a parametros como, tiempo, inversion,
// probabilidad segun sistemas y demas se da una nota de riesgo.
//
// Si el riesgo es bajo, se sigue el sistema independiente si gana o pierde.
//
// Si el riesgo es alto. se cierra siguiendo el sistema ganador. (Se penaliza solo el sistema de apertura)
//
// Este apartado es riesgo, y luego sigue el cierre de operaciones.
//
// Cuando se cierra una operacion se crea un archivo con el nombre del sistema de apertura y
// dentro de ese archivo se añade el tiquet, e informacion importante de la operacion (el cierre, rentabilidad,
//   etc.).
// A traves de la información almacenada se sacara datos de comportamiento de cada sistema mediante un for
// y un exist file.


double RiskBehavior=0;
integer SegundosElapsed=0;
string FileDBarchivos=commentID+".eakdb";
string FDBread1r="0:0;";

for(int cnta1=0;cnta1<OrdersTotal();cnta1++){
  OrderSelect(cnta1,SELECT_BY_POS,MODE_TRADES);
  if(OrderSymbol()==Symbol()&&OrderMagicNumber()==MagicNumber){
    SegundosElapsed=TimeCurrent()-OrderOpenTime();//tiempo en segundos

    if(FileIsExist(FileDBarchivos)){ //aqui se va a sacar solo el archivo info de la operacion en especial.
      //aqui tiene que dar info del archivo.
      //RIESGO NOTA
      if(SegundosElapsed>Tiempomedioporoperacion){
        //Incremento riesgo Exponencial. X^1
        //RiesgoTiempo=RAIZCUADRADA((RiesgoInicial/Tiempomedioporoperacion)*(SegundosElapsed-Tiempomedioporoperacion))
        //RiesgoTiempo+RiesgoInicial=RiesgoTiempoCompleto;
        //El riesgo inicial viene indicado al porcentaje de victorias y rentibilidad esperada por operacion.
        //Si no hay estos datos no es posible catalogar operacion
      }
    }else{
      //Si no hay archivo de donde sacar el riesgo, riesgo es neutro.
    }


    //------------------------------------------------------------------
    // CIERRE
    //------------------------------------------------------------------


if(FileIsExist(FileDBarchivos)){
  string FDBread1 = FileOpen(FileDBarchivos,FILE_READ);
  if(FDBread1a==INVALID_HANDLE){
  printf("FDBread1 1");
  }else{
  string FDBread1r = FileReadString(FDBread1);
  FileClose(FDBread1);
  }
}



      if(RiskBehavior<=50){//Riesgo controlado, cierre normal.
      //->SE CREA ARCHIVO DE CIERRE ESPECIFICANDO DATOS PARA ESTADISTICA

      string Fdb1 = FileOpen(FileDBarchivos,FILE_WRITE);
       if(Fdb1==INVALID_HANDLE){
      printf("Fdb1 1");
      }else{
        string Fdb1w = FDBread1r+profitordersC+":"+TimeCurrent()";"; //cada una de estas lineas se añade lo nuevo.
                FileWrite(Fdb1,Fdb1w);
                FileClose(Fdb1);
         }
    }

    if(RiskBehavior>50){
      //Riesgo alto,
      if(OrderProfit()>0){
        //Riesgo alto pero hay beneficios. Se sigue con la estrategia. Cierre normal
        //->SE CREA ARCHIVO DE CIERRE ESPECIFICANDO DATOS PARA ESTADISTICA
        string Fdb1 = FileOpen(FileDBarchivos,FILE_WRITE);
         if(Fdb1==INVALID_HANDLE){
        printf("Fdb1 1");
        }else{
          string Fdb1w = FDBread1r+profitordersC+":"+TimeCurrent()";";
                  FileWrite(Fdb1,Fdb1w);
                  FileClose(Fdb1);
           }
      }else{
        //Se cierra siguiendo Cierre normal o cierre de la estrategia 1ra.
        //->SE CREA ARCHIVO DE CIERRE ESPECIFICANDO DATOS PARA ESTADISTICA
        string Fdb1 = FileOpen(FileDBarchivos,FILE_WRITE);
         if(Fdb1==INVALID_HANDLE){
        printf("Fdb1 1");
        }else{
          string Fdb1w = FDBread1r+profitordersC+":"+TimeCurrent()";";
                  FileWrite(Fdb1,Fdb1w);
                  FileClose(Fdb1);
           }
      }
    }
    //--------------------------------------------------------
  }//Fin If
}//Fin For



//----------------------------------------------------------
//BEHAVIOUR
//----------------------------------------------------------
string behaviorrow[],behavioritem[],control;
integer cntrowbehavior=0;
integer ticketitem=0;
double riesgoitem=0;
integer Tiempooperacionbehavior,tiempomedio1,Tiempomedioporoperacion2;
double profitmediobehavior,Profitmedioporoperacion2;
if(FileIsExist(FileDBarchivos)){
  string behavior1read = FileOpen(FileDBarchivos,FILE_READ);
  if(behavior1read==INVALID_HANDLE){
  printf("behavior1read 1");
  }else{
  string behavior1readall = FileReadString(behavior1read);
  FileClose(behavior1read);
  }
  StringSplit(behavior1readall,seprow,behaviorrow);
  cntrowbehavior=ArraySize(behaviorrow);

  //-----------------------------------------------------------
  //
  // Se acceden a los archivos de cada sistema, se verifica si hay mas de x operaciones
  // si hay mas, se elimina del archivo la op 1. con un search and replace.
  //
  //-----------------------------------------------------------

if(cntrowbehavior>100){
  control=StringReplace(behavior1readall,behaviorrow[0],"");
  control+=StringReplace(behavior1readall,behaviorrow[1],"");
    string Fdb2 = FileOpen(FileDBarchivos,FILE_WRITE);
     if(Fdb2==INVALID_HANDLE){
    printf("Fdb2 1");
    }else{
      string Fdb2w = behavior1readall;
              FileWrite(Fdb2,Fdb2w);
              FileClose(Fdb2);
       }
}
//aqui se sacarán datos en claro, como el profit medio por operacion (por sistema), mediante el ticket.
for(int cntb1=0;cntb1<cntrowbehavior;cntb1++){
StringSplit(behaviorrow[cntb1],sep,behavioritem);
ticketitem=behavioritem[0];
riesgoitem=behavioritem[1];
if(OrderSelect(ticketitem,SELECT_BY_TICKET)==true){
Tiempooperacionbehavior=OrderCloseTime()-OrderOpenTime();
tiempomedio1=tiempomedio1+Tiempooperacionbehavior;
profitmediobehavior=profitmediobehavior+OrderProfit();
}

Tiempomedioporoperacion2=tiempomedio1/cntrowbehavior;
Profitmedioporoperacion2=profitmediobehabior/cntrowbehavior;

}//fin for




}





//------------------------------------------------------------------
//GRID 2 POSITIONALOTOFORDERS - POSITION A LOT OF ORDERS
//------------------------------------------------------------------
//esto esta bien, no permitir operaciones mas malas.
  if(filternegativeopenorders==true){
    if(DiffPipsv>gridposition){
     filter1v=1;
    }else{
     filter1v=0;
    }
    if(DiffPipsc>gridposition){
    filter1c=1;
    }else{
    filter1c=0;
    }
  }
  if(filternegativeopenorders==false){
    if(DiffPipsv>gridposition&&profitordersV<0){ //&&lastorderpS1<0
     filter1v=1;
    }else{
     filter1v=0;
    }
    if(DiffPipsc>gridposition&&profitordersC<0){ //&&lastorderpB1<0
    filter1c=1;
    }else{
    filter1c=0;
    }
  }



   if(next_candle<=Time[0])
      {
         next_candle=Time[0]+Period();
         // New candle. Your trading functions here

          double MyPoint=Point;

   if(TotalOrdersCount()>=0&&TotalOrdersCount()<199)
     {


     int result=0;



//------------------------------------------------------------------
// GESTION LOTES
//------------------------------------------------------------------
// Esto se vera influenciado por el BEHAVIOUR siguiendo varias probabilidades, riesgo
// (mayor riesgo mas pequeña inversion), SIN MARTINGALE. Rentabilidad en tiempo, Inversion realizada,
// en funciona a las probabilidades de perdidas se observa un capital optimo. y riesgo de default que
// ayudara a definir el capital medio, minimo y maximo de inversion recomendado.

double lotesposicionc=0;
double lotesposicionv=0;

if(gestionlotesmethod==4){
//Se obeserva el BEHAVIOR y segun el riesgo, probabilidad, rentabilidad del sistema, lotes inicial,
//Existe lotes maximo conforme a un porcentaje del capital maximo para invertir. Segundo lotes minimo.
//en funcion a lo permitido, para poder hacer mas estadisticas.


}


    //------------------------------------------------------------------
    // APERTURA
    //------------------------------------------------------------------

// Si el triger de sistema es enviado, se coteja con riesgo minimo,
// se envia operacion y se crea un archivo con nombre de ticket. con informacion importante de envio, por el momento
// se pone el sistema de entrada.
//
// De momento pondremos en el comentario el sistema para facilitar la programación.



if(spreadvalue<maxspread){
  if(posicionesabiertasrobotc==0&&op=1){
    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,commentID,MagicNumber,0,Blue);
  }
  if(posicionesabiertasrobotc>0&&filter1c&&op=1){
    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,commentID,MagicNumber,0,Blue);
  }
  if(posicionesabiertasrobotv==0&&op=2){
    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,commentID,MagicNumber,0,Red);
  }
  if(posicionesabiertasrobotv>0&&filter1v&&op=2){
    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,commentID,MagicNumber,0,Red);
  }
}






//---------------------------------------------------------------------
// pips modify demomento no se va a utilizar, aunque puede servir para precios objetivos, ya se vera.
//---------------------------------------------------------------------
int pipsmodify2V=pipsmodify;
int pipsmodify2C=pipsmodify;
if(ordertpmodify==true){
  for(int c2=0;c2<OrdersTotal();c2++){
  OrderSelect(c2,SELECT_BY_POS,MODE_TRADES);
  double takeprofitmodifyS=0;
  double takeprofitmodifyB=0;
  if(OrderSymbol()==Symbol()&&OrderComment()==commentID){
  if(OrderType()==OP_SELL){
   takeprofitmodifyS = NormalizeDouble(lastorderopenpriceV-(pipsmodify2V*MarketInfo(Symbol(),MODE_POINT)),MODE_DIGITS);
    if(takeprofitmodifyS>0&&OrderTakeProfit()==0&&OrderTakeProfit()!=takeprofitmodifyS&&OrderTicket()>0){
      OrderModify(OrderTicket(),OrderOpenPrice(),0,takeprofitmodifyS,0,Red);
    }
  }
  if(OrderType()==OP_BUY){
   takeprofitmodifyB = NormalizeDouble(lastorderopenpriceC+(pipsmodify2C*MarketInfo(Symbol(),MODE_POINT)),MODE_DIGITS);
  if(takeprofitmodifyB>0&&OrderTakeProfit()==0&&OrderTakeProfit()!=takeprofitmodifyB&&OrderTicket()>0){
    OrderModify(OrderTicket(),OrderOpenPrice(),0,takeprofitmodifyB,0,Blue);
    }
  }
  }
  }
}





}//FIN TOTAL ORDERS 0 199


 if(GetLastError()==true){
   printf(GetLastError());
 }



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
