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
extern bool filternegativeopenorders=true;
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
extern string TAICHI="TAICHI INDICATOR.";
extern bool filtercronextaichi=true;
extern ENUM_TIMEFRAMES Tiempotaichi=PERIOD_M1;
extern int Tenkan=9;
extern int Kijun=26;
extern int Senkou=54;
extern bool autoclosetaichi=true;
extern string DEGREES="DEGREES";
extern bool filterdegrees=true;
extern ENUM_TIMEFRAMES Tiempolrdegrees=PERIOD_M1;
extern ENUM_TIMEFRAMES Tiempolrdegrees2=PERIOD_M15;
extern bool autoclosedegrees=true;
extern string CAPCHANNEL="INDICADOR CAP CHANNEL";
extern bool CAPChannelfilter=true;
extern ENUM_TIMEFRAMES TiempoCAPchannel=PERIOD_M1;
extern ENUM_TIMEFRAMES TiempoCAPchannel2=PERIOD_M5;
extern ENUM_TIMEFRAMES TiempoCAPchannel3=PERIOD_M15;
extern int periodCAPchannel=300;
extern bool autoclosecapchannel=true;
extern int periodCAPchannel2=100;
extern bool turtletrend=true;
extern ENUM_TIMEFRAMES Tiempoturtletrend=PERIOD_M1;
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
ObjectCreate(Symbol()+"ordersprofit",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"filter1",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"Interface1",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"Interface2",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"Interface3",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"Interface4",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"channel",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"tpmpV",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"tpmpC",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"degrees",OBJ_LABEL,0,0,0,0);

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





 //------------------------------------------------------------------
//Global OrdersProfit for bad orders V2
//------------------------------------------------------------------
double profitgpo1C=0;
double profitgpo1V=0;
double profitorder1C=0;
double profitorder1V=0;
double profitorder2C=0;
double profitorder2V=0;
for(int gpo1=0;gpo1<OrdersTotal();gpo1++){
OrderSelect(gpo1,SELECT_BY_POS,MODE_TRADES);
  if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()&&OrderComment()=="EAK"){
  profitgpo1C = OrderProfit();
  if(profitgpo1C<0){
    profitorder1C++;
  }
  if(profitgpo1C>0){
    profitorder2C++;
  }
  }
  if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()&&OrderComment()=="EAK"){
  profitgpo1V = OrderProfit();
    if(profitgpo1V<0){
      profitorder1V++;
    }
    if(profitgpo1V>0){
      profitorder2V++;
    }
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
    if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()&&OrderComment()=="EAK"){

      double DiffPipsc1 = MathAbs((NormalizeDouble(((Bid-OrderOpenPrice())/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);

      if(OrderSwap()<0){
        badorderswapC=OrderSwap();
      }
      if(OrderCommission()<0){
      badordercommissionC=OrderCommission();
      }
      if(OrderProfit()<0){
        badorderprofit1C = OrderProfit()+(badorderprofit1C/2);
      }
      if(OrderProfit()>0){
        badorderprofit2C = OrderProfit()+(badorderprofit2C/2)+(badorderprofit1C/2);
      }



      lastorderopenpriceC=OrderOpenPrice();
    }
    if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()&&OrderComment()=="EAK"){
      double DiffPipsv1 = MathAbs((NormalizeDouble(((Bid-OrderOpenPrice())/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);

      if(OrderSwap()<0){
        badorderswapV=OrderSwap();
      }
      if(OrderCommission()<0){
      badordercommissionV=OrderCommission();
      }
      if(OrderProfit()<0){
        badorderprofit1V = OrderProfit()+(badorderprofit1V/2);
      }
      if(OrderProfit()>0){
        badorderprofit2V = OrderProfit()+(badorderprofit2V/2)+(badorderprofit1V/2);
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
if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()&&OrderComment()=="EAK"){
  lastorderpS1=OrderProfit();
double DiffPipsv = MathAbs((NormalizeDouble(((Bid-OrderOpenPrice())/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);
if(DiffPipsv>takeprofitpips&&autotakeprofit2==true&&profitordersV>0){
  closeallordersv=1;
}
}
if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()&&OrderComment()=="EAK"){
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
     // FILTROS E INDICADORES
     //------------------------------------------------------------------


     // Cronex_Taichi
     if(filtercronextaichi==true){

     double taichi = iCustom(Symbol(),Tiempotaichi,"Cronex_Taichi",Tenkan,Kijun,Senkou,0,0);
     double taichifor = iCustom(Symbol(),Tiempotaichi,"Cronex_Taichi",Tenkan,Kijun,Senkou,3,0);
     double taisignal = iCustom(Symbol(),Tiempotaichi,"Cronex_Taichi",Tenkan,Kijun,Senkou,1,0);
     double taissignal = iCustom(Symbol(),Tiempotaichi,"Cronex_Taichi",Tenkan,Kijun,Senkou,2,0);
     double taiflat = iCustom(Symbol(),Tiempotaichi,"Cronex_Taichi",Tenkan,Kijun,Senkou,4,0);
     int flat=0;
     int taichitend1=0;
     int taichitend=0;
     int closetaichi=0;
     if(taiflat>0&&taiflat<1000000){
       flat=1;
       ObjectSetText(Symbol()+"taichi","Taichi: FLAT",7,NULL,Orange);
         ObjectSet(Symbol()+"taichi",OBJPROP_CORNER,0);
         ObjectSet(Symbol()+"taichi",OBJPROP_XDISTANCE,15);
         ObjectSet(Symbol()+"taichi",OBJPROP_YDISTANCE,300);
     }
     if(taichi<Bid&&taichi<taichifor&&taisignal<taissignal){
     taichitend1=2;
     }
     if(taichi>Ask&&taichi>taichifor&&taisignal>taissignal){
     taichitend1=1;
     }

     if(taichitend1==1&&flat==0){
       taichitend=1;
       ObjectSetText(Symbol()+"taichi","Taichi: COMPRA",7,NULL,Blue);
         ObjectSet(Symbol()+"taichi",OBJPROP_CORNER,0);
         ObjectSet(Symbol()+"taichi",OBJPROP_XDISTANCE,15);
         ObjectSet(Symbol()+"taichi",OBJPROP_YDISTANCE,300);
     }
     if(taichitend1==2&&flat==0){
       taichitend=2;
       ObjectSetText(Symbol()+"taichi","Taichi: VENTA",7,NULL,Red);
         ObjectSet(Symbol()+"taichi",OBJPROP_CORNER,0);
         ObjectSet(Symbol()+"taichi",OBJPROP_XDISTANCE,15);
         ObjectSet(Symbol()+"taichi",OBJPROP_YDISTANCE,300);
     }


     if(autoclosetaichi==true){
       if(taichitend==1){
         closetaichi=2;
       }
       if(taichitend==2){
         closetaichi=1;
       }
     }
     }


 if(CAPChannelfilter==true){
   double icapc= iCustom(Symbol(),TiempoCAPchannel,"CAPChannel","EAKV1",2.0,periodCAPchannel,true,true,Purple,Magenta,"EAKV1","EAKV1",0,false,false,false,false,"alert2.wav","email.wav",9,0);
   double icapv= iCustom(Symbol(),TiempoCAPchannel,"CAPChannel","EAKV1",2.0,periodCAPchannel,true,true,Purple,Magenta,"EAKV1","EAKV1",0,false,false,false,false,"alert2.wav","email.wav",3,0);
   double icapct2= iCustom(Symbol(),TiempoCAPchannel2,"CAPChannel","EAKV1",2.0,periodCAPchannel,true,true,Purple,Magenta,"EAKV1","EAKV1",0,false,false,false,false,"alert2.wav","email.wav",9,0);
   double icapvt2= iCustom(Symbol(),TiempoCAPchannel2,"CAPChannel","EAKV1",2.0,periodCAPchannel,true,true,Purple,Magenta,"EAKV1","EAKV1",0,false,false,false,false,"alert2.wav","email.wav",3,0);
   double icapct3= iCustom(Symbol(),TiempoCAPchannel3,"CAPChannel","EAKV1",2.0,periodCAPchannel,true,true,Purple,Magenta,"EAKV1","EAKV1",0,false,false,false,false,"alert2.wav","email.wav",9,0);
   double icapvt3= iCustom(Symbol(),TiempoCAPchannel3,"CAPChannel","EAKV1",2.0,periodCAPchannel,true,true,Purple,Magenta,"EAKV1","EAKV1",0,false,false,false,false,"alert2.wav","email.wav",3,0);

   double icapc1= iCustom(Symbol(),TiempoCAPchannel,"CAPChannel","EAKV1",2.0,periodCAPchannel2,true,true,Purple,Magenta,"EAKV1","EAKV1",0,false,false,false,false,"alert2.wav","email.wav",7,0);
   double icapv1= iCustom(Symbol(),TiempoCAPchannel,"CAPChannel","EAKV1",2.0,periodCAPchannel2,true,true,Purple,Magenta,"EAKV1","EAKV1",0,false,false,false,false,"alert2.wav","email.wav",1,0);
   int icaptend=0;
   int cerrarcap=0;
 double priceima = iMA(Symbol(),PERIOD_CURRENT,2,0,MODE_SMA,PRICE_MEDIAN,0);


   if(priceima<icapc&&priceima<icapc1&&priceima<icapct2&&priceima<icapct3){
     icaptend=1;

     ObjectSetText(Symbol()+"channel","Channel: Compra "+icapc,9,NULL,Blue);
      ObjectSet(Symbol()+"channel",OBJPROP_CORNER,0);
      ObjectSet(Symbol()+"channel",OBJPROP_XDISTANCE,15);
      ObjectSet(Symbol()+"channel",OBJPROP_YDISTANCE,300);
   }else{
     if(priceima>icapv&&priceima>icapv1&&priceima>icapvt2&&priceima>icapvt3){
     icaptend=2;
       ObjectSetText(Symbol()+"channel","Channel: Venta "+icapv,9,NULL,Red);
        ObjectSet(Symbol()+"channel",OBJPROP_CORNER,0);
        ObjectSet(Symbol()+"channel",OBJPROP_XDISTANCE,15);
        ObjectSet(Symbol()+"channel",OBJPROP_YDISTANCE,300);
     }else{
       icaptend=0;
       ObjectSetText(Symbol()+"channel","Channel: Neutro "+icapc+" - "+icapv,9,NULL,Yellow);
        ObjectSet(Symbol()+"channel",OBJPROP_CORNER,0);
        ObjectSet(Symbol()+"channel",OBJPROP_XDISTANCE,15);
        ObjectSet(Symbol()+"channel",OBJPROP_YDISTANCE,300);
     }
   }




 }

 if(turtletrend==true){
   double iturtletrendC= iCustom(Symbol(),Tiempoturtletrend,"FML/FML_Gift1_Histogram",10,10,false,false,0,0);
   double iturtletrendV= iCustom(Symbol(),Tiempoturtletrend,"FML/FML_Gift1_Histogram",10,10,false,false,1,0);
 //  double iturtletrendV= iCustom(Symbol(),Tiempoturtletrend,"TheTurtleTradingChannel",1,0);
   int turtletrendtend=0;
   if(iturtletrendC>0.1&&iturtletrendC<100000){
     turtletrendtend=1;
   }else{
     if(iturtletrendV>0.1&&iturtletrendV<100000){
       turtletrendtend=2;
     }else{
       turtletrendtend=0;
     }

   }
 }


 string tenddegrees="0";
 string tenddegrees2="0";
 int tendlr=0;
 int tendlr2=0;
 int tendlr3=0;
 if(filterdegrees==true){
   double ilrdegrees= iCustom(Symbol(),Tiempolrdegrees,"LRDegrees",0,105,15,Red,Blue,Aqua,Aqua,Aqua,Aqua,0,2,true,true,false,"alert.wav",0,0);
   string fileName = "Z"+Tiempolrdegrees+"-"+Symbol()+"EAKV1.txt";
   string fileHandle = FileOpen(fileName,FILE_CSV|FILE_READ);// | FILE_WRITE
   if(fileHandle==INVALID_HANDLE){
   printf("ERROR LECTURA 1");
   }else{
   tenddegrees = FileReadString(fileHandle);
   FileClose(fileHandle);
   }


   double ilrdegrees2= iCustom(Symbol(),Tiempolrdegrees2,"LRDegrees",0,105,15,Red,Blue,Aqua,Aqua,Aqua,Aqua,0,2,true,true,false,"alert.wav",0,0);
   string fileName2 = "Z"+Tiempolrdegrees2+"-"+Symbol()+"EAKV1.txt";
   string fileHandle2 = FileOpen(fileName2,FILE_CSV|FILE_READ);// | FILE_WRITE
   if(fileHandle2==INVALID_HANDLE){
   printf("ERROR LECTURA 2");
   }else{
   tenddegrees2 = FileReadString(fileHandle2);
   FileClose(fileHandle2);
   }



    if(tenddegrees2=="ALCDEB-COMBAJAR"){
    tendlr3=0;
    tendlr2=2;

    }
    if(tenddegrees2=="REVERSAL-ALCISTA"){
    tendlr3=1;
    tendlr2=1;

    }
    if(tenddegrees2=="BAJ-FORTALEZIDO"){
      tendlr3=2;
     tendlr2=2;
    }
    if(tenddegrees2=="BAJISTA-FUERTE"){
      tendlr3=2;
     tendlr2=2;
    }
    if(tenddegrees2=="BAJDEB-COMSUBIR"){
      tendlr3=0;
     tendlr2=1;
    }
    if(tenddegrees2=="REVERSAL-BAJISTA"){
     tendlr3=2;
     tendlr2=2;

    }
    if(tenddegrees2=="ALC-FORTALEZIDO"){
     tendlr3=1;
     tendlr2=1;

    }
    if(tenddegrees2=="ALCISTA-FUERTE"){
     tendlr3=1;
     tendlr2=1;

    }



 if(tenddegrees=="ALCDEB-COMBAJAR"&&tendlr3==2){
 tendlr=2;
 }
 if(tenddegrees=="REVERSAL-ALCISTA"&&tendlr3==1){
 tendlr=1;
 }
 if(tenddegrees=="BAJ-FORTALEZIDO"&&tendlr3==2){
  tendlr=2;
  //tendlr2=2;

 }
 if(tenddegrees=="BAJISTA-FUERTE"&&tendlr3==2){
  tendlr=2;
//  tendlr2=2;
 }
 if(tenddegrees=="BAJDEB-COMSUBIR"&&tendlr3==1){
  tendlr=1;
//  tendlr2=1;
 }
 if(tenddegrees=="REVERSAL-BAJISTA"&&tendlr3==2){
  tendlr=2;
//  tendlr2=2;

 }
 if(tenddegrees=="ALC-FORTALEZIDO"&&tendlr3==1){
  tendlr=1;
//  tendlr2=1;

 }
 if(tenddegrees=="ALCISTA-FUERTE"&&tendlr3==1){
  tendlr=1;
//  tendlr2=1;
 }







 ObjectSetText(Symbol()+"degrees","Degrees: "+tenddegrees+" - "+tendlr,9,NULL,Orange);
  ObjectSet(Symbol()+"degrees",OBJPROP_CORNER,0);
  ObjectSet(Symbol()+"degrees",OBJPROP_XDISTANCE,15);
  ObjectSet(Symbol()+"degrees",OBJPROP_YDISTANCE,360);


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
if(OrderSymbol()==Symbol()&&OrderComment()=="EAK")
{
if(OrderType()==OP_SELL){
 posicionesabiertasrobotv++;
 LastOrderlotsv=OrderLots();
 if(closeallordersv==1&&autotakeprofit2==true)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);//Aqui
 if(autotkpfcierreV==1&&autotakeprofit==true)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);//Aqui
// if(autoclosecapchannel==true&&cerrarcap==2)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
//if(autoclosedegrees==true&&closedegrees==2&&profitordersV>0)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);

}
}
if(OrderSymbol()==Symbol()&&OrderComment()=="EAK")
{
if(OrderType()==OP_BUY){
  LastOrderlotsc=OrderLots();
posicionesabiertasrobotc++;
if(closeallordersc==1&&autotakeprofit2==true)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);//Aqui
if(autotkpfcierreC==1&&autotakeprofit==true)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);//Aqui
//if(autoclosecapchannel==true&&cerrarcap==1)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);
//if(autoclosedegrees==true&&closedegrees==1&&profitordersC>0)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);

}
}
}
double pf1C = posicionesabiertasrobotc/1.5;
int tpmpC=0;
if(pf1C>profitorder1C||posicionesabiertasrobotc==1){
  tpmpC=1;
  ObjectSetText(Symbol()+"tpmpC","pf1C:"+pf1C+"profitorder1C:"+profitorder1C+"profitorder2C:"+profitorder2C+"TPMPC:"+tpmpC,9,NULL,Red);
   ObjectSet(Symbol()+"tpmpC",OBJPROP_CORNER,0);
   ObjectSet(Symbol()+"tpmpC",OBJPROP_XDISTANCE,15);
   ObjectSet(Symbol()+"tpmpC",OBJPROP_YDISTANCE,320);
}else{
  tpmpC=0;
  ObjectSetText(Symbol()+"tpmpC","pf1C:"+pf1C+"profitorder1C:"+profitorder1C+"profitorder2C:"+profitorder2C+"TPMPC:"+tpmpC,9,NULL,Red);
   ObjectSet(Symbol()+"tpmpC",OBJPROP_CORNER,0);
   ObjectSet(Symbol()+"tpmpC",OBJPROP_XDISTANCE,15);
   ObjectSet(Symbol()+"tpmpC",OBJPROP_YDISTANCE,320);
}
double pf1V = posicionesabiertasrobotv/1.5;
int tpmpV=0;
if(pf1V>profitorder1V||posicionesabiertasrobotv==1){
  tpmpV=1;
  ObjectSetText(Symbol()+"tpmpV","pf1V:"+pf1V+"profitorder1V:"+profitorder1V+"profitorder2V:"+profitorder2V+"TPMPV:"+tpmpV,9,NULL,Red);
   ObjectSet(Symbol()+"tpmpV",OBJPROP_CORNER,0);
   ObjectSet(Symbol()+"tpmpV",OBJPROP_XDISTANCE,15);
   ObjectSet(Symbol()+"tpmpV",OBJPROP_YDISTANCE,340);
}else{
  tpmpV=0;
  ObjectSetText(Symbol()+"tpmpV","pf1V:"+pf1V+"profitorder1V:"+profitorder1V+"profitorder2V:"+profitorder2V+"TPMPV:"+tpmpV,9,NULL,Red);
   ObjectSet(Symbol()+"tpmpV",OBJPROP_CORNER,0);
   ObjectSet(Symbol()+"tpmpV",OBJPROP_XDISTANCE,15);
   ObjectSet(Symbol()+"tpmpV",OBJPROP_YDISTANCE,340);
}

if(autoclosecapchannel==true&&CAPChannelfilter==true){
  if(icapc1<priceima&&tpmpC==1&&profitordersC>0){
    cerrarcap=1;
  }else{
    if(icapv1>priceima&&tpmpV==1&&profitordersV>0){
    cerrarcap=2;
  }else{
    cerrarcap=0;
  }
  }
}
if(autoclosedegrees==true){
  int closedegrees=0;
  if(tendlr2==1&&profitordersV>0&&DiffPipsv1>1){
 closedegrees=2;
}else{
 if(tendlr2==2&&profitordersC>0&&DiffPipsc1>1){
closedegrees=1;
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





            if(CAPChannelfilter==true&&icaptend==2){
              if(turtletrend==true&&turtletrendtend==2){
                if(filterdegrees==true&&tendlr==2){
                  if(filtercronextaichi==true&&taichitend==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                  }
                  if(filtercronextaichi==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                  }
                }
                if(filterdegrees==false){
                  if(filtercronextaichi==true&&taichitend==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                  }
                  if(filtercronextaichi==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                  }
                }
              }
              if(turtletrend==false){
                if(filterdegrees==true&&tendlr==2){
                  if(filtercronextaichi==true&&taichitend==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                  }
                  if(filtercronextaichi==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                  }
                }
                if(filterdegrees==false){
                  if(filtercronextaichi==true&&taichitend==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                  }
                  if(filtercronextaichi==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                  }
                }
              }
            }
            if(CAPChannelfilter==false){
              if(turtletrend==true&&turtletrendtend==2){
                if(filterdegrees==true&&tendlr==2){
                  if(filtercronextaichi==true&&taichitend==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                  }
                  if(filtercronextaichi==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                  }
                }
                if(filterdegrees==false){
                  if(filtercronextaichi==true&&taichitend==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                  }
                  if(filtercronextaichi==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                  }
                }
              }
              if(turtletrend==false){
                if(filterdegrees==true&&tendlr==2){
                  if(filtercronextaichi==true&&taichitend==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                  }
                  if(filtercronextaichi==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                  }
                }
                if(filterdegrees==false){
                  if(filtercronextaichi==true&&taichitend==2){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                  }
                  if(filtercronextaichi==false){
                    OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                  }
                }
              }
            }




      }

      //------------Fin venta sola
    //------------INICIO COMPRA sola

    if(posicionesabiertasrobotc==0){



      if(CAPChannelfilter==true&&icaptend==1){
        if(turtletrend==true&&turtletrendtend==1){
          if(filterdegrees==true&&tendlr==1){
            if(filtercronextaichi==true&&taichitend==1){
              OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
            }
            if(filtercronextaichi==false){
              OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
            }
          }
          if(filterdegrees==false){
            if(filtercronextaichi==true&&taichitend==1){
              OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
            }
            if(filtercronextaichi==false){
              OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
            }
          }
        }
        if(turtletrend==false){
          if(filterdegrees==true&&tendlr==1){
            if(filtercronextaichi==true&&taichitend==1){
              OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
            }
            if(filtercronextaichi==false){
              OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
            }
          }
          if(filterdegrees==false){
            if(filtercronextaichi==true&&taichitend==1){
              OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
            }
            if(filtercronextaichi==false){
              OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
            }
          }
        }
      }
      if(CAPChannelfilter==false){
        if(turtletrend==true&&turtletrendtend==1){
          if(filterdegrees==true&&tendlr==1){
            if(filtercronextaichi==true&&taichitend==1){
              OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
            }
            if(filtercronextaichi==false){
              OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
            }
          }
          if(filterdegrees==false){
            if(filtercronextaichi==true&&taichitend==1){
              OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
            }
            if(filtercronextaichi==false){
              OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
            }
            }
        }
        if(turtletrend==false){
          if(filterdegrees==true&&tendlr==1){
            if(filtercronextaichi==true&&taichitend==1){
              OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
            }
            if(filtercronextaichi==false){
              OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
            }
            }
          if(filterdegrees==false){
            if(filtercronextaichi==true&&taichitend==1){
              OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
            }
            if(filtercronextaichi==false){
              OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
            }
            }
        }
      }



       }
    //-------------FIN COMPRA SOLA
    //----------------INICIO VENTA GRUPAL
    if(posicionesabiertasrobotv>0&&filter1v==1&&posicionesabiertasrobotv<maxposition){







                  if(CAPChannelfilter==true&&icaptend==2){
                    if(turtletrend==true&&turtletrendtend==2){
                      if(filterdegrees==true&&tendlr==2){
                        if(filtercronextaichi==true&&taichitend==2){
                          OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                        }
                        if(filtercronextaichi==false){
                          OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                        }
                      }
                      if(filterdegrees==false){
                        if(filtercronextaichi==true&&taichitend==2){
                          OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                        }
                        if(filtercronextaichi==false){
                          OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                        }
                      }
                    }
                    if(turtletrend==false){
                      if(filterdegrees==true&&tendlr==2){
                        if(filtercronextaichi==true&&taichitend==2){
                          OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                        }
                        if(filtercronextaichi==false){
                          OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                        }
                      }
                      if(filterdegrees==false){
                        if(filtercronextaichi==true&&taichitend==2){
                          OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                        }
                        if(filtercronextaichi==false){
                          OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                        }
                      }
                    }
                  }
                  if(CAPChannelfilter==false){
                    if(turtletrend==true&&turtletrendtend==2){
                      if(filterdegrees==true&&tendlr==2){
                        if(filtercronextaichi==true&&taichitend==2){
                          OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                        }
                        if(filtercronextaichi==false){
                          OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                        }
                      }
                      if(filterdegrees==false){
                        if(filtercronextaichi==true&&taichitend==2){
                          OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                        }
                        if(filtercronextaichi==false){
                          OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                        }
                      }
                    }
                    if(turtletrend==false){
                      if(filterdegrees==true&&tendlr==2){
                        if(filtercronextaichi==true&&taichitend==2){
                          OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                        }
                        if(filtercronextaichi==false){
                          OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                        }
                      }
                      if(filterdegrees==false){
                        if(filtercronextaichi==true&&taichitend==2){
                          OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                        }
                        if(filtercronextaichi==false){
                          OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,"EAK",MagicNumber,0,Red);
                        }
                      }
                    }
                  }





    }

    //----------------FIN VENTA GRUPAL
    //----------------INICIO COMPRA GRUPAL
    if(posicionesabiertasrobotc>0&&filter1c==1&&posicionesabiertasrobotc<maxposition){





            if(CAPChannelfilter==true&&icaptend==1){
              if(turtletrend==true&&turtletrendtend==1){
                if(filterdegrees==true&&tendlr==1){
                  if(filtercronextaichi==true&&taichitend==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
                  }
                  if(filtercronextaichi==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
                  }
                }
                if(filterdegrees==false){
                  if(filtercronextaichi==true&&taichitend==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
                  }
                  if(filtercronextaichi==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
                  }
                }
              }
              if(turtletrend==false){
                if(filterdegrees==true&&tendlr==1){
                  if(filtercronextaichi==true&&taichitend==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
                  }
                  if(filtercronextaichi==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
                  }
                }
                if(filterdegrees==false){
                  if(filtercronextaichi==true&&taichitend==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
                  }
                  if(filtercronextaichi==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
                  }
                }
              }
            }
            if(CAPChannelfilter==false){
              if(turtletrend==true&&turtletrendtend==1){
                if(filterdegrees==true&&tendlr==1){
                  if(filtercronextaichi==true&&taichitend==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
                  }
                  if(filtercronextaichi==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
                  }
                }
                if(filterdegrees==false){
                  if(filtercronextaichi==true&&taichitend==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
                  }
                  if(filtercronextaichi==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
                  }
                  }
              }
              if(turtletrend==false){
                if(filterdegrees==true&&tendlr==1){
                  if(filtercronextaichi==true&&taichitend==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
                  }
                  if(filtercronextaichi==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
                  }
                  }
                if(filterdegrees==false){
                  if(filtercronextaichi==true&&taichitend==1){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
                  }
                  if(filtercronextaichi==false){
                    OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,"EAK",MagicNumber,0,Blue);
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
if(OrderSymbol()==Symbol()&&OrderComment()=="EAK")
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
  if(autoclosecapchannel==true&&cerrarcap==2)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
  if(autoclosedegrees==true&&closedegrees==2)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);

}
}
if(OrderSymbol()==Symbol()&&OrderComment()=="EAK")
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
  if(autoclosecapchannel==true&&cerrarcap==1)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);
  if(autoclosedegrees==true&&closedegrees==1)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);

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
