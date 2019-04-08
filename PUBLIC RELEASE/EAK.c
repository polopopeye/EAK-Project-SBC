//+------------------------Kenneth Suarez-------------------------------+


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
string commentID="EAK";
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

if(next_candle<=Time[0])
   {
     MathSrand(TimeCurrent());
     int num = (MathRand()%300) + 1;     // random number between 1 to 10 (even distribution)
     double num2=num*0.1;
     if(num2<=0.1){
       num2=1;
     }
     printf("num2:"+num2);
      }


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
     // FILTROS E INDICADORES
     //------------------------------------------------------------------
double priceima = iMA(Symbol(),PERIOD_M1,1,0,MODE_EMA,PRICE_MEDIAN,0);
double PRcogB=0;
double PRcogS=0;
double CcogB = 1;
double CcogS = 1;

if(cogindv2==true){
  double cognumbera = iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,3,0);
  double cognumberb = iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,1,0);
  double cognumberc = iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,2,0);
  double cognumberd = iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,4,0);

  double cognumberap = iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,3,1);
  double cognumberbp = iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,1,1);
  double cognumbercp = iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,2,1);
  double cognumberdp = iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,4,1);

if(priceima>cognumbera&&cognumberap>cognumbera){
  //venta
PRcogS=0.60;
}else{
PRcogS=0;
}
if(priceima<cognumberd&&cognumberdp<cognumberd){
  //compra
PRcogB=0.60;
}else{
PRcogB=0;
}

ObjectSetText(Symbol()+"cog","COG  S:"+PRcogS+" B:"+PRcogB,7,NULL,Orange);
  ObjectSet(Symbol()+"cog",OBJPROP_CORNER,0);
  ObjectSet(Symbol()+"cog",OBJPROP_XDISTANCE,15);
  ObjectSet(Symbol()+"cog",OBJPROP_YDISTANCE,150);

}




//SpearmanRank

double PRspearmanRankB,PRspearmanRankS;
double spearmanrankA=iCustom(Symbol(),PERIOD_M15,"SpearmanRankCorr",14,0,30,true,0,0);
//printf("Spearman"+spearmanrankA);
if(spearmanrankA>0){
  //PermitirCompra;
  PRspearmanRankB=0.7;
  PRspearmanRankS=0;
}else{
  //permitirVenta;
  PRspearmanRankB=0;
  PRspearmanRankS=0.7;

}



if(Extrapolatorind==true){
  double PRextrapolatorB,PRextrapolatorS,riskextrapolatorc, riskextrapolatorv;
  int extrapolatortend=0;
  double extrapolatorA = iCustom(Symbol(),PERIOD_M15,"Extrapolator",Methodextrapolator,30,300,0.6,100,20,0.0001,0,1,0);
  double extrapolatorB = iCustom(Symbol(),PERIOD_M1,"Extrapolator",Methodextrapolator,30,300,0.6,100,20,0.0001,0,1,0);
if(extrapolatorA>priceima){//&&extrapolatorB>priceima
  extrapolatortend=2;
  PRextrapolatorS=0.6;
  PRextrapolatorB=0;
  riskextrapolatorc=Extrapolatorbadop;
  riskextrapolatorv=Extrapolatorgoodop;
   if(debugoption==true){
     ObjectSetText(Symbol()+"Extrapolator","Extrapolator -> Venta"+riskextrapolatorv+" "+riskextrapolatorc,7,NULL,Red);
       ObjectSet(Symbol()+"Extrapolator",OBJPROP_CORNER,0);
       ObjectSet(Symbol()+"Extrapolator",OBJPROP_XDISTANCE,15);
       ObjectSet(Symbol()+"Extrapolator",OBJPROP_YDISTANCE,50);
   }
}
if(extrapolatorA<priceima){//&&extrapolatorB<priceima
  extrapolatortend=1;
  PRextrapolatorB=0.6;
  PRextrapolatorS=0;
   riskextrapolatorc=Extrapolatorgoodop;
   riskextrapolatorv=Extrapolatorbadop;
   if(debugoption==true){
     ObjectSetText(Symbol()+"Extrapolator","Extrapolator -> Compra"+riskextrapolatorc+" "+riskextrapolatorv,7,NULL,Blue);
     ObjectSet(Symbol()+"Extrapolator",OBJPROP_CORNER,0);
     ObjectSet(Symbol()+"Extrapolator",OBJPROP_XDISTANCE,15);
     ObjectSet(Symbol()+"Extrapolator",OBJPROP_YDISTANCE,50);
   }
}

}




if(semafor2ind==true){
int semtC,semtV,semtC1,semtC2,semtV1,semtV2;
semtC=num2*10;
semtV=num2*10;
semtC1=num2*20;
semtV1=num2*20;
semtC2=num2*40;
semtV2=num2*40;


double semaforindv2B = 0;
semaforindv2B = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",semtC,semtC1,semtC2,4,1);
double semaforindv2S = 0;
semaforindv2S = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",semtV,semtV1,semtV2,5,1);
  //double semaforindv2BC = iCustom(Symbol(),PERIOD_M1,"semaforov2eak",10,20,800,4,1);
  //double semaforindv2SC = iCustom(Symbol(),PERIOD_M1,"semaforov2eak",10,20,800,5,1);
  double PRsemaforC=0;
  double PRsemaforV=0;
  double PRsemaforC2=0;
  double PRsemaforV2=0;
if(semaforindv2B==NULL||semaforindv2B==EMPTY_VALUE){
  //PRsemaforC=0.6;
 PRsemaforC=0;
}else{
  PRsemaforC=0.6;
}
if(semaforindv2S==NULL||semaforindv2S==EMPTY_VALUE){
  //PRsemaforV=0.6;
  PRsemaforV=0;
}else{
  PRsemaforV=0.6;
}



}



 //------------------------------------------------------------------
 // EOPR
 //------------------------------------------------------------------

string Favramisgop=Symbol()+"avrgop";
double RAIavramis=1;
if(FileIsExist(Favramisgop)==true){
  string avramisia = FileOpen(Favramisgop,FILE_READ);
  if(avramisia==INVALID_HANDLE){
  printf("File Read Error 1");
  }else{
  RAIavramis = FileReadString(avramisia);
  FileClose(avramisia);
  }
  // StringSplit(RAIavramis,sep,CierreOC1);
  // double PFLCierreC=CierreOC1[0];
  // double TELCierreC=CierreOC1[1];
}else{
  //AVROP
   string avramisia2 = FileOpen(Favramisgop,FILE_WRITE);
    if(avramisia2==INVALID_HANDLE){
   printf("GF Error 3");
   }else{
     string writefirstd = "1";
             FileWrite(avramisia2,writefirstd);
             FileClose(avramisia2);
      }
  //AVROP
}

int pa=9,pb=26,pc=52;
double pda=NormalizeDouble(RAIavramis*pa,0);
double pdb=NormalizeDouble(RAIavramis*pb,0);
double pdc=NormalizeDouble(RAIavramis*pc,0);
printf(RAIavramis+":pda"+pda+"-pdb"+pdb);

int avramis=0;
double avramisgoodop=1.50;
double avramisbadop=0.70;
double avramisc,avramisv;
 avramisc = iCustom(Symbol(),PERIOD_M15,"Cronex_Taichi",pda,pdb,pdc,0,0);
 avramisv = iCustom(Symbol(),PERIOD_M15,"Cronex_Taichi",pda,pdb,pdc,3,0);
double avrLPC,avrLPV;
double PRavrC=0,PRavrV=0;
if(avramisc>avramisv){
  PRavrC=1;
  avrLPC=avramisgoodop;
  PRavrV=0;
  avrLPV=avramisbadop;
}
if(avramisv>avramisc){
  PRavrC=0;
  PRavrV=1;
  avrLPC=avramisbadop;
  avrLPV=avramisgoodop;
}








 double tmaslopeC = iCustom(Symbol(),PERIOD_M5,"tma_slope_nrp_alerts",75,150,5,true,0.005,-0.005,"EAK",false,false,false,false,false,false,2,0);
 double tmaslopeCp = iCustom(Symbol(),PERIOD_M5,"tma_slope_nrp_alerts",75,150,5,true,0.005,-0.005,"EAK",false,false,false,false,false,false,2,1);
 double tmaslopeV = iCustom(Symbol(),PERIOD_M5,"tma_slope_nrp_alerts",75,150,5,true,0.005,-0.005,"EAK",false,false,false,false,false,false,3,0);
 double tmaslopeVp = iCustom(Symbol(),PERIOD_M5,"tma_slope_nrp_alerts",75,150,5,true,0.005,-0.005,"EAK",false,false,false,false,false,false,3,1);
 double tmaslopeCp1 = iCustom(Symbol(),PERIOD_M5,"tma_slope_nrp_alerts",75,150,5,true,0.005,-0.005,"EAK",false,false,false,false,false,false,2,2);
 double tmaslopeVp1 = iCustom(Symbol(),PERIOD_M5,"tma_slope_nrp_alerts",75,150,5,true,0.005,-0.005,"EAK",false,false,false,false,false,false,3,2);




 int tma1c=0,tma1v=0,tma2c=0,tma2v=0,tma3c=0,tma3v=0;

if(tmaslopeC!=EMPTY_VALUE)tma1c=1;
if(tmaslopeV!=EMPTY_VALUE)tma1v=1;
if(tmaslopeCp!=EMPTY_VALUE)tma2c=1;
if(tmaslopeVp!=EMPTY_VALUE)tma2v=1;
if(tmaslopeCp1!=EMPTY_VALUE)tma3c=1;
if(tmaslopeVp1!=EMPTY_VALUE)tma3v=1;


double tmaC1=NormalizeDouble(tmaslopeC,4);
double tmaC2=NormalizeDouble(tmaslopeCp,4);
double tmaC3=NormalizeDouble(tmaslopeCp1,4);
double tmaV1=NormalizeDouble(tmaslopeV,4);
double tmaV2=NormalizeDouble(tmaslopeVp,4);
double tmaV3=NormalizeDouble(tmaslopeVp1,4);




double PRopenC=0;
double PRopenV=0;

double PRtrC,PRtrV;
double tr23V = iCustom(Symbol(),PERIOD_M5,"TrendSignal 2.3 mtf",PERIOD_M15,67.0,33.0,0,4,1.0,true,false,false,false,false,false,false,0,1);
double tr23C = iCustom(Symbol(),PERIOD_M5,"TrendSignal 2.3 mtf",PERIOD_M15,67.0,33.0,0,4,1.0,true,false,false,false,false,false,false,1,1);
if(tr23V!=EMPTY_VALUE){
//  printf("VENTAAAAAAAAAAAAAAAAAA");
  PRtrV=0.6;
  PRtrC=0;
}else{
  //printf("Nada");

}
if(tr23C!=EMPTY_VALUE){
//  printf("COMPRAAAAAAAAAAAAAAAAAA");
  PRtrC=0.6;
  PRtrV=0;
}else{
  //printf("Nada");
}
 //------------------------------------------------------------------
 // PROBABILIDAD
 //------------------------------------------------------------------

 double probabilidadC=0;
 double probabilidadV=0;
 double probabilidadC2=0;
 double probabilidadV2=0;
 double probabilidadC3=0;
 double probabilidadV3=0;
 int variablestotalesC=1;
 int variablestotalesV=1;
 int variablestotales2=1;
  int variablestotales3=1;
  string probabilidad0,probabilidad1;
 //double variablesprobabilidadB=PRholtB+PRsemaforC;
 //double variablesprobabilidadS=PRholtS+PRsemaforV;
 double variablesprobabilidadB=0,variablesprobabilidadB2=0,variablesprobabilidadS=0,variablesprobabilidadS2=0;


 variablestotalesC=1;
 variablestotalesV=1;


//variablesprobabilidadB=PRsemaforC;//PRavrC;//PRsemaforC;//PRhiloB
//variablesprobabilidadS=PRsemaforV;//PRsemaforV;//+PRhiloS;
variablesprobabilidadB=PRavrC;//PRavrC;//PRsemaforC;//PRhiloB
variablesprobabilidadS=PRavrV;//PRsemaforV;//+PRhiloS;

variablesprobabilidadB2=PRavrC;//+PRspearmanRankB;//+PRholtB;PRspearmanRankB;//PRopenC+PRsemaforC
variablesprobabilidadS2=PRavrV;//+PRspearmanRankB;//+PRholtB;PRspearmanRankB;//PRopenC+PRsemaforC






 probabilidadC= variablesprobabilidadB/variablestotalesC;
 probabilidadV= variablesprobabilidadS/variablestotalesV;
probabilidadC2= variablesprobabilidadB2/variablestotales2;
probabilidadV2= variablesprobabilidadS2/variablestotales2;





if(probabilidadC>probabilidadV){
  probabilidad0="Compra";
}
if(probabilidadC<probabilidadV){
  probabilidad0="Venta";
}
if(probabilidadC2>probabilidadV2){
  probabilidad1="Compra";
  //printf("HOLA COMPAAAAAAAAAAAA");
}
if(probabilidadC2<probabilidadV2){
  probabilidad1="Venta";
  //printf("HOLA ventaAAAAAAAAAAAA");

}

 ObjectSetText(Symbol()+"PR","[PR: 1"+probabilidad0+"] 2"+probabilidad1,12,NULL,Orange);
   ObjectSet(Symbol()+"PR",OBJPROP_CORNER,0);
   ObjectSet(Symbol()+"PR",OBJPROP_XDISTANCE,15);
   ObjectSet(Symbol()+"PR",OBJPROP_YDISTANCE,130);
//------------------------------------------------------------------
// CONTADOR POSICIONES ABIERTAS POR ROBOT Y CIERRE
//------------------------------------------------------------------

double LastOrderlotsv = 0;
double LastOrderlotsc = 0;
double gridpositionV=100000;
double gridpositionC=100000;
double Totalorderslotv=0;
double Totalorderslotc=0;
double tiempoelapsedS=0;
double tiempoelapsedB=0;
string FcierreV=Symbol()+"Cv";
string FcierreC=Symbol()+"Cc";
bool vctV,vctC,ordcloseC1,ordcloseV1;
int cierrecloseV=0;
int cierrecloseC=0;

for(int cnt1=0;cnt1<OrdersTotal();cnt1++)
{
OrderSelect(cnt1,SELECT_BY_POS,MODE_TRADES);
if(OrderSymbol()==Symbol()&&OrderComment()==commentID){
if(OrderType()==OP_SELL){
 LastOrderlotsv=OrderLots();
 Totalorderslotv=Totalorderslotv+OrderLots();
 tiempoelapsedS=TimeCurrent()-OrderOpenTime();//tiempo en segundos


}

if(OrderType()==OP_BUY){
  LastOrderlotsc=OrderLots();
Totalorderslotc=Totalorderslotc+OrderLots();
tiempoelapsedB=TimeCurrent()-OrderOpenTime();


}



if(probabilidadC>probabilidadV){
  if(posicionesabiertasrobotv>3){
    gridpositionV=gridposition;//*3
  }else{
    gridpositionV=gridposition;
  }
  gridpositionC=gridposition;
}else{
  if(posicionesabiertasrobotc>3){
    gridpositionC=gridposition;//*3
  }else{
    gridpositionC=gridposition;
  }
  gridpositionV=gridposition;
}



  if((OrderType()==OP_SELL&&probabilidadC2>probabilidadV2)||tiempoelapsedS>86400){
    if(posicionesabiertasrobotv>=1){
      vctV=true;
    }else{
      //CIERRE OBSERVADO
       string GFcierreV2 = FileOpen(FcierreV,FILE_WRITE);
        if(GFcierreV2==INVALID_HANDLE){
       printf("GF Error 3");
       }else{
         string FWcierreV2 = profitordersV+":"+TimeCurrent();
                 FileWrite(GFcierreV2,FWcierreV2);
                 FileClose(GFcierreV2);
          }
      //CIERRE OBSERVADO
    }
}
if((OrderType()==OP_BUY&&probabilidadV2>probabilidadC2)||tiempoelapsedB>86400){
if(posicionesabiertasrobotc>=1){
  vctC=true;
}else{
  //PRUEBA CIERRE OBSERVADO
   string GFcierreC1 = FileOpen(FcierreC,FILE_WRITE);
    if(GFcierreC1==INVALID_HANDLE){
   printf("GF Error 2");
   }else{
     string FWcierreC1 = profitordersC+":"+TimeCurrent();
             FileWrite(GFcierreC1,FWcierreC1);
             FileClose(GFcierreC1);
      }
  //FIN CIERRE OBSERVADO
}

  }

}


string CierreOC1[];
string CierreOV1[];
string CierreOC="N";
string CierreOV="N";
int TCierreObservado=TimeCurrent()-30;

double trashopC=0;
if(posicionesabiertasrobotc>0){
trashopC=profitordersC/posicionesabiertasrobotc;
}
double trashopV=0;
if(posicionesabiertasrobotv>0){
trashopV=profitordersV/posicionesabiertasrobotv;
}

//CIERRE OBSERVADO CIERRE TOTAL
 if(FileIsExist(FcierreC)==true&&OrderType()==OP_BUY&&OrderSymbol()==Symbol()&&OrderComment()==commentID){
   //printf("EXITO!");
   string FRcierreC = FileOpen(FcierreC,FILE_READ);
   if(FRcierreC==INVALID_HANDLE){
   printf("File Read Error 1");
   }else{
   CierreOC = FileReadString(FRcierreC);
   FileClose(FRcierreC);
   }
   StringSplit(CierreOC,sep,CierreOC1);
   double PFLCierreC=CierreOC1[0];
   double TELCierreC=CierreOC1[1];

   if(TCierreObservado>TELCierreC){
     if(PFLCierreC>profitordersC){
       if(OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue)){
         cierrecloseC++;
if(OrderProfit()<10){
  //cierrecloseC++;
}




           FileDelete(FcierreC);

     }
     }
     if(PFLCierreC<profitordersC){
       string GFcierreC3 = FileOpen(FcierreC,FILE_WRITE);//|FILE_READ| FILE_WRITE
        if(GFcierreC3==INVALID_HANDLE){
       printf("GF Error 5");
       }else{
         string FWcierreC3 = profitordersC+":"+TimeCurrent();
                 FileWrite(GFcierreC3,FWcierreC3);
                 FileClose(GFcierreC3);
          }
     }
   }//TIEMPO
    //COSAS POR FUERA

 }
//FIN CIERRE OBSERVADO

//CIERRE OBSERVADO CIERRE TOTAL
 if(FileIsExist(FcierreV)==true&&OrderType()==OP_SELL&&OrderSymbol()==Symbol()&&OrderComment()==commentID){
   string FRcierreV = FileOpen(FcierreV,FILE_READ);// | FILE_WRITE
   if(FRcierreV==INVALID_HANDLE){
   printf("File Read Error 2");
   }else{
   CierreOV = FileReadString(FRcierreV);
   FileClose(FRcierreV);
   }
    StringSplit(CierreOV,sep,CierreOV1);
   double PFLCierreV=CierreOV1[0];
   double TELCierreV=CierreOV1[1];

   if(TCierreObservado>TELCierreV){
     if(PFLCierreV>profitordersV){

         if(OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red)){
           cierrecloseV++;
if(cierrecloseV<0){
  //cierrecloseV++;

}

  FileDelete(FcierreV);

         }

     }else{
       string GFcierreV3 = FileOpen(FcierreV,FILE_WRITE);//|FILE_READ| FILE_WRITE
        if(GFcierreV3==INVALID_HANDLE){
       printf("GF Error 6");
       }else{
         string FWcierreV3 = profitordersV+":"+TimeCurrent();
                 FileWrite(GFcierreV3,FWcierreV3);
                 FileClose(GFcierreV3);
          }
     }
   }

 }
 //FIN cierre OBSERVADO






}//Fin cierre for


if(LastOrderlotsc>=maxlotsG){//posicionesabiertasrobotv>=lotofpos
//vctV=true;
}
// else{
// vctV=false;
// }
if(LastOrderlotsv>=maxlotsG){//&&posicionesabiertasrobotc>=lotofpos
//vctC=true;
}
// else{
// vctC=false;
// }
//printf("C:"+vctC+"V"+vctV);
int bclosedall=0;
if(vctC==true){
  if(profitordersC<0){
    bclosedall=1;
  }
  for(int cnt12=0;cnt12<OrdersTotal();cnt12++){
  OrderSelect(cnt12,SELECT_BY_POS,MODE_TRADES);
  if(OrderSymbol()==Symbol()&&OrderComment()==commentID&&OrderType()==OP_BUY){
    OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Orange);
   }
  }
}
if(vctV==true){
  if(profitordersV<0){
    bclosedall=1;
  }
  for(int cnt13=0;cnt13<OrdersTotal();cnt13++){
  OrderSelect(cnt13,SELECT_BY_POS,MODE_TRADES);
  if(OrderSymbol()==Symbol()&&OrderComment()==commentID&&OrderType()==OP_SELL){
    OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Orange);
   }
  }
}
double CSelectivoV=cierrecloseV;
double CSelectivoC=cierrecloseC;
double fincierreV=posicionesabiertasrobotv;
double fincierreC=posicionesabiertasrobotc;
  if(CSelectivoC>=fincierreC){
  FileDelete(FcierreC);
  }
  if(CSelectivoV>=fincierreV){
    FileDelete(FcierreV);
  }
//-------------------------IA-------------------------


if(bclosedall>0){
if(FileIsExist("avramisbadop.eakdb")==true){
string avramisiabop2 = FileOpen("avramisbadop.eakdb",FILE_READ);
if(avramisiabop2==INVALID_HANDLE){
printf("File Read Error 1");
}else{
string Ravramisiabop2 = FileReadString(avramisiabop2);
FileClose(avramisiabop2);
}

//AVROP
string avramisiabop3 = FileOpen("avramisbadop.eakdb",FILE_WRITE);
if(avramisiabop3==INVALID_HANDLE){
printf("GF Error 3");
}else{
string writefirstdbop3 = Ravramisiabop2+":"+RAIavramis;
  FileWrite(avramisiabop3,writefirstdbop3);
  FileClose(avramisiabop3);
}
string DBbadop[];
StringSplit(writefirstdbop3,sep,DBbadop);
int tdb=ArraySize(DBbadop);
int cambiar=0;
int cnt17=0;


while(cnt17<tdb){
if(DBbadop[cnt17]!=num2){
  cnt17++;
  //cambiar=1;
 printf("DIFERENTE POR AHORA n"+num2+" que d"+DBbadop[cnt17]);
}

if(DBbadop[cnt17]==num2){
  printf("es igual n"+num2+" que d"+DBbadop[cnt17]);
cambiar=0;
cnt17=999;
}
}
if(cnt17<998){
  cambiar=1;
}
if(cambiar==1){
  //AVROP
  string avramisia3 = FileOpen(Favramisgop,FILE_WRITE);
  if(avramisia3==INVALID_HANDLE){
  printf("GF Error 3");
  }else{
  string writefirstd3 = num2;
      FileWrite(avramisia3,writefirstd3);
      FileClose(avramisia3);
  }
  //AVROP
  printf("DIFERENTE!!!!!!!!!! n"+num2+" que d"+DBbadop[cnt17]);

}


}else{
string avramisiabop31 = FileOpen("avramisbadop.eakdb",FILE_WRITE);
if(avramisiabop31==INVALID_HANDLE){
printf("GF Error 3");
}else{
string writefirstdbop31 = RAIavramis;
   FileWrite(avramisiabop31,writefirstdbop31);
   FileClose(avramisiabop31);
}
}


//--------------------------AQUI SE PONE EL NUEVO VALOR CON OBJETIVO A MEJORAR



}


//------------------------------------------------------------------
//GRID 2 POSITIONALOTOFORDERS - POSITION A LOT OF ORDERS
//------------------------------------------------------------------

  if(filternegativeopenorders==true){
    if(DiffPipsv>gridpositionV){
     filter1v=1;
    }else{
     filter1v=0;
    }
    if(DiffPipsc>gridpositionC){
    filter1c=1;
    }else{
    filter1c=0;
    }
  }
  if(filternegativeopenorders==false){
    if(DiffPipsv>gridpositionV&&profitordersV<0){ //&&lastorderpS1<0
     filter1v=1;
    }else{
     filter1v=0;
    }
    if(DiffPipsc>gridpositionC&&profitordersC<0){ //&&lastorderpB1<0
    filter1c=1;
    }else{
    filter1c=0;
    }
  }


ObjectSetText(Symbol()+"filter1","filter1c: ["+filter1c+"]   filter1v:["+filter1v+"]",7,NULL,Orange);
  ObjectSet(Symbol()+"filter1",OBJPROP_CORNER,0);
  ObjectSet(Symbol()+"filter1",OBJPROP_XDISTANCE,15);
  ObjectSet(Symbol()+"filter1",OBJPROP_YDISTANCE,200);



   if(next_candle<=Time[0])
      {
         next_candle=Time[0]+Period();
         // New candle. Your trading functions here

          double MyPoint=Point;

   if(TotalOrdersCount()>=0&&TotalOrdersCount()<199)
     {


     int result=0;

//------------------------------------------------------------------
// CRASH
//------------------------------------------------------------------
if(posicionesabiertasrobotc>0){

}
double multiplicadorC,multiplicadorV; //Martingale factor to recover bad choices
if(posicionesabiertasrobotc>3){
multiplicadorC=1;
}else{
multiplicadorC=1;
}
if(posicionesabiertasrobotv>3){
  multiplicadorV=1;
}else{
  multiplicadorV=1;
}

double riskextrapolatorcCrash=riskextrapolatorc;
double riskextrapolatorvCrash=riskextrapolatorv;
double CcogSCrash=CcogS;
double CcogBCrash=CcogB;
double lotesinicialB=lotesinicial*0.80;
double lotesinicialG=lotesinicial*1.10;
double liquidmulti1=posicionesabiertasrobotc+posicionesabiertasrobotv;
//double liquidmulti=liquidmulti1*3;


if(posicionesabiertasrobotv>=lotofpos){

    //riskextrapolatorcCrash=riskextrapolatorc*25;//liquidmulti

}
if(posicionesabiertasrobotc>=lotofpos){
    //riskextrapolatorvCrash=riskextrapolatorc*25;//liquidmulti
}


//------------------------------------------------------------------
// GESTION LOTES
//------------------------------------------------------------------
double lotesposicionc=0;
double lotesposicionv=0;

if(gestionlotesmethod==3){
double calclotsC=LastOrderlotsc*multiplicadorC*riskextrapolatorcCrash*avrLPC;
double calclotsV=LastOrderlotsv*multiplicadorV*riskextrapolatorvCrash*avrLPC;

  if(posicionesabiertasrobotc==0){
    if(probabilidadC<probabilidadV){
    lotesposicionc=NormalizeDouble(lotesinicialB*riskextrapolatorcCrash*avrLPC,lotround);
    }else{
    lotesposicionc=NormalizeDouble(lotesinicialG*riskextrapolatorcCrash*avrLPC,lotround);
    }

  }else{
    if(LastOrderlotsc>0){
if(probabilidadC<probabilidadV){
  if(LastOrderlotsc>=maxlotsB||calclotsC>=maxlotsB){
  lotesposicionc=NormalizeDouble(maxlotsB,lotround);
  }else{
  lotesposicionc=NormalizeDouble(calclotsC,lotround);
  }
}else{
  if(LastOrderlotsc>=maxlotsG||calclotsC>=maxlotsG){
  lotesposicionc=NormalizeDouble(maxlotsG,lotround);
  }else{
  lotesposicionc=NormalizeDouble(calclotsC,lotround);
  }
}


    }
  }
  if(posicionesabiertasrobotv==0){
    if(probabilidadC>probabilidadV){
      lotesposicionv=NormalizeDouble(lotesinicialB*riskextrapolatorvCrash,lotround);
    }else{
      lotesposicionv=NormalizeDouble(lotesinicialG*riskextrapolatorvCrash,lotround);
    }
  }else{
    if(LastOrderlotsv>0){
      if(probabilidadC>probabilidadV){
        if(LastOrderlotsv>=maxlotsB||calclotsV>=maxlotsB){
          lotesposicionv=NormalizeDouble(maxlotsB,lotround);
        }else{
          lotesposicionv=NormalizeDouble(calclotsV,lotround);//+posicionesabiertasrobotv);
        }
      }else{
        if(LastOrderlotsv>=maxlotsG||calclotsV>=maxlotsG){
          lotesposicionv=NormalizeDouble(maxlotsG,lotround);
        }else{
          lotesposicionv=NormalizeDouble(calclotsV,lotround);//+posicionesabiertasrobotv);
        }
      }
    }
  }
}

if(debugoption==true){
ObjectSetText(Symbol()+"lotesop","GLotes -> LOPC: "+lotesposicionc+" LOPV: "+lotesposicionv,7,NULL,Orange);
ObjectSet(Symbol()+"lotesop",OBJPROP_CORNER,0);
ObjectSet(Symbol()+"lotesop",OBJPROP_XDISTANCE,15);
ObjectSet(Symbol()+"lotesop",OBJPROP_YDISTANCE,100);
}

    //------------------------------------------------------------------
    // ENVIO OPERACIONES
    //------------------------------------------------------------------
string FordersendV=Symbol()+"OrdsV";
string FordersendC=Symbol()+"OrdsC";

if(spreadvalue<maxspread){

    //------------INICIO VENTA sola


    if(posicionesabiertasrobotv==0&&lotesposicionv>minlots){

if(probabilidadV>probabilidadC){//&&probabilidadV>probabilidadC ------
OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,commentID,MagicNumber,0,Red);
// //APERTURA OBSERVADO
//  string GFordersendV1 = FileOpen(FordersendV,FILE_WRITE);//|FILE_READ| FILE_WRITE
//   if(GFordersendV1==INVALID_HANDLE){
//  printf("GF Error 7");
//  }else{
//    string FWordersendV1 = Bid+":"+TimeCurrent();
//            FileWrite(GFordersendV1,FWordersendV1);
//            FileClose(GFordersendV1);
//     }
// //FIN APERTURA OBSERVADO
}
      }
      //------------Fin venta sola
    //------------INICIO COMPRA sola

    if(posicionesabiertasrobotc==0&&lotesposicionc>minlots){


      if(probabilidadV<probabilidadC){//&&probabilidadV<probabilidadC---- &&CcogB>CcogS
     OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,commentID,MagicNumber,0,Blue);

      //
      // //APERTURA OBSERVADO
      //  string GFordersendC1 = FileOpen(FordersendC,FILE_WRITE);//|FILE_READ| FILE_WRITE
      //   if(GFordersendC1==INVALID_HANDLE){
      //  printf("GF Error 8");
      //  }else{
      //    string FWordersendC1 = Ask+":"+TimeCurrent();
      //            FileWrite(GFordersendC1,FWordersendC1);
      //            FileClose(GFordersendC1);
      //     }
      // //FIN APERTURA OBSERVADO


      }


       }
    //-------------FIN COMPRA SOLA
    //----------------INICIO VENTA GRUPAL
    if(posicionesabiertasrobotv>0&&filter1v==1&&posicionesabiertasrobotv<maxposition&&tiempoelapsedS>240&&lotesposicionv>minlots){

      if(probabilidadV>probabilidadC){
      OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,commentID,MagicNumber,0,Red);


      // //APERTURA OBSERVADO
      //  string GFordersendV2 = FileOpen(FordersendV,FILE_WRITE);//|FILE_READ| FILE_WRITE
      //   if(GFordersendV2==INVALID_HANDLE){
      //  printf("GF Error 9");
      //  }else{
      //    string FWordersendV2 = Bid+":"+TimeCurrent();
      //            FileWrite(GFordersendV2,FWordersendV2);
      //            FileClose(GFordersendV2);
      //     }
      // //FIN APERTURA OBSERVADO
      }

    }

    //----------------FIN VENTA GRUPAL
    //----------------INICIO COMPRA GRUPAL
    if(posicionesabiertasrobotc>0&&filter1c==1&&posicionesabiertasrobotc<maxposition&&tiempoelapsedB>240&&lotesposicionc>minlots){


      if(probabilidadV<probabilidadC){
      OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,commentID,MagicNumber,0,Blue);
      // //APERTURA OBSERVADO
      //  string GFordersendC2 = FileOpen(FordersendC,FILE_WRITE);//|FILE_READ| FILE_WRITE
      //   if(GFordersendC2==INVALID_HANDLE){
      //  printf("GF Error 10");
      //  }else{
      //    string FWordersendC2 = Ask+":"+TimeCurrent();
      //            FileWrite(GFordersendC2,FWordersendC2);
      //            FileClose(GFordersendC2);
      //     }
      // //FIN APERTURA OBSERVADO
      }






      }



    //FIN COMPRA GRUPAL

}

//ORDER SEND
string OrdersendOV, OrdersendOV1[],OrdersendOC, OrdersendOC1[];
double TEOrdersend=TimeCurrent()-60;


if(FileIsExist(FordersendC)==true){

  string FRordersendC = FileOpen(FordersendC,FILE_READ);// | FILE_WRITE
  if(FRordersendC==INVALID_HANDLE){
  printf("File Read Error 3");
  }else{
  OrdersendOC = FileReadString(FRordersendC);
  FileClose(FRordersendC);
  }
  StringSplit(OrdersendOC,sep,OrdersendOC1);
  double POrdersendC=OrdersendOC1[0];
  double TOrdersendC=OrdersendOC1[1];

  if(TEOrdersend>TOrdersendC){
  if(Ask<POrdersendC){
    //APERTURA OBSERVADO
     string GFordersendC3 = FileOpen(FordersendC,FILE_WRITE);//|FILE_READ| FILE_WRITE
      if(GFordersendC3==INVALID_HANDLE){
     printf("GF Error 11");
     }else{
       string FWordersendC3 = Ask+":"+TimeCurrent();
               FileWrite(GFordersendC3,FWordersendC3);
               FileClose(GFordersendC3);
        }
    //FIN APERTURA OBSERVADO
  }
  if(Ask>POrdersendC){
     if(OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,commentID,MagicNumber,0,Blue)){
       FileDelete(FordersendC);
     }
  }

  }
}


if(FileIsExist(FordersendV)==true){

  string FRordersendV = FileOpen(FordersendV,FILE_READ);// | FILE_WRITE
  if(FRordersendV==INVALID_HANDLE){
  printf("File Read Error 3");
  }else{
  OrdersendOV = FileReadString(FRordersendV);
  FileClose(FRordersendV);
  }
  StringSplit(OrdersendOV,sep,OrdersendOV1);
  double POrdersendV=OrdersendOV1[0];
  double TOrdersendV=OrdersendOV1[1];

  if(TEOrdersend>TOrdersendV){
  if(Bid>POrdersendV){
    //APERTURA OBSERVADO
     string GFordersendV3 = FileOpen(FordersendV,FILE_WRITE);//|FILE_READ| FILE_WRITE
      if(GFordersendV3==INVALID_HANDLE){
     printf("GF Error 11");
     }else{
       string FWordersendV3 = Bid+":"+TimeCurrent();
               FileWrite(GFordersendV3,FWordersendV3);
               FileClose(GFordersendV3);
        }
    //FIN APERTURA OBSERVADO
  }
  if(Bid<POrdersendV){
     if(OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,commentID,MagicNumber,0,Red)){
       FileDelete(FordersendV);
     }
  }

  }
}



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
