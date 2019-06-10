
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
SetIndexLabel(0,"SMA");

SetIndexBuffer(1,Buffer2);
SetIndexEmptyValue(1,0.0);
SetIndexLabel(1,"OP");

SetIndexBuffer(2,Buffer3);
SetIndexEmptyValue(2,0.0);
SetIndexLabel(2,"COP");

SetIndexBuffer(3,Buffer4);
SetIndexEmptyValue(3,0.0);
SetIndexLabel(3,"SMA2");

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


    double BuyArrow = iCustom(Symbol(),PERIOD_M5,"BuySellArrowScalper_V2.0",2,true,true,false,false,false,false,false,4,1);
    double SellArrow = iCustom(Symbol(),PERIOD_M5,"BuySellArrowScalper_V2.0",2,true,true,false,false,false,false,false,5,1);
    double BuyArrow2 = iCustom(Symbol(),PERIOD_M5,"BuySellArrowScalper_V2.0",2,true,true,false,false,false,false,false,0,1);
    double SellArrow2 = iCustom(Symbol(),PERIOD_M5,"BuySellArrowScalper_V2.0",2,true,true,false,false,false,false,false,1,1);


    double BuyArrowC = iCustom(Symbol(),PERIOD_H1,"BuySellArrowScalper_V2.0",2,true,true,false,false,false,false,false,4,1);
    double SellArrowC = iCustom(Symbol(),PERIOD_H1,"BuySellArrowScalper_V2.0",2,true,true,false,false,false,false,false,5,1);

    double c1semaforindv2B = iCustom(Symbol(),PERIOD_M15,"semaforov2eak",4,1);//COMPRA
    double c1semaforindv2S = iCustom(Symbol(),PERIOD_M15,"semaforov2eak",5,1);//VENTA

    //double stB = iCustom(Symbol(),PERIOD_M5,"SuperTrend",0,0);//compra
    //double stS = iCustom(Symbol(),PERIOD_M5,"SuperTrend",1,0);//compra
    double stB = 1;//compra
    double stS = 1;//compra


    // double BuyArrowC2 = iCustom(Symbol(),PERIOD_H1,"BuySellArrowScalper_V2.0",2,true,true,false,false,false,false,false,0,1);
    // double SellArrowC2 = iCustom(Symbol(),PERIOD_H1,"BuySellArrowScalper_V2.0",2,true,true,false,false,false,false,false,1,1);
//-------------------------------------------------------
double pivotN = iCustom(Symbol(),PERIOD_M5,"Pivot_Voty",1440,3,0);//43200 10080 1440
double pivotNT = iCustom(Symbol(),PERIOD_M5,"Pivot_Voty",1440,1,0);//43200 10080 1440
double pivotNB = iCustom(Symbol(),PERIOD_M5,"Pivot_Voty",1440,5,0);//43200 10080 1440

int extremo=0;
// if(Ask>pivotN&&Ask<pivotNT)extremo=2;
// if(Ask<pivotN&&Ask>pivotNT)extremo=3;
if((Ask>pivotNB&&Ask<pivotNT)||(Bid>pivotNB&&Bid<pivotNT))extremo=5;
if(Ask<pivotNB||Bid<pivotNB)extremo=4;
if(Ask>pivotNT||Bid>pivotNT)extremo=1;

//printf("ex"+extremo);

if(extremo==5){
  if(c1semaforindv2B!=0&&c1semaforindv2B!=EMPTY_VALUE&&stB!=0&&stB!=EMPTY_VALUE){
    Buffer2[0]=1;
  }
  if(c1semaforindv2S!=0&&c1semaforindv2S!=EMPTY_VALUE&&stS!=0&&stS!=EMPTY_VALUE){
    Buffer2[0]=2;
  }

// if(BuyArrow!=0&&BuyArrow!=EMPTY_VALUE){
//   Buffer2[0]=1;
// }
// if(SellArrow!=0&&SellArrow!=EMPTY_VALUE){
//   Buffer2[0]=2;
// }
}


// if(BuyArrow!=0&&BuyArrow!=EMPTY_VALUE&&BuyArrow2!=0&&BuyArrow2!=EMPTY_VALUE){//&&stB!=0&&stB!=EMPTY_VALUE(extremo==2||extremo==4)
// Buffer2[0]=1;
// Buffer3[0]=2;
//
// }
// if(SellArrow!=0&&SellArrow!=EMPTY_VALUE&&SellArrow2!=0&&SellArrow2!=EMPTY_VALUE){//&&stS!=0&&stS!=EMPTY_VALUE&&(extremo==3||extremo==1)
// Buffer2[0]=2;
// Buffer3[0]=1;
//
// }


if(c1semaforindv2B!=0&&c1semaforindv2B!=EMPTY_VALUE){//
Buffer3[0]=2;
}
if(c1semaforindv2S!=0&&c1semaforindv2S!=EMPTY_VALUE){//
Buffer3[0]=1;
}
if(extremo==1){
  Buffer3[0]=2;
}
if(extremo==4){
  Buffer3[0]=1;
}



  }
//+------------------------------------------------------------------+
//RESULTADOS ESTRATEGIA
