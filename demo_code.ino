#include <Wire.h>
#include <rgb_lcd.h>
#include <DHT.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "homePage.h"

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define SOIL_SENSOR_PIN 34
#define PUMP_PIN 5
#define TRIG_PIN 12  
#define ECHO_PIN 14  
#define LDR_PIN 35    

#define INTERVAL 2000  // Sensor update every 2 secs

const char* ssid = "jxxj";
const char* password = "bershka1";
WebServer server(80);
rgb_lcd lcd;

long lastReadTime = 0;  

// Sensor Readings
String getTemp() { 
    return String(dht.readTemperature(), 1); 
}

String getHumid() {
   return String(dht.readHumidity(), 1); 
   }
   
String getSoil() {
  int raw = analogRead(SOIL_SENSOR_PIN);
  int percent = map(raw, 600, 2000, 0, 100);
  percent = constrain(percent, 0, 100);
  return String(percent);
}


String getLDR() {
  int raw = analogRead(LDR_PIN); 
  int percent = map(raw, 100, 1550, 0, 100);
  percent = constrain(percent, 0, 100);
  return String(percent);
}



long getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10); 
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    return (duration == 0) ? -1 : duration / 58.2;
}

// HTML 
void handleRoot() {
    server.send(200, "text/html", homePagePart1);
}

 //Real-Time Sensor readings
void handleSensorData() {
    String json = "{";
  json += "\"temperature\":" + getTemp() + ",";
  json += "\"humidity\":" + getHumid() + ",";
  json += "\"soilMoisture\":" + getSoil() + ",";
  json += "\"ldr\":" + getLDR() + ",";
  json += "\"ultrasonic\":" + String(getDistance());
  json += "}";

    server.send(200, "application/json", json);
}

//404 Not Found
void handleNotFound() {
    server.send(404, "text/plain", "Not Found");
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    lcd.begin(16, 2);
    lcd.setRGB(0, 128, 255);
    dht.begin();
    pinMode(PUMP_PIN, OUTPUT);
    pinMode(SOIL_SENSOR_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // WiFi connection
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }

    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    lcd.setCursor(0, 0);
    lcd.print("Connected to WiFi!");
    delay(2000);
    lcd.clear();

    if (MDNS.begin("esp32")) { Serial.println("MDNS responder started"); }

    //Web Server Endpoints
    server.on("/", handleRoot);
    server.on("/sensor-data", handleSensorData);
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();

    if (millis() - lastReadTime >= INTERVAL) {
        lastReadTime = millis();

        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();
        int soilRaw = analogRead(SOIL_SENSOR_PIN);
        int soilPercent = map(soilRaw, 600, 2800, 0, 100);
        soilPercent = constrain(soilPercent, 0, 100);

        int ldrRaw = analogRead(LDR_PIN);
        int ldrPercent = map(ldrRaw, 100, 2250, 0, 100);
        ldrPercent = constrain(ldrPercent, 0, 100);

        long distance = getDistance();

        //Lcd Temp + Humidity
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(temperature, 1);
        lcd.print("C");

        lcd.setCursor(0, 1);
        lcd.print("Hum: ");
        lcd.print(humidity, 1);
        lcd.print("%");
        delay(1000);

        //Lcd Soil + LDR %
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Soil: ");
        lcd.print(soilPercent);
        lcd.print("%");

        lcd.setCursor(0, 1);
        lcd.print("Light: ");
        lcd.print(ldrPercent);
        lcd.print("%");
        delay(1000);

        //Lcd Ultrasonic
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Water Tank:");

        lcd.setCursor(0, 1);
        if (distance == -1) {
            lcd.print("Full!");
        } else {
            lcd.print(distance);
            lcd.print(" cm");
        }
        delay(1000);

        // Pump when soilM < 800
        if (soilRaw < 800) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Moisture lvl Low!\n");
            lcd.setCursor(0, 1);
            lcd.print("Watering...");
            digitalWrite(PUMP_PIN, HIGH);
            delay(5000);
            digitalWrite(PUMP_PIN, LOW);
            lcd.clear();
        }
    }
}
