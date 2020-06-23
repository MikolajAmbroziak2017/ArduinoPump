const int waterSens = A5; //define water sensor
const int led=7; //pin led
const int power=8; // 
const int button=6;
int waterVal; //define the water sensor value
int buttonVal;
int pumpTime=10000; //time of pumping water (1000 is 1 secound)


void setup() {
pinMode(waterSens, INPUT);  //set water sensor as an input
pinMode(power,OUTPUT);
pinMode(led, OUTPUT);
pinMode(button, INPUT);
Serial.begin(9600);
}

void loop() {
if(checkButton()||checkWaterStatus())
pump();
}

void pump(){
    Serial.println("PUMPING IS IN PROGRESS. . .");
    digitalWrite(power,HIGH);
    digitalWrite(led,HIGH);
    delay(pumpTime);
    digitalWrite(power,LOW);
    digitalWrite(led, LOW);
    }
    
boolean checkButton(){
  buttonVal=digitalRead(button);
  if(buttonVal==1)
    return true;
  return false;
  }
  
boolean checkWaterStatus(){
  //read water sensorfor
  digitalWrite(led,HIGH);
  int j=0;
  boolean status=false;
  for(int i=0;i<5;i++){
    waterVal=analogRead(waterSens);
 
    if(waterVal>300){
      delay(1000);
      j++;
      digitalWrite(led,LOW);
      delay(1000);
      }
      
    if(j==5){
      Serial.println("HIGH WATER LEVEL!");
      status=true;
      }

    if(waterVal<300){
      digitalWrite(led,LOW);
      delay(1000);
      digitalWrite(led,LOW);
      status=false;
      }
      
    digitalWrite(led,HIGH);
    }
  digitalWrite(led,LOW);
  return status;}
