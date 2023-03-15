#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <ezTime.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <String.h>
#include "arduino_secrets.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <Servo.h>

int totalColumns = 16;
int totalRows = 2;
Servo myservo;
int pos;

LiquidCrystal_I2C lcd(0x27, totalColumns, totalRows);

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;

const int buttonPin = 13;
int times = 0;

String current_time;
String past_time;
int a =0;
int b =0;
int tem = 0;
int hum = 0;
Timezone GB;
ESP8266WebServer server(80);
const char* mqtt_server = "mqtt.cetools.org";
WiFiClient espClient;            //handle wifi messages
PubSubClient client(espClient);  //handle MQTT messages, pass wificlient to connect
StaticJsonDocument<200> doc;     // Allocate the JSON document
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);

  startWifi(); 
  startWebserver(); 
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.init(); 
  lcd.backlight(); // use to turn on and turn off LCD back light
  // Set button as interrupt, assign interrupt function and set RISING mode

  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  //waitForSync();

  Serial.println("UTC: " + UTC.dateTime());

  GB.setLocation("Europe/London");
  Serial.println("London time: " + GB.dateTime());  

  // start MQTT server
  client.setServer(mqtt_server, 1884);
  client.setCallback(callback);
}

void detectButton() {
      delay(100);
      if(digitalRead(buttonPin) == LOW){
        //Print when button pressed
       Serial.println("Button pressed");
              // Current time
        times = times+ 1;
      }

    
}

void startWifi() {
  // connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // when not connected keep trying until you are
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //Exit the while loop means have a connection
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address of Huzzah
}

void startWebserver() {
  // when connected and IP address obtained start HTTP server
  server.begin();
  Serial.println("HTTP server started");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  StaticJsonDocument<1024> doc;  // Allocate the JSON document
  String myString = String((char*)payload);
  //char json[length] = myString;

  deserializeJson(doc, myString);  // Deserialize the JSON document

  // Fetch values.
  int home_score = doc["Temperature"];
  // int away_score = doc["away_score"];
  // String home_team_en = doc["home_team_en"];
  // String away_team_en = doc["away_team_en"];
  //String finished = doc["finished"];
  // String datatime = doc["datetime"];
  a = home_score;
  Serial.println(a);
  // b = away_score;
  // current = finished;
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
      client.subscribe("student/ucfnbou/medConnect");  //subscribe to the topic
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void sendMQTT() {
  //reconnect if the client is no connected
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  // Temperature = 1;
  // put data in json document
  // create json document called docSend
  StaticJsonDocument<256> docSend;
  // add temperature object with value of temperature variable
  docSend["times"] = times;
  // using buffer helps to allocate memory quicker
  char buffer[256];
  // serialize json document
  serializeJson(docSend, buffer);
  // publish json document
  client.publish("student/ucfnbou/medConnected", buffer);
}






void testTime(){
  current_time = GB.dateTime("d-M-y");
 //Serial.println(current_time);  
}

void drawlcd1(){
  lcd.setCursor(0, 0);
  lcd.print("temperature:");
  lcd.setCursor(0,1);
  lcd.print(tem);
  delay(1000);
  lcd.clear(); 
}

void drawlcd2(){
  lcd.setCursor(0, 0);
  lcd.print("humidity:");
  lcd.setCursor(0,1);
  lcd.print(hum);
  delay(1000);
  lcd.clear(); 
}

void servo1() {
  myservo.write(0);
}

void servo2(){
  myservo.write(180);
}
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();      //?
  if (!client.connected()) {  //check if connected to MQTT
    reconnect();
  }

  client.loop();
  testTime();
  drawlcd2();
  Serial.println(times);
  if(current_time != past_time){
 // servo reset
  }
  if (a != b && a != 0){
//servo run    and b=a

  }
  if (a =0){
    b=0;
  }
  past_time = current_time;
  detectButton();
  sendMQTT();
  delay(1000);
  drawlcd1();
}
