/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/Users/shoubhitsstuff/Desktop/Lab11/src/Lab11.ino"
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

#include "Particle.h"
void setup();
void loop();
#line 5 "/Users/shoubhitsstuff/Desktop/Lab11/src/Lab11.ino"
#include "oled-wing-adafruit.h"
#include "LIS3DH.h"

const unsigned long currentPrintSample = 100;

LIS3DHSPI accel(SPI, D3, WKP);
OledWingAdafruit display;

unsigned long lastPrintSample = 0;

void setup()
{
  display.setup();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.display();

  Serial.begin(9600);

  LIS3DHConfig config;
  config.setAccelMode(LIS3DH::RATE_100_HZ);

  bool setupSuccess = accel.setup(config);
  Serial.printlnf("setupSuccess=%d", setupSuccess);
}

void loop()
{
  display.loop();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  if (millis() - lastPrintSample >= currentPrintSample)
  {
    lastPrintSample = millis();

    LIS3DHSample sample;
    if (accel.getSample(sample))
    {
      Serial.printlnf("%d,%d,%d", sample.x, sample.y, sample.z);
      display.println("X, Y, Z:");
      display.printf("%d,%d,%d", sample.x, sample.y, sample.z);
      display.display();
    }
    else
    {
      Serial.println("no sample");
    }
  }
}