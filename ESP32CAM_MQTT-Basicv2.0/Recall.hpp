int flashLedPin = 4;                  // Para indicar el estatus de conexión
int statusLedPin = 33;                // Para ser controlado por MQTT
               
// Esta función permite tomar acciones en caso de que se reciba un mensaje correspondiente a un tema al cual se hará una suscripción
void callback(char* topic, byte* message, unsigned int length) {
  // Indicar por serial que llegó un mensaje
    Serial.print("Llegó un mensaje en el tema: ");
    Serial.print(topic);
  // Concatenar los mensajes recibidos para conformarlos como una varialbe String
    String messageTemp;                                   // Se declara la variable en la cual se generará el mensaje completo  
    for (int i = 0; i < length; i++) {                    // Se imprime y concatena el mensaje
      Serial.print((char)message[i]);
      messageTemp += (char)message[i];
  }

  // Se comprueba que el mensaje se haya concatenado correctamente
  Serial.println();
  Serial.print ("Mensaje concatenado en una sola variable: ");
  Serial.println (messageTemp);

  // En esta parte puedes agregar las funciones que requieras para actuar segun lo necesites al recibir un mensaje MQTT
  // Ejemplo, en caso de recibir el mensaje true - false, se cambiará el estado del led soldado en la placa.
  // El ESP323CAM está suscrito al tema esp/output
  
  if (String(topic) == "home/esp32/output") {                 // En caso de recibirse mensaje en el tema esp32/output
    if(messageTemp == "true"){
      Serial.println("Led encendido");
      digitalWrite(flashLedPin, HIGH);
    }                                                   // fin del if (String(topic) == "esp32/output")
    else if(messageTemp == "false"){
      Serial.println("Led apagado");
      digitalWrite(flashLedPin, LOW);
    }                                                   // fin del else if(messageTemp == "false")
  }                                                     // fin del if (String(topic) == "esp32/output")
}                                                       // fin del void callback

// Función para reconectarse
void reconnect() {
  // Bucle hasta lograr conexión
  while (!client.connected()) {                         // Pregunta si hay conexión
    Serial.print("Tratando de contectarse...");
    // Intentar reconexión
    if (client.connect("ESP32CAMClient")) {             //Pregunta por el resultado del intento de conexión
      Serial.println("Conectado");
      client.subscribe("home/esp32/output");                 // Esta función realiza la suscripción al tema
    }                                                   // fin del  if (client.connect("ESP32CAMClient"))
    else {                                              //en caso de que la conexión no se logre
      Serial.print("Conexion fallida, Error rc=");
      Serial.print(client.state());                     // Muestra el codigo de error
      Serial.println(" Volviendo a intentar en 5 segundos");
      // Espera de 5 segundos bloqueante
      delay(5000);
      Serial.println (client.connected ());             // Muestra estatus de conexión
    }                                                   // fin del else
  }                                                     // fin del bucle while (!client.connected())
}                                                       // fin de void reconnect(
