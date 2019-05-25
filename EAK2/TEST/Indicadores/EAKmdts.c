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
SetIndexLabel(0,"Ciclo");

SetIndexBuffer(1,Buffer2);
SetIndexEmptyValue(1,0.0);
SetIndexLabel(1,"OP");

SetIndexBuffer(2,Buffer3);
SetIndexEmptyValue(2,0.0);
SetIndexLabel(2,"COP");

SetIndexBuffer(3,Buffer4);
SetIndexEmptyValue(3,0.0);
SetIndexLabel(3,"CicloC");

SetIndexBuffer(4,Buffer5);
SetIndexEmptyValue(4,0.0);
SetIndexLabel(4,"CicloV");

ObjectCreate(Symbol()+"rmi1",OBJ_LABEL,0,0,0,0);

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

//Config 1
//Entra en solo extremos y sale rapido

//double histogramC = iCustom(Symbol(),PERIOD_H1,"Fxtrader1969_force-index_histogram",1,0);
//double histogramV = iCustom(Symbol(),PERIOD_H1,"Fxtrader1969_force-index_histogram",2,0);
//double mtf = iCustom(Symbol(),PERIOD_M15,"Fxtrader1969_force-index_mtf",0,0);

//double macdC = iCustom(Symbol(),PERIOD_M15,"Fxtrader1969_MACD_ColorHist_Alert",0,0);
//double macdV = iCustom(Symbol(),PERIOD_M15,"Fxtrader1969_MACD_ColorHist_Alert",1,0);

//
// double qqtC = iCustom(Symbol(),PERIOD_H1,"#MTF_QQEA_Hist_Alert",0,0);
// double qqtV = iCustom(Symbol(),PERIOD_H1,"#MTF_QQEA_Hist_Alert",1,0);
// double qqtC2 = iCustom(Symbol(),PERIOD_H4,"#MTF_QQEA_Hist_Alert",0,0);
// double qqtV2 = iCustom(Symbol(),PERIOD_H4,"#MTF_QQEA_Hist_Alert",1,0);


//CONFIG 1

double qqe1 = iCustom(Symbol(),PERIOD_D1,"###QQE_Alert_MTF_v5###",0,0);
double qqe2 = iCustom(Symbol(),PERIOD_D1,"###QQE_Alert_MTF_v5###",1,0);

double qqe3 = iCustom(Symbol(),PERIOD_H4,"###QQE_Alert_MTF_v5###",0,0);
double qqe4 = iCustom(Symbol(),PERIOD_H4,"###QQE_Alert_MTF_v5###",1,0);

double qqtopen1 = iCustom(Symbol(),PERIOD_D1,"#MTF_QQEA_Hist_Alert",0,5,14,4.236,60,40,false,false,false,false,false,false,0,0);
double qqtopen2 = iCustom(Symbol(),PERIOD_D1,"#MTF_QQEA_Hist_Alert",0,5,14,4.236,60,40,false,false,false,false,false,false,1,0);




if(qqe1>qqe2&&qqe1<50&&qqtopen1==1&&qqtopen2!=1){//&&qqe1<0
    Buffer2[0]=1;
}
if(qqe1<qqe2&&qqe2>50&&qqtopen2==1&&qqtopen1!=1){//&&qqe2>0
    Buffer2[0]=2;
}

if(qqe3>qqe4&&qqtopen1==1&&qqtopen2!=1){
  Buffer3[0]=2;
}
if(qqe3<qqe4&&qqtopen2==1&&qqtopen1!=1){
  Buffer3[0]=1;
}









  }
//+------------------------------------------------------------------+
