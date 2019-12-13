#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif


const char* ssid = "SSID";
const char* password = "PASSWORD";

// REPLACE with your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.43.133:8000";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
String apiKeyValue = "KCN17TZrrs";

// DHT Config
#include "DHT.h"
#define DHTTYPE DHT11     // DHT 11
#define DHTPin  5         // D1
DHT dht(DHTPin, DHTTYPE); // Initialize DHT sensor
float Temperature;
float Humidity;

// DS18B20 Config
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4     // D2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Capacitive Soil Moisture Config
#define CSM A0

//LDR Config
#define LDR_1 14   // D5 
#define LDR_2 12   // D6 
#define LDR_3 13   // D7 
#define LDR_4 0    // D3 

void connectWifi(){
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  
  connectWifi();
  
  // DHT Config
  pinMode(DHTPin, INPUT);
  dht.begin();
  
  // DS18B20 Config
  pinMode(ONE_WIRE_BUS, INPUT);
  sensors.begin();

  // LDR Config
  pinMode(LDR_1, INPUT);
  pinMode(LDR_2, INPUT);
  pinMode(LDR_3, INPUT);
  pinMode(LDR_4, INPUT);
  
}

void loop() {
  
  /*
   * Gathering data to send
   */
   
  // DHT Data
  float Temperature = dht.readTemperature(); // Gets the values of the temperature
  float Humidity = dht.readHumidity();       // Gets the values of the humidity
  // DS18B20 Data
  sensors.requestTemperatures();
  float TempDS = sensors.getTempCByIndex(0);
  // CSM Data
  int val = analogRead(CSM);
  int moistureVal = map(val,900,300,0,100);
  // LDR Data
  int ldr_value = digitalRead(LDR_1) + digitalRead(LDR_2) + digitalRead(LDR_3) + digitalRead(LDR_4);
  
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Preparing HTTP POST request data
    
    String httpRequestData = "api_key=" + apiKeyValue 
                           + "&value1=" + String(Temperature)
                           + "&value2=" + String(Humidity) 
                           + "&value3=" + String(TempDS) 
                           + "&value4=" + String(moistureVal)
                           + "&value5=" + String(ldr_value)
                           + "";   
    
    // You can comment the httpRequestData variable above
    // then, use the httpRequestDataTest variable below (for testing purposes)
    /*
      String httpRequestDataTest = "api_key=" + apiKeyValue 
                             + "&value1=" + String(27.5)
                             + "&value2=" + String(45) 
                             + "&value3=" + String(27.2) 
                             + "&value4=" + String(30)
                             + "&value5=" + String(0)
                             + "";   
    */
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
    
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
    
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();

  unsigned long time_delay = 30*1000;
  delay(time_delay);
  
  WiFi.forceSleepWake();
  delay(10);
  WiFi.mode(WIFI_STA);
  connectWifi();
}
