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
#property indicator_buffers 10
extern int activadasestrategias=5;
double Buffer1[],Buffer2[],Buffer3[],Buffer4[],Buffer5[],Buffer6[],Buffer7[],Buffer8[],Buffer9[],Buffer10[];




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
SetIndexLabel(0,"1PF (MEJOR)");

SetIndexBuffer(1,Buffer2);
SetIndexEmptyValue(1,0.0);
SetIndexLabel(1,"2PF");

SetIndexBuffer(2,Buffer3);
SetIndexEmptyValue(2,0.0);
SetIndexLabel(2,"3PF");

SetIndexBuffer(3,Buffer4);
SetIndexEmptyValue(3,0.0);
SetIndexLabel(3,"4PF");

SetIndexBuffer(4,Buffer5);
SetIndexEmptyValue(4,0.0);
SetIndexLabel(4,"5PF (PEOR)");

SetIndexBuffer(5,Buffer6);
SetIndexEmptyValue(5,0.0);
SetIndexLabel(5,"1NOTA (MEJOR)");

SetIndexBuffer(6,Buffer7);
SetIndexEmptyValue(6,0.0);
SetIndexLabel(6,"2NOTA");

SetIndexBuffer(7,Buffer8);
SetIndexEmptyValue(7,0.0);
SetIndexLabel(7,"3NOTA");

SetIndexBuffer(8,Buffer9);
SetIndexEmptyValue(8,0.0);
SetIndexLabel(8,"4NOTA");

SetIndexBuffer(9,Buffer10);
SetIndexEmptyValue(9,0.0);
SetIndexLabel(9,"5NOTA (PEOR)");


//ObjectCreate(Symbol()+"rmi1",OBJ_LABEL,0,0,0,0);

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
    ushort sep=StringGetCharacter(":",0);
    string Readsistembehavior="none";
    int cntrs=1;
    int str_size;
    string FileDBarchivosRG;
    string ResultarrayS[10];
    double ProfitFactor[10],ProfitFactor2[10],Nota[10],Nota2[10];
    double Tiempo[10];


      for( ;cntrs<=activadasestrategias;cntrs++){
         FileDBarchivosRG="RS"+cntrs+Symbol()+".eakdb";
      if(FileIsExist(FileDBarchivosRG)){
        string Rbehavior1read = FileOpen(FileDBarchivosRG,FILE_READ);
        if(Rbehavior1read==INVALID_HANDLE){
        printf("behavior1read 1");
        }else{
        str_size=FileReadInteger(Rbehavior1read,INT_VALUE);
        Readsistembehavior = FileReadString(Rbehavior1read,str_size);
        FileClose(Rbehavior1read);


        }
        StringSplit(Readsistembehavior,sep,ResultarrayS);
        ProfitFactor[cntrs]=ResultarrayS[0];//PF
        ProfitFactor2[cntrs]=ResultarrayS[0];//PF
        Nota[cntrs]=ResultarrayS[1];//NOTA
        Nota2[cntrs]=ResultarrayS[1];//NOTA
        // Tiempo[cntrs]=ResultarrayS[2];//TIEMPO

      }

      }


    if(ArraySort(ProfitFactor2,WHOLE_ARRAY,1,MODE_DESCEND)){
      if(ProfitFactor2[1]==ProfitFactor[1])Buffer1[0]=1;
      if(ProfitFactor2[1]==ProfitFactor[2])Buffer1[0]=2;
      if(ProfitFactor2[1]==ProfitFactor[3])Buffer1[0]=3;
      if(ProfitFactor2[1]==ProfitFactor[4])Buffer1[0]=4;
      if(ProfitFactor2[1]==ProfitFactor[5])Buffer1[0]=5;

      if(ProfitFactor2[2]==ProfitFactor[1])Buffer2[0]=1;
      if(ProfitFactor2[2]==ProfitFactor[2])Buffer2[0]=2;
      if(ProfitFactor2[2]==ProfitFactor[3])Buffer2[0]=3;
      if(ProfitFactor2[2]==ProfitFactor[4])Buffer2[0]=4;
      if(ProfitFactor2[2]==ProfitFactor[5])Buffer2[0]=5;

      if(ProfitFactor2[3]==ProfitFactor[1])Buffer3[0]=1;
      if(ProfitFactor2[3]==ProfitFactor[2])Buffer3[0]=2;
      if(ProfitFactor2[3]==ProfitFactor[3])Buffer3[0]=3;
      if(ProfitFactor2[3]==ProfitFactor[4])Buffer3[0]=4;
      if(ProfitFactor2[3]==ProfitFactor[5])Buffer3[0]=5;

      if(ProfitFactor2[4]==ProfitFactor[1])Buffer4[0]=1;
      if(ProfitFactor2[4]==ProfitFactor[2])Buffer4[0]=2;
      if(ProfitFactor2[4]==ProfitFactor[3])Buffer4[0]=3;
      if(ProfitFactor2[4]==ProfitFactor[4])Buffer4[0]=4;
      if(ProfitFactor2[4]==ProfitFactor[5])Buffer4[0]=5;

      if(ProfitFactor2[5]==ProfitFactor[1])Buffer5[0]=1;
     if(ProfitFactor2[5]==ProfitFactor[2])Buffer5[0]=2;
     if(ProfitFactor2[5]==ProfitFactor[3])Buffer5[0]=3;
     if(ProfitFactor2[5]==ProfitFactor[4])Buffer5[0]=4;
     if(ProfitFactor2[5]==ProfitFactor[5])Buffer5[0]=5;
    }


    if(ArraySort(Nota2,WHOLE_ARRAY,1,MODE_DESCEND)){
      if(Nota2[1]==Nota[1])Buffer6[0]=1;
      if(Nota2[1]==Nota[2])Buffer6[0]=2;
      if(Nota2[1]==Nota[3])Buffer6[0]=3;
      if(Nota2[1]==Nota[4])Buffer6[0]=4;
      if(Nota2[1]==Nota[5])Buffer6[0]=5;

      if(Nota2[2]==Nota[1])Buffer7[0]=1;
      if(Nota2[2]==Nota[2])Buffer7[0]=2;
      if(Nota2[2]==Nota[3])Buffer7[0]=3;
      if(Nota2[2]==Nota[4])Buffer7[0]=4;
      if(Nota2[2]==Nota[5])Buffer7[0]=5;

      if(Nota2[3]==Nota[1])Buffer8[0]=1;
      if(Nota2[3]==Nota[2])Buffer8[0]=2;
      if(Nota2[3]==Nota[3])Buffer8[0]=3;
      if(Nota2[3]==Nota[4])Buffer8[0]=4;
      if(Nota2[3]==Nota[5])Buffer8[0]=5;

      if(Nota2[4]==Nota[1])Buffer9[0]=1;
      if(Nota2[4]==Nota[2])Buffer9[0]=2;
      if(Nota2[4]==Nota[3])Buffer9[0]=3;
      if(Nota2[4]==Nota[4])Buffer9[0]=4;
      if(Nota2[4]==Nota[5])Buffer9[0]=5;

      if(Nota2[5]==Nota[1])Buffer10[0]=1;
     if(Nota2[5]==Nota[2])Buffer10[0]=2;
     if(Nota2[5]==Nota[3])Buffer10[0]=3;
     if(Nota2[5]==Nota[4])Buffer10[0]=4;
     if(Nota2[5]==Nota[5])Buffer10[0]=5;
    }


  }
//+------------------------------------------------------------------+
