/*
   Ejercicio04 - Contar pulsos
*/

//Librerías pantalla LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//PINES
#define PIN_BOTON_A 2
#define PIN_BOTON_B 3

//Objeto pantalla
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

//variables
int pulsos_a = 0;
int pulsos_b = 0;
static boolean anterior_a = digitalRead(PIN_BOTON_A);
static boolean anterior_b = digitalRead(PIN_BOTON_B);
boolean estado_a = digitalRead(PIN_BOTON_A);
boolean estado_b = digitalRead(PIN_BOTON_B);
boolean cambio = false;
  
void setup() {
  //Inicializo puerto serie
  Serial.begin(9600);

  //Inicializo Pines
  Serial.println(F("Inicializando pines digitales..."));
  pinMode(PIN_BOTON_A, INPUT_PULLUP);
  pinMode(PIN_BOTON_B, INPUT);

  //Inicializo pantalla
  Serial.println(F("Inicializando pantalla..."));
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  Serial.println(F("Prueba Botones"));
  delay(1000);
}

void loop() {
    estado_a = digitalRead(PIN_BOTON_A);
    estado_b = digitalRead(PIN_BOTON_B);
    if (anterior_a != estado_a && estado_a == LOW) {  //flanco descendente pull-up
        pulsos_a++;
        cambio = true;
      }
    if (anterior_b != estado_b && estado_b == HIGH) {  //flanco ascendente pull-down
        pulsos_b++;
        cambio = true;
      }

    if (cambio) {
      Serial.println("Boton A: " + (String)pulsos_a + " Boton B: " + (String)pulsos_b);
      lcd.clear();
      lcd.setCursor(0, 0); lcd.print("Prueba Botones");
      lcd.setCursor(0, 1); lcd.print("A:"); lcd.print(pulsos_a);
      lcd.setCursor(8, 1); lcd.print("B:"); lcd.print(pulsos_b);
      cambio = false;
    }
     
    anterior_a = estado_a;
    anterior_b = estado_b;
    delay(50);
}
