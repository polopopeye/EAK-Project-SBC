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

//RECOMENDADO M30
    double ExtremeC = iCustom(Symbol(),PERIOD_M15,"Symphonie_Extreme_Cycle_Indikator",1,1);
    double ExtremeV = iCustom(Symbol(),PERIOD_M15,"Symphonie_Extreme_Cycle_Indikator",2,1);
    //double ExtremeC = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,4,1);//COMPRA
    //double ExtremeV = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,5,1);//VENTA
    double MarketC = iCustom(Symbol(),PERIOD_H4,"Symphonie_Market_Emotion_Indikator",0,1);
    double MarketV = iCustom(Symbol(),PERIOD_H4,"Symphonie_Market_Emotion_Indikator",1,1);
    double SentimentC = iCustom(Symbol(),PERIOD_H4,"Symphonie_Sentiment_Indikator",1,1);
    double SentimentV = iCustom(Symbol(),PERIOD_H4,"Symphonie_Sentiment_Indikator",2,1);
    //double TrendC = iCustom(Symbol(),PERIOD_M30,"Symphonie_Trendline_Indikator",0,1);
    //double TrendV = iCustom(Symbol(),PERIOD_M30,"Symphonie_Trendline_Indikator",1,1);



if(ExtremeC!=EMPTY_VALUE&&ExtremeC!=0){
  if(MarketC!=EMPTY_VALUE&&MarketC!=0){
    if(SentimentC!=EMPTY_VALUE&&SentimentC!=0){
    //  if(TrendC!=EMPTY_VALUE&&TrendC!=0){
        Buffer2[0]=1;
        Buffer3[0]=2;

      //  }
      }
    }
  }
  if(ExtremeV!=EMPTY_VALUE&&ExtremeV!=0){
    if(MarketV!=EMPTY_VALUE&&MarketV!=0){
      if(SentimentV!=EMPTY_VALUE&&SentimentV!=0){
      //  if(TrendV!=EMPTY_VALUE&&TrendV!=0){
          Buffer2[0]=2;
          Buffer3[0]=1;

        //  }
        }
      }
    }
    // if(TrendC!=EMPTY_VALUE&&TrendC!=0){
    //
    //   }
    // if(TrendV!=EMPTY_VALUE&&TrendV!=0){
    //
    //   }

  }
//+------------------------------------------------------------------+
