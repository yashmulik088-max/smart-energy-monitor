/*
  Smart Energy Monitor
  ESP32 + PZEM-004T

  IMPORTANT:
  PZEM-004T measures AC mains electricity.
  Do not work on mains wiring yourself.
  Use a qualified person for the AC-side installation.
*/

#include <WiFi.h>
#include <WebServer.h>
#include <PZEM004Tv30.h>

// =============================
// Wi-Fi SETTINGS
// =============================

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// =============================
// PZEM SERIAL PINS
// =============================

// ESP32 UART2
#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17

HardwareSerial pzemSerial(2);

PZEM004Tv30 pzem(
  pzemSerial,
  PZEM_RX_PIN,
  PZEM_TX_PIN
);

// =============================
// WEB SERVER
// =============================

WebServer server(80);


// =============================
// SENSOR DATA
// =============================

float voltage = 0.0;
float current = 0.0;
float power = 0.0;
float energy = 0.0;
float frequency = 0.0;
float powerFactor = 0.0;


// =============================
// READ PZEM
// =============================

void readEnergyData() {

  voltage = pzem.voltage();
  current = pzem.current();
  power = pzem.power();
  energy = pzem.energy();
  frequency = pzem.frequency();
  powerFactor = pzem.pf();

  Serial.println("-----------------------------");

  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  Serial.print("Current: ");
  Serial.print(current);
  Serial.println(" A");

  Serial.print("Power: ");
  Serial.print(power);
  Serial.println(" W");

  Serial.print("Energy: ");
  Serial.print(energy);
  Serial.println(" kWh");

  Serial.print("Frequency: ");
  Serial.print(frequency);
  Serial.println(" Hz");

  Serial.print("Power Factor: ");
  Serial.println(powerFactor);

  Serial.println("-----------------------------");
}


// =============================
// JSON API
// =============================

void sendEnergyData() {

  readEnergyData();

  String json = "{";

  json += "\"voltage\":";
  json += String(voltage, 2);

  json += ",\"current\":";
  json += String(current, 2);

  json += ",\"power\":";
  json += String(power, 2);

  json += ",\"energy\":";
  json += String(energy, 3);

  json += ",\"frequency\":";
  json += String(frequency, 2);

  json += ",\"powerFactor\":";
  json += String(powerFactor, 2);

  json += "}";

  server.sendHeader(
    "Access-Control-Allow-Origin",
    "*"
  );

  server.send(
    200,
    "application/json",
    json
  );
}


// =============================
// HOME PAGE
// =============================

void handleRoot() {

  String message = "";

  message += "<html>";
  message += "<head>";
  message += "<title>Smart Energy Monitor</title>";
  message += "</head>";

  message += "<body>";

  message += "<h1>Smart Energy Monitor</h1>";

  message += "<p>ESP32 is connected.</p>";

  message += "<p>Open /data to view sensor data.</p>";

  message += "</body>";
  message += "</html>";

  server.send(
    200,
    "text/html",
    message
  );
}


// =============================
// SETUP
// =============================

void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("=============================");
  Serial.println("SMART ENERGY MONITOR");
  Serial.println("=============================");


  // -------------------------
  // PZEM SERIAL
  // -------------------------

  pzemSerial.begin(
    9600,
    SERIAL_8N1,
    PZEM_RX_PIN,
    PZEM_TX_PIN
  );


  // -------------------------
  // WIFI
  // -------------------------

  WiFi.begin(
    WIFI_SSID,
    WIFI_PASSWORD
  );

  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");
  }

  Serial.println();

  Serial.println("Wi-Fi connected!");

  Serial.print("ESP32 IP address: ");

  Serial.println(
    WiFi.localIP()
  );


  // -------------------------
  // WEB SERVER ROUTES
  // -------------------------

  server.on(
    "/",
    handleRoot
  );

  server.on(
    "/data",
    sendEnergyData
  );


  // -------------------------
  // START SERVER
  // -------------------------

  server.begin();

  Serial.println(
    "Web server started."
  );

  Serial.println(
    "Open http://ESP32-IP/data"
  );
}


// =============================
// LOOP
// =============================

void loop() {

  server.handleClient();

  delay(10);
}