//+------------------------------------------------------------------+
//|                                                    B3_Grid_X.mq4 |
//|                                                   March 25, 2011 |
//|                                    Copyright © 2011, J Talon LLC |
//|                                          http://www.jtatoday.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2010, J Talon LLC"
#property link      "http://www.jtatoday.com"

//+------------------------------------------------------------------+
//| script program start function                                    |
//+------------------------------------------------------------------+
int start()
{	for(int Index=ObjectsTotal();Index>=0;Index--)if(StringSubstr(ObjectName(Index),0,7)=="B3_Grid")ObjectDelete(ObjectName(Index));
	return(0);
}
//+------------------------------------------------------------------+