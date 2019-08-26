

#include <PubSubClient.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>
#include <WiFiEsp.h>
//#include <WiFiEspUdp.h>
//#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define ORG "gefj3r"
#define DEVICE_TYPE "Arduino"
#define DEVICE_ID "SONAR"
#define TOKEN "6w@P_@eWOccUI?(y&a"
#define WIFI_AP "Acer"
#define WIFI_PASSWORD "Moin786ahamad@"
// Defines Tirg and Echo pins of the Ultrasonic Sensor
WiFiEspClient espClient;

SoftwareSerial soft(6, 5); // 6-tx,5-rx
int status = WL_IDLE_STATUS;
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

const char publishTopic[] = "iot-2/evt/status/fmt/json";
const char responseTopic[] = "iotdm-1/response";
const char manageTopic[] = "iotdevice-1/mgmt/manage";
const char updateTopic[] = "iotdm-1/device/update";
const char rebootTopic[] = "iotdm-1/mgmt/initiate/device/reboot";
void callback(char* publishTopic, char* payload, unsigned int payloadLength);

PubSubClient client(server, 1883, callback, espClient);

int publishInterval = 30000; // 30 seconds
long lastPublishMillis;

long duration, distance;
int period = 5000;
unsigned long time_now = 0;
    
const int trigPin = 10;
const int echoPin = 11;
// Variables for the duration and the distance


void setup() 
{
    Serial.begin(115200);
        pinMode(trigPin, OUTPUT);
        pinMode(echoPin, INPUT);
        InitWiFi();
        Serial.print(WiFi.localIP());
        if (!!!client.connected()) 
        {
                Serial.print("Reconnecting client to ");
                Serial.println(server);
                while (!!!client.connect(clientId, authMethod, token)) 
                {
                Serial.print(".");
                }
          Serial.println();
        }
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  
}
void loop() 
{
  
  
      distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
      send_data(distance);
      
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}
void InitWiFi()
{
      // initialize serial for ESP module
      soft.begin(112500);
      // initialize ESP module
      WiFi.init(&soft);
      
      Serial.println("Connecting to AP …");
      // attempt to connect to WiFi network
      while ( status != WL_CONNECTED) {
            Serial.print("Attempting to connect to WPA SSID: ");
            Serial.println(WIFI_AP);
            // Connect to WPA/WPA2 network
            status = WiFi.begin(WIFI_AP, WIFI_PASSWORD);
            delay(1000);
      }
      Serial.println("Connected to AP");
}

void callback(char* publishTopic, char* payload, unsigned int length) {
      Serial.println("callback invoked");
}

void send_data(int distance)
{
  String payload = "{\"d\":{ \"level\" :";
          payload += distance;
          payload += "} }";
          Serial.print("Sending payload: ");
          Serial.println(payload);

          while (!!!client.publish(publishTopic, (char *)payload.c_str())) {
                  Serial.println("Publish ok");
                  if (!!!client.connected()) {
                        Serial.print("Reconnecting client to ");
                        Serial.println(server);
                        while (!!!client.connect(clientId, authMethod, token)) {
                              Serial.print(".");
                              delay(1000);
                        }
                        Serial.println();
                  }
          
          } 
            time_now = millis();           
            Serial.println("5 sec Delay");           
            while(millis() < time_now + period){
                //wait approx. [period] ms
            }  
}
