#include <PID_v1.h>
#include <TimerOne.h>

int sig=0;
double signaltime;
int trig = 6;
int echo = 7;

int trigR = 8;
int echoR = 9;

int trigL = 10;
int echoL = 11;   

int motor1 = 4;
int motor2 = 5;
int dirA1 = 22;
int dirA2 = 23;
int dirB1 = 24;
int dirB2 = 25;
int duration = 0;
int distance = 0;

long durationL = 0;
int distanceL = 0;

long durationR = 0;
int distanceR = 0;

int enc1 = 2;
int enc2 = 3;
double counterU;
double counterU2;
double counterU3;
double counterU4;
double counterU5;
int value =0;

double R_pwmOutput = 0 ;
double R_SpeedRPM = 0.0;

double L_pwmOutput = 0 ;
double L_SpeedRPM = 0.0;

double Setpoint = 90;
double Setpoint2=90;

int flag = 0;
int flag1 = 0;

float R_Kp = 1.4, R_Ki = 1, R_Kd = 0.01;
//float R_Kp = 2, R_Ki = 1.3, R_Kd = 0.;
float L_Kp = 1, L_Ki = 1, L_Kd = 0;
//float L_Kp = 0.4, L_Ki = 3.5, L_Kd = 0.05;
PID R_rpm(&R_SpeedRPM, &R_pwmOutput, &Setpoint2, R_Kp, R_Ki , R_Kd, DIRECT ) ;
PID L_rpm(&L_SpeedRPM, &L_pwmOutput, &Setpoint, L_Kp, L_Ki , L_Kd, DIRECT ) ;

volatile unsigned long counter1 = 0;
volatile unsigned long counter2 = 0;
const float ppr = 384.0/10;

void int_count1(){
  counter1++;
}
void int_count2(){
  counter2++;
}

void int_timer(){
  Timer1.detachInterrupt();
  R_SpeedRPM = (counter1/ppr)*60.0;
  R_rpm.Compute();
  analogWrite (motor1 , R_pwmOutput );
  //Serial.print("motor 1 speed : ");
  //Serial.print(R_SpeedRPM);
  //Serial.print(",");
  //Serial.println(Setpoint);
  counter1 = 0;
  L_SpeedRPM = (counter2/ppr)*60.0 ;
 L_rpm.Compute();
  analogWrite (motor2 , L_pwmOutput );
//  Serial.print("motor 2 speed : ");
 //Serial.println(L_SpeedRPM);
  counter2 = 0;
//  Serial.println("");
  Timer1.attachInterrupt(int_timer);
}

void setup() {
  pinMode(motor1, OUTPUT);
  pinMode(dirA1, OUTPUT);
  pinMode(dirA2, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(dirB1, OUTPUT);
  pinMode(dirB2, OUTPUT);
  pinMode(trig , OUTPUT);  
  pinMode(echo , INPUT);
  pinMode(trigL , OUTPUT);  
  pinMode(echoL , INPUT);
  pinMode(trigR , OUTPUT);  
  pinMode(echoR , INPUT);
  Serial.begin(9600);
  Timer1.initialize(100000);
  attachInterrupt(digitalPinToInterrupt(enc1),int_count1, RISING);
  attachInterrupt(digitalPinToInterrupt(enc2),int_count2, RISING);
  R_rpm.SetMode(AUTOMATIC);
  L_rpm.SetMode(AUTOMATIC);
  Timer1.attachInterrupt(int_timer);
}

void loop() {
Serial.print("Distance: ");
Serial.println(distance);
/*Serial.print(",");
Serial.print("DistanceL: ");
Serial.println(distanceL);
Serial.print(",");
Serial.print("DistanceR: ");
Serial.println(distanceR);*/
/*digitalWrite(trig , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trig , LOW);
duration = pulseIn(echo , HIGH); 
distance = (duration/2) / 28.5 ; */
digitalWrite(trig , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trig , LOW);
duration = pulseIn(echo , HIGH); 
distance = (duration/2) / 28.5 ; 
if ( (distance < 30 && distance>0 ) ) 
{ 
  flag =1;
  if (flag ==1)
  {
    flag1=1;
  counterU2= millis()+ 3000;
  
  }
}
else { 
digitalWrite(dirA1, HIGH); 
digitalWrite(dirA2 , LOW);
digitalWrite(dirB1, HIGH); 
digitalWrite(dirB2 , LOW);
}
while (counterU>millis()){
digitalWrite(dirA1, HIGH); 
digitalWrite(dirA2 , LOW);
digitalWrite(dirB1, LOW); 
digitalWrite(dirB2 , HIGH);
counterU3= millis()+ 3500; 
}
  while (counterU2>millis())
  {
  digitalWrite(dirA1, LOW);
  digitalWrite(dirA2, LOW); 
  digitalWrite(dirB1, LOW);
  digitalWrite(dirB2, LOW);
  counterU= millis()+ 3500; 
  flag1=1;
  }

   while (counterU3>millis())
  {
  digitalWrite(dirA1, LOW);
  digitalWrite(dirA2, LOW); 
  digitalWrite(dirB1, LOW);
  digitalWrite(dirB2, LOW);
} 
if(Serial.available()>0){
int pi=Serial.read()-'0';
if (pi ==1){
 while(1){
pi=Serial.read()-'0';
 //print ULTRASonic readings 
Serial.print("Distance: ");
Serial.println(distance);
Serial.print(",");
Serial.print("DistanceL: ");
Serial.println(distanceL);
Serial.print(",");
Serial.print("DistanceR: ");
Serial.println(distanceR);
//Ultrasonics reading calculations
digitalWrite(trig , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trig , LOW);
duration = pulseIn(echo , HIGH); 
distance = (duration/2) / 28.5 ; 

digitalWrite(trigL , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trigL , LOW);
durationL = pulseIn(echoL , HIGH); 
distanceL = (durationL/2) / 28.5 ;


digitalWrite(trigR , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trigR , LOW);
durationR = pulseIn(echoR , HIGH); 
distanceR = (durationR/2) / 28.5 ;
//following human code
  if((distance<100) && (distance >60) )
  {
    while((distance<100) && (distance >60) ){
    forward();
digitalWrite(trig , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trig , LOW);
duration = pulseIn(echo , HIGH); 
distance = (duration/2) / 28.5 ;     
    }
  }

if ((distance >35)&&(distance<60)){
while((distance >35)&&(distance<60)){
stopA();
digitalWrite(trig , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trig , LOW);
duration = pulseIn(echo , HIGH); 
distance = (duration/2) / 28.5 ; 
  }
  }
if (distance > 100){
while(distance > 100){
  stopA();
digitalWrite(trig , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trig , LOW);
duration = pulseIn(echo , HIGH); 
distance = (duration/2) / 28.5 ; 
}
}
if ((distance<25) && (distanceL<30) && (distanceR<30)){
while((distance<25) && (distanceL<30) && (distanceR<30)){
  backward();
digitalWrite(trig , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trig , LOW);
duration = pulseIn(echo , HIGH); 
distance = (duration/2) / 28.5 ; 
digitalWrite(trigL , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trigL , LOW);
durationL = pulseIn(echoL , HIGH); 
distanceL = (durationL/2) / 28.5 ;
digitalWrite(trigR , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trigR , LOW);
durationR = pulseIn(echoR , HIGH); 
distanceR = (durationR/2) / 28.5 ;
}
} 
if ((distance<30) && (distanceL<30) && (distanceR>50))
{
while((distance<30) && (distanceL<30) && (distanceR>50)){
 turnLeft();
digitalWrite(trig , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trig , LOW);
duration = pulseIn(echo , HIGH); 
distance = (duration/2) / 28.5 ; 
digitalWrite(trigL , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trigL , LOW);
durationL = pulseIn(echoL , HIGH); 
distanceL = (durationL/2) / 28.5 ;
digitalWrite(trigR , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trigR , LOW);
durationR = pulseIn(echoR , HIGH); 
distanceR = (durationR/2) / 28.5 ; 
}
}
if ((distance<30) && (distanceL>50) && (distanceR<30))
{
while((distance<30) && (distanceL>50) && (distanceR<30)){
 turnRight();
digitalWrite(trig , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trig , LOW);
duration = pulseIn(echo , HIGH); 
distance = (duration/2) / 28.5 ; 
digitalWrite(trigL , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trigL , LOW);
durationL = pulseIn(echoL , HIGH); 
distanceL = (durationL/2) / 28.5 ;
digitalWrite(trigR , HIGH); 
delayMicroseconds(1000); 
digitalWrite(trigR , LOW);
durationR = pulseIn(echoR , HIGH); 
distanceR = (durationR/2) / 28.5 ; 
}
}
if(pi==0){
  break;
  }
}
}
}
}
void forward(){// turn it on going forward
digitalWrite(dirA1, HIGH); 
digitalWrite(dirA2 , LOW);
digitalWrite(dirB1, HIGH); 
digitalWrite(dirB2 , LOW);
}

void backward(){ // the other way
  //counterU4= millis()+ 2000;
   //while (counterU4>millis())
   //{stopA ();}
digitalWrite(dirA1, LOW); 
digitalWrite(dirA2 , HIGH);
digitalWrite(dirB1, LOW); 
digitalWrite(dirB2 , HIGH);
}

void turnRight(){ // the other right
digitalWrite(dirA1, LOW); 
digitalWrite(dirA2 , HIGH);
digitalWrite(dirB1, HIGH); 
digitalWrite(dirB2 , LOW);
}

void turnLeft(){ // turn it on going left
  
digitalWrite(dirA1, HIGH); 
digitalWrite(dirA2 , LOW);
digitalWrite(dirB1, LOW); 
digitalWrite(dirB2 , HIGH);
}

void stopA(){ // stopped
  digitalWrite(dirA1, LOW);
  digitalWrite(dirA2, LOW); 
  digitalWrite(dirB1, LOW);
  digitalWrite(dirB2, LOW);
}
