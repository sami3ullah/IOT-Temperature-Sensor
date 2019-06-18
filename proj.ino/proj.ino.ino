#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <String.h>

const char* ssid = "Sami";
const char* password = "cd688835";

// Web server address
const char *host = "127.0.0.1"; 

int pinout = A0;
int analogValue;
float volts, celcius;
void setup () {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.println("Connecting..");
 
  }
 
}
 
void loop() {

 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    Serial.println("Connected");
    analogValue = analogRead(pinout);
    volts = (analogValue / 1024.0) * 5.0;
    celcius = volts * 100.0;
    String str, def;
    str = String(celcius);
    Serial.println(str);

    def = "http://127.0.0.1/demo/insert.php?status=" + str;
    //http://127.0ifcon.0.1/apis/insert.php?status=30.5
    Serial.println(def);
    HTTPClient http;  //Declare an object of class HTTPClient
  
    http.begin(def);     //Specify request destination
    
    int httpCode = http.GET();            //Send the request
    String payload = http.getString();    //Get the response payload
   
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
   
    http.end();  //Close connection
    
    delay(5000);  //GET Data at every 5 seconds  
 
//    http.begin(str);  //Specify request destination
//    int httpCode = http.GET();  //Send the GET request
//    Serial.println(httpCode);
//    if (httpCode > 0) { //Check the returning code
// 
//      String payload = http.getString();   //Get the request response payload
//      Serial.println(payload);                     //Print the response payload
// 
//    }
// 
//    http.end();   //Close connection
// 
//  }
// 
//  delay(15000);    //Send a request every 30 seconds
// 
  }
}
