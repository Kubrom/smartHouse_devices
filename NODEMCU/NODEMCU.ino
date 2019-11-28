// Use WiFiClient class to create TCP connections
 WiFiClient client;
 const int httpPort = 80;
 if (!client.connect(host, httpPort)) {
  Serial.println("connection failed");
  return;
 }

 // We now create a URI for the request
 String url = "/";

 Serial.print("Requesting URL: ");
 Serial.println(url);

 // This will send the request to the server
 client.print(String("GET ") + url + " HTTP/1.1\r\n" +
           "Host: " + host + "\r\n" + 
           "Connection: close\r\n\r\n");
 unsigned long timeout = millis();
 while (client.available() == 0) {
 if (millis() - timeout > 5000) {
  Serial.println(">>> Client Timeout !");
  client.stop();
  return;
 }
}

 // Read all the lines of the reply from server and print them to Serial
 while(client.available()){
  String line = client.readStringUntil('\r');
  Serial.print(line);
 }

 Serial.println();
 Serial.println("closing connection");
}
