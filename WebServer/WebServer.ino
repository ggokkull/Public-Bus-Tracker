/*
 WiFiEsp example: WebServer

 A simple web server that shows the value of the analog input 
 pins via a web page using an ESP8266 module.
 This sketch will print the IP address of your ESP8266 module (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to display the web page.
 The web page will be automatically refreshed each 20 seconds.

 For more details see: http://yaab-arduino.blogspot.com/p/wifiesp.html
*/

#include "WiFiEsp.h"

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(4,5); // RX, TX
#endif

char ssid[] = "22";            // your network SSID (name)
char pass[] = "";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
int reqCount = 0;                // number of requests received

WiFiEspServer server(80);
void  printWifiStatus();

String X;

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);
  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");
  printWifiStatus();
  
  // start the web server on port 80
  server.begin();
}


void loop()
{
  int n = WiFi.scanNetworks();
  
    for (int i = 0; i < n; i++)
    {
      //  Serial.println(WiFi.SSID(i));
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

  // listen for incoming clients
  WiFiEspClient client = server.available();
  if (client && a=="22") {
    Serial.println("New client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          Serial.println("Sending response");
          
          // send a standard http response header
          // use \r\n instead of many println statements to speedup data send
          client.print(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"  // the connection will be closed after completion of the response
            "Refresh: 20\r\n"        // refresh the page automatically every 20 sec
            "\r\n");
          client.print("<!DOCTYPE HTML>\r\n");
          client.print("<html>\r\n");
          client.print("<table style=");
          client.print("width:100%");
          client.print(">");
          client.print("<tr><th>Bus Number</th>");
          client.print("<th>Distance</th>");
          client.print("<th>Arrival Time</th>");
          client.print("<th>Departure Time</th>");
          client.print("</tr>");   
             client.print("<tr>");
             client.print("<th>22</th>");
             client.print("<th>");
             client.print(X);
             client.print("</th>");
             client.print("<th>1:15</th>");   
                         client.print("<th>1:15</th>");   
                              
          
    
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(10);

    // close the connection:
    client.stop();
    Serial.println("Client disconnected");
  }
}
}


void printWifiStatus()
{
  // print the SSID of the network you're asttached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  
  // print where to go in the browser
  Serial.println();
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
  Serial.println();
}
