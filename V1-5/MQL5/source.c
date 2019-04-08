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
   IndList2 = 2, //ATR (Average true Range)
   IndList3 = 3, //CCI (Commodity Channel Index)
   IndList4 = 4  //RSI (Relative Strength Index)
  };


//:::::::::::::::::::::::::::::::::::::::::::::
#include <mt4accountinfo.mqh>
#include <mt4string.mqh>
#include <mt4datetime.mqh>
#include <mt4objects_1.mqh>
#include <mt4timeseries_2.mqh>
//Etc.
//:::::::::::::::::::::::::::::::::::::::::::::::

input string GESTIONLOTES="METODO 1 MARTINGALE, METODO 2 EN CONSTRUCCION --------------";
input int gestionlotesmethod=1;
input double lotesinicial=0.1; //first lot
input double multiplicador=3; //Martingale factor to recover bad choices
input string GRID="POSITION FIJA EN PIPS A PARTIR DE UNA OPERACION ABIERTA";
input double gridposition=80; //pips on every new trade
input string MAXPOSITION="NUMERO MAXIMO DE OPERACIONES A TENER ABIERTAS";
input int maxposition=20;//Max positions
input string MODIFY="MODIFY ORDER, SI TP FIJO PUEDES FIJARLO CON PIPSMODIFY";
input int pipsmodify=40; //pips to reach in position modify.
input string GRID2="METODO 2 GRID Y TP VARIABLES EN FUNCION A ORDENES CON PERDIDAS";
input bool filtergridpositionalotoforders=true;
input double gridpositionalotoforders1=100;
input double gridpositionalotoforders2=80;
input double gridpositionalotoforders3=60;
input double gridpositionalotoforders4=40;
input double gridpositionalotoforders5=20;
input double gridpositionalotoforderstp1=600;
input double gridpositionalotoforderstp2=500;
input double gridpositionalotoforderstp3=400;
input double gridpositionalotoforderstp4=350;
input double gridpositionalotoforderstp5=300;
input string FILTROMA="FILTRO MA QUE INDICA TENDENCIA A MEDIO PLAZO";
input bool filtermatrend=true;
input int periodmarojo=600;
input int periodmaamarillo=300;
input int periodmaverde=100;
input ENUM_TIMEFRAMES timematrend=PERIOD_M15;
input string FILTROHISTO="--------FILTRO HISTO-------------------";
input bool filterHisto=true;//Filter Momentum|ATR|CCI|RSI. UNDERCONSTRUCTION
input IndList histoindicator= 1;//Indicator Name
input int histoperiod = 150;//Indicator Period
input ENUM_APPLIED_PRICE histoapliedprice=PRICE_CLOSE;//Applied Price for Momentum, CCI or RSI
input ENUM_TIMEFRAMES tiempohisto=PERIOD_M15;//Bes time 15
input double momentumresistancetop=100.3;
input double momentumresistancebot=99.7;
input string FILTROMAHISTO="FILTRO MA DEL HISTO";
input bool filtermahisto=false;//FILTER MA FROM HISTO
input ENUM_TIMEFRAMES tiempomahisto=PERIOD_M1;
input int maperiodhisto=70;
input string FILTROFISHER="------ FILTRO FISHER ----------";
input bool filterFish=true;
input bool closeorderfisher=true;
input double minimumpipstocloseFISHER=70;
input ENUM_TIMEFRAMES tiempofish=PERIOD_M5;
input int periodfish=50;
input int apliedpricefish=0;
input bool modefastfish=false;
input bool signalsfish=false;
input int fishmaperiod1=9;
input int fishmaperiod2=45;
input int typema1fish=0;
input int typema2fish=3;
input string FILTRORESISTENCIAS="FILTRO RESISTENCIAS, EVITA ORDENES ERRONEAS CERCA DE RESISTENCIAS.";
input bool Resistanceopenfilter=true;
input double Resistancepipsminimo=30;//Cuanto mas pequeño mas se adiere a la resistencia
input ENUM_TIMEFRAMES Tiemporesistencias=PERIOD_H4;//Cuanto mas alto el valor mas seguro
input string CIERREPORMERCADO2="AUTOTP EN FUNCION A LAS RESISTENCIAS, EL SENSOR ES PIPS ANTES DE LLEGAR A RESISTENCIA";
input bool autotakeprofit=true;//V1, resistance fixed by pips (false and takeprofit value) or dinamic (true),
input int sensorautotkpf=5;//Min pips to get resistance (10 is ok)
input string CIERREPORMERCADO="METODO NO RECOMENDABLE DE CIERRE, TP FIJO EN FUNCION DE MERCADO, NO HAY LIMITE PARA FIJAR PIPS";
input double takeprofitpips=40; //Min pips to take profit
input string CIERREPORMERCADO3="AUTOTP2 EN FUNCION A FILTROS, PERDIDAS Y MIN PIPS";
input bool autotakeprofit2=true;//V1, Look for the profit of open orders and minimumpips allowed to close
input int minimumpipsallowedauto=35;
input string GLOBALORDERPROFIT="FILTRO PARA EVITAR CIERRE CON PERDIDAS";
input bool globalordersprofit=true;
input string GLOBALORDERPROFIT2="FILTRO GLOBAL PARA EVITAR CIERRE MENOS PIPS";
input int minpositionallowedtoclosepips=5;
input string FILTROBOLLINGER="FILTRO BOLLINGER";
input bool filterbollingerbands=true; //Bollinger usefull for Identify high and low
input int periodobandas=100; //Best period
input ENUM_TIMEFRAMES tiempobandas=PERIOD_M5; //Best time
input string FILTROITREND="FILTRO ITREND";
input bool filteritrend=false;
input ENUM_TIMEFRAMES tiempoitrend=PERIOD_M1;
input int itrendperiod=150;
input int itrendpower=100;
input string FILTROMIRROR="FILTRO MIRROR, INDICA DONDE ABRIR Y DONDE CERRAR.";
input bool filtermirror=false; //Mirror filter not very good
input int periodmirror=300; //Best period 300
input ENUM_TIMEFRAMES timemirror=PERIOD_M15; //Best time 15
input string OTHEROPTIONS="OTHER OPTIONS-----------------------";
input int TrailingStop=0;
input int MagicNumber=10001;
input int Slippage=10;

//+------------------------------------------------------------------+
//    ADVANCED CONFIGURATION
//+------------------------------------------------------------------+
input int Sizetrade=1000;



datetime next_candle;
//+------------------------------------------------------------------+
//    EAMufasa start function
//+------------------------------------------------------------------+
int OnInit()
  {


//   next_candle=Time[0]+Period();
datetime Time[];
int count=100;   // number of elements to copy
ArraySetAsSeries(Time,true);
CopyTime(_Symbol,_Period,0,count,Time);

   next_candle=Time[0]+30;
   ObjectCreate(_Symbol+1,OBJ_LABEL,0,0,0,0); // Tendencia Bands
   ObjectCreate(_Symbol+2,OBJ_LABEL,0,0,0,0); // Pips
   ObjectCreate(_Symbol+"slc",OBJ_HLINE,0,0,0,0,0);
   ObjectCreate(_Symbol+"slv",OBJ_HLINE,0,0,0,0,0);
   ObjectCreate(_Symbol+"restop",OBJ_LABEL,0,0,0,0);
   ObjectCreate(_Symbol+"resfiltsent",OBJ_LABEL,0,0,0,0);
   ObjectCreate(_Symbol+"minlot",OBJ_LABEL,0,0,0,0);
   ObjectCreate(_Symbol+"fbollinger",OBJ_LABEL,0,0,0,0);
ObjectCreate(_Symbol+"fmirror",OBJ_LABEL,0,0,0,0);
ObjectCreate(_Symbol+"fhisto",OBJ_LABEL,0,0,0,0);
ObjectCreate(_Symbol+"ffish",OBJ_LABEL,0,0,0,0);
ObjectCreate(_Symbol+"ordersprofit",OBJ_LABEL,0,0,0,0);
ObjectCreate(_Symbol+"filter1",OBJ_LABEL,0,0,0,0);
ObjectCreate(_Symbol+"Interface1",OBJ_LABEL,0,0,0,0);
ObjectCreate(_Symbol+"Interface2",OBJ_LABEL,0,0,0,0);
ObjectCreate(_Symbol+"Interface3",OBJ_LABEL,0,0,0,0);
ObjectCreate(_Symbol+"Interface4",OBJ_LABEL,0,0,0,0);
ObjectCreate(_Symbol+"matrend",OBJ_LABEL,0,0,0,0);




//+------------------------------------------------------------------+
//|                                                     InitMQL4.mqh |
//|                                                 Copyright DC2008 |
//|                                              https://www.mql5.com |
//+------------------------------------------------------------------+
#property copyright "keiji"
#property copyright "DC2008"
#property link      "https://www.mql5.com"
//--- Declaration of constants
#define OP_BUY 0           //Buy
#define OP_SELL 1          //Sell
#define OP_BUYLIMIT 2      //Pending order of BUY LIMIT type
#define OP_SELLLIMIT 3     //Pending order of SELL LIMIT type
#define OP_BUYSTOP 4       //Pending order of BUY STOP type
#define OP_SELLSTOP 5      //Pending order of SELL STOP type
//---
#define MODE_OPEN 0
#define MODE_CLOSE 3
#define MODE_VOLUME 4
#define MODE_REAL_VOLUME 5
#define MODE_TRADES 0
#define MODE_HISTORY 1
#define SELECT_BY_POS 0
#define SELECT_BY_TICKET 1
//---
#define DOUBLE_VALUE 0
#define FLOAT_VALUE 1
#define LONG_VALUE INT_VALUE
//---
#define CHART_BAR 0
#define CHART_CANDLE 1
//---
#define MODE_ASCEND 0
#define MODE_DESCEND 1
//---
#define MODE_LOW 1
#define MODE_HIGH 2
#define MODE_TIME 5
#define MODE_BID 9
#define MODE_ASK 10
#define MODE_POINT 11
#define MODE_DIGITS 12
#define MODE_SPREAD 13
#define MODE_STOPLEVEL 14
#define MODE_LOTSIZE 15
#define MODE_TICKVALUE 16
#define MODE_TICKSIZE 17
#define MODE_SWAPLONG 18
#define MODE_SWAPSHORT 19
#define MODE_STARTING 20
#define MODE_EXPIRATION 21
#define MODE_TRADEALLOWED 22
#define MODE_MINLOT 23
#define MODE_LOTSTEP 24
#define MODE_MAXLOT 25
#define MODE_SWAPTYPE 26
#define MODE_PROFITCALCMODE 27
#define MODE_MARGINCALCMODE 28
#define MODE_MARGININIT 29
#define MODE_MARGINMAINTENANCE 30
#define MODE_MARGINHEDGED 31
#define MODE_MARGINREQUIRED 32
#define MODE_FREEZELEVEL 33
//---
#define EMPTY -1





   return(0);
  }
  int OnDeinit()
  {


//----

//----
   return(0);
  }

void OnTick()
  {

    //:::::::::::::::::::::::::::::::::::::::::::::
    double Ask = SymbolInfoDouble(_Symbol,SYMBOL_ASK);
    double Bid = SymbolInfoDouble(_Symbol,SYMBOL_BID);
    int Bars=Bars(_Symbol,PERIOD_CURRENT);
    double Point=Point();
    double Orderprofitold=1;
    double OrderSwapold=0;
    double Ordercommissionold=0;
    double DiffPipsc1=0;
    double DiffPipsc=0;
    double DiffPipsv1=0;
    double DiffPipsv=0;
    double DiffPipsResistanceT=0;
    double DiffPipsResistanceB=0;
    //Etc.
    //:::::::::::::::::::::::::::::::::::::::::::::::


int point_compat=1;
//+------------------------------------------------------------------+
//    INTERFACE
//+------------------------------------------------------------------+
 double minlots = SymbolInfoDouble(_Symbol,SYMBOL_VOLUME_MIN);
 ObjectSetText(_Symbol+"minlot","Lots (Min: "+minlots+" Max: "+SymbolInfoDouble(_Symbol, SYMBOL_VOLUME_MAX)+") Size: "+SymbolInfoDouble(_Symbol, SYMBOL_TRADE_CONTRACT_SIZE)+" step:"+SymbolInfoDouble(_Symbol, SYMBOL_VOLUME_STEP),7,NULL,Orange);
  ObjectSet(_Symbol+"minlot",OBJPROP_CORNER,0);
  ObjectSet(_Symbol+"minlot",OBJPROP_XDISTANCE,50);
  ObjectSet(_Symbol+"minlot",OBJPROP_YDISTANCE,15);

int lotround=0;

if(SymbolInfoDouble(_Symbol,SYMBOL_VOLUME_STEP)==0.1){
  lotround=1;
}
if(SymbolInfoDouble(_Symbol,SYMBOL_VOLUME_STEP)==0.01){
  lotround=2;
}
if(SymbolInfoDouble(_Symbol,SYMBOL_VOLUME_STEP)==0.001){
  lotround=3;
}
if(SymbolInfoDouble(_Symbol,SYMBOL_VOLUME_STEP)==0.0001){
  lotround=4;
}

  ObjectSetText(_Symbol+"Interface1","Margen:["+AccountInfoDouble(ACCOUNT_MARGIN)+"] Margen Libre:["+AccountInfoDouble(ACCOUNT_FREEMARGIN)+"] Liquidez:["+AccountInfoDouble(ACCOUNT_EQUITY)+"] ",10,NULL,Yellow);
   ObjectSet(_Symbol+"Interface1",OBJPROP_CORNER,0);
   ObjectSet(_Symbol+"Interface1",OBJPROP_XDISTANCE,300);
   ObjectSet(_Symbol+"Interface1",OBJPROP_YDISTANCE,5);

   ObjectSetText(_Symbol+"Interface3","Rentabilidad:["+AccountInfoDouble(ACCOUNT_PROFIT)+"] Balance:["+AccountInfoDouble(ACCOUNT_BALANCE)+"] Credito:["+AccountInfoDouble(ACCOUNT_CREDIT)+"]",9,NULL,Yellow);
    ObjectSet(_Symbol+"Interface3",OBJPROP_CORNER,0);
    ObjectSet(_Symbol+"Interface3",OBJPROP_XDISTANCE,300);
    ObjectSet(_Symbol+"Interface3",OBJPROP_YDISTANCE,25);


   ObjectSetText(_Symbol+"Interface2",AccountInfoString(ACCOUNT_NAME)+"       Cuenta: "+AccountInfoInteger(ACCOUNT_LOGIN)+" ("+AccountInfoString(ACCOUNT_CURRENCY)+")",9,NULL,Yellow);
    ObjectSet(_Symbol+"Interface2",OBJPROP_CORNER,0);
    ObjectSet(_Symbol+"Interface2",OBJPROP_XDISTANCE,300);
    ObjectSet(_Symbol+"Interface2",OBJPROP_YDISTANCE,45);

    ObjectSetText(_Symbol+"Interface4","Server: "+AccountInfoString(ACCOUNT_SERVER)+" Empresa: "+AccountInfoString(ACCOUNT_COMPANY),9,NULL,Yellow);
     ObjectSet(_Symbol+"Interface4",OBJPROP_CORNER,0);
     ObjectSet(_Symbol+"Interface4",OBJPROP_XDISTANCE,300);
     ObjectSet(_Symbol+"Interface4",OBJPROP_YDISTANCE,65);








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
    ulong ticketordergpo=OrderGetTicket(gpo);
    OrderSelect(ticketordergpo);

    if(OrderGetInteger(ORDER_TYPE)==ORDER_TYPE_BUY&&OrderGetString(ORDER_SYMBOL)==_Symbol){
     DiffPipsc1 = MathAbs((NormalizeDouble(((Bid-OrderGetDouble(ORDER_PRICE_OPEN))/SymbolInfoDouble(_Symbol,SYMBOL_POINT)),SymbolInfoInteger(_Symbol,SYMBOL_DIGITS)))/point_compat);

      if(OrderSwapold<0){
        badorderswapC=OrderSwapold;
      }
       if(Ordercommissionold<0){
         badordercommissionC=Ordercommissionold;
       }
      if(Orderprofitold<0){
        badorderprofit1C = Orderprofitold;

      }
      if(Orderprofitold>0){
        badorderprofit2C = Orderprofitold;
      }
      lastorderopenpriceC=OrderGetDouble(ORDER_PRICE_OPEN);
    }
    if(OrderGetInteger(ORDER_TYPE)==ORDER_TYPE_SELL&&OrderGetString(ORDER_SYMBOL)==_Symbol){
       DiffPipsv1 = MathAbs((NormalizeDouble(((Bid-OrderGetDouble(ORDER_PRICE_OPEN))/SymbolInfoDouble(_Symbol,SYMBOL_POINT)),SymbolInfoInteger(_Symbol,SYMBOL_DIGITS)))/point_compat);

      if(OrderSwapold<0){
        badorderswapV=OrderSwapold;
      }
      if(Ordercommissionold<0){
      badordercommissionV=Ordercommissionold;
      }
      if(Orderprofitold<0){
        badorderprofit1V = Orderprofitold;
      }
      if(Orderprofitold>0){
        badorderprofit2V = Orderprofitold;
      }
      lastorderopenpriceV=OrderGetDouble(ORDER_PRICE_OPEN);
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
      ObjectSetText(_Symbol+"ordersprofit","OrderP B: ["+profitordersC+"]    OrdersP S: ["+profitordersV+"]",7,NULL,Orange);
       ObjectSet(_Symbol+"ordersprofit",OBJPROP_CORNER,0);
       ObjectSet(_Symbol+"ordersprofit",OBJPROP_XDISTANCE,15);
       ObjectSet(_Symbol+"ordersprofit",OBJPROP_YDISTANCE,180);
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

if(SymbolInfoInteger(_Symbol,SYMBOL_DIGITS)==3||SymbolInfoInteger(_Symbol,SYMBOL_DIGITS)==5)point_compat=10;
for(int pg=0;pg<OrdersTotal();pg++){
    ulong ticketorderpg=OrderGetTicket(pg);
OrderSelect(ticketorderpg);
if(OrderGetInteger(ORDER_TYPE)==ORDER_TYPE_SELL&&OrderGetString(ORDER_SYMBOL)==_Symbol){
  lastorderpS1=Orderprofitold;
 DiffPipsv = MathAbs((NormalizeDouble(((Bid-OrderGetDouble(ORDER_PRICE_OPEN))/SymbolInfoDouble(_Symbol,SYMBOL_POINT)),SymbolInfoInteger(_Symbol,SYMBOL_DIGITS)))/point_compat);
if(DiffPipsv>takeprofitpips&&autotakeprofit2==true&&profitordersV>0){
  closeallordersv=1;
}
}
if(OrderGetInteger(ORDER_TYPE)==ORDER_TYPE_BUY&&OrderGetString(ORDER_SYMBOL)==_Symbol){
  lastorderpB1=Orderprofitold;
   DiffPipsc = MathAbs((NormalizeDouble(((OrderGetDouble(ORDER_PRICE_OPEN)-Ask)/SymbolInfoDouble(_Symbol,SYMBOL_POINT)),SymbolInfoInteger(_Symbol,SYMBOL_DIGITS)))/point_compat);
if(DiffPipsc>takeprofitpips&&autotakeprofit2==true&&profitordersC>0){
  closeallordersc=1;
}
}
ObjectSetText(_Symbol+2,"PipsC: "+DiffPipsc+" PipsV: "+DiffPipsv,7,NULL,Orange);
  ObjectSet(_Symbol+2,OBJPROP_CORNER,0);
  ObjectSet(_Symbol+2,OBJPROP_XDISTANCE,15);
  ObjectSet(_Symbol+2,OBJPROP_YDISTANCE,40);
}





//------------------------------------------------------------------
//VALORES DE TAKEPROFIT Y STOPLOSS (RESTOP Y RESBOT)
//------------------------------------------------------------------
if(autotakeprofit==true||Resistanceopenfilter==true){
  double takeprofitp1v = iCustom(_Symbol,Tiemporesistencias,"SL_BW",0,0);//15 //30 //60 //240
  double takeprofitp1c = iCustom(_Symbol,Tiemporesistencias,"SL_BW",1,0);//15 //30 //60 //240
  DiffPipsResistanceT = MathAbs((NormalizeDouble(((takeprofitp1v-Ask)/SymbolInfoDouble(_Symbol,SYMBOL_POINT)),SymbolInfoInteger(_Symbol,SYMBOL_DIGITS)))/point_compat);
 DiffPipsResistanceB = MathAbs((NormalizeDouble(((takeprofitp1c-Bid)/SymbolInfoDouble(_Symbol,SYMBOL_POINT)),SymbolInfoInteger(_Symbol,SYMBOL_DIGITS)))/point_compat);

  ObjectSetText(_Symbol+"restop","TOP: [Venta "+DiffPipsResistanceT+"] BOT: [Compra "+DiffPipsResistanceB+"]",7,NULL,Orange);
    ObjectSet(_Symbol+"restop",OBJPROP_CORNER,0);
    ObjectSet(_Symbol+"restop",OBJPROP_XDISTANCE,15);
    ObjectSet(_Symbol+"restop",OBJPROP_YDISTANCE,60);


    if(Resistanceopenfilter==true){
    int Filterresistance=0;

      if(DiffPipsResistanceT>DiffPipsResistanceB){
        if(DiffPipsResistanceT>1000000){
          Filterresistance=1;
          ObjectSetText(_Symbol+"resfiltsent","F Resistencias: Compra",7,NULL,Blue);
            ObjectSet(_Symbol+"resfiltsent",OBJPROP_CORNER,0);
            ObjectSet(_Symbol+"resfiltsent",OBJPROP_XDISTANCE,15);
            ObjectSet(_Symbol+"resfiltsent",OBJPROP_YDISTANCE,80);
        }else{
          if(DiffPipsResistanceB>1000000){
            Filterresistance=2;
            ObjectSetText(_Symbol+"resfiltsent","F Resistencias: Venta",7,NULL,Red);
              ObjectSet(_Symbol+"resfiltsent",OBJPROP_CORNER,0);
              ObjectSet(_Symbol+"resfiltsent",OBJPROP_XDISTANCE,15);
              ObjectSet(_Symbol+"resfiltsent",OBJPROP_YDISTANCE,80);
          }else{
            Filterresistance=2;
            ObjectSetText(_Symbol+"resfiltsent","F Resistencias: Venta",7,NULL,Red);
              ObjectSet(_Symbol+"resfiltsent",OBJPROP_CORNER,0);
              ObjectSet(_Symbol+"resfiltsent",OBJPROP_XDISTANCE,15);
              ObjectSet(_Symbol+"resfiltsent",OBJPROP_YDISTANCE,80);
          }

        }


      }else{
        if(DiffPipsResistanceT<DiffPipsResistanceB){
          if(DiffPipsResistanceT>1000000){
            Filterresistance=1;
            ObjectSetText(_Symbol+"resfiltsent","F Resistencias: Compra",7,NULL,Blue);
              ObjectSet(_Symbol+"resfiltsent",OBJPROP_CORNER,0);
              ObjectSet(_Symbol+"resfiltsent",OBJPROP_XDISTANCE,15);
              ObjectSet(_Symbol+"resfiltsent",OBJPROP_YDISTANCE,80);
          }else{
            if(DiffPipsResistanceB>1000000){
              Filterresistance=2;
              ObjectSetText(_Symbol+"resfiltsent","F Resistencias: Venta",7,NULL,Red);
                ObjectSet(_Symbol+"resfiltsent",OBJPROP_CORNER,0);
                ObjectSet(_Symbol+"resfiltsent",OBJPROP_XDISTANCE,15);
                ObjectSet(_Symbol+"resfiltsent",OBJPROP_YDISTANCE,80);
            }else{
              Filterresistance=1;
              ObjectSetText(_Symbol+"resfiltsent","F Resistencias: Compra",7,NULL,Blue);
                ObjectSet(_Symbol+"resfiltsent",OBJPROP_CORNER,0);
                ObjectSet(_Symbol+"resfiltsent",OBJPROP_XDISTANCE,15);
                ObjectSet(_Symbol+"resfiltsent",OBJPROP_YDISTANCE,80);
            }
          }




        }else{
          Filterresistance=0;
          ObjectSetText(_Symbol+"resfiltsent","F Resistencias: Neutro",7,NULL,Orange);
            ObjectSet(_Symbol+"resfiltsent",OBJPROP_CORNER,0);
            ObjectSet(_Symbol+"resfiltsent",OBJPROP_XDISTANCE,15);
            ObjectSet(_Symbol+"resfiltsent",OBJPROP_YDISTANCE,80);
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
  double fishbuf1white = iCustom(_Symbol,tiempofish,"fisher",periodfish,apliedpricefish,modefastfish,signalsfish,fishmaperiod1,fishmaperiod2,"1","1",typema1fish,typema2fish,2,0);
  double fishbuf2green = iCustom(_Symbol,tiempofish,"fisher",periodfish,apliedpricefish,modefastfish,signalsfish,fishmaperiod1,fishmaperiod2,"1","1",typema1fish,typema2fish,3,0);
  double fishbuf3red = iCustom(_Symbol,tiempofish,"fisher",periodfish,apliedpricefish,modefastfish,signalsfish,fishmaperiod1,fishmaperiod2,"1","1",typema1fish,typema2fish,4,0);

if(fishbuf1white<1&&fishbuf1white>fishbuf2green&&fishbuf2green>fishbuf3red){
  tendfisher=1;
  ObjectSetText(_Symbol+"ffish","F Fisher(T"+tiempofish+")("+periodfish+"): COMPRA",7,NULL,Blue);
    ObjectSet(_Symbol+"ffish",OBJPROP_CORNER,0);
    ObjectSet(_Symbol+"ffish",OBJPROP_XDISTANCE,15);
    ObjectSet(_Symbol+"ffish",OBJPROP_YDISTANCE,160);
}else{
  if(fishbuf1white>-1&&fishbuf3red>fishbuf2green&&fishbuf2green>fishbuf1white){
    tendfisher=2;
    ObjectSetText(_Symbol+"ffish","F Fisher(T"+tiempofish+")("+periodfish+"): VENTA",7,NULL,Red);
      ObjectSet(_Symbol+"ffish",OBJPROP_CORNER,0);
      ObjectSet(_Symbol+"ffish",OBJPROP_XDISTANCE,15);
      ObjectSet(_Symbol+"ffish",OBJPROP_YDISTANCE,160);
  }else{
    tendfisher=0;
    ObjectSetText(_Symbol+"ffish","F Fisher(T"+tiempofish+")("+periodfish+"): NEUTRO [white: "+fishbuf1white+"][B: "+fishbuf2green+"][S: "+fishbuf3red+"]",7,NULL,Orange);
      ObjectSet(_Symbol+"ffish",OBJPROP_CORNER,0);
      ObjectSet(_Symbol+"ffish",OBJPROP_XDISTANCE,15);
      ObjectSet(_Symbol+"ffish",OBJPROP_YDISTANCE,160);
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
      double marojo1 = iMA(_Symbol,timematrend,periodmarojo,0,MODE_SMA,PRICE_MEDIAN);
      double maamarillo1 = iMA(_Symbol,timematrend,periodmaamarillo,0,MODE_SMA,PRICE_MEDIAN);
      double maverde1 = iMA(_Symbol,timematrend,periodmaverde,0,MODE_SMA,PRICE_MEDIAN);
      if(marojo1>maamarillo1&&maamarillo1>maverde1){
        matend=2;
        ObjectSetText(_Symbol+"matrend","F MATREND (Tiempo"+timematrend+"R"+periodmarojo+"A"+periodmaamarillo+"V"+periodmaverde+"): VENTA",7,NULL,Red);
          ObjectSet(_Symbol+"matrend",OBJPROP_CORNER,0);
          ObjectSet(_Symbol+"matrend",OBJPROP_XDISTANCE,15);
          ObjectSet(_Symbol+"matrend",OBJPROP_YDISTANCE,220);
      }else{
        if(maverde1>maamarillo1&&maamarillo1>marojo1){
          matend=1;
          ObjectSetText(_Symbol+"matrend","F MATREND (Tiempo"+timematrend+"R"+periodmarojo+"A"+periodmaamarillo+"V"+periodmaverde+"): COMPRA",7,NULL,Blue);
            ObjectSet(_Symbol+"matrend",OBJPROP_CORNER,0);
            ObjectSet(_Symbol+"matrend",OBJPROP_XDISTANCE,15);
            ObjectSet(_Symbol+"matrend",OBJPROP_YDISTANCE,220);
        }else{
          matend=0;
          ObjectSetText(_Symbol+"matrend","F MATREND (Tiempo"+timematrend+"R"+periodmarojo+"A"+periodmaamarillo+"V"+periodmaverde+"): NEUTRO",7,NULL,Orange);
            ObjectSet(_Symbol+"matrend",OBJPROP_CORNER,0);
            ObjectSet(_Symbol+"matrend",OBJPROP_XDISTANCE,15);
            ObjectSet(_Symbol+"matrend",OBJPROP_YDISTANCE,220);
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
    ulong ticketordercnt1=OrderGetTicket(cnt1);
OrderSelect(ticketordercnt1);
if(OrderGetString(ORDER_SYMBOL)==_Symbol)
{
if(OrderGetInteger(ORDER_TYPE)==ORDER_TYPE_SELL){
 posicionesabiertasrobotv++;
 LastOrderlotsv=OrderGetDouble(ORDER_VOLUME_CURRENT);
 if(closeallordersv==1&&autotakeprofit2==true)OrderClose(ticketordercnt1,OrderGetDouble(ORDER_VOLUME_CURRENT),OrderClosePrice(),Slippage,Red);//Aqui
 if(autotkpfcierreV==1&&autotakeprofit==true)OrderClose(ticketordercnt1,OrderGetDouble(ORDER_VOLUME_CURRENT),OrderClosePrice(),Slippage,Red);//Aqui
 if(closefishertend=="CLOSESELL"&&closeorderfisher==true)OrderClose(ticketordercnt1,OrderGetDouble(ORDER_VOLUME_CURRENT),OrderClosePrice(),Slippage,Red);//Aqui


}
}
if(OrderGetString(ORDER_SYMBOL)==_Symbol)
{
if(OrderGetInteger(ORDER_TYPE)==ORDER_TYPE_BUY){
  LastOrderlotsc=OrderGetDouble(ORDER_VOLUME_CURRENT);
posicionesabiertasrobotc++;
if(closeallordersc==1&&autotakeprofit2==true)OrderClose(ticketordercnt1,OrderGetDouble(ORDER_VOLUME_CURRENT),OrderClosePrice(),Slippage,Blue);//Aqui
if(autotkpfcierreC==1&&autotakeprofit==true)OrderClose(ticketordercnt1,OrderGetDouble(ORDER_VOLUME_CURRENT),OrderClosePrice(),Slippage,Blue);//Aqui
if(closefishertend=="CLOSEBUY"&&closeorderfisher==true)OrderClose(ticketordercnt1,OrderGetDouble(ORDER_VOLUME_CURRENT),OrderClosePrice(),Slippage,Blue);//Aqui

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
if(posicionesabiertasrobotc>4){
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
if(posicionesabiertasrobotv>4){
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



ObjectSetText(_Symbol+"filter1","filter1c: ["+filter1c+"]   filter1v:["+filter1v+"]",7,NULL,Orange);
  ObjectSet(_Symbol+"filter1",OBJPROP_CORNER,0);
  ObjectSet(_Symbol+"filter1",OBJPROP_XDISTANCE,15);
  ObjectSet(_Symbol+"filter1",OBJPROP_YDISTANCE,200);

//------------------------------------------------------------------
//FILTRO 1: BANDAS MIRROR
//------------------------------------------------------------------

if(filtermirror==true){
  int tendmirror=0;
  double mirrorred=iCustom(_Symbol,timemirror,"MA_Mirror",periodmirror,0,0,0);//Rojo //si positivo comprar si negativo Vender
if(mirrorred>0){
  tendmirror=1;
  ObjectSetText(_Symbol+"fmirror","F Mirror: Compra",7,NULL,Blue);
    ObjectSet(_Symbol+"fmirror",OBJPROP_CORNER,0);
    ObjectSet(_Symbol+"fmirror",OBJPROP_XDISTANCE,15);
    ObjectSet(_Symbol+"fmirror",OBJPROP_YDISTANCE,100);
}else{
  if(mirrorred<0)tendmirror=2;
  ObjectSetText(_Symbol+"fmirror","F Mirror: Venta",7,NULL,Red);
    ObjectSet(_Symbol+"fmirror",OBJPROP_CORNER,0);
    ObjectSet(_Symbol+"fmirror",OBJPROP_XDISTANCE,15);
    ObjectSet(_Symbol+"fmirror",OBJPROP_YDISTANCE,100);
}
}

//------------------------------------------------------------------
//FILTRO 2: BANDAS BOLLINGER
//------------------------------------------------------------------

if(filterbollingerbands==true){
  double bollingeralto = iBands(_Symbol,tiempobandas,periodobandas,2.0,0,PRICE_MEDIAN,1,0);
  double bollingerbajo = iBands(_Symbol,tiempobandas,periodobandas,2.0,0,PRICE_MEDIAN,2,0);
 int tendbollinger=0;
  if(bollingeralto<Bid){
    tendbollinger=2;
    ObjectSetText(_Symbol+"fbollinger","F Bollinger: Venta",7,NULL,Red);
      ObjectSet(_Symbol+"fbollinger",OBJPROP_CORNER,0);
      ObjectSet(_Symbol+"fbollinger",OBJPROP_XDISTANCE,15);
      ObjectSet(_Symbol+"fbollinger",OBJPROP_YDISTANCE,120);
  }else{
    if(bollingerbajo>Ask){
      tendbollinger=1;
      ObjectSetText(_Symbol+"fbollinger","F Bollinger: Compra",7,NULL,Blue);
        ObjectSet(_Symbol+"fbollinger",OBJPROP_CORNER,0);
        ObjectSet(_Symbol+"fbollinger",OBJPROP_XDISTANCE,15);
        ObjectSet(_Symbol+"fbollinger",OBJPROP_YDISTANCE,120);
    }else{
      tendbollinger=0;
      ObjectSetText(_Symbol+"fbollinger","F Bollinger: Neutro",7,NULL,Orange);
        ObjectSet(_Symbol+"fbollinger",OBJPROP_CORNER,0);
        ObjectSet(_Symbol+"fbollinger",OBJPROP_XDISTANCE,15);
        ObjectSet(_Symbol+"fbollinger",OBJPROP_YDISTANCE,120);
    }
  }
}


//------------------------------------------------------------------
//FILTRO 3: HISTO - MOMENTUM|MA|Itrend
//------------------------------------------------------------------
if(filterHisto==true){
  int tendhisto=0;
  int tendhistoma=0;
  if(histoindicator==1){
    double momentum = iMomentum(_Symbol,tiempohisto,histoperiod,histoapliedprice,0);
  }

  if(filteritrend==true){
    int itrendtend=0;
    double itrendb=iCustom(_Symbol,tiempoitrend,"itrend",2.0,0,0,itrendperiod,0,itrendpower,0,0);
    double itrends=iCustom(_Symbol,tiempoitrend,"itrend",2.0,0,0,itrendperiod,0,itrendpower,1,0);
    if(itrendb>0){
      itrendtend=1;
    }
    if(itrends>0){
      itrendtend=2;
    }
  }


    if(filtermahisto==true){
      double mahisto = iMA(_Symbol,tiempomahisto,maperiodhisto,0,MODE_SMA,histoapliedprice);

      if(Bid>mahisto){
        tendhistoma=2;
      }
      if(Ask<mahisto){
        tendhistoma=1;
      }



      if(histoindicator==1){

      if(momentum<momentumresistancetop&&tendhistoma==1){
        if(filteritrend==true&&itrendtend==1){
          tendhisto=1;
          ObjectSetText(_Symbol+"fhisto","F Histo: COMPRA",7,NULL,Blue);
            ObjectSet(_Symbol+"fhisto",OBJPROP_CORNER,0);
            ObjectSet(_Symbol+"fhisto",OBJPROP_XDISTANCE,15);
            ObjectSet(_Symbol+"fhisto",OBJPROP_YDISTANCE,140);
        }
        if(filteritrend==false){
          tendhisto=1;
          ObjectSetText(_Symbol+"fhisto","F Histo: COMPRA",7,NULL,Blue);
            ObjectSet(_Symbol+"fhisto",OBJPROP_CORNER,0);
            ObjectSet(_Symbol+"fhisto",OBJPROP_XDISTANCE,15);
            ObjectSet(_Symbol+"fhisto",OBJPROP_YDISTANCE,140);
        }

      }else{
        if(momentum>momentumresistancebot&&tendhistoma==2){
          if(filteritrend==true&&itrendtend==2){
            tendhisto=2;
            ObjectSetText(_Symbol+"fhisto","F Histo: VENTA",7,NULL,Red);
              ObjectSet(_Symbol+"fhisto",OBJPROP_CORNER,0);
              ObjectSet(_Symbol+"fhisto",OBJPROP_XDISTANCE,15);
              ObjectSet(_Symbol+"fhisto",OBJPROP_YDISTANCE,140);
          }
          if(filteritrend==false){
            tendhisto=2;
            ObjectSetText(_Symbol+"fhisto","F Histo: VENTA",7,NULL,Red);
              ObjectSet(_Symbol+"fhisto",OBJPROP_CORNER,0);
              ObjectSet(_Symbol+"fhisto",OBJPROP_XDISTANCE,15);
              ObjectSet(_Symbol+"fhisto",OBJPROP_YDISTANCE,140);
          }

        }else{
          tendhisto=0;
          ObjectSetText(_Symbol+"fhisto","F Histo: Neutral",7,NULL,Orange);
            ObjectSet(_Symbol+"fhisto",OBJPROP_CORNER,0);
            ObjectSet(_Symbol+"fhisto",OBJPROP_XDISTANCE,15);
            ObjectSet(_Symbol+"fhisto",OBJPROP_YDISTANCE,140);
        }

      }

      }




    }



  if(filtermahisto==false){
    if(histoindicator==1){
    if(momentum>100){
      tendhisto=1;
      ObjectSetText(_Symbol+"fhisto","F Histo: COMPRA",7,NULL,Blue);
        ObjectSet(_Symbol+"fhisto",OBJPROP_CORNER,0);
        ObjectSet(_Symbol+"fhisto",OBJPROP_XDISTANCE,15);
        ObjectSet(_Symbol+"fhisto",OBJPROP_YDISTANCE,140);
    }else{
      tendhisto=2;
      ObjectSetText(_Symbol+"fhisto","F Histo: VENTA",7,NULL,Red);
        ObjectSet(_Symbol+"fhisto",OBJPROP_CORNER,0);
        ObjectSet(_Symbol+"fhisto",OBJPROP_XDISTANCE,15);
        ObjectSet(_Symbol+"fhisto",OBJPROP_YDISTANCE,140);
    }
    }
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
    lotesposicionc=NormalizeDouble((LastOrderlotsc*multiplicador),lotround);
  }
  if(posicionesabiertasrobotv==0){
    lotesposicionv=NormalizeDouble(lotesinicial,lotround);
  }else{
    lotesposicionv=NormalizeDouble((LastOrderlotsv*multiplicador),lotround);//+posicionesabiertasrobotv);
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
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
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
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
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
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
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
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
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
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
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
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
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
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
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
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
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
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
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
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
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
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
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
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==2){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==2){
                if(filterbollingerbands==true&&tendbollinger==2){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==2){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,1,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
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
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
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
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
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
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
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
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(filterFish==false){
              if(Resistanceopenfilter==true&&Filterresistance==1){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                }
              }
              if(Resistanceopenfilter==false){
                if(filtermirror==true&&tendmirror==1){
                if(filterbollingerbands==true&&tendbollinger==1){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                if(filterbollingerbands==false){
                  OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                }
                }
                if(filtermirror==false){
                  if(filterbollingerbands==true&&tendbollinger==1){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
                  }
                  if(filterbollingerbands==false){
                    OrderSend(_Symbol,0,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
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
  if(posicionesabiertasrobotv>4){
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
  if(posicionesabiertasrobotc>4){
  pipsmodify2C=gridpositionalotoforderstp5;
  }

}


if(filtergridpositionalotoforders==false){
pipsmodify2V=pipsmodify;
pipsmodify2C=pipsmodify;
}


for(int c2=0;c2<OrdersTotal();c2++)
{
    ulong ticketorderc2=OrderGetTicket(c2);
OrderSelect(ticketorderc2);
double takeprofitmodifyS=0;
double takeprofitmodifyB=0;
if(OrderGetString(ORDER_SYMBOL)==_Symbol)
{
if(OrderGetInteger(ORDER_TYPE)==ORDER_TYPE_SELL){
  //ORDER MODIFY

 takeprofitmodifyS = NormalizeDouble(lastorderopenpriceV-(pipsmodify2V*SymbolInfoDouble(_Symbol,SYMBOL_POINT)),MODE_DIGITS);
if(takeprofitmodifyS>0){
  if(OrderTakeProfit()!=takeprofitmodifyS&&ticketorderc2>0){
    OrderModify(ticketorderc2,OrderGetDouble(ORDER_PRICE_OPEN),0,takeprofitmodifyS,0,Red);
  }
}


 //ORDER MODIFY
  if(closeallordersv==1&&autotakeprofit2==true)OrderClose(ticketorderc2,OrderGetDouble(ORDER_VOLUME_CURRENT),OrderClosePrice(),Slippage,Red);//Aqui
  if(autotkpfcierreV==1&&autotakeprofit==true)OrderClose(ticketorderc2,OrderGetDouble(ORDER_VOLUME_CURRENT),OrderClosePrice(),Slippage,Red);//Aqui
if(closefishertend=="CLOSESELL"&&closeorderfisher==true)OrderClose(ticketorderc2,OrderGetDouble(ORDER_VOLUME_CURRENT),OrderClosePrice(),Slippage,Red);//Aqui
}
}
if(OrderGetString(ORDER_SYMBOL)==_Symbol)
{
if(OrderGetInteger(ORDER_TYPE)==ORDER_TYPE_BUY){
  //ORDER MODIFY

 takeprofitmodifyB = NormalizeDouble(lastorderopenpriceC+(pipsmodify2C*SymbolInfoDouble(_Symbol,SYMBOL_POINT)),MODE_DIGITS);
if(takeprofitmodifyB>0){

  if(OrderTakeProfit()!=takeprofitmodifyB){
    OrderModify(ticketorderc2,OrderGetDouble(ORDER_PRICE_OPEN),0,takeprofitmodifyB,0,Blue);
  }

}
 //ORDER MODIFY
  if(closeallordersc==1&&autotakeprofit2==true)OrderClose(ticketorderc2,OrderGetDouble(ORDER_VOLUME_CURRENT),OrderClosePrice(),Slippage,Blue);//Aqui
  if(autotkpfcierreC==1&&autotakeprofit==true)OrderClose(ticketorderc2,OrderGetDouble(ORDER_VOLUME_CURRENT),OrderClosePrice(),Slippage,Blue);//Aqui
  if(closefishertend=="CLOSEBUY"&&closeorderfisher==true)OrderClose(ticketorderc2,OrderGetDouble(ORDER_VOLUME_CURRENT),OrderClosePrice(),Slippage,Blue);//Aqui
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
   ulong ticketorderi=OrderGetTicket(i);
      OrderSelect(ticketorderi);
      if(OrderMagicNumber()==MagicNumber) result++;

     }
   return (result);
  }
