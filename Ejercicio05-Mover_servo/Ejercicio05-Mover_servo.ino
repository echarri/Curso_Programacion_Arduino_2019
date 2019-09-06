/*
   Ejercicio05 - Mover servo
*/

//Librerías pantalla LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Librería Servo
#include <Servo.h>

//PINES
#define PIN_SERVO 9
#define PIN_POT A0

//Objeto servo
Servo miservo;

//Objeto pantalla
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// variables
long pot;
long pos_servo;

void setup() {
  //Inicializo puerto serie
  Serial.begin(9600);

  //Inicializo Servo
  Serial.println(F("Inicializando servo..."));
  miservo.attach(PIN_SERVO);

  //Inicializo pantalla
  Serial.println(F("Inicializando pantalla..."));
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(800);
  lcd.clear();
}

void loop() {
  pot = analogRead(PIN_POT);
  if (pot>1000) pot = 1000;
  if (pot<20) pot = 20;
  pos_servo=10+((pot-20)*160/980);
  Serial.print("Potenciometro: " + String(pot));
  Serial.println(" Servo: " + String(pos_servo));
  lcd.setCursor(0, 0); lcd.print("Pote.: "); lcd.print(pot);
  lcd.setCursor(0, 1); lcd.print("Servo: "); lcd.print(pos_servo);
  miservo.write(pos_servo);
  delay(300);
  lcd.clear();
}
