
//list of all needed variables

const int PIN_a=12;
const int PIN_b=13;
const int PIN_c=11;
const int PIN_d=8;
const int PIN_water_leakage = 4;
const int PIN_stove = 5;
const int PIN_fire_alarm = 2;
const int PIN_window = 6;

int incomingCommandByte = 0; // for incoming serial data
int reading_water_leakage; // used to read switch values
int reading_stove; // used to read switch values
int reading_fire_alarm; // used to read switch values
int reading_window; // used to read switch values







void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Welcome to the Smart house");
   pinMode(PIN_a, OUTPUT);
   pinMode(PIN_b, OUTPUT);
   pinMode(PIN_c, OUTPUT);
   pinMode(PIN_d, OUTPUT);
   pinMode(PIN_water_leakage, INPUT);
   
   
   

}

void loop() {
  //Switch water leakage
   reading_water_leakage = digitalRead(PIN_water_leakage);
   if(reading_water_leakage == HIGH) {
   timer2ON();
    }
    if(reading_water_leakage == LOW) {
   timer2OFF();
      }

//Switch for stove
    reading_stove = digitalRead(PIN_stove);
   if(reading_stove == HIGH) {
  timer2ON();
    }
    if(reading_stove == LOW) {
  timer2OFF();
      }   

   //Switch for fire alarm
   reading_fire_alarm = digitalRead(PIN_fire_alarm);
   if(reading_fire_alarm == HIGH) {
  timer2ON();
  fireAlarmON();
    }
    if(reading_fire_alarm == LOW) {
  timer2OFF();
  fireAlarmOFF();
      }   

   //Switch for window

    reading_window = digitalRead(PIN_window);
   if(reading_window == HIGH) {
  timer2ON();
    }
    if(reading_window == LOW) {
  timer2OFF();
      }   


      //--------------
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
    else if( incomingCommandByte == 8){
    
    incomingCommandByte = 0;
    }
}
}
 
 void indoorLightsON(){
  //method to turn on  indoor lights

   digitalWrite(PIN_a, LOW);
   digitalWrite(PIN_b, LOW);
   digitalWrite(PIN_c, HIGH);
   digitalWrite(PIN_d, LOW);
   Serial.println("indoor Light on");
   
  }

  
 
 void indoorLightsOFF(){
//method to turn off  indoor lights

   digitalWrite(PIN_a, HIGH);
   digitalWrite(PIN_b, LOW);
   digitalWrite(PIN_c, HIGH);
   digitalWrite(PIN_d, LOW);
   Serial.println("indoor Light off");
  
  }


 void outdoorLightsON(){
  //method to turn on outdoor lights

   digitalWrite(PIN_a, LOW);
   digitalWrite(PIN_b, HIGH);
   digitalWrite(PIN_c, HIGH);
   digitalWrite(PIN_d, HIGH);
   Serial.println("outdoor Light on");
  }
  
 void outdoorLightsOFF(){
  //method to turn on outdoor lights
  
   digitalWrite(PIN_a, HIGH);
   digitalWrite(PIN_b, HIGH);
   digitalWrite(PIN_c, HIGH);
   digitalWrite(PIN_d, HIGH);
   Serial.println("outdoor Light off");
  }
  
 void radiatorON(){
//  method to turn on radiator

   digitalWrite(PIN_a, LOW);
   digitalWrite(PIN_b, HIGH);
   digitalWrite(PIN_c, LOW);
   digitalWrite(PIN_d, HIGH);
   Serial.println("radiator inside On");
  }

  
void radiatorOFF(){
  //method to turn off radiator

   digitalWrite(PIN_a, HIGH);
   digitalWrite(PIN_b, HIGH);
   digitalWrite(PIN_c, LOW);
   digitalWrite(PIN_d, HIGH);
   Serial.println("radiator inside On");
  }

  
 double getInternalTemperature(){
  //method to get internal temperature
  }
  
double getExternalTemperature(){
 // method to get external temperature 
 }

 
void stoveON(){
  //method to turn the stove on
}


void stoveOFF(){
  //method to turn the stove off
}


void windowOPEN(){
  //method to open the windows
}

void timer2ON(){
  //method to turn on timer 2
   digitalWrite(PIN_a, LOW);
   digitalWrite(PIN_b, LOW);
   digitalWrite(PIN_c, LOW);
   digitalWrite(PIN_d, HIGH);
   Serial.println("timer 2 Light On");
}

void timer2OFF(){
  //method to turn off the timer (2)
   digitalWrite(PIN_a, HIGH);
   digitalWrite(PIN_b, LOW);
   digitalWrite(PIN_c, LOW);
   digitalWrite(PIN_d, HIGH);
   Serial.println("timer 2 Light Off");
}


void windowCLOSE(){
  //method to close the windows}
}


void waterLeakageON(){
  //method to signal water leakage
  
}


void waterLeakegeOFF(){
  //method to turn off water leakage signal
  }
  

  void fireAlarmON(){
  //method to turn on fire alarm sound
  digitalWrite(PIN_a ,HIGH);
  digitalWrite(PIN_b ,LOW);
  digitalWrite(PIN_c ,LOW);
  digitalWrite(PIN_d ,LOW);
  Serial.println("Fire Alarm is ON");
  }
  
   void fireAlarmOFF(){
  //method to turn off fire alarm sound
 
  digitalWrite(PIN_a ,LOW);
  digitalWrite(PIN_b ,LOW);
  digitalWrite(PIN_c ,LOW);
  digitalWrite(PIN_d ,LOW);
  Serial.println("Fire Alarm is OFF");
  }
