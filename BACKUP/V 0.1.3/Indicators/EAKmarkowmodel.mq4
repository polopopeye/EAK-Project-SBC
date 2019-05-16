//+------------------------------------------------------------------+
//|                                               MarkowModel.mq4 |
//|                        Copyright 2019, EAKV2. |
//|                                             |
//+------------------------------------------------------------------+
#property copyright "Copyright 2019, EAKV2"
#property link      "https://xvideos.com/"
#property version   "1.00"
#property strict
#property indicator_chart_window
#property indicator_buffers 8
double Buffer1[];
double Buffer2[];
double Buffer3[];
double Buffer4[];
double Buffer5[];
double Buffer6[];
double Buffer7[];
double Buffer8[];


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
SetIndexLabel(0,"TA");

SetIndexBuffer(1,Buffer2);
SetIndexEmptyValue(1,0.0);
SetIndexLabel(1,"TP");

SetIndexBuffer(2,Buffer3);
SetIndexEmptyValue(2,0.0);
SetIndexLabel(2,"steadystate1");

SetIndexBuffer(3,Buffer4);
SetIndexEmptyValue(3,0.0);
SetIndexLabel(3,"steadystate2");

SetIndexBuffer(4,Buffer5);
SetIndexEmptyValue(4,0.0);
SetIndexLabel(4,"OP");

SetIndexBuffer(5,Buffer6);
SetIndexEmptyValue(5,0.0);
SetIndexLabel(5,"COP");

SetIndexBuffer(6,Buffer7);
SetIndexEmptyValue(6,0.0);
SetIndexLabel(6,"riesgo");

SetIndexBuffer(7,Buffer8);
SetIndexEmptyValue(7,0.0);
SetIndexLabel(7,"Probabilidad");

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


//Buffer1[P1ma1v1]=iMA(Symbol(),PERIOD_CURRENT,P1ma1v1,0,0,PRICE_LOW,0);
//High[], Low[], Open[], Close[]
//Buffer1[1]=Open[1];

//primero hay que sacar el precio medio de un lapso.
//este lapso hay que dividirlo en 3 partes.
//10 10 10 por ejemplo
int lapso=200,ciclo=lapso*3;
int lapso1=(ciclo/3)*1,lapso2=(ciclo/3)*2,lapso3=(ciclo/3)*3;
double TprecioA,TprecioB,TprecioC,precioMedioA,precioMedioB,precioMedioC;

for(int cnta=0;cnta<lapso1;cnta++){
//aqui se saca la media para poder comparar posteriormente
TprecioA=Open[cnta]+TprecioA;
}
precioMedioA=TprecioA/lapso;
for(int cntb=lapso1;cntb<lapso2;cntb++){
TprecioB=Open[cntb]+TprecioB;
}
precioMedioB=TprecioB/lapso;

for(int cntc=lapso2;cntc<lapso3;cntc++){
TprecioC=Open[cntc]+TprecioC;
}
precioMedioC=TprecioC/lapso;

double tendenciaActual=0,tendenciaPasada=0,tendenciaFutura=0;


// Tendencia Pasada
if(precioMedioC<precioMedioB){
tendenciaPasada=1;
}
if(precioMedioC>precioMedioB){
tendenciaPasada=2;
}
// Tendencia Actual
if(precioMedioB<precioMedioA){
  tendenciaActual=1;
}
if(precioMedioB>precioMedioA){
  tendenciaActual=2;
}

// Tendencia Futura
Buffer1[0]=tendenciaActual;
Buffer2[0]=tendenciaPasada;

double contador1=0,contador2=0;
double prtendactual1,prtendactual2,prtendpasada1,prtendpasada2;
for(int cnt1=0;cnt1<ciclo;cnt1++){
if(Buffer1[cnt1]==1){
  contador1++;
}
if(Buffer2[cnt1]==1){
  contador2++;
}
}
 prtendactual1=contador1/ciclo;//compra actual porcentaje
 prtendpasada1=contador2/ciclo;//compra pasada porcentaje
 prtendactual2=1-prtendactual1;//compra actual porcentaje
 prtendpasada2=1-prtendpasada1;//compra pasada porcentaje

//la idea es sacar el steady state value. para determinar que es mejor.
double steadystate1,steadystate2,arbitratgeC,arbitratgeV;
double exitoC,exitoV,exitoC1,exitoV1;

if(prtendpasada2>0&&prtendactual1>0)steadystate1=(prtendpasada2/((prtendactual1-prtendpasada2)-1))*-1;
if(steadystate1>0)steadystate2=1-steadystate1;


double semaforindv2B = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,4,1);//COMPRA
double semaforindv2S = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,5,1);//VENTA

//APERTURA
if(steadystate1>0.55&&semaforindv2B!=EMPTY_VALUE&&semaforindv2B!=0)Buffer5[0]=1;
if(steadystate2>0.55&&semaforindv2S!=EMPTY_VALUE&&semaforindv2S!=0)Buffer5[0]=2;
//CIERRE
if(steadystate1>0.55&&semaforindv2B!=EMPTY_VALUE&&semaforindv2B!=0)Buffer6[0]=2;
if(steadystate2>0.55&&semaforindv2S!=EMPTY_VALUE&&semaforindv2S!=0)Buffer6[0]=1;


double expectedvalue1,expectedvalue2;

if(steadystate1>0.5){
  expectedvalue1=iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,4,0);// LINEA ARRIBA
  expectedvalue2=iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,3,0);// LINEA ABAJO
}
if(steadystate2>0.5){
  expectedvalue1=iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,3,0);// LINEA ARRIBA
  expectedvalue2=iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,4,0);// LINEA ABAJO
}

if(steadystate1>0&&expectedvalue1>0&&expectedvalue2>0){
  double interestrates=expectedvalue1/precioMedioA;
  double riesgo=MathSqrt(interestrates/2);
  double probabilidad=(precioMedioA-expectedvalue2)/(expectedvalue1-expectedvalue2);

  Buffer7[0]=riesgo;
  Buffer8[0]=probabilidad;
}


//expectedvalue1=
//steadystate2=prtendpasada1/((prtendactual2-prtendpasada1)-1);

// int contador1=0,contador2=0,contador3=0,contador4=0,contador5=0,contador6=0;
// double prtendactual1,prtendpasada1,prtendactual2,prtendpasada2,prtendactual3,prtendpasada3;
// for(int cnt1=0;cnt1<lapso1;cnt1++){
// if(Buffer1[cnt1]==1){
//   contador1=1+contador1;
// }
// if(Buffer2[cnt1]==1){
//   contador2=1+contador2;
// }
// }
// prtendactual1=contador1/lapso;
// prtendpasada1=contador2/lapso;
//
// for(int cnt2=lapso1;cnt2<lapso2;cnt2++){
//   if(Buffer1[cnt2]==1){
//     contador3=1+contador3;
//   }
//   if(Buffer2[cnt2]==1){
//     contador4=1+contador4;
//   }
// }
// prtendactual2=contador3/lapso;
// prtendpasada2=contador4/lapso;
//
// for(int cnt3=lapso2;cnt3<lapso3;cnt3++){
//   if(Buffer1[cnt3]==1){
//     contador5=1+contador5;
//   }
//   if(Buffer2[cnt3]==1){
//     contador6=1+contador6;
//   }
// }
// prtendactual3=contador5/lapso;
// prtendpasada3=contador6/lapso;
//
// //
//
// if(prtendactual1>prtendactual2){
//
// }
Buffer3[0]=steadystate1;
Buffer4[0]=steadystate2;

  }
//+------------------------------------------------------------------+
