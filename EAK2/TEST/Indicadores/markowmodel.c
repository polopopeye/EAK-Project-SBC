//+------------------------------------------------------------------+
//|                                               MarkowModel.mq4 |
//|                        Copyright 2019, EAKV2. |
//|                                             |
//+------------------------------------------------------------------+
#property copyright "Copyright 2019, EAKV2"
#property link      "https://xvideos.com/"
#property version   "1.00"
#property strict
#property indicator_chart_window
#property indicator_buffers 2
double Buffer1[];
double Buffer2[];


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
SetIndexLabel(0,"P1");

SetIndexBuffer(1,Buffer2);
SetIndexEmptyValue(1,0.0);
SetIndexLabel(1,"P2");





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

Buffer1[0]=Open[0];
Buffer2[0]=Open[0]
Buffer1[m1]=m1233;
Buffer2[m2]=m1234;
//Buffer1[P1ma1v1]=iMA(Symbol(),PERIOD_CURRENT,P1ma1v1,0,0,PRICE_LOW,0);
//High[], Low[], Open[], Close[]
//Buffer1[1]=Open[1];

//primero hay que sacar el precio medio de un lapso.
//este lapso hay que dividirlo en partes.



  }
//+------------------------------------------------------------------+
