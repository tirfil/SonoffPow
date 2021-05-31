
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"

#define REL_PIN 12
#define LED_PIN 15
#define BUTTON 0

#define WIFI_SSID "*****"
#define WIFI_PASS "*****"

#define ID_NAME_1 "sonoff"

#define SERIAL_BAUDRATE 115200
#define PERIOD 1000

fauxmoESP fauxmo;
bool relay;
bool led;
bool button;
unsigned long now;
unsigned long prev_led = 0L;
unsigned long prev_button = 0L;


void WiFiStationConnected(WiFiEvent_t event){

    Serial.println();
 
    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
    
    fauxmo.addDevice(ID_NAME_1);

    fauxmo.setPort(80); // required for gen3 devices
    fauxmo.enable(true);

    fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
        if (strcmp(device_name, ID_NAME_1) == 0)
        {
          if (relay != state) {
            relay = state;
            digitalWrite(REL_PIN,relay);
          }
        }
    });
}

void WiFiStationDisconnected(WiFiEvent_t event){
    Serial.println("Disconnected from WiFi access point");
    Serial.println("Trying to Reconnect");
    WiFi.begin(WIFI_SSID, WIFI_PASS);
}

void setup() {

    relay = false;
    led = true;
    button = true;
    
    Serial.begin(SERIAL_BAUDRATE);

    pinMode(REL_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON, INPUT);

    digitalWrite(REL_PIN,0);
    digitalWrite(LED_PIN,1);

    WiFi.disconnect(true);

    delay(1000);
    
    WiFi.onEvent(WiFiStationConnected, WIFI_EVENT_STAMODE_CONNECTED);
    WiFi.onEvent(WiFiStationDisconnected, WIFI_EVENT_STAMODE_DISCONNECTED);

    // Set WIFI module to STA mode
    WiFi.mode(WIFI_STA); 
    // Connect
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASS);

}

void loop() {
    now = millis();

    // Wifi management
    if (WiFi.status() == WL_CONNECTED) {
      fauxmo.handle();
    }

    // led management
    if ((now - prev_led) >= 2000) {
      prev_led = now;
      if (WiFi.status() == WL_CONNECTED) {
        led = !led;
      } else {
        led = true;
      }
      digitalWrite(LED_PIN,led);
    }

    // Button management
    if ((now - prev_button) >= 100) {
      prev_button = now;
      if (!digitalRead(BUTTON)) {
        if (button) {
          relay = !relay;
          digitalWrite(REL_PIN,relay);
          button = false;
        } 
      } else {
        if (!button) {
          button = true;
        }
      }
    }
}
