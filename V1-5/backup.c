//+------------------------Kenneth Suarez-------------------------------+
//                   Expert Advisor MUFASA V1.5- 2014-2018
//
//Estrategia martingale, con un filtro a los 150 pips, con un multiplicador
//alto para recuperar las perdidas, las resistencias seran las mas bajas posibles.
// basado en el mercado.
//+---------------------------------------------------------------------+
enum IndList
  {
   IndList1 = 1, //Momentum
   IndList2 = 2, //ATR (Average True Range)
   IndList3 = 3, //CCI (Commodity Channel Index)
   IndList4 = 4  //RSI (Relative Strength Index)
  };
extern double lotesinicial=0.1; //first lot
extern int pipsmodify=40; //pips to reach in position modify.
extern bool globalordersprofit=TRUE;
extern double multiplicador=3; //Martingale factor to recover bad choices
extern double gridposition=80; //pips on every new trade
extern bool filtergridpositionalotoforders=TRUE;
extern double gridpositionalotoforders1=100;
extern double gridpositionalotoforders2=80;
extern double gridpositionalotoforders3=60;
extern double gridpositionalotoforders4=40;
extern double gridpositionalotoforders5=20;
extern double gridpositionalotoforderstp1=600;
extern double gridpositionalotoforderstp2=500;
extern double gridpositionalotoforderstp3=400;
extern double gridpositionalotoforderstp4=350;
extern double gridpositionalotoforderstp5=300;
extern int gridpositionminorders=2;
extern double takeprofitpips=40; //Min pips to take profit
extern int maxposition=20;//Max positions
extern bool autotakeprofit=TRUE;//V1, resistance fixed by pips (False and takeprofit value) or dinamic (True),
extern int sensorautotkpf=5;//Min pips to get resistance (10 is ok)
extern bool autotakeprofit2=TRUE;//V1, Look for the profit of open orders and minimumpips allowed to close
extern int minpositionallowedtoclosepips=5;
extern int minimumpipsallowedauto=35;
extern bool filtermatrend=TRUE;
extern int periodmarojo=600;
extern int periodmaamarillo=300;
extern int periodmarverde=100;
extern int timematrend=15;
extern bool Resistanceopenfilter=TRUE;
extern double Resistancepipsminimo=30;//Cuanto mas pequeño mas se adiere a la resistencia
extern int Tiemporesistencias=240;//Cuanto mas alto el valor mas seguro
extern bool filtermirror=FALSE; //Mirror filter not very good
extern int periodmirror=300; //Best period 300
extern int timemirror=15; //Best time 15
extern bool filterbollingerbands=TRUE; //Bollinger usefull for Identify high and low
extern int periodobandas=100; //Best period
extern int tiempobandas=5; //Best time
extern bool filterHisto=TRUE;//Filter Momentum|ATR|CCI|RSI. UNDERCONSTRUCTION
extern int tiempohisto=15;//Bes time 15
extern IndList histoindicator= 1;//Indicator Name
extern int histoperiod = 150;//Indicator Period
extern ENUM_APPLIED_PRICE histoapliedprice=PRICE_CLOSE;//Applied Price for Momentum, CCI or RSI
extern bool filtermahisto=FALSE;//FILTER MA FROM HISTO
extern int tiempomahisto=1;
extern int maperiodhisto=70;
extern double momentumresistancetop=100.3;
extern double momentumresistancebot=99.7;
extern bool filteritrend=FALSE;
extern int tiempoitrend=1;
extern int itrendperiod=150;
extern int itrendpower=100;
extern bool filterFish=TRUE;
extern bool closeorderfisher=TRUE;
extern double minimumpipstocloseFISHER=70;
extern int tiempofish=5;
extern int periodfish=50;
extern int apliedpricefish=0;
extern bool modefastfish=FALSE;
extern bool signalsfish=FALSE;
extern int fishmaperiod1=9;
extern int fishmaperiod2=45;
extern int typema1fish=0;
extern int typema2fish=3;
extern int TrailingStop=0;
extern int MagicNumber=10001;
extern int Slippage=5;

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
 ObjectSetText(Symbol()+"minlot","Minimum lots allowed: "+minlots,7,NULL,Orange);
  ObjectSet(Symbol()+"minlot",OBJPROP_CORNER,0);
  ObjectSet(Symbol()+"minlot",OBJPROP_XDISTANCE,50);
  ObjectSet(Symbol()+"minlot",OBJPROP_YDISTANCE,15);





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



     string fileNamec =  "Margin Required for "+OrderSymbol()+".txt";

     string fileHandlecierre41 = FileOpen(fileNamec,FILE_CSV|FILE_READ);// | FILE_WRITE
     if(fileHandlecierre41==INVALID_HANDLE){
     printf("Handle Invalido, apertura error 21 - Error al leer cierre cuando hay mas de una operacion en el mercado actual");
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
     //FILTRO 5: MA trend
     //------------------------------------------------------------------

         if(filtermatrend==TRUE){
           int matend=0;
           double marojo1 = iMA(Symbol(),timematrend,periodmarojo,0,0,PRICE_MEDIAN,0);
           double maamarillo1 = iMA(Symbol(),timematrend,periodmaamarillo,0,0,PRICE_MEDIAN,0);
           double maverde1 = iMA(Symbol(),timematrend,periodmarverde,0,0,PRICE_MEDIAN,0);
           if(marojo1>maamarillo1&&maamarillo1>maverde1){
             matend=2;
             ObjectSetText(Symbol()+"matrend","F MATREND: VENTA",7,NULL,Red);
               ObjectSet(Symbol()+"matrend",OBJPROP_CORNER,0);
               ObjectSet(Symbol()+"matrend",OBJPROP_XDISTANCE,15);
               ObjectSet(Symbol()+"matrend",OBJPROP_YDISTANCE,220);
           }else{
             if(maverde1>maamarillo1&&maamarillo1>marojo1){
               matend=1;
               ObjectSetText(Symbol()+"matrend","F MATREND: COMPRA",7,NULL,Blue);
                 ObjectSet(Symbol()+"matrend",OBJPROP_CORNER,0);
                 ObjectSet(Symbol()+"matrend",OBJPROP_XDISTANCE,15);
                 ObjectSet(Symbol()+"matrend",OBJPROP_YDISTANCE,220);
             }else{
               matend=0;
               ObjectSetText(Symbol()+"matrend","F MATREND: NEUTRO",7,NULL,Orange);
                 ObjectSet(Symbol()+"matrend",OBJPROP_CORNER,0);
                 ObjectSet(Symbol()+"matrend",OBJPROP_XDISTANCE,15);
                 ObjectSet(Symbol()+"matrend",OBJPROP_YDISTANCE,220);
             }
           }
         }

  //------------------------------------------------------------------
  //Global OrdersProfit for bad orders
  //------------------------------------------------------------------
  double profitordersC = 0;
  double profitordersV = 0;

  if(globalordersprofit==TRUE){
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

    if(globalordersprofit==TRUE){
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
  if(globalordersprofit==FALSE){
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
if(DiffPipsv>takeprofitpips&&autotakeprofit2==TRUE&&profitordersV>0){
  closeallordersv=1;
}
}
if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()&&OrderComment()=="MUFASA"){
  lastorderpB1=OrderProfit();
  double DiffPipsc = MathAbs((NormalizeDouble(((OrderOpenPrice()-Ask)/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);
if(DiffPipsc>takeprofitpips&&autotakeprofit2==TRUE&&profitordersC>0){
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
if(autotakeprofit==TRUE||Resistanceopenfilter==TRUE){
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


    if(Resistanceopenfilter==TRUE){
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
if(autotakeprofit==TRUE){
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


if(filterFish==TRUE){

string  closefishertend="CLOSENULL";
int tendfisher=0;
  double fishbuf1white = iCustom(Symbol(),tiempofish,"fisher",periodfish,apliedpricefish,modefastfish,signalsfish,fishmaperiod1,fishmaperiod2,"1","1",typema1fish,typema2fish,2,0);
  double fishbuf2green = iCustom(Symbol(),tiempofish,"fisher",periodfish,apliedpricefish,modefastfish,signalsfish,fishmaperiod1,fishmaperiod2,"1","1",typema1fish,typema2fish,3,0);
  double fishbuf3red = iCustom(Symbol(),tiempofish,"fisher",periodfish,apliedpricefish,modefastfish,signalsfish,fishmaperiod1,fishmaperiod2,"1","1",typema1fish,typema2fish,4,0);

if(fishbuf1white<-1&&fishbuf1white>fishbuf2green&&fishbuf2green>fishbuf3red){
  tendfisher=1;
  ObjectSetText(Symbol()+"ffish","F Fisher: COMPRA",7,NULL,Blue);
    ObjectSet(Symbol()+"ffish",OBJPROP_CORNER,0);
    ObjectSet(Symbol()+"ffish",OBJPROP_XDISTANCE,15);
    ObjectSet(Symbol()+"ffish",OBJPROP_YDISTANCE,160);
}else{
  if(fishbuf1white>1&&fishbuf3red>fishbuf2green&&fishbuf2green>fishbuf1white){
    tendfisher=2;
    ObjectSetText(Symbol()+"ffish","F Fisher: VENTA",7,NULL,Red);
      ObjectSet(Symbol()+"ffish",OBJPROP_CORNER,0);
      ObjectSet(Symbol()+"ffish",OBJPROP_XDISTANCE,15);
      ObjectSet(Symbol()+"ffish",OBJPROP_YDISTANCE,160);
  }else{
    tendfisher=0;
    ObjectSetText(Symbol()+"ffish","F Fisher: NEUTRO [white: "+fishbuf1white+"][B: "+fishbuf2green+"][S: "+fishbuf3red+"]",7,NULL,Orange);
      ObjectSet(Symbol()+"ffish",OBJPROP_CORNER,0);
      ObjectSet(Symbol()+"ffish",OBJPROP_XDISTANCE,15);
      ObjectSet(Symbol()+"ffish",OBJPROP_YDISTANCE,160);
  }
}

if(closeorderfisher==TRUE){

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
 if(closeallordersv==1&&autotakeprofit2==TRUE)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);//Aqui
 if(autotkpfcierreV==1&&autotakeprofit==TRUE)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);//Aqui
 if(closefishertend=="CLOSESELL"&&closeorderfisher==TRUE)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);//Aqui


}
}
if(OrderSymbol()==Symbol()&&OrderComment()=="MUFASA")
{
if(OrderType()==OP_BUY){
  LastOrderlotsc=OrderLots();
posicionesabiertasrobotc++;
if(closeallordersc==1&&autotakeprofit2==TRUE)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);//Aqui
if(autotkpfcierreC==1&&autotakeprofit==TRUE)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);//Aqui
if(closefishertend=="CLOSEBUY"&&closeorderfisher==TRUE)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);//Aqui

}
}
}



//------------------------------------------------------------------
//GRID 2 POSITIONALOTOFORDERS - POSITION A LOT OF ORDERS
//------------------------------------------------------------------




if(filtergridpositionalotoforders==TRUE){
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

if(filtergridpositionalotoforders==FALSE){
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

if(filtermirror==TRUE){
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

if(filterbollingerbands==TRUE){
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
if(filterHisto==TRUE){
  int tendhisto=0;
  int tendhistoma=0;
  if(histoindicator==1){
    double momentum = iMomentum(Symbol(),tiempohisto,histoperiod,histoapliedprice,0);
  }

  if(filteritrend==TRUE){
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


    if(filtermahisto==TRUE){
      double mahisto = iMA(Symbol(),tiempomahisto,maperiodhisto,0,0,histoapliedprice,0);

      if(Bid>mahisto){
        tendhistoma=2;
      }
      if(Ask<mahisto){
        tendhistoma=1;
      }



      if(histoindicator==1){

      if(momentum<momentumresistancetop&&tendhistoma==1){
        if(filteritrend==TRUE&&itrendtend==1){
          tendhisto=1;
          ObjectSetText(Symbol()+"fhisto","F Histo: COMPRA",7,NULL,Blue);
            ObjectSet(Symbol()+"fhisto",OBJPROP_CORNER,0);
            ObjectSet(Symbol()+"fhisto",OBJPROP_XDISTANCE,15);
            ObjectSet(Symbol()+"fhisto",OBJPROP_YDISTANCE,140);
        }
        if(filteritrend==FALSE){
          tendhisto=1;
          ObjectSetText(Symbol()+"fhisto","F Histo: COMPRA",7,NULL,Blue);
            ObjectSet(Symbol()+"fhisto",OBJPROP_CORNER,0);
            ObjectSet(Symbol()+"fhisto",OBJPROP_XDISTANCE,15);
            ObjectSet(Symbol()+"fhisto",OBJPROP_YDISTANCE,140);
        }

      }else{
        if(momentum>momentumresistancebot&&tendhistoma==2){
          if(filteritrend==TRUE&&itrendtend==2){
            tendhisto=2;
            ObjectSetText(Symbol()+"fhisto","F Histo: VENTA",7,NULL,Red);
              ObjectSet(Symbol()+"fhisto",OBJPROP_CORNER,0);
              ObjectSet(Symbol()+"fhisto",OBJPROP_XDISTANCE,15);
              ObjectSet(Symbol()+"fhisto",OBJPROP_YDISTANCE,140);
          }
          if(filteritrend==FALSE){
            tendhisto=2;
            ObjectSetText(Symbol()+"fhisto","F Histo: VENTA",7,NULL,Red);
              ObjectSet(Symbol()+"fhisto",OBJPROP_CORNER,0);
              ObjectSet(Symbol()+"fhisto",OBJPROP_XDISTANCE,15);
              ObjectSet(Symbol()+"fhisto",OBJPROP_YDISTANCE,140);
          }

        }else{
          tendhisto=0;
          ObjectSetText(Symbol()+"fhisto","F Histo: Neutral",7,NULL,Orange);
            ObjectSet(Symbol()+"fhisto",OBJPROP_CORNER,0);
            ObjectSet(Symbol()+"fhisto",OBJPROP_XDISTANCE,15);
            ObjectSet(Symbol()+"fhisto",OBJPROP_YDISTANCE,140);
        }

      }

      }




    }



  if(filtermahisto==FALSE){
    if(histoindicator==1){
    if(momentum>100){
      tendhisto=1;
      ObjectSetText(Symbol()+"fhisto","F Histo: COMPRA",7,NULL,Blue);
        ObjectSet(Symbol()+"fhisto",OBJPROP_CORNER,0);
        ObjectSet(Symbol()+"fhisto",OBJPROP_XDISTANCE,15);
        ObjectSet(Symbol()+"fhisto",OBJPROP_YDISTANCE,140);
    }else{
      tendhisto=2;
      ObjectSetText(Symbol()+"fhisto","F Histo: VENTA",7,NULL,Red);
        ObjectSet(Symbol()+"fhisto",OBJPROP_CORNER,0);
        ObjectSet(Symbol()+"fhisto",OBJPROP_XDISTANCE,15);
        ObjectSet(Symbol()+"fhisto",OBJPROP_YDISTANCE,140);
    }
    }
  }





  }





   if(next_candle<=Time[0])
      {
         next_candle=Time[0]+Period();
         // New candle. Your trading functions here


          double MyPoint=Point;
   //if(Digits==3 || Digits==5) MyPoint=Point*10;


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
    lotesposicionc=NormalizeDouble(lotesinicial,MODE_DIGITS);
  }else{
    lotesposicionc=NormalizeDouble((LastOrderlotsc*multiplicador),MODE_DIGITS);
  }
  if(posicionesabiertasrobotv==0){
    lotesposicionv=NormalizeDouble(lotesinicial,MODE_DIGITS);
  }else{
    lotesposicionv=NormalizeDouble((LastOrderlotsv*multiplicador),MODE_DIGITS);//+posicionesabiertasrobotv);
  }
}
if(gestionlotesmethod==2){
  if(posicionesabiertasrobotc==0){
    lotesposicionc=NormalizeDouble(lotesinicial,MODE_DIGITS);
  }else{
    lotesposicionc=NormalizeDouble((LastOrderlotsc*multiplicador)/posicionesabiertasrobotc,MODE_DIGITS);
  }
  if(posicionesabiertasrobotv==0){
    lotesposicionv=NormalizeDouble(lotesinicial,MODE_DIGITS);
  }else{
    lotesposicionv=NormalizeDouble((LastOrderlotsv*multiplicador)/posicionesabiertasrobotv,MODE_DIGITS);//+posicionesabiertasrobotv);
  }
}




//------------------------------------------------------------------
// ENVIO OPERACIONES
//------------------------------------------------------------------
//------------INICIO VENTA sola
if(posicionesabiertasrobotv==0){




    if(filtermatrend==TRUE&&matend==2){
      if(filterHisto==TRUE&&tendhisto==2){
        if(filterFish==TRUE&&tendfisher==2){
          if(Resistanceopenfilter==TRUE&&Filterresistance==2){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
        }
        if(filterFish==FALSE){
          if(Resistanceopenfilter==TRUE&&Filterresistance==2){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
        }
      }
      if(filterHisto==FALSE){
        if(filterFish==TRUE&&tendfisher==2){
          if(Resistanceopenfilter==TRUE&&Filterresistance==2){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
        }
        if(filterFish==FALSE){
          if(Resistanceopenfilter==TRUE&&Filterresistance==2){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
        }
      }
    }
    if(filtermatrend==FALSE){
      if(filterHisto==TRUE&&tendhisto==2){
        if(filterFish==TRUE&&tendfisher==2){
          if(Resistanceopenfilter==TRUE&&Filterresistance==2){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
        }
        if(filterFish==FALSE){
          if(Resistanceopenfilter==TRUE&&Filterresistance==2){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
        }
      }
      if(filterHisto==FALSE){
        if(filterFish==TRUE&&tendfisher==2){
          if(Resistanceopenfilter==TRUE&&Filterresistance==2){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
        }
        if(filterFish==FALSE){
          if(Resistanceopenfilter==TRUE&&Filterresistance==2){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
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



    if(filtermatrend==TRUE&&matend==1){
      if(filterHisto==TRUE&&tendhisto==1){
        if(filterFish==TRUE&&tendfisher==1){
          if(Resistanceopenfilter==TRUE&&Filterresistance==1){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
        }
        if(filterFish==FALSE){
          if(Resistanceopenfilter==TRUE&&Filterresistance==1){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
        }
      }
      if(filterHisto==FALSE){
        if(filterFish==TRUE&&tendfisher==1){
          if(Resistanceopenfilter==TRUE&&Filterresistance==1){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
        }
        if(filterFish==FALSE){
          if(Resistanceopenfilter==TRUE&&Filterresistance==1){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
        }
      }
    }
    if(filtermatrend==FALSE){
      if(filterHisto==TRUE&&tendhisto==1){
        if(filterFish==TRUE&&tendfisher==1){
          if(Resistanceopenfilter==TRUE&&Filterresistance==1){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
        }
        if(filterFish==FALSE){
          if(Resistanceopenfilter==TRUE&&Filterresistance==1){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
        }
      }
      if(filterHisto==FALSE){
        if(filterFish==TRUE&&tendfisher==1){
          if(Resistanceopenfilter==TRUE&&Filterresistance==1){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
        }
        if(filterFish==FALSE){
          if(Resistanceopenfilter==TRUE&&Filterresistance==1){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
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



    if(filtermatrend==TRUE&&matend==2){
      if(filterHisto==TRUE&&tendhisto==2){
        if(filterFish==TRUE&&tendfisher==2){
          if(Resistanceopenfilter==TRUE&&Filterresistance==2){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
        }
        if(filterFish==FALSE){
          if(Resistanceopenfilter==TRUE&&Filterresistance==2){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
        }
      }
      if(filterHisto==FALSE){
        if(filterFish==TRUE&&tendfisher==2){
          if(Resistanceopenfilter==TRUE&&Filterresistance==2){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
        }
        if(filterFish==FALSE){
          if(Resistanceopenfilter==TRUE&&Filterresistance==2){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
        }
      }
    }
    if(filtermatrend==FALSE){
      if(filterHisto==TRUE&&tendhisto==2){
        if(filterFish==TRUE&&tendfisher==2){
          if(Resistanceopenfilter==TRUE&&Filterresistance==2){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
        }
        if(filterFish==FALSE){
          if(Resistanceopenfilter==TRUE&&Filterresistance==2){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
        }
      }
      if(filterHisto==FALSE){
        if(filterFish==TRUE&&tendfisher==2){
          if(Resistanceopenfilter==TRUE&&Filterresistance==2){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
        }
        if(filterFish==FALSE){
          if(Resistanceopenfilter==TRUE&&Filterresistance==2){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==2){
            if(filterbollingerbands==TRUE&&tendbollinger==2){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==2){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_SELL,lotesposicionv,Bid,Slippage,0,0,"MUFASA",MagicNumber,0,Red);
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




    if(filtermatrend==TRUE&&matend==1){
      if(filterHisto==TRUE&&tendhisto==1){
        if(filterFish==TRUE&&tendfisher==1){
          if(Resistanceopenfilter==TRUE&&Filterresistance==1){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
        }
        if(filterFish==FALSE){
          if(Resistanceopenfilter==TRUE&&Filterresistance==1){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
        }
      }
      if(filterHisto==FALSE){
        if(filterFish==TRUE&&tendfisher==1){
          if(Resistanceopenfilter==TRUE&&Filterresistance==1){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
        }
        if(filterFish==FALSE){
          if(Resistanceopenfilter==TRUE&&Filterresistance==1){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
        }
      }
    }
    if(filtermatrend==FALSE){
      if(filterHisto==TRUE&&tendhisto==1){
        if(filterFish==TRUE&&tendfisher==1){
          if(Resistanceopenfilter==TRUE&&Filterresistance==1){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
        }
        if(filterFish==FALSE){
          if(Resistanceopenfilter==TRUE&&Filterresistance==1){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
        }
      }
      if(filterHisto==FALSE){
        if(filterFish==TRUE&&tendfisher==1){
          if(Resistanceopenfilter==TRUE&&Filterresistance==1){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
        }
        if(filterFish==FALSE){
          if(Resistanceopenfilter==TRUE&&Filterresistance==1){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
            }
          }
          if(Resistanceopenfilter==FALSE){
            if(filtermirror==TRUE&&tendmirror==1){
            if(filterbollingerbands==TRUE&&tendbollinger==1){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            if(filterbollingerbands==FALSE){
              OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
            }
            }
            if(filtermirror==FALSE){
              if(filterbollingerbands==TRUE&&tendbollinger==1){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
              }
              if(filterbollingerbands==FALSE){
                OrderSend(Symbol(),OP_BUY,lotesposicionc,Ask,Slippage,0,0,"MUFASA",MagicNumber,0,Blue);
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
if(filtergridpositionalotoforders==TRUE){
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


if(filtergridpositionalotoforders==FALSE){
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
  if(OrderTakeProfit()!=takeprofitmodifyS){
    OrderModify(OrderTicket(),OrderOpenPrice(),0,takeprofitmodifyS,0,Red);
  }
}


 //ORDER MODIFY
  if(closeallordersv==1&&autotakeprofit2==TRUE)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);//Aqui
  if(autotkpfcierreV==1&&autotakeprofit==TRUE)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);//Aqui
if(closefishertend=="CLOSESELL"&&closeorderfisher==TRUE)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);//Aqui
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
  if(closeallordersc==1&&autotakeprofit2==TRUE)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);//Aqui
  if(autotkpfcierreC==1&&autotakeprofit==TRUE)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);//Aqui
  if(closefishertend=="CLOSEBUY"&&closeorderfisher==TRUE)OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);//Aqui
}
}
}




}//FIN TOTAL ORDERS 0 199






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
