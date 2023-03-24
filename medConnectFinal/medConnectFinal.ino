// import libraries
#include <ezTime.h> // time
#include <PubSubClient.h> // pub/sub to mqtt
#include <ArduinoJson.h> // send json data
//#include <DHT.h> // dht temp/hum sensor
//#include <DHT_U.h> // dht temp/hum sensor
#include <ESP8266WiFi.h> // connect nodemcu to wifi
#include "arduino_secrets.h" // contains sensetive data like passwords


// set the dht type
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// Sensors and Buzzer
// uint8_t DHTPIN = A1;   // for dht on pin analog 4 of the nodemcu
uint8_t BUZZERPIN = 16;   // for buzzer on pin analog 2 of the nodemcu
uint8_t BOXPINS[] = {14, 12, 13, 5, 0, 4, 2}; // array of input bins for box circuits
float Temperature;
float Humidity;
//DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT sensor.

// Wifi and MQTT
const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;
const char* mqtt_server = "mqtt.cetools.org";
const char* topic = "student/ucfnbou/medConnected";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int past = 0;

// Date and time
Timezone GB;

void setup() {
  // open serial connection for debug info
  Serial.begin(115200);
  delay(1000);

  // start DHT sensor
  //pinMode(DHTPIN, INPUT);
  //dht.begin();

  // start buzzer
  pinMode(BUZZERPIN, OUTPUT);

  // set box pins
  for (int i = 0; i < 7; i++) {
      pinMode(BOXPINS[i], INPUT_PULLUP);
    }

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
  // start by connecting to a WiFi network
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
  Serial.println("Wi-Fi connected");
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
  // Temperature = 1;
  // Serial.print("Publish message for t: ");
  // Serial.println(msg);

  // Humidity = dht.readHumidity(); // Gets the values of the humidity
  // default humidity value for debugging without a dht sensor
  // Humidity = 1;
  // Serial.print("Publish message for h: ");
  // Serial.println(msg);

  int openCount = 0; // count number of open circuits
  // iterate through pins and read state
  // start; stop; step
  for (int i = 0; i < 7; i++) {
    // state is TRUE or FALSE based on pin reading at i
    // TRUE if LOW; FALSE if HIGH
    bool state = digitalRead(BOXPINS[i]) == LOW;
    // if state = TRUE
    if (state) {
      Serial.print("Circuit ");
      Serial.print(i + 1);
      Serial.println(" is closed");
    } else { // if state = FALSE
      Serial.print("Circuit ");
      Serial.print(i + 1);
      Serial.println(" is open");
      // increment the count of open circuits
      openCount++;
    }
  }
  Serial.print("Number of open circuits: ");
  Serial.println(openCount);
  delay(500);

  // put data in json document
  // create json document called docSend
  StaticJsonDocument<256> docSend;
  // add temperature object with value of temperature variable
  // docSend["Temperature"] = Temperature;
  // add humidity object with value of humidity
  // docSend["Humidity"] = Humidity;
  // add open circuit count
  docSend["Number"] = openCount;

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
  int myValue = docRec["times"];
  //char json[length] = myString;
  Serial.print(myValue);
  Serial.println();

  if (myValue != past) {
    for (int i = 0; i < 5; i++) {
      Serial.print("buzz ");
      tone(BUZZERPIN, 600);
      delay(2000);
      noTone(BUZZERPIN);
    }
  past = myValue;
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
      delay(1000);
    }
  }
}
