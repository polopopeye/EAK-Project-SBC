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


double gridposition=20; //pips on every new trade

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


}

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

int posicionesS1C=0,posicionesS2C=0,posicionesS3C=0,posicionesS4C=0,posicionesS5C=0,posicionesS6C=0,posicionesS7C=0,posicionesS8C=0,posicionesS9C=0,posicionesS10C=0;
int posicionesS1V=0,posicionesS2V=0,posicionesS3V=0,posicionesS4V=0,posicionesS5V=0,posicionesS6V=0,posicionesS7V=0,posicionesS8V=0,posicionesS9V=0,posicionesS10V=0;
double pfS1C=0,pfS2C=0,pfS3C=0,pfS4C=0,pfS5C=0,pfS6C=0,pfS7C=0,pfS8C=0,pfS9C=0,pfS10C=0;
double pfS1V=0,pfS2V=0,pfS3V=0,pfS4V=0,pfS5V=0,pfS6V=0,pfS7V=0,pfS8V=0,pfS9V=0,pfS10V=0;
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
  if(OrderSymbol()==Symbol()&&OrderComment()=="S6"){
if(OrderType()==OP_BUY){
  pfS6C=pfS6C+OrderProfit();
  posicionesS6C++;
}
if(OrderType()==OP_SELL){
  pfS6V=pfS6V+OrderProfit();
  posicionesS6V++;
}
  }
  if(OrderSymbol()==Symbol()&&OrderComment()=="S7"){
if(OrderType()==OP_BUY){
  pfS7C=pfS7C+OrderProfit();
  posicionesS7C++;
}
if(OrderType()==OP_SELL){
  pfS7V=pfS7V+OrderProfit();
  posicionesS7V++;
}
  }
  if(OrderSymbol()==Symbol()&&OrderComment()=="S8"){
if(OrderType()==OP_BUY){
  pfS8C=pfS8C+OrderProfit();
  posicionesS8C++;
}
if(OrderType()==OP_SELL){
  pfS8V=pfS8V+OrderProfit();
  posicionesS8V++;
}
  }
  if(OrderSymbol()==Symbol()&&OrderComment()=="S9"){
if(OrderType()==OP_BUY){
  pfS9C=pfS9C+OrderProfit();
  posicionesS9C++;
}
if(OrderType()==OP_SELL){
  pfS9V=pfS9V+OrderProfit();
  posicionesS9V++;
}
  }
  if(OrderSymbol()==Symbol()&&OrderComment()=="S10"){
if(OrderType()==OP_BUY){
  pfS10C=pfS10C+OrderProfit();
  posicionesS10C++;
}
if(OrderType()==OP_SELL){
  pfS10V=pfS10V+OrderProfit();
  posicionesS10V++;
}
  }

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

//ESTRATEGIA1 - S1
bool s1=true;
bool s2=true;
bool s3=true;
bool s4=true;
bool s5=true;
bool s6=true;
bool s7=true;
bool s8=false;
bool s9=false;
bool s10=false;
double activadasestrategias=7;










string StrategyName="NONE";



   if(next_candle<=Time[0])
      {
         next_candle=Time[0]+Period();
         // New candle. Your trading functions here
          double MyPoint=Point;
if(TotalOrdersCount()>150)Alert("DEMASIADAS OPERACIONES EN "+Symbol());
   if(TotalOrdersCount()>=0&&TotalOrdersCount()<199)
     {



       for(int sond=0;sond<=activadasestrategias;sond++){
         string FileDBarchivosSG="S"+sond+Symbol()+".eakdb";
         string FileDBarchivosRG="R"+FileDBarchivosSG;




         if(s1==true&&sond==1){
           double op4=iCustom(Symbol(),PERIOD_M5,"EAKrmi",1,0);
           double cop4=iCustom(Symbol(),PERIOD_M5,"EAKrmi",2,0);
           if(op4!=EMPTY_VALUE&&op4!=0){
                 commentID="S1";
                 op=op4;
                 StrategyName="RMI - S1";
           }
           if(posicionesS1C>0||posicionesS1V>0){
             if(cop4!=EMPTY_VALUE&&cop4!=0){
                   commentID="S1";
                   cierreop=cop4;
                   StrategyName="RMI - S1";
             }
           }
         }

         if(s2==true&&sond==2){
           double op1=iCustom(Symbol(),PERIOD_M5,"EAKyzyz",1,0);
           double cop1=iCustom(Symbol(),PERIOD_M5,"EAKyzyz",2,0);
           if(op1!=EMPTY_VALUE&&op1!=0){
                 commentID="S2";
                 op=op1;
                 StrategyName="YZYZ - S2";

           }
             if(posicionesS2C>0||posicionesS2V>0){
           if(cop1!=EMPTY_VALUE&&cop1!=0){
                 commentID="S2";
                 cierreop=cop1;
                 StrategyName="YZYZ - S2";

           }
         }

         }


         if(s3==true&&sond==3){
           double op5=iCustom(Symbol(),PERIOD_M5,"EAKBINOPT",1,0);
           double cop5=iCustom(Symbol(),PERIOD_M5,"EAKBINOPT",2,0);
           if(op5!=EMPTY_VALUE&&op5!=0){
                 commentID="S3";
                 op=op5;
                 StrategyName="BINOPT - S3";

           }
           if(posicionesS3C>0||posicionesS3V>0){
           if(cop5!=EMPTY_VALUE&&cop5!=0){
                 commentID="S3";
                 cierreop=cop5;
                 StrategyName="BINOPT - S3";

               }
           }
         }


         if(s4==true&&sond==4){
           double op7=iCustom(Symbol(),PERIOD_M5,"EAKsymphonie",1,0);
           double cop7=iCustom(Symbol(),PERIOD_M5,"EAKsymphonie",2,0);
           if(op7!=EMPTY_VALUE&&op7!=0){
                 commentID="S4";
                 op=op7;
                 StrategyName="Symphonie - S4";

           }
           if(posicionesS4C>0||posicionesS4V>0){
           if(cop7!=EMPTY_VALUE&&cop7!=0){
                 commentID="S4";
                 cierreop=cop7;
                 StrategyName="Symphonie - S4";

               }
           }
         }

           if(s5==true&&sond==5){
             double op6=iCustom(Symbol(),PERIOD_M5,"EAKsymphonie2",1,0);
             double cop6=iCustom(Symbol(),PERIOD_M5,"EAKsymphonie2",2,0);
             if(op6!=EMPTY_VALUE&&op6!=0){
                   commentID="S5";
                   op=op6;
                   StrategyName="Symphonie2 - S5";

             }
             if(posicionesS5C>0||posicionesS5V>0){
             if(cop6!=EMPTY_VALUE&&cop6!=0){
                   commentID="S5";
                   cierreop=cop6;
                   StrategyName="Symphonie2 - S5";

                 }
             }
           }


           if(s6==true&&sond==6){
             double op11=iCustom(Symbol(),PERIOD_M5,"EAKmdts",1,0);
             double cop11=iCustom(Symbol(),PERIOD_M5,"EAKmdts",2,0);
             if(op11!=EMPTY_VALUE&&op11!=0){
                   commentID="S6";
                   op=op11;
                   StrategyName="MDTS - S6";
             }
             if(posicionesS6C>0||posicionesS6V>0){
               if(cop11!=EMPTY_VALUE&&cop11!=0){
                     commentID="S6";
                     cierreop=cop11;
                     StrategyName="MDTS - S6";
               }
             }
           }

           if(s7==true&&sond==7){
             double op12=iCustom(Symbol(),PERIOD_M5,"EAKsdtr",1,0);
             double cop12=iCustom(Symbol(),PERIOD_M5,"EAKsdtr",2,0);
             if(op12!=EMPTY_VALUE&&op12!=0){
                   commentID="S7";
                   op=op12;
                   StrategyName="SDTR - S7";
             }
             if(posicionesS7C>0||posicionesS7V>0){
               if(cop12!=EMPTY_VALUE&&cop12!=0){
                     commentID="S7";
                     cierreop=cop12;
                     StrategyName="SDTR - S7";
               }
             }
           }


             int posicionSB=0;
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
             if(commentID=="S6"){
               pfSGBC=pfS6C;
               pfSGBV=pfS6V;
               if(op==1){
                 posicionSB=posicionesS6C;
               }
               if(op==2){
                 posicionSB=posicionesS6V;
               }
             }
             if(commentID=="S7"){
               pfSGBC=pfS7C;
               pfSGBV=pfS7V;
               if(op==1){
                 posicionSB=posicionesS7C;
               }
               if(op==2){
                 posicionSB=posicionesS7V;
               }
             }
             if(commentID=="S8"){
               pfSGBC=pfS8C;
               pfSGBV=pfS8V;
               if(op==1){
                 posicionSB=posicionesS8C;
               }
               if(op==2){
                 posicionSB=posicionesS8V;
               }
             }
             if(commentID=="S9"){
               pfSGBC=pfS9C;
               pfSGBV=pfS9V;
               if(op==1){
                 posicionSB=posicionesS9C;
               }
               if(op==2){
                 posicionSB=posicionesS9V;
               }
             }
             if(commentID=="S10"){
               pfSGBC=pfS10C;
               pfSGBV=pfS10V;
               if(op==1){
                 posicionSB=posicionesS10C;
               }
               if(op==2){
                 posicionSB=posicionesS10V;
               }
             }


       //Evita solapamiento por error en indicadores (no envia esa señal contradictoria)
       if(op==cierreop){
         commentID="error";
       }
         string FileDBarchivos, FileDBarchivos2,FDBread4r[];
         double RiskBehavior=0,nota=0,ProbabilidadBehavior,NotaBehavior,TiempoBehavior;
         double FProfitBehavior=0;
         int SegundosElapsed=0;
         string FDBread1r;
         string nuevosdatos;

         for(int cnta1=0;cnta1<OrdersTotal();cnta1++){
           OrderSelect(cnta1,SELECT_BY_POS,MODE_TRADES);
           FileDBarchivos=OrderComment()+Symbol()+".eakdb";
           FileDBarchivos2="R"+FileDBarchivos;
            bool cierre=false;

           if(OrderSymbol()==Symbol()&&OrderMagicNumber()==MagicNumber){
             SegundosElapsed=TimeCurrent()-OrderOpenTime();//tiempo en segundos

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
           //RiskBehavior=FDBread4r[1];
           //ProbabilidadBehavior=FDBread4r[2];
           NotaBehavior=FDBread4r[1];
           TiempoBehavior=FDBread4r[2];
         }


         double TiempoElapsedBehavior=SegundosElapsed;
         if(TiempoElapsedBehavior>0){
           double FProfitBehavior2=(OrderProfit()/OrderLots())/TiempoElapsedBehavior;

           if(OrderComment()==commentID){

             double pfSGBGB=pfSGBC+pfSGBV;
             if(pfSGBGB>0.01)nota=1;




             if(OrderType()==OP_BUY&&cierreop==1){
                 cierre=true;
                 OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);
                  FileDBarchivosSG="S"+sond+Symbol()+".eakdb";
                  FileDBarchivosRG="R"+FileDBarchivosSG;
             }
             if(OrderType()==OP_SELL&&cierreop==2){
                 cierre=true;
                 OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
                  FileDBarchivosSG="S"+sond+Symbol()+".eakdb";
                  FileDBarchivosRG="R"+FileDBarchivosSG;
             }


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
             nuevosdatos=OrderTicket()+":"+nota+"_";
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
         double LotesmedioporoperacionbehaviourV,LotesmedioporoperacionbehaviourC,profitmediobehaviorc,profitmediobehaviorv,PFbehaviorC=0,PFbehaviorV=0,probabilidadcompraop=0,probabilidadventaop=0,PRlotesC=1,PRlotesV=1,PRlotesC2=1,PRlotesV2=1;
         int PFoperacionC=0,PFoperacionV=0,totalopV=0,totalopC=0;



         if(FileIsExist(FileDBarchivosSG)){
           string behavior1read = FileOpen(FileDBarchivosSG,FILE_READ);
           if(behavior1read==INVALID_HANDLE){
           printf("behavior1read 1");
           }else{
           int  str_sizebehavior1read=FileReadInteger(behavior1read,INT_VALUE);
           string behavior1readall = FileReadString(behavior1read,str_sizebehavior1read);
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
               string Fdb2 = FileOpen(FileDBarchivosSG,FILE_WRITE);
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
         ticketitem=StrToInteger(behavioritem[0]);
         // riesgoitem=behavioritem[1];
         // probabilidaditem=behavioritem[2];
         notaitem=StrToInteger(behavioritem[1]);
         //printf("ticket"+ticketitem);

         if(OrderSelect(ticketitem,SELECT_BY_TICKET)==true){
         Lotesmedioporoperacionbehaviour=Lotesmedioporoperacionbehaviour+OrderLots();
         Tiempooperacionbehavior=OrderCloseTime()-OrderOpenTime();
         tiempomedio1=tiempomedio1+Tiempooperacionbehavior;
         profitmediobehavior=profitmediobehavior+OrderProfit();
         //riesgomedio1=riesgomedio1+riesgoitem;
         //probabilidadmedia1=probabilidadmedia1+probabilidaditem;
         notamedia1=notamedia1+notaitem;
       if(OrderType()==OP_BUY){
         totalopC=totalopC+1;
         profitmediobehaviorc=profitmediobehaviorc+OrderProfit();
         LotesmedioporoperacionbehaviourC=LotesmedioporoperacionbehaviourC+OrderLots();
         if(OrderProfit()>0){
           PFoperacionC=PFoperacionC+1;
         }
       }
       if(OrderType()==OP_SELL){
         totalopV=totalopV+1;
         profitmediobehaviorv=profitmediobehaviorv+OrderProfit();
       LotesmedioporoperacionbehaviourV=LotesmedioporoperacionbehaviourV+OrderLots();
         if(OrderProfit()>0){
           PFoperacionV=PFoperacionV+1;
         }
       }

         }
         }//fin for

         if(totalopC>0)probabilidadcompraop=PFoperacionC/totalopC;
         if(totalopV>0)probabilidadventaop=PFoperacionV/totalopV;
         if(LotesmedioporoperacionbehaviourC>0)PFbehaviorC=profitmediobehaviorc/LotesmedioporoperacionbehaviourC;
         if(LotesmedioporoperacionbehaviourV>0)PFbehaviorV=profitmediobehaviorv/LotesmedioporoperacionbehaviourV;

         notamedia2=notamedia1/cntrowbehavior;//PROBABILIDAD
         Lotesmedioporoperacion2behaviour=Lotesmedioporoperacionbehaviour/cntrowbehavior;
         Tiempomedioporoperacion2=tiempomedio1/cntrowbehavior;
         Profitmedioporoperacion2=profitmediobehavior/cntrowbehavior;
         factorprofit=Profitmedioporoperacion2/Lotesmedioporoperacion2behaviour;
         //riesgomedioporoperacion2=riesgomedio1/cntrowbehavior;
         //probabilidadmediaporoperacion2=probabilidadmedia1/cntrowbehavior;

           //-----------------------------------------------------------
           // Rarchivos Sistema, se guardan los datos en cada actualizacion
           //-----------------------------------------------------------
           if(cierre==true){
             string Rdb2 = FileOpen(FileDBarchivosRG,FILE_WRITE);
              if(Rdb2==INVALID_HANDLE){
             printf("Rdb2 1");
             }else{
               string Rdb2w = factorprofit+":"+notamedia2+":"+Tiempomedioporoperacion2;
                       FileWrite(Rdb2,Rdb2w);
                       FileClose(Rdb2);
                }
           }




         }


           //-----------------------------------------------------------
           // BEHAVIOR - COMPETICIÓN DE SISTEMAS
           //-----------------------------------------------------------


         double Spf1=iCustom(Symbol(),PERIOD_M5,"EAKbuildPF",0,0);
         double Spf2=iCustom(Symbol(),PERIOD_M5,"EAKbuildPF",1,0);
         double Spf3=iCustom(Symbol(),PERIOD_M5,"EAKbuildPF",2,0);
         double Spf4=iCustom(Symbol(),PERIOD_M5,"EAKbuildPF",3,0);
         double Spf5=iCustom(Symbol(),PERIOD_M5,"EAKbuildPF",4,0);
         double Spf6=iCustom(Symbol(),PERIOD_M5,"EAKbuildPF",5,0);
         double Spf7=iCustom(Symbol(),PERIOD_M5,"EAKbuildPF",6,0);

         double Snota1=iCustom(Symbol(),PERIOD_M5,"EAKbuildPF",7,0);
         double Snota2=iCustom(Symbol(),PERIOD_M5,"EAKbuildPF",8,0);
         double Snota3=iCustom(Symbol(),PERIOD_M5,"EAKbuildPF",9,0);
         double Snota4=iCustom(Symbol(),PERIOD_M5,"EAKbuildPF",10,0);
         double Snota5=iCustom(Symbol(),PERIOD_M5,"EAKbuildPF",11,0);
         double Snota6=iCustom(Symbol(),PERIOD_M5,"EAKbuildPF",12,0);
         double Snota7=iCustom(Symbol(),PERIOD_M5,"EAKbuildPF",13,0);
         string stringSpf1="S"+Spf1;
         string stringSpf2="S"+Spf2;
         string stringSpf3="S"+Spf3;
         string stringSpf4="S"+Spf4;
         string stringSpf5="S"+Spf5;
         string stringSpf6="S"+Spf6;
         string stringSpf7="S"+Spf7;
         string stringSnota1="S"+Snota1;
         string stringSnota2="S"+Snota2;
         string stringSnota3="S"+Snota3;
         string stringSnota4="S"+Snota4;
         string stringSnota5="S"+Snota5;
         string stringSnota6="S"+Snota6;
         string stringSnota7="S"+Snota7;
         double relacionpuntexp=2/activadasestrategias;//0.45 //0.53
       int punt1=7,punt2=6,punt3=5,punt4=4,punt5=3,punt6=2,punt7=2;
       double pfB=1,notaB=1;
       if(stringSpf7==commentID)pfB=punt7*relacionpuntexp;
       if(stringSpf6==commentID)pfB=punt6*relacionpuntexp;
       if(stringSpf5==commentID)pfB=punt5*relacionpuntexp;
       if(stringSpf4==commentID)pfB=punt4*relacionpuntexp;
       if(stringSpf3==commentID)pfB=punt3*relacionpuntexp;
       if(stringSpf2==commentID)pfB=punt2*relacionpuntexp;
       if(stringSpf1==commentID)pfB=punt1*relacionpuntexp;

       if(stringSnota7==commentID)notaB=punt7*relacionpuntexp;
       if(stringSnota6==commentID)notaB=punt6*relacionpuntexp;
       if(stringSnota5==commentID)notaB=punt5*relacionpuntexp;
       if(stringSnota4==commentID)notaB=punt4*relacionpuntexp;
       if(stringSnota3==commentID)notaB=punt3*relacionpuntexp;
       if(stringSnota2==commentID)notaB=punt2*relacionpuntexp;
       if(stringSnota1==commentID)notaB=punt1*relacionpuntexp;

       //  if(pfB<0.4)pfB=0.4;
       //  if(notaB<0.4)notaB=0.4;
         //----------------------------------------------------------------
         // GESTION LOTE
         //------------------------------------------------------------------
         // Esto se vera influenciado por el BEHAVIOUR siguiendo varias probabilidades, riesgo
         // (mayor riesgo mas pequeña inversion), SIN MARTINGALE. Rentabilidad en tiempo, Inversion realizada,
         // en funciona a las probabilidades de perdidas se observa un capital optimo. y riesgo de default que
         // ayudara a definir el capital medio, minimo y maximo de inversion recomendado.

//Porcentaje a aumentar o disminuir



      double multiplicadorlotesestrategia=(pfB+notaB)/2;
      double porcentaje=0.1*multiplicadorlotesestrategia;

       if(probabilidadcompraop>probabilidadventaop){
         PRlotesC=multiplicadorlotesestrategia+porcentaje;
         PRlotesV=multiplicadorlotesestrategia-porcentaje;
       }
       if(probabilidadcompraop<probabilidadventaop){
         PRlotesC=multiplicadorlotesestrategia-porcentaje;
         PRlotesV=multiplicadorlotesestrategia+porcentaje;
       }
       if(probabilidadcompraop==probabilidadventaop){
         PRlotesC=multiplicadorlotesestrategia;
         PRlotesV=multiplicadorlotesestrategia;
       }
       if(PFbehaviorC>PFbehaviorV){
         PRlotesC2=PRlotesC+porcentaje;
         PRlotesV2=PRlotesV-porcentaje;
       }
       if(PFbehaviorC<PFbehaviorV){
         PRlotesC2=PRlotesC-porcentaje;
         PRlotesV2=PRlotesV+porcentaje;
       }
       if(PFbehaviorC==PFbehaviorV){
         PRlotesC2=PRlotesC;
         PRlotesV2=PRlotesV;
       }


         double lotesposicionc=NormalizeDouble(lotesinicial*PRlotesC2,2);
         double lotesposicionv=NormalizeDouble(lotesinicial*PRlotesV2,2);
        // printf("pfB: "+pfB+"  _notaB:"+notaB+" _relacionpuntexp:"+relacionpuntexp);

       if(lotesposicionc<minlots)lotesposicionc=minlots;
       if(lotesposicionv<minlots)lotesposicionv=minlots;


             //------------------------------------------------------------------
             // APERTURA
             //------------------------------------------------------------------

         // Si el triger de sistema es enviado, se coteja con riesgo minimo,
         // se envia operacion y se crea un archivo con nombre de ticket. con informacion importante de envio, por el momento
         // se pone el sistema de entrada.
         //
         // De momento pondremos en el comentario el sistema para facilitar la programación.


           //------------------------------------------------------------------
           //GRID 2 POSITIONALOTOFORDERS - POSITION A LOT OF ORDERS
           //------------------------------------------------------------------
           //esto esta bien, no permitir operaciones mas malas.
           int filter1c=3,filter1v=3;

    int filterCtrue=0,filterVtrue=0;
       double GridpipsC=10000,GridpipsV=10000;

for(int cntfilter=0 ;cntfilter<=OrdersTotal() ;cntfilter++){
if(OrderSelect(cntfilter,SELECT_BY_POS,MODE_TRADES)){
  if(OrderSymbol()==Symbol()&&OrderComment()==commentID){
    if(OrderType()==OP_BUY){
      GridpipsC = MathAbs((NormalizeDouble(((Bid-OrderOpenPrice())/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);
      if(GridpipsC<gridposition)filterCtrue++;
    }
    if(OrderType()==OP_SELL){
      GridpipsV = MathAbs((NormalizeDouble(((OrderOpenPrice()-Ask)/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);
      if(GridpipsV<gridposition)filterVtrue++;
    }
  }
}
}


       if(posicionSB==0){
         filter1c=1;
         filter1v=1;
       }else{
         if(filterCtrue>0){ //&&lastorderpS1<0
          filter1c=0;
         }else{
           if(pfSGBC<0)filter1c=1;
         }
         if(filterVtrue>0){ //&&lastorderpS1<0
          filter1v=0;
        }else{
          if(pfSGBV<0)filter1v=1;
         }
       }

       bool actualordersend=false;
       int sendop;
       double lotsend;
       string strategysend,Nombrestrategia;
       //printf("F1: "+filter1c+" _ GridpipsC: "+GridpipsC+" _ pfSGBC:"+pfSGBC);
         double precio=SymbolInfoDouble(Symbol(),SYMBOL_BID);
         color clrR=clrRed;
         color clrB=clrBlue;
       //  int cntopener=0;
         if(spreadvalue<maxspread){
           if(op==1&&filter1c==1&&commentID!="error"){

             actualordersend=true;
             sendop=1;
             strategysend=commentID;
             lotsend=lotesposicionc;
             Nombrestrategia=StrategyName;


                 OrderSend(Symbol(),0,lotsend,Ask,Slippage,0,0,strategysend,MagicNumber,0,Blue);
                 ObjectCreate(ChartID(),Time[0],OBJ_TEXT,0,TimeCurrent(),precio);
                 ObjectSetString(ChartID(),Time[0],OBJPROP_TEXT,Nombrestrategia);
                 ObjectSetString(ChartID(),Time[0],OBJPROP_FONT,"Arial");
                ObjectSetInteger(ChartID(),Time[0],OBJPROP_FONTSIZE,"12");
                ObjectSetInteger(ChartID(),Time[0],OBJPROP_COLOR,clrB);



           }
           if(op==2&&filter1v==1&&commentID!="error"){
             actualordersend=true;
             sendop=2;
             strategysend=commentID;
             lotsend=lotesposicionv;
             Nombrestrategia=StrategyName;

               OrderSend(Symbol(),1,lotsend,Bid,Slippage,0,0,strategysend,MagicNumber,0,Red);
              ObjectCreate(ChartID(),Time[0],OBJ_TEXT,0,TimeCurrent(),precio);
              ObjectSetString(ChartID(),Time[0],OBJPROP_TEXT,Nombrestrategia);
              ObjectSetString(ChartID(),Time[0],OBJPROP_FONT,"Arial");
              ObjectSetInteger(ChartID(),Time[0],OBJPROP_FONTSIZE,"12");
              ObjectSetInteger(ChartID(),Time[0],OBJPROP_COLOR,clrR);


           }

         }

       }//FIN FOR ESTRATEGIAS

//aqui va el codigo
     int result=0;











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
