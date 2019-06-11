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

    double orderopC = iCustom(Symbol(),0,"PipFinite Trend PRO",8,1);//43200 10080 1440
    double orderopV = iCustom(Symbol(),0,"PipFinite Trend PRO",9,1);//43200 10080 1440
    double up = iCustom(Symbol(),0,"PipFinite Trend PRO",10,1);//43200 10080 1440
    double down = iCustom(Symbol(),0,"PipFinite Trend PRO",11,1);//43200 10080 1440
    double exitwin = iCustom(Symbol(),0,"PipFinite Trend PRO",18,1);//43200 10080 1440
    double exitloss = iCustom(Symbol(),0,"PipFinite Trend PRO",19,1);//43200 10080 1440
    double tp1hit = iCustom(Symbol(),0,"PipFinite Trend PRO",20,1);//43200 10080 1440
    double tp2hit = iCustom(Symbol(),0,"PipFinite Trend PRO",21,1);//43200 10080 1440
    double sucessrate = iCustom(Symbol(),0,"PipFinite Trend PRO",29,1);//43200 10080 1440

//     printf("opC"+orderopC+"_ opV"+orderopV+"_ eloss"+exitloss+"_ ewin"+exitwin);
// printf("_ tp1"+tp1op+"_ tp2"+tp2op+"_ up"+up+"_ down"+down);
//---------------------------------------------------------
//EJECUCION
//---------------------------------------------------------


 int cerrar2=0;
 int permitir=1;

if(OrdersTotal()>0){
  for(int cnt;cnt<OrdersTotal();cnt++){
    OrderSelect(cnt,SELECT_BY_POS,MODE_TRADES);
  if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()){
    permitir=0;
    if(down>up){
      cerrar2=1;
    }
  }
  if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()){
    permitir=0;

    if(up>down){
      cerrar2=2;
    }
  }
}
}


if(sucessrate>70){
  //if(up>down){
    if(orderopC!=0&&permitir==1)Buffer2[0]=1;
    if(tp1hit>0)Buffer3[0]=1;
    //if(tp2hit>0)Buffer3[0]=1;
    if(exitwin>0)Buffer3[0]=1;
      if(exitloss>0)Buffer3[0]=1;
  //}
  //if(down>up){
    if(orderopV!=0&&permitir==1)Buffer2[0]=2;
    if(tp1hit>0)Buffer3[0]=2;
  //if(tp2hit>0)Buffer3[0]=2;
  if(exitwin>0)Buffer3[0]=2;
    if(exitloss>0)Buffer3[0]=2;
  //}

}



//printf("tp1hit"+tp1hit+" _tp2hit"+tp2hit);

 if(cerrar2==1)Buffer3[0]=1;
 if(cerrar2==2)Buffer3[0]=2;



  }
//+------------------------------------------------------------------+
