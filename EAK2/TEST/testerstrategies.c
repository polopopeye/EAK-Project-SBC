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

   next_candle=Time[0]+30;
//ObjectCreate(Symbol()+1,OBJ_LABEL,0,0,0,0); // Tendencia Bands



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
double gridposition=5; //pips on every new trade


if(Digits==3||Digits==5)point_compat=10;
//+------------------------------------------------------------------+
//    INTERFACE
//+------------------------------------------------------------------+
 double minlots = MarketInfo(Symbol(),MODE_MINLOT);

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






//+------------------------------------------------------------------+
//    GRID
//+------------------------------------------------------------------+


if(Digits==3||Digits==5)point_compat=10;


 int filter1c=3,filter1v=3;
int posicionSB=0;
 int filterCtrue=0,filterVtrue=0;
 double GridpipsC=10000,GridpipsV=10000,pfSGBC,pfSGBV;
int cntfilter=0;
 while(cntfilter<=OrdersTotal()){
 if(OrderSelect(cntfilter,SELECT_BY_POS,MODE_TRADES)){
 if(OrderSymbol()==Symbol()&&OrderComment()==commentID){
 if(OrderType()==OP_BUY){
   pfSGBC=OrderProfit()+pfSGBC;
   posicionSB++;
 GridpipsC = MathAbs((NormalizeDouble(((OrderOpenPrice()-Bid)/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);
 if(GridpipsC<gridposition)filterCtrue=filterCtrue+1;
 }
 if(OrderType()==OP_SELL){
   pfSGBV=OrderProfit()+pfSGBV;

   posicionSB++;
 GridpipsV = MathAbs((NormalizeDouble(((Ask-OrderOpenPrice())/MarketInfo(Symbol(),MODE_POINT)),MarketInfo(Symbol(),MODE_DIGITS)))/point_compat);
 if(GridpipsV<gridposition)filterVtrue=filterVtrue+1;
 }
 }
 }
 cntfilter=cntfilter+1;

 }

if(posicionSB!=0){
if(filterCtrue>0){ //&&lastorderpS1<0
filter1c=0;
}
if(filterCtrue==0){
if(pfSGBC<0)filter1c=1;
}
if(filterVtrue>0){ //&&lastorderpS1<0
filter1v=0;
}
if(filterVtrue==0){
if(pfSGBV<0)filter1v=1;
}
}
if(posicionSB<1){
 filter1c=1;
 filter1v=1;
}

int permitirC=filter1c,permitirV=filter1v;

//Variables sin definir
int op=0;
int cierreop=0;
string StrategyName="NONE";

double MyPoint=Point;

{



 double op5=iCustom(Symbol(),0,"EAKBINOPT",1,0);
 double cop5=iCustom(Symbol(),0,"EAKBINOPT",2,0);
 if(op5!=EMPTY_VALUE&&op5!=0){
       commentID="S1";
       op=op5;
       StrategyName="S1";

 }

 if(cop5!=EMPTY_VALUE&&cop5!=0){
       commentID="S1";
       cierreop=cop5;
       StrategyName="S1";

     }



if(cierreop!=0){
  for(int cnt991=0;cnt991<OrdersTotal();cnt991++){
  OrderSelect(cnt991,SELECT_BY_POS,MODE_TRADES);
  if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()&&OrderComment()==commentID&&cierreop==1){
    OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Blue);
  }
  if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()&&OrderComment()==commentID&&cierreop==2){
    OrderClose(OrderTicket(),OrderLots(),OrderClosePrice(),Slippage,Red);
  }
}
}


//----------------------------------------------------------------
// GESTION LOTE
//------------------------------------------------------------------

double lotesposicionc=NormalizeDouble(lotesinicial,2);
double lotesposicionv=NormalizeDouble(lotesinicial,2);


   //------------------------------------------------------------------
   // APERTURA
   //------------------------------------------------------------------

double precio=SymbolInfoDouble(Symbol(),SYMBOL_BID);
color clrR=clrRed;
color clrB=clrBlue;
int actualordersend=0;
 if(op==1&&permitirC==1&&commentID!="error"){

OrderSend(Symbol(),0,lotesposicionc,Ask,Slippage,0,0,commentID,MagicNumber,0,Blue);
ObjectCreate(ChartID(),Time[0]+commentID,OBJ_TEXT,0,TimeCurrent(),precio);
ObjectSetString(ChartID(),Time[0]+commentID,OBJPROP_TEXT,StrategyName);
ObjectSetString(ChartID(),Time[0]+commentID,OBJPROP_FONT,"Arial");
ObjectSetInteger(ChartID(),Time[0]+commentID,OBJPROP_FONTSIZE,"12");
ObjectSetInteger(ChartID(),Time[0]+commentID,OBJPROP_COLOR,clrB);
//printf("BUY:"+Ask+" _comment:"+commentID+" _Time:"+TimeCurrent());

 }

 if(op==2&&permitirV==1&&commentID!="error"){

 OrderSend(Symbol(),1,lotesposicionv,Bid,Slippage,0,0,commentID,MagicNumber,0,Red);
 ObjectCreate(ChartID(),Time[0]+commentID,OBJ_TEXT,0,TimeCurrent(),precio);
 ObjectSetString(ChartID(),Time[0]+commentID,OBJPROP_TEXT,StrategyName);
 ObjectSetString(ChartID(),Time[0]+commentID,OBJPROP_FONT,"Arial");
 ObjectSetInteger(ChartID(),Time[0]+commentID,OBJPROP_FONTSIZE,"12");
 ObjectSetInteger(ChartID(),Time[0]+commentID,OBJPROP_COLOR,clrR);

 }




//aqui va el codigo
int result=0;




}//FIN TOTAL ORDERS 0 199


   if(next_candle<=Time[0])
      {
         next_candle=Time[0]+Period();
         // New candle. Your trading functions here


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
