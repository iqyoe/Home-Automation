/*This project is made by
 * Muhammad Iqbal Lukman
 * Samuel ANthony
 * Tedy Kurnia Ramdani
 * Aldo Wijaya
 * Lia Kurniasari
 * 
 * This project is about making a Home Automation.
 * by only inputing value to the terminal, automatically
 * a command will be executed by the device.
 * 
 * features:
 * Garage open
 * Light Control
 * Security detection with alarm
 */
#include<Servo.h> //insert Servo library to manipulate servo.

const int led1 = 2; //initialize led 1 in pin 2
const int led2 = 3; //initialize led 2 in pin 3
const int led3 = 4; //initialize led 3 in pin 4
const int tri = 13, ech = 12; //initizalize ultrasonic sensor trigger in pin 13 and echo in pin 12 
const int buzz = 9; //initialize buzzer in pin 9
Servo servo1; //initizalize servo1 as Object Servo to manipulate
              //servo

int security, garage, living, bed, back;
/*security store int value indicate that 0 is off and 1 is on
 *garage store int value indicate that 0 is off and 1 is on
 *livinge store int value indicate that 0 is off and 1 is on
 *bed store int value indicate that 0 is off and 1 is on
 *back store int value indicate that 0 is off and 1 is on
 */
int angle = 0, sound = 0;
/*angle is a variable to determine the angle use in servo
 *sound is a variable to determine what note sound output by buzzer
 */

//features
void lampLiving(int);
void lampBed(int);
void lampBack(int);
void securityCheck(int);
void openGarage(int);

void setup() {
  // put your setup code here, to run once:  
  pinMode(led1, OUTPUT); //Make pin in 2, 3, and 4 as OUTPUT
  pinMode(led2, OUTPUT); //for LED
  pinMode(led3, OUTPUT);

  pinMode(tri, OUTPUT); //pin 13 as output to make rigger and
  pinMode(ech, INPUT); //pin 12 as input to count distance
  
  pinMode(buzz, OUTPUT); //pin 9 as output to make sound in buzzer

  
  servo1.attach(8); //initialize servo in pin 7
  
  Serial.begin(9600);
  
  servo1.write(90);
  
  security = 0;
  garage = 0;
  living = 0;
  bed = 0;
  back = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  int state; //store serial input value
  
  //check the input from terminal
  //and process it if the input is more than 0
  if(Serial.available()>0){
    state = Serial.read();
    switch(state){
      case 49: //1
        living = 1;
        break;
      case 50: //2
        living = 0;
        break;
      case 51: //3
        bed = 1;
        break;
      case 52: //4
        bed = 0;
        break;
      case 53: //5
        back = 1;
        break;
      case 54: //6
        back = 0;
        break;
      case 55: //7
        security = 1;
        break;
      case 56: //8
        security = 0;
        break;
      case 57: //9
        garage = 1;
        break;
      case 48: //0
        garage = 0;
        break;
    }
  }

 lampLiving(living);
 lampBed(bed);
 lampBack(back);
 securityCheck(security);

 if(garage==1){
   int angelinsert = angle/2;
   openGarage(angelinsert);
   if(angle<36) {
    angle++;
   }
 } else {
  int angleinsert = angle/2;
  if(angle>0){
    openGarage(angleinsert);
    angle--; 
  } else {
    servo1.write(90);
  }
 }
 
 Serial.print(state);Serial.print(" ");
 Serial.print(living);Serial.print(" ");
 Serial.print(bed);Serial.print(" ");
 Serial.print(back);Serial.print(" ");
 Serial.print(security);Serial.print(" ");
 Serial.print(garage);Serial.print(" ");
 Serial.println(angle);
 delay(125);
}

//Feature Living Room Lamp
void lampLiving(int l){
  if(l==1){
    digitalWrite(led1, HIGH);
  } else {
    digitalWrite(led1,LOW);
  }
}

//Feature Bed Room Lamp
void lampBed(int l){
  if(l==1){
    digitalWrite(led3, HIGH);
  } else {
    digitalWrite(led3,LOW);
  }
}

//Feature Back Room Light
void lampBack(int l){
  if(l==1){
    digitalWrite(led2, HIGH);
  } else {
    digitalWrite(led2,LOW);
  }
}

//Feature Security Alarm
void securityCheck(int c){
  if(c==1){
    digitalWrite(tri, LOW); //clear trigger
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(tri, HIGH);
    delayMicroseconds(10);
    digitalWrite(tri, LOW);
  
    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(ech, HIGH);
    // Calculating the distance
    int distance= duration*0.034/2;

    //Check Distance
    Serial.print("Distance: ");Serial.print(distance);
    Serial.print(" Sound: ");Serial.println(sound);
    
    if(distance<15){
      int sn[2]={1136, 1432};
      tone(buzz,sn[sound%2]);  
      sound++;
    } else {
      sound = 0;
      noTone(buzz);
    }
  } else {
    sound = 0;
    noTone(buzz);
  }
}

//Feature to open garage
void openGarage(int ang){
  int an[20] = {90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150, 155, 160, 165, 170, 175, 180};
  servo1.write(an[ang]);
  Serial.print(ang);Serial.print(" ");Serial.println(an[ang]);
}

