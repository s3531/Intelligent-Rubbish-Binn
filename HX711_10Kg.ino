#include <Adafruit_NeoPixel.h>
#include "HX711.h"
#include "SegmentLCD.h"
#define PIN 13
#define PIN_NUM 2 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIN_NUM, PIN, NEO_GRB + NEO_KHZ800);
unsigned long Weight = 0;
void setup()
{
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  unsigned char i;
  Init_Hx711();      
  Init_1621();
        Get_Maopi();  
  
  for( i = 0 ; i < 6 ; i++ )
  {
    Write_1621_data(5-i,Table_Hello[i]);     
  }
  delay(500);

  Serial.begin(9600);
  Serial.print("Welcome to use!\n");

  Get_Maopi();   
  
}

void loop()
{
  unsigned char i;
  Weight = Get_Weight();  
  Serial.print(Weight); 
  Serial.print(" g\n");
  Serial.print("\n");  

  if(Flag_Error == 0)
  {
    Write_1621_data(5,0x00);       
    Write_1621_data(4,num[Weight%100000/10000]);        
    Write_1621_data(3,num[Weight%10000/1000]);        
    Write_1621_data(2,num[Weight%1000/100]|0x80); 
    Write_1621_data(1,num[Weight%100/10]);
    Write_1621_data(0,num[Weight%10]);
  }
  else
  {
    for( i = 0 ; i < 6 ; i++ )
    {
      Write_1621_data(5-i,Table_Error[i]);        //Error
    } 
  }

  delay(300);       //延时0.3s
 if(Weight>0&&Weight<3000)
 {
     digitalWrite(13,HIGH); digitalWrite(12,LOW); digitalWrite(11,LOW);
     delay(1000);  //blue
 }
 else if(Weight>=3000&&Weight<6000)
 {
     digitalWrite(13,LOW); digitalWrite(12,HIGH); digitalWrite(11,LOW);
  delay(1000);  //green
 }
 else if(Weight>=6000&&Weight<10000)
 {
     digitalWrite(13,LOW); digitalWrite(12,LOW); digitalWrite(11,HIGH);//
  delay(1000);  //red
 }
 else if(Weight>10000)
 {
    digitalWrite(13,HIGH); digitalWrite(12,HIGH); digitalWrite(11,HIGH);
  delay(1000);  //all
 }
 else if(Weight==0)
 {
    digitalWrite(13,LOW); digitalWrite(12,LOW); digitalWrite(11,LOW);
  delay(1000);  //none
 }

}








