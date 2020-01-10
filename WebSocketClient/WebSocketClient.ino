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


const char* ssid = "xxxx";
const char* password = "xxxx";

char path[] = "/HouseServer_war_exploded/sockets/arduino";
char host[] = "ec2-13-53-175-23.eu-north-1.compute.amazonaws.com";
  
WebSocketClient webSocketClient;

// Use WiFiClient class to create TCP connections
WiFiClient client;

void setup() {

  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

//  Serial.println();
//  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
  
 // WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    Serial.print(".");
  }

//  Serial.println("");
//  Serial.println("WiFi connected");  
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());

  delay(5000);
 
  

  // Connect to the websocket server
 
 if (client.connect(host, 9475)) {
   
    
  } else {
    Serial.println("Connection failed.");
    while(1) {
      // Hang on failure
    }
  }

  // Handshake with the server
  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    //Serial.println("Handshake successful");
    //webSocketClient.sendData("Handshake successfull");
    Serial.write("\nD");
    Serial.write("\nC");
    
  } else {
    //Serial.println("Handshake failed.");
    while(1) {
      // Hang on failure
    }  
  }
Serial.flush();
}


void loop() {

  if (client.connected()) {
    webSocketClient.getData(dataFromServer);
    
    if (dataFromServer.length() > 0) { 
     if(dataFromServer =="11011"){
      Serial.write("\nA");
     dataFromServer="";}
     
     else if(dataFromServer=="11010"){
      Serial.write("\nB");
     dataFromServer="";}

     else if(dataFromServer=="11021"){
      Serial.write("\nC");
     dataFromServer="";}

     else if(dataFromServer=="11020"){
      Serial.write("\nD");
     dataFromServer="";}

     else if(dataFromServer=="11031"){
      Serial.write("\nE");
     dataFromServer="";}

     else if(dataFromServer=="11030"){
      Serial.write("\nF");
     dataFromServer="";}

     else if(dataFromServer=="11041"){
      Serial.write("\nG");
     dataFromServer="";}

     else if(dataFromServer=="11040"){
      Serial.write("\nH");
     dataFromServer="";}

     else if(dataFromServer=="11053"){
      Serial.write("\nI");
     dataFromServer="";}
     
     else if(dataFromServer=="11063"){
      Serial.write("\nJ");
     dataFromServer="";}
     
      else if(dataFromServer=="11073"){
      Serial.write("\nK");
     dataFromServer="";}
     
       else if(dataFromServer=="11081"){
      Serial.write("\nL");
     dataFromServer="";}
     
       else if(dataFromServer=="11080"){
      Serial.write("\nM");
     dataFromServer="";}
     
       else if(dataFromServer=="11091"){
      Serial.write("\nN");
     dataFromServer="";}
     
       else if(dataFromServer=="11090"){
      Serial.write("\nO");
     dataFromServer="";}
     
       else if(dataFromServer=="11101"){
      Serial.write("\nP");
     dataFromServer="";}
     
       else if(dataFromServer=="11100"){
      Serial.write("\nQ");
     dataFromServer="";}
     
       else if(dataFromServer=="11111"){
      Serial.write("\nR");
     dataFromServer="";}
     
       else if(dataFromServer=="11110"){
      Serial.write("\nS");
     dataFromServer="";}
     
       else if(dataFromServer=="11121"){
      Serial.write("\nT");
     dataFromServer="";}
     
       else if(dataFromServer=="11120"){
      Serial.write("\nU");
     dataFromServer="";}

         else if(dataFromServer=="11131"){
      Serial.write("\nV");
     dataFromServer="";}

         else if(dataFromServer=="11130"){
      Serial.write("\nW");
     dataFromServer="";}

         else if(dataFromServer=="11141"){
      Serial.write("\nX");
     dataFromServer="";}

         else if(dataFromServer=="11140"){
      Serial.write("\nY");
     dataFromServer="";}

         else if(dataFromServer==""){
      Serial.write("\nZ");
     dataFromServer="";}
      
      
    }

     if (Serial.available() > 0 ) {
     fromArduinoRX     = Serial.readString();
    
     
     webSocketClient.sendData(fromArduinoRX);
     Serial.println(fromArduinoRX );
     fromArduinoRX = "";
    
  }
    
 
  } else {
    //Serial.println("Client disconnected.");
     webSocketClient.sendData("client disconnected");
  }
  
 
  //delay(3000);


  
}
