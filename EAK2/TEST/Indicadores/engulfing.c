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

    double rmi1 = iCustom(Symbol(),PERIOD_M5,"RMI",4,600,0,0);//43200 10080 1440
    double rmi2 = iCustom(Symbol(),PERIOD_M5,"RMI",6,6,0,0);//43200 10080 1440
int tend=0;
if(rmi1>50){
  tend=1;
}
if(rmi1<50){
  tend=2;
}

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
    permitir=1;
    if(tend==2){
      cerrar2=1;
    }
  }
  if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()){
    permitir=1;

    if(tend==1){
      cerrar2=2;
    }
  }
}
}

if(tend==1){
  if(rmi2<10&&permitir==1){
    Buffer2[0]=1;
  }
  if(rmi2>90){
    Buffer3[0]=1;
  }
}

if(tend==2){
  if(rmi2>90&&permitir==1){
    Buffer2[0]=2;
  }
  if(rmi2<10){
    Buffer3[0]=2;
  }
}

//printf("tp1hit"+tp1hit+" _tp2hit"+tp2hit);
 //
 if(cerrar2==1)Buffer3[0]=1;
 if(cerrar2==2)Buffer3[0]=2;



  }
//+------------------------------------------------------------------+
