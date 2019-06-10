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


        double stB = 1;//compra
        double stS = 1;//compra

    double pivotN = iCustom(Symbol(),PERIOD_M5,"Pivot_Voty",1440,3,0);//43200 10080 1440
    double pivotNT = iCustom(Symbol(),PERIOD_M5,"Pivot_Voty",1440,1,0);//43200 10080 1440
    double pivotNB = iCustom(Symbol(),PERIOD_M5,"Pivot_Voty",1440,5,0);//43200 10080 1440

    double rsiG= iRSI(Symbol(),PERIOD_M5,4,PRICE_CLOSE,0);//Recomiendan h4
    double rsiG2= iRSI(Symbol(),PERIOD_M5,4,PRICE_CLOSE,1);//Recomiendan h4
    double rsiGp= iRSI(Symbol(),PERIOD_M5,4,PRICE_CLOSE,2);//Recomiendan h4

    double rsiG3= iRSI(Symbol(),PERIOD_M5,7,PRICE_CLOSE,0);//Recomiendan h4
    double rsiG32= iRSI(Symbol(),PERIOD_M5,7,PRICE_CLOSE,1);//Recomiendan h4
    double rsiG3p= iRSI(Symbol(),PERIOD_M5,7,PRICE_CLOSE,2);//Recomiendan h4

    double rsiG4= iRSI(Symbol(),PERIOD_M5,32,PRICE_CLOSE,0);//Recomiendan h4
    double rsiG42= iRSI(Symbol(),PERIOD_M5,32,PRICE_CLOSE,1);//Recomiendan h4
    double rsiG4p= iRSI(Symbol(),PERIOD_M5,32,PRICE_CLOSE,2);//Recomiendan h4

    double rsiM= iRSI(Symbol(),PERIOD_H1,14,PRICE_CLOSE,0);

    double rsiP= iRSI(Symbol(),PERIOD_M5,70,PRICE_CLOSE,0);

    //double rsiP= iCustom(Symbol(),PERIOD_M5,"RMI",56,20,0,0);

    double rsiPp= iRSI(Symbol(),PERIOD_M5,55,PRICE_CLOSE,1);
    double rsiPpp= iRSI(Symbol(),PERIOD_M5,55,PRICE_CLOSE,2);
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


    if(rsiP<rsiPp&&rsiPp>60&&tendrsi==1&&tendrsi2==1&&tendrsi3==1)openrsi=2;
    if(rsiP>rsiPp&&rsiPp<30&&tendrsi==2&&tendrsi2==2&&tendrsi3==2)openrsi=1;
    if(rsiC<rsiCP&&rsiCP>60)cierrersi=1;
    if(rsiC>rsiCP&&rsiCP<30)cierrersi=2;
//
// Este sistema utiliza soportes y resistencias cortos para abrir posiciones.
// en principio...
// se utiliza tendencia RSI a corto plazo. para mejorar la apertura de posiciones.
// (se podria utilizar el precio de pivotes estandar para evitar el funcionamiento en extremos).

double dinerito=0;


double livelliT = iCustom(Symbol(),PERIOD_M1,"livelli_sr_now",15,135,0,1);//12 48 24 96
double livelliB = iCustom(Symbol(),PERIOD_M1,"livelli_sr_now",15,135,1,1);//6 24
double livelliT2 = iCustom(Symbol(),PERIOD_M5,"livelli_sr_now",75,700,0,1);//12 48 24 96 30 170
double livelliB2 = iCustom(Symbol(),PERIOD_M5,"livelli_sr_now",75,700,1,1);//6 24
    // double livelliT = iCustom(Symbol(),PERIOD_M1,"livelli_sr_now",275,615,0,1);//12 48 24 96
    // double livelliB = iCustom(Symbol(),PERIOD_M1,"livelli_sr_now",275,615,1,1);//6 24
double priceC=Ask;
double priceV=Bid;
int livelliopC=0;
int livelliopV=0;

if(livelliB<priceC&&rsiP<50&&tendrsi==2&&tendrsi2==2&&tendrsi3==2){//livelliB<priceC&&tendrsi==2
  //Comprar o si existe compra mantener la compra.rsiPpp<50&&rsiPp>rsiPpp&&
  livelliopC=1;
}
if(livelliT>priceV&&rsiP>50&&tendrsi==1&&tendrsi2==1&&tendrsi3==2){//livelliT>priceV&&tendrsi==1
  //Comprar o si existe compra mantener la compra.rsiPpp>50&&rsiPp<rsiPpp&&
  livelliopV=1;
}


if(OrdersTotal()>0){
  for(int cnt;cnt<OrdersTotal();cnt++){
    OrderSelect(cnt,SELECT_BY_POS,MODE_TRADES);
    dinerito=OrderProfit()+dinerito;
  if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()){
    if(livelliB<priceC){
      livelliopC=3;
    }
  }
  if(OrderType()==OP_SELL&&OrderSymbol()==Symbol()){
    if(livelliT>priceV){
      livelliopV=3;
    }
  }
}
}

if(livelliB2>priceC){
  livelliopC=2;
}
if(livelliT2<priceV){
  livelliopV=2;
}

//printf(livelliopC+" - "+livelliopV+" - "+livelliT+" - "+livelliB);









//printf(tendrsi+" - "+rsiP);





//---------------------------------------------------------
//EJECUCION
//---------------------------------------------------------

if(livelliopC==1){//&&tend==1
  Buffer2[0]=1;
}
if(livelliopV==1){//&&tend==2
  Buffer2[0]=2;
}

if(livelliopC==2){
  Buffer3[0]=1;
}
if(livelliopV==2){
  Buffer3[0]=2;
}


  }
//+------------------------------------------------------------------+
//RESULTADOS ESTRATEGIA
//2014 1 todo h1
//el punto esta en 26 de Junio
