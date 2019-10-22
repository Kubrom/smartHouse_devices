
//list of all needed variables

const int PIN_a=12;
const int PIN_b=13;
const int PIN_c=11;
const int PIN_d=8;
const int PIN_water_leakage = 4; // physical switch that triggers water leakage.
const int PIN_stove = 5; //physical switch that triggers stove.
const int PIN_fire_alarm = 2; //physical switch that trigger fire alarm.
const int PIN_window = 6; // physical switch that trigger window.

int incomingCommandByte = 0; // for incoming serial data
int waterLeakage_state; // used to read  waterLeakage switch values
int stove_state; // used to read stove switch values
int fireAlarm_state; // used to read fireAlarm switch values
int window_state; // used to read window switch values


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   pinMode(PIN_a, OUTPUT);
   pinMode(PIN_b, OUTPUT);
   pinMode(PIN_c, OUTPUT);
   pinMode(PIN_d, OUTPUT);
   pinMode(PIN_water_leakage, INPUT);
   pinMode(PIN_stove, INPUT);
   pinMode(PIN_fire_alarm, INPUT);
   pinMode(PIN_window, INPUT);
   timer1OFF();
   timer2OFF();
   Serial.println("Welcome to the Smart house");
  
}

void loop() {
  
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
    
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 8){
    
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 9){
    
    incomingCommandByte = 0;
    }
}
}

 double getInternalTemperature(){
  //method to get internal temperature
  }
  
double getExternalTemperature(){
 // method to get external temperature 
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
 if(stove_state == HIGH || waterLeakage_state == HIGH || fireAlarm_state == HIGH || window_state == HIGH) {
  timer2ON();
  delay(100);
    }
 if(stove_state == LOW && waterLeakage_state == LOW && fireAlarm_state == LOW && window_state == LOW) {
  timer2OFF();
  delay(100);
      } 
    }

    
  
