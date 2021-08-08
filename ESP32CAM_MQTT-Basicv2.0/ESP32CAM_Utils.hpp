void ConnectWiFi(bool useStaticIP = false)
{
   
  Serial.println();
  Serial.println();
  Serial.print("Conectar a ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);                           // Esta es la función que realiz la conexión a WiFi
  if(useStaticIP) WiFi.config(ip, gateway, subnet);     // En caso de usar una Ip estatica
  while (WiFi.status() != WL_CONNECTED) {               // Este bucle espera a que se realice la conexión
    digitalWrite (statusLedPin, HIGH);
    delay(500);                                         //dado que es de suma importancia esperar a la conexión, debe usarse espera bloqueante
    digitalWrite (statusLedPin, LOW);
    Serial.print(".");                                  // Indicador de progreso
    delay (5);
  }
  
  // Cuando se haya logrado la conexión, el programa avanzará, por lo tanto, puede informarse lo siguiente
  Serial.println();
  Serial.println("WiFi conectado");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());

  // Si se logro la conexión, encender led
  if (WiFi.status () > 0){
  digitalWrite (statusLedPin, LOW);
  }
  
  delay (1000);                                          // Esta espera es solo una formalidad antes de iniciar la comunicación con el broker

}
