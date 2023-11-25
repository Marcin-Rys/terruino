/*-----PINOUT-----*/
#define TFT_CS D11 //TFT PIN CS
#define TFT_RST D0   //TFT PIN RST
#define TFT_DC  D9   //TFT PIN DC
  
 /*      //LIGHT RELAY PIN
#define relayHEAT D8      //HEAT RELAY PIN
#define relayFAN D4       //FAN RELAY PIN
*/

/*------------------ WIFI------------------*/
char ssid[] = "";     // Wifi SSID
char pass[] = "";     // Wifi Password

/*---------------SEND/GET Data-----------*/
WiFiUDP ntpUDP;
WiFiClient wifiClient;                                        // Starting and declaring a WifiUDP and WiFiClient
NTPClient timeClient(ntpUDP, "tempus1.gum.gov.pl", 7200);     //7200 - value for Warsaw timezone.
PubSubClient mqttClient(wifiClient);                          //Starting MQTT Client   

//MQTT Server
/*const char* MQTTserver = "";
const int MQTTport = 0000;
const char* MQTTid = "";
const char* MQTTuser = "";
const char* MQTTpass = "";
*/

/*------------------ TERRARIUM VALUE SETTING ------------------*/
float tempMIN = 35.00;
float tempMAX = 40.00;
float humiMIN = 30.00;
float humiMAX = 65.00;
int lightOn_hour = 7;
int lightOn_min = 0;
int lightOff_hour = 21;
int lightOff_min = 30;
int timeZone = 2;
float humiTER, tempTER;
float humiPOK, tempPOK;
boolean lightVal, heatVal, fanVal;

/*------------------ DHT SETTING ------------------*/
DHTesp dht_TER;   //Declaring a terrarium sensor
DHTesp dht_POK;   //Declaring a room sensor

/*-----------------PERIODS FOR MILLIS----------------*/
int period60sec = 60000;
int period30sec = 30000;
int period10sec = 10000;
int period5sec = 5000;
int period1sec = 1000;
unsigned long time_now = 0;

/*------------------ VERSION ------------------*/
String p1 = " ";
const char* terruinoVersion = "0.0.1a";   //Version of Terruino
