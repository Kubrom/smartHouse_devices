#include <SoftwareSerial.h>
SoftwareSerial s(0,1);

//#include <ArduinoJson.h>

/*
  Device id's  since in our case we have 1 house and 1 room  the initial 2 integers of the command protocol are 11
  1101 indoorLight (to add 0 for OFF and 1 for ON)
  1102 outDoorLigh (to add 0 for OFF and 1 for ON)
  1103 radiator (to add 0 for OFF and 1 for ON)
  1104 fan: (to add 0 for OFF and 1 for ON)

  get sensor value ( GET = 3 according to the protocol)
  11053 internalTemp (to add 1 for celsius and 2 for fahrenheit) 
  11063 ExternalTemp (to add 1 for celsius and 2 for fahrenheit)
  11073 electricConsumption 
  alarm
  1108 fireAlarmState (to add 0 for OFF and 1 for ON)
  1109 waterLeakageState (to add 0 for OFF and 1 for ON)
  1110 houseBreakingAlarm (to add 0 for OFF and 1 for ON)
  1111 window (to add 0 for OFF and 1 for ON)
  1112 stove (to add 0 for OFF and 1 for ON)
  1113 powercut (to add 0 for OFF and 1 for ON)
*/

int var;


//variables needed for communicatiing with NodeMCU

String fromNodemcu;
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
void smartHousePanel();
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
  
    attachInterrupt(digitalPinToInterrupt(PIN_housebreaking_alarm), houseBreakingAlarm, LOW);
    timer1OFF();
    timer2OFF();
  
  Serial.println("Welcome to the Smart house");

}

void loop() {


  automaticTwilightSystem();
  smartHousePanel();

  if (Serial.available() > 0 ) {
    fromNodemcu    = Serial.readString();
    Serial.println(fromNodemcu);
  }

  switch (fromNodemcu.toInt()) {

    case 11011://indoor light on
      indoorLightsON();
      fromNodemcu = "";
      break;

    case 11010://indoor light off
      indoorLightsOFF();
      fromNodemcu = "";
      break;

    case 11021://outdoor ligth on
      outdoorLightsON();
      fromNodemcu = "";
      break;

    case 11020://outdoor light off
      outdoorLightsOFF();
      fromNodemcu = "";
      break;

    case 11031://indoor heater on
      radiatorON();
      fromNodemcu = "";
      break;

    case 11030://indoor heater off
      radiatorOFF();
      fromNodemcu = "";
      break;
      
    case 11041:// turn smart house fan on
      fanON();
      fromNodemcu = "";
      break;

    case 11040:// turn smart house fan off
      fanOFF();
      fromNodemcu = "";
      break;

    case 110531:// get the value of internal temperature in celsius
      getInternalTemperature();
      fromNodemcu = "";
      
      break;

    case 110532:// get internal temperature in fahrenheit
      getInternalTemperatureFahr();
      fromNodemcu = "";
      break;

    case 110631://get the value of the external temperature in celsisus
      getExternalTemperature();
      fromNodemcu = "";
      break;


    case 110632:// get external temperature in fahrenheit
      getExternalTemperatureFahr();
      fromNodemcu = "";
      break;

    case 11073:// get the total electric consumption
      electricityConsumption();
      fromNodemcu = "";
      break;

    case 14:// method for testing purposes
      testLedOn();
      fromNodemcu = "";
      break;

    case 15:// method for testing purposes
      testLedOff();
      fromNodemcu = "";
      break;


  }

}


void testLedOn() {
  timer2ON();
  Serial.println("led Test on");
}

void testLedOff() {
  fireAlarmOFF();
  Serial.println("led Test off");
}




void automaticTwilightSystem() {
  //turns on outdoorlight when it's dark outside
  int ldrStatus = analogRead(PIN_ats);
  if (ldrStatus > 150 && var == 1) {
    outdoorLightsOFF();
    Serial.println("light is OFF");
    Serial.println(ldrStatus);
    var = 0;
    Serial.println(var);
  }
  else if (ldrStatus <= 150) {
    outdoorLightsON();
    Serial.println("LDR is dark and light is ON");
    Serial.println(ldrStatus);
    var = 1;
    Serial.println(var);
  }
}

void fanON() {
  analogWrite(PIN_fan, 100);
  Serial.println("11041");

  //turns ON the fan
}

void fanOFF() {
  analogWrite(PIN_fan, 0);
  Serial.println("11040");
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
  String response = "110531 = " + stringVal;
  Serial.print(response);
  delay(500);
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
  String response = "110532 = " + stringVal;
  Serial.print(response);
  delay(500);
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
  String response = "110631 = " + stringVal;
  Serial.print(response);

  delay(500);
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
  String response = "110632 = " + stringVal;
  Serial.print(response);
  delay(1000);

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
  String response = "11073 = " + stringVal;
  Serial.print(response);
  delay(1000);

}


void sendWaterLeakageState() {
  if (waterLeakage_state == HIGH) {
    //send message to server to tell there is water leakage
  Serial.println("11091");
  }
  else if (waterLeakage_state == LOW) {
    ////send message to server to tell there is no  water leakage
  Serial.println("11090");
  }
}


void sendWindowState() {
  if (window_state == HIGH) {
    //send message to server to tell there is water leakage
  Serial.println("11111");
  }
  else if (window_state == LOW) {
    ////send message to server to tell there is no  water leakage
  Serial.println("11110");
  }
}


void sendStoveState() {
  if (stove_state == HIGH) {
    //send message to server to tell there is water leakage
  Serial.println("11121");
  }
  else if (stove_state == LOW) {
    ////send message to server to tell there is no  water leakage
  Serial.println("11120");
  }
}


void sendFireAlarmState() {
  if (fireAlarm_state == HIGH) {

    fireAlarmON();
    delay(100);
  }
  else if (fireAlarm_state == LOW) {

    fireAlarmOFF();
    delay(100);
  }
}
void indoorLightsON() {
  //method to turn on  indoor light 0010

  digitalWrite(PIN_a, LOW);
  digitalWrite(PIN_b, LOW);
  digitalWrite(PIN_c, HIGH);
  digitalWrite(PIN_d, LOW);
  Serial.println("11011");

}

void indoorLightsOFF() {
  //method to turn off  indoor lights 1010

  digitalWrite(PIN_a, HIGH);
  digitalWrite(PIN_b, LOW);
  digitalWrite(PIN_c, HIGH);
  digitalWrite(PIN_d, LOW);
Serial.println("11010");

}


void outdoorLightsON() {
  //method to turn on outdoor lights 0111

  digitalWrite(PIN_a, LOW);
  digitalWrite(PIN_b, HIGH);
  digitalWrite(PIN_c, HIGH);
  digitalWrite(PIN_d, HIGH);
Serial.println("11021");
}

void outdoorLightsOFF() {
  //method to turn on outdoor lights 1111

  digitalWrite(PIN_a, HIGH);
  digitalWrite(PIN_b, HIGH);
  digitalWrite(PIN_c, HIGH);
  digitalWrite(PIN_d, HIGH);
Serial.println("11020");
}

void radiatorON() {
  //  method to turn on radiator 0101

  digitalWrite(PIN_a, LOW);
  digitalWrite(PIN_b, HIGH);
  digitalWrite(PIN_c, LOW);
  digitalWrite(PIN_d, HIGH);
Serial.println("11031");
}


void radiatorOFF() {
  //method to turn off radiator 1101

  digitalWrite(PIN_a, HIGH);
  digitalWrite(PIN_b, HIGH);
  digitalWrite(PIN_c, LOW);
  digitalWrite(PIN_d, HIGH);
Serial.println("11030");
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
Serial.println("11081");
}

void fireAlarmOFF() {
  //method to turn off fire alarm sound 0000

  digitalWrite(PIN_a , LOW);
  digitalWrite(PIN_b , LOW);
  digitalWrite(PIN_c , LOW);
  digitalWrite(PIN_d , LOW);
Serial.write("11080\n");
}

void houseBreakingAlarm() {
  //method to turn on housebreaking alarm
  digitalWrite(PIN_a , HIGH);
  digitalWrite(PIN_b , LOW);
  digitalWrite(PIN_c , LOW);
  digitalWrite(PIN_d , LOW);
Serial.println("11101");
}


void smartHousePanel() {

  waterLeakage_state = digitalRead(PIN_water_leakage);
  delay(100);
  stove_state = digitalRead(PIN_stove);
  delay(100);
  fireAlarm_state = digitalRead(PIN_fire_alarm);
  sendFireAlarmState();
  delay(100);
  window_state = digitalRead(PIN_window);
  delay(100);
  if (stove_state == HIGH || waterLeakage_state == HIGH || fireAlarm_state == HIGH || window_state == HIGH) {
    timer2ON();
    delay(100);
  }
  if (stove_state == LOW && waterLeakage_state == LOW && fireAlarm_state == LOW && window_state == LOW) {
    timer2OFF();
    delay(100);
  }
}

void powerCut() {

}

void initialize() {

}
