#include <Wire.h>
#include <rgb_lcd.h>
#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "homePage.h"

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define SOIL_SENSOR_PIN 34
#define PUMP_PIN 5

const char* ssid = "jxxj";
const char* password = "bershka1";
WebServer server(80);
rgb_lcd lcd;

String getTemp() 
{
  float temperature = dht.readTemperature();
  return String(temperature, 1);
}

String getHumid() 
{
  float humidity = dht.readHumidity();
  return String(humidity, 1);
}

String getSoil() 
{
  int soilMoisture = analogRead(SOIL_SENSOR_PIN);
  return String(soilMoisture, 1);
}

void handleRoot() 
{
  String message = homePagePart1 + getTemp() + homePagePart2 + getHumid() + homePagePart3 + getSoil() + homePagePart4;
  server.send(200, "text/html", message);
}

void handleNotFound() 
{
  String message = "File Not Found\n\n";
  message += "URI: " + server.uri() + "\n";
  message += "Method: " + String((server.method() == HTTP_GET) ? "GET" : "POST") + "\n";
  message += "Arguments: " + String(server.args()) + "\n";
  for (uint8_t i = 0; i < server.args(); i++) 
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup() 
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  lcd.begin(16, 2);
  lcd.setRGB(0, 128, 255);
  dht.begin();
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(SOIL_SENSOR_PIN, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("Connecting to WIFI!");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connected!");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Automated Home");
  lcd.setCursor(0, 1);
  lcd.print("Irrigation System");
  delay(2000);
  lcd.clear();

  if (MDNS.begin("esp32")) 
  {
    Serial.println("MDNS responder started");
  }
  server.on("/", handleRoot);
  server.on("/inline", []() 
  {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {

  server.handleClient();
  delay(2);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int soilMoisture = analogRead(SOIL_SENSOR_PIN);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Automated Home");
  lcd.setCursor(0, 1);
  lcd.print("Irrigation System");
  delay(2000);
  lcd.clear();

  // Display DHT11 readings
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity, 1);
  lcd.print("%");
  delay(2000);
  lcd.clear();

  // Display soil moisture
  lcd.setCursor(0, 0);
  lcd.print("Soil M: ");
  lcd.print(soilMoisture, 1);
  lcd.print(" %");
  delay(2000);

  // Check soil moisture and water plants
  if (soilMoisture < 500) 
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Moisture content");
    lcd.setCursor(0, 1);
    lcd.print("low!! Watering...");
    digitalWrite(PUMP_PIN, HIGH);
    delay(5000);
    digitalWrite(PUMP_PIN, LOW);
    lcd.clear();
  }
}
