string gsa_188[8] = {"USD", "EUR", "GBP", "CHF", "JPY", "CAD", "AUD", "NZD"};
int gia_192[8] = {9639167, 16711680, 16711680, 65535, 65535, 9639167, 16711680, 16711680};
string gsa_196[28] = {"EURUSD", "GBPUSD", "AUDUSD", "USDJPY", "USDCHF", "USDCAD", "EURAUD", "EURCAD", "EURCHF", "EURGBP", "EURJPY", "GBPJPY", "GBPCHF", "NZDUSD", "AUDCAD", "AUDJPY", "CHFJPY",
      "AUDNZD", "NZDJPY", "NZDCAD", "NZDCHF", "GBPNZD", "EURNZD", "GBPCAD", "GBPAUD", "AUDCHF", "CADCHF", "CADJPY"};
ForexProfitSupreme Meter
ls_40
ld_56

voy a utilizar archivos.

pensar en cambiar las noticias.


debug -
Extrapolator
Simeter
Avramis
Lucky
Semafor
---------------------
advanceddebug

7


ObjectSetText(Symbol()+2,"PipsC: "+DiffPipsc+" PipsV: "+DiffPipsv,7,NULL,Orange);
  ObjectSet(Symbol()+2,OBJPROP_CORNER,0);
  ObjectSet(Symbol()+2,OBJPROP_XDISTANCE,15);
  ObjectSet(Symbol()+2,OBJPROP_YDISTANCE,40);


  if(debugoption==true){
    ObjectSetText(Symbol()+"Extrapolator","Extrapolator -> Neutro"+riskextrapolatorc,6.5,NULL,Orange);
      ObjectSet(Symbol()+"Extrapolator",OBJPROP_CORNER,0);
      ObjectSet(Symbol()+"Extrapolator",OBJPROP_XDISTANCE,15);
      ObjectSet(Symbol()+"Extrapolator",OBJPROP_YDISTANCE,50);
  }
  if(debugoption==true){
    ObjectSetText(Symbol()+"Simeter","Simeter -> Compra",7,NULL,Blue);
      ObjectSet(Symbol()+"Simeter",OBJPROP_CORNER,0);
      ObjectSet(Symbol()+"Simeter",OBJPROP_XDISTANCE,15);
      ObjectSet(Symbol()+"Simeter",OBJPROP_YDISTANCE,60);
  }
  ObjectSetText(Symbol()+"Avramis","Avramis -> Venta",7,NULL,Red);
    ObjectSet(Symbol()+"Avramis",OBJPROP_CORNER,0);
    ObjectSet(Symbol()+"Avramis",OBJPROP_XDISTANCE,15);
    ObjectSet(Symbol()+"Avramis",OBJPROP_YDISTANCE,70);

    if(debugoption==true){
  ObjectSetText(Symbol()+"Lucky","Lucky -> VENTA",7,NULL,Red);
    ObjectSet(Symbol()+"Lucky",OBJPROP_CORNER,0);
    ObjectSet(Symbol()+"Lucky",OBJPROP_XDISTANCE,15);
    ObjectSet(Symbol()+"Lucky",OBJPROP_YDISTANCE,80);
  }
