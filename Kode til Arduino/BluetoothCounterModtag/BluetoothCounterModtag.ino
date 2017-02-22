#include <SoftwareSerial.h>
int bluetoothTx = 4;
int bluetoothRx = 5;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);//Arduino RX,Tx
char msg;
int counter = 0;
void setup(){
  Serial.begin(9600);
  bluetooth.begin(115200);//standard bluetooth mate
}

void loop(){
  bluetooth.listen();
  modtagFraBluetooth();
  Serial.println(counter);
  bluetooth.println(counter);
  counter++;
  delay(10);
}

void modtagFraBluetooth(){
  char msg;
  if(bluetooth.available()){ 
    msg= (char)bluetooth.read(); 
    if(msg=='Forward') {
      forward();
    }
    else if(msg =='Back'){
      back();
    }      

    else if (msg =='Right') {
      right();  
    }

    else if (msg =='Left') {
      left();
    }

    
    
    
    bluetooth.print(msg); //returner det modtagne
  }
}

void forward(){
  digitalWrite(input1,HIGH);
  digitalWrite(input2,LOW);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  
}

void back() {
  digitalWrite(input1,LOW);
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
 
}

void left() {
  digitalWrite(input1,HIGH);
  digitalWrite(input2,LOW);
  digitalWrite(input3,LOW);
  digitalWrite(input4,LOW);
  
}

void right() {
  digitalWrite(input1,LOW);
  digitalWrite(input2,LOW);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  
}

void stopMotors() {
  digitalWrite(input1,LOW);
  digitalWrite(input2,LOW);
  digitalWrite(input3,LOW);
  digitalWrite(input4,LOW);  

}

