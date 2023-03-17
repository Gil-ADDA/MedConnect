#include <ezTime.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <DHT_U.h>
#include "arduino_secrets.h"

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// Sensors and Buzzer
uint8_t DHTPin = 4;   // on Pin 4 of the nodemcu
uint8_t BuzzerPin = 2;   // Pin 2 of the nodemcu
float Temperature;
float Humidity;
DHT dht(DHTPin, DHTTYPE);   // Initialize DHT sensor.

// Wifi and MQTT
const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;
const char* mqtt_server = "mqtt.cetools.org";
const char* topic = "student/ucfnbou/medConnected";

ESP8266WebServer server(80);

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

// Date and time
Timezone GB;

void setup() {
  // open serial connection for debug info
  Serial.begin(115200);
  delay(100);

  // start DHT sensor
  pinMode(DHTPin, INPUT);
  dht.begin();

  //start buzzer
  pinMode(BuzzerPin, OUTPUT);

  // run initialisation functions
  startWifi();
  syncDate();

  // start MQTT server
  client.setServer(mqtt_server, 1884);
  client.setCallback(callback);
}

void loop() {

  if (minuteChanged()) {
    sendMQTT();
    Serial.println(GB.dateTime("H:i:s")); // UTC.dateTime("l, d-M-y H:i:s.v T")
  }

  client.loop();
}

void startWifi() {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // check to see if connected and wait until you are
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void syncDate() {
  // get real date and time
  waitForSync();
  Serial.println("UTC: " + UTC.dateTime());
  GB.setLocation("Europe/London");
  Serial.println("London time: " + GB.dateTime());

}

void sendMQTT() {
  //reconnect if the client is no connected
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // get data
  // Temperature = dht.readTemperature(); // Gets the values of the temperature
  // default temperature value for debugging without a dht sensor
  Temperature = 1;
  Serial.print("Publish message for t: ");
  Serial.println(msg);

  // Humidity = dht.readHumidity(); // Gets the values of the humidity
  // default humidity value for debugging without a dht sensor
  Humidity = 1;
  Serial.print("Publish message for h: ");
  Serial.println(msg);

  // put data in json document
  // create json document called docSend
  StaticJsonDocument<256> docSend;
  // add temperature object with value of temperature variable
  docSend["Temperature"] = Temperature;
  // add humidity object with value of humidity
  docSend["Humidity"] = Humidity;

  // using buffer helps to allocate memory quicker
  char buffer[256];
  // serialize json document
  serializeJson(docSend, buffer);
  // publish json document
  client.publish("student/ucfnbou/medConnect", buffer);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  StaticJsonDocument<256> docRec;  // Allocate the JSON document
  deserializeJson(docRec, payload, length);// Deserialize the JSON document
  String myString = String((char*)payload);
  int myValue = docRec["Temperature"];
  //char json[length] = myString;
  Serial.print(myValue);
  Serial.println();

  if (myValue == 1) {
    for (int i = 0; i < 5; i++) {
      Serial.print("buzz ");
      tone(BuzzerPin, 441);
      delay(500);
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    // Attempt to connect with clientID, username and password
    if (client.connect(clientId.c_str(), mqttuser, mqttpass)) {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe("student/ucfnbou/medConnected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
