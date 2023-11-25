
/*TODO: 
- at mqtt reconnect change from millis to delay
- add full remote controll and for safety offline constant value for maintaining temperature.
- add heating and fan relays, connect it to web mqtt server.
- apply dusk2dawn to check if there should be switched on automated lightning and heating, depending on the time of the day.

/*Thanks to this tutorials, they get me here ;)
  * https://www.instructables.com/id/TerraControl-V10-With-NodeMCU-Webserver/ - Basic idea
  * https://github.com/taranais/NTPClient NTPClient with formatteddate string
  * https://github.com/taranais/NTPClient CHANGED in String NTPClient::getFormattedDate(unsigned long secs) {  "+ "T" + this->getFormattedTime(secs ? secs : 0) + "Z"" - DELETED

*/
/*-------Libraries and settings-------*/
#include <ESP8266WiFi.h> //To get wifi connection
#include <PubSubClient.h> //To communicate with HomeAssistant/Database with MTQQ protocol
#include <NTPClient.h> //Library to connect with local time server
#include <WiFiUdp.h> //For NTP Client communication - maybe i'll rework that.
#include <time.h>
#include <Adafruit_ST7735.h> //TFT display library
#include <Adafruit_GFX.h> //TFT display library
#include <DHTesp.h> //DHT Thermometer/Higromether library
#include "settings.h"
#include "tft.h"
#include "mqtt.h"

bool statusFAN;
bool statusHEAT;

void setup(void) {
 Serial.begin(115200);
 delay(100);
 Serial.print("Welcome to Terruino" + p1 + terruinoVersion);

/*---Initialize 1.8" TFT ST7735S chip, black tab, you can choose REDTAB, GREENTAB as you wish---*/
tftInit();
/*---WiFi connecting and status on LCD, getting time---*/
 Serial.println();
  WiFi.begin(ssid, pass);                 //Change ssid and pass in settings.h
  Serial.print("Connecting");
  Serial.println("");
    while (WiFi.status() != WL_CONNECTED)
    {
    delay(500);
    Serial.print(".");
    tft.setCursor(50, 85);
    tft.setTextColor(White, Grey);
    tft.print("Laczenie.");
    }
  tft.println("");
   Serial.println("");       
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  tft.setCursor(15, 100);
  tft.print("Connected, IP address: ");
  tft.setCursor(40, 110);
  tft.println(WiFi.localIP());  
  delay(5000);
 
/*---Starting and setting the temperature and humidity control sensors---*/
  dht_TER.setup(D3, DHTesp::DHT22);
  dht_POK.setup(D4, DHTesp::DHT22);

/*---Starting up NTP time library---*/
  timeClient.begin();

/*---Loading a TFT screen drawings---*/
  tftSetup();

/*---Setup for the MQTT Broker---*/

/*mqttClient.setServer(MQTTserver,MQTTport);
//mqttClient.setCallback(callback_function); */
}

void loop(){
/*---EST8266 dht commands to get humidity and temperature from sensors---*/
  humiTER = dht_TER.getHumidity();
  tempTER = dht_TER.getTemperature();
  humiPOK = dht_POK.getHumidity();
  tempPOK = dht_POK.getTemperature();
   
  
  
 if (tempTER > tempMAX || humiTER > humiMAX)  {
  digitalWrite(relayFAN, HIGH);}
 else {
   digitalWrite(relayFAN, LOW);
}
if (digitalRead(relayFAN) == HIGH && statusFAN == false) {
  Serial.println();
  Serial.print("Włączono wentylator");
  statusFAN = true;
}
if (digitalRead(relayFAN) == LOW && statusFAN == true){
  Serial.println();
  Serial.print("Wyłączono wentylator");
  statusFAN = false;
}

if (tempTER < tempMIN) {
  digitalWrite(relayHEAT, HIGH);}
else {
    digitalWrite(relayHEAT, LOW);
}


if (digitalRead(relayHEAT) == HIGH && statusHEAT == false) {
  Serial.println();
  Serial.print("Włączono ogrzewanie");
  statusHEAT = true;
}
if (digitalRead(relayHEAT) == LOW && statusHEAT == true){
  Serial.println();
  Serial.print("Wyłączono ogrzewanie");
  statusHEAT = false;
}
tftLoop();
}


/*
 * 
 * WORK IN PROGRESS
 * 
 */

/*---Posting and getting data to server---*/

/*if (millis() >= time_now + period1sec) //Sending data via MQTT with 30sec period
    {  
       time_now = millis();  
dhtMQTTsend();

    }
}
*/










 /* if (millis() >= time_now + period30sec) //Sending data via HTTP with 30sec period
    {  
       time_now = millis();  
       dhtMQTTSend();
       //relaystatusPOST();
      //relaysettingGET("fan","FAN");
       //relaysettingGET("heat","Heating");
       
    }
*/


  






/*
 *  WARNING-  DEPRECEATED
 *   THIS IS OLD VERSION OF POSTING AND GETTING DATA, NOW I USE MQTT, AS THE HTTP PUSHING IS NOT SECURE, USE AT OWN RISK.
 *   I WAS USING THIS TUTORIALS/DOCS TO GET IT WORKING, IF YOU WANNA - YOU CAN MAKE IT YOURSELF TO WORK!
 *   https://randomnerdtutorials.com/esp32-esp8266-mysql-database-php/
 *   http://ice786pk.com/how-to-read-data-from-database-with-php-for-wemos-eps8266/ 
 */



/*-----SENDING DHT SENSORS DATA TO .PHP SCRIPT ON SERVER
  void dhtstatusPOST(){
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    String url = serverPHP+"esp8266-dhtstatus-post.php";
    // Your Domain name with URL path or IP address with path
    http.begin(url);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data with values from DHT sensors
    String httpRequestData = "api_key=" + apiKeyValue + "&sensorlocation1=" + "dhtTER"
                          + "&temp1=" + String(tempTER) + "&humi1=" + String(humTER)
                          + "&sensorlocation2=" +"dhtPOK" + "&temp2=" + String(tempPOK) + "&humi2=" + String(humPOK) + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // Send HTTP POST request with values
    int httpResponseCode = http.POST(httpRequestData);
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
      else {
          Serial.print("Error code: ");
          Serial.println(httpResponseCode);
          }
    // Free resources
    http.end();
  }
      else {
    Serial.println("WiFi Disconnected");
          }
  }

 void relaystatusPOST(){
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    String url = serverPHP+"esp8266-relaystatus-post.php";
    // Your Domain name with URL path or IP address with path
    http.begin(url);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data with values from DHT sensors
    String httpRequestData = "api_key=" + apiKeyValue + "&heatstatus=" + heatVal
                          + "&fanstatus=" + fanVal + "&lightstatus=" + lightVal + "";                    
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // Send HTTP POST request with values
    int httpResponseCode = http.POST(httpRequestData);
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
      else {
          Serial.print("Error code: ");
          Serial.println(httpResponseCode);
          }
    // Free resources
    http.end();
  }
      else {
    Serial.println("WiFi Disconnected");
          }
  }

  /*-----GETING RELAY SETTINGS FROM .PHP SCRIPT ON SERVER
void relaysettingGET(String relay_name, String relay_text)
  {
 
        HTTPClient http;
        String url = serverPHP+"esp8266-relaysetting-get.php?relay_name="+relay_name;
        
        http.begin(url);
       
        //GET method
        int httpCode = http.GET();
        String payload = http.getString();
        if(payload=="1")
        {
          Serial.println(relay_text+" is ON");
        }
        else
        {
          Serial.println(relay_text+" is Off");
          }
        http.end();
  }
*/
