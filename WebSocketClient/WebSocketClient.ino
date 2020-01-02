#include <Base64.h>
#include <global.h>
#include <MD5.h>
#include <sha1.h>
#include <WebSocketClient.h>
#include <WebSocketServer.h>

#include <ESP8266WiFi.h>
#include <WebSocketClient.h>


String toArduinoTX  ;
String fromArduinoRX ;

String dataFromServer;
String dataToServer;


const char* ssid = "EE-Hub-j3Gg";
const char* password = "ACRE-tag-rocky";

char path[] = "/houseserver/sockets/arduino";
char host[] = "194.47.41.79";
  
WebSocketClient webSocketClient;

// Use WiFiClient class to create TCP connections
WiFiClient client;

void setup() {

  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
/*
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  */
  WiFi.begin(ssid, password);
 /* 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(5000);
 
  
*/
  // Connect to the websocket server
  
  if (client.connect("194.47.41.79", 5678)) {
    //Serial.println("Connected to smart house");
  } else {
    //Serial.println("Connection failed.");
    while(1) {
      // Hang on failure
    }
  }

  // Handshake with the server
  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    //Serial.println("Handshake successful");
  } else {
    //Serial.println("Handshake failed.");
    while(1) {
      // Hang on failure
    }  
  }

}


void loop() {
 if (Serial.available() > 0 ) {
  
    fromArduinoRX     = Serial.readString();
    Serial.println(fromArduinoRX);
    
  }
  /*
  if (client.connected()) {
 
    webSocketClient.sendData("Connection successful");
    webSocketClient.getData(dataFromServer);
    if (dataFromServer.length() > 0) {
      
      Serial.print("Received data: ");
      Serial.println(dataFromServer);

        if (Serial.available() > 0 ) {
    fromArduinoRX     = Serial.readString();
     webSocketClient.sendData(fromArduinoRX);
     fromArduinoRX = "";
    
  }
    }
 
  } else {
    //Serial.println("Client disconnected.");
  }
 
  delay(3000);

*/
  
}
