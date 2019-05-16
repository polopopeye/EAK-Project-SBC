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
    int Methodextrapolator=4;
    double avramisA = iCustom(Symbol(),PERIOD_H1,"Cronex_Taichi",9,26,54,0,0);
    double avramisB = iCustom(Symbol(),PERIOD_H1,"Cronex_Taichi",9,26,54,3,0);
      double extrapolatorA = iCustom(Symbol(),PERIOD_M30,"Extrapolator",Methodextrapolator,30,300,0.6,100,20,0.0001,0,1,0);
     double semaforindv2B = iCustom(Symbol(),PERIOD_M15,"semaforov2eak",50,100,200,4,1);//COMPRA
     double semaforindv2S = iCustom(Symbol(),PERIOD_M15,"semaforov2eak",50,100,200,5,1);//VENTA
    //double semaforindv2B = 1;
    //double semaforindv2S = 1;

    double semaforindv2B2 = iCustom(Symbol(),PERIOD_M15,"semaforov2eak",50,100,200,5,1);//COMPRA
    double semaforindv2S2 = iCustom(Symbol(),PERIOD_M15,"semaforov2eak",50,100,200,4,1);//VENTA


  if(avramisA>avramisB){
  //ALCISTA
  if(extrapolatorA<Open[0]){
   //printf("ALTO");
   Buffer1[0]=1;
   if(semaforindv2B!=EMPTY_VALUE&&semaforindv2B>0&&semaforindv2B<1000000){
     Buffer2[0]=1;
     Buffer3[0]=2;
  //printf("COMPRA");
   }
  }

  if(semaforindv2S2!=EMPTY_VALUE&&semaforindv2S2!=0){
  // Buffer3[0]=2;
  }

  }



  if(avramisA<avramisB){
  //BAJISTA
  if(extrapolatorA>Open[0]){
  //printf("BAJO");
  Buffer1[0]=2;
  if(semaforindv2S!=EMPTY_VALUE&&semaforindv2S>0&&semaforindv2S<1000000){
    Buffer2[0]=2;
  Buffer3[0]=1;
  //printf("VENTA");

  }
  }
  if(semaforindv2B2!=EMPTY_VALUE&&semaforindv2B2!=0){
  //  Buffer3[0]=1;
  }
  }





  }
//+------------------------------------------------------------------+
