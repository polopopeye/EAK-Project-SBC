#property copyright "Fractal Knight Ltd"

#include <stderror.mqh>
#include <stdlib.mqh>

#property show_inputs

extern double lots = 0.02;
extern int fireMagic = 1261;
extern string opType = "0=Buy, 1=Sell, 2=BL, 3=SL, 4=BS, 5=SS";
extern int op = 0;
extern string opPrice = "Enter price for pending orders";
extern double price = 0;
extern string comment = "";
extern int positions = 1;
extern int sl = 0;
extern int tp = 0;
extern int slippage = 0;
extern bool stpBroker = true;

int retryMaxCt = 3;
int retrySleepPeriod = 500;

int digits;
int lastError;

int start() {
	digits = MarketInfo(Symbol(), MODE_DIGITS);
	int mult;
	switch (op) {
	case 0:
		price = Ask;
		mult = -1;
		break;
	case 2:
	case 4:
		mult = -1;
		break;
	case 1:
		price = Bid;
		mult = 1;
		break;
	case 3:
	case 5:
		mult = 1;
		break;
	default:
		return(0);
	}
	for (int ix=0; ix<positions; ix++) {
		sendOrder(Symbol(), op, lots, price, slippage, 
			sl, tp,
			//price+mult*sl*Point, 
			//price-mult*tp*Point, 
			mult,
			comment, fireMagic);
	 }
	return(0);
}

int sendOrder(string symbol, int cmd, double volume, double price, int slippage, double stoploss, double takeprofit, int mult, string comment, int magic) {
	//if (verboseLog) 
	bool exit_loop = false;
	int cnt = 0, ticket = 0;
	while (!exit_loop && cnt<=retryMaxCt && ticket<=0) {
		Print("sendOrder "+"@"+DoubleToStr(price, digits)+" sl="+DoubleToStr(stoploss, digits)+" tp="+DoubleToStr(takeprofit, digits)+" ct="+cnt);
		if (stpBroker) {
			ticket = OrderSend(symbol, cmd, volume, price, slippage, 0, 0, comment, magic);
			retrieveLastError();
			if (ticket>0) {
				if (stoploss>0 || takeprofit>0) {
					if (stoploss>0) stoploss = price+mult*stoploss*Point;
					if (takeprofit>0) takeprofit = price-mult*takeprofit*Point;
					bool modified = OrderModify(ticket, price, stoploss, takeprofit, 0);
					retrieveLastError();
					if (!modified)
						Print("error modifystp = "+formatLastError());
				}
			} else
				Print("error sendstp = "+formatLastError());
		} else { // !stpBroker
			if (stoploss>0) stoploss = price+mult*stoploss*Point;
			if (takeprofit>0) takeprofit = price-mult*takeprofit*Point;
			ticket = OrderSend(symbol, cmd, volume, price, slippage, stoploss, takeprofit, comment, magic);
			retrieveLastError();
			if (ticket<0)
				Print("error send2 = "+formatLastError());
		}
		
		switch (lastError) {
			case ERR_NO_ERROR:
				exit_loop = true;
				break;
			case ERR_SERVER_BUSY:
			case ERR_NO_CONNECTION:
			case ERR_INVALID_PRICE:
			case ERR_OFF_QUOTES:
			case ERR_BROKER_BUSY:
			case ERR_TRADE_CONTEXT_BUSY: 
			case ERR_INVALID_STOPS:
				cnt++; // a retryable error
				break;
			case ERR_PRICE_CHANGED:
			case ERR_REQUOTE:
				cnt++; RefreshRates();  
				continue; // we can apparently retry immediately 
			default:
				exit_loop = true; // an apparently serious error.
				break; 
		}  // end switch 
		if (!exit_loop) {
			Print("retry delay ct="+cnt);
			Sleep(retrySleepPeriod);
			RefreshRates();
		}
	}
	return (ticket);
}
string formatError(int lastError) {
	return (lastError+":"+ErrorDescription(lastError));
}
string formatLastError() {
	//lastError = GetLastError();
	return (formatError(lastError));
}
int retrieveLastError() {
	lastError = GetLastError();
	return (lastError);
}
