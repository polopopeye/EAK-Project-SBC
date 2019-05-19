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
  double maxspread=101;

  //+---------------------------------------------------------------------+
bool debugoption=true;
bool advanceddebug=false;
string commentID="error";
 string semaforv2="SEMAFOR V2";
 bool semafor2ind=true;
 string cogindv2t="CENTEROFGRAVITY";
 bool cogindv2=true;

extern string GESTIONLOTES="METODO 1 MARTINGALE, METODO 2 EN CONSTRUCCION --------------";
 int gestionlotesmethod=4;
extern double lotesinicial=0.1; //first lot

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
ushort seprow=StringGetCharacter("_",0);


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


  ObjectSetText(Symbol()+"secreco","BR"+brsecreco+" DD"+ddsecreco+" BM"+Bmes+" SPR"+spreadvalue,10,NULL,Orange);
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
int cierreop=0;
//ESTRATEGIA1 - S1
bool s1=true;
bool s2=false;
bool s3=false;
bool s4=false;
int activadasestrategias=1;
//----------- FORMULAS INTERESANTES ----------------//
//double interestrates=expectedvalue1/priceima;
//double interestrates=crecimiento*inflacion*riesgo;
//double riesgo*crecimiento=interestrates/inflacion;
//double RAIZCUADRADA(riesgo*crecimiento)=riesgo (aproximado)
//double expectedvalue1*p+expectedvalue2*(1-p)=priceima;
//
// if(s1==true){
//   Tiempomedioporoperacion=14400;
//
//   double cognumbera = iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,3,0);
//   double cognumberb = iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,1,0);
//   double cognumberc = iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,2,0);
//   double cognumberd = iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,4,0);
//
//   if(priceima>cognumbera){
//     //venta
//     commentID="S1";
//   op=2;
//   cierreop=1;
//   expectedvalue1=cognumberd;
//   expectedvalue2=cognumbera*1.1;
//   interestrates=expectedvalue1/priceima;
//   riesgoporcrecimiento=interestrates/inflacion;
//   riesgo=MathSqrt(riesgoporcrecimiento);
//   // probabilidad=expectedvalue1*p+expectedvalue2*(1-p)=priceima;
//   // expectedvalue1*p+expectedvalue2-expectedvalue2*p=priceima;
//   // expectedvalue1-expectedvalue2=priceima-expectedvalue2;
//   probabilidad=(priceima-expectedvalue2)/(expectedvalue1-expectedvalue2);
//   }
//   if(priceima<cognumberd){
//     //compra
//     commentID="S1";
//   op=1;
//   cierreop=2;
//   expectedvalue1=cognumbera;
//   expectedvalue2=cognumberd*1.1;
//   interestrates=expectedvalue1/priceima;
//   riesgoporcrecimiento=interestrates/inflacion;
//   riesgo=MathSqrt(riesgoporcrecimiento);
//   probabilidad=(priceima-expectedvalue2)/(expectedvalue1-expectedvalue2);
//   }
// }



//
// if(s2==true){
//   //Tiempomedioporoperacion=14400;
//
//   double semaforindv2B = 0;
//   semaforindv2B = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,4,1);
//   double semaforindv2S = 0;
//   semaforindv2S = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,5,1);
//   if(semaforindv2B==NULL||semaforindv2B==EMPTY_VALUE){
//     //PRsemaforC=0.6;
//   }else{
//     commentID="S2";
//     op=1;
//     cierreop=2;
//     expectedvalue1=semaforindv2B*1.2;
//     expectedvalue2=semaforindv2B/1.2;
//     interestrates=expectedvalue1/priceima;
//     riesgoporcrecimiento=interestrates/inflacion;
//     riesgo=MathSqrt(riesgoporcrecimiento);
//     probabilidad=(priceima-expectedvalue2)/(expectedvalue1-expectedvalue2);
//
//
//   }
//   if(semaforindv2S==NULL||semaforindv2S==EMPTY_VALUE){
//     //PRsemaforV=0.6;
//
//   }else{
//     commentID="S2";
//     op=2;
//     cierreop=1;
//     expectedvalue1=semaforindv2S*1.2;
//     expectedvalue2=semaforindv2S/1.2;
//     interestrates=expectedvalue1/priceima;
//     riesgoporcrecimiento=interestrates/inflacion;
//     riesgo=MathSqrt(riesgoporcrecimiento);
//     probabilidad=(priceima-expectedvalue2)/(expectedvalue1-expectedvalue2);
//   }
// }


// if(s1==true){
//   int op2;
//   op2 = iCustom(Symbol(),PERIOD_M5,"EAKcanaldow",2,0);
//
// if(op2!=EMPTY_VALUE&&op2!=0){
//   commentID="S1";
// cierreop=iCustom(Symbol(),PERIOD_M5,"EAKcanaldow",5,0);
// op=op2;
// riesgo = iCustom(Symbol(),PERIOD_M5,"EAKcanaldow",3,0);
// probabilidad = iCustom(Symbol(),PERIOD_M5,"EAKcanaldow",4,0);
// Tiempomedioporoperacion=iCustom(Symbol(),PERIOD_M5,"EAKcanaldow",6,0);
// }
// }

if(s1==true){
  double op5=iCustom(Symbol(),PERIOD_M5,"EAKBINOPT",1,0);
  double cop5=iCustom(Symbol(),PERIOD_M5,"EAKBINOPT",2,0);
  if(op5!=EMPTY_VALUE&&op5!=0){
        commentID="S1";
        op=op5;
  }
  if(cop5!=EMPTY_VALUE&&cop5!=0){
        commentID="S1";
        cierreop=cop5;
  }
}

if(s2==true){
  double op4=iCustom(Symbol(),PERIOD_M5,"EAKrmi",1,0);
  double cop4=iCustom(Symbol(),PERIOD_M5,"EAKrmi",2,0);
  if(op4!=EMPTY_VALUE&&op4!=0){
        commentID="S2";
        op=op4;
  }
  if(cop4!=EMPTY_VALUE&&cop4!=0){
        commentID="S2";
        cierreop=cop4;
  }
}

if(s3==true){
  double op1=iCustom(Symbol(),PERIOD_M5,"EAKyzyz",1,0);
  double cop1=iCustom(Symbol(),PERIOD_M5,"EAKyzyz",2,0);
  if(op1!=EMPTY_VALUE&&op1!=0){
        commentID="S3";
        op=op1;
  }
  if(cop1!=EMPTY_VALUE&&cop1!=0){
        commentID="S3";
        cierreop=cop1;
  }

}

if(s4==true){
  double op3,cierreop3;
  op3 = iCustom(Symbol(),PERIOD_M5,"EAKmarkowmodel",4,0);
  cierreop3=iCustom(Symbol(),PERIOD_M5,"EAKmarkowmodel",5,0);
if(op3>0){
commentID="S4";
op=op3;
cierreop=cierreop3;
riesgo=iCustom(Symbol(),PERIOD_M5,"EAKmarkowmodel",6,0);
probabilidad=iCustom(Symbol(),PERIOD_M5,"EAKmarkowmodel",7,0);
}

}

// if(s3==true){
//   double op4 = iCustom(Symbol(),PERIOD_M5,"EAKOceanTrend",6,0);
//   double cierreop4 = iCustom(Symbol(),PERIOD_M5,"EAKOceanTrend",7,0);
//   if(op4!=EMPTY_VALUE&&op4!=0){
//     commentID="S3";
//     op=op4;
//     cierreop=cierreop4;
//   }
//
// }



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

string FileDBarchivos, FileDBarchivos2,FDBread4r[];
double RiskBehavior=0,nota=0,ProbabilidadBehavior,NotaBehavior,TiempoBehavior;
double FProfitBehavior=0;
int SegundosElapsed=0;
string FDBread1r;
string nuevosdatos;

int posicionesS1C=0,posicionesS2C=0,posicionesS3C=0,posicionesS4C=0,posicionesS5C=0;
int posicionesS1V=0,posicionesS2V=0,posicionesS3V=0,posicionesS4V=0,posicionesS5V=0;
double pfS1C=0,pfS2C=0,pfS3C=0,pfS4C=0,pfS5C=0;
double pfS1V=0,pfS2V=0,pfS3V=0,pfS4V=0,pfS5V=0;
for(int posicionS=0; posicionS<OrdersTotal();posicionS++) {
  OrderSelect(posicionS,SELECT_BY_POS,MODE_TRADES);
  if(OrderSymbol()==Symbol()&&OrderComment()=="S1"){
if(OrderType()==OP_BUY){
  pfS1C=pfS1C+OrderProfit();
  posicionesS1C++;
}
if(OrderType()==OP_SELL){
  pfS1V=pfS1V+OrderProfit();
  posicionesS1V++;
}
  }
  if(OrderSymbol()==Symbol()&&OrderComment()=="S2"){
if(OrderType()==OP_BUY){
  pfS2C=pfS2C+OrderProfit();
  posicionesS2C++;
}
if(OrderType()==OP_SELL){
  pfS2V=pfS2V+OrderProfit();
  posicionesS2V++;
}
  }
  if(OrderSymbol()==Symbol()&&OrderComment()=="S3"){
if(OrderType()==OP_BUY){
  pfS3C=pfS3C+OrderProfit();
  posicionesS3C++;
}
if(OrderType()==OP_SELL){
  pfS3V=pfS3V+OrderProfit();
  posicionesS3V++;
}
  }
  if(OrderSymbol()==Symbol()&&OrderComment()=="S4"){
if(OrderType()==OP_BUY){
  pfS4C=pfS4C+OrderProfit();
  posicionesS4C++;
}
if(OrderType()==OP_SELL){
  pfS4V=pfS4V+OrderProfit();
  posicionesS4V++;
}
  }
  if(OrderSymbol()==Symbol()&&OrderComment()=="S5"){
if(OrderType()==OP_BUY){
  pfS5C=pfS5C+OrderProfit();
  posicionesS5C++;
}
if(OrderType()==OP_SELL){
  pfS5V=pfS5V+OrderProfit();
  posicionesS5V++;
}
  }
}
int posicionSB=1;
double pfSGBC=0,pfSGBV=0;
if(commentID=="S1"){
  pfSGBC=pfS1C;
  pfSGBV=pfS1V;
  if(op==1){
    posicionSB=posicionesS1C;
  }
  if(op==2){
    posicionSB=posicionesS1V;
  }
}
if(commentID=="S2"){
  pfSGBC=pfS2C;
  pfSGBV=pfS2V;
  if(op==1){
    posicionSB=posicionesS2C;
  }
  if(op==2){
    posicionSB=posicionesS2V;
  }
}
if(commentID=="S3"){
  pfSGBC=pfS3C;
  pfSGBV=pfS3V;
  if(op==1){
    posicionSB=posicionesS3C;
  }
  if(op==2){
    posicionSB=posicionesS3V;
  }
}
if(commentID=="S4"){
  pfSGBC=pfS4C;
  pfSGBV=pfS4V;
  if(op==1){
    posicionSB=posicionesS4C;
  }
  if(op==2){
    posicionSB=posicionesS4V;
  }
}
if(commentID=="S5"){
  pfSGBC=pfS5C;
  pfSGBV=pfS5V;
  if(op==1){
    posicionSB=posicionesS5C;
  }
  if(op==2){
    posicionSB=posicionesS5V;
  }
}

for(int cnta1=0;cnta1<OrdersTotal();cnta1++){
  OrderSelect(cnta1,SELECT_BY_POS,MODE_TRADES);
  FileDBarchivos=OrderComment()+Symbol()+".eakdb";
  FileDBarchivos2="R"+OrderComment()+Symbol()+".eakdb";
   bool cierre=false;

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

if(FileIsExist(FileDBarchivos2)){
  string FDBread3 = FileOpen(FileDBarchivos2,FILE_READ);
  if(FDBread3==INVALID_HANDLE){
  printf("FDBread3 1");
  }else{
   string FDBread3r = FileReadString(FDBread3);
  FileClose(FDBread3);
  }
  StringSplit(FDBread3r,sep,FDBread4r);
  FProfitBehavior=FDBread4r[0];
  RiskBehavior=FDBread4r[1];
  ProbabilidadBehavior=FDBread4r[2];
  NotaBehavior=FDBread4r[3];
  TiempoBehavior=FDBread4r[4];
}


double TiempoElapsedBehavior=SegundosElapsed;
double FProfitBehavior2=(OrderProfit()/OrderLots())/TiempoElapsedBehavior;

// if(TiempoElapsedBehavior<TiempoBehavior){
//   RiskBehavior=RiskBehavior/1.15;
// }
// if(TiempoElapsedBehavior>TiempoBehavior){
//   RiskBehavior=RiskBehavior*1.15;
// }

if(OrderComment()==commentID){
  if(FProfitBehavior2>=FProfitBehavior)nota++;
  if(FProfitBehavior2<FProfitBehavior)nota--;
  if(OrderProfit()>0)nota++;
  if(OrderProfit()<0)nota--;
  //if(riesgo<RiskBehavior)nota++;
  //if(riesgo>RiskBehavior)nota--;
  if(TiempoElapsedBehavior<TiempoBehavior)nota++;
  int tiempocierre=0;
  if(TiempoElapsedBehavior>TiempoBehavior){
  nota--;
  tiempocierre=1;
  }
  //if(probabilidad>ProbabilidadBehavior)nota++;
  //if(probabilidad<ProbabilidadBehavior)nota--;
  if(nota>NotaBehavior)nota++;
  if(nota<NotaBehavior)nota--;


  // if(OrderType()==OP_BUY&&cierreop==1&&pfSGBC>0&&posicionSB<5){
  //     cierre=true;
  //     OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);
  // }
  // if(OrderType()==OP_SELL&&cierreop==2&&pfSGBV>0&&posicionSB<5){
  //     cierre=true;
  //     OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
  // }

  // if(OrderType()==OP_BUY&&cierreop==1&&posicionSB>4){
  //     cierre=true;
  //     OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);
  // }
  // if(OrderType()==OP_SELL&&cierreop==2&&posicionSB>4){
  //     cierre=true;
  //     OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
  // }

  if(OrderType()==OP_BUY&&cierreop==1){
      cierre=true;
      OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);
  }
  if(OrderType()==OP_SELL&&cierreop==2){
      cierre=true;
      OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
  }


}







    //--------------------------------------------------------
  }//Fin If



  //----------------------------------------------------------
  //DBARCHIVOS
  //----------------------------------------------------------
  //Primero observa si ya hay archivos, si los hay mantener los datos anteriores y
  //guardarlos en una variable.
if(OrderComment()==commentID){
  if(FileIsExist(FileDBarchivos)){
    string FDBread1 = FileOpen(FileDBarchivos,FILE_READ);
    if(FDBread1==INVALID_HANDLE){
    printf("FDBread1 1");
    }else{
     FDBread1r = FileReadString(FDBread1);
    FileClose(FDBread1);
    }
  }

  //Añadir los datos anteriores y escrivir nuevos datos.
  if(cierre==true){
    nuevosdatos=OrderTicket()+":"+riesgo+":"+probabilidad+":"+nota+"_";
    string Fdb1 = FileOpen(FileDBarchivos,FILE_WRITE);
     if(Fdb1==INVALID_HANDLE){
    printf("Fdb1 1");
    }else{
      string Fdb1w = FDBread1r+nuevosdatos;
              FileWrite(Fdb1,Fdb1w);
              FileClose(Fdb1);

       }
  }
}
}//Fin For

//----------------------------------------------------------
//CUERPO DEL BEHAVIOR
//----------------------------------------------------------
string behaviorrow[],behavioritem[];
int cntrowbehavior=0;
int ticketitem=0;
double riesgoitem=0;
double probabilidaditem=0;
double Tiempooperacionbehavior,tiempomedio1,Tiempomedioporoperacion2,riesgomedio1,probabilidadmedia1,Lotesmedioporoperacionbehaviour,notaitem,notamedia1,notamedia2;
double profitmediobehavior,Profitmedioporoperacion2, factorprofit,riesgomedioporoperacion2,probabilidadmediaporoperacion2,Lotesmedioporoperacion2behaviour;
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
string borrar=behaviorrow[0]+"_";
//printf("borrar"+borrar);
  //-----------------------------------------------------------
  //
  // Se acceden a los archivos de cada sistema, se verifica si hay mas de x operaciones
  // si hay mas, se elimina del archivo la op 1. con un search and replace.
  //
  //-----------------------------------------------------------
  if(cntrowbehavior>500){
    if(StringReplace(behavior1readall,borrar,"")){
      string Fdb2 = FileOpen(FileDBarchivos,FILE_WRITE);
       if(Fdb2==INVALID_HANDLE){
      printf("Fdb2 1");
      }else{
        string Fdb2w = behavior1readall;
                FileWrite(Fdb2,Fdb2w);
                FileClose(Fdb2);
         }
    }
  }

//aqui se sacarán datos en claro, como el profit medio por operacion (por sistema), mediante el ticket.
for(int cntb1=0;cntb1<cntrowbehavior;cntb1++){
StringSplit(behaviorrow[cntb1],sep,behavioritem);
ticketitem=behavioritem[0];
riesgoitem=behavioritem[1];
probabilidaditem=behavioritem[2];
notaitem=behavioritem[3];
//printf("ticket"+ticketitem);

if(OrderSelect(ticketitem,SELECT_BY_TICKET)==true){
Lotesmedioporoperacionbehaviour=Lotesmedioporoperacionbehaviour+OrderLots();
Tiempooperacionbehavior=OrderCloseTime()-OrderOpenTime();
tiempomedio1=tiempomedio1+Tiempooperacionbehavior;
profitmediobehavior=profitmediobehavior+OrderProfit();
riesgomedio1=riesgomedio1+riesgoitem;
probabilidadmedia1=probabilidadmedia1+probabilidaditem;
notamedia1=notamedia1+notaitem;
}
}//fin for
notamedia2=notamedia1/cntrowbehavior;
Lotesmedioporoperacion2behaviour=Lotesmedioporoperacionbehaviour/cntrowbehavior;
Tiempomedioporoperacion2=tiempomedio1/cntrowbehavior;
Profitmedioporoperacion2=profitmediobehavior/cntrowbehavior;
factorprofit=(Profitmedioporoperacion2/Lotesmedioporoperacion2behaviour)/Tiempomedioporoperacion2;
riesgomedioporoperacion2=riesgomedio1/cntrowbehavior;
probabilidadmediaporoperacion2=probabilidadmedia1/cntrowbehavior;

//-----------------------------------------------------------
// Rarchivos Sistema, se guardan los datos en cada actualizacion
//-----------------------------------------------------------
if(cierre==true){
  string rfilesistema="R"+FileDBarchivos;
  string Rdb2 = FileOpen(rfilesistema,FILE_WRITE);
   if(Rdb2==INVALID_HANDLE){
  printf("Rdb2 1");
  }else{
    string Rdb2w = factorprofit+":"+riesgomedioporoperacion2+":"+probabilidadmediaporoperacion2+":"+notamedia2+":"+Tiempomedioporoperacion2;
            FileWrite(Rdb2,Rdb2w);
            FileClose(Rdb2);
     }
}


//-----------------------------------------------------------
// BEHAVIOR - COMPETICIÓN DE SISTEMAS
//-----------------------------------------------------------

//printf("TMO: "+Tiempomedioporoperacion2+" PMO:"+Profitmedioporoperacion2+" "+FileDBarchivos+" I"+cntrowbehavior);

// string Rbehavior1read2[10,10];
string ResultarrayS[];
double Itemsistem1[10];
double Itemsistem2[10];
double Itemsistem3[10];
double Itemsistem4[10];
double Itemsistem5[10];

for(int cntrs=0;cntrs<=activadasestrategias;cntrs++){
string rsfile="RS"+cntrs+Symbol()+".eakdb";
if(FileIsExist(rsfile)){
  string Rbehavior1read = FileOpen(rsfile,FILE_READ);
  if(Rbehavior1read==INVALID_HANDLE){
  printf("behavior1read 1");
  }else{
  string Readsistembehavior = FileReadString(Rbehavior1read);
  FileClose(Rbehavior1read);
  }
  StringSplit(Readsistembehavior,sep,ResultarrayS);
  Itemsistem1[cntrs]=ResultarrayS[0];
  Itemsistem2[cntrs]=ResultarrayS[1];
  Itemsistem3[cntrs]=ResultarrayS[2];
  Itemsistem4[cntrs]=ResultarrayS[3];
  Itemsistem5[cntrs]=ResultarrayS[4];
  // Rbehavior1read2[cntrs,0]=ResultarrayS[0];
  // Rbehavior1read2[cntrs,1]=ResultarrayS[1];
}
}


int profitMBad = ArrayMinimum(Itemsistem1,activadasestrategias,1);
int profitMB = ArrayMaximum(Itemsistem1,activadasestrategias,1);
int riesgoMBad = ArrayMaximum(Itemsistem2,activadasestrategias,1);
int riesgoMB = ArrayMinimum(Itemsistem2,activadasestrategias,1);
int probabilidadMB = ArrayMaximum(Itemsistem3,activadasestrategias,1);
int probabilidadMBad = ArrayMinimum(Itemsistem3,activadasestrategias,1);
int notaMB = ArrayMaximum(Itemsistem4,activadasestrategias,1);
int notaMBad = ArrayMinimum(Itemsistem4,activadasestrategias,1);
int tiempoMBad = ArrayMaximum(Itemsistem5,activadasestrategias,1);
int tiempoMB = ArrayMinimum(Itemsistem5,activadasestrategias,1);

//printf("profitMB: "+profitMB+" riesgoMB: "+riesgoMB+" Prob: "+probabilidadMB+" Nota: "+notaMB+"("+Itemsistem4[notaMB]+")");
// printf("Itemsistem1 1: "+Itemsistem2[1]);
// printf("Itemsistem1 2: "+Itemsistem2[2]);




}




//------------------------------------------------------------------
//GRID 2 POSITIONALOTOFORDERS - POSITION A LOT OF ORDERS
//------------------------------------------------------------------
//esto esta bien, no permitir operaciones mas malas.

if(posicionesabiertasrobotv==0){
  filter1v=1;
}else{
  if(DiffPipsv>gridposition&&pfSGBV<0){ //&&lastorderpS1<0
   filter1v=1;
  }else{
   filter1v=0;
  }
}
if(posicionesabiertasrobotc==0){
  filter1c=1;
}else{
  if(DiffPipsc>gridposition&&pfSGBC<0){ //&&lastorderpB1<0
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

double lotesposicionc=lotesinicial;
double lotesposicionv=lotesinicial;

if(gestionlotesmethod==4){
//Se obeserva el BEHAVIOR y segun el riesgo, probabilidad, rentabilidad del sistema, lotes inicial,
//Existe lotes maximo conforme a un porcentaje del capital maximo para invertir. Segundo lotes minimo.
//en funcion a lo permitido, para poder hacer mas estadisticas.
//tiempo promedio, cuanto mayor tiempo mas riesgo.
//riesgo,probabilidad,nota, de operaciones actuales
string MejorS="S"+notaMB;
string PeorS="S"+notaMBad;
string MejorPfS="S"+profitMB;//profit
string PeorPfS="S"+profitMBad;
string MejorPrS="S"+probabilidadMB;//Probabilidad
string PeorPrS="S"+probabilidadMBad;
string MejorRiS="S"+riesgoMB;//Riesgo
string PeorRiS="S"+riesgoMBad;
string MejorTiS="S"+tiempoMB;//tiempo
string PeorTiS="S"+tiempoMBad;
//printf(MejorS+PeorS);
//
// if(riesgo<0.5){
//   lotesposicionc=lotesposicionc*1.25;
//   lotesposicionv=lotesposicionc*1.25;
// }
// if(probabilidad>0.5){
//   lotesposicionc=lotesposicionc*1.25;
//   lotesposicionv=lotesposicionv*1.25;
// }
// if(commentID==MejorPrS){
//   lotesposicionc=lotesposicionc*1.25;
//   lotesposicionv=lotesposicionv*1.25;
// }
// if(commentID==PeorPrS){
//   lotesposicionc=lotesposicionc/1.25;
//   lotesposicionv=lotesposicionv/1.25;
// }

//martingale

if(posicionSB==0)posicionSB=1;

if(commentID==MejorPfS){
   lotesposicionc=lotesposicionc*1.1;//*posicionSB;
   lotesposicionv=lotesposicionv*1.1;//*posicionSB;
  //lotesposicionc=lotesposicionc*1.25;
  //lotesposicionv=lotesposicionv*1.25;
}
if(commentID==PeorPfS){
  lotesposicionc=lotesposicionc/1.5;
  lotesposicionv=lotesposicionv/1.5;
}

if(commentID==MejorS){
  lotesposicionc=lotesposicionc*1.1;
  lotesposicionv=lotesposicionv*1.1;
}
if(commentID==PeorS){
  lotesposicionc=lotesposicionc/1.4;
  lotesposicionv=lotesposicionv/1.4;
}
// if(commentID==MejorRiS){
//   lotesposicionc=lotesposicionc*1.25;
//   lotesposicionv=lotesposicionv*1.25;
// }
// if(commentID==PeorRiS){
//   lotesposicionc=lotesposicionc/1.25;
//   lotesposicionv=lotesposicionv/1.25;
// }
if(lotesposicionc<minlots){
  lotesposicionc=minlots;
}
if(lotesposicionv<minlots){
  lotesposicionv=minlots;
}

//la idea es que el sistema invierta en los primeros sistemas y minimamanete en los malos.
//el mejor sistema tendra un 3, un mal sistema tendra un 1 y uno normal un 2.




}


    //------------------------------------------------------------------
    // APERTURA
    //------------------------------------------------------------------

// Si el triger de sistema es enviado, se coteja con riesgo minimo,
// se envia operacion y se crea un archivo con nombre de ticket. con informacion importante de envio, por el momento
// se pone el sistema de entrada.
//
// De momento pondremos en el comentario el sistema para facilitar la programación.

double precio=SymbolInfoDouble(Symbol(),SYMBOL_BID);
color clrR=clrRed;
color clrB=clrBlue;

if(spreadvalue<maxspread){
  if(op==1&&filter1c==1&&commentID!="error"){
    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,commentID,MagicNumber,0,Blue);
      ObjectCreate(ChartID(),Time[0],OBJ_TEXT,0,TimeCurrent(),precio);
      ObjectSetString(ChartID(),Time[0],OBJPROP_TEXT,commentID);
      ObjectSetString(ChartID(),Time[0],OBJPROP_FONT,"Arial");
     ObjectSetInteger(ChartID(),Time[0],OBJPROP_FONTSIZE,"12");
     ObjectSetInteger(ChartID(),Time[0],OBJPROP_COLOR,clrB);
  }
  if(op==2&&filter1v==1&&commentID!="error"){
    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,commentID,MagicNumber,0,Red);
ObjectCreate(ChartID(),Time[0],OBJ_TEXT,0,TimeCurrent(),precio);
ObjectSetString(ChartID(),Time[0],OBJPROP_TEXT,commentID);
ObjectSetString(ChartID(),Time[0],OBJPROP_FONT,"Arial");
ObjectSetInteger(ChartID(),Time[0],OBJPROP_FONTSIZE,"12");
ObjectSetInteger(ChartID(),Time[0],OBJPROP_COLOR,clrR);

  }
  // if(posicionesabiertasrobotv>0&&op==2){
  //   OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,commentID,MagicNumber,0,Red);
  // }
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
