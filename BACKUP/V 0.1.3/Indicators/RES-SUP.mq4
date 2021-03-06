//+------------------------------------------------------------------+
//|                                                     !RES-SUP.mq4 |
//|                                                          TOPpoint|
//|                                                toppoint@yandex.ru|
//+------------------------------------------------------------------+
#property copyright "TOPpoint"
#property link      "mailto:TOPpoint@yandex.ru"
//----
#property indicator_chart_window
#property indicator_buffers 4
#property indicator_color1 Red        // Öâåò ëèíèé ãðàôèêà
#property indicator_color2 Red
#property indicator_color3 Red
#property indicator_color4 Red
//----
#define   LevelMaxDeep  6000          //----- Ãëóáèíà ïðîñìîòðà óðîâíåé 2000
// Èíäèêàòîð ðàññ÷èòûâàåò ïðèîðèòåòíûå óðîâíè ïîääåðæêè/ñîïðîòèâëåíèÿ 
// ïî çíà÷åíèÿì äíåâíîãî ATR
//extern int ATRPeriod = 10;          // Ïåðèîä ãðàôèêà
//extern int Aprox=1;                 // 0-ïîäàëüøå; 1 - ïîáëèæå
datetime PrevTime;                    // Lock äëÿ ïðåäóïðåæäåíèÿ ïîâòîðíîé îòðèñîâêè
string ShortName="RES-SUP";           // Êîðîòêîå íàçâàíèå èíäèêàòîðà â îêíå
double OHLC_D1[][6];                  // Ìàññèâ êóäà êîïèðóþòñÿ äíåâíûå ñâå÷êè
//---- buffers
double Sup0[],Sup1[],Res0[],Res1[];
//+------------------------------------------------------------------+
//| Èíèöèàëèçàöèÿ ìàññèâîâ                                           |
//+------------------------------------------------------------------+
int InitChart()
  {
//---- indicator line
   SetIndexStyle(0,DRAW_LINE,STYLE_DOT);
   SetIndexStyle(1,DRAW_LINE,STYLE_DOT);
   SetIndexStyle(2,DRAW_LINE,STYLE_DOT);
   SetIndexStyle(3,DRAW_LINE,STYLE_DOT);
   SetIndexBuffer(0,Sup0);
   SetIndexBuffer(1,Sup1);
   SetIndexBuffer(2,Res0);
   SetIndexBuffer(3,Res1);
//---- name for DataWindow and indicator subwindow label
   //  IndicatorShortName(ShortName+" ("+ATRPeriod+")");
   IndicatorShortName(ShortName);
   SetIndexLabel(0,"Ïîääåðæêà0");
   SetIndexLabel(1,"Ïîääåðæêà1");
   SetIndexLabel(2,"Ñîïðîòèâëåíèå0");
   SetIndexLabel(3,"Ñîïðîòèâëåíèå1");
//----
   SetIndexEmptyValue(0,0);
   SetIndexEmptyValue(1,0);
   SetIndexEmptyValue(2,0);
   SetIndexEmptyValue(3,0);
//----
   return(0);
  }
//+------------------------------------------------------------------+
//| Ôóíêöèÿ èíèöèàëèçàöèè - óäàëÿåì ïðåäûäóùèå ëèíèè                 |
//+------------------------------------------------------------------+
int init()
  {
   InitChart();
   return(0);
  }
//+------------------------------------------------------------------+
//| Ôóíêöèÿ äåèíèöèàëèçàöèè - óäàëÿåì ïðåäûäóùèå ëèíèè               |
//+------------------------------------------------------------------+
int deinit()
  {
   InitChart();
   return(0);
  }
//+------------------------------------------------------------------+
//| Îñíîâàÿ ôóíêöèÿ ðàñ÷åòà óðîâíåé                                  |
//+------------------------------------------------------------------+
int start()
  {
   int  counted_bars=IndicatorCounted();
   int  lastday=0, i, j, daybar=0, chartbar=0;
   double LowYesterday, HighYesterday, LowToday, HighToday, fullatr1, fullatr2,fullatr4,fullatr5,fullatr3,L2,H2,L3,H3,L4,H4,L5,H5;
   double LowY,HighY,Avr,AvrY,UpLine1,UpLine2,DnLine1,DnLine2;
   //if (counted_bars<1) return(0);
   // Åñëè âðåìÿ áàðà íå èçìåíèëîñü, âûõîäèì
   if (PrevTime==Time[0]) return(-1);
   if(Period() > PERIOD_H4)
     {
      Comment("ATR Levels - îøèáêà: ïåðèîä ãðàôèêà áîëåå Í4 !");
      return(-1); // then exit
     }
   // 0 - time, 1 - open, 2 - low, 3 - high, 4 - close, 5 - volume.
   ArrayCopyRates(OHLC_D1, Symbol(), PERIOD_D1);
   lastday=TimeDay(Time[0]);
     for(i=0; i<Bars; i++) 
     {
        if (lastday!=TimeDay(Time[i])) 
        {
         // Âû÷èñëÿåì çíà÷åíèå ATR ïðåäûäóùåãî áàðà
 /*   fullatr1 = iATR(Symbol(), PERIOD_D1, ATRPeriod, daybar+1);
    fullatr2 = iATR(Symbol(), PERIOD_D1, ATRPeriod, daybar+2);
    fullatr3 = iATR(Symbol(), PERIOD_D1, ATRPeriod, daybar+3);
    fullatr4 = iATR(Symbol(), PERIOD_D1, ATRPeriod, daybar+4);
    fullatr5 = iATR(Symbol(), PERIOD_D1, ATRPeriod, daybar+5);
     // Îïðåäåëÿåì óðîâíè         
    LowYesterday  = OHLC_D1[daybar+1][3] - fullatr1;//Äëÿ ðàññ÷åòà Ïÿòèäíåâíîé   
    HighYesterday = OHLC_D1[daybar+1][2] + fullatr1;//Äëÿ ðàññ÷åòà Ïÿòèäíåâíîé 
    LowY = OHLC_D1[daybar+1][1] - fullatr1/2;//Äëÿ ïîñòðîåíèÿ êàíàëîâ   
    HighY = OHLC_D1[daybar+1][1] + fullatr1/2;//Äëÿ ïîñòðîåíèÿ êàíàëîâ
    L2=OHLC_D1[daybar+2][3] - fullatr2;
    H2=OHLC_D1[daybar+2][2] + fullatr2;
    L3=OHLC_D1[daybar+3][3] - fullatr3;
    H3=OHLC_D1[daybar+3][2] + fullatr3;
    L4=OHLC_D1[daybar+4][3] - fullatr4;
    H4=OHLC_D1[daybar+4][2] + fullatr4;
    L5=OHLC_D1[daybar+5][3] - fullatr5;
    H5=OHLC_D1[daybar+5][2] + fullatr5;
    LowToday  = OHLC_D1[daybar][1] - (fullatr1+fullatr2)/4;   
    HighToday = OHLC_D1[daybar][1] + (fullatr1+fullatr2)/4;
    Avr=(LowToday+HighToday)/2;
    AvrY=(LowY+HighY)/2;*/
         // Ñìåíèëñÿ äåíü, ðèñóåì ëèíèþ
         UpLine1=HighToday;
         UpLine2=HighYesterday;
         DnLine1=LowToday;
         DnLine2=LowYesterday;
         //=============================
           for(j=chartbar; j<i; j++) 
           {
            //Ôèêñèðîâàííîå ðàâíîâåñèå (äíåâíîå)
            //  Bline0[j]=(OHLC_D1[daybar+1][2]+OHLC_D1[daybar+1][3]+OHLC_D1[daybar+1][4])/3;
            //Áàëàíñîâûå ñòóïåíüêè (äíåâíîå)
            //  Bline1[j]=((OHLC_D1[daybar+1][2]+OHLC_D1[daybar+1][3]+OHLC_D1[daybar+1][4])/3+(OHLC_D1[daybar+2][2]+OHLC_D1[daybar+2][3]+OHLC_D1[daybar+2][4])/3+(OHLC_D1[daybar+3][2]+OHLC_D1[daybar+3][3]+OHLC_D1[daybar+3][4])/3+(OHLC_D1[daybar+4][2]+OHLC_D1[daybar+4][3]+OHLC_D1[daybar+4][4])/3+(OHLC_D1[daybar+5][2]+OHLC_D1[daybar+5][3]+OHLC_D1[daybar+5][4])/3)/5;    
            //Äèíàìè÷åñêîå ðàâíîâåñèå (ïÿòèäíåâíîå)
            //   Bline2[j]=(OHLC_D1[daybar][2]+OHLC_D1[daybar][3]+OHLC_D1[daybar][4])/3;
            Sup0[j]=(OHLC_D1[daybar+1][2]+OHLC_D1[daybar+1][3]+OHLC_D1[daybar+1][4])/3-(OHLC_D1[daybar+1][3]-OHLC_D1[daybar+1][2])*0.5;
            Sup1[j]=(OHLC_D1[daybar+1][2]+OHLC_D1[daybar+1][3]+OHLC_D1[daybar+1][4])/3-(OHLC_D1[daybar+1][3]-OHLC_D1[daybar+1][2])*0.618;
            Res0[j]=(OHLC_D1[daybar+1][2]+OHLC_D1[daybar+1][3]+OHLC_D1[daybar+1][4])/3+(OHLC_D1[daybar+1][3]-OHLC_D1[daybar+1][2])*0.5;
            Res1[j]=(OHLC_D1[daybar+1][2]+OHLC_D1[daybar+1][3]+OHLC_D1[daybar+1][4])/3+(OHLC_D1[daybar+1][3]-OHLC_D1[daybar+1][2])*0.618;
            // Bline1[j]=(LowYesterday+HighYesterday+L2+L3+H3+H2+L4+H4+L5+H5)/10;
            // Bline2[j]=(OHLC_D1[daybar][1]+(OHLC_D1[daybar+1][2]+OHLC_D1[daybar+1][3]+OHLC_D1[daybar+1][4])/3+(OHLC_D1[daybar+2][2]+OHLC_D1[daybar+2][3]+OHLC_D1[daybar+2][4])/3)/3;
            // Bline3[j]=(OHLC_D1[daybar][1]+OHLC_D1[daybar+1][1]+OHLC_D1[daybar+2][1]+OHLC_D1[daybar+3][1]+OHLC_D1[daybar+4][1])/5;
            //  Bline1[j]=((OHLC_D1[daybar+1][2]+OHLC_D1[daybar+1][3]+OHLC_D1[daybar+1][4])/3+(OHLC_D1[daybar+2][2]+OHLC_D1[daybar+2][3]+OHLC_D1[daybar+2][4])/3+(OHLC_D1[daybar+3][2]+OHLC_D1[daybar+3][3]+OHLC_D1[daybar+3][4])/3+(OHLC_D1[daybar+4][2]+OHLC_D1[daybar+4][3]+OHLC_D1[daybar+4][4])/3+(OHLC_D1[daybar+5][2]+OHLC_D1[daybar+5][3]+OHLC_D1[daybar+5][4])/3)/5;    
           }
         lastday=TimeDay(Time[i]);
         daybar++;
         chartbar=i;
        }
     }
   // Çàïîìèíàåì âðåìÿ ïîñëåäíåãî áàðà (÷òîáû íå ñ÷èòàòü äèâåðû ïîâòîðíî)
   PrevTime=Time[0];
//----
   return(0);
  }
//+------------------------------------------------------------------+