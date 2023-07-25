#include <AFMotor.h>


AF_DCMotor motor1(1);
AF_DCMotor motor2(2);


int j=0;

const int pingPinL = 9; // Trigger Pin of Ultrasonic Sensor
const int echoPinL = 8; // Echo Pin of Ultrasonic Sensor

const int pingPinF = 11; // Trigger Pin of Ultrasonic Sensor
const int echoPinF = 10; // Echo Pin of Ultrasonic Sensor

const int pingPinR = 12; // Trigger Pin of Ultrasonic Sensor
const int echoPinR = 13; // Echo Pin of Ultrasonic Sensor

const int modePin=7;
int mode;
int speedval=255;
int threshhold=500;

long durationL,durationF,durationR;

int leftwall,rightwall,frontwall;

int turnTime=1000;//Give value for this. By finding experimentally
int turns;

char patharray[100];


void rightturn(){
  Stop();
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  
  Serial.println("RightTurn");
  delay(turnTime);
  
  motor1.setSpeed(255);
  motor1.run(RELEASE);
  motor2.setSpeed(255);
  motor2.run(RELEASE);
  Serial.println("Done");
  patharray[j]="R";
  j++;
  
}

void leftturn(){
  Stop();
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  
  Serial.println("LeftTurn");
  delay(turnTime);
  
  motor1.setSpeed(255);
  motor1.run(RELEASE);
  motor2.setSpeed(255);
  motor2.run(RELEASE);
  Serial.println("Done");
  patharray[j]="R";
  j++;
  
}

void forward(){
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  
  Serial.println("Forward");
  //patharray.append("F");
}

void Uturn()
{
  Stop();
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  
  Serial.println("Right");
  delay(turnTime);
  
  motor1.setSpeed(255);
  motor1.run(RELEASE);
  motor2.setSpeed(255);
  motor2.run(RELEASE);
  Serial.println("Done");


  Stop();
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  
  Serial.println("Right");
  delay(turnTime);
  
  motor1.setSpeed(255);
  motor1.run(RELEASE);
  motor2.setSpeed(255);
  motor2.run(RELEASE);
  Serial.println("Done");
  patharray[j]="R";
  j++;
  
}

void Stop()
{
  motor1.setSpeed(255);
  motor1.run(RELEASE);
  motor2.setSpeed(255);
  motor2.run(RELEASE);
  Serial.println("Stop");
  delay(100);
  patharray[j]="S";
  j++;
}

void looking()
{
  digitalWrite(pingPinL, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinL, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);
  Serial.println(durationL);
  //delay(1000);

  digitalWrite(pingPinF, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinF, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinF, LOW);
  durationF = pulseIn(echoPinF, HIGH);
  Serial.println(durationF);
  //delay(1000);

  digitalWrite(pingPinR, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinR, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinR, LOW);
  durationR = pulseIn(echoPinR, HIGH);
  Serial.println(durationR);
  //delay(1000);

  if(durationL>threshhold)
  {
    leftwall=0;
    Serial.println("No left wall");
    //delay(1000);
  }
  else
  {
    leftwall=1;
    Serial.println("Left wall");
    //delay(1000);
  }

  if(durationR>threshhold)
  {
    rightwall=0;
    Serial.println("No right wall");
    //delay(1000);
  }
  else
  {
    rightwall=1;
    Serial.println("Right wall");
    //delay(1000);
  }

  if(durationF>threshhold)
  {
    frontwall=0;
    Serial.println("No front wall");
    //delay(1000);
  }
  else
  {
    frontwall=1;
    Serial.println("Front wall");
    //delay(1000);
  }

  
}

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   
   pinMode(pingPinL, OUTPUT);
   pinMode(echoPinL, INPUT);
   
   pinMode(pingPinR, OUTPUT);
   pinMode(echoPinR, INPUT);
   
   pinMode(pingPinF, OUTPUT);
   pinMode(echoPinF, INPUT);

   pinMode(modePin,INPUT);
}

void loop() {
 //delay(1000);
  looking();
  //mode=digitalRead(modePin);
  mode=1;

//Maze Solving mode
  //if(mode==1){

  if((leftwall==0) && ((frontwall==0)||(frontwall==1)) && ((rightwall==1)||(rightwall==0)))
  {
    //Left no wall. Front and Right dont matter
    leftturn();
    Serial.println("Turning Left");
  }

  else if((leftwall==1) && ((frontwall==0)) && ((rightwall==1)||(rightwall==0)))
  {
    //Left wall is there. No wall in front. Right dont matter
    forward();
    Serial.println("Going Straight");
  }

  else if((leftwall==1) && ((frontwall==1)) && (rightwall==0))
  {
    rightturn();
    Serial.println("Turning Right");
  }

  else if((leftwall==1) && ((frontwall==1)) && (rightwall==1))
  {
    Uturn();
    Serial.println("Taking Uturn");
  }
  else
  {
    Stop();
    Serial.println("Stop");
  }
  //}

//Optimum path mode
 /* else
  {
    if(!((leftwall==1)||(rightwall==1)))
    {
      if(patharray[turns]=='L')
      {
        leftturn();
      }
      else if(patharray[turns]=='F')
      {
        forward();
      }
      else if(patharray[turns]=='R')
      {
        rightturn();
      }
      else if(patharray[turns]=='S')
      {
        Stop();
      }
      else
      {
        
      }
    }
  }*/
  
  
}
