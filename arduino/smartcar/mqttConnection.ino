#include <Smartcar.h>
#include <ArduinoMqttClient.h>
#include <WiFi101.h>
#include "arduino_secrets.h"

char ssid[] = "Kwabena's iPhone";        // your network SSID
char pass[] = "twumasi123..";        // your network password

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = '127.0.0.1' ; //host
int        port     = 1883;
const char topic[]  = "control_button_topic";
const char topic2[]  = "car_movement_topic";

void setup() {
	  //Initialize serial and wait for port to open:
	  Serial.begin(9600);
	  while (!Serial) {

	    ; // wait for serial port to connect. Needed for native USB port only

	  }

	  // attempt to connect to Wifi network:
	  Serial.print("Attempting to connect to SSID: ");
	  Serial.println(ssid);
	  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {

	    // failed, retry

	    Serial.print(".");

	    delay(5000);

	  }


	  Serial.println("You're connected to the network");
	  Serial.println();


	  Serial.print("Attempting to connect to the MQTT broker: ");
	  Serial.println(broker);


	  if (!mqttClient.connect(broker, port)) {
	    Serial.print("MQTT connection failed! Error code = ");
	    Serial.println(mqttClient.connectError());
	    while (1);
	  }


	  Serial.println("You're connected to the MQTT broker!");
	  Serial.println();


	  // set the message receive callback

	  mqttClient.onMessage(onMqttMessage);
	  Serial.print("Subscribing to topic: ");
	  Serial.println(topic);

	  Serial.println();


	  // subscribe to a topic

	  mqttClient.subscribe(topic);

	  mqttClient.subscribe(topic2);

	  mqttClient.subscribe(topic3);


	  // topics can be unsubscribed using:

	  // mqttClient.unsubscribe(topic);


	  Serial.print("Topic: ");

	  Serial.println(topic);

	  Serial.print("Topic: ");

	  Serial.println(topic2);

	  Serial.print("Topic: ");

	  Serial.println(topic3);


	  Serial.println();

	}

    void loop() {

	  // call poll() regularly to allow the library to receive MQTT messages and

	  // send MQTT keep alive which avoids being disconnected by the broker

	  mqttClient.poll();

	}

    void onMqttMessage(int messageSize) {
	  DynamicJsonDocument doc(1024);

	  // we received a message, print out the topic and contents
	  Serial.println("Received a message with topic '");
	  Serial.print(mqttClient.messageTopic());
	  Serial.print("', length ");
	  Serial.print(messageSize);
	  Serial.println(" bytes:");


	  // Tenemos que procesar los mensajes



	  // You can use a String as your JSON input.
	  // WARNING: the string in the input  will be duplicated in the JsonDocument.
	  String input = mqttClient.messageTopic();
	  deserializeJson(doc, input);
	  JsonObject obj = doc.as<JsonObject>();

	  // 1. Separar por coma
	  // 2. Separar por :
	  // 3. Buscar en el array, porque no es un objeto, el elemento dirección
	  // 4. Buscar en el array, porque no es un objeto, el elemento steps
	  // -----> Esto esta mal, estamos en POO, mejor usemos objetos porque nos van a permitir tener un código más limpio

	  // You can use a String to get an element of a JsonObject
	  // No duplication is done.
	  String direction = obj[String("direction")];
	  Int steps = obj[String("steps")];


	  // use the Stream interface to print the contents

	  while (mqttClient.available()) {

	    Serial.print((char)mqttClient.read());
	  }
	  Serial.println();
	  Serial.println();

	}