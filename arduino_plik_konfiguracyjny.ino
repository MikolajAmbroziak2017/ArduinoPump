const int waterSensorPin=12;
const int relayPin=13;
const int buttonOnPin=1;
const int buttonOffPin=2;
const int redDiodPin=3;
const int isAutomatSwitchPin=4;
const int isAutomatDiodPin=5;
int isRun=0;
int isAutomatic=0;
int pTime=2;
void setup() {
  // water sensor return LOW signal when detect water on the bord 
    pinMode(waterSensorPin, INPUT);
  // two buttons start and stop   
    pinMode(buttonOnPin, INPUT);
    pinMode(buttonOffPin, INPUT);    
    pinMode(isAutomatSwitchPin, INPUT); 
 // relay must be set as HIGH signal to the current flow (current=prąd)  
    pinMode(relayPin, OUTPUT);
 // Diode pins   
    pinMode(isAutomatDiodPin, OUTPUT);
    pinMode(redDiodPin, OUTPUT);  
}

void loop() {
 isAutomatic = digitalRead(isAutomatSwitchPin);
 if (isAutomatic==HIGH){
   startStop();
   if(isRun==HIGH)
   automatic();
   }
 else if(isAutomatic==LOW)
   manual();
}

// functionaly run only if buttonON is HIGH and buttonOFF is LOW 
// when  buttonON is LOW and buttonOFF is LOW, state isRun do not change a condition, 
// because this  juxtaposition can be when user isnt cliking any button, at the moment . 
 void startStop(){
  if(digitalRead(buttonOnPin)==HIGH&&digitalRead(buttonOffPin)==LOW)
  isRun= HIGH;
  else if (digitalRead(buttonOnPin)==HIGH&&digitalRead(buttonOffPin)==HIGH)
  isRun= LOW;
 else if (digitalRead(buttonOnPin)==LOW&&digitalRead(buttonOffPin)==HIGH)
  isRun= LOW;
  } 
  
 void automatic(){
  //musi być po sprawdzeniu czy start !!!!!
  digitalWrite(isAutomatDiodPin,HIGH);
  if(digitalRead(waterSensorPin)==LOW){
    digitalWrite(redDiodPin,HIGH);
    for(int i=0;i<pTime;i++){
      if(isRun==HIGH)
      automaticPomp();
       if(isRun==LOW)
      break;
      }
      digitalWrite(relayPin,LOW);
      digitalWrite(redDiodPin,LOW);
    }
  }
  
 void automaticPomp(){
    digitalWrite(relayPin,HIGH);
    delay(60000);
    startStop();
    }
 void manual(){
  digitalWrite(isAutomatDiodPin, LOW);
  do 
  {
    startStop();
    if(isRun==LOW)
    break;
    digitalWrite(relayPin, HIGH);
    digitalWrite(redDiodPin, HIGH);
    }while(isRun==HIGH);
    digitalWrite(redDiodPin, LOW);
    digitalWrite(relayPin, LOW);
  }
