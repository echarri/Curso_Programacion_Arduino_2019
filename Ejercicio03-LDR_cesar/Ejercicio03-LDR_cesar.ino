/*
   Ejercicio03 - César
*/

//Librerías pantalla LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//PINES
#define PIN_LDR A1

//Objeto pantalla
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// variables
int maximo = 0;
int minimo = 1023;
int actual = 0;

void setup() {
  //Inicializo puerto serie
  Serial.begin(9600);

  //Inicializo pantalla
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  
  Serial.println(F("Capturando datos..."));
  delay(1000);
  lcd.clear();
  
}

void loop() {

  actual = analogRead(PIN_LDR);
  maximo = max(maximo, actual);
  minimo = min(minimo, actual);
 
  lcd.setCursor(2, 0);
  lcd.print("Actual: ");
  lcd.print(actual);
  lcd.print("  ");
  lcd.setCursor(0, 1);
  lcd.print("Max:");
  lcd.print(maximo);
  lcd.print("  ");
  lcd.setCursor(8, 1);
  lcd.print("Min:");
  lcd.print(minimo);
  lcd.print("  ");

  Serial.print("Actual:");
  Serial.print(actual);
  Serial.print(" ... maximo:");
  Serial.print(maximo);
  Serial.print(" ... minimo:");
  Serial.println(minimo);
  
  delay(500);
  lcd.clear();
}
