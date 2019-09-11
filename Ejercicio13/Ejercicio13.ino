/*
   Ejercicio13 - PulseIn
*/

//PINES
#define PIN_BOTON_A 2
#define PIN_LED_1 4
#define PIN_LED_2 5 //PWM
#define PIN_LED_3 6 //PWM
#define PIN_LED_4 7

u32 pulso;
u32 ultimo_pulso = millis(); 
boolean encendido = false;
int led;  

void setup() {
  //Inicializo puerto serie
  Serial.begin(9600);

  //Inicializo Pines
  Serial.println(F("Inicializando pines digitales..."));
  pinMode(PIN_BOTON_A, INPUT_PULLUP);
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  pinMode(PIN_LED_4, OUTPUT);

  for (int i = PIN_LED_1; i <= PIN_LED_4; i++) digitalWrite(i, LOW);
}

void loop() {
  if ((millis()-ultimo_pulso)>10000) {     
    Serial.println("Pulsa el boton, caramba !");
    ultimo_pulso = millis();
  }
  
  pulso = pulseIn(PIN_BOTON_A,LOW,10000000)/1000;
  if (pulso) {
    if (pulso>=2000)  Serial.print("Pulsación larga");
    else              Serial.print("Pulsación corta");
    ultimo_pulso = millis();
    Serial.println(" -> Tiempo de pulsacion -> " + (String)pulso);
    delay(50);
    if (encendido==false) {
      if (pulso>=2000) {
        encendido = true;
        led = PIN_LED_1;
        digitalWrite(led, HIGH);
        Serial.println("Encendiendo...");
        }
      }
     else {
      if (pulso>=2000) {
        encendido = false;
        digitalWrite(led, LOW);
        Serial.println("Apagando...");
        }
      else
        if (pulso) {
          digitalWrite(led, LOW);
          led++;
          if (led>PIN_LED_4) led = PIN_LED_1;
          digitalWrite(led, HIGH);
          Serial.println("Saltando...");
          }
      }
    }
}
/*
for (int i = PIN_LED_1; i <= PIN_LED_4; i++) {
      Serial.println("Probando LED en PIN " + (String)i);
      digitalWrite(i, HIGH);
      delay(500);
      digitalWrite(i, LOW);
      delay(500);
    }
*/
