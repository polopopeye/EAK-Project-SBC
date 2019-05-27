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
SetIndexLabel(0,"Supersignal");

SetIndexBuffer(1,Buffer2);
SetIndexEmptyValue(1,0.0);
SetIndexLabel(1,"OP");

SetIndexBuffer(2,Buffer3);
SetIndexEmptyValue(2,0.0);
SetIndexLabel(2,"COP");

SetIndexBuffer(3,Buffer4);
SetIndexEmptyValue(3,0.0);
SetIndexLabel(3,"Arrow");

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


//CONFIG 1

double emaC = iCustom(Symbol(),PERIOD_H4,"Double EMA crossover with arrow and email",0,1);
double emaV = iCustom(Symbol(),PERIOD_H4,"Double EMA crossover with arrow and email",1,1);
double cci = iCustom(Symbol(),PERIOD_M30,"DRBobCCI",0,0);


if(emaC!=EMPTY_VALUE&&emaC>0&&cci<0){//SolarwindsC>0&&SolarwindsC!=EMPTY_VALUE
  Buffer2[0]=1;
}

if(emaV!=EMPTY_VALUE&&emaV>0&&cci>0){//SolarwindsV<0&&SolarwindsV!=EMPTY_VALUE
    Buffer2[0]=2;
}
if(emaC!=EMPTY_VALUE&&emaC>0){
  Buffer3[0]=2;
}
if(emaV!=EMPTY_VALUE&&emaV>0){
  Buffer3[0]=1;
}

  }
//+------------------------------------------------------------------+
