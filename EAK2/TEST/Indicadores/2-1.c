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
#property indicator_buffers 5
double Buffer1[];
double Buffer2[];
double Buffer3[];
double Buffer4[];
double Buffer5[];



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

SetIndexBuffer(3,Buffer4);
SetIndexEmptyValue(3,0.0);
SetIndexLabel(3,"SMA2");

SetIndexBuffer(4,Buffer5);
SetIndexEmptyValue(4,0.0);
SetIndexLabel(4,"CicloV");

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

    double inrmi = iCustom(Symbol(),0,"RMI",100,200,0,0);//100 20015,60
    double inrmi2 = iCustom(Symbol(),0,"RMI",5,10,0,0);//30 30
    double tendC = iCustom(Symbol(),0,"SuperTrend",600,75.0,0,0);//65//20.0
    double tendV = iCustom(Symbol(),0,"SuperTrend",600,75.0,1,0);//43200 10080 1440
    double tendC3 = iCustom(Symbol(),0,"SuperTrend",600,15.0,0,0);//43200 10080 1440
    double tendV3 = iCustom(Symbol(),0,"SuperTrend",600,15.0,1,0);//43200 10080 1440
     double tendC2 = iCustom(Symbol(),0,"SuperTrend",600,7.0,0,0);//43200 10080 1440
     double tendV2 = iCustom(Symbol(),0,"SuperTrend",600,7.0,1,0);//43200 10080 1440
     double tendopenC = iCustom(Symbol(),0,"SuperTrend",600,3.5,0,0);//43200 10080 1440
     double tendopenV = iCustom(Symbol(),0,"SuperTrend",600,3.5,1,0);//43200 10080 1440
    // double tendC2 = iCustom(Symbol(),PERIOD_M5,"SuperTrend",1000,15.0,0,0);//43200 10080 1440
    // double tendV2 = iCustom(Symbol(),PERIOD_M5,"SuperTrend",1000,15.0,1,0);//43200 10080 1440
    double sentimentC = iCustom(Symbol(),0,"Symphonie_Sentiment_Indikator",120,1,0);//65//20.0
    double sentimentV = iCustom(Symbol(),0,"Symphonie_Sentiment_Indikator",120,2,0);//65//20.0


//---------------------------------------------------------
//EJECUCION
//---------------------------------------------------------



int opsend=0,opsend2=0,tend=0,tend2=0,tend3=0,tend4=0,tendopen=0,compra=0,venta=0,tiempoC=0,tiempoV=0;
double dineritoC=0,dineritoV=0,timeelapsedC=0,timeelapsedV=0;
int permitirC=0,permitirV=0;

if(inrmi>70)opsend=2;//70 30
if(inrmi<30)opsend=1;
if(inrmi2>80)opsend2=2;
if(inrmi2<20)opsend2=1;
 if(tendC!=EMPTY_VALUE&&tendC!=0)tend=1;
 if(tendV!=EMPTY_VALUE&&tendV!=0)tend=2;
if(sentimentC!=EMPTY_VALUE&&sentimentC!=0)tend4=1;
if(sentimentV!=EMPTY_VALUE&&sentimentV!=0)tend4=2;
if(tendC2!=EMPTY_VALUE&&tendC2!=0)tend2=1;
if(tendV2!=EMPTY_VALUE&&tendV2!=0)tend2=2;
if(tendC3!=EMPTY_VALUE&&tendC3!=0)tend3=1;
if(tendV3!=EMPTY_VALUE&&tendV3!=0)tend3=2;
if(tendopenC!=EMPTY_VALUE&&tendopenC!=0)tendopen=1;
if(tendopenV!=EMPTY_VALUE&&tendopenV!=0)tendopen=2;


for(int cnt;cnt<OrdersTotal();cnt++){

  OrderSelect(cnt,SELECT_BY_POS,MODE_TRADES);
  if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()){
    timeelapsedC=TimeCurrent()-OrderOpenTime();
    dineritoC=OrderProfit()+dineritoC;
    compra++;
  }
  if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()){
    timeelapsedV=TimeCurrent()-OrderOpenTime();
    dineritoV=OrderProfit()+dineritoV;
    venta++;
  }
  // if(timeelapsedC>86400){
  //     Buffer3[0]=1;
  // }
  // if(timeelapsedV>86400){
  //     Buffer3[0]=2;
  // }
  if(timeelapsedC<604800){
      tiempoC=1;
  }
  if(timeelapsedV<604800){
     tiempoV=1;
  }
}
// if(tend2==2&&venta>0)Buffer3[0]=1;
// if(tend2==1&&compra>0)Buffer3[0]=2;
if(opsend2==1&&opsend!=2&&dineritoV>0&&tiempoV==1)Buffer3[0]=2;
if(opsend2==2&&opsend!=1&&dineritoC>0&&tiempoC==1)Buffer3[0]=1;
if(opsend2==1&&opsend!=2&&tiempoV==0)Buffer3[0]=2;
if(opsend2==2&&opsend!=1&&tiempoC==0)Buffer3[0]=1;


//---------------------------------------------------------
//EJECUCION
//---------------------------------------------------------

// if(opsend==1&&tendopen==1&&tend3==1&&tend==1)Buffer2[0]=1;//opsend==1&&&&tend3==1 &&tend==1
// if(opsend==2&&tendopen==2&&tend3==2&&tend==2)Buffer2[0]=2;

//&&tendopen==1&&tend==1&&tend3==1 //&&tendopen==2&&tend==2&&tend3==2
if(opsend2==1&&tend4==1)Buffer2[0]=1;//opsend==1&&&&tend3==1 &&tend==1
if(opsend2==2&&tend4==2)Buffer2[0]=2; //&&tend3==1&&tend==1opsend2==1&&tend2==1

if(tend3==2&&compra>0&&Buffer2[0]!=1)Buffer3[0]=1;
if(tend3==1&&venta>0&&Buffer2[0]!=2)Buffer3[0]=2;
  }
//+------------------------------------------------------------------+
//tend1 quitado de la apertura y cierre
//he cambiado el orden por error, y e cambiado la configuracion de tendencia y rmi
