#include <LiquidCrystal.h>
LiquidCrystal LCD(6,7,5,4,3,2);

// Push Button is Connected to Pin No. 8
int pushButton = 8; 

// Trig pin & Echo pin of Ultrasonic Sensor are Connected to Pin No. 9 & 10 Respictevely.
#define trigpin 9 
#define echopin 10

// Orange & White LED are Connected to Pin No. 11 & 12 Respectively.
int blue = 11; 
int white = 12;

// Defined Variables
float duration;
float distance;
float heightMeasuredFromInch;
float heightInch;
float distanceInch;
float actualHeight;

// The Height from Where Height is Measured, It's Value is in CM.
float heightMeasuredFrom = 72.60; 
// 68.52cm /26.98 In is the Height of Table in IOT LAB.

void setup()
{
  LCD.begin(16,2);
  
  pinMode(pushButton, INPUT);
  pinMode(echopin, INPUT);
  
  pinMode(trigpin, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(white, OUTPUT);

  LCD.setCursor(6,0);
  LCD.print("Height");
  LCD.setCursor(3,1);
  LCD.print("Measurement");
  
  delay(3000);
  Serial.begin(9600);
}

void loop()
{
  int buttonState = digitalRead(pushButton);

    // If Push Button is Pressed.
    if (buttonState == 1) { 
      
       LCD.setCursor(0,0);
       LCD.print("YOUR DEVICE IS  ");
       LCD.setCursor(0,1);
       LCD.print("  READY TO USE  ");
      
      Serial.println(" ");
      Serial.println("You Device is Ready to Use.");
//      LCD.print("You Device is Ready to Use.");
      
      digitalWrite(blue, LOW);

      // White Light is the Indicator that the Device is ON.
      digitalWrite(white, HIGH);
      digitalWrite(trigpin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigpin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigpin, LOW);
      
      duration = pulseIn(echopin,HIGH);

      // Converting CM into INCH.
      heightMeasuredFromInch = heightMeasuredFrom*0.3937;

      // Converting Pulse Value into CM.
      distance = duration * 0.0344 / 2;

      // Converting CM into INCH.
      distanceInch = distance*0.3937;

      // Object Height = Distance Measured From - Object Distance
      actualHeight= heightMeasuredFrom-distance;
      heightInch = actualHeight*0.3937;

      Serial.println(" ");
      Serial.print("Measured From: ");
      Serial.print(heightMeasuredFrom);
      Serial.print(" cm (");
      Serial.print(heightMeasuredFromInch);
      Serial.println(" Inch)");
      
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.print(" cm (");
      Serial.print(distanceInch);
      Serial.println(" Inch)");
      
      Serial.print("Height: ");
      Serial.print(actualHeight);
      Serial.print(" cm (");
      Serial.print(heightInch);
      Serial.println(" Inch)");
      Serial.println(" ");

      LCD.setCursor(0,0);
      LCD.print("Height: ");
      LCD.print(actualHeight);
      LCD.print(" CM");

      LCD.setCursor(0,1);
      LCD.print("Height: ");
      LCD.print(heightInch);
      LCD.print(" INCH");

  } 
  // If Push Button is Unpressed.
  else {
    // Orange Light is the Indicator that the Device is OFF.
    digitalWrite(blue, HIGH);
    digitalWrite(white, LOW);
    
    
    LCD.setCursor(0,0);
    LCD.print("     TURN ON     ");
    LCD.setCursor(0,1);
    LCD.print("   YOUR DEVICE  ");
    Serial.println("Turn On Your Device to Measure Height");  
  }
  delay(3000);
}
