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


    double SMAcrossUP = iCustom(Symbol(),PERIOD_D1,"SMA CrossOver_Justin",1,1);
    double SMAcrossDOWN = iCustom(Symbol(),PERIOD_D1,"SMA CrossOver_Justin",0,1);

    double adxUP1 = iCustom(Symbol(),PERIOD_H4,"ADXcrossesNon-repainting",0,1);
    double adxDOWN1 = iCustom(Symbol(),PERIOD_H4,"ADXcrossesNon-repainting",1,1);

    double adxUP2 = iCustom(Symbol(),PERIOD_H4,"@@ADXcrossesNon-repainting",0,1);
    double adxDOWN2 = iCustom(Symbol(),PERIOD_H4,"@@ADXcrossesNon-repainting",1,1);

    double TrendUP = iCustom(Symbol(),PERIOD_H4,"SuperTrend",0,0);
    double TrendDOWN = iCustom(Symbol(),PERIOD_H4,"SuperTrend",1,0);

//-------------------------------------------------------
    //
    // double adxUP12 = iCustom(Symbol(),PERIOD_H1,"ADXcrossesNon-repainting",0,1);
    // double adxDOWN12 = iCustom(Symbol(),PERIOD_H1,"ADXcrossesNon-repainting",1,1);
    //
    // double adxUP22 = iCustom(Symbol(),PERIOD_H1,"@@ADXcrossesNon-repainting",0,1);
    // double adxDOWN22 = iCustom(Symbol(),PERIOD_H1,"@@ADXcrossesNon-repainting",1,1);
    // double TrendUP2 = iCustom(Symbol(),PERIOD_M5,"SuperTrend",0,0);
    // double TrendDOWN2 = iCustom(Symbol(),PERIOD_M5,"SuperTrend",1,0);

int sma=0;

if(SMAcrossUP!=EMPTY_VALUE&&SMAcrossUP!=0)sma=1;
if(SMAcrossDOWN!=EMPTY_VALUE&&SMAcrossDOWN!=0)sma=2;

if(Buffer1[1]==1&&sma==0)Buffer1[0]=1;
if(Buffer1[1]==2&&sma==0)Buffer1[0]=2;
if(sma==1)Buffer1[0]=1;
if(sma==2)Buffer1[0]=2;




if(Buffer1[0]!=EMPTY_VALUE&&Buffer1[0]!=0){
if(Buffer1[0]==1&&adxUP1!=EMPTY_VALUE&&adxUP1!=0&&adxUP2!=EMPTY_VALUE&&adxUP2!=0){//&&TrendUP!=EMPTY_VALUE&&TrendUP!=0
Buffer2[0]=1;
Buffer3[0]=2;
}
if(Buffer1[0]==2&&adxDOWN1!=EMPTY_VALUE&&adxDOWN1!=0&&adxDOWN2!=EMPTY_VALUE&&adxDOWN2!=0){//&&TrendDOWN!=EMPTY_VALUE&&TrendDOWN!=0
Buffer2[0]=2;
Buffer3[0]=1;
}
//Buffer1[0]==1&&
  }
  // if(Buffer1[0]==1&&adxUP12!=EMPTY_VALUE&&adxUP12!=0&&adxUP22!=EMPTY_VALUE&&adxUP22!=0&&TrendUP2!=EMPTY_VALUE&&TrendUP2!=0){//
  // }
  // //Buffer1[0]==2&&
  // if(Buffer1[0]==2&&adxDOWN12!=EMPTY_VALUE&&adxDOWN12!=0&&adxDOWN22!=EMPTY_VALUE&&adxDOWN22!=0&&TrendDOWN2!=EMPTY_VALUE&&TrendDOWN2!=0){//
  // }

  }
//+------------------------------------------------------------------+
