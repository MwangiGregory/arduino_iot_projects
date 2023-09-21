/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL2WQ5gWfQh"
#define BLYNK_TEMPLATE_NAME "Water Level Monitoring Template"
#define BLYNK_AUTH_TOKEN "6nVgSN5jHG0J5KPj9AhaAyLxBDNFJjED"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Novatech";
char pass[] = "Nova@Tech";

#include <NewPing.h>

#define TRIGGER_PIN  D6
#define ECHO_PIN     D5
#define MAX_DISTANCE 300

#define PUMP_PIN D7

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

BlynkTimer timer;

unsigned long int prevMillis = 0;
unsigned int prevWaterLevel = MAX_DISTANCE;

unsigned int manualMode = 0;

int getDistance();
void myTimerEvent();

// Manual mode
BLYNK_WRITE(V0)
{
  manualMode = param.asInt();
}

// Turn pump on/off in manual mode
BLYNK_WRITE(V2)
{
  int pumpState = param.asInt();
  digitalWrite(PUMP_PIN, pumpState);
}

void setup() {
  Serial.begin(115200);

  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, HIGH);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  Blynk.run();
  timer.run();
  
  unsigned long int currentMillis = millis();

  if (manualMode == false && currentMillis - prevMillis > 10000UL) {
    bool on = false;
    while (getDistance() > 30) {
      if (on == false) {
        Blynk.virtualWrite(V3, "ON");
      }
      Serial.print(getDistance());
      Serial.println(" ==> Pump on");
      digitalWrite(PUMP_PIN, LOW);
      delay(500);
    }
    Blynk.virtualWrite(V3, "OFF");
    prevMillis = millis();
  }
  
  if (manualMode == false) {
    digitalWrite(PUMP_PIN, HIGH);
  }

  delay(200);
  Serial.print("Water level: ");
  Serial.print(getDistance());
  Serial.println("cm");
}

void myTimerEvent()
{
  int waterLevel = getDistance();
  waterLevel = map(waterLevel, 0, 150, 100, 0);
  Blynk.virtualWrite(V1, waterLevel);
  // Blynk.virtualWrite(V1, waterLevel);
}

int getDistance() {
  // maybe should return previous water level
  int waterLevel = sonar.ping_cm();

  if (waterLevel <= 0) {
    return prevWaterLevel;
  }

  prevWaterLevel = waterLevel;
  return waterLevel;
}