




------------------------------------COMPRA ABAJO






_-----------------------------------------------------------------------AQUI VA EL ELSE--------------------




  int permitirabrirv=0;
  int permitirabrirc=0;
string cierreposicion4 = "0";



//  if(tendenciasar==1&&tendenciamirror==1&&tendenciamirror2==1&&optimocompra==1&&permitirabrirc==1){
   if(operacionabrir==1&&permitirabrirc==1){
if(restop==0){
  //No hay restop
}else{
      OrderSend(Symbol(),OP_BUY,lotesfinal,Ask,Slippage,0,0,0,MagicNumber,0,Blue); //Compra restop
      string fileNamec1 = OrderSymbol()+"c"+OrderTicket()+".txt";
      string fileHandlec1 = FileOpen(fileNamec1,FILE_CSV|FILE_READ | FILE_WRITE);
      string datac1 = restop;
      if(fileHandlec1 ==INVALID_HANDLE){
      printf("No se ha podido abrir operacion 2 o mas compra establecer takeprofit de operacion actual");
      }else{
                FileWrite(fileHandlec1,datac1);
                FileClose(fileHandlec1);
       }


        //+------------------------------------------------------------------+
        //   CICLO FOR para nuevo take profit por nueva operacion COMPRA
        //+------------------------------------------------------------------+

        for(int cnt22=0;cnt22<OrdersTotal();cnt22++)
        {
        OrderSelect(cnt22,SELECT_BY_POS,MODE_TRADES);

        if(OrderType()==OP_BUY&&OrderSymbol()==Symbol()){

        string fileNamenuevoc11 = OrderSymbol()+"c"+OrderTicket()+".txt";
        string fileHandlenuevoc11 = FileOpen(fileNamenuevoc11,FILE_CSV|FILE_READ | FILE_WRITE);
        if(fileHandlec1 ==INVALID_HANDLE){
        printf("No se ha podido actualizar las operaciones de compra para establecer nuevo takeprofit");
        }else{
          string datanuevoc11 = resbot;
          FileWrite(fileHandlenuevoc11,datanuevoc11);

          FileClose(fileHandlenuevoc11);
         }

        }
        }
}

  }
--------------------------------------------------------------SEPARARAR PRIMERO VENTA DEL ELSE------------
int permitirabrirv=0;
string cierreposicion4 = "0";
for(int cnt4=0;cnt4<OrdersTotal();cnt4++)
{

OrderSelect(cnt4,SELECT_BY_POS,MODE_TRADES);
if(OrderSymbol()==Symbol()){
string fileNamecierre4 = "nada.txt";
if(OrderType()==OP_SELL){
fileNamecierre4 = OrderSymbol()+"v"+OrderTicket()+".txt";
}

string fileHandlecierre4 = FileOpen(fileNamecierre4,FILE_CSV|FILE_READ);// | FILE_WRITE
if(fileHandlecierre4==INVALID_HANDLE){
printf("Handle Invalido, apertura error 2 - Error al leer cierre cuando hay mas de una operacion en el mercado actual");
}else{
cierreposicion4 = FileReadString(fileHandlecierre4);
FileClose(fileHandlecierre4);
}
string stopname11 = OrderSymbol()+"vstop"+OrderTicket()+".txt";
string handlestop11 = FileOpen(stopname11,FILE_CSV|FILE_READ | FILE_WRITE);
if(handlestop11 ==INVALID_HANDLE){
printf("Handle Invalido 1-1-1 Al abrir operacion primera venta, no ha podido actualizar los stoploss de todas las operaciones");
}else{
string datastop11 = restop;
          FileWrite(handlestop11,datastop11);
          FileClose(handlestop11);
}
}
ObjectSetText(Symbol()+6,"Takeprofit "+Symbol()+"  : "+cierreposicion4,9,"Verdana",Red);
ObjectSet(Symbol()+6,OBJPROP_CORNER,0);
ObjectSet(Symbol()+6,OBJPROP_XDISTANCE,20);
ObjectSet(Symbol()+6,OBJPROP_YDISTANCE,170);
if(resbot>cierreposicion4)//modelo
{
 permitirabrirv=1;// permitir
}else{
  permitirabrirv=2;// no permitir
}
}


---------------------------------------------------------------------------------AQUI EL ELSE DE Compra
int permitirabrirc=0;
string cierreposicion41 = "0";
for(int cnt41=0;cnt41<OrdersTotal();cnt41++)
{

OrderSelect(cnt41,SELECT_BY_POS,MODE_TRADES);
if(OrderSymbol()==Symbol()){
string fileNamecierre41 = "nada.txt";
if(OrderType()==OP_BUY){
fileNamecierre41 = OrderSymbol()+"c"+OrderTicket()+".txt";
}

string fileHandlecierre41 = FileOpen(fileNamecierre41,FILE_CSV|FILE_READ);// | FILE_WRITE
if(fileHandlecierre41==INVALID_HANDLE){
printf("Handle Invalido, apertura error 21 - Error al leer cierre cuando hay mas de una operacion en el mercado actual");
}else{
cierreposicion41 = FileReadString(fileHandlecierre4);
FileClose(fileHandlecierre4);
}
string stopname111 = OrderSymbol()+"cstop"+OrderTicket()+".txt";
string handlestop111 = FileOpen(stopname111,FILE_CSV|FILE_READ | FILE_WRITE);
if(handlestop111 ==INVALID_HANDLE){
printf("Handle Invalido 1-1-1 Al abrir operacion primera venta, no ha podido actualizar los stoploss de todas las operaciones");
}else{
string datastop111 = resbot;
          FileWrite(handlestop111,datastop111);
          FileClose(handlestop111);
}
}
ObjectSetText(Symbol()+8,"TP COMPRA "+Symbol()+"  : "+cierreposicion41,9,"Verdana",Red);
ObjectSet(Symbol()+8,OBJPROP_CORNER,0);
ObjectSet(Symbol()+8,OBJPROP_XDISTANCE,20);
ObjectSet(Symbol()+8,OBJPROP_YDISTANCE,170);
if(restop<cierreposicion4)//modelo
{
 permitirabrirc=1;// permitir
}else{
  permitirabrirc=2;// no permitir
}
}
