#include <ESP8266WiFi.h>
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <PubSubClient.h>
#include <Streaming.h>
#include <Servo.h>

//#define SLEEP_DELAY_IN_SECONDS   30

// MQTT setup
const char* mqtt_server = "<MQTT Broker address>";
const char* mqtt_username = "esp12";                   // used while connecting to the broker
const char* mqtt_password = "";                        // leave empty if not needed
const String mqtt_topic_syntax = "servo/";             // the first part of the MQTT topic, the mac address of the ESP is added automaticaly when creating the full topic
char* mqtt_topic = "";
char* mqtt_payload = "";
boolean retained = false;
char message_buff[100];

WiFiClient espClient;
PubSubClient client(espClient);
Servo myservo;

void setup() {
  // setup serial port
  Serial.begin(115200);

  // setup WiFi
  WiFiManager wifiManager;
  wifiManager.autoConnect("ESP_setup");

  //setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // setup servo
  myservo.attach(5);

  // create mqtt_topic with MAC address
  mqtt_topic = createMqtt_topic(mqtt_topic_syntax);
  Serial << "MQTT Topic generated (dialog): " << mqtt_topic << endl;

  // sending "connected" to broker
  client.publish(mqtt_topic, "connected", retained);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  //Serial << "Closing MQTT connection..." << endl;
  //client.disconnect();

  //Serial << "Closing WiFi connection..." << endl;
  //WiFi.disconnect();
}
