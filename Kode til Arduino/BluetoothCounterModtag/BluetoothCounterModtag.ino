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
bool forwardActive = false;

//Alle pins angives som variabler, så de er nemmere at arbejde med.
//forwardActive bruges senere til at se, om en funktion er aktiv.
//SoftwareSerial-library skal bruges til bluetoothmodulet.

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
char msg;
unsigned long int counter = 0;
//der laves en char, som er beskeden bluetoothmodulet modtager.
//Der bruges en unsigned long integer til en tæller. Det er for at maksimere tiden, robotten kan bruges inden variablen indeholder for stort et tal.

void setup(){
  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin,INPUT);//Denne modtager ultralydspulsen
  pinMode(enable1,OUTPUT);//Denne udsender ultralydspulsen
  pinMode(enable2,OUTPUT);
  pinMode(input1,OUTPUT);
  pinMode(input2,OUTPUT);
  pinMode(input3,OUTPUT);
  pinMode(input4,OUTPUT);
 
  Serial.begin(9600);
  bluetooth.begin(115200);//standard bluetooth mate

  //Alle pins bliver sat til output eller input og bluetoothmodulet kan begynde at modtage beskeder.

}
int Speed = 100;//standardhastigheden
void loop(){

  analogWrite(enable1,Speed);
  analogWrite(enable2,Speed);

  //begge enable-pins bruges til at justere hastighed med. 
  
  long duration, cm;
  digitalWrite(triggerPin,LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  //der udsendes først en lille puls til at nulstille sensoren, og bagefter sendes den rigtige puls. Tiden måles.
  cm = microSecondsToCentimeters(duration); // denne funktion konverterer tid til sekunder.
  if(cm > 400) {
    cm = 400;
  }
  if(cm < 30 && forwardActive){
    stopMotors();
    forwardActive = false;
    //hvis der er mindre end 30 cm til et objekt og forward-funktionen er tændt, skal motorerne stoppes, så robotten ikke kører ind i noget. Bagefter nulstilles forwardActive, så man stadig kan bruge de andre funktioner.
  }
  
  bluetooth.listen();
  modtagFraBluetooth();
  Serial.println(counter);
  bluetooth.println(counter);
  counter++;

  delay(10);

  //Bluetoothmodulet modtager en besked og udsender en besked. Der ventes i 10 millisekunder og hele loopet kører igen.
  
}

long microSecondsToCentimeters(long microseconds) {
    return microseconds / 58;
    //funktionen, der konverterer mikrosekunder til cm.
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
    //Hele denne funktion består af If-statements, der aktiverer andre funktioner hvis den får en bestemt besked.
  }
}

void incSpeed() {
  Speed += 25;
  if(Speed > 250) {
    Speed = 250;
  }
}//En funktion til at forøge hastigheden. Kan ikke bliver større en 250.

void decSpeed() {
  Speed -= 25;
  if(Speed < 100) {
    Speed = 100;
  }//En funktion til at formindske hastigheden. Kan ikke blive mindre end 100.
  
}

void forward(){
  forwardActive = true;
  
  digitalWrite(input1,LOW);
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);

}//forward-funktionen. Den sætter forwardActive til at være true, så koden ved, hvornår forward-funktionen er tændt, og kan slukke for motorerne, hvis den forsøger at køre fremad mens der er noget i vejen.

void back() {
  digitalWrite(input1,HIGH);
  digitalWrite(input2,LOW);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
 
}//robotten kører tilbage

void left() {
  digitalWrite(input1,LOW);
  digitalWrite(input2,LOW);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  
}//robotten drejer til venstre

void right() {
  digitalWrite(input1,LOW);
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,LOW);
  
}//robotten drejer til højre

void stopMotors() {
  digitalWrite(input1,LOW);
  digitalWrite(input2,LOW);
  digitalWrite(input3,LOW);
  digitalWrite(input4,LOW);  

}//motorerne stopper




