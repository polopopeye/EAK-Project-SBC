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

    double c1rmi = iCustom(Symbol(),PERIOD_H4,"RMI",0,0);
    double c1semaforindv2B = iCustom(Symbol(),PERIOD_M30,"semaforov2eak",50,100,200,4,1);//COMPRA
    double c1semaforindv2S = iCustom(Symbol(),PERIOD_M30,"semaforov2eak",50,100,200,5,1);//VENTA

//-----------------------------
//Config 2 (Creo que mejor)
//Entra rapido y sale rapido

    double c2rmi = iCustom(Symbol(),PERIOD_H1,"RMI",0,0);
    double c2semaforindv2B = iCustom(Symbol(),PERIOD_M15,"semaforov2eak",50,100,200,4,1);//COMPRA
    double c2semaforindv2S = iCustom(Symbol(),PERIOD_M15,"semaforov2eak",50,100,200,5,1);//VENTA


//Siempre igual
double c2rmi2 = iCustom(Symbol(),PERIOD_M30,"RMI",0,0);
double c2semaforindv2B2 = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,4,1);//COMPRA
double c2semaforindv2S2 = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,5,1);//VENTA


    // double tu = iCustom(Symbol(),PERIOD_M5,"SuperTrend",0,1);
    // double td = iCustom(Symbol(),PERIOD_M5,"SuperTrend",1,1);
    // double tu2 = iCustom(Symbol(),PERIOD_M30,"SuperTrend",0,1);
    // double td2 = iCustom(Symbol(),PERIOD_M30,"SuperTrend",1,1);
//    double instrendR = iCustom(Symbol(),PERIOD_M30,"InstantaneousTrendline",0,0);//Rojo
//    double instrendA = iCustom(Symbol(),PERIOD_M30,"InstantaneousTrendline",1,0);//Azul

//if(tu!=EMPTY_VALUE&&tu!=0){//compra


  if(c1semaforindv2B!=EMPTY_VALUE&&c1semaforindv2B!=0){
    if(c1rmi<25){
      Buffer2[0]=1;
    }
    }

if(c1semaforindv2S!=EMPTY_VALUE&&c1semaforindv2S!=0){//Venta
  if(c1rmi>75){
    Buffer2[0]=2;
  }
}

if(c2semaforindv2B!=EMPTY_VALUE&&c2semaforindv2B!=0){
  if(c2rmi<10){
    Buffer2[0]=1;
  }
  }

if(c2semaforindv2S!=EMPTY_VALUE&&c2semaforindv2S!=0){//Venta
if(c2rmi>90){
  Buffer2[0]=2;

}
}

//Para el cierre siempre igual

if(c2semaforindv2B2!=EMPTY_VALUE&&c2semaforindv2B2!=0){
  if(c2rmi2<25){
  Buffer3[0]=2;
}
}
if(c2semaforindv2S2!=EMPTY_VALUE&&c2semaforindv2S2!=0){
  if(c2rmi2>75){
  Buffer3[0]=1;
}
}









  }
//+------------------------------------------------------------------+
