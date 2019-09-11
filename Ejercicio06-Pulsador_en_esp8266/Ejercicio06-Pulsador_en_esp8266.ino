/*
   Ejercicio06 - Pulsador en esp8266
   La parte del botón funciona bien. 
   Lo del servidor lo miro en tu ejemplo ...
*/

//Librería Wifi
#include "ESP8266WiFi.h"

//Archivo de contraseñas: añade un fichero secrets.h con este contenido
const char* ssid = "CTLR";
const char* password = "cntrTcnlgc012";
//#include <secrets.h>

//Librería Pantalla
#include <Wire.h>
#include <Adafruit_SSD1306.h>

//Define pines
#define PIN_BOTON_B D3

//Define pantalla
#define OLED_RESET 0  // GPIO0

//Objeto Pantalla
Adafruit_SSD1306 display(OLED_RESET);

// Create an instance of the server
WiFiServer server(80);

boolean led_state = LOW;
int pulsos_b = 0;
boolean anterior_b = digitalRead(PIN_BOTON_B);
long momento = millis();

void setup() {
  Serial.begin(115200);

  //Configure LED BUILTIN
  pinMode(LED_BUILTIN, OUTPUT);
  
  //Configure pulsador
  pinMode(PIN_BOTON_B, INPUT);

  //Pantalla
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)

  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  Serial.println(F("Prueba Pulsador"));
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  Serial.println(WiFi.localIP());
  
}

void loop() {

  boolean estado_b = digitalRead(PIN_BOTON_B);
  if (anterior_b != estado_b && estado_b == HIGH) {  //flanco ascendente pull-down
    pulsos_b ++;
      
    Serial.println("Botón pulsado " + (String)pulsos_b + " veces en " + (millis()-momento) + " milisegundos." );
        
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(pulsos_b);
    display.print(" pulsos\n");
    display.print((millis()-momento)/1000);
    display.print(" s.");
    display.display();

    // Check if a client has connected
    WiFiClient client = server.available();
    if (client) {
      // Wait until the client sends some data
      Serial.println("new client");
      while (!client.available()) delay(1);
      // Read the first line of the request
      String req = client.readStringUntil('\r');
      Serial.println(req);
      client.flush();
      // Match the request
      if (req.indexOf("GET / HTTP/1.1") != -1)
        muestraWeb(client);
      else if (req.indexOf("POST / HTTP/1.1") != -1) {
              Serial.println("------> Cambio estado LED");
              led_state = !led_state;
              digitalWrite(LED_BUILTIN, led_state);  //cambio el estado del led
              muestraWeb(client);
              }
           else { Serial.println("invalid request"); client.stop(); }
      client.flush();
      delay(1);
      Serial.println("Client disonnected");
    }

    momento = millis();
    }
  anterior_b = estado_b;
  delay(1); //Evitar rebotes
  }

  void muestraWeb(WiFiClient client) {
  client.println("HTTP/1.0 200K");
  client.println();
  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<body>");
  if (led_state == HIGH) client.println("<p>LED ENCENDIDO</p>");
  else client.println("<p>LED APAGADO</p>");
  client.println("<form action=\"\" method=\"post\">");
  if (led_state == HIGH) client.println("<input type=\"submit\" value=\"Apaga Led\" />");
  else client.println("<input type=\"submit\" value=\"Enciende Led\" />");
  client.println("</form>");
  client.println("</body>");
  client.println("</html>");
  client.println();
  client.stop();
  client.flush();
}
