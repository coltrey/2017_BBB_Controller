//Servo power is from the AA pack
//Arduino power is frome the 9V
//Common ground required between the battery systems

//Servos data pin is connected to D2 and D3
//Bluetooth is getting 3.3v power from the arduino, TX and RX connect to the RX and TX of the arduino microcontroller
//NOTE: to upload code you must remove the bluetooth with this setup

#include <Servo.h>
#include <SoftwareSerial.h>

Servo myservo1;
Servo myservo2;

Servo weaponServo;

//Sets up pins 4 and 5 to be used for serial communication (optional, not used in default configuration)
SoftwareSerial softSerial(5, 4); // RX, TX

char input = 'S';

const int WEAPON_SERVO_PIN = 5;

 typedef struct{
  int redPin;
  int greenPin;
  int bluePin;
} LED;

int servoPos = 0;
LED led1;
LED led2;

int RED[] = {LOW,HIGH,HIGH};
int OFF[] = {HIGH,HIGH,HIGH};
int WHITE[] = {LOW,LOW,LOW};
int GREEN[] = {HIGH,LOW,HIGH};
int BLUE[] = {HIGH,HIGH,LOW};




void initLed(LED led){
  pinMode(led.redPin,OUTPUT);
  digitalWrite(led.redPin,HIGH);
  pinMode(led.bluePin,OUTPUT);
   digitalWrite(led.bluePin,HIGH);
  pinMode(led.greenPin,OUTPUT);
   digitalWrite(led.greenPin,HIGH);
}

void setup() {
  //Setup serial connections for Monitor and Bluetooth
  softSerial.begin(9600);
  Serial.begin(9600);

  //Connects to the servos
  pinMode (2, OUTPUT);
  pinMode (3, OUTPUT);
 


  led1.redPin = 6;
  led1.bluePin = 7;
  led1.greenPin = 8;
  led2.redPin = 9;
  led2.bluePin = 11;
  led2.greenPin = 10;
  


  initLed(led1);
  initLed(led2);

  myservo1.attach(2);
  myservo2.attach(3);

  weaponServo.attach(WEAPON_SERVO_PIN);

  Serial.println("Setup Complete!");
}

void robotForward (int duration) {
  //myservo1.write(45);
  //myservo2.write(135);
   myservo1.write(0);
  myservo2.write(180);
}

void robotBackward (int duration) {
  myservo1.write(135);
  myservo2.write(45);
}

void robotRight (int duration) {
  myservo1.write(135);
  myservo2.write(135);
}

void robotLeft (int duration) {
  myservo1.write(45);
  myservo2.write(45);
}
void robotStop (int duration) {
  myservo1.write(90);
  myservo2.write(90);
}

void setLed(LED led, int color[]){
   digitalWrite(led.redPin,color[0]);
   digitalWrite(led.greenPin,color[1]);
   digitalWrite(led.bluePin,color[2]);
}

void forwardLeft(){
    myservo1.write(45);
  myservo2.write(180);
}



void processScrollBarInput(char input){
  int intVal = 0;
  if(input=='q'){
    intVal = 10;
  }else{
      String inputStr = String(input);
      intVal = inputStr.toInt();
  }

  if(intVal==0){
    return;
  } 
  int angle = intVal * 18;
  weaponServo.write(angle);
  
}

void loop() {
  if (Serial.available())
  { //if there is data being recieved
    input = Serial.read();
    if (input == 'F')
    {
      robotBackward(1);
    }
    if (input == 'B')
    {
      robotForward(1);
    }
    if (input == 'R')
    {
      robotRight(1);
    }
    if (input == 'L')
    {
      robotLeft(1);
    }
    if (input == 'S' )
    {
      robotStop(1);
    }

    
    if(input == 'W' || input == 'w'){
      setLed(led1,RED);
      setLed(led2,RED);
    }
   if(input == 'U' || input == 'u'){
      setLed(led1,GREEN);
      setLed(led2,GREEN);
    }
   if(input == 'V' || input == 'v'){
      setLed(led1,BLUE);
      setLed(led2,BLUE);
    }
  if(input == 'X' || input == 'x'){
      setLed(led1,WHITE);
      setLed(led2,WHITE);
    }
  }
  processScrollBarInput(input);
  //weaponServo.write(servoPos++);
  /*digitalWrite(redPin1,HIGH);
  delay(1000);
  digitalWrite(redPin1,LOW);
  delay(1000);*/
  
  /*setLed(led1,RED);
  setLed(led2,RED);
  delay(1000);
  setLed(led1,GREEN);
  setLed(led2,GREEN);
  delay(1000);
  setLed(led1,BLUE);
  setLed(led2,BLUE);
  delay(1000);
  setLed(led1,WHITE);
  setLed(led2,WHITE);
  delay(1000);
  setLed(led1,OFF);
  setLed(led2,OFF);
  delay(1000);*/
  
}




