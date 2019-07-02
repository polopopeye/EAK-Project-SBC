//+------------------------------------------------------------------+
//|                                       EAKextrapolatoravramis.mq4 |
//|                              Kenneth Suarez, EAK, 2018, v.0.1.01 |
//|                                             https://www.mql5.com |
//+------------------------------------------------------------------+
#property copyright "Copyright 2019, EAKV2"
#property link      "https://xvideos.com/"
#property version   "1.00"
#property strict
#property indicator_chart_window
#property indicator_buffers 3
double Buffer1[];
double Buffer2[];
double Buffer3[];
extern string sistema="S2";

datetime next_candle;
//+------------------------------------------------------------------+
//| Custom indicator initialization function                         |
//+------------------------------------------------------------------+
int OnInit()
  {
//--- indicator buffers mapping
//EventSetTimer(60);
//---
//SetIndexStyle(0,DRAW_ARROW,0,1);
//SetIndexArrow(0,140);
SetIndexBuffer(0,Buffer1);
SetIndexEmptyValue(0,0.0);
SetIndexLabel(0,"SMA");

SetIndexBuffer(1,Buffer2);
SetIndexEmptyValue(1,0.0);
SetIndexLabel(1,"OP");

SetIndexBuffer(2,Buffer3);
SetIndexEmptyValue(2,0.0);
SetIndexLabel(2,"COP");


next_candle=Time[0]+60;

   return(INIT_SUCCEEDED);
  }
  int deinit()
    {
  //----

  //----
     return(0);
    }

//+------------------------------------------------------------------+
//| Timer function                                                   |
//+------------------------------------------------------------------+
void start()
  {


    string MAINCURR=StringSubstr(Symbol(),0,3);
    string SECCURR=StringSubstr(Symbol(),3,5);
    int mainindex=0;
    int secuindex=0;
if(MAINCURR=="EUR")mainindex=0;
if(MAINCURR=="GBP")mainindex=1;
if(MAINCURR=="AUD")mainindex=2;
if(MAINCURR=="NZD")mainindex=3;
if(MAINCURR=="CHF")mainindex=4;
if(MAINCURR=="CAD")mainindex=5;
if(MAINCURR=="JPY")mainindex=6;
if(MAINCURR=="USD")mainindex=7;
if(MAINCURR=="XAU")mainindex=8;

if(SECCURR=="EUR")secuindex=0;
if(SECCURR=="GBP")secuindex=1;
if(SECCURR=="AUD")secuindex=2;
if(SECCURR=="NZD")secuindex=3;
if(SECCURR=="CHF")secuindex=4;
if(SECCURR=="CAD")secuindex=5;
if(SECCURR=="JPY")secuindex=6;
if(SECCURR=="USD")secuindex=7;
if(SECCURR=="XAU")secuindex=8;

    double inrmi = iCustom(Symbol(),0,"RMI",100,200,0,0);//100 20015,60
    double inrmi2 = iCustom(Symbol(),0,"RMI",5,10,0,0);//30 30
    //double tendC = iCustom(Symbol(),0,"SuperTrend",600,75.0,0,0);//65//20.0
    //double tendV = iCustom(Symbol(),0,"SuperTrend",600,75.0,1,0);//43200 10080 1440
    //double tendC3 = iCustom(Symbol(),0,"SuperTrend",600,15.0,0,0);//43200 10080 1440
    //double tendV3 = iCustom(Symbol(),0,"SuperTrend",600,15.0,1,0);//43200 10080 1440
     //double tendC2 = iCustom(Symbol(),0,"SuperTrend",600,7.0,0,0);//43200 10080 1440
     //double tendV2 = iCustom(Symbol(),0,"SuperTrend",600,7.0,1,0);//43200 10080 1440
     double tendopenC = iCustom(Symbol(),0,"SuperTrend",600,3.5,0,0);//43200 10080 1440
     double tendopenV = iCustom(Symbol(),0,"SuperTrend",600,3.5,1,0);//43200 10080 1440
    // double tendC2 = iCustom(Symbol(),PERIOD_M5,"SuperTrend",1000,15.0,0,0);//43200 10080 1440
    // double tendV2 = iCustom(Symbol(),PERIOD_M5,"SuperTrend",1000,15.0,1,0);//43200 10080 1440

    double correlC1 = iCustom(Symbol(),0,"correl8b",400,mainindex,1);//65//20.0
    double correlC2 = iCustom(Symbol(),0,"correl8b",400,mainindex,3);//65//20.0
    double correlC3 = iCustom(Symbol(),0,"correl8b",400,mainindex,6);//65//20.0
    double correlV1 = iCustom(Symbol(),0,"correl8b",400,secuindex,1);//65//20.0
    double correlV2 = iCustom(Symbol(),0,"correl8b",400,secuindex,3);//65//20.0
    double correlV3 = iCustom(Symbol(),0,"correl8b",400,secuindex,6);//65//20.0
    //double sentimentC = iCustom(Symbol(),0,"Symphonie_Sentiment_Indikator",1960,1,0);//65//20.0
    //double sentimentV = iCustom(Symbol(),0,"Symphonie_Sentiment_Indikator",1960,2,0);//65//20.0
    //double volatility = iCustom(Symbol(),0,"volatility-indicator-2",60,0.6,1,0);//65//20.0




//---------------------------------------------------------
//EJECUCION
//---------------------------------------------------------


int opsend=0,opsend2=0,opsend3=0,tend=0,tend2=0,tend3=0,tend4=0,tendopen=0,tendopen2=0,compra=0,venta=0,tiempoC=0,tiempoV=0;

int timeelapsedC=0,timeelapsedV=0;
int permitirC=0,permitirV=0, volatilityhigh=0;

double dineritoC=0,dineritoV=0;

for(int cnt=0;cnt<OrdersTotal();cnt++){
  OrderSelect(cnt,SELECT_BY_POS,MODE_TRADES);
  if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()&&OrderComment()==sistema){
    timeelapsedC=(int)TimeCurrent()-(int)OrderOpenTime();
     dineritoC=dineritoC+(double)OrderProfit()+(double)OrderSwap()+(double)OrderCommission();
    compra++;
  }
  if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()&&OrderComment()==sistema){
    timeelapsedV=(int)TimeCurrent()-(int)OrderOpenTime();
    dineritoV =dineritoV+(double)OrderProfit()+(double)OrderSwap()+(double)OrderCommission();
    venta++;
  }

}



//int opsend3=0;

//if(volatility>0&&volatility!=EMPTY_VALUE)volatilityhigh=1;

if(inrmi2>70)opsend3=2;//70 30
if(inrmi2<30)opsend3=1;



if(correlC1>correlV1&&correlC1>correlC3&&correlC1!=EMPTY_VALUE&&correlV1<0)opsend=1;//70 30
if(correlV1>correlC1&&correlV1>correlV3&&correlC1!=EMPTY_VALUE&&correlC1<0)opsend=2;//70 30
if(correlC1>correlV1)opsend2=1;//70 30
if(correlV1>correlC1)opsend2=2;//70 30
// if(tendC!=EMPTY_VALUE&&tendC!=0)tend=1;
// if(tendV!=EMPTY_VALUE&&tendV!=0)tend=2;
//if(sentimentC!=EMPTY_VALUE&&sentimentC!=0)tend4=1;
//if(sentimentV!=EMPTY_VALUE&&sentimentV!=0)tend4=2;
//if(tendC2!=EMPTY_VALUE&&tendC2!=0)tend2=1;
//if(tendV2!=EMPTY_VALUE&&tendV2!=0)tend2=2;
//if(tendC3!=EMPTY_VALUE&&tendC3!=0)tend3=1;
//if(tendV3!=EMPTY_VALUE&&tendV3!=0)tend3=2;
if(tendopenC!=EMPTY_VALUE&&tendopenC!=0)tendopen=1;
if(tendopenV!=EMPTY_VALUE&&tendopenV!=0)tendopen=2;
//if(tendopenC2!=EMPTY_VALUE&&tendopenC2!=0)tendopen2=1;
//if(tendopenV2!=EMPTY_VALUE&&tendopenV2!=0)tendopen2=2;

//---------------------------------------------------------
//EJECUCION
//---------------------------------------------------------

int send=0,close=0;


if(next_candle<=Time[0])
   {
      next_candle=Time[0]+Period();


      //printf("opsend"+opsend+" :2:"+opsend2 );
      //printf("_1:"+correlC1+" _2:"+correlV1 );
      //&&tendopen==1&&tend==1&&tend3==1 //&&tendopen==2&&tend==2&&tend3==2
      //if(opsend==1&&opsend3==1&&tendopen==1&&tend4==1)send=1;//BBBBBBBBBBBBBB
      //if(opsend==2&&opsend3==2&&tendopen==2&&tend4==2)send=2; //BBBBBBBBBBBBb
     //if(opsend==1&&tendopen==1&&tend4==1)send=1;//opsend==1&&&&tend3==1 &&tend==1
      //if(opsend==2&&tendopen==2&&tend4==2)send=2; //&&tend3==1&&tend==1opsend2==1&&tend2==1
      if(opsend==1&&opsend3==1&&tendopen==1)send=1;//BBBBBBBBBBBBBB
      if(opsend==2&&opsend3==2&&tendopen==2)send=2; //BBBBBBBBBBBBb 1.4
    //  if(opsend==1)send=1;//opsend==1&&&&tend3==1 &&tend==1
    //  if(opsend==2)send=2; //&&tend3==1&&tend==1opsend2==1&&tend2==1

      //if(opsend2==2&&dineritoC>0)close=1;
      //if(opsend2==1&&dineritoV>0)close=2;
      if(opsend3==2&&dineritoC>0.1&&dineritoC!=EMPTY_VALUE&&dineritoC!=NULL&&dineritoC!=0)close=1; //ULTIMOOOO
      if(opsend3==1&&dineritoV>0.1&&dineritoV!=EMPTY_VALUE&&dineritoV!=NULL&&dineritoV!=0)close=2; //ULTIMOOO
      //if(send==2&&dineritoC>0.1)close=1;
      //if(send==1&&dineritoV>0.1)close=2;
      if(compra>0&&timeelapsedV>259200&&timeelapsedV!=EMPTY_VALUE&&timeelapsedV!=NULL&&timeelapsedV!=0)close=2;//43200
      if(venta>0&&timeelapsedC>259200&&timeelapsedC!=EMPTY_VALUE&&timeelapsedC!=NULL&&timeelapsedC!=0)close=1;

      //if(opsend3==2&&tend4==2&&tend3==2)close=1;
      //if(opsend3==1&&tend4==1&&tend3==1)close=2;
      //if(compra>1&&dineritoC>0)close=1;
      //if(venta>1&&dineritoV>0)close=2;
      if(close==1||close==2)Buffer3[0]=close;
      if(close!=send){
      if(send==1||send==2)Buffer2[0]=send;
}
      //ObjectSetText(Symbol()+"S1conf","dineritoC"+dineritoC+" dineritoV"+dineritoV,12,NULL,Orange);
      // ObjectSetText(Symbol()+"S1conf","timeelapsedC"+timeelapsedC+" timeelapsedV"+timeelapsedV,12,NULL,Orange);
      //  ObjectSet(Symbol()+"S1conf",OBJPROP_CORNER,0);
      //  ObjectSet(Symbol()+"S1conf",OBJPROP_XDISTANCE,150);
      //  ObjectSet(Symbol()+"S1conf",OBJPROP_YDISTANCE,70);
// if(GetLastError()==true){
// printf(GetLastError());
// }



  //}


}


  }
//+------------------------------------------------------------------+
//la configuracion sin sentiment de apertura bien. (aceptable)
