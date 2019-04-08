if(OrderTakeProfit()>resbot2){
printf("takeprofit es mas pequeño (valor mas alto) que la resistencia bot actual va en camino bueno...");
 if(OrderTakeProfit()==0){
    OrderModify(OrderTicket(),0,0,resbot2,0,Red);
printf("takeprofit no establecido, establecerlo por primera vez en "+resbot2);
 }
}else{
  OrderModify(OrderTicket(),0,0,resbot2,0,Red);
  printf("takeprofit es mas alto que el nuevo resbot "+resbot2);
}
printf("mirar operaciones de venta abiertas para ver si cerrar o no");
