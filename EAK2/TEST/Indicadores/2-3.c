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
#property indicator_buffers 3
double Buffer1[];
double Buffer2[];
double Buffer3[];
extern string sistema="S1";

datetime next_candle;
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


next_candle=Time[0]+30;

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

    double inrmi = iCustom(Symbol(),0,"RMI",300,50,0,0);//100 20015,60 OPSEND 200 1500
    double inrmi2 = iCustom(Symbol(),0,"RMI",2,30,0,0);//30 30  OPSEND2 //5 10 bien

    double tendC3 = iCustom(Symbol(),0,"SuperTrend",1000,20.0,0,1);//43200 10080 1440 600 13
    double tendV3 = iCustom(Symbol(),0,"SuperTrend",1000,20.0,1,1);//43200 10080 1440 TEND 3

     double tendopenC2 = iCustom(Symbol(),0,"SuperTrend",600,3.5,0,0);//43200 10080 1440 TEND OPEN estyaba en 3.5 600Bien
    double tendopenV2 = iCustom(Symbol(),0,"SuperTrend",600,3.5,1,0);//43200 10080 1440 4 100 esta bien tambien
      double tendopenC = iCustom(Symbol(),0,"Symphonie_Trendline_Indikator",1000,500,0,0);
    double tendopenV = iCustom(Symbol(),0,"Symphonie_Trendline_Indikator",1000,500,1,0);

      double sentimentC = iCustom(Symbol(),0,"Symphonie_Sentiment_Indikator",1960,1,1);//65//20.01960 TEND 4
    double sentimentV = iCustom(Symbol(),0,"Symphonie_Sentiment_Indikator",1960,2,1);//65//20.0
     double volatility = iCustom(Symbol(),0,"volatility-indicator-2",60,0.5,1,1);//65//20.0



//---------------------------------------------------------
//EJECUCION
//---------------------------------------------------------


int opsend=0,opsend2=0,opsend3=0,tend=0,tend2=0,tend3=0,tend4=0,tend5=0,tendopen=0,tendopen2=0,compra=0,venta=0,tiempoC=0,tiempoV=0;

int timeelapsedC=0,timeelapsedV=0;
int permitirC=0,permitirV=0, volatilityhigh=0;

double dineritoC=0,dineritoV=0;

for(int cnt=0;cnt<OrdersTotal();cnt++){
  OrderSelect(cnt,SELECT_BY_POS,MODE_TRADES);
  if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()&&OrderComment()==sistema){
    timeelapsedC=(int)TimeCurrent()-(int)OrderOpenTime();
     dineritoC=dineritoC+(double)OrderProfit()+(double)OrderSwap()+(double)OrderCommission();
    compra++;
  }
  if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()&&OrderComment()==sistema){
    timeelapsedV=(int)TimeCurrent()-(int)OrderOpenTime();
    dineritoV =dineritoV+(double)OrderProfit()+(double)OrderSwap()+(double)OrderCommission();
    venta++;
  }
}




if(volatility>0&&volatility!=EMPTY_VALUE)volatilityhigh=1;
if(inrmi>70&&inrmi!=EMPTY_VALUE)opsend=2;//70 30
if(inrmi<30&&inrmi!=EMPTY_VALUE)opsend=1;
if(inrmi2>70&&inrmi2!=EMPTY_VALUE)opsend2=2;
if(inrmi2<30&&inrmi2!=EMPTY_VALUE)opsend2=1;

if(sentimentC!=EMPTY_VALUE&&sentimentC!=0)tend4=1;
if(sentimentV!=EMPTY_VALUE&&sentimentV!=0)tend4=2;

if(tendC3!=EMPTY_VALUE&&tendC3!=0)tend3=1;
if(tendV3!=EMPTY_VALUE&&tendV3!=0)tend3=2;
if(tendopenC!=EMPTY_VALUE&&tendopenC!=0)tendopen=1;
if(tendopenV!=EMPTY_VALUE&&tendopenV!=0)tendopen=2;
if(tendopenC2!=EMPTY_VALUE&&tendopenC2!=0)tendopen2=1;
if(tendopenV2!=EMPTY_VALUE&&tendopenV2!=0)tendopen2=2;

//---------------------------------------------------------
//EJECUCION
//---------------------------------------------------------

int send=0,close=0;


if(next_candle<=Time[0])
   {
      next_candle=Time[0]+Period();
      // New candle. Your trading functions here


   //Apertura sin volatilidad
      if(opsend2==1&&tend4==1&&opsend!=2&&volatilityhigh==0)send=1;//opsend==1&&&&tend3==1 &&tend==1
      if(opsend2==2&&tend4==2&&opsend!=1&&volatilityhigh==0)send=2; //&&tend3==1&&tend==1opsend2==1&&tend2==1

      if(volatilityhigh==1){
      //CIERRE MAS LENTO SIGUIENDO LA TENDENCIA
      if(dineritoC>0.1&&compra!=0&&opsend2==2&&tendopen2==2&&dineritoC!=NULL&&dineritoC!=EMPTY_VALUE&&compra!=NULL&&compra!=EMPTY_VALUE)close=1;//(SE ENCUENTRA AQUI EL PROBLEMA)
      if(dineritoV>0.1&&venta!=0&&opsend2==1&&tendopen2==1&&dineritoV!=NULL&&dineritoV!=EMPTY_VALUE&&venta!=NULL&&venta!=EMPTY_VALUE)close=2;
      }



 //APERTURA DE EXTREMOS CON VOLATILIDAD
      if(opsend2==1&&opsend!=2&&volatilityhigh==1&&tendopen2==1&&tend3==1)send=1;//opsend==1&&&&tend3==1 &&tend==1
     if(opsend2==2&&opsend!=1&&volatilityhigh==1&&tendopen2==2&&tend3==2)send=2; //&&tend3==1&&tend==1opsend2==1&&tend2==1


      //ObjectSetText(Symbol()+"S1conf","dineritoC"+dineritoC+" dineritoV"+dineritoV,12,NULL,Orange);
      // ObjectSetText(Symbol()+"S1conf","timeelapsedC"+timeelapsedC+" timeelapsedV"+timeelapsedV,12,NULL,Orange);
      //  ObjectSet(Symbol()+"S1conf",OBJPROP_CORNER,0);
      //  ObjectSet(Symbol()+"S1conf",OBJPROP_XDISTANCE,150);
      //  ObjectSet(Symbol()+"S1conf",OBJPROP_YDISTANCE,70);
  //CIERRE si hay otra op
      if(venta>2&&compra>2&&Buffer2[1]==1&&venta!=NULL&&venta!=EMPTY_VALUE)close=2;//&&tend3==2
      if(venta>2&&compra>2&&Buffer2[1]==2&&compra!=NULL&&compra!=EMPTY_VALUE)close=1;
if(volatilityhigh==0){
      //CIERRE RAPIDO SIN VOLATILIDAD
      if(opsend2==1&&opsend!=2&&dineritoV>0.1&&tendopen2==1&&venta!=0&&venta!=NULL&&venta!=EMPTY_VALUE&&dineritoV!=NULL&&dineritoV!=EMPTY_VALUE)close=2;//&&tiempoV==1
      if(opsend2==2&&opsend!=1&&dineritoC>0.1&&tendopen2==2&&compra!=0&&compra!=NULL&&compra!=EMPTY_VALUE&&dineritoC!=NULL&&dineritoC!=EMPTY_VALUE)close=1;//&&tiempoC==1
     }else{
     if(opsend2==1&&opsend!=2&&dineritoV>0.1&&tendopen2==1&&venta>2&&venta!=0&&venta!=NULL&&venta!=EMPTY_VALUE&&dineritoV!=NULL&&dineritoV!=EMPTY_VALUE)close=2;//&&tiempoV==1
      if(opsend2==2&&opsend!=1&&dineritoC>0.1&&tendopen2==2&&compra>2&&compra!=NULL&&compra!=EMPTY_VALUE&&dineritoC!=NULL&&dineritoC!=EMPTY_VALUE)close=1;//&&tiempoC==1
     }
//FIN NEW CANDLE


}


  //CIERRE POR UNA MALA TENDENCIA
    //  if(tend4==1&&venta!=0&&tend3==1&&tendopen==1&&tendopen2==1)close=2;//&&tend3==2
     // if(tend4==2&&compra!=0&&tend3==2&&tendopen==2&&tendopen2==2)close=1;



    if(close!=0)Buffer3[0]=close;

      if(close!=send){

      if(send!=0)Buffer2[0]=send;

  }





  }
//+------------------------------------------------------------------+
//tend1 quitado de la apertura y cierre
//he cambiado el orden por error, y e cambiado la configuracion de tendencia y rmi
