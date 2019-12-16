//#include <ArduinoJson.h>

/*
  Device id's
  01 indoorLight
  02 outDoorLight
  03 radiator
  04 fan:

  sensor value
  05 internalTemp
  06 ExternalTemp
  07 electricConsumption
  alarm
  08 fireAlarmState
  09 waterLeakageState
  10 houseBreakingAlarm
*/


//variables needed for communicatiing with NodeMCU

String fromNodemucRX;
String toNodemucTX;



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

void sendJsonObjectResponse();


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
  /*
    attachInterrupt(digitalPinToInterrupt(PIN_housebreaking_alarm), houseBreakingAlarm, LOW);
    timer1OFF();
    timer2OFF();
  */
  Serial.println("Welcome to the Smart house");

}

void loop() {


  //automaticTwilightSystem();
  //smartHousePanel();

  if (Serial.available() > 0 ) {
    fromNodemucRX     = Serial.readString();
    Serial.println(fromNodemucRX);
  }

  switch (fromNodemucRX.toInt()) {

    case 11011://indoor light on
      indoorLightsON();
      fromNodemucRX = "";
      Serial.println("indoor lights on");
      break;

    case 11010://indoor light off
      indoorLightsOFF();
      fromNodemucRX = "";
      Serial.println("indoor lights off");
      break;

    case 11021://outdoor ligth on
      outdoorLightsON();
      fromNodemucRX = "";
      Serial.println(" outdoor ligth on");
      break;

    case 11020://outdoor light off
      outdoorLightsOFF();
      fromNodemucRX = "";
      Serial.println("outdoor light off ");
      break;

    case 11031://indoor heater on
      radiatorON();
      fromNodemucRX = "";
      Serial.println("indoor heater on ");
      break;

    case 11030://indoor heater off
      radiatorOFF();
      fromNodemucRX = "";
      Serial.println(" indoor heater off");
      break;
      
    case 11041:// turn smart house fan on
      fanON();
      fromNodemucRX = "";
      Serial.println("smart house fan on ");
      break;

    case 11040:// turn smart house fan off
      fanOFF();
      fromNodemucRX = "";
      Serial.println("smart house fan off ");
      break;

    case 110531:// get the value of internal temperature in celsius
      getInternalTemperature();
      fromNodemucRX = "";
      Serial.println("internal temperature in celsius ");
      break;

    case 110532:// get internal temperature in fahrenheit
      getInternalTemperatureFahr();
      fromNodemucRX = "";
      Serial.println("internal temperature in fahrenheit ");
      break;

    case 110631://get the value of the external temperature in celsisus
      getExternalTemperature();
      fromNodemucRX = "";
      Serial.println("external temperature in celsisus ");
      break;


    case 110632:// get external temperature in fahrenheit
      getExternalTemperatureFahr();
      fromNodemucRX = "";
      Serial.println(" external temperature in fahrenheit");
      break;

    case 11073:// get the total electric consumption
      electricityConsumption();
      fromNodemucRX = "";
      Serial.println(" electric consumption");
      break;

    case 14:// method for testing purposes
      testLedOn();
      fromNodemucRX = "";
      break;

    case 15:// method for testing purposes
      testLedOff();
      fromNodemucRX = "";
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
  if (ldrStatus <= 150) {
    outdoorLightsON();
  }
  else {
    outdoorLightsOFF();
  }
}

void fanON() {
  analogWrite(PIN_fan, 100);

  //turns ON the fan
}

void fanOFF() {
  analogWrite(PIN_fan, 0);
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
  Serial.print("Indoor Temperature in Celsius: " );
  Serial.print(tempc);
  Serial.print("");
  delay(500);
}

double getInternalTemperatureFahr() {
  float tempc;
  float vout;
  vout = analogRead(PIN_tempIn);
  vout = (vout * 500) / 1023;
  tempc = vout;
  float tempInF = (tempc * 9) / 5 + 32;
  Serial.print("Indoor Temperature in Fahrenheit: " );
  Serial.print(tempInF);
  Serial.print("");
  delay(500);
}

void getExternalTemperature() {
  //method to get external temperature
  float tempOut;
  tempOut = analogRead(PIN_tempOut);
  tempOut = tempOut * 0.48828125;
  Serial.print("Outdoor Temperature in Celsius: ");
  Serial.print(tempOut);
  Serial.print("*C");
  Serial.println();
  delay(1000);
}

void getExternalTemperatureFahr() {
  float tempOut;
  tempOut = analogRead(PIN_tempOut);
  tempOut = tempOut * 0.48828125;
  float tempOutF = (tempOut * 9) / 5 + 32;
  Serial.print("Outdoor Temperature in Fahrenheit: ");
  Serial.print(tempOutF);
  Serial.print("*F");
  Serial.println();
  delay(1000);

}

void electricityConsumption() {
  //method to calculate current electricity consumption
  float voltageOnA0;
  voltageOnA0 = analogRead(PIN_elCon) / 1023.0 * 1.1;
  Serial.println(voltageOnA0);
  delay(1000);

}


void sendWaterLeakageState() {
  if (waterLeakage_state == HIGH) {
    //send message to server to tell there is water leakage
  }
  else if (waterLeakage_state == LOW) {
    ////send message to server to tell there is no  water leakage
  }
}


void sendWindowState() {
  if (window_state == HIGH) {
    //send message to server to tell there is water leakage
  }
  else if (window_state == LOW) {
    ////send message to server to tell there is no  water leakage
  }
}


void sendStoveState() {
  if (stove_state == HIGH) {
    //send message to server to tell there is water leakage
  }
  else if (stove_state == LOW) {
    ////send message to server to tell there is no  water leakage
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

}

void indoorLightsOFF() {
  //method to turn off  indoor lights 1010

  digitalWrite(PIN_a, HIGH);
  digitalWrite(PIN_b, LOW);
  digitalWrite(PIN_c, HIGH);
  digitalWrite(PIN_d, LOW);


}


void outdoorLightsON() {
  //method to turn on outdoor lights 0111

  digitalWrite(PIN_a, LOW);
  digitalWrite(PIN_b, HIGH);
  digitalWrite(PIN_c, HIGH);
  digitalWrite(PIN_d, HIGH);

}

void outdoorLightsOFF() {
  //method to turn on outdoor lights 1111

  digitalWrite(PIN_a, HIGH);
  digitalWrite(PIN_b, HIGH);
  digitalWrite(PIN_c, HIGH);
  digitalWrite(PIN_d, HIGH);

}

void radiatorON() {
  //  method to turn on radiator 0101

  digitalWrite(PIN_a, LOW);
  digitalWrite(PIN_b, HIGH);
  digitalWrite(PIN_c, LOW);
  digitalWrite(PIN_d, HIGH);

}


void radiatorOFF() {
  //method to turn off radiator 1101

  digitalWrite(PIN_a, HIGH);
  digitalWrite(PIN_b, HIGH);
  digitalWrite(PIN_c, LOW);
  digitalWrite(PIN_d, HIGH);

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

}

void fireAlarmOFF() {
  //method to turn off fire alarm sound 0000

  digitalWrite(PIN_a , LOW);
  digitalWrite(PIN_b , LOW);
  digitalWrite(PIN_c , LOW);
  digitalWrite(PIN_d , LOW);

}

void houseBreakingAlarm() {
  //method to turn on housebreaking alarm
  digitalWrite(PIN_a , HIGH);
  digitalWrite(PIN_b , LOW);
  digitalWrite(PIN_c , LOW);
  digitalWrite(PIN_d , LOW);

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
