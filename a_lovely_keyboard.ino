#include <Wire.h>

#define PCAL9555 0x20

byte shiftflag=0;
byte oldcol,oldrow;
byte oldcol2,oldrow2;
boolean repf=0, repf2=0;
unsigned long time1, time2,time3,time4;
  unsigned int diftime;
void setup() {
  Serial.begin(4800);
  Wire.begin();
  i2c_write(PCAL9555, 0x4F, 0x00);
  i2c_write(PCAL9555, 0x06, 0x00);
  i2c_write(PCAL9555, 0x07, 0x00);
  i2c_write(PCAL9555, 0x40, 0xFF);
  i2c_write(PCAL9555, 0x41, 0xFF);
  i2c_write(PCAL9555, 0x42, 0xFF);
  i2c_write(PCAL9555, 0x43, 0xFF);  
  for(int i=2; i<10; i++){
  pinMode(i, INPUT);    
  digitalWrite(i, LOW);
  }
  pinMode(10, OUTPUT);
  
}

void loop() {
  byte row, column,row2;
  byte sense;

  // put your main code here, to run repeatedly:
  for(column=1; column<17; column++){
    scan_function(column);
  for(row=1; row<9; row++){
    row2=row+1;
    sense=digitalRead(row2);
    if(sense==1){ ////sensing part start
  
  if(repf==0){ /// if not repeating start
      if(((column==7)&&(row==1))||((column==7)&&(row==3)))
      {
        shiftflag=1;
      }
      
    if(shiftflag==1){/// shift processing start
      shift_chara(column,row);
        oldrow=row;
        oldcol=column;
    }else{
      send_chara(column,row);
        oldrow=row;
        oldcol=column;
    }/// shift processing end 
  }////// if not repeating end   
    }///sensing end
  }
  }

}

void i2c_write(int device_address, int memory_address, int value)
{
  Wire.beginTransmission(device_address);
  Wire.write(memory_address);
  Wire.write(value);
  Wire.endTransmission();
  delay(3);
}

void i2c_write2(int device_address, int memory_address, int value, int value2)
{
  Wire.beginTransmission(device_address);
  Wire.write(memory_address);
    delay(5);
  Wire.write(value);
    delay(5);
  Wire.write(value2);
    delay(5);
  Wire.endTransmission();
}

void scan_function(int row)
{
  int val1,val2;
  switch(row)
  {
    case 1:
    val1=0b00000001;
    val2=0b00000000;
    break;
    case 2:
    val1=0b00000010;
    val2=0b00000000;
    break;
    case 3:
    val1=0b00000100;
    val2=0b00000000;
    break;
    case 4:
    val1=0b00001000;
    val2=0b00000000;
    break;  
    case 5:
    val1=0b00010000;
    val2=0b00000000;
    break;
    case 6:
    val1=0b00100000;
    val2=0b00000000;
    break;
    case 7:
    val1=0b01000000;
    val2=0b00000000;
    break;
    case 8:
    val1=0b10000000;
    val2=0b00000000;
    break;
    case 9:
    val1=0b00000000;
    val2=0b00000001;
    break;
    case 10:
    val1=0b00000000;
    val2=0b00000010;
    break; 
    case 11:
    val1=0b00000000;
    val2=0b00000100;
    break;      
    case 12:
    val1=0b00000000;
    val2=0b00001000;
    break;
    case 13:
    val1=0b00000000;
    val2=0b00010000;
    break;
    case 14:
    val1=0b00000000;
    val2=0b00100000;
    break;
    case 15:
    val1=0b00000000;
    val2=0b01000000;
    break;
    case 16:
    val1=0b00000000;
    val2=0b10000000;
    break;              
  }
  i2c_write(PCAL9555, 0x02, val1);
  i2c_write(PCAL9555, 0x03, val2);
}

void shift_chara(int col, int row){

char charamap2[17][9];

charamap2[4][1]='~';
charamap2[4][3]='!';
charamap2[2][4]='@';
charamap2[3][2]='#';
charamap2[3][3]='$';
charamap2[3][4]='%';
charamap2[12][3]='^';
charamap2[14][4]='&';
charamap2[14][3]='*';
charamap2[14][2]='(';
charamap2[13][2]=')';
charamap2[11][2]='_';
charamap2[10][2]='+';
charamap2[13][1]=0x08;
charamap2[4][8]=0x09;
charamap2[4][4]='Q';
charamap2[2][5]='W';
charamap2[2][6]='E';
charamap2[3][5]='R';
charamap2[12][4]='T';
charamap2[14][5]='Y';
charamap2[13][4]='U';
charamap2[13][3]='I';
charamap2[11][4]='O';
charamap2[11][3]='P';
charamap2[10][3]='{';
charamap2[16][3]='}';
charamap2[9][7]='|';
charamap2[4][5]='A';
charamap2[4][6]='S';
charamap2[2][7]='D';
charamap2[3][6]='F';
charamap2[12][5]='G';
charamap2[14][6]='H';
charamap2[13][5]='J';
charamap2[11][5]='K';
charamap2[10][4]='L';
charamap2[10][5]=':';
charamap2[16][4]='"';
charamap2[15][5]='\n';
charamap2[4][7]='Z';
charamap2[9][2]='X';
charamap2[12][7]='C';
charamap2[12][6]='V';
charamap2[14][7]='B';
charamap2[13][6]='N';
charamap2[11][6]='M';
charamap2[10][6]='<';
charamap2[16][6]='>';
charamap2[16][5]='a';
charamap2[13][7]=0x20;

{if((col!=7)&(row!=1)||(col!=7)&(row!=3)){
Serial.print(charamap2[col][row]);
delay(100);
shiftflag=0;
}

}}


void send_chara(int col, int row){

char charamap[17][9];

charamap[4][1]='`';
charamap[4][3]='1';
charamap[2][4]='2';
charamap[3][2]='3';
charamap[3][3]='4';
charamap[3][4]='5';
charamap[12][3]='6';
charamap[14][4]='7';
charamap[14][3]='8';
charamap[14][2]='9';
charamap[13][2]='0';
charamap[11][2]='-';
charamap[10][2]='=';
charamap[13][1]=0x08;
charamap[4][8]=0x09;
charamap[4][4]='q';
charamap[2][5]='w';
charamap[2][6]='e';
charamap[3][5]='r';
charamap[12][4]='t';
charamap[14][5]='y';
charamap[13][4]='u';
charamap[13][3]='i';
charamap[11][4]='o';
charamap[11][3]='p';
charamap[10][3]='[';
charamap[16][3]=']';
charamap[9][7]=0x5c;
charamap[4][5]='a';
charamap[4][6]='s';
charamap[2][7]='d';
charamap[3][6]='f';
charamap[12][5]='g';
charamap[14][6]='h';
charamap[13][5]='j';
charamap[11][5]='k';
charamap[10][4]='l';
charamap[10][5]=';';
charamap[16][4]=0x27;
charamap[15][5]='\n';
charamap[4][7]='z';
charamap[9][2]='x';
charamap[12][7]='c';
charamap[12][6]='v';
charamap[14][7]='b';
charamap[13][6]='n';
charamap[11][6]='m';
charamap[10][6]=',';
charamap[16][6]='.';
charamap[16][5]='/';
charamap[14][1]='\n';
charamap[13][7]=0x20;


if((oldrow2==row)&&(oldcol2==col)){
  repf2=1;
  time2=time1;
  time1=millis();
}else{
  repf2=0;
}
  diftime=time1-time2;

  if(diftime>600){
    repf2=0;    
  }
if(millis()-time3>150){
if(repf2==0){if((col!=7)&(row!=1)||(col!=7)&(row!=3)){
//Serial.print(col);
//Serial.println(row);
if(col==2&&row==8){
  Serial.print("print ");
}else if(col==2&&row==2){
  Serial.print("load ");
}else if(col==2&&row==3){
  Serial.print("list\n");
}else if(col==14&&row==8){
  Serial.print("run\n");
}else if(col==13&&row==8){
  Serial.print("mem\n");
}else if(col==11&&row==8){
  Serial.print("cls\n");
}else
Serial.print(charamap[col][row]);
time3=millis();
}
}
}
  oldcol2=col;
  oldrow2=row;

}




