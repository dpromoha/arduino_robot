#include<Servo.h>
int val;
Servo ultr;
#define ECHO_PIN 13
#define TRIG_PIN 12
#define LET 20
#define B_LEFT 4
#define B_RIGHT 8
unsigned long times;

void setup() {
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  ultr.attach(7);   
  ultr.write(83);
  pinMode (B_LEFT, INPUT);
  pinMode (B_RIGHT, INPUT);
  Serial.begin(9600);

}

void loop() {
  int distance = measure(); 
  boolean left_b = digitalRead(B_LEFT); 
  boolean right_b = digitalRead(B_RIGHT);

  Serial.print(distance);
  Serial.println(" cm");


 if (distance > LET && left_b == HIGH && right_b == HIGH) {
    drive(255, 255);
  }
      else if (distance > LET && left_b == HIGH && right_b == LOW) {
     drive(0, 255);  
  }
     else if (distance > LET && left_b == LOW && right_b == HIGH) {
       drive(255, 0);
  }
 else if (distance <= LET){
  drive(0, 0);
 if (millis() > times + 2000){
      times=millis();
      ultr.write(128);
      int dist_left = measure();
    }
    if (millis() > times + 2000){
      times=millis();
      ultr.write(38);
      int dist_right = measure();
    }
    if (millis() > times + 2000){
      times=millis();
      ultr.write(83);
      int dist_right = measure();
    }
 }
 int dist_left = measure();
 int dist_right = measure();
        if (dist_left > dist_right && dist_left > 25){
          drive(-255, 255);
          delay(500);
          }
             else if (dist_left < dist_right && dist_right >25){
                drive(255, -255);
                delay(500);
            }
           else {
              drive(-255, -255);
              delay(500);
              drive(255, -255);
              delay(500);
          }
  }

  void drive(int left, int right) {

  left = constrain(left, -255, 255);
  right = constrain(right, -255, 255);

  if (right>=0) {
      analogWrite(6, abs(right));
      analogWrite(3, 0); //right
  }    
    else {
      analogWrite(6, 0);
      analogWrite(3, abs(right));
      
  }
  
  if (left>=0) {
      analogWrite(11, 0);
      analogWrite(5, abs(left));
  }    
    else {
      analogWrite(11, abs(left));
      analogWrite(5, 0);
  }


}

int measure()
{
  digitalWrite(TRIG_PIN, HIGH);
  digitalWrite(TRIG_PIN, LOW);
  int dist = pulseIn(ECHO_PIN, HIGH)/50;
  
  return dist;
}
  


