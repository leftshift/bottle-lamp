#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>

#define NUM_LEDS 12

#define DATA_PIN D5
#define CLOCK_PIN 1


CRGB leds[NUM_LEDS];

CRGB user_color;

int brightness = 20;
int frames_per_second = 60;

void (*animation)();

ESP8266WebServer server(80);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println();

  Serial.println(WiFi.softAP("bottle", "bottle123") ? "softAP started" : "softAP failed");
  Serial.println(MDNS.begin("bottle", WiFi.softAPIP()) ? "MDNS started" : "MDNS failed");
  serverSetup();
  Serial.println(WiFi.softAPIP());

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  FastLED.setBrightness(brightness);
  animation = &black;
  user_color = 0x000000;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  server.handleClient();

  animation();
  FastLED.show();
  FastLED.delay(1000/frames_per_second);
}
