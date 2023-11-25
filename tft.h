/* PINOUT TFT SCREEN -> ESP8266 FROM LEFT:
 * 1. VCC 5/3.3V - VCC 5/3.3V 
 * 2. GND - GND
 * 3. CS - D10
 * 4. RESET - D8
 * 5. A0 - D9
 * 6. SDA - D11
 * 7. SCK - D13
 * 8. LED BACKLIGHT - 3.3V
 */


/*---------TFT STARTUP--------*/
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
  
/*---------COLORS FOR TFT--------*/
	  #define Black 0x0000
    #define Grey 0xC618
    #define GreyG 0x424A
    #define GreyT 0x530D
    #define Blue 0x4B78
    #define Red 0xF800
    #define BrownG 0xD575
    #define BrownT 0x72CC 
    #define Green 0x07E0
    #define Cyan 0x07FF
    #define Magenta 0xF81F
    #define Yellow 0xFFE0
    #define White 0xFFFF
    #define Pink  0xD1BC
    #define PinkT 0xE73E
    #define PinkBackground 0xF7BF
//defining colors by RGB565(http://www.barth-dev.de/online/rgb565-color-picker/), after name G=GUI rectangles etc, T=Text.


/*-----TFT CODE FOR void setup()-----*/
 void tftInit(){
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(Grey);//Filling background with color
  Serial.println("Display Started!");  //Serial information that display works
  Serial.println("");
  tft.setRotation(1);           //Setting screen rotation to landscape 
  tft.setCursor(15, 55);        //Down here there are just some commands to display information
  tft.setTextColor(PinkT);
  tft.setTextSize(1);
  tft.println("Welcome to Terruino" + p1 + terruinoVersion);
  delay(50);
  tft.setTextSize(1);
  tft.setTextColor(White);
  tft.setCursor(55, 70);
  tft.println("Scren OK!");
  delay(150);
  Serial.println("TFT Startup Ended");
 }
  
  void tftSetup(){
    //---DATA SCREEN DISPLAY ON LCD---//
  tft.fillScreen(PinkBackground);
 //Header
  tft.fillRect(2, 2, 156, 9, GreyG);
  tft.setCursor(3, 3);
  tft.setTextColor(Grey);
  tft.setTextSize(1);
  tft.println("Terruino" + p1 + terruinoVersion);
  //Rectangle for tmp TER and hum TER
  tft.fillRect(4, 13, 90, 30, BrownG);

  //Temperature_TERarium screen 
  tft.setCursor(6, 17);
  tft.setTextColor(Black);
  tft.println("Tmp TER:");
  tft.drawCircle(88, 17, 2, BrownT);

  //Humidity_TERrarium screen constants
  tft.setCursor(6, 32);
  tft.setTextColor(Black);
  tft.println("Hum TER:");
  tft.setCursor(80, 32);
  tft.setTextColor(GreyT);
  tft.println(" %");

  //Rectangle for Tmp POK and Hum POK
  tft.fillRect(4, 45, 90, 30, BrownG);

  //Temperature_POKoju screen 
  tft.setCursor(6 , 49);
  tft.setTextColor(Black);
  tft.println("Tmp POK:");
  tft.drawCircle(88, 49, 2, GreyT); //Circle for temperature icon

  //Humidity_POKoju screen 
  tft.setCursor(6, 63);
  tft.setTextColor(Black);
  tft.println("Hum POK:");
  tft.setCursor(80, 63);
  tft.setTextColor(GreyT);
  tft.println(" %");

  //Rectangle non-used
  tft.fillRect(4, 77, 90, 30, BrownG);

  //Sider for fans, relays etc
  tft.fillRect(96, 13, 60, 94, PinkT);
  
  //Footer !!! add warnings about temperature/humidity
  tft.fillRect(3, 118, 156, 9, GreyG);
  }

/*-----TFT CODE FOR void loop()-----*/
  void tftLoop(){
  /*---Temperature and humidity---*/
   tft.setCursor(53,17);
   tft.setTextColor(GreyT, BrownG);
   tft.print(tempTER);
   
  tft.setCursor(53, 32);
  tft.setTextColor(GreyT, BrownG);
  tft.print(humiTER);

  tft.setCursor(54, 49);
  tft.setTextColor(GreyT, BrownG);
  tft.print(tempPOK);

  tft.setCursor(54, 63);
  tft.setTextColor(GreyT, BrownG);
  tft.print(humiPOK);

  /*---Sider Relays info---*/
  tft.setCursor(97, 13);
  




 /*---Time and Date on header/footer---*/
  timeClient.update();
  tft.setTextColor(White, GreyG);
  tft.setCursor(109, 3);
  tft.print(timeClient.getFormattedTime());
  tft.setCursor(97, 119);
  tft.print(timeClient.getFormattedDate());

  /*---Footer WiFi, Temperature, Humidity Status---*/
  tft.setCursor(4, 119);
  if (WiFi.status() != WL_CONNECTED){
  tft.setTextColor(Red, GreyG);
  tft.println("WiFi");
  }
    else {
       tft.setTextColor(Green, GreyG);
      tft.println("WiFi");
      }
  tft.setCursor(33, 119);
  tft.setTextColor(Green, GreyG);{   
    if (tempTER < tempMIN){
    tft.setTextColor(Blue, GreyG);
    Serial.print("tempter niższa niż tempmax");
    }
    else if (tempTER > tempMAX){
    tft.setTextColor(Red, GreyG);
    Serial.print("tempter wyższa niż tempmax");
    }
  tft.println("Temp");
   }
   tft.setCursor(64, 119);
  tft.setTextColor(Green, GreyG);{   
    if (humiTER < humiMIN){
    tft.setTextColor(Blue, GreyG);
    }
    else if (humiTER > humiMAX){
    tft.setTextColor(Red, GreyG);
    }
  tft.println("Humi");
   }
  }
