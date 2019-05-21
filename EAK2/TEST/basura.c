//AQUI VA LA MAIZENA
double pfSGBGB=pfSGBC+pfSGBV;
int PRGBa=0,PRGBa2=0;
int cntPRop=0;
if(pfSGBGB>0.01)PRGBa=1;

string FileDBarchivosPR="PR"+FileDBarchivos;
string nuevosdatosPR2=1+":"+PRGBa;
string fdb1prarray[];
if(FileIsExist(FileDBarchivosPR)){
string Fdb1prREADh = FileOpen(FileDBarchivosPR,FILE_READ);
if(Fdb1prREADh==INVALID_HANDLE){
printf("Fdb1prREADh 1");
}else{
int  str_sizePR1read=FileReadInteger(Fdb1prREADh,INT_VALUE);
string Fdb1prREAD = FileReadString(Fdb1prREADh,str_sizePR1read);
FileClose(Fdb1prREADh);
}
StringSplit(Fdb1prREAD,sep,fdb1prarray);
cntPRop= StrToInteger(fdb1prarray[0])+1;
PRGBa2=StrToInteger(fdb1prarray[1])+PRGBa;

if(cntPRop>fdb1prarray[0]){
string Fdb1pr = FileOpen(FileDBarchivosPR,FILE_WRITE);
if(Fdb1pr==INVALID_HANDLE){
printf("Fdb1pr 1");
}else{
string Fdb1prw = cntPRop+":"+PRGBa2;
     FileWrite(Fdb1pr,Fdb1prw);
     FileClose(Fdb1pr);
}
}
}else{
string Fdb2pr = FileOpen(FileDBarchivosPR,FILE_WRITE);
if(Fdb2pr==INVALID_HANDLE){
printf("Fdb2pr 1");
}else{
string Fdb2prw = nuevosdatosPR2;
     FileWrite(Fdb2pr,Fdb2prw);
     FileClose(Fdb2pr);
}
}
//Bocata
