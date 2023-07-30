#include <Servo.h>            //include servo.h library
#include <SoftwareSerial.h>  //include SoftwareSerial.h library

Servo myservo;
 
int pos = 0;    
// bool fire = false;


// Pin Definitions
#define in1 6 
#define in2 7
#define in3 8
#define in4 9

const int pump = 5;
const int flameSensorPin_Left = 13;   // Flame sensor connected to digital pin 13
const int flameSensorPin_Forward = 12;   // Flame sensor connected to digital pin 12
const int flameSensorPin_Right = 11;   // Flame sensor connected to digital pin 11

void setup() 
{
  
  Serial.begin(9600);// Initialize serial communication

  // Set flame sensor pin as input
  pinMode(flameSensorPin_Left, INPUT);
  pinMode(flameSensorPin_Forward, INPUT);
  pinMode(flameSensorPin_Right, INPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);



  pinMode(pump,OUTPUT);

  digitalWrite(pump, HIGH);

  myservo.attach(4);
  myservo.write(90); 

}

void loop() 
{

  myservo.write(90); //Sweep_Servo();  



  // Read flame sensor value

  int flameSensorValue_Left = digitalRead(flameSensorPin_Left);
  int flameSensorValue_Forward = digitalRead(flameSensorPin_Forward);
  int flameSensorValue_Right = digitalRead(flameSensorPin_Right);

  // Check if flame is detected
  if (flameSensorValue_Left == LOW)
  {
    
    Serial.println("Fire detected - left side");

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    // Perform actions when fire is detected
  }
  else if(flameSensorValue_Forward == LOW)
  {

    Serial.println("Fire detected - front");

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    Serial.println("WHEELS MOVED!");

    delay(900);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
   
    Serial.println("WHEELS STOPPED!");
   
    digitalWrite(pump, LOW);


    delay(2000);
    for (pos = 50; pos <= 110; pos += 1) 
      { 
          myservo.write(pos); 
           delay(10);  
      }
    for (pos = 110; pos >= 50; pos -= 1)
      { 
            myservo.write(pos); 
            delay(10);
      }
    digitalWrite(pump, HIGH);
    Serial.println("Fire and pump turned off ");
   // put_of_fire();
  }
  else if(flameSensorValue_Right == LOW)
  {
    
    Serial.println("Fire detected RIGHT LO!");
    

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

  }
  else if(digitalRead(flameSensorValue_Left) == HIGH && digitalRead(flameSensorValue_Right)== HIGH && digitalRead(flameSensorValue_Forward) == HIGH)
  {
   
    Serial.println("No fire");
   
   
    delay(500);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
  delay(400);

}
/*void put_of_fire()
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(pump, LOW);
    delay(2000);

     for (pos = 50; pos <= 110; pos += 1) 0
      { 
          myservo.write(pos); 
           delay(10);  
       }
      for (pos = 110; pos >= 50; pos -= 1)
      { 
            myservo.write(pos); 
            delay(10);
      }
 /*   digitalWrite(pump, HIGH);
    //myservo.write(90); 
    fire=false;
    Serial.println("Fire turned off!");
}*/