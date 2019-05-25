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


//CONFIG 1

//double zigzagB = iCustom(Symbol(),PERIOD_M15,"ZigZag Arrow",0,0);
//double zigzagS = iCustom(Symbol(),PERIOD_M15,"ZigZag Arrow",1,0);
double jrsxB = iCustom(Symbol(),PERIOD_M15,"3c_turbo_jrsx_filtered",1,1);
double jrsxS = iCustom(Symbol(),PERIOD_M15,"3c_turbo_jrsx_filtered",2,1);


double pivotT = iCustom(Symbol(),PERIOD_H4,"Pivot_Voty",1,0);
double pivotB = iCustom(Symbol(),PERIOD_H4,"Pivot_Voty",5,0);
double pivotN = iCustom(Symbol(),PERIOD_H4,"Pivot_Voty",3,0);
//double pivotNT = iCustom(Symbol(),PERIOD_H4,"Pivot_Voty",2,0);
//double pivotNB = iCustom(Symbol(),PERIOD_H4,"Pivot_Voty",4,0);


double price=Ask;


//if(zigzagB!=EMPTY_VALUE&&zigzagB>0){
if(jrsxB!=EMPTY_VALUE&&jrsxB>0&&jrsxB<40){
if(price<pivotB&&pivotB!=EMPTY_VALUE){
  Buffer2[0]=1;
}
}
//}


//if(zigzagS!=EMPTY_VALUE&&zigzagS>0){
if(jrsxS!=EMPTY_VALUE&&jrsxS>0&&jrsxS>60){
if(price>pivotT&&pivotT!=EMPTY_VALUE){
  Buffer2[0]=2;
}
}
//}


if(price<pivotN){
//Cerrar venta
Buffer3[0]=2;
}
if(price>pivotN){
//Cerrar compra
Buffer3[0]=1;
}





  }
//+------------------------------------------------------------------+
