//+------------------------------------------------------------------+
//|                                               EAKoceantrend1.mq4 |
//|                        Copyright 2019, MetaQuotes Software Corp. |
//|                                             https://www.mql5.com |
//+------------------------------------------------------------------+
#property copyright "Copyright 2019, MetaQuotes Software Corp."
#property link      "https://www.mql5.com"
#property version   "1.00"
#property strict
#property indicator_chart_window
#property indicator_buffers 9
double Buffer1[];
double Buffer2[];
double Buffer3[];
double Buffer4[];
double Buffer5[];
double Buffer6[];
double Buffer7[];
double Buffer8[];
double Buffer9[];

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
SetIndexLabel(0,"EAK C");

SetIndexBuffer(1,Buffer2);
SetIndexEmptyValue(1,0.0);
SetIndexLabel(1,"EAK V");

SetIndexBuffer(2,Buffer3);
SetIndexEmptyValue(2,0.0);
SetIndexLabel(2,"Degrees C");

SetIndexBuffer(3,Buffer4);
SetIndexEmptyValue(3,0.0);
SetIndexLabel(3,"Degrees V");

SetIndexBuffer(4,Buffer5);
SetIndexEmptyValue(4,0.0);
SetIndexLabel(4,"P1ma1v1");

SetIndexBuffer(5,Buffer6);
SetIndexEmptyValue(5,0.0);
SetIndexLabel(5,"P1ma1v2");

SetIndexBuffer(6,Buffer7);
SetIndexEmptyValue(6,0.0);
SetIndexLabel(6,"OP");

SetIndexBuffer(7,Buffer8);
SetIndexEmptyValue(7,0.0);
SetIndexLabel(7,"COP");

SetIndexBuffer(8,Buffer9);
SetIndexEmptyValue(8,0.0);
SetIndexLabel(8,"Tend");

ObjectCreate(0,Symbol()+"trendVenta",OBJ_TRENDBYANGLE,0,0,1,0,0);
ObjectSetInteger(0,Symbol()+"trendVenta",OBJPROP_COLOR,Red);
 ObjectSetInteger(0,Symbol()+"trendVenta",OBJPROP_STYLE,STYLE_SOLID);
  ObjectSetInteger(0,Symbol()+"trendVenta",OBJPROP_WIDTH,3);
  ObjectSetInteger(0,Symbol()+"trendVenta",OBJPROP_SELECTABLE,false);
   ObjectSetInteger(0,Symbol()+"trendVenta",OBJPROP_HIDDEN,true);
ObjectSetInteger(0,Symbol()+"trendVenta",OBJPROP_RAY_RIGHT,false);

   ObjectCreate(0,Symbol()+"trendCompra",OBJ_TRENDBYANGLE,0,0,1,0,0);
   ObjectSetInteger(0,Symbol()+"trendCompra",OBJPROP_COLOR,Blue);
    ObjectSetInteger(0,Symbol()+"trendCompra",OBJPROP_STYLE,STYLE_SOLID);
     ObjectSetInteger(0,Symbol()+"trendCompra",OBJPROP_WIDTH,3);
     ObjectSetInteger(0,Symbol()+"trendCompra",OBJPROP_SELECTABLE,false);
      ObjectSetInteger(0,Symbol()+"trendCompra",OBJPROP_HIDDEN,true);
      ObjectSetInteger(0,Symbol()+"trendCompra",OBJPROP_RAY_RIGHT,false);


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
    int P1ma1v1,P1ma1v2;


if(Buffer5[1]!=0){
  P1ma1v1=Buffer5[1];
}else{
  if(Buffer5[2]!=0){
    P1ma1v1=Buffer5[2];
  }else{
    P1ma1v1=27;
  }
}
if(Buffer6[1]!=0){
  P1ma1v2=Buffer6[1];
}else{
  if(Buffer6[2]!=0){
    P1ma1v2=Buffer6[2];
  }else{
    P1ma1v2=27;
  }
}

int m1=P1ma1v1;
int m2=P1ma1v2;
if(m1*3>700){
  P1ma1v1=P1ma1v1/3;
}
if(m2*3>700){
  P1ma1v2=P1ma1v2/3;
}



double  m1231=iMA(Symbol(),PERIOD_CURRENT,m1,0,0,PRICE_LOW,0);
double  m1232=iMA(Symbol(),PERIOD_CURRENT,m2,0,0,PRICE_HIGH,0);
double  m1233=iMA(Symbol(),PERIOD_CURRENT,m1,0,0,PRICE_LOW,m1);
double  m1234=iMA(Symbol(),PERIOD_CURRENT,m2,0,0,PRICE_HIGH,m2);
//ArrayResize(Buffer1,100000,100000);
//ArrayResize(Buffer2,100000,100000);
Buffer1[0]=m1231;
Buffer2[0]=m1232;
Buffer1[m1]=m1233;
Buffer2[m2]=m1234;
//Buffer1[P1ma1v1]=iMA(Symbol(),PERIOD_CURRENT,P1ma1v1,0,0,PRICE_LOW,0);
//High[], Low[], Open[], Close[]
//Buffer1[1]=Open[1];

//Alert("NUEVO TICK!");
ObjectMove(0,Symbol()+"trendCompra",1,Time[0],Buffer1[0]);
ObjectMove(0,Symbol()+"trendCompra",0,Time[m1],Buffer1[m1]);

ObjectMove(0,Symbol()+"trendVenta",1,Time[0],Buffer2[0]);
ObjectMove(0,Symbol()+"trendVenta",0,Time[m2],Buffer2[m2]);

int timec1=Time[m1];
int timec2=Time[0];
int timev1=Time[m2];
int timev2=Time[0];
int tiempo1=(timec2-timec1)/60;
int tiempo2=(timev2-timev1)/60;

int tendencia1=0;

if(m1>m2){
  if(Buffer1[0]<Buffer1[m1]&&Buffer2[0]>Buffer2[m2])tendencia1++;
  if(Buffer1[0]>Buffer1[m1]&&Buffer2[0]>Buffer2[m2])tendencia1++;
  if(Buffer1[0]>Buffer1[m1]&&Buffer2[0]<Buffer2[m2])tendencia1=0;
}
if(m2>m1){
  if(Buffer2[0]<Buffer2[m2]&&Buffer1[0]>Buffer1[m1])tendencia1--;
  if(Buffer1[0]<Buffer1[m1]&&Buffer2[0]<Buffer2[m2])tendencia1--;
  if(Buffer2[0]>Buffer2[m2]&&Buffer1[0]<Buffer1[m1])tendencia1=0;
}



Buffer9[0]=tendencia1;
//printf("tend"+tendencia1);



//double radiansC=;
//double radiansV=;
//double degreesV=MathArctan(((Buffer2[P1ma1v2]-Buffer2[0])*20000) / P1ma1v2);
//double pendientev=180*degreesV/MathArccos(-1.0);

int cnta=0;
int cntb=0;
double degreesC=0;
double pendientec=0;
double degreesV=0;
double pendientev=0;
for(int cnta=0;cnta<700;cnta++){
  degreesC=MathArctan(((Buffer1[0]-Buffer1[P1ma1v1])*20000) / P1ma1v1);
  pendientec=180*degreesC/MathArccos(-1.0);
  if((pendientec<40&&pendientec>5)||(pendientec>70)||(pendientec<-5)){ //de 6 a 39º
P1ma1v1=P1ma1v1+1;
  }

}
for(int cntb=0;cntb<700;cntb++){
   degreesV=MathArctan(((Buffer2[P1ma1v2]-Buffer2[0])*20000) / P1ma1v2);
   pendientev=180*degreesV/MathArccos(-1.0);
  if((pendientev<40&&pendientev>5)||(pendientev>70)||(pendientev<-5)){
P1ma1v2=P1ma1v2+1;
  }

}
if((pendientec>40&&pendientec<70)||(pendientec>-5&&pendientec<5)){ //o neutro o
  Buffer5[0]=P1ma1v1;
}
if((pendientev>40&&pendientev<70)||(pendientev>-5&&pendientev<5)){
  Buffer6[0]=P1ma1v2;
}




Buffer4[0]=pendientev;
Buffer3[0]=pendientec;


//  quiero que siempre busque y encuentre el 45º ->
//todo va en funcion a los grados actuales y fuerza aztual.




double semaforindv2B = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,4,1);//COMPRA
double semaforindv2S = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,5,1);//VENTA


if(tendencia1>0&&semaforindv2B!=EMPTY_VALUE){
  Buffer7[0]=1;
  Buffer8[0]=2;
}
if(tendencia1<0&&semaforindv2S!=EMPTY_VALUE){
  Buffer7[0]=2;
  Buffer8[0]=1;
}




  }
//+------------------------------------------------------------------+
