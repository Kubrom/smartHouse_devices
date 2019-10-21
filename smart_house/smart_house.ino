
//list of all needed variables

const int PIN_a=12;
const int PIN_b=13;
const int PIN_c=11;
const int PIN_d=8;
int incomingCommandByte = 0; // for incoming serial data





void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Welcome to the Smart house");
   pinMode(PIN_a, OUTPUT);
   pinMode(PIN_b, OUTPUT);
   pinMode(PIN_c, OUTPUT);
   pinMode(PIN_d, OUTPUT);
   
   
   

}

void loop() {
   while (Serial.available() > 0){
 
  incomingCommandByte = Serial.read() - '0';
  
    if( incomingCommandByte == 1){
    indoorLightsON();
    incomingCommandByte = 0;
    }
     else if( incomingCommandByte == 2){
    //indoorLightsOFF();
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 3){
    //outdoorLightsON();
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 4){
    
    //outdoorLightsON();
    incomingCommandByte = 0;
    }
    else if( incomingCommandByte == 5){

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
   Serial.println("indoor Light on");
  
  }


 void outdoorLightsON(){
  //method to turn on outdoor lights

   digitalWrite(PIN_a, LOW);
   digitalWrite(PIN_b, HIGH);
   digitalWrite(PIN_c, HIGH);
   digitalWrite(PIN_d, HIGH);
   Serial.println("indoor Light on");
  }
  
 void outdoorLightsOFF(){
  //method to turn on outdoor lights
  
   digitalWrite(PIN_a, HIGH);
   digitalWrite(PIN_b, HIGH);
   digitalWrite(PIN_c, HIGH);
   digitalWrite(PIN_d, HIGH);
   Serial.println("indoor Light on");
  }
  
 void radiatorON(){
//  method to turn on radiator
  }

  
void radiatorOFF(){
  //method to turn off radiator
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
  //method to turn  fire alarm
  }
  
 void fireAlarmOFF(){
  //method to turn off fire alarm}
}
