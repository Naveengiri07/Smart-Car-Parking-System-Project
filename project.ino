#include <ESP8266WiFi.h>
#include <timer.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo motor;
int angle=0;
int slotFilled=0;
const int maxSlot=4;
const int iRPin1=5;         //D1
const int iRPin2=4;         //D2
const int iRPin3=0;         //D3
const int iRPin4=2;         //D4
const int iRPin5=14;        //D5
const int iRPin6=12;        //D6
const int motorPin=13;      //D7
const int piezoPin=15;      //D8 

char auth[]="Feu9caay_SSvRXvJzt7g8f4M4W32D2S9";
char ssid[]="ASUS_X01BDA";
char pass[]="naveen07";

SimpleTimer timer;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(iRPin1,INPUT);
  pinMode(iRPin2,INPUT);
  pinMode(iRPin3,INPUT);
  pinMode(iRPin4,INPUT);
  pinMode(iRPin5,INPUT);
  pinMode(iRPin6,INPUT);
  motor.attach(motorPin);
  timer.setInterval(1000L,slot1);
  timer.setInterval(1000L,slot2);
  timer.setInterval(1000L,slot3);
  timer.setInterval(1000L,slot4);
  timer.setInterval(1000L,entrySide);
  timer.setInterval(1000L,exitSide);
}
void loop() {
  Blynk.run();
  timer.run();
}
void motorRun(){                                      //function to opening and closing of the gate
  for(angle = 0; angle < 100; angle += 1)   
  { motor.write(angle);                 
    delay(20);                       
  } 
  delay(1000);
  for(angle = 100  ; angle>=1; angle-=5)    
  { motor.write(angle);              
    delay(20);                       
  } 
  delay(1000);
}
//slot functions are made to demonstrate empty parking slots.
void slot1(){
if(digitalRead(iRPin1)==HIGH){
  Blynk.virtualWrite(V0,255);
  slotFilled++;
  }
if(digitalRead(iRPin1)==LOW){
  Blynk.virtualWrite(V0,0);
  slotFilled--;
  }  
}
void slot2(){
if(digitalRead(iRPin2)==HIGH){
  Blynk.virtualWrite(V1,255);
  slotFilled++;
  }
if(digitalRead(iRPin2)==LOW){
  Blynk.virtualWrite(V1,0);
  slotFilled--;
  }  
}
void slot3(){
if(digitalRead(iRPin3)==HIGH){
  Blynk.virtualWrite(V2,255);
  slotFilled++;
  }
if(digitalRead(iRPin3)==LOW){
  Blynk.virtualWrite(V2,0);
  slotFilled--;
  }  
}
void slot4(){
if(digitalRead(iRPin4)==HIGH){
  Blynk.virtualWrite(V3,255);
  slotFilled++;
  }
if(digitalRead(iRPin4)==LOW){
  Blynk.virtualWrite(V3,0);
  slotFilled--;
  }  
}
//entrySide and exitSide functions are made for opening and closing of gate.
void entrySide(){
if(digitalRead(iRPin5)==HIGH){
   if(slotFilled<maxSlot){
    motorRun();
    }
  else{
    tone(piezoPin,1000,3000);
    delay(500);
    noTone(piezoPin);
    }  
  }
}
void exitSide(){
if(digitalRead(iRPin6)==HIGH){
  motorRun();
  }  
}
