// IM CURRENTLY WORKING ON THIS IN MY FEW AMOUNT OF FREE TIME AFTER WORK. //

/*void mqttReconnect(){
// Loop until we're reconnected
       while (!mqttClient.connected()){
    Serial.println("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (mqttClient.connect(MQTTid,MQTTuser,MQTTpass)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");;
    }
  }
}
bool checkBound(float newValue, float prevValue, float maxDiff) {
  return !isnan(newValue) &&
         (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff);
}

long lastMsg = 0;
float tem1 = 0.0;
float hum1 = 0.0;
float tem2 = 0.0;
float hum2 = 0.0;
float diff = 1.0;
       
void dhtMQTTsend(){
if (!mqttClient.connected())
{
  mqttReconnect();
  }
  mqttClient.loop();

  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;

    if (checkBound(tempPOK, tem1, diff)) {
      tem1 = tempPOK;
      Serial.print("MQTT POK New temperature:");
      Serial.println(String(tem1).c_str());
      mqttClient.publish("terruino/dhtPOK/temp", String(tem1).c_str(), true);
    }
    if (checkBound(humiPOK, hum1, diff)) {
      hum1 = humiPOK;
      Serial.print("MQTT POK New humidity:");
      Serial.println(String(hum1).c_str());
      mqttClient.publish("terruino/dhtPOK/humi", String(hum1).c_str(), true);
    }
      if (checkBound(tempTER, tem2, diff)) {
      tem2 = tempTER;
      Serial.print("MQTT TER New temperature:");
      Serial.println(String(tem2).c_str());
      mqttClient.publish("terruino/dhtTER/temp", String(tem2).c_str(), true);
    }
      if (checkBound(humiTER, hum2, diff)) {
      hum2 = humiTER;
      Serial.print("MQTT TER New humidity:");
      Serial.println(String(hum2).c_str());
      mqttClient.publish("terruino/dhtTER/humi", String(hum2).c_str(), true);
      
      }
  }
 
}

*/
