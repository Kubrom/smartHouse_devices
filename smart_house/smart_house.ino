/*
 * Here is a list of all the commands according  to the command protocol
 * 1: indoor Lights ON
 * 2: indoor Lights OFF
 * 3: outdoor Lights ON
 * 4: outdoor Lights OFF
 * 5: radiator ON
 * 6: radiator OFF
 * 7: internal temperature
 * 8: external temperature
 * 9: electricity consumption
 * 10: fan ON
 * 11: fan OFF
 */
//list of all needed variables

const int PIN_a=12;
const int PIN_b=13;
const int PIN_c=11;
const int PIN_d=8;
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

unsigned int incomingCommandByte = 0; // for incoming serial data
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


void setup() {
  // put your setup code here, to run once:
<<<<<<< Updated upstream
  Serial.begin(9600);
   pinMode(PIN_a, OUTPUT);
   pinMode(PIN_b, OUTPUT);
   pinMode(PIN_c, OUTPUT);
   pinMode(PIN_d, OUTPUT);
   pinMode(PIN_water_leakage, INPUT);
   pinMode(PIN_stove, INPUT);
   pinMode(PIN_fire_alarm, INPUT);
   pinMode(PIN_window, INPUT);
   pinMode(PIN_tempIn, INPUT);
   pinMode(PIN_tempOut, INPUT);
   pinMode(PIN_housebreaking_alarm, INPUT);
   attachInterrupt(digitalPinToInterrupt(PIN_housebreaking_alarm), houseBreakingAlarm, LOW);
   pinMode(PIN_elCon, INPUT);
   pinMode(PIN_ats, INPUT);
   pinMode(PIN_fan, OUTPUT);   
   analogWrite(PIN_fan, 0);
   pinMode(PIN_powerCut,INPUT);

   timer1OFF();
   timer2OFF();
   Serial.println("Welcome to the Smart house");
  
  
=======
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

>>>>>>> Stashed changes
}

void loop() {
  automaticTwilightSystem();
  
  smartHousePanel(); //methods to control the switches at the smart house.
       
   while (Serial.available() > 0){
  incomingCommandByte = Serial.read() - '0';
  
    if( incomingCommandByte == 1){
    indoorLightsON();
    incomingCommandByte = 0;
    }
     else if( incomingCommandByte == 2){
    indoorLightsOFF();
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 3){
    outdoorLightsON();
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 4){
    
    outdoorLightsOFF();
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 5){
    radiatorON();
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 6){
    radiatorOFF();
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 7){
    getInternalTemperature();
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 8){
    getExternalTemperature();
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 9){
    electricityConsumption();
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 10){
    fanON();
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 11){
    fanOFF();
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 12){
    getExternalTemperatureFahr();
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 13){
    getInternalTemperatureFahr();
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 14) {
     powerCut();
     incomingCommandByte = 0;
    }
}
}

void powerCut(){

digitalWrite(PIN_a, LOW);
   digitalWrite(PIN_b, LOW);
   digitalWrite(PIN_c, HIGH);
   digitalWrite(PIN_d, LOW);

analogRead(PIN_powerCut);// 
int buttonState = 0;
  Serial.print("Powercut");
}


void automaticTwilightSystem(){
//turns on outdoorlight when it's dark outside  
int ldrStatus = analogRead(PIN_ats);
if(ldrStatus <= 150){
  outdoorLightsON();
   Serial.println("LDR is dark and light is ON");
} 
else{
  outdoorLightsOFF();
}
}
 
void fanON(){
  analogWrite(PIN_fan, 100);
  //turns ON the fan 
}

void fanOFF(){
  analogWrite(PIN_fan, 0);
  //turns OFF the fan
}


 double getInternalTemperature(){
  //method to get internal temperature
  //LM35C
  float tempc;
  float vout;
  vout=analogRead(PIN_tempIn);
  vout=(vout*500)/1023;
  tempc=vout;
  Serial.print("Indoor Temperature in Celsius: " );
  Serial.print(tempc);
  Serial.print("");
  delay(500); 
  }

double getInternalTemperatureFahr(){
  float tempc;
  float vout;
  vout=analogRead(PIN_tempIn);
  vout=(vout*500)/1023;
  tempc=vout;
  float tempInF = (tempc * 9) / 5 + 32;
  Serial.print("Indoor Temperature in Fahrenheit: " );
  Serial.print(tempInF);
  Serial.print("");
  delay(500); 
}

 void getExternalTemperature(){
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

 void getExternalTemperatureFahr(){
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

 void electricityConsumption(){
  //method to calculate current electricity consumption
    float voltageOnA0;
    voltageOnA0 = analogRead(PIN_elCon) / 1023.0 * 1.1;
    Serial.println(voltageOnA0);
    delay(1000);
    
  }


   void sendWaterLeakageState(){
      if(waterLeakage_state == HIGH){
        //send message to server to tell there is water leakage
        }
        else if (waterLeakage_state == LOW){
          ////send message to server to tell there is no  water leakage
          }
      }

      
      void sendWindowState(){
      if(window_state == HIGH){
        //send message to server to tell there is water leakage
        }
        else if (window_state == LOW){
          ////send message to server to tell there is no  water leakage
          }
      }

      
      void sendStoveState(){
      if(stove_state == HIGH){
        //send message to server to tell there is water leakage
        }
        else if (stove_state == LOW){
          ////send message to server to tell there is no  water leakage
          }
      }

      
      void sendFireAlarmState(){
      if(fireAlarm_state == HIGH){
        Serial.println("Fire alarm ON!");//send message to server to tell there is water leakage
        fireAlarmON();
        delay(100);
        }
        else if (fireAlarm_state == LOW){
          Serial.println("Fire alarm OFF!");//send message to server to tell there is no  water leakage
          fireAlarmOFF();
          delay(100);
          }
      }
 void indoorLightsON(){
  //method to turn on  indoor light 0010

   digitalWrite(PIN_a, LOW);
   digitalWrite(PIN_b, LOW);
   digitalWrite(PIN_c, HIGH);
   digitalWrite(PIN_d, LOW);
   
  }
 
 void indoorLightsOFF(){
//method to turn off  indoor lights 1010

   digitalWrite(PIN_a, HIGH);
   digitalWrite(PIN_b, LOW);
   digitalWrite(PIN_c, HIGH);
   digitalWrite(PIN_d, LOW);
   
  
  }


 void outdoorLightsON(){
  //method to turn on outdoor lights 0111

   digitalWrite(PIN_a, LOW);
   digitalWrite(PIN_b, HIGH);
   digitalWrite(PIN_c, HIGH);
   digitalWrite(PIN_d, HIGH);
   
  }
  
 void outdoorLightsOFF(){
  //method to turn on outdoor lights 1111
  
   digitalWrite(PIN_a, HIGH);
   digitalWrite(PIN_b, HIGH);
   digitalWrite(PIN_c, HIGH);
   digitalWrite(PIN_d, HIGH);
 
  }
  
 void radiatorON(){
//  method to turn on radiator 0101

   digitalWrite(PIN_a, LOW);
   digitalWrite(PIN_b, HIGH);
   digitalWrite(PIN_c, LOW);
   digitalWrite(PIN_d, HIGH);
  
  }

  
void radiatorOFF(){
  //method to turn off radiator 1101

   digitalWrite(PIN_a, HIGH);
   digitalWrite(PIN_b, HIGH);
   digitalWrite(PIN_c, LOW);
   digitalWrite(PIN_d, HIGH);
  
  }

void timer1ON(){
  //method to turn on timer 2 0100
   digitalWrite(PIN_a, LOW);
   digitalWrite(PIN_b, HIGH);
   digitalWrite(PIN_c, LOW);
   digitalWrite(PIN_d, LOW);
  
}

void timer1OFF(){
  //method to turn off the timer (2) 1100
   digitalWrite(PIN_a, HIGH);
   digitalWrite(PIN_b, HIGH);
   digitalWrite(PIN_c, LOW);
   digitalWrite(PIN_d, LOW);
   
}

void timer2ON(){
  //method to turn on timer 2 0001
   digitalWrite(PIN_a, LOW);
   digitalWrite(PIN_b, LOW);
   digitalWrite(PIN_c, LOW);
   digitalWrite(PIN_d, HIGH);
  
}

void timer2OFF(){
  //method to turn off the timer (2) 1001
   digitalWrite(PIN_a, HIGH);
   digitalWrite(PIN_b, LOW);
   digitalWrite(PIN_c, LOW);
   digitalWrite(PIN_d, HIGH);
  
}

  void fireAlarmON(){
  //method to turn on fire alarm sound 1000
  digitalWrite(PIN_a ,HIGH);
  digitalWrite(PIN_b ,LOW);
  digitalWrite(PIN_c ,LOW);
  digitalWrite(PIN_d ,LOW);
 
  }
  
   void fireAlarmOFF(){
  //method to turn off fire alarm sound 0000
 
  digitalWrite(PIN_a ,LOW);
  digitalWrite(PIN_b ,LOW);
  digitalWrite(PIN_c ,LOW);
  digitalWrite(PIN_d ,LOW);
 
  }

  void houseBreakingAlarm(){
  //method to turn on housebreaking alarm 
    digitalWrite(PIN_a ,HIGH);
    digitalWrite(PIN_b ,LOW);
    digitalWrite(PIN_c ,LOW);
    digitalWrite(PIN_d ,LOW);
    
     }

  
     

  void smartHousePanel(){
    
  waterLeakage_state = digitalRead(PIN_water_leakage);
  delay(100);
  stove_state = digitalRead(PIN_stove);
  delay(100);
  fireAlarm_state = digitalRead(PIN_fire_alarm);
  sendFireAlarmState();
  delay(100);
  window_state = digitalRead(PIN_window);
  delay(100);
<<<<<<< Updated upstream
 if(stove_state == HIGH || waterLeakage_state == HIGH || fireAlarm_state == HIGH || window_state == HIGH) {
  timer2ON();
  delay(100);
    }
 if(stove_state == LOW && waterLeakage_state == LOW && fireAlarm_state == LOW && window_state == LOW) {
  timer2OFF();
  delay(100);
      } 
    }

    
  
=======
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
  String old_something; 
  String old_somethings;
if (digitalRead(PIN_powerCut)== HIGH) {
  String something = "Power on";
  if (something != old_something) 
  Serial.println(something);
  old_something = something;
}
else if (digitalRead(PIN_powerCut) == LOW){
  String somethings = "Power off";
  if (somethings != old_somethings);
  Serial.println (somethings); 
  old_somethings = somethings;
}
}
>>>>>>> Stashed changes
