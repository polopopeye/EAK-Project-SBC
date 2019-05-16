//+------------------------------------------------------------------+
//|                                        3_Level_ZZ_Semafor.mq4    |
//+------------------------------------------------------------------+
#property copyright "asystem2000"
#property link      "asystem2000@yandex.ru"

// Â îñíîâó ðàñ÷åòà çèãçàãà âçÿò àëãîðèòì klot@mail.ru
// Çà ÷òî åìó îãðîìíîå ñïàñèáî

#property indicator_chart_window
#property indicator_buffers 6
#property indicator_color1 Chocolate
#property indicator_color2 Chocolate
#property indicator_color3 MediumVioletRed
#property indicator_color4 MediumVioletRed
#property indicator_color5 Green
#property indicator_color6 Red

//---- input parameters
extern double Period1=5;
extern double Period2=13;
extern double Period3=34;
extern string   Dev_Step_1="1,3";
extern string   Dev_Step_2="8,5";
extern string   Dev_Step_3="21,12";
extern int Symbol_1_Kod=140;
extern int Symbol_2_Kod=141;
extern int Symbol_3_Kod=142;

//---- buffers
double FP_BuferUp[];
double FP_BuferDn[];
double NP_BuferUp[];
double NP_BuferDn[];
double HP_BuferUp[];
double HP_BuferDn[];
double resumen[];

int F_Period;
int N_Period;
int H_Period;
int Dev1;
int Stp1;
int Dev2;
int Stp2;
int Dev3;
int Stp3;

//+------------------------------------------------------------------+
//| Custom indicator initialization function                         |
//+------------------------------------------------------------------+
int init()
  {
// --------- Êîððåêòèðóåì ïåðèîäû äëÿ ïîñòðîåíèÿ ÇèãÇàãîâ
   if (Period1>0) F_Period=MathCeil(Period1*Period()); else F_Period=0;
   if (Period2>0) N_Period=MathCeil(Period2*Period()); else N_Period=0;
   if (Period3>0) H_Period=MathCeil(Period3*Period()); else H_Period=0;

//---- Îáðàáàòûâàåì 1 áóôåð
   if (Period1>0)
   {



   SetIndexStyle(0,DRAW_ARROW,0,1);
   SetIndexArrow(0,Symbol_1_Kod);
   SetIndexBuffer(0,FP_BuferUp);
   SetIndexEmptyValue(0,0.0);

   SetIndexStyle(1,DRAW_ARROW,0,1);
   SetIndexArrow(1,Symbol_1_Kod);
   SetIndexBuffer(1,FP_BuferDn);
   SetIndexEmptyValue(1,0.0);


   }

//---- Îáðàáàòûâàåì 2 áóôåð
   if (Period2>0)
   {
   SetIndexStyle(2,DRAW_ARROW,0,2);
   SetIndexArrow(2,Symbol_2_Kod);
   SetIndexBuffer(2,NP_BuferUp);
   SetIndexEmptyValue(2,0.0);

   SetIndexStyle(3,DRAW_ARROW,0,2);
   SetIndexArrow(3,Symbol_2_Kod);
   SetIndexBuffer(3,NP_BuferDn);
   SetIndexEmptyValue(3,0.0);
   }
//---- Îáðàáàòûâàåì 3 áóôåð
   if (Period3>0)
   {
   SetIndexStyle(4,DRAW_ARROW,0,4);
   SetIndexArrow(4,Symbol_3_Kod);
   SetIndexBuffer(4,HP_BuferUp);
   SetIndexEmptyValue(4,0.0);
   SetIndexLabel(4,"COMPRA");

   SetIndexStyle(5,DRAW_ARROW,0,4);
   SetIndexArrow(5,Symbol_3_Kod);
   SetIndexBuffer(5,HP_BuferDn);
   SetIndexEmptyValue(5,0.0);
   SetIndexLabel(5,"VENTA");

   }
// Îáðàáàòûâàåì çíà÷åíèÿ äåâèàöèé è øàãîâ
   int CDev=0;
   int CSt=0;
   int Mass[];
   int C=0;
   if (IntFromStr(Dev_Step_1,C, Mass)==1)
      {
        Stp1=Mass[1];
        Dev1=Mass[0];
      }

   if (IntFromStr(Dev_Step_2,C, Mass)==1)
      {
        Stp2=Mass[1];
        Dev2=Mass[0];
      }


   if (IntFromStr(Dev_Step_3,C, Mass)==1)
      {
        Stp3=Mass[1];
        Dev3=Mass[0];
      }
   return(0);
  }
//+------------------------------------------------------------------+
//| Custor indicator deinitialization function                       |
//+------------------------------------------------------------------+
int deinit()
  {
//----

//----
   return(0);
  }

//+------------------------------------------------------------------+
//| Custom indicator iteration function                              |
//+------------------------------------------------------------------+
int start()
  {
   if (Period1>0){
     CountZZ(FP_BuferUp,FP_BuferDn,Period1,Dev1,Stp1);
   }
   if (Period2>0) CountZZ(NP_BuferUp,NP_BuferDn,Period2,Dev2,Stp2);
   if (Period3>0){
     CountZZ(HP_BuferUp,HP_BuferDn,Period3,Dev3,Stp3);

   }
   return(0);
  }
//+------------------------------------------------------------------+
// äîïîëíèòåëüíûå ôóíêöèè
//int Take



//+------------------------------------------------------------------+
//| Ôóíêö ôîðìèðîâàíèÿ ÇèãÇàãà                        |
//+------------------------------------------------------------------+


int CountZZ( double& ExtMapBuffer[], double& ExtMapBuffer2[], int ExtDepth, int ExtDeviation, int ExtBackstep )
  {
   int    shift, back,lasthighpos,lastlowpos;
   double val,res;
   double curlow,curhigh,lasthigh,lastlow;

   for(shift=Bars-ExtDepth; shift>=0; shift--)
     {
      val=Low[Lowest(NULL,0,MODE_LOW,ExtDepth,shift)];
      if(val==lastlow){
val=0.0;
      }
      else
        {
         lastlow=val;
         if((Low[shift]-val)>(ExtDeviation*Point)){
           val=0.0;
         }
         else
           {
            for(back=1; back<=ExtBackstep; back++)
              {
               res=ExtMapBuffer[shift+back];
               if((res!=0)&&(res>val)) ExtMapBuffer[shift+back]=0.0;
              }
           }
        }

          ExtMapBuffer[shift]=val;
      //--- high
      val=High[Highest(NULL,0,MODE_HIGH,ExtDepth,shift)];
      if(val==lasthigh) val=0.0;
      else
        {
         lasthigh=val;
         if((val-High[shift])>(ExtDeviation*Point)) val=0.0;
         else
           {
            for(back=1; back<=ExtBackstep; back++)
              {
               res=ExtMapBuffer2[shift+back];
               if((res!=0)&&(res<val)) ExtMapBuffer2[shift+back]=0.0;
              }
           }
        }
      ExtMapBuffer2[shift]=val;
     }
   // final cutting
   lasthigh=-1; lasthighpos=-1;
   lastlow=-1;  lastlowpos=-1;

   for(shift=Bars-ExtDepth; shift>=0; shift--)
     {
      curlow=ExtMapBuffer[shift];
      curhigh=ExtMapBuffer2[shift];
      if((curlow==0)&&(curhigh==0)) continue;
      //---
      if(curhigh!=0)
        {
         if(lasthigh>0)
           {
            if(lasthigh<curhigh) ExtMapBuffer2[lasthighpos]=0;
            else ExtMapBuffer2[shift]=0;
           }
         //---
         if(lasthigh<curhigh || lasthigh<0)
           {
            lasthigh=curhigh;
            lasthighpos=shift;
           }
         lastlow=-1;
        }
      //----
      if(curlow!=0)
        {
         if(lastlow>0)
           {
            if(lastlow>curlow) ExtMapBuffer[lastlowpos]=0;
            else ExtMapBuffer[shift]=0;
           }
         //---
         if((curlow<lastlow)||(lastlow<0))
           {
            lastlow=curlow;
            lastlowpos=shift;
           }
         lasthigh=-1;
        }
     }



     string fileName=_Symbol+"-"+_Period+"-"+"Csemafor.txt";
     string fileName2=_Symbol+"-"+_Period+"-"+"Vsemafor.txt";


//AQUI BEU

if(HP_BuferUp[0]>0||HP_BuferUp[1]>0){
      // printf("compra");
       string fileHandle1 = FileOpen(fileName,FILE_CSV|FILE_READ | FILE_WRITE);//|FILE_READ| FILE_WRITE
        if(fileHandle1==INVALID_HANDLE){
       printf("Handle Invalido, ERROR 1");
       }else{
         string data1 = "COMPRA";
                 FileWrite(fileHandle1,data1);
                 FileClose(fileHandle1);
          }

     }else{
       string fileHandle11 = FileOpen(fileName,FILE_CSV|FILE_READ | FILE_WRITE);//|FILE_READ| FILE_WRITE
        if(fileHandle11==INVALID_HANDLE){
       printf("Handle Invalido, ERROR 1");
       }else{
         string data11 = "NEUTRO";
                 FileWrite(fileHandle11,data11);
                 FileClose(fileHandle11);
          }
     }

        if(HP_BuferDn[0]>0||HP_BuferDn[1]>0){
       //printf("venta");
       string fileHandle2 = FileOpen(fileName2,FILE_CSV|FILE_READ | FILE_WRITE);//|FILE_READ| FILE_WRITE
        if(fileHandle2==INVALID_HANDLE){
       printf("Handle Invalido, ERROR 2");
       }else{
         string data2 = "VENTA";
                 FileWrite(fileHandle2,data2);
                 FileClose(fileHandle2);
          }

     }else{
       string fileHandle22 = FileOpen(fileName2,FILE_CSV|FILE_READ | FILE_WRITE);//|FILE_READ| FILE_WRITE
        if(fileHandle22==INVALID_HANDLE){
       printf("Handle Invalido, ERROR 22");
       }else{
         string data22 = "NEUTRO";
                 FileWrite(fileHandle22,data22);
                 FileClose(fileHandle22);
          }
     }

//AQUI SEU




     string f2ileName=_Symbol+"-"+_Period+"-"+"C2semafor.txt";
     string f2ileName2=_Symbol+"-"+_Period+"-"+"V2semafor.txt";






     if(NP_BuferUp[0]>0||NP_BuferUp[1]>0){
      // printf("compra");
       string f2ileHandle1 = FileOpen(f2ileName,FILE_CSV|FILE_READ | FILE_WRITE);//|FILE_READ| FILE_WRITE
        if(f2ileHandle1==INVALID_HANDLE){
       printf("Handle Invalido, ERROR 21");
       }else{
         string d2ata1 = "COMPRA";
                 FileWrite(f2ileHandle1,d2ata1);
                 FileClose(f2ileHandle1);
          }

     }else{
       string f2ileHandle11 = FileOpen(f2ileName,FILE_CSV|FILE_READ | FILE_WRITE);//|FILE_READ| FILE_WRITE
        if(f2ileHandle11==INVALID_HANDLE){
       printf("Handle Invalido, ERROR 21");
       }else{
         string d2ata11 = "NEUTRO";
                 FileWrite(f2ileHandle11,d2ata11);
                 FileClose(f2ileHandle11);
          }
     }
     if(NP_BuferDn[0]>0||NP_BuferDn[1]>0){
       //printf("venta");
       string f2ileHandle2 = FileOpen(f2ileName2,FILE_CSV|FILE_READ | FILE_WRITE);//|FILE_READ| FILE_WRITE
        if(f2ileHandle2==INVALID_HANDLE){
       printf("Handle Invalido, ERROR 2");
       }else{
         string d2ata2 = "VENTA";
                 FileWrite(f2ileHandle2,d2ata2);
                 FileClose(f2ileHandle2);
          }

     }else{
       string f2ileHandle22 = FileOpen(f2ileName2,FILE_CSV|FILE_READ | FILE_WRITE);//|FILE_READ| FILE_WRITE
        if(f2ileHandle22==INVALID_HANDLE){
       printf("Handle Invalido, ERROR 22");
       }else{
         string d2ata22 = "NEUTRO";
                 FileWrite(f2ileHandle22,d2ata22);
                 FileClose(f2ileHandle22);
          }
     }
   for(shift=Bars-1; shift>=0; shift--)
     {
      if(shift>=Bars-ExtDepth) ExtMapBuffer[shift]=0.0;
      else
        {
         res=ExtMapBuffer2[shift];
         if(res!=0.0) ExtMapBuffer2[shift]=res;
        }
     }

 }

int Str2Massive(string VStr, int& M_Count, int& VMass[])
  {
    int val=StrToInteger( VStr);
    if (val>0)
       {
         M_Count++;
         int mc=ArrayResize(VMass,M_Count);
         if (mc==0)return(-1);
          VMass[M_Count-1]=val;
         return(1);
       }
    else return(0);
  }


int IntFromStr(string ValStr,int& M_Count, int& VMass[])
  {

    if (StringLen(ValStr)==0) return(-1);
    string SS=ValStr;
    int NP=0;
    string CS;
    M_Count=0;
    ArrayResize(VMass,M_Count);
    while (StringLen(SS)>0)
      {
            NP=StringFind(SS,",");
            if (NP>0)
               {
                 CS=StringSubstr(SS,0,NP);
                 SS=StringSubstr(SS,NP+1,StringLen(SS));

               }
               else
               {
                 if (StringLen(SS)>0)
                    {
                      CS=SS;
                      SS="";
                    }
               }
            if (Str2Massive(CS,M_Count,VMass)==0)
               {
                 return(-2);
               }
      }
    return(1);
  }
