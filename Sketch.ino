#include <Servo.h> 
#include <Ultrasonic.h>

const int buzzer = 13;
const int motorA1= 6;
const int motorA2= 9;
const int motorB1=10;
const int motorB2=11;
const int gap=15;

Ultrasonic USsensor(A2 ,A1);
Servo S_Motor;

int distance;
int checkRight;
int checkLeft;
int pos=90;

void setup()
{
    S_Motor.attach(3);
    Serial.begin(9600);
    
    Serial.println("\t\t\t|*******************************************************|\n");
    Serial.println("\t\t\t|***************       Turning ON       ****************|\n");
    Serial.println("\t\t\t|*******************************************************|\n");
    delay(50);
    Serial.println("\t\t\t|**********      Hi! I am WALL.E 'v5.5'    *************|\n");
    Serial.println("\t\t\t|***********  An Obstacle Avoiding Robot  **************|\n");
    Serial.println("\t\t\t|*******************************************************|\n");
    
    S_Motor.write(pos);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(motorA1,OUTPUT);
    pinMode(motorA2,OUTPUT);
    pinMode(motorB1,OUTPUT);
    pinMode(motorB2,OUTPUT);
    
    delay(50);
    Serial.println("\t\t\t|**************** Let's Get Started...! ****************|\n");
    Serial.println("\t\t\t|*******************************************************|\n\n");
    Serial.println("All clear...!\n\tMoving forward!");
}

void loop()
{
    distance = USsensor.Ranging(CM);
    if (distance > gap){
      forward();
      digitalWrite(LED_BUILTIN, LOW);
    }
    else if (distance <= gap){
            tone(buzzer,500);
            backward();
            delay(1000);
            Stop();
            Serial.println("\t\t\tLooking Left...!");
            for(pos ; pos<=180; pos += 1){
                S_Motor.write(pos);
                delay(5);
            }
            
            delay(25);
            checkLeft = USsensor.Ranging(CM);
            delay(25);
            
            for(pos = 180; pos>=90; pos-=1){
                S_Motor.write(pos);
                delay(5);
            }
            delay(5);
            
            Serial.println("\t\t\tLooking Right...!");
            for(pos = 90; pos>=0; pos-=1){
                S_Motor.write(pos);
                delay(5);
            }
            
            delay(25);
            checkRight= USsensor.Ranging(CM);
            delay(25);
            noTone(buzzer);
            
            for(pos = 0; pos<=90; pos+=1){
                S_Motor.write(pos);
                delay(5);
            }
            delay(5);
            pos=90;
            S_Motor.write(pos);
            
            if (checkLeft < checkRight){
              right();
              delay(1900);
              Serial.println("All clear...!\n\tMoving forward!");         
              }
            else if (checkLeft > checkRight){
              left();
              delay(1900);
              Serial.println("All clear...!\n\tMoving forward!");
            }
            else if (checkLeft <= gap && checkRight <= gap){
              Serial.println("\n!...The road is closed...!\n");
              backward();
              delay(1500);
              left();
              delay(1900);
              Serial.println("All clear...!\n\tMoving forward!\n");
            }
    }

}


void forward(){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW); 
}

void backward(){
  Serial.println("\tGoing Back...!");
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void right(){
  Serial.println("\t\tTurning Right...!");
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void left(){
  Serial.println("\t\tTurning Left...!");
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW); 
}

void Stop(){
  Serial.println("\n!...OBSTACLE Ahead...!\n");
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
