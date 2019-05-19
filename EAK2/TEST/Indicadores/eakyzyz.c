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
SetIndexLabel(0,"Tendencia");

SetIndexBuffer(1,Buffer2);
SetIndexEmptyValue(1,0.0);
SetIndexLabel(1,"OP");

SetIndexBuffer(2,Buffer3);
SetIndexEmptyValue(2,0.0);
SetIndexLabel(2,"COP");

SetIndexBuffer(3,Buffer4);
SetIndexEmptyValue(3,0.0);
SetIndexLabel(3,"riesgo");

SetIndexBuffer(4,Buffer5);
SetIndexEmptyValue(4,0.0);
SetIndexLabel(4,"Probabilidad");


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
    double yzyzCOpen = iCustom(Symbol(),PERIOD_H1,"yzyz",0,1);//COMPRA
    double yzyzVOpen = iCustom(Symbol(),PERIOD_H1,"yzyz",1,1);//VENTA
    double yzyzC = iCustom(Symbol(),PERIOD_H4,"yzyz",0,1);//COMPRA
    double yzyzV = iCustom(Symbol(),PERIOD_H4,"yzyz",1,1);//VENTA
    double yzyzC2 = iCustom(Symbol(),PERIOD_D1,"yzyz",0,1);//COMPRA CIERRE
    double yzyzV2 = iCustom(Symbol(),PERIOD_D1,"yzyz",1,1);//VENTA CIERRE
    double tu = iCustom(Symbol(),PERIOD_M30,"SuperTrend",0,1);
    double td = iCustom(Symbol(),PERIOD_M30,"SuperTrend",1,1);
    //double semaforindv2B = iCustom(Symbol(),PERIOD_M15,"semaforov2eak",50,100,200,4,1);//COMPRA
    //double semaforindv2S = iCustom(Symbol(),PERIOD_M15,"semaforov2eak",50,100,200,5,1);//VENTA
    double tu2 = iCustom(Symbol(),PERIOD_M15,"SuperTrend",0,0);
    double td2 = iCustom(Symbol(),PERIOD_M15,"SuperTrend",1,0);
  //  double tu3 = iCustom(Symbol(),PERIOD_M30,"SuperTrend",0,0);
  //  double td3 = iCustom(Symbol(),PERIOD_M30,"SuperTrend",1,0);
int op=0;
if(tu!=EMPTY_VALUE&&tu!=0){
if(yzyzCOpen!=EMPTY_VALUE&&yzyzCOpen!=0)op=1;
}
if(td!=EMPTY_VALUE&&td!=0){
if(yzyzVOpen!=EMPTY_VALUE&&yzyzVOpen!=0)op=2;
}
if(tu2!=EMPTY_VALUE&&tu2!=0){

if(yzyzV!=EMPTY_VALUE&&yzyzV!=0){//&&semaforindv2B!=EMPTY_VALUE&&semaforindv2B!=0
    Buffer3[0]=2;
    }
}
if(td2!=EMPTY_VALUE&&td2!=0){

if(yzyzC!=EMPTY_VALUE&&yzyzC!=0){//&&semaforindv2S!=EMPTY_VALUE&&semaforindv2S!=0
    Buffer3[0]=1;
}
}


if(Buffer3[0]!=op||Buffer3[1]!=op){
  Buffer2[0]=op;
}






  }
//+------------------------------------------------------------------+
