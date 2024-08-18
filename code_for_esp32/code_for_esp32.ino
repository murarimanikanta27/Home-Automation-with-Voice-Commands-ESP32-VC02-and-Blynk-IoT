#define BLYNK_TEMPLATE_ID "TMPL3jdYm7zM4"
#define BLYNK_TEMPLATE_NAME "LIVE CAM HOME AUTOMATION"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#include<WiFi.h>
//#define BLYNK_DEBUG
#include<ESP32Servo.h>
Servo s1,s2;
#define APP_DEBUG
#include "BlynkEdgent.h"
int pin1=25;
int pin2=26;
int pin3=12;
int pin4=14;
int pin5=32;
int pin6=33;
int val1,val2,val3,val4,val5,val6;
unsigned int receivedValue = 0;
void setup()
{
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
  s1.attach(32);
  s2.attach(33);
  s1.write(90);
  s2.write(90);
  Serial.begin(9600);
  Serial2.begin(9600,SERIAL_8N1,16,17);
  delay(100);
  BlynkEdgent.begin();
}
BLYNK_WRITE(V0)
{
  val1=param.asInt();
  digitalWrite(pin1,val1);
  Serial.print(val1);
}
BLYNK_WRITE(V1)
{
  val2=param.asInt();
  digitalWrite(pin2,val2);
}
BLYNK_WRITE(V2)
{
  val3=param.asInt();
  digitalWrite(pin3,val3);
}
BLYNK_WRITE(V3)
{
  val4=param.asInt();
  digitalWrite(pin4,val4);
}
BLYNK_WRITE(V4)
{
  val5=param.asInt();
  Serial.print("xaxis is");
  Serial.println(val5);
  val5=map(val5,255,0,0,180);
  s1.write(val5);
}
BLYNK_WRITE(V5)
{
  val6=param.asInt();
  Serial.print("y axis is");
  Serial.println(val6);
  val6=map(val6,0,255,0,180);
  s2.write(val6);
}
void loop() {
  BlynkEdgent.run();
  if (Serial2.available()) {
    byte highByte = Serial2.read();
    byte lowByte = Serial2.read();
    receivedValue = (highByte << 8) | lowByte;
    Serial.print("Received HEX value: 0x");
    Serial.println(receivedValue, HEX);
  }
   if (receivedValue == 0xA100)  //led 0n
  { digitalWrite(pin1, LOW);  
    Blynk.virtualWrite(V0, 0);
    Serial.println("led on");
  } else if(receivedValue == 0xA111) { //led off

    digitalWrite(pin1,HIGH);  
    Blynk.virtualWrite(V0, 1);
    Serial.println("led off");
  } else if(receivedValue == 0xAA00){ //bed on
    digitalWrite(pin2,LOW);  
    Blynk.virtualWrite(V1, 0); 
    Serial.println("bed on"); 
  }else if(receivedValue == 0xAA22){//bed off
    digitalWrite(pin2,HIGH);  
    Blynk.virtualWrite(V1, 1); 
    Serial.println("bed off");  
  }else if(receivedValue == 0xAA1B){//motor on
    digitalWrite(pin3,LOW);  
    Blynk.virtualWrite(V2, 0); 
    Serial.println("motor on");   
  }else if(receivedValue == 0xAB01){ //motor off
    digitalWrite(pin3,HIGH);  
    Blynk.virtualWrite(V2, 1);
    Serial.println("motor off"); 
  }else if(receivedValue == 0xA1B1){ //fan on
    digitalWrite(pin4,LOW);  
    Blynk.virtualWrite(V3, 0);
    Serial.println("fan on");   
  }else if(receivedValue == 0xAE23){//fan off
    digitalWrite(pin4,HIGH);  
    Blynk.virtualWrite(V3, 1);
    Serial.println("fan off");   
  }else if(receivedValue == 0xA276){    //All on
  digitalWrite(pin1,HIGH);  
  Blynk.virtualWrite(V0, 1);//led on
  digitalWrite(pin2,HIGH);  
  Blynk.virtualWrite(V1, 1);//bed on
  digitalWrite(pin3,HIGH);  
  Blynk.virtualWrite(V2, 1);//motor on 
  digitalWrite(pin4,HIGH);  
  Blynk.virtualWrite(V3, 1); //fan on
  Serial.println("all on");
  }else if(receivedValue == 0x5ABB){  //all off
    digitalWrite(pin1, LOW);  
    Blynk.virtualWrite(V0, 0);//led off
    digitalWrite(pin2,LOW);  
    Blynk.virtualWrite(V1, 0); //bed off   
    digitalWrite(pin3,LOW);  
    Blynk.virtualWrite(V2, 0); //motor off 
    digitalWrite(pin4,LOW);  
    Blynk.virtualWrite(V3, 0); //fan off 
    Serial.println("all off");    
  }
  else
  delay(10);
  receivedValue = 0;

}

