#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;

int motorSpeed = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  
  float potValInt = analogRead(A0);
  float potValFloat = (potValInt/1023);

  Serial.println(potValInt);
  Serial.println("");
  Serial.println(potValFloat);
  
  motorSpeed = (int) (100 + 75*potValFloat);
  int motorSpeedInt = (int) (motorSpeed-100.00)/0.75;
  String motorSpeedStr = String(motorSpeedInt)+'%';

  if(motorSpeedInt == 0)
  {
    motorSpeedStr = "OFF";
    motorSpeed = 0;
  }

  int motorSpeedLen = motorSpeedStr.length();

  lcd.setCursor(0,0);
  lcd.print("MotorSpeed:     ");
  lcd.setCursor(16-motorSpeedLen,0);
  lcd.print(motorSpeedStr);
  lcd.setCursor(0,1);
  lcd.print(" 3D-PRINTED RFB ");
    
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  analogWrite(9, motorSpeed);
  analogWrite(10, motorSpeed);

  delay(50);

} 
