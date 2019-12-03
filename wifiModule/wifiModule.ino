
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Guest";
const char* password = "test1234";

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting...");
  }

  int res=sendmessage("Hi,Server");
  delay(1000);
  if (res==1)
  {
    Serial.println("Send Successfully");
  }
  else
  {
    Serial.println("Error on Server side or client side.");
  }
}

void loop() 


{
  String data=receivelastmessage();
  int response=validatemessage(data);
  if (response==1)
  {
    Serial.print("Message Received from client : ");
    Serial.println(data);
    handleresponse(data);
  }
  /*
  if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http; //Object of class HTTPClient
    http.begin("http://houseserver.000webhostapp.com/datastorage.txt");
    int httpCode = http.GET();

    if (httpCode > 0) 
    {
      const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      DynamicJsonDocument doc(bufferSize);
      DeserializationError error = deserializeJson(doc,http.getString());
      if(error){
       Serial.print("deserializeJson() failed with code");
       Serial.println(error.c_str());
       return;
        } 
      
 
      int id = doc["id"]; 
      const char* name = doc["name"]; 
      const char* username = doc["username"]; 
      const char* email = doc["email"]; 

      Serial.print("Name:");
      Serial.println(name);
      Serial.print("Username:");
      Serial.println(username);
      Serial.print("Email:");
      Serial.println(email);
    }
    http.end(); //Close connection
  }
  delay(60000);
  */
}
String receivelastmessage()
{
  String lastmessage="";
  if(WiFi.status()==WL_CONNECTED)
  {
    HTTPClient http;
    String url="http://houseserver.000webhostapp.com/public_html/datastorage.txt";
    http.begin(url);
    http.addHeader("Content-Type","text/plain");
    int httpCode=http.GET();
    String data=http.getString();
    lastmessage=getlastline(data);
    http.end();
  }
  else
  {
    lastmessage="";
  }
  return lastmessage;
}

String getlastline(String str)
{
  String s="";
  int len=str.length();
  for (int i=len-2;i>=0;i--)
  {
    if (str[i]=='\n')
    {
      break;
    }
    else
    {
      s=s+str[i];
    }
  }
  String rs="";
  for (int i=s.length()-1;i>=0;i--)
  {
    rs=rs+s[i];
  }
  return rs;
}

int validatemessage(String message)
{
  String sender="";
  for (int i=0;i<message.length();i++)
  {
    if (message[i]==':')
    {
      break;
    }
    else
    {
      sender=sender+message[i];
    }
  }
  if (sender=="client")
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void handleresponse(String message)
{
  Serial.println("Sending reply to client.");
  String mes="";
  for (int i=7;i<message.length();i++)
  {
    mes=mes+message[i];
  }
  if (mes=="hello,server")
  {
    int response=sendmessage("server:hello,client");
    if (response==1)
    {
      Serial.println("Replied Successfully.");
    }
    else
    {
      Serial.println("Error! Check Internet Connection or Server Error!");
    }
  }
}

int sendmessage(String d)
{
  int sres;
  int net;
  if (WiFi.status()==WL_CONNECTED)
  {
    HTTPClient http;
    String url="http://rihatax.000webhostapp.com/writefile.php?data="+d;
    http.begin(url);
    http.addHeader("Content-Type","text/plain");
    int httpCode=http.GET();
    String payload=http.getString();
    Serial.println("While sending I received this from server : "+payload);
    if (payload=="SUCCESS. Data written in file.")
    {
      sres=1;
    }
    else
    {
      sres=0;
    }
    http.end();
    net=1;
  }
  else
  {
    Serial.println("Internet Problem!");
    net=0;
  }
  return (net && sres);
}
