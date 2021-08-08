/*
 * Conexión básica por MQTT del NodeMCU
 * por: Hugo Escalpelo
 * Fecha: 28 de julio de 2021
 * 
 * Este programa envía datos  por Internet a través del protocolo MQTT. Para poder
 * comprobar el funcionamiento de este programa, es necesario conectarse a un broker
 * y usar NodeRed para visualzar que la información se está recibiendo correctamente.
 * Este programa no requiere componentes adicionales.
 * 
 * Componente     PinESP32CAM     Estados lógicos
 * ledStatus------GPIO 33---------On=>LOW, Off=>HIGH
 * ledFlash-------GPIO 4----------On=>HIGH, Off=>LOW
 */

//Bibliotecas       

#include <WiFi.h>                      // Biblioteca para el control de WiFi
#include <PubSubClient.h>              // Biblioteca para conexion MQTT
#include <DHT.h>                       // Biblioteca para elsensor DHT11
#include <ArduinoJson.h>               // Biblioteca para crear un documento JSON


#include "config.h"                    //Biblioteca para configurar las credenciales de nuestra red como la del broker, no esnecesario instalarla                
#include "Recall.hpp"                  //Biblioteca que contiene las funciones callback y reconect, no esnecesario instalarla 
#include "ESP32CAM_Utils.hpp"          //Biblioteca para conectarse a la red, no esnecesario instalarla 

// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11
 
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);
 


// Variables

long timeNow, timeLast;               // Variables de control de tiempo no bloqueante
int wait = 5000;                      // Indica la espera cada 5 segundos para envío de mensajes MQTT
char buffer[256];                     // Variables para almacenar la conversion de JSON object a string 

// Inicialización del programa

void setup() {

  Serial.begin (115200);                        // Iniciar comunicación serial
  pinMode (flashLedPin, OUTPUT);
  pinMode (statusLedPin, OUTPUT);
  digitalWrite (flashLedPin, LOW);
  digitalWrite (statusLedPin, HIGH);
  dht.begin();
  ConnectWiFi();
  // Conexión con el broker MQTT
  client.setServer(server, 1883);               // Conectarse a la IP del broker en el puerto indicado
  client.setCallback(callback);                 // Activar función de CallBack, permite recibir mensajes MQTT y ejecutar funciones a partir de ellos
  delay(1500);                                  // Esta espera es preventiva, espera a la conexión para no perder información
  timeLast = millis ();                         // Inicia el control de tiempo
}                                               // fin del void setup ()

void loop() {

  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();

  DynamicJsonDocument doc2(JSON_OBJECT_SIZE(13));

      doc2["id"]="humberto9003";
      doc2["temperatura"]=t;         // arreglo dentro de objeto cread del primer doc
      doc2["humedad"]=h;
  
                                      //Verificar siempre que haya conexión al broker
  if (!client.connected()) {
    reconnect();                      // En caso de que no haya conexión, ejecutar la función de reconexión, definida despues del void setup ()
  }                                   // fin del if (!client.connected())
  client.loop();                      // Esta función es muy importante, ejecuta de manera no bloqueante las funciones necesarias para la comunicación con el broker
  
  timeNow = millis();                 // Control de tiempo para esperas no bloqueantes
  if (timeNow - timeLast > wait) {    // Manda un mensaje por MQTT cada cinco segundos
    timeLast = timeNow;               // Actualización de seguimiento de tiempo

    serializeJson(doc2, buffer);
    Serial.println(buffer);
    
    client.publish("home/esp32/data", buffer); // Esta es la función que envía los datos por MQTT, especifica el tema y el valor
  }                                   // fin del if (timeNow - timeLast > wait)
}                                     // fin del void loop ()
