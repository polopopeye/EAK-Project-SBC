//+-------------------------------------------------------------------------------------------+
//|                                                                                           |
//|                                      DonnaFX Label.mq4                                    |
//|                                                                                           |
//+-------------------------------------------------------------------------------------------+
#property copyright "Copyright @ 2015 traderathome"
#property link      "email: traderathome@msn.com"

/*---------------------------------------------------------------------------------------------
Overview:

This indicator is coded to run on MT4 Builds 600+.  It places a "PVSRA...donnaforex.com" label
in the lower left corner of the chart.  The text and the font color, style and size can be
changed.  The position can be adjusted accordingly if you do change the font style and/or size.

The display TFs can be set so the label automatically does not show above/below a set TF, or
above/below a set range of TFs.

                                                                   - Traderathome, 08-01-2015
----------------------------------------------------------------------------------------------
Suggested Settings:   White Chart           Black Chart

Text_Color            Black                 Gray
---------------------------------------------------------------------------------------------*/


//+-------------------------------------------------------------------------------------------+
//| Indicator Global Inputs                                                                   |
//+-------------------------------------------------------------------------------------------+
#property indicator_chart_window

//global external inputs
extern bool     Indicator_On                  = true;
extern color    Text_Color                    = Gray;
extern string   Text_Message                  = "PVSRA with Traderathome @ donnaforex.com";
extern string   Text_Font                     = "Tahoma";
extern int      Text_Size                     = 8;
extern int      Indent                        = 3;
extern int      Elevate                       = 4;
extern int      Display_Min_TF                = 1;
extern int      Display_Max_TF                = 43200;
extern string   TF_Choices                    = "1-5-15-30-60-240-1440-10080-43200";

//Global Buffers and Variables
bool            Deinitialized;
string          item1  = "[DF Label]";

//+-------------------------------------------------------------------------------------------+
//| Indicator De-initialization                                                               |
//+-------------------------------------------------------------------------------------------+
int deinit()
  {
  int obj_total= ObjectsTotal();
  for (int i= obj_total; i>=0; i--) 
    {
    string name= ObjectName(i);
    if (StringSubstr(name,0,3)=="[DF") {ObjectDelete(name);}
    }

  return(0);
  }

//+-------------------------------------------------------------------------------------------+
//| Indicator Initialization                                                                  |
//+-------------------------------------------------------------------------------------------+
int init()
  {
  Deinitialized = false;

  //Label Placement
  ObjectCreate(item1,OBJ_LABEL,0,0,0);
  ObjectSet(item1,OBJPROP_CORNER,2);
  ObjectSet(item1,OBJPROP_YDISTANCE,Indent);
  ObjectSet(item1,OBJPROP_XDISTANCE,Elevate);
  ObjectSet(item1,OBJPROP_BACK,false);

  return(0);
  }

//+-------------------------------------------------------------------------------------------+
//| Indicator Start                                                                           |
//+-------------------------------------------------------------------------------------------+
int start()
  {
  //If Indicator is "Off" or chart is out of range deinitialize only once, not every tick.
  if((!Indicator_On) || ((Period() < Display_Min_TF) || (Period() > Display_Max_TF)))
    {
    if (!Deinitialized) {deinit(); Deinitialized = true;}
    ObjectDelete(item1);
    return(0);
    }
  else {Deinitialized = false;}

  //Display Configurations Label
  ObjectSetText(item1,Text_Message,Text_Size,Text_Font,Text_Color);

  return(0);
  }

//+-------------------------------------------------------------------------------------------+
//| Indicator End                                                                             |
//+-------------------------------------------------------------------------------------------+




