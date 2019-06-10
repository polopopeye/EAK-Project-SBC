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

    double inrmi = iCustom(Symbol(),PERIOD_M1,"RMI",0,0);//43200 10080 1440
    double sell = 0; //iCustom(Symbol(),PERIOD_H1,"RMI",0,0);//43200 10080 1440
    double buy = 0;//iCustom(Symbol(),PERIOD_H1,"MagicDots",3,1);//43200 10080 1440
    double sell2 = 0; //iCustom(Symbol(),PERIOD_H1,"RMI",0,0);//43200 10080 1440
    double buy2 = 0;//iCustom(Symbol(),PERIOD_H1,"MagicDots",3,1);//43200 10080 1440
    //double hilo = iCustom(Symbol(),PERIOD_M5,"Hi-loSSL",50,0,0);//43200 10080 1440 BIEN
    // double hilo = iCustom(Symbol(),PERIOD_M5,"Hi-loSSL",100,0,0);//43200 10080 1440
    // double hilop = iCustom(Symbol(),PERIOD_M5,"Hi-loSSL",100,0,1);//43200 10080 1440
    double tendC = iCustom(Symbol(),PERIOD_M1,"SuperTrend",20,3.0,0,1);//43200 10080 1440
//    double tendV = iCustom(Symbol(),PERIOD_M1,"SuperTrend",20,3.0,1,1);//43200 10080 1440

//---------------------------------------------------------
//EJECUCION
//---------------------------------------------------------

int tend=0;
int permitir=0;
if(inrmi>80){
  sell=1;
}
if(inrmi<20){
  buy=1;
}
if(tendC!=0&&tendC!=EMPTY_VALUE)tend=1;
//if(tendV!=0&&tendV!=EMPTY_VALUE)tend=2;
 double dineritoC=0;
 double dineritoV=0;
 int cerrar2=0;
  int cerrar1=0;
  int compra=0;
  int venta=0;
 // int permitir=1;

if(OrdersTotal()>0){
  for(int cnt;cnt<OrdersTotal();cnt++){
    OrderSelect(cnt,SELECT_BY_POS,MODE_TRADES);
    double timeelapsed=TimeCurrent()-OrderOpenTime();
  if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()){
    compra++;
    if(timeelapsed>25000){
        cerrar1=1;
    }
  dineritoC=OrderProfit()+dineritoC;
  }
  if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()){
    venta++;
    dineritoV=OrderProfit()+dineritoV;
    if(timeelapsed>25000){
        cerrar1=2;
    }
  }
}


//FUERA DE for
if(compra<12){
  if(sell!=0&&sell!=EMPTY_VALUE&&dineritoC>0){
   cerrar2=1;
  }
}else{
  if(sell!=0&&sell!=EMPTY_VALUE){
   cerrar2=1;
  }
}
if(venta<12){
  if(buy!=0&&buy!=EMPTY_VALUE&&dineritoV>0){
   cerrar2=2;
  }
}else{
  if(buy!=0&&buy!=EMPTY_VALUE){
   cerrar2=2;
  }

}

}


int sendop=0;
if(tend==1){
  //compra
  if(buy!=0&&buy!=EMPTY_VALUE){
    sendop=1;
  }
}

if(tend==2){
  //venta
  if(sell!=0&&sell!=EMPTY_VALUE){
    sendop=2;
  }
}

if(sendop==1){
  Buffer1[0]=1;
}
if(Buffer1[1]==1){
  if(sendop!=2){
    Buffer1[0]=1;
  }
}

if(sendop==2){
  Buffer4[0]=2;
}
if(Buffer4[1]==2){
  if(sendop!=1){
    Buffer4[0]=2;
  }
}

if(sendop==0){
  if(Buffer2[1]==1&&venta<4&&tend==2)Buffer2[0]=1;
  if(Buffer2[1]==2&&compra<4&&tend==1)Buffer2[0]=2;
}

if(Buffer4[0]==2&&tend==2){
Buffer2[0]=2;
}
if(Buffer1[0]==1&&tend==1){
Buffer2[0]=1;
}

if(tend==1&&Buffer2[0]==2){
  Buffer3[0]=2;
}
if(tend==2&&Buffer2[0]==1){
  Buffer3[0]=1;
}

if(cerrar2==1){
  Buffer3[0]=1;
}
if(cerrar2==2){
  Buffer3[0]=2;
}
if(cerrar1==1){
  Buffer3[0]=1;
}
if(cerrar1==2){
  Buffer3[0]=2;
}

// Buffer2[0]=Buffer1[0];
// Buffer3[0]=Buffer4[0];
// if(Buffer1[0]==1&&Buffer4[0]==1){
//   Buffer2[0]==1;
//   Buffer3[0]==0;
// }
// if(Buffer1[0]==2&&Buffer4[0]==2){
//   Buffer2[0]==2;
//   Buffer3[0]==0;
// }

  }
//+------------------------------------------------------------------+
