//+------------------------------------------------------------------+
//|                                               CanalDow.mq4 |
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
SetIndexLabel(0,"LUP");

SetIndexBuffer(1,Buffer2);
SetIndexEmptyValue(1,0.0);
SetIndexLabel(1,"LDOWN");


SetIndexBuffer(2,Buffer3);
SetIndexEmptyValue(2,0.0);
SetIndexLabel(2,"Operacion");

SetIndexBuffer(3,Buffer4);
SetIndexEmptyValue(3,0.0);
SetIndexLabel(3,"Riesgo");

SetIndexBuffer(4,Buffer5);
SetIndexEmptyValue(4,0.0);
SetIndexLabel(4,"Probabilidad");

SetIndexBuffer(5,Buffer6);
SetIndexEmptyValue(5,0.0);
SetIndexLabel(5,"CierreOP");

SetIndexBuffer(6,Buffer7);
SetIndexEmptyValue(6,0.0);
SetIndexLabel(6,"Tiempo");

SetIndexBuffer(7,Buffer8);
SetIndexEmptyValue(7,0.0);
SetIndexLabel(7,"Tend");


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
double expectedvalue1,expectedvalue2;
string Fcanaltend=Symbol()+"canaltend.eakdb";


// iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,1,0);//Pequño arriba
// Buffer2[0]=iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,2,0);//Pequeño Abajo
Buffer1[0]=iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,3,0);// LINEA ARRIBA
Buffer2[0]=iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,4,0);// LINEA ABAJO
int tendenciaA=0;
// semaforindv2B = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,4,1);
// //semaforindv2S = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,5,1);
//
//
// if(semaforindv2B==NULL||semaforindv2B==EMPTY_VALUE){
//   Buffer5[0]=0;
// }else{
//   Buffer5[0]=1;
// }

// if(Buffer5[0]==1){
//   int cicloB=0;
//   int puntoB;
//   for(puntoB=1;Buffer5[puntoB]<1&&cicloB==0;puntoB++){
//     if(puntoB>500)cicloB=1;
//     printf("punto"+puntoB);
//   }
//   if(puntoB>2){
//     cicloB=1;
//   }
//   if(Buffer3[0]>Buffer3[puntoB]&&Buffer4[0]>Buffer4[puntoB]){
//     //Tendencia Alcista
//     tendenciaA=1;
//   }
//   if(Buffer3[0]<Buffer3[puntoB]&&Buffer4[0]<Buffer4[puntoB]){
//     //Tendencia Bajista
//     tendenciaA=2;
//   }
// }

// if(Buffer1[100]!=EMPTY_VALUE&&Buffer2[100]!=EMPTY_VALUE){
//   if(Buffer1[0]>Buffer1[100]&&Buffer2[0]>Buffer2[100]){
//     //Tendencia Alcista
//     tendenciaA=1;
//   }
//   if(Buffer1[0]<Buffer1[100]&&Buffer2[0]<Buffer2[100]){
//     //Tendencia Bajista
//     tendenciaA=2;
//   }
// }


if(Buffer8[1]==1||Buffer8[1]==2){
  tendenciaA=Buffer8[1];
}
//
// if(FileIsExist(Fcanaltend)==true){
//   string canaldowR = FileOpen(Fcanaltend,FILE_READ);
//   if(canaldowR==INVALID_HANDLE){
//   printf("canaldowR 1");
//   }else{
//    string canaldowR2 = FileReadString(canaldowR);
//    tendenciaA=canaldowR2;
//   FileClose(canaldowR);
//   }
// }

int cntA=5;
int cntB=5;
double semaforindv2B,semaforindv2S,semaforindv2B2,semaforindv2S2;
semaforindv2B = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,4,1);//COMPRA
semaforindv2S = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,5,1);//VENTA
semaforindv2B2 = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,4,cntA);//COMPRA
semaforindv2S2 = iCustom(Symbol(),PERIOD_M5,"semaforov2eak",50,100,200,5,cntB);//VENTA


if(semaforindv2B!=EMPTY_VALUE){
  for( ;cntA<100;cntA++){
    if(semaforindv2B2!=EMPTY_VALUE&&semaforindv2B2<semaforindv2B){
      tendenciaA=1;

      // string canaltendB = FileOpen(Fcanaltend,FILE_WRITE);
      //  if(canaltendB==INVALID_HANDLE){
      // printf("canaltend Error 1");
      // }else{
      //   string FWcanaltendB = 1;
      //           FileWrite(canaltendB,FWcanaltendB);
      //           FileClose(canaltendB);
      //       //  printf("TENDENCIA CAMBIADA a 1");
      //
      //    }
    }
    if(semaforindv2B2!=EMPTY_VALUE&&semaforindv2B2>semaforindv2B){
      tendenciaA=2;

    }

}
}
if(semaforindv2S!=EMPTY_VALUE){
for( ;cntB<100;cntB++){
  if(semaforindv2S2!=EMPTY_VALUE&&semaforindv2S2>semaforindv2S){

    tendenciaA=2;

      // string canaltendS = FileOpen(Fcanaltend,FILE_WRITE);
      //  if(canaltendS==INVALID_HANDLE){
      // printf("canaltend Error 2");
      // }else{
      //   string FWcanaltendS = 2;
      //           FileWrite(canaltendS,FWcanaltendS);
      //           FileClose(canaltendS);
      //       //    printf("TENDENCIA CAMBIADA a 2");
      //
      //    }
  }
  if(semaforindv2S2!=EMPTY_VALUE&&semaforindv2S2<semaforindv2S){
    tendenciaA=1;
  }
}
}

double interestrates,riesgoporcrecimiento,riesgo,probabilidad;

if(tendenciaA==1&&(Open[0]<Buffer2[0]||Close[0]<Buffer2[0])){
Buffer3[0]=1;
//printf("Compra");

expectedvalue1=iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,1,0);
expectedvalue2=Open[0]/1.1;

interestrates=expectedvalue1/Open[0];
riesgoporcrecimiento=interestrates/2;
riesgo=MathSqrt(riesgoporcrecimiento);
probabilidad=(Open[0]-expectedvalue2)/(expectedvalue1-expectedvalue2);

}
if(tendenciaA==2&&(Open[0]>Buffer1[0]||Close[0]>Buffer1[0])){
Buffer3[0]=2;
//printf("Venta");
expectedvalue1=iCustom(Symbol(),PERIOD_M5,"cog",125,2,0,0.8,1102,2,0);
expectedvalue2=Open[0]*1.1;

interestrates=expectedvalue1/Open[0];
riesgoporcrecimiento=interestrates/2;
riesgo=MathSqrt(riesgoporcrecimiento);
probabilidad=(Open[0]-expectedvalue2)/(expectedvalue1-expectedvalue2);
}

// printf("exv1: "+expectedvalue1+"exv2: "+expectedvalue2);
// printf("pr"+probabilidad);
//Buffer4[0]=expectedvalue1;
//Buffer5[0]=expectedvalue2;
double orderprofittotal,tiempomediotodasoperaciones2,tiempomediotodasoperaciones1=0;
int tiempooperacionsola,contadoroperaciones;
for(int cntb=0;cntb<OrdersTotal();cntb++){
  OrderSelect(cntb,SELECT_BY_POS,MODE_TRADES);
  if(OrderSymbol()==Symbol()&&OrderComment()=="S3"){
    contadoroperaciones++;
    orderprofittotal=orderprofittotal+OrderProfit();
    tiempooperacionsola=OrderCloseTime()-OrderOpenTime();
    tiempomediotodasoperaciones2=tiempooperacionsola+tiempomediotodasoperaciones2;
  }
}
if(contadoroperaciones>0)tiempomediotodasoperaciones1=tiempomediotodasoperaciones2/contadoroperaciones;

int cierreop=0;
if(Buffer3[0]==1)cierreop=2;
if(Buffer3[0]==2)cierreop=1;
if(orderprofittotal>0){
  Buffer4[0]=riesgo;
}else{
  Buffer4[0]=riesgo*1.1;
}
Buffer5[0]=probabilidad;
Buffer6[0]=cierreop;
Buffer7[0]=tiempomediotodasoperaciones1;
Buffer8[0]=tendenciaA;
  }
//+------------------------------------------------------------------+
