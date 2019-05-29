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
SetIndexLabel(3,"NT");

SetIndexBuffer(4,Buffer5);
SetIndexEmptyValue(4,0.0);
SetIndexLabel(4,"NB");

ObjectCreate(Symbol()+"a",OBJ_LABEL,0,0,0,0);
ObjectCreate(Symbol()+"b",OBJ_LABEL,0,0,0,0);

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


double jrsxB = iCustom(Symbol(),PERIOD_M5,"3c_turbo_jrsx_filtered",1,1);
double jrsxS = iCustom(Symbol(),PERIOD_M5,"3c_turbo_jrsx_filtered",2,1);


double pivotT1 = iCustom(Symbol(),PERIOD_M5,"Pivot_Voty",10080,8,0);//43200 10080 1440
double pivotB1 = iCustom(Symbol(),PERIOD_M5,"Pivot_Voty",10080,9,0);
double pivotN1 = iCustom(Symbol(),PERIOD_M5,"Pivot_Voty",10080,3,0);
//double pivotNT1 = iCustom(Symbol(),PERIOD_M5,"Pivot_Voty",10080,2,0);
//double pivotNB1 = iCustom(Symbol(),PERIOD_M5,"Pivot_Voty",10080,4,0);

double pivotT=NormalizeDouble(pivotT1,10);
double pivotB=NormalizeDouble(pivotB1,10);
double pivotN=NormalizeDouble(pivotN1,10);

double price=Ask;

//if(zigzagB!=EMPTY_VALUE&&zigzagB>0){
if(jrsxB!=EMPTY_VALUE&&jrsxB>0&&jrsxB<40){
if(price<pivotB&&pivotB!=EMPTY_VALUE&&pivotN>price){
  Buffer2[0]=1;
}
}
//}


//if(zigzagS!=EMPTY_VALUE&&zigzagS>0){
if(jrsxS!=EMPTY_VALUE&&jrsxS>0&&jrsxS>60){
if(price>pivotT&&pivotT!=EMPTY_VALUE&&pivotN<price){
  Buffer2[0]=2;
}
}
//}



if(pivotN>Ask||pivotN>Bid){
//Cerrar venta
Buffer3[0]=2;
}
if(Ask>pivotN||Bid>pivotN){
//Cerrar compra
Buffer3[0]=1;
}


  }
//+------------------------------------------------------------------+
