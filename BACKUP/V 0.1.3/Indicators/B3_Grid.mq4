//+------------------------------------------------------------------+
//|                                                      B3_Grid.mq4 |
//|                                                   March 25, 2011 |
//|                                    Copyright © 2011, J Talon LLC |
//|                                          http://www.jtatoday.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2010, J Talon LLC"
#property link      "http://www.jtatoday.com"
#property show_inputs

extern double  BasePrice      =  0.0000;        // Price for first trade
extern string  SetCountArray  =  "4,4";         // Specifies number of grids in each block (separated by a comma) 
extern string  GridSetArray   =  "25,50,100";   // Specifies number of pips for each grid in the block (separated by a comma)
extern double  GAF            =  1;             // Grid Adjustment Factor
extern int     MaxTrades      =  15;            // max trades for grid
extern color   BaseColor      =  Green;
extern color   BuyColor       =  Blue;
extern color   SellColor      =  Red;

int Index;
int GridArray[];
double Points;
string EA="B3";
//+------------------------------------------------------------------+
//| script program start function                                    |
//+------------------------------------------------------------------+
int start()
{	if(ObjectFind(EA+"_GridBase")==0)LabelDelete(EA+"_Grid");
	int GridSet,GridTemp,GridTP,GridIndex,GridLevel,GridError;
	if(Digits%2==1)Points=Point*10;
	else Points=Point;
	ArrayResize(GridArray,MaxTrades);
	while(GridIndex<MaxTrades)
	{	if(StringFind(SetCountArray,",")==-1&&GridIndex==0)
		{	GridError=1;
			break;
		}
		else GridSet=StrToInteger(StringSubstr(SetCountArray,0,StringFind(SetCountArray,",")));
		if(GridSet>0)
		{	SetCountArray=StringSubstr(SetCountArray,StringFind(SetCountArray,",")+1);
			GridTemp=StrToInteger(StringSubstr(GridSetArray,0,StringFind(GridSetArray,",")));
			GridSetArray=StringSubstr(GridSetArray,StringFind(GridSetArray,",")+1);
		}
		else GridSet=MaxTrades;
		if(GridTemp==0)
		{	GridError=2;
			break;
		}
		for(GridLevel=GridIndex;GridLevel<=MathMin(GridIndex+GridSet-1,MaxTrades-1);GridLevel++)
		{	if(GridLevel==0)GridArray[GridLevel]=GridTemp;
			else GridArray[GridLevel]=GridArray[GridLevel-1]+GridTemp;
		}
		GridIndex=GridLevel;
	}
	if(GridError>0||GridArray[0]==0)
	{	if(GridError==1)Print("Grid Array Error ("+GridSetArray+"). Each value should be separated by a comma.");
		else Print("Grid Array Error. Check that there is one more 'Grid' and 'TP' number than there are 'Set' numbers, separated by commas.");
		return;
	}
	if(BasePrice==0)BasePrice=WindowPriceOnDropped();
	if(BasePrice==0)BasePrice=(Ask+Bid)/2;
	for(Index=0;Index<=MaxTrades;Index++)
	{	if(Index==0)
		{	CreateLine(EA+"_GridBase",BaseColor,1,STYLE_DOT);
			ObjectMove(EA+"_GridBase",0,Time[1],BasePrice);
		}
		else
		{	CreateLine(EA+"_Grid"+Index+"Dn",BuyColor,1,STYLE_DOT);
			ObjectMove(EA+"_Grid"+Index+"Dn",0,Time[1],BasePrice-GridArray[Index-1]*Points*GAF);
			CreateLine(EA+"_Grid"+Index+"Up",SellColor,1,STYLE_DOT);
			ObjectMove(EA+"_Grid"+Index+"Up",0,Time[1],BasePrice+GridArray[Index-1]*Points*GAF);
		}
	}
	return;
}
//+------------------------------------------------------------------+
//| Create Line Function (OBJ_HLINE ONLY)                            |
//+------------------------------------------------------------------+
void CreateLine(string Name,color Colour,int Width,int Style)
{	ObjectCreate(Name,OBJ_HLINE,0,0,0);
	ObjectSet(Name,OBJPROP_COLOR,Colour);
	ObjectSet(Name,OBJPROP_WIDTH,Width);
	ObjectSet(Name,OBJPROP_STYLE,Style);
}
//+------------------------------------------------------------------+
//| Delete Overlay Label Function                                    |
//+------------------------------------------------------------------+
void LabelDelete(string Name)
{	for(Index=ObjectsTotal();Index>=0;Index--)if(StringSubstr(ObjectName(Index),0,7)==Name)ObjectDelete(ObjectName(Index));
}
//+------------------------------------------------------------------+