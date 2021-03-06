//+------------------------------------------------------------------+
//|                                                               fAMA.mq4 |
//|                                             Copyright © 2005, Profi_R |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005, Profi_R"
#property link      "rvm_fam@fromru.com"

#property indicator_chart_window
#property indicator_buffers 1
#property indicator_color1 Crimson
//---- input parameters
extern int Range=10;
extern int FastMA=2;
extern int SlowMA=30;
extern int filter=50;
extern int n=4;
extern int h=10;
//---- buffers
double fAMA[];
double mAMA[];
double AMA[];
double  k1,k2;
//+------------------------------------------------------------------+
//| Custom indicator initialization function                               |
//+------------------------------------------------------------------+
int init()
  {
   string short_name; //обявление переменной short_name типа "строковый"
//---- indicators
   IndicatorBuffers(3);
   SetIndexStyle(2,DRAW_LINE);
   SetIndexBuffer(0,fAMA);
   SetIndexBuffer(1,mAMA);
   SetIndexBuffer(2,AMA);
//---- name for DataWindow and indicator subwindow label
   //переменной short_name присваиваем строковое значение равное выражению
   short_name="AMA("+Range+","+FastMA+","+SlowMA+","+filter+","+n+","+h+")";
   //для отображения на графике присвоим индикатору краткое наименование
   IndicatorShortName(short_name);
   SetIndexLabel(0,short_name);//Установим метку для буфера
//----
   SetIndexDrawBegin(0,Range); //установка начальной точки прорисовки для 0 буфера

   k1=2.0/(SlowMA+1);
   k2=2.0/(FastMA+1)-k1;

//----
   return(0);
  }
//+------------------------------------------------------------------+
//| Custom indicator iteration function                                    |
//+------------------------------------------------------------------+
int start()
  {
   int    counted_bars=IndicatorCounted();
//---- TODO: add your code here
   int cb,i,limit;
   double  Noise,ER,SSC,sdAMA,dAMA;
   
   if (counted_bars==0) limit=Bars-Range;
   if (counted_bars>0) limit=Bars-counted_bars;
   limit--;
   
   if(Bars<=Range) return(0);
   else
      {
      AMA[Bars-Range]=Close[Bars-Range];
      mAMA[Bars-Range]=Close[Bars-Range+1];
      //for(cb=Bars-counted_bars-Range-1;cb>=0;cb--)
      
      for(cb=limit;cb>=0;cb--)
         {
         Noise=0;
         for(i=cb;i<=cb+Range-1;i++)
            {
            Noise=Noise+MathAbs(Close[i]-Close[i+1]);
            }
         if(Noise!=0.0) ER=MathAbs(Close[cb]-Close[cb+Range])/Noise; else ER=0;
         
         SSC=(ER*k2+k1);
         
         AMA[cb]=AMA[cb+1]+NormalizeDouble(SSC*SSC*(Close[cb]-AMA[cb+1]),Digits);
         mAMA[cb]=AMA[cb];
         if(filter<1)
            {
            fAMA[cb]=mAMA[cb];
            }
         else
            {
            for(i=cb;i<=cb+SlowMA-1;i++)
               {
               sdAMA=sdAMA+MathAbs(mAMA[i]-mAMA[i+1]);
               }
            dAMA=mAMA[cb]-mAMA[cb+1];
            if(dAMA>=0)
               {
               if(dAMA<NormalizeDouble(filter*sdAMA/(100*SlowMA),4)&&
                  High[cb]<=High[Highest(NULL,0,MODE_HIGH,n,cb)]+h*Point)
                  {
                  fAMA[cb]=fAMA[cb+1];
                  }
               else
                  {
                  fAMA[cb]=mAMA[cb];
                  }
               }
            else
               {
               if(MathAbs(dAMA)<NormalizeDouble(filter*sdAMA/(100*SlowMA),4)&&
                  Low[Lowest(NULL,0,MODE_LOW,n,cb)]-h*Point<Low[cb])
                  {
                  fAMA[cb]=fAMA[cb+1];
                  }
               else
                  {
                  fAMA[cb]=mAMA[cb];
                  }
               }
            sdAMA=0.0;
            }
         }
         
      }//for(cb=Bars-counted_bars;cb>=0;cb--)
   //ObjectsRedraw();

//----
   return(0);
  }
//+------------------------------------------------------------------+

