#include<PinChangeInterrupt.h>


//#include <ArduinoJson.h>

/*
  Device id's  since in our case we have 1 house and 1 room  the initial 2 integers of the command protocol are 11
  
  1101 indoorLight (to add 0 for OFF and 1 for ON) --> a,b 
  1102 outDoorLigh (to add 0 for OFF and 1 for ON) --> c,d
  1103 radiator (to add 0 for OFF and 1 for ON) --> e,f
  1104 fan: (to add 0 for OFF and 1 for ON) --> g,h

  get sensor value ( GET = 3 according to the protocol)
  
  11053 internalTemp (to add 1 for celsius and 2 for fahrenheit) --> i
  11063 ExternalTemp (to add 1 for celsius and 2 for fahrenheit) -->j
  11073 electricConsumption --> k
  
  alarm
 
  1108 fireAlarmState (to add 0 for OFF and 1 for ON) --> l,m
  1109 waterLeakageState (to add 0 for OFF and 1 for ON)--> n,o
  1110 houseBreakingAlarm (to add 0 for OFF and 1 for ON)--> p,q
  1111 window (to add 0 for OFF and 1 for ON)--> r,s
  1112 stove (to add 0 for OFF and 1 for ON)--> t,u
  1113 powercut (to add 0 for OFF and 1 for ON)-->v,w
  1114 twilight system -->x,y
*/

int var; // twilight system controller
const unsigned   long timeInterval = 4000;
unsigned long currentMillis;
unsigned long previousMillis = 0;


//variables needed for communicatiing with NodeMCU

String fromNodemcu ;
String toNodemcu;



const int PIN_a = 12;
const int PIN_b = 13;
const int PIN_c = 11;
const int PIN_d = 8;

const int PIN_water_leakage = 4; // physical switch that triggers water leakage.
const int PIN_stove = 5; //physical switch that triggers stove.
const int PIN_fire_alarm = 2; //physical switch that trigger fire alarm.
const int PIN_window = 6; // physical switch that trigger window.
const int PIN_housebreaking_alarm = 3; //Housebreaking Alarm

const int PIN_elCon = A0; // Electricity Consumption
const int PIN_fan = 10; // Pin for turning on and off the fan
const int PIN_ats = A3; // Automatic Twilight System
const int PIN_powerCut = 7; // Power Cut
const int PIN_tempIn = A1; // Indoor temperature pin.
const int PIN_tempOut = PB1; // Outdoor temperature pin.
int waterLeakage_state; // used to read  waterLeakage switch values
int stove_state; // used to read stove switch values
int fireAlarm_state; // used to read fireAlarm switch values
int window_state; // used to read window switch values
int houseBreakingalarm_state; // used to read house breaking alarm state

//list of all the prototypes of the functions created

double getInternalTemperature();
void getExternalTemperature();
void sendWaterLeakageState();
void smartHousePanel();
void sendWindowState();
void sendStoveState();
void sendFireAlarmState();
void indoorLightsON();
void indoorLightsOFF();
void outdoorLightsON();
void outdoorLightsOFF();
void radiatorON();
void radiatorOFF();
void fanON();
void fanOFF();
void electricityConsumption();
void timer1ON();
void timer1OFF();
void timer2ON();
void timer2OFF();
void fireAlarmON();
void fireAlarmOFF();
void automaticTwilightSystem();
void getExternalTemperatureFahr();
double getInternalTemperatureFahr();
void powerCut();
void testLedOn();
void testLedOff();

void initialize(); // method that send the initial state of the smart house to the server in the fist communication


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //outputs
  pinMode(PIN_a, OUTPUT);
  pinMode(PIN_b, OUTPUT);
  pinMode(PIN_c, OUTPUT);
  pinMode(PIN_d, OUTPUT);
  pinMode(PIN_fan, OUTPUT);
  analogWrite(PIN_fan, 0);
  //inputs
  pinMode(PIN_water_leakage, INPUT);
  pinMode(PIN_stove, INPUT);
  pinMode(PIN_fire_alarm, INPUT);
  pinMode(PIN_window, INPUT);
  pinMode(PIN_tempIn, INPUT);
  pinMode(PIN_tempOut, INPUT);
  pinMode(PIN_housebreaking_alarm, INPUT);
  pinMode(PIN_elCon, INPUT);
  pinMode(PIN_ats, INPUT);
  //intereputs
//PIN_fire_alarm = 2;
//PIN_housebreaking_alarm = 3; 
//PIN_water_leakage = 4;
//PIN_stove = 5;   
//PIN_window = 6; 

  attachInterrupt(digitalPinToInterrupt(PIN_fire_alarm),sendFireAlarmState,CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_housebreaking_alarm), sendHouseBreakingAlarmState, CHANGE);
    
  attachPCINT(digitalPinToPCINT( PIN_stove),sendWaterLeakageState,CHANGE);
 attachPCINT(digitalPinToPCINT( PIN_window),sendWindowState,CHANGE);
  attachPCINT(digitalPinToPCINT( PIN_water_leakage),sendWindowState,CHANGE);
 
  
  //Serial.println("welcome to the smart house");
  Serial.flush();

}

void loop() {
 
  if (Serial.available() > 0  ) {
    fromNodemcu    = char(Serial.read());
    //Serial.println(fromNodemcu);
   
    if(fromNodemcu == "A"){
      indoorLightsON();
      fromNodemcu="";
      }
    else if(fromNodemcu == "B"){
      indoorLightsOFF();
      fromNodemcu="";}
      
    else if(fromNodemcu == "C"){
      outdoorLightsON();
      fromNodemcu="";}
      
    else if(fromNodemcu == "D"){
      outdoorLightsOFF();
      fromNodemcu="";}
      
    else if(fromNodemcu == "E"){
      radiatorON();
      fromNodemcu="";}
      
    else if(fromNodemcu == "F"){
      radiatorOFF();
      fromNodemcu="";}
      
    else if(fromNodemcu == "G"){
      fanON();
      fromNodemcu="";}
      
    else if(fromNodemcu == "H"){
      fanOFF();
      fromNodemcu="";}
      
      else if(fromNodemcu == "I"){
        getInternalTemperature();
      fromNodemcu="";}
      
        else if(fromNodemcu == "J"){
          getExternalTemperature();
      fromNodemcu="";}
      
        else if(fromNodemcu == "K"){
           electricityConsumption();
      fromNodemcu="";}

       else if(fromNodemcu == "L"){
           fromNodemcu="";}

           else if(fromNodemcu == "M"){
           fromNodemcu="";}

           else if(fromNodemcu == "N"){
           fromNodemcu="";}
           
           else if(fromNodemcu == "O"){
           fromNodemcu="";}

           else if(fromNodemcu == "P"){
           fromNodemcu="";}

           else if(fromNodemcu == "Q"){
           fromNodemcu="";}

           else if(fromNodemcu == "R"){
           fromNodemcu="";}

           else if(fromNodemcu == "S"){
           fromNodemcu="";}

           else if(fromNodemcu == "T"){
           fromNodemcu="";}

           else if(fromNodemcu == "U"){
           fromNodemcu="";}

           else if(fromNodemcu == "V"){
           fromNodemcu="";}

            else if(fromNodemcu == "W"){
           fromNodemcu="";}

            else if(fromNodemcu == "X"){
           fromNodemcu="";}

            else if(fromNodemcu == "Y"){
           fromNodemcu="";}

            else if(fromNodemcu == "Z"){
           fromNodemcu="";}
     
  
   }
    automaticTwilightSystem();
    sendSensorsValueToServer();


}


void automaticTwilightSystem() {
  //turns on outdoorlight when it's dark outside
  int ldrStatus = analogRead(PIN_ats);
  if (ldrStatus > 150 && var == 1) {
     digitalWrite(PIN_a, HIGH);
  digitalWrite(PIN_b, HIGH);
  digitalWrite(PIN_c, HIGH);
  digitalWrite(PIN_d, HIGH);
Serial.println("11140");
    //Serial.println("light is OFF");
    //Serial.println(ldrStatus);
    var = 0;
    //Serial.println(var);
  }
  else if (ldrStatus <= 150 && var ==0) {
      digitalWrite(PIN_a, LOW);
  digitalWrite(PIN_b, HIGH);
  digitalWrite(PIN_c, HIGH);
  digitalWrite(PIN_d, HIGH);
Serial.println("11141");
    //Serial.println("LDR is dark and light is ON");
    //Serial.println(ldrStatus);
    var = 1;
    //Serial.println(var);
  }
}

void fanON() {
  analogWrite(PIN_fan, 100);
  Serial.write("\n11041");

  //turns ON the fan
}

void fanOFF() {
  analogWrite(PIN_fan, 0);
  Serial.write("\n11040");
  //turns OFF the fan
}


double getInternalTemperature() {
  //method to get internal temperature
  //LM35C
  float tempc;
  float vout;
  vout = analogRead(PIN_tempIn);
  vout = (vout * 500) / 1023;
  tempc = vout;
  //tempc is a float value in order to be concatinated to the string response it must be
  //coverted into a string value. in arduino float to string conversion is not straightforward.
  char charVal[10];               //temporarily holds data from vals 
  String stringVal = "";     //data on buff is copied to this string
  
  dtostrf(tempc, 4, 4, charVal);  //4 is mininum width, 4 is precision; float value is copied onto buff
  //convert chararray to string
  for(int i=0;i<sizeof(charVal);i++)
  {
    stringVal+=charVal[i];
  }
  String response = "11053" + stringVal;
  Serial.println(response);
 
}

double getInternalTemperatureFahr() {
  float tempc;
  float vout;
  vout = analogRead(PIN_tempIn);
  vout = (vout * 500) / 1023;
  tempc = vout;
  float tempInF = (tempc * 9) / 5 + 32;
  //tempInF is a float value in order to be concatinated to the string response it must be
  //coverted into a string value. in arduino float to string conversion is not straightforward.
  char charVal[10];               //temporarily holds data from vals 
  String stringVal = "";     //data on buff is copied to this string
  
  dtostrf(tempInF, 4, 4, charVal);  //4 is mininum width, 4 is precision; float value is copied onto buff
  //convert chararray to string
  for(int i=0;i<sizeof(charVal);i++)
  {
    stringVal+=charVal[i];
  }
  String response = "et110532 = " + stringVal;
  Serial.println(response);
  
}

void getExternalTemperature() {
  //method to get external temperature
  float tempOut;
  tempOut = analogRead(PIN_tempOut);
  tempOut = tempOut * 0.48828125;
    //tempOut is a float value in order to be concatinated to the string response it must be
  //coverted into a string value. in arduino float to string conversion is not straightforward.
  char charVal[10];               //temporarily holds data from vals 
  String stringVal = "";     //data on buff is copied to this string
  
  dtostrf(tempOut, 4, 4, charVal);  //4 is mininum width, 4 is precision; float value is copied onto buff
  //convert chararray to string
  for(int i=0;i<sizeof(charVal);i++)
  {
    stringVal+=charVal[i];
  }
  String response = "C11063 = " + stringVal;
  Serial.println(response);

}

void getExternalTemperatureFahr() {
  float tempOut;
  tempOut = analogRead(PIN_tempOut);
  tempOut = tempOut * 0.48828125;
  float tempOutF = (tempOut * 9) / 5 + 32;
  //tempOutF is a float value in order to be concatinated to the string response it must be
  //coverted into a string value. in arduino float to string conversion is not straightforward.
  char charVal[10];               //temporarily holds data from vals 
  String stringVal = "";     //data on buff is copied to this string
  
  dtostrf(tempOutF, 4, 4, charVal);  //4 is mininum width, 4 is precision; float value is copied onto buff
  //convert chararray to string
  for(int i=0;i<sizeof(charVal);i++)
  {
    stringVal+=charVal[i];
  }
  String response = "110632" + stringVal;
  Serial.println(response);
  

}

void electricityConsumption() {
  //method to calculate current electricity consumption
  float voltageOnA0;
  voltageOnA0 = analogRead(PIN_elCon) / 1023.0 * 1.1;
    // voltageOnA0 is a float value in order to be concatinated to the string response it must be
  //coverted into a string value. in arduino float to string conversion is not straightforward.
  char charVal[10];               //temporarily holds data from vals 
  String stringVal = "";     //data on buff is copied to this string
  
  dtostrf(voltageOnA0, 4, 4, charVal);  //4 is mininum width, 4 is precision; float value is copied onto buff
  //convert chararray to string
  for(int i=0;i<sizeof(charVal);i++)
  {
    stringVal+=charVal[i];
  }
  String response = "ec11073" + stringVal;
  Serial.println(response);
  

}


void sendWaterLeakageState() {
  waterLeakage_state = digitalRead(PIN_water_leakage);
  if (waterLeakage_state == HIGH) {
    //send message to server to tell there is water leakage
  Serial.write("\n11091");
  }
  else if (waterLeakage_state == LOW) {
    ////send message to server to tell there is no  water leakage
  Serial.write("\n11090");
  }
}


void sendWindowState() {
    window_state = digitalRead(PIN_window);
  if (window_state == HIGH) {
    //send message to server to tell there is water leakage
  Serial.write("\n11111");
  }
  else if (window_state == LOW) {
    ////send message to server to tell there is no  water leakage
  Serial.write("\n11110");
  }
}


void sendStoveState() {
  stove_state = digitalRead(PIN_stove);
  if (stove_state == HIGH) {
    //send message to server to tell there is water leakage
  Serial.write("\n11121");
  }
  else if (stove_state == LOW) {
    ////send message to server to tell there is no  water leakage
  Serial.write("\n11120");
  }
}


void sendFireAlarmState() {
  fireAlarm_state= digitalRead(PIN_fire_alarm);
  if (fireAlarm_state == HIGH) {

    fireAlarmON();
   
  }
  else if (fireAlarm_state == LOW) {

    fireAlarmOFF();
   
  }
}
void indoorLightsON() {
  //method to turn on  indoor light 0010

  digitalWrite(PIN_a, LOW);
  digitalWrite(PIN_b, LOW);
  digitalWrite(PIN_c, HIGH);
  digitalWrite(PIN_d, LOW);
  Serial.write("\n11011");

}

void indoorLightsOFF() {
  //method to turn off  indoor lights 1010

  digitalWrite(PIN_a, HIGH);
  digitalWrite(PIN_b, LOW);
  digitalWrite(PIN_c, HIGH);
  digitalWrite(PIN_d, LOW);
Serial.write("\n11010");

}


void outdoorLightsON() {
  //method to turn on outdoor lights 0111

  digitalWrite(PIN_a, LOW);
  digitalWrite(PIN_b, HIGH);
  digitalWrite(PIN_c, HIGH);
  digitalWrite(PIN_d, HIGH);
Serial.write("\n11021");
}

void outdoorLightsOFF() {
  //method to turn on outdoor lights 1111

  digitalWrite(PIN_a, HIGH);
  digitalWrite(PIN_b, HIGH);
  digitalWrite(PIN_c, HIGH);
  digitalWrite(PIN_d, HIGH);
Serial.write("\n11020");
}

void radiatorON() {
  //  method to turn on radiator 0101

  digitalWrite(PIN_a, LOW);
  digitalWrite(PIN_b, HIGH);
  digitalWrite(PIN_c, LOW);
  digitalWrite(PIN_d, HIGH);
Serial.write("\n11031");
}


void radiatorOFF() {
  //method to turn off radiator 1101

  digitalWrite(PIN_a, HIGH);
  digitalWrite(PIN_b, HIGH);
  digitalWrite(PIN_c, LOW);
  digitalWrite(PIN_d, HIGH);
Serial.write("\n11030");
}

void timer1ON() {
  //method to turn on timer 2 0100
  digitalWrite(PIN_a, LOW);
  digitalWrite(PIN_b, HIGH);
  digitalWrite(PIN_c, LOW);
  digitalWrite(PIN_d, LOW);

}

void timer1OFF() {
  //method to turn off the timer (2) 1100
  digitalWrite(PIN_a, HIGH);
  digitalWrite(PIN_b, HIGH);
  digitalWrite(PIN_c, LOW);
  digitalWrite(PIN_d, LOW);

}

void timer2ON() {
  //method to turn on timer 2 0001
  digitalWrite(PIN_a, LOW);
  digitalWrite(PIN_b, LOW);
  digitalWrite(PIN_c, LOW);
  digitalWrite(PIN_d, HIGH);

}

void timer2OFF() {
  //method to turn off the timer (2) 1001
  digitalWrite(PIN_a, HIGH);
  digitalWrite(PIN_b, LOW);
  digitalWrite(PIN_c, LOW);
  digitalWrite(PIN_d, HIGH);

}

void fireAlarmON() {
  //method to turn on fire alarm sound 1000
  digitalWrite(PIN_a , HIGH);
  digitalWrite(PIN_b , LOW);
  digitalWrite(PIN_c , LOW);
  digitalWrite(PIN_d , LOW);
Serial.write("\n11081");
}

void fireAlarmOFF() {
  //method to turn off fire alarm sound 0000

  digitalWrite(PIN_a , LOW);
  digitalWrite(PIN_b , LOW);
  digitalWrite(PIN_c , LOW);
  digitalWrite(PIN_d , LOW);
Serial.write("\n11080");
}

void sendHouseBreakingAlarmState() {
  //method to turn on housebreaking alarm
  houseBreakingalarm_state = digitalRead(PIN_housebreaking_alarm);
  if(houseBreakingalarm_state == LOW){
  digitalWrite(PIN_a , HIGH);
  digitalWrite(PIN_b , LOW);
  digitalWrite(PIN_c , LOW);
  digitalWrite(PIN_d , LOW);
Serial.write("\n11101");
}

 else if (houseBreakingalarm_state == HIGH){
   digitalWrite(PIN_a , LOW);
  digitalWrite(PIN_b , LOW);
  digitalWrite(PIN_c , LOW);
  digitalWrite(PIN_d , LOW);
  Serial.write("\n11100");}
}


void smartHousePanel() {
waterLeakage_state= digitalRead(PIN_water_leakage); 
stove_state= digitalRead(PIN_stove);
window_state = digitalRead(PIN_window);
houseBreakingalarm_state= digitalRead(PIN_housebreaking_alarm); 
  if (stove_state == HIGH || waterLeakage_state == HIGH || fireAlarm_state == HIGH || window_state == HIGH) {
    timer2ON();
  }
  if (stove_state == LOW && waterLeakage_state == LOW && fireAlarm_state == LOW && window_state == LOW) {
    timer2OFF();
  }
}

void powerCut() {
String old_something; 
String old_somethings;
if (digitalRead(PIN_powerCut)== HIGH) {
  String something = "Power on";
  if (something != old_something) 
  Serial.write("\n11131");
  old_something = something;
}
else if (digitalRead(PIN_powerCut) == LOW){
  String somethings = "Power off";
  if (somethings != old_somethings);
  Serial.write("\n11130"); 
  old_somethings = somethings;

}}

void sendSensorsValueToServer() {
//  const  long timeInterval = 20000;
//unsigned long urrentMillisc;
//unsigned long previousMillis;

currentMillis = millis();
if((currentMillis -  previousMillis) > timeInterval){
  previousMillis = currentMillis;
  getExternalTemperature();
  
  }
  
  

  

}
