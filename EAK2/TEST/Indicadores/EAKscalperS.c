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


double SuperSignalsC = iCustom(Symbol(),PERIOD_M15,"Super Signals",3,1);
double SuperSignalsV = iCustom(Symbol(),PERIOD_M15,"Super Signals",2,1);

//double SolarwindsC = iCustom(Symbol(),PERIOD_M30,"Solar Winds joy - histo",0,0);
//double SolarwindsV = iCustom(Symbol(),PERIOD_M30,"Solar Winds joy - histo",1,0);
double arrowsC = iCustom(Symbol(),PERIOD_M5,"Arrows",2,1);
double arrowsV = iCustom(Symbol(),PERIOD_M5,"Arrows",3,1);

int tend=0;



if(Buffer1[1]==1&&SuperSignalsC==EMPTY_VALUE&&SuperSignalsV==EMPTY_VALUE)tend=1;
if(Buffer1[1]==2&&SuperSignalsC==EMPTY_VALUE&&SuperSignalsV==EMPTY_VALUE)tend=2;
if(SuperSignalsC!=EMPTY_VALUE&&SuperSignalsC>0){
  tend=1;

}
if(SuperSignalsV!=EMPTY_VALUE&&SuperSignalsV>0){
  tend=2;

}

//printf("SC"+SolarwindsC+"SV"+SolarwindsV);
//printf("_   Buffer1[1]"+Buffer1[1]+"_   Buffer4[1]"+Buffer4[1]);

if(SuperSignalsC!=EMPTY_VALUE&&arrowsC>0){//SolarwindsC>0&&SolarwindsC!=EMPTY_VALUE

  Buffer2[0]=1;

}

if(SuperSignalsV!=EMPTY_VALUE&&arrowsV>0){//SolarwindsV<0&&SolarwindsV!=EMPTY_VALUE

    Buffer2[0]=2;

}
if(arrowsC>0){
  Buffer3[0]=2;

}
if(arrowsV>0){
  Buffer3[0]=1;

}
Buffer1[0]=tend;
printf("arrowsC"+arrowsC);

  }
//+------------------------------------------------------------------+
