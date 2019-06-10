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


     double BuyArrow = iCustom(Symbol(),PERIOD_M15,"BuySellArrowScalper_V2.0",2,true,true,false,false,false,false,false,4,1);
     double SellArrow = iCustom(Symbol(),PERIOD_M15,"BuySellArrowScalper_V2.0",2,true,true,false,false,false,false,false,5,1);
    //
    //
     double BuyArrowC = iCustom(Symbol(),PERIOD_M15,"BuySellArrowScalper_V2.0",2,true,true,false,false,false,false,false,4,1);
     double SellArrowC = iCustom(Symbol(),PERIOD_M15,"BuySellArrowScalper_V2.0",2,true,true,false,false,false,false,false,5,1);

    double c1semaforindv2B = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",0,1);//COMPRA
    double c1semaforindv2S = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",1,1);//VENTA
    double c1semaforindv2B2 = iCustom(Symbol(),PERIOD_H1,"semaforov2eak",2,1);//COMPRA
    double c1semaforindv2S2 = iCustom(Symbol(),PERIOD_H1,"semaforov2eak",3,1);//VENM15
    double avramisA = iCustom(Symbol(),PERIOD_H4,"Cronex_Taichi",9,26,54,0,0);
    double avramisB = iCustom(Symbol(),PERIOD_H4,"Cronex_Taichi",9,26,54,3,0);

    double avramisA2 = iCustom(Symbol(),PERIOD_M30,"Cronex_Taichi",9,26,54,0,0);
    double avramisB2 = iCustom(Symbol(),PERIOD_M30,"Cronex_Taichi",9,26,54,3,0);

    double stB = 1;//compra
    double stS = 1;//compra

double pivotN = iCustom(Symbol(),PERIOD_M5,"Pivot_Voty",1440,3,0);//43200 10080 1440
double pivotNT = iCustom(Symbol(),PERIOD_M5,"Pivot_Voty",1440,1,0);//43200 10080 1440
double pivotNB = iCustom(Symbol(),PERIOD_M5,"Pivot_Voty",1440,5,0);//43200 10080 1440

double rsiG= iRSI(Symbol(),PERIOD_M5,14,PRICE_CLOSE,0);//Recomiendan h4
double rsiG2= iRSI(Symbol(),PERIOD_M5,14,PRICE_CLOSE,1);//Recomiendan h4
double rsiGp= iRSI(Symbol(),PERIOD_M5,14,PRICE_CLOSE,2);//Recomiendan h4

double rsiG3= iRSI(Symbol(),PERIOD_H1,14,PRICE_CLOSE,0);//Recomiendan h4
double rsiG32= iRSI(Symbol(),PERIOD_H1,14,PRICE_CLOSE,1);//Recomiendan h4
double rsiG3p= iRSI(Symbol(),PERIOD_H1,14,PRICE_CLOSE,2);//Recomiendan h4

double rsiG4= iRSI(Symbol(),PERIOD_H4,14,PRICE_CLOSE,0);//Recomiendan h4
double rsiG42= iRSI(Symbol(),PERIOD_H4,14,PRICE_CLOSE,1);//Recomiendan h4
double rsiG4p= iRSI(Symbol(),PERIOD_H4,14,PRICE_CLOSE,2);//Recomiendan h4

double rsiM= iRSI(Symbol(),PERIOD_H1,14,PRICE_CLOSE,0);

double rsiP= iRSI(Symbol(),PERIOD_M15,14,PRICE_CLOSE,0);
double rsiPp= iRSI(Symbol(),PERIOD_M15,14,PRICE_CLOSE,1);
double rsiC= iRSI(Symbol(),PERIOD_M15,14,PRICE_CLOSE,0);
double rsiCP= iRSI(Symbol(),PERIOD_M15,14,PRICE_CLOSE,1);


//double quantumC=iCustom(Symbol(),PERIOD_H1,"QuantumSuperChannel v1.09",2,1);
//double quantumV=iCustom(Symbol(),PERIOD_H1,"QuantumSuperChannel v1.09",3,1);
int openrsi=0;
int cierrersi=0;
if(Buffer1[1]==1)Buffer1[0]=1;
if(Buffer1[1]==2)Buffer1[0]=2;
if(rsiGp>70&&rsiG<rsiGp&&rsiG2<rsiG)Buffer1[0]=2;
if(rsiGp<30&&rsiG>rsiGp&&rsiG2>rsiG)Buffer1[0]=1;

if(Buffer4[1]==1)Buffer4[0]=1;
if(Buffer4[1]==2)Buffer4[0]=2;
if(rsiG3p>70&&rsiG3<rsiG3p&&rsiG32<rsiG3)Buffer4[0]=2;
if(rsiG3p<30&&rsiG3>rsiG3p&&rsiG32>rsiG3)Buffer4[0]=1;

if(Buffer5[1]==1)Buffer5[0]=1;
if(Buffer5[1]==2)Buffer5[0]=2;
if(rsiG4p>70&&rsiG4<rsiG4p&&rsiG42<rsiG4)Buffer5[0]=2;
if(rsiG4p<30&&rsiG4>rsiG4p&&rsiG42>rsiG4)Buffer5[0]=1;

int tendrsi=Buffer1[0];
int tendrsi2=Buffer4[0];
int tendrsi3=Buffer5[0];

// if(rsiM>50&&Buffer1[0]==1)tendrsi=1;
// if(rsiM<50&&Buffer1[0]==2)tendrsi=2;
if(rsiP<rsiPp&&rsiPp>60&&tendrsi==1&&tendrsi2==1&&tendrsi3==1)openrsi=2;
if(rsiP>rsiPp&&rsiPp<30&&tendrsi==2&&tendrsi2==2&&tendrsi3==2)openrsi=1;
if(rsiC<rsiCP&&rsiCP>60)cierrersi=1;
if(rsiC>rsiCP&&rsiCP<30)cierrersi=2;
//
// if((Ask>pivotNB&&Ask<pivotNT)||(Bid>pivotNB&&Bid<pivotNT))extremo=5;
// if(Ask<pivotNB||Bid<pivotNB)extremo=4;
// if(Ask>pivotNT||Bid>pivotNT)extremo=1;
int tend=0;
if(avramisA>avramisB&&avramisA2>avramisB2)tend=1;
if(avramisA<avramisB&&avramisA2<avramisB2)tend=2;
//printf("ex"+extremo);
printf(tendrsi+" - "+rsiP);
//if(extremo==5){



double dinerito=0;
  if(OrdersTotal()>0){
    for(int cnt;cnt<OrdersTotal();cnt++){
      OrderSelect(cnt,SELECT_BY_POS,MODE_TRADES);
      dinerito=OrderProfit()+dinerito;
    }
  }
  if(dinerito<0){
    // if(tendrsi3==2)Buffer2[0]=1;
    // if(tendrsi3==1)Buffer2[0]=2;
  }else{
    if(BuyArrow!=0&&openrsi==1){//&&tend==1
      Buffer2[0]=1;
    }
    if(SellArrow!=0&&openrsi==2){//&&tend==2
      Buffer2[0]=2;
    }
  }


//}

// if(avramisA2>avramisB2){//extremo==1
//   Buffer3[0]=2;
// }
// if(avramisA2<avramisB2){//extremo==4
//   Buffer3[0]=1;
// }

// if(BuyArrowC!=0&&BuyArrowC!=EMPTY_VALUE&&c1semaforindv2B2!=0&&c1semaforindv2B2!=EMPTY_VALUE){//c1semaforindv2B2!=0&&c1semaforindv2B2!=EMPTY_VALUE
// Buffer3[0]=2;
// }
// if(SellArrowC!=0&&SellArrowC!=EMPTY_VALUE&&c1semaforindv2S2!=0&&c1semaforindv2S2!=EMPTY_VALUE){//c1semaforindv2S2!=0&&c1semaforindv2S2!=EMPTY_VALUE
// Buffer3[0]=1;
// }


// if(tendrsi==1){//c1semaforindv2B2!=0&&c1semaforindv2B2!=EMPTY_VALUE
// Buffer3[0]=2;
// }
// if(tendrsi==2){//c1semaforindv2S2!=0&&c1semaforindv2S2!=EMPTY_VALUE
// Buffer3[0]=1;
// }
// if(c1semaforindv2B2!=0&&c1semaforindv2B2!=EMPTY_VALUE){
//   Buffer3[0]=2;
// }
// if(c1semaforindv2S2!=0&&c1semaforindv2S2!=EMPTY_VALUE){
//   Buffer3[0]=1;
// }
if(dinerito<0){
  //NO CERRAR HAY PERDIDA MUYAYO
}else{

}
if(tendrsi3==2)Buffer3[0]=2;
if(tendrsi3==1)Buffer3[0]=1;
if(BuyArrowC!=EMPTY_VALUE)Buffer3[0]=2;
if(SellArrowC!=EMPTY_VALUE)Buffer3[0]=1;

  }
//+------------------------------------------------------------------+
//RESULTADOS ESTRATEGIA
//h4 y m30 va bien 2014

//D1 y H1 va bien 2014

//D1 y H1 va bien 2015

//problema en 2015

//M30 y H1 con Avramis de h4 y m30 va bien 2015
