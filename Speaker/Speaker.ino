
#include <SD.h>                      // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 10  //using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>
#include <WiFiEsp.h>
#include <SoftwareSerial.h>
TMRpcm tmrpcm;   // create an object for use in this sketch

SoftwareSerial Serial1(4, 5); // RX, TX 
void setup() {

  tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc

  Serial.begin(9600);
  Serial1.begin(9600);    
  SD.begin(SD_ChipSelectPin);
   WiFi.init(&Serial1); 
   //the sound file "music" will play each time the arduino powers up, or is reset
}
int c=0,d=0;


void loop() {
  int n = WiFi.scanNetworks();
  Serial.println("scan done");

  if (n == 0)
   
    {
      Serial.println("no networks found");
     
    }
  else
  {
    for (int i = 0; i < n; i++)
    {

      String a = WiFi.SSID(i);
      
      if (a == "22" && c==0)
      {
    
         c++;
      }
       
if (a == "23" && d==0  )
      {
      d++;
      }
if(c==1)
{
      Serial.println(a);
       tmrpcm.setVolume(6);
  tmrpcm.play("22.wav");
   delay(5000);
   c=0;
}
if(d==1)
{
       //Serial.println(a);
       tmrpcm.setVolume(6);
  tmrpcm.play("23.wav");
   delay(5000);
d=0; 
}
  //delay(50000);
}
  }
  
  }


