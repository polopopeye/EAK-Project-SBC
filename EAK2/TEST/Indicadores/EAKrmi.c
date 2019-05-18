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

    double rmi = iCustom(Symbol(),PERIOD_M30,"RMI",9,26,54,0,0);
    double semaforindv2B = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,4,1);//COMPRA
    double semaforindv2S = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,5,1);//VENTA
//    double instrendR = iCustom(Symbol(),PERIOD_M30,"InstantaneousTrendline",0,0);//Rojo
//    double instrendA = iCustom(Symbol(),PERIOD_M30,"InstantaneousTrendline",1,0);//Azul

//if(instrendA>instrendR){//compra
  if(semaforindv2B!=EMPTY_VALUE&&semaforindv2B!=0){
    if(rmi<25){
      Buffer2[0]=1;
      Buffer3[0]=2;
    }
      }
//}
//if(instrendA<instrendR){//Venta
  if(semaforindv2S!=EMPTY_VALUE&&semaforindv2S!=0){
  if(rmi>75){
    Buffer2[0]=2;
  Buffer3[0]=1;
  }
  }
//}











  }
//+------------------------------------------------------------------+
