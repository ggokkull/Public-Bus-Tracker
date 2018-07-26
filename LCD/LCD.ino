
#include "WiFiEsp.h"
#include "SoftwareSerial.h"
#include "LiquidCrystal.h"
SoftwareSerial Serial1(4, 5); // RX, TX
LiquidCrystal lcd(14,15,16,17,18,19);
void checkPossibility();
void setup() {

  Serial.begin(9600);   // initialize serial for debugging
  Serial1.begin(9600);    // initialize serial for ESP module
  WiFi.init(&Serial1);    // initialize ESP module
  lcd.begin(16, 2);
}

void loop() 
{
  Serial.println("scan start");
  checkPossibility();
  Serial.println("");
  delay(5000);
}

String X;
int c=0,d=0;
void checkPossibility()
{
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  Serial.println(n);
  if (n == 0)
   
    {
      Serial.println("no networks found");
      lcd.println("no networks found");     
    }
  else
  {
    for (int i = 0; i < n; i++)
    {

      String a = WiFi.SSID(i);

              int  m=WiFi.RSSI(i);
      // Serial.println(m);
        m=m*(-1);
    if(m>=20 && m<=48)
    X="35m";
    if(m>=55 && m<=60)
     X="5m"; 
    if(m>=60 && m<=70)
    X="10m"; 
    if(m>=70 && m<=75)
    X="20m"; 
    if(m>=75 && m<=78)
    X="30m";
    if(m>=78 && m<=83)
    X="45m";
    if(m>=83 && m<=87)
    X="56m";
    if(m>=87 && m<=90)
    X="67m";
    if(m>=90 && m<=92)
    X="75m";


      if (a == "22")
      {
       Serial.println(a);
       lcd.setCursor(16,1);
       lcd.print("BUSNO:");
       Serial.println("BUSNO:");
       lcd.setCursor(0,2);
       lcd.print(a);
       Serial.print(a);
       delay(2000);
       lcd.clear();
       lcd.setCursor(16,1);
      Serial.println("");
       Serial.println("Distance:");
       lcd.print("Dist:");
       lcd.setCursor(0,2);
       Serial.print(X);
       lcd.print(X);
       delay(2000);
       lcd.clear(); 
       lcd.setCursor(16,1);
       lcd.print("ArTime");
       Serial.println("");
       Serial.println("Arrival Time:");
       lcd.setCursor(0,2);
       Serial.print("1-15PM");
       lcd.print("1-15PM");
       delay(2000);
       lcd.clear();
       lcd.setCursor(16,1);
       Serial.println("");
       Serial.println("Departure Time:");
       lcd.print("DeTime");
       lcd.setCursor(0,2);
       Serial.print("1-25PM");
       lcd.print("1-25PM");
       delay(5000);
       c++;
      }
       
if (a == "23" )
      {
       
       Serial.println(a);
       lcd.setCursor(16,1);
       lcd.print("BUSNO:");
       Serial.println("BUSNO:");
       lcd.setCursor(0,2);
       lcd.print(a);
       Serial.print(a);
       delay(2000);
       lcd.clear();
       lcd.setCursor(16,1);
       Serial.println("");
       Serial.println("Distance:");
       lcd.print("Dist:");
       lcd.setCursor(0,2);
       Serial.print(X);
       lcd.print(X);
       delay(2000);
       lcd.clear(); 
       lcd.setCursor(16,1);
       Serial.println("");
       lcd.print("ArTime");
       Serial.println("Arrival Time:");
       lcd.setCursor(0,2);
       Serial.println("1-15PM");
       lcd.print("1-25PM");
       delay(2000);
       lcd.clear();
       lcd.setCursor(16,1);
       Serial.print("");
       Serial.println("Departure Time:");
       lcd.print("DeTime");
       lcd.setCursor(0,2);
       Serial.print("1-25PM");
       lcd.print("1-25PM");
       delay(5000);
       d++;
      }      
      }
      
  //delay(50000);
 }
  }



