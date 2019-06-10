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
    double inrmi2 = iCustom(Symbol(),PERIOD_M1,"RMI",0,0);//43200 10080 1440
    double ichiC = iCustom(Symbol(),PERIOD_M5,"ZB-CloudLines",192,696,816,true,true,true,false,5,0);//43200 10080 1440
    double ichiV = iCustom(Symbol(),PERIOD_M5,"ZB-CloudLines",192,696,816,true,true,true,false,6,0);//43200 10080 1440
    double ichiCp = iCustom(Symbol(),PERIOD_M5,"ZB-CloudLines",192,696,816,true,true,true,false,5,1);//43200 10080 1440
    double icompra = iCustom(Symbol(),PERIOD_M5,"ZB-CloudLines",192,696,816,true,true,true,false,0,0);//43200 10080 1440
    double iventa = iCustom(Symbol(),PERIOD_M5,"ZB-CloudLines",192,696,816,true,true,true,false,1,0);//43200 10080 1440

//---------------------------------------------------------
//EJECUCION
//---------------------------------------------------------
printf("ichiC"+ichiC);
int tend=0,permitir=0,cerrar=0,cerrar2=0,opsend2=0,opsend=0;
double dineritoC=0,dineritoV=0,timeelapsedC=0,timeelapsedV=0;

if(ichiC>ichiV&&Ask>ichiV&&Ask>ichiC&&icompra>iventa)permitir=1;
if(ichiC<ichiV&&Ask<ichiV&&Ask<ichiC&&icompra<iventa)permitir=2;
if(Ask<ichiV)cerrar=1;
if(Ask>ichiC)cerrar=2;
if(icompra<iventa)cerrar2=1;
if(icompra>iventa)cerrar2=2;
if(Ask<ichiC&&Ask>ichiV)permitir=0;
if(Ask>ichiC&&Ask<ichiV)permitir=0;
if(inrmi>80)opsend=1;
if(inrmi<20)opsend=2;
if(inrmi2>80)opsend2=1;
if(inrmi2<20)opsend2=2;
//---------------------------------------------------------
//EJECUCION
//---------------------------------------------------------
for(int cnt;cnt<OrdersTotal();cnt++){
  OrderSelect(cnt,SELECT_BY_POS,MODE_TRADES);
  if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()){
    dineritoC=OrderProfit()+dineritoC;
    permitir=0;
  }
  if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()){
    dineritoV=OrderProfit()+dineritoV;
    permitir=0;
  }
}

if(cerrar2==1)Buffer3[0]=1;//opsend==1&&&&tend3==1
if(cerrar2==2)Buffer3[0]=2;
if(cerrar==1)Buffer3[0]=1;//opsend==1&&&&tend3==1
if(cerrar==2)Buffer3[0]=2;

//if(opsend2==2&&dineritoC>0)Buffer3[0]=1;
//if(opsend2==1&&dineritoV>0)Buffer3[0]=2;

if(permitir==1)Buffer2[0]=1;//opsend==1&&&&tend3==1
if(permitir==2)Buffer2[0]=2;
  }
//+------------------------------------------------------------------+
