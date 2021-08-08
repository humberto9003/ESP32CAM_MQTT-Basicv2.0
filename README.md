# ESP32CAM_MQTT-DHT11
Este repositorio contiene el programa para comunicar el ESP32CAM por MQTT, enviando las variables sensadas por el DHT11 (Temperatura y Humedad) en un documento JSON. Publicando en un tema en particular hacia un broker, al cual se puede subscribir cualquier cliente para poder monitorear la temperatura y humedad en tiempo real. 

Puedes encontrar un video del funcionamiento correspondiente a este ejercicio en el siguiente enlace.

https://edu.codigoiot.com/

### Requisitos
Para que el código de este repositorio funcione, es necesario contar con lo siguiente:

- ESP32CAM AI-Thinker
- Camara OV2640
- Programador FTDI con su cable
- Sensor de Temperatura y Humedad DHT11
- Ubuntu 20.04
- IDE de Arduino 1.8 o superior
- Biblioteca PubSubClient para Arduino IDE
- Biblioteca ArduinoJson
- Biblioteca DHT sensor library
- Broker Mosquitto funcionando de forma local en el puerto 1883
- NodeRed corriendo de forma local en el puerto 1880
- Nodos Dashboard para NodeRed

### Guías
Para configurar correctamente la IDE de Arduino para trabajar con el ESP32CAM, puedes consultar el siguiente enlace.

https://edu.codigoiot.com/course/view.php?id=850

Para configurar correctamente tu broker mosquitto puedes consultar el siguiente enlace.

https://edu.codigoiot.com/course/view.php?id=818

Para configurar correctamente NodeRed puedes consultar el siguiente enlace.

https://edu.codigoiot.com/course/view.php?id=817

Puedes obtener la biblioteca PubSubClient desde el siguiente enlace.

https://github.com/knolleary/pubsubclient

Puedes obtener la biblioteca ArduinoJson desde el siguiente enlace.

https://github.com/bblanchon/ArduinoJson.git


Puedes obtener la biblioteca DHT-sensor-librery desde el siguiente enlace.

https://github.com/adafruit/DHT-sensor-library

El flow de NodeRed lee en el tema `home/esp32/data` y publica en el tema `home/esp32/output`, por lo que deberás configurar los nodos MQTT para conectarse a estos temas y al broker de tu elección.

Los nodos switch, gauge y chart  de la sección dashboard deberán tener correctamente configurados el tab y group en el que se visualizarán.

### Funcionamiento

Para observar el funcionamiento de este proyecto deberás realizar lo siguiente.

1. Carga el flow MQTT+ESP32CAM-Basicv2.0.json en NodeRed.
2. Comprueba que el broker MQTT esté funcionando.
3. Carga el programa ES2CAM_MQTT-Basic.ino en el ESP32CAM.
4. Visita el dashboard de NodeRed

![](https://github.com/humberto9003/ESP32CAM_MQTT-Basicv2.0/blob/master/flow_DHT11.jpg)

Podrás monitoraer la temperatura y la humedad del sensor dht11, la cual envía el prográma base del ESP32CAM. Puedes controlar el led flash del ESP32CAM con el switch del dashboard.

Por: [Humberto Pastor](https://https://github.com/humberto9003)
