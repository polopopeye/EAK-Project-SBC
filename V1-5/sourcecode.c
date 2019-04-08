//+------------------------Kenneth Suarez-------------------------------+
//                   Expert Advisor MUFASA V1.5- 2014-2018
//gestion de lotes y operaciones con martingale(2 versiones), con grid(2 Versiones),
//filtro fisher (cuando abrir operacion)- histo (determina si esta sobrevalorado).
//Resistencias (Identifica resistencias),MAtrend(identifica tendencia),
//bollinger(identifica bandas bollinger) itrend(tendencias) mirror(cuando abrir operacion),
//ESTRATEGIA 1
//histo muy alto para evitar operaciones contrarias al mercado y favorecer a las faciles
//fisher simple para abrir operaciones seguras.
//grid fijo relativamente bajo(50),
//tp fijo relativamente bajo (cerrar operaciones rapido),
//martigale v1 relativamente bajo.
//ESTRATEGIA 2
//histo muy alto para evitar operaciones contrarias al mercado y favorecer a las faciles
//fisher simple para abrir operaciones seguras.
//grid variable primero relativamente alto para evitar dropdown alto,
//despues relativamente bajo, para cerrar varias posiciones en positivo.
//(evita perdidas o pocas ganancias y muchas posiciones abiertas)
//tp variable primero relativamente alto y luego bajo a medida de varias operaciones.
//martigale v1 relativamente alto.
//+---------------------------------------------------------------------+
enum IndList
  {
   IndList1 = 1, //Momentum
   IndList2 = 2, //ATR (Average True Range)
   IndList3 = 3, //CCI (Commodity Channel Index)
   IndList4 = 4  //RSI (Relative Strength Index)
  };
extern string GESTIONLOTES="METODO 1 MARTINGALE, METODO 2 EN CONSTRUCCION --------------";
extern int gestionlotesmethod=1;
extern double lotesinicial=0.1; //first lot
extern double multiplicador=2; //Martingale factor to recover bad choices
extern double maxlots=30;
extern string GRID="POSITION FIJA EN PIPS A PARTIR DE UNA OPERACION ABIERTA";
extern double gridposition=150; //pips on every new trade
extern string MAXPOSITION="NUMERO MAXIMO DE OPERACIONES A TENER ABIERTAS";
extern int maxposition=100;//Max positions
extern string MODIFY="MODIFY ORDER, SI TP FIJO PUEDES FIJARLO CON PIPSMODIFY";
extern int pipsmodify=450; //pips to reach in position modify.
extern string GRID2="METODO 2 GRID Y TP VARIABLES EN FUNCION A ORDENES CON PERDIDAS";
extern bool filtergridpositionalotoforders=true;
extern double gridpositionalotoforders1=50;
extern double gridpositionalotoforders2=40;
extern double gridpositionalotoforders3=30;
extern double gridpositionalotoforders4=20;
extern double gridpositionalotoforders5=10;
extern double gridpositionalotoforderstp1=600;
extern double gridpositionalotoforderstp2=600;
extern double gridpositionalotoforderstp3=550;
extern double gridpositionalotoforderstp4=500;
extern double gridpositionalotoforderstp5=450;
extern string FILTROMA="FILTRO MA QUE INDICA TENDENCIA A MEDIO PLAZO";
extern bool filtermatrend=true;
extern int periodmarojo=600;
extern int periodmaamarillo=300;
extern int periodmaverde=25;
extern ENUM_TIMEFRAMES timematrend=PERIOD_M5;
extern string FILTROHISTO="--------FILTRO HISTO-------------------";
extern bool filterHisto=true;//Filter Momentum|ATR|CCI|RSI. UNDERCONSTRUCTION
extern IndList histoindicator= 1;//Indicator Name
extern int histoperiod = 300;//Indicator Period
extern int histoperiod2 = 300;//Indicator Period
extern ENUM_APPLIED_PRICE histoapliedprice=PRICE_CLOSE;//Applied Price for Momentum, CCI or RSI
extern ENUM_TIMEFRAMES tiempohisto=PERIOD_D1;//Bes time 15
extern ENUM_TIMEFRAMES tiempohisto2=PERIOD_H4;//Bes time 15
extern double momentumresistancetop=100.3;
extern double momentumresistancebot=99.7;
extern string FILTROMAHISTO="FILTRO MA DEL HISTO";
extern bool filtermahisto=false;//FILTER MA FROM HISTO
extern ENUM_TIMEFRAMES tiempomahisto=PERIOD_M1;
extern int maperiodhisto=300;
extern string FILTROFISHER="------ FILTRO FISHER ----------";
extern bool filterFish=true;
extern bool closeorderfisher=false;
extern double minimumpipstocloseFISHER=70;
extern ENUM_TIMEFRAMES tiempofish=PERIOD_M5;
extern int periodfish=600;
extern int apliedpricefish=0;
extern bool modefastfish=false;
extern bool signalsfish=false;
extern int fishmaperiod1=9;
extern int fishmaperiod2=45;
extern int typema1fish=0;
extern int typema2fish=3;
extern string FILTRORESISTENCIAS="FILTRO RESISTENCIAS, EVITA ORDENES ERRONEAS CERCA DE RESISTENCIAS.";
extern bool Resistanceopenfilter=false;
extern double Resistancepipsminimo=30;//Cuanto mas pequeño mas se adiere a la resistencia
extern ENUM_TIMEFRAMES Tiemporesistencias=PERIOD_H4;//Cuanto mas alto el valor mas seguro
extern string CIERREPORMERCADO2="AUTOTP EN FUNCION A LAS RESISTENCIAS, EL SENSOR ES PIPS ANTES DE LLEGAR A RESISTENCIA";
extern bool autotakeprofit=false;//V1, resistance fixed by pips (False and takeprofit value) or dinamic (True),
extern int sensorautotkpf=5;//Min pips to get resistance (10 is ok)
extern string CIERREPORMERCADO="METODO NO RECOMENDABLE DE CIERRE, TP FIJO EN FUNCION DE MERCADO, NO HAY LIMITE PARA FIJAR PIPS";
extern double takeprofitpips=40; //Min pips to take profit
extern string CIERREPORMERCADO3="AUTOTP2 EN FUNCION A FILTROS, PERDIDAS Y MIN PIPS";
extern bool autotakeprofit2=false;//V1, Look for the profit of open orders and minimumpips allowed to close
extern int minimumpipsallowedauto=35;
extern string GLOBALORDERPROFIT="FILTRO PARA EVITAR CIERRE CON PERDIDAS";
extern bool globalordersprofit=true;
extern string GLOBALORDERPROFIT2="FILTRO GLOBAL PARA EVITAR CIERRE MENOS PIPS";
extern int minpositionallowedtoclosepips=5;
extern string FILTROBOLLINGER="FILTRO BOLLINGER";
extern bool filterbollingerbands=false; //Bollinger usefull for Identify high and low
extern int periodobandas=100; //Best period
extern ENUM_TIMEFRAMES tiempobandas=PERIOD_M5; //Best time
extern string FILTROITREND="FILTRO ITREND";
extern bool filteritrend=false;
extern ENUM_TIMEFRAMES tiempoitrend=PERIOD_M1;
extern int itrendperiod=150;
extern int itrendpower=100;
extern string FILTROMIRROR="FILTRO MIRROR, INDICA DONDE ABRIR Y DONDE CERRAR.";
extern bool filtermirror=false; //Mirror filter not very good
extern int periodmirror=300; //Best period 300
extern ENUM_TIMEFRAMES timemirror=PERIOD_M15; //Best time 15
extern string OTHEROPTIONS="OTHER OPTIONS-----------------------";
extern int TrailingStop=0;
extern int MagicNumber=10001;
extern int Slippage=10;

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
   ObjectCreate(Symbol()+"slc",OBJ_HLINE,0,0,0,0,0);
   ObjectCreate(Symbol()+"slv",OBJ_HLINE,0,0,0,0,0);
   ObjectCreate(Symbol()+"restop",OBJ_LABEL,0,0,0,0);
   ObjectCreate(Symbol()+"resfiltsent",OBJ_LABEL,0,0,0,0);
   ObjectCreate(Symbol()+"minlot",OBJ_LABEL,0,0,0,0);
   ObjectCreate(Symbol()+"fbollinger",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"fmirror",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"fhisto",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"ffish",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"ordersprofit",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"filter1",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"Interface1",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"Interface2",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"Interface3",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"Interface4",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"matrend",OBJ_LABEL,0,0,0,0);








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
//+------------------------------------------------------------------+
//    INTERFACE
//+------------------------------------------------------------------+
 double minlots = MarketInfo(Symbol(),MODE_MINLOT);
 ObjectSetText(Symbol()+"minlot","Lots (Min: "+minlots+" Max: "+MarketInfo(Symbol(), MODE_MAXLOT)+") Size: "+MarketInfo(Symbol(), MODE_LOTSIZE)+" step:"+MarketInfo(Symbol(), MODE_LOTSTEP),7,NULL,Orange);
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



     string fileNamec =  "Margin Required for "+Symbol()+".txt";

     string fileHandlecierre41 = FileOpen(fileNamec,FILE_CSV|FILE_READ);// | FILE_WRITE
     if(fileHandlecierre41==INVALID_HANDLE){

     string crearfile = FileOpen(fileNamec,FILE_CSV|FILE_READ | FILE_WRITE);
     if(crearfile==INVALID_HANDLE){
     printf("Error no se ha podido crear el archivo");
     printf("Handle Invalido, apertura error 21 - Error al leer cierre cuando hay mas de una operacion en el mercado actual");
     }else{
     string datacrear = 0;
     FileWrite(crearfile,datacrear);
     FileClose(crearfile);
     }

     }else{
     string marginrequired = FileReadString(fileHandlecierre41);
     FileClose(fileHandlecierre41);
     }
     if(marginrequired<AccountMargin()){
       string fileHandlec = FileOpen(fileNamec,FILE_CSV|FILE_READ | FILE_WRITE);
       if(fileHandlec ==INVALID_HANDLE){
       printf("Error al abrir archivo no se ha podido establecer el Margin");
       }else{
       string datac = AccountMargin();
       FileWrite(fileHandlec,datac);
       FileClose(fileHandlec);
       }

     }




  //------------------------------------------------------------------
  //Global OrdersProfit for bad orders
  //------------------------------------------------------------------
  double profitordersC = 0;
  double profitordersV = 0;

  if(globalordersprofit==true){
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
    if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()&&OrderComment()=="MUFASA"){
      double DiffPipsc1 = MathAbs((NormalizeDouble(((Bid-OrderOpenPrice())/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);

      if(OrderSwap()<0){
        badorderswapC=OrderSwap();
      }
       if(OrderCommission()<0){
         badordercommissionC=OrderCommission();
       }
      if(OrderProfit()<0){
        badorderprofit1C = OrderProfit();

      }
      if(OrderProfit()>0){
        badorderprofit2C = OrderProfit();
      }
      lastorderopenpriceC=OrderOpenPrice();
    }
    if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()&&OrderComment()=="MUFASA"){
      double DiffPipsv1 = MathAbs((NormalizeDouble(((Bid-OrderOpenPrice())/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);

      if(OrderSwap()<0){
        badorderswapV=OrderSwap();
      }
      if(OrderCommission()<0){
      badordercommissionV=OrderCommission();
      }
      if(OrderProfit()<0){
        badorderprofit1V = OrderProfit();
      }
      if(OrderProfit()>0){
        badorderprofit2V = OrderProfit();
      }
      lastorderopenpriceV=OrderOpenPrice();
    }


  }

  //------------------------------------------------------------------
  //GLOBAL ORDER PROFIT SMALL TO AVOID FAST CLOSE
  //------------------------------------------------------------------

    if(globalordersprofit==true){
      if(DiffPipsc1>minpositionallowedtoclosepips){
        profitordersC = badorderprofit1C+badorderprofit2C+badordercommissionC+badorderswapC;
      }
      if(DiffPipsv1>minpositionallowedtoclosepips){
        profitordersV = badorderprofit1V+badorderprofit2V+badordercommissionV+badorderswapV;
      }
      ObjectSetText(Symbol()+"ordersprofit","OrderP B: ["+profitordersC+"]    OrdersP S: ["+profitordersV+"]",7,NULL,Orange);
       ObjectSet(Symbol()+"ordersprofit",OBJPROP_CORNER,0);
       ObjectSet(Symbol()+"ordersprofit",OBJPROP_XDISTANCE,15);
       ObjectSet(Symbol()+"ordersprofit",OBJPROP_YDISTANCE,180);
    }



  }
  if(globalordersprofit==false){
   profitordersC = 1;
   profitordersV = 1;
  }
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

if(Digits==3||Digits==5)point_compat=10;
for(int pg=0;pg<OrdersTotal();pg++){
OrderSelect(pg,SELECT_BY_POS,MODE_TRADES);
if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()&&OrderComment()=="MUFASA"){
  lastorderpS1=OrderProfit();
double DiffPipsv = MathAbs((NormalizeDouble(((Bid-OrderOpenPrice())/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);
if(DiffPipsv>takeprofitpips&&autotakeprofit2==true&&profitordersV>0){
  closeallordersv=1;
}
}
if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()&&OrderComment()=="MUFASA"){
  lastorderpB1=OrderProfit();
  double DiffPipsc = MathAbs((NormalizeDouble(((OrderOpenPrice()-Ask)/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);
if(DiffPipsc>takeprofitpips&&autotakeprofit2==true&&profitordersC>0){
  closeallordersc=1;
}
}
ObjectSetText(Symbol()+2,"PipsC: "+DiffPipsc+" PipsV: "+DiffPipsv,7,NULL,Orange);
  ObjectSet(Symbol()+2,OBJPROP_CORNER,0);
  ObjectSet(Symbol()+2,OBJPROP_XDISTANCE,15);
  ObjectSet(Symbol()+2,OBJPROP_YDISTANCE,40);
}





//------------------------------------------------------------------
//VALORES DE TAKEPROFIT Y STOPLOSS (RESTOP Y RESBOT)
//------------------------------------------------------------------
if(autotakeprofit==true||Resistanceopenfilter==true){
  double takeprofitp1v = iCustom(Symbol(),Tiemporesistencias,"SL_BW",0,0);//15 //30 //60 //240
  double takeprofitp1c = iCustom(Symbol(),Tiemporesistencias,"SL_BW",1,0);//15 //30 //60 //240
  double DiffPipsResistanceT = MathAbs((NormalizeDouble(((takeprofitp1v-Ask)/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);
  double DiffPipsResistanceB = MathAbs((NormalizeDouble(((takeprofitp1c-Bid)/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);
  ObjectSet(Symbol()+"slc",OBJPROP_PRICE1,takeprofitp1c);
  ObjectSet(Symbol()+"slv",OBJPROP_PRICE1,takeprofitp1v);

  ObjectSetText(Symbol()+"restop","TOP: [Venta "+DiffPipsResistanceT+"] BOT: [Compra "+DiffPipsResistanceB+"]",7,NULL,Orange);
    ObjectSet(Symbol()+"restop",OBJPROP_CORNER,0);
    ObjectSet(Symbol()+"restop",OBJPROP_XDISTANCE,15);
    ObjectSet(Symbol()+"restop",OBJPROP_YDISTANCE,60);


    if(Resistanceopenfilter==true){
    int Filterresistance=0;

      if(DiffPipsResistanceT>DiffPipsResistanceB){
        if(DiffPipsResistanceT>1000000){
          Filterresistance=1;
          ObjectSetText(Symbol()+"resfiltsent","F Resistencias: Compra",7,NULL,Blue);
            ObjectSet(Symbol()+"resfiltsent",OBJPROP_CORNER,0);
            ObjectSet(Symbol()+"resfiltsent",OBJPROP_XDISTANCE,15);
            ObjectSet(Symbol()+"resfiltsent",OBJPROP_YDISTANCE,80);
        }else{
          if(DiffPipsResistanceB>1000000){
            Filterresistance=2;
            ObjectSetText(Symbol()+"resfiltsent","F Resistencias: Venta",7,NULL,Red);
              ObjectSet(Symbol()+"resfiltsent",OBJPROP_CORNER,0);
              ObjectSet(Symbol()+"resfiltsent",OBJPROP_XDISTANCE,15);
              ObjectSet(Symbol()+"resfiltsent",OBJPROP_YDISTANCE,80);
          }else{
            Filterresistance=2;
            ObjectSetText(Symbol()+"resfiltsent","F Resistencias: Venta",7,NULL,Red);
              ObjectSet(Symbol()+"resfiltsent",OBJPROP_CORNER,0);
              ObjectSet(Symbol()+"resfiltsent",OBJPROP_XDISTANCE,15);
              ObjectSet(Symbol()+"resfiltsent",OBJPROP_YDISTANCE,80);
          }

        }


      }else{
        if(DiffPipsResistanceT<DiffPipsResistanceB){
          if(DiffPipsResistanceT>1000000){
            Filterresistance=1;
            ObjectSetText(Symbol()+"resfiltsent","F Resistencias: Compra",7,NULL,Blue);
              ObjectSet(Symbol()+"resfiltsent",OBJPROP_CORNER,0);
              ObjectSet(Symbol()+"resfiltsent",OBJPROP_XDISTANCE,15);
              ObjectSet(Symbol()+"resfiltsent",OBJPROP_YDISTANCE,80);
          }else{
            if(DiffPipsResistanceB>1000000){
              Filterresistance=2;
              ObjectSetText(Symbol()+"resfiltsent","F Resistencias: Venta",7,NULL,Red);
                ObjectSet(Symbol()+"resfiltsent",OBJPROP_CORNER,0);
                ObjectSet(Symbol()+"resfiltsent",OBJPROP_XDISTANCE,15);
                ObjectSet(Symbol()+"resfiltsent",OBJPROP_YDISTANCE,80);
            }else{
              Filterresistance=1;
              ObjectSetText(Symbol()+"resfiltsent","F Resistencias: Compra",7,NULL,Blue);
                ObjectSet(Symbol()+"resfiltsent",OBJPROP_CORNER,0);
                ObjectSet(Symbol()+"resfiltsent",OBJPROP_XDISTANCE,15);
                ObjectSet(Symbol()+"resfiltsent",OBJPROP_YDISTANCE,80);
            }
          }




        }else{
          Filterresistance=0;
          ObjectSetText(Symbol()+"resfiltsent","F Resistencias: Neutro",7,NULL,Orange);
            ObjectSet(Symbol()+"resfiltsent",OBJPROP_CORNER,0);
            ObjectSet(Symbol()+"resfiltsent",OBJPROP_XDISTANCE,15);
            ObjectSet(Symbol()+"resfiltsent",OBJPROP_YDISTANCE,80);
        }
      }

    }

}else{
  //No resistance and no autotakeprofit by resistances;
}





//------------------------------------------------------------------
//AUTOTAKEPROFIT V1
//------------------------------------------------------------------
int autotkpfcierreC=0;
int autotkpfcierreV=0;
if(autotakeprofit==true){
  if(DiffPipsResistanceT>1000000&&profitordersC>0){
    autotkpfcierreC=0;
    autotkpfcierreV=0;
  }else{
    if(DiffPipsResistanceB>1000000&&profitordersV>0){
      autotkpfcierreV=0;
      autotkpfcierreC=0;
    }else{
  if(DiffPipsResistanceB<sensorautotkpf&&profitordersC>0&&DiffPipsc>minimumpipsallowedauto){
        autotkpfcierreC=1;
        autotkpfcierreV=0;
      }
  if(DiffPipsResistanceT<sensorautotkpf&&profitordersV>0&&DiffPipsv>minimumpipsallowedauto){
        autotkpfcierreV=1;
        autotkpfcierreC=0;
      }
    }
  }
}


//------------------------------------------------------------------
//FILTRO 4: FISHER
//------------------------------------------------------------------


if(filterFish==true){

string  closefishertend="CLOSENULL";
int tendfisher=0;
  double fishbuf1white = iCustom(Symbol(),tiempofish,"fisher",periodfish,apliedpricefish,modefastfish,signalsfish,fishmaperiod1,fishmaperiod2,"1","1",typema1fish,typema2fish,2,0);
  double fishbuf2green = iCustom(Symbol(),tiempofish,"fisher",periodfish,apliedpricefish,modefastfish,signalsfish,fishmaperiod1,fishmaperiod2,"1","1",typema1fish,typema2fish,3,0);
  double fishbuf3red = iCustom(Symbol(),tiempofish,"fisher",periodfish,apliedpricefish,modefastfish,signalsfish,fishmaperiod1,fishmaperiod2,"1","1",typema1fish,typema2fish,4,0);

if(fishbuf1white<1&&fishbuf1white>fishbuf2green&&fishbuf2green>fishbuf3red){
  tendfisher=1;
  ObjectSetText(Symbol()+"ffish","F Fisher(T"+tiempofish+")("+periodfish+"): COMPRA",7,NULL,Blue);
    ObjectSet(Symbol()+"ffish",OBJPROP_CORNER,0);
    ObjectSet(Symbol()+"ffish",OBJPROP_XDISTANCE,15);
    ObjectSet(Symbol()+"ffish",OBJPROP_YDISTANCE,160);
}else{
  if(fishbuf1white>-1&&fishbuf3red>fishbuf2green&&fishbuf2green>fishbuf1white){
    tendfisher=2;
    ObjectSetText(Symbol()+"ffish","F Fisher(T"+tiempofish+")("+periodfish+"): VENTA",7,NULL,Red);
      ObjectSet(Symbol()+"ffish",OBJPROP_CORNER,0);
      ObjectSet(Symbol()+"ffish",OBJPROP_XDISTANCE,15);
      ObjectSet(Symbol()+"ffish",OBJPROP_YDISTANCE,160);
  }else{
    tendfisher=0;
    ObjectSetText(Symbol()+"ffish","F Fisher(T"+tiempofish+")("+periodfish+"): NEUTRO [white: "+fishbuf1white+"][B: "+fishbuf2green+"][S: "+fishbuf3red+"]",7,NULL,Orange);
      ObjectSet(Symbol()+"ffish",OBJPROP_CORNER,0);
      ObjectSet(Symbol()+"ffish",OBJPROP_XDISTANCE,15);
      ObjectSet(Symbol()+"ffish",OBJPROP_YDISTANCE,160);
  }
}

if(closeorderfisher==true){

  if(fishbuf1white>fishbuf2green&&fishbuf2green>fishbuf3red&&profitordersV>0&&DiffPipsv>minimumpipstocloseFISHER){
    closefishertend="CLOSESELL";
  }else{
    if(fishbuf3red>fishbuf2green&&fishbuf2green>fishbuf1white&&profitordersC>0&&DiffPipsc>minimumpipstocloseFISHER){
      closefishertend="CLOSEBUY";
    }
  }

}

}

//------------------------------------------------------------------
//FILTRO 5: MA trend
//------------------------------------------------------------------

    if(filtermatrend==true){
      int matend=0;
      double marojo1 = iMA(Symbol(),timematrend,periodmarojo,0,0,PRICE_MEDIAN,0);
      double maamarillo1 = iMA(Symbol(),timematrend,periodmaamarillo,0,0,PRICE_MEDIAN,0);
      double maverde1 = iMA(Symbol(),timematrend,periodmaverde,0,0,PRICE_MEDIAN,0);
      if(marojo1>maamarillo1&&maamarillo1>maverde1){
        matend=2;
        ObjectSetText(Symbol()+"matrend","F MATREND (Tiempo"+timematrend+"R"+periodmarojo+"A"+periodmaamarillo+"V"+periodmaverde+"): VENTA",7,NULL,Red);
          ObjectSet(Symbol()+"matrend",OBJPROP_CORNER,0);
          ObjectSet(Symbol()+"matrend",OBJPROP_XDISTANCE,15);
          ObjectSet(Symbol()+"matrend",OBJPROP_YDISTANCE,220);
      }else{
        if(maverde1>maamarillo1&&maamarillo1>marojo1){
          matend=1;
          ObjectSetText(Symbol()+"matrend","F MATREND (Tiempo"+timematrend+"R"+periodmarojo+"A"+periodmaamarillo+"V"+periodmaverde+"): COMPRA",7,NULL,Blue);
            ObjectSet(Symbol()+"matrend",OBJPROP_CORNER,0);
            ObjectSet(Symbol()+"matrend",OBJPROP_XDISTANCE,15);
            ObjectSet(Symbol()+"matrend",OBJPROP_YDISTANCE,220);
        }else{
          matend=0;
          ObjectSetText(Symbol()+"matrend","F MATREND (Tiempo"+timematrend+"R"+periodmarojo+"A"+periodmaamarillo+"V"+periodmaverde+"): NEUTRO",7,NULL,Orange);
            ObjectSet(Symbol()+"matrend",OBJPROP_CORNER,0);
            ObjectSet(Symbol()+"matrend",OBJPROP_XDISTANCE,15);
            ObjectSet(Symbol()+"matrend",OBJPROP_YDISTANCE,220);
        }
      }
    }
//------------------------------------------------------------------
// CONTADOR POSICIONES ABIERTAS POR ROBOT Y CIERRE
//------------------------------------------------------------------
int posicionesabiertasrobotc = 0;
int posicionesabiertasrobotv = 0;
double LastOrderlotsv = 0;
double LastOrderlotsc = 0;
for(int cnt1=0;cnt1<OrdersTotal();cnt1++)
{
OrderSelect(cnt1,SELECT_BY_POS,MODE_TRADES);
if(OrderSymbol()==Symbol()&&OrderComment()=="MUFASA")
{
if(OrderType()==OP_SELL){
 posicionesabiertasrobotv++;
 LastOrderlotsv=OrderLots();
 if(closeallordersv==1&&autotakeprofit2==true)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);//Aqui
 if(autotkpfcierreV==1&&autotakeprofit==true)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);//Aqui
 if(closefishertend=="CLOSESELL"&&closeorderfisher==true)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);//Aqui


}
}
if(OrderSymbol()==Symbol()&&OrderComment()=="MUFASA")
{
if(OrderType()==OP_BUY){
  LastOrderlotsc=OrderLots();
posicionesabiertasrobotc++;
if(closeallordersc==1&&autotakeprofit2==true)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);//Aqui
if(autotkpfcierreC==1&&autotakeprofit==true)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);//Aqui
if(closefishertend=="CLOSEBUY"&&closeorderfisher==true)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);//Aqui

}
}
}



//------------------------------------------------------------------
//GRID 2 POSITIONALOTOFORDERS - POSITION A LOT OF ORDERS
//------------------------------------------------------------------




if(filtergridpositionalotoforders==true){
//INICIO FILTER GRID Compra

if(posicionesabiertasrobotc==1){
  if(DiffPipsc>gridpositionalotoforders1&&profitordersC<0&&lastorderpB1<0){
  filter1c=1;
  }else{
  filter1c=0;
  }
}

if(posicionesabiertasrobotc==2){
  if(DiffPipsc>gridpositionalotoforders2&&profitordersC<0&&lastorderpB1<0){
  filter1c=1;
  }else{
  filter1c=0;
  }
}
if(posicionesabiertasrobotc==3){
  if(DiffPipsc>gridpositionalotoforders3&&profitordersC<0&&lastorderpB1<0){
  filter1c=1;
  }else{
  filter1c=0;
  }
}
if(posicionesabiertasrobotc==4){
  if(DiffPipsc>gridpositionalotoforders4&&profitordersC<0&&lastorderpB1<0){
  filter1c=1;
  }else{
  filter1c=0;
  }
}
if(posicionesabiertasrobotc==5){
  if(DiffPipsc>gridpositionalotoforders5&&profitordersC<0&&lastorderpB1<0){
  filter1c=1;
  }else{
  filter1c=0;
  }
}
if(posicionesabiertasrobotc==6){
  if(DiffPipsc>gridpositionalotoforders5&&profitordersC<0&&lastorderpB1<0){
  filter1c=1;
  }else{
  filter1c=0;
  }
}
if(posicionesabiertasrobotc==7){
  if(DiffPipsc>gridpositionalotoforders5&&profitordersC<0&&lastorderpB1<0){
  filter1c=1;
  }else{
  filter1c=0;
  }
}
if(posicionesabiertasrobotc==8){
  if(DiffPipsc>gridpositionalotoforders5&&profitordersC<0&&lastorderpB1<0){
  filter1c=1;
  }else{
  filter1c=0;
  }
}
if(posicionesabiertasrobotc==9){
  if(DiffPipsc>gridpositionalotoforders5&&profitordersC<0&&lastorderpB1<0){
  filter1c=1;
  }else{
  filter1c=0;
  }
}
if(posicionesabiertasrobotc>9){
  if(DiffPipsc>gridpositionalotoforders5&&profitordersC<0&&lastorderpB1<0){
  filter1c=1;
  }else{
  filter1c=0;
  }
}
//FIN FILTER GRID COMPRA

//INICIO FILTER GRID Venta
if(posicionesabiertasrobotv==1){
  if(DiffPipsv>gridpositionalotoforders1&&profitordersV<0&&lastorderpS1<0){
  filter1v=1;
  }else{
  filter1v=0;
  }
}
if(posicionesabiertasrobotv==2){
  if(DiffPipsv>gridpositionalotoforders2&&profitordersV<0&&lastorderpS1<0){
  filter1v=1;
  }else{
  filter1v=0;
  }
}
if(posicionesabiertasrobotv==3){
  if(DiffPipsv>gridpositionalotoforders3&&profitordersV<0&&lastorderpS1<0){
  filter1v=1;
  }else{
  filter1v=0;
  }
}
if(posicionesabiertasrobotv==4){
  if(DiffPipsv>gridpositionalotoforders4&&profitordersV<0&&lastorderpS1<0){
  filter1v=1;
  }else{
  filter1v=0;
  }
}
if(posicionesabiertasrobotv==5){
  if(DiffPipsv>gridpositionalotoforders5&&profitordersV<0&&lastorderpS1<0){
  filter1v=1;
  }else{
  filter1v=0;
  }
}
if(posicionesabiertasrobotv==6){
  if(DiffPipsv>gridpositionalotoforders5&&profitordersV<0&&lastorderpS1<0){
  filter1v=1;
  }else{
  filter1v=0;
  }
}
if(posicionesabiertasrobotv==7){
  if(DiffPipsv>gridpositionalotoforders5&&profitordersV<0&&lastorderpS1<0){
  filter1v=1;
  }else{
  filter1v=0;
  }
}
if(posicionesabiertasrobotv==8){
  if(DiffPipsv>gridpositionalotoforders5&&profitordersV<0&&lastorderpS1<0){
  filter1v=1;
  }else{
  filter1v=0;
  }
}
if(posicionesabiertasrobotv==9){
  if(DiffPipsv>gridpositionalotoforders5&&profitordersV<0&&lastorderpS1<0){
  filter1v=1;
  }else{
  filter1v=0;
  }
}
if(posicionesabiertasrobotv>9){
  if(DiffPipsv>gridpositionalotoforders5&&profitordersV<0&&lastorderpS1<0){
  filter1v=1;
  }else{
  filter1v=0;
  }
}
//FIN FILTER GRID VENTA

}

if(filtergridpositionalotoforders==false){
  if(DiffPipsv>gridposition&&profitordersV<0&&lastorderpS1<0){
   filter1v=1;
  }else{
   filter1v=0;
  }
  if(DiffPipsc>gridposition&&profitordersC<0&&lastorderpB1<0){
  filter1c=1;
  }else{
  filter1c=0;
  }
}



ObjectSetText(Symbol()+"filter1","filter1c: ["+filter1c+"]   filter1v:["+filter1v+"]",7,NULL,Orange);
  ObjectSet(Symbol()+"filter1",OBJPROP_CORNER,0);
  ObjectSet(Symbol()+"filter1",OBJPROP_XDISTANCE,15);
  ObjectSet(Symbol()+"filter1",OBJPROP_YDISTANCE,200);

//------------------------------------------------------------------
//FILTRO 1: BANDAS MIRROR
//------------------------------------------------------------------

if(filtermirror==true){
  int tendmirror=0;
  double mirrorred=iCustom(Symbol(),timemirror,"MA_Mirror",periodmirror,0,0,0);//Rojo //si positivo comprar si negativo Vender
if(mirrorred>0){
  tendmirror=1;
  ObjectSetText(Symbol()+"fmirror","F Mirror: Compra",7,NULL,Blue);
    ObjectSet(Symbol()+"fmirror",OBJPROP_CORNER,0);
    ObjectSet(Symbol()+"fmirror",OBJPROP_XDISTANCE,15);
    ObjectSet(Symbol()+"fmirror",OBJPROP_YDISTANCE,100);
}else{
  if(mirrorred<0)tendmirror=2;
  ObjectSetText(Symbol()+"fmirror","F Mirror: Venta",7,NULL,Red);
    ObjectSet(Symbol()+"fmirror",OBJPROP_CORNER,0);
    ObjectSet(Symbol()+"fmirror",OBJPROP_XDISTANCE,15);
    ObjectSet(Symbol()+"fmirror",OBJPROP_YDISTANCE,100);
}
}

//------------------------------------------------------------------
//FILTRO 2: BANDAS BOLLINGER
//------------------------------------------------------------------

if(filterbollingerbands==true){
  double bollingeralto = iBands(Symbol(),tiempobandas,periodobandas,2.0,0,PRICE_MEDIAN,1,0);
  double bollingerbajo = iBands(Symbol(),tiempobandas,periodobandas,2.0,0,PRICE_MEDIAN,2,0);
 int tendbollinger=0;
  if(bollingeralto<Bid){
    tendbollinger=2;
    ObjectSetText(Symbol()+"fbollinger","F Bollinger: Venta",7,NULL,Red);
      ObjectSet(Symbol()+"fbollinger",OBJPROP_CORNER,0);
      ObjectSet(Symbol()+"fbollinger",OBJPROP_XDISTANCE,15);
      ObjectSet(Symbol()+"fbollinger",OBJPROP_YDISTANCE,120);
  }else{
    if(bollingerbajo>Ask){
      tendbollinger=1;
      ObjectSetText(Symbol()+"fbollinger","F Bollinger: Compra",7,NULL,Blue);
        ObjectSet(Symbol()+"fbollinger",OBJPROP_CORNER,0);
        ObjectSet(Symbol()+"fbollinger",OBJPROP_XDISTANCE,15);
        ObjectSet(Symbol()+"fbollinger",OBJPROP_YDISTANCE,120);
    }else{
      tendbollinger=0;
      ObjectSetText(Symbol()+"fbollinger","F Bollinger: Neutro",7,NULL,Orange);
        ObjectSet(Symbol()+"fbollinger",OBJPROP_CORNER,0);
        ObjectSet(Symbol()+"fbollinger",OBJPROP_XDISTANCE,15);
        ObjectSet(Symbol()+"fbollinger",OBJPROP_YDISTANCE,120);
    }
  }
}


//------------------------------------------------------------------
//FILTRO 3: HISTO - MOMENTUM|MA|Itrend
//------------------------------------------------------------------
if(filterHisto==true){
  int tendhisto1=0;
  int tendhisto=0;
  if(histoindicator==1){
    double momentum = iMomentum(Symbol(),tiempohisto,histoperiod,histoapliedprice,0);
    double momentum2 = iMomentum(Symbol(),tiempohisto2,histoperiod2,histoapliedprice,0);
if(momentum>momentumresistancetop&&momentum2>momentumresistancetop){
  tendhisto1=2;
}else{
  if(momentum<momentumresistancebot&&momentum2<momentumresistancebot){
  tendhisto1=1;
}else{
  tendhisto1=0;
}
}
  }

  if(filteritrend==true){
    int itrendtend=0;
    double itrendb=iCustom(Symbol(),tiempoitrend,"itrend",2.0,0,0,itrendperiod,0,itrendpower,0,0);
    double itrends=iCustom(Symbol(),tiempoitrend,"itrend",2.0,0,0,itrendperiod,0,itrendpower,1,0);
    if(itrendb>0){
      itrendtend=1;
    }
    if(itrends>0){
      itrendtend=2;
    }
  }
    if(filtermahisto==true){
      int tendhistoma=0;
      double mahisto = iMA(Symbol(),tiempomahisto,maperiodhisto,0,0,histoapliedprice,0);
      if(Bid>mahisto){
        tendhistoma=2;
      }
      if(Ask<mahisto){
        tendhistoma=1;
      }

    }


if(filteritrend==true&&itrendtend==1){
  if(filtermahisto==true&&tendhistoma==1){
    if(histoindicator==1&&tendhisto1==1){
      tendhisto=1;
    }
    }
    if(filtermahisto==false){
      if(histoindicator==1&&tendhisto1==1){
        tendhisto=1;
      }
    }
  }


if(filteritrend==false){
  if(filtermahisto==true&&tendhistoma==1){
    if(histoindicator==1&&tendhisto1==1){
      tendhisto=1;
    }
    }
    if(filtermahisto==false){
      if(histoindicator==1&&tendhisto1==1){
        tendhisto=1;
      }
    }
}


if(filteritrend==true&&itrendtend==2){
  if(filtermahisto==true&&tendhistoma==2){
    if(histoindicator==1&&tendhisto1==2){
      tendhisto=2;
    }
    }
    if(filtermahisto==false){
      if(histoindicator==2&&tendhisto1==2){
        tendhisto=2;
      }
    }
  }
  if(filteritrend==false){
    if(filtermahisto==true&&tendhistoma==2){
      if(histoindicator==1&&tendhisto1==2){
        tendhisto=2;
      }
      }
      if(filtermahisto==false){
        if(histoindicator==1&&tendhisto1==2){
          tendhisto=2;
        }
      }
  }

if(tendhisto1==0){
  tendhisto=0;
}
if(tendhisto==1){
    ObjectSetText(Symbol()+"fhisto","F Histo: COMPRA",7,NULL,Blue);
      ObjectSet(Symbol()+"fhisto",OBJPROP_CORNER,0);
      ObjectSet(Symbol()+"fhisto",OBJPROP_XDISTANCE,15);
      ObjectSet(Symbol()+"fhisto",OBJPROP_YDISTANCE,140);
}
if(tendhisto==2){
  ObjectSetText(Symbol()+"fhisto","F Histo: VENTA",7,NULL,Red);
    ObjectSet(Symbol()+"fhisto",OBJPROP_CORNER,0);
    ObjectSet(Symbol()+"fhisto",OBJPROP_XDISTANCE,15);
    ObjectSet(Symbol()+"fhisto",OBJPROP_YDISTANCE,140);

}
if(tendhisto==0){
  ObjectSetText(Symbol()+"fhisto","F Histo: NEUTRAL",7,NULL,Orange);
    ObjectSet(Symbol()+"fhisto",OBJPROP_CORNER,0);
    ObjectSet(Symbol()+"fhisto",OBJPROP_XDISTANCE,15);
    ObjectSet(Symbol()+"fhisto",OBJPROP_YDISTANCE,140);
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
double lotesposicionc=0;
double lotesposicionv=0;

if(gestionlotesmethod==1){
  if(posicionesabiertasrobotc==0){
    lotesposicionc=NormalizeDouble(lotesinicial,lotround);
  }else{
    if(LastOrderlotsc>0){
      if(LastOrderlotsc>maxlots){
      lotesposicionc=NormalizeDouble(maxlots,lotround);
      }else{
        lotesposicionc=NormalizeDouble((LastOrderlotsc*multiplicador),lotround);
      }

    }else{
      lotesposicionc=NormalizeDouble(lotesinicial,lotround);
    }
  }
  if(posicionesabiertasrobotv==0){
    lotesposicionv=NormalizeDouble(lotesinicial,lotround);
  }else{
    if(LastOrderlotsv>0){
      if(LastOrderlotsv>maxlots){
        lotesposicionv=NormalizeDouble(maxlots,lotround);
      }
      lotesposicionv=NormalizeDouble((LastOrderlotsv*multiplicador),lotround);//+posicionesabiertasrobotv);
    }else{
      lotesposicionv=NormalizeDouble(lotesinicial,lotround);
    }
  }
}
if(gestionlotesmethod==2){
  if(posicionesabiertasrobotc==0){
    lotesposicionc=NormalizeDouble(lotesinicial,lotround);
  }else{
    lotesposicionc=NormalizeDouble((LastOrderlotsc*multiplicador)/posicionesabiertasrobotc,lotround);
  }
  if(posicionesabiertasrobotv==0){
    lotesposicionv=NormalizeDouble(lotesinicial,lotround);
  }else{
    lotesposicionv=NormalizeDouble((LastOrderlotsv*multiplicador)/posicionesabiertasrobotv,lotround);//+posicionesabiertasrobotv);
  }
}




    //------------------------------------------------------------------
    // ENVIO OPERACIONES
    //------------------------------------------------------------------
    //------------INICIO VENTA sola
    if(posicionesabiertasrobotv==0){




        if(filtermatrend==true&&matend==2){
          if(filterHisto==true&&tendhisto==2){
            if(filterFish==true&&tendfisher==2){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
          }
          if(filterHisto==false){
            if(filterFish==true&&tendfisher==2){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
          }
        }
        if(filtermatrend==false){
          if(filterHisto==true&&tendhisto==2){
            if(filterFish==true&&tendfisher==2){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
          }
          if(filterHisto==false){
            if(filterFish==true&&tendfisher==2){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
          }
        }




      }

      //------------Fin venta sola
    //------------INICIO COMPRA sola

    if(posicionesabiertasrobotc==0){



        if(filtermatrend==true&&matend==1){
          if(filterHisto==true&&tendhisto==1){
            if(filterFish==true&&tendfisher==1){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
          }
          if(filterHisto==false){
            if(filterFish==true&&tendfisher==1){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
          }
        }
        if(filtermatrend==false){
          if(filterHisto==true&&tendhisto==1){
            if(filterFish==true&&tendfisher==1){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
          }
          if(filterHisto==false){
            if(filterFish==true&&tendfisher==1){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
          }
        }



       }
    //-------------FIN COMPRA SOLA
    //----------------INICIO VENTA GRUPAL
    if(posicionesabiertasrobotv>0&&filter1v==1&&posicionesabiertasrobotv<maxposition){



        if(filtermatrend==true&&matend==2){
          if(filterHisto==true&&tendhisto==2){
            if(filterFish==true&&tendfisher==2){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
          }
          if(filterHisto==false){
            if(filterFish==true&&tendfisher==2){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
          }
        }
        if(filtermatrend==false){
          if(filterHisto==true&&tendhisto==2){
            if(filterFish==true&&tendfisher==2){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
          }
          if(filterHisto==false){
            if(filterFish==true&&tendfisher==2){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
          }
        }




    }

    //----------------FIN VENTA GRUPAL
    //----------------INICIO COMPRA GRUPAL
    if(posicionesabiertasrobotc>0&&filter1c==1&&posicionesabiertasrobotc<maxposition){




        if(filtermatrend==true&&matend==1){
          if(filterHisto==true&&tendhisto==1){
            if(filterFish==true&&tendfisher==1){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
          }
          if(filterHisto==false){
            if(filterFish==true&&tendfisher==1){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
          }
        }
        if(filtermatrend==false){
          if(filterHisto==true&&tendhisto==1){
            if(filterFish==true&&tendfisher==1){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
          }
          if(filterHisto==false){
            if(filterFish==true&&tendfisher==1){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
          }
        }




      }



    //FIN COMPRA GRUPAL



//ORDER MODIFY
int pipsmodify2V=0;
int pipsmodify2C=0;
if(filtergridpositionalotoforders==true){
  if(posicionesabiertasrobotv==1){
  pipsmodify2V=gridpositionalotoforderstp1;
  }
  if(posicionesabiertasrobotv==2){
  pipsmodify2V=gridpositionalotoforderstp2;
  }
  if(posicionesabiertasrobotv==3){
  pipsmodify2V=gridpositionalotoforderstp3;
  }
  if(posicionesabiertasrobotv==4){
  pipsmodify2V=gridpositionalotoforderstp4;
  }
  if(posicionesabiertasrobotv>=5){
  pipsmodify2V=gridpositionalotoforderstp5;
  }
  if(posicionesabiertasrobotc==1){
  pipsmodify2C=gridpositionalotoforderstp1;
  }
  if(posicionesabiertasrobotc==2){
  pipsmodify2C=gridpositionalotoforderstp2;
  }
  if(posicionesabiertasrobotc==3){
  pipsmodify2C=gridpositionalotoforderstp3;
  }
  if(posicionesabiertasrobotc==4){
  pipsmodify2C=gridpositionalotoforderstp4;
  }
  if(posicionesabiertasrobotc>=5){
  pipsmodify2C=gridpositionalotoforderstp5;
  }

}


if(filtergridpositionalotoforders==false){
pipsmodify2V=pipsmodify;
pipsmodify2C=pipsmodify;
}


for(int c2=0;c2<OrdersTotal();c2++)
{
OrderSelect(c2,SELECT_BY_POS,MODE_TRADES);
double takeprofitmodifyS=0;
double takeprofitmodifyB=0;
if(OrderSymbol()==Symbol()&&OrderComment()=="MUFASA")
{
if(OrderType()==OP_SELL){
  //ORDER MODIFY

 takeprofitmodifyS = NormalizeDouble(lastorderopenpriceV-(pipsmodify2V*MarketInfo(Symbol(),MODE_POINT)),MODE_DIGITS);
if(takeprofitmodifyS>0){
  if(OrderTakeProfit()!=takeprofitmodifyS&&OrderTicket()>0){
    OrderModify(OrderTicket(),OrderOpenPrice(),0,takeprofitmodifyS,0,Red);
  }
}


 //ORDER MODIFY
  if(closeallordersv==1&&autotakeprofit2==true)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);//Aqui
  if(autotkpfcierreV==1&&autotakeprofit==true)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);//Aqui
if(closefishertend=="CLOSESELL"&&closeorderfisher==true)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);//Aqui
}
}
if(OrderSymbol()==Symbol()&&OrderComment()=="MUFASA")
{
if(OrderType()==OP_BUY){
  //ORDER MODIFY

 takeprofitmodifyB = NormalizeDouble(lastorderopenpriceC+(pipsmodify2C*MarketInfo(Symbol(),MODE_POINT)),MODE_DIGITS);
if(takeprofitmodifyB>0){

  if(OrderTakeProfit()!=takeprofitmodifyB){
    OrderModify(OrderTicket(),OrderOpenPrice(),0,takeprofitmodifyB,0,Blue);
  }

}
 //ORDER MODIFY
  if(closeallordersc==1&&autotakeprofit2==true)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);//Aqui
  if(autotkpfcierreC==1&&autotakeprofit==true)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);//Aqui
  if(closefishertend=="CLOSEBUY"&&closeorderfisher==true)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);//Aqui
}
}
}




}//FIN TOTAL ORDERS 0 199


if(GetLastError()>0){
  printf("Ultimo error"+GetLastError());
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
