#include "secrets.h"
#include "rfid.h"
#include "wifi.h"
#include "ntp.h"
#include "mqtt.h"

void checkWiFiThenMQTT(){
  connectToWiFi("Conectando ao WiFi");
  connectToMqtt();
}

void setup() {
  Serial.begin(115200);
  
  setupWifi();
  NTPConnect();
  setupSSL();
  setupMQTT();
  setupRFID();

  connectToMqtt();
}

void loop() {
  if (!client.connected()) {
    checkWiFiThenMQTT();
  } 
  else{
    client.loop();
    String id = getRFID();
    if(id != "" && id != oldResult){
      Serial.print("Enviando o id: ");
      Serial.println(id);
      sendData(id);
      oldResult = id;
    }
  }
}