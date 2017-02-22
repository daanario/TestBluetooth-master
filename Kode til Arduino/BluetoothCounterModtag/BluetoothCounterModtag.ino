#include <SoftwareSerial.h>
const int bluetoothTx = 4;
const int bluetoothRx = 5;
const int triggerPin = 11;
const int echoPin = 12;
const int enable1 = 9;
const int enable2 = 10;
const int input1 = 3;
const int input2 = 2;
const int input3 = 8;
const int input4 = 7;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);//Arduino RX,Tx
char msg;
unsigned long int counter = 0;
void setup(){
  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(enable1,OUTPUT);
  pinMode(enable2,OUTPUT);
  pinMode(input1,OUTPUT);
  pinMode(input2,OUTPUT);
  pinMode(input3,OUTPUT);
  pinMode(input4,OUTPUT);
 
  Serial.begin(9600);
  bluetooth.begin(115200);//standard bluetooth mate


}
int Speed = 100;
void loop(){

  analogWrite(enable1,Speed);
  analogWrite(enable2,Speed);
  
  long duration, cm;
  digitalWrite(triggerPin,LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  cm = microSecondsToCentimeters(duration);
  if(cm > 400) {
    cm = 400;
  }
  if(cm < 10){
    stopMotors();
  }
  
  bluetooth.listen();
  modtagFraBluetooth();
  Serial.println(counter);
  bluetooth.println(counter);
  counter++;

  delay(10);

}

long microSecondsToCentimeters(long microseconds) {
    return microseconds / 58;
}

void modtagFraBluetooth(){
  char msg;
  if(bluetooth.available()){ 
    msg= (char)bluetooth.read(); 
    if(msg=='f') {
      forward();
    }
    else if(msg =='b'){
      back();
    }      

    else if (msg =='r') {
      right();  
    }

    else if (msg =='l') {
      left();
    }

    else if (msg =='s') {
      stopMotors();
    }
    
    else if (msg=='i') {
      incSpeed();
    }
    else if (msg=='d') {
      decSpeed();
    }
    
    bluetooth.print(msg); //returner det modtagne
  }
}

void incSpeed() {
  Speed += 25;
  if(Speed > 250) {
    Speed = 250;
  }
}

void decSpeed() {
  Speed -= 25;
  if(Speed < 25) {
    Speed = 25;
  }
  
}

void forward(){
  digitalWrite(input1,LOW);
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  
}

void back() {
  digitalWrite(input1,HIGH);
  digitalWrite(input2,LOW);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
 
}

void left() {
  digitalWrite(input1,LOW);
  digitalWrite(input2,LOW);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  
}

void right() {
  digitalWrite(input1,LOW);
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,LOW);
  
}

void stopMotors() {
  digitalWrite(input1,LOW);
  digitalWrite(input2,LOW);
  digitalWrite(input3,LOW);
  digitalWrite(input4,LOW);  

}





