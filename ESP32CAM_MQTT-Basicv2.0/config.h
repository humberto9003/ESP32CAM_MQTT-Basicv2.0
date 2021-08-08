// Sustituir con datos de vuestra red
const char* ssid     = "***********";   
const char* password = "***********";
const char* hostname = "ESP32CAM";
const char* mqtt_server = "3,66,119,222"; //Datos del broker MQTT// Si estas en una red local, coloca la IP asignada, en caso contrario, coloca la IP publica

IPAddress server(3,66,119,222);
IPAddress ip (192,168,1,0);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Objetos
WiFiClient espClient; // Este objeto maneja los datos de conexion WiFi
PubSubClient client(espClient); // Este objeto maneja los datos de conexion al broker
