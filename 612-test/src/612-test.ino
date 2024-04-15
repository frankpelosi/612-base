/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "../lib/neopixel/src/neopixel.h"

#define PIXEL_COUNT 12
#define PIXEL_PIN D0
#define PIXEL_TYPE WS2812

// int LED = D0;
int sensorPin = A0;

Adafruit_NeoPixel ring(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup(){
  // pinMode(LED,OUTPUT);
  pinMode(sensorPin, INPUT);
  ring.begin();
  for (int i=1; i < ring.numPixels(); i++){
    ring.setPixelColor(i, 0, 255, 0);
    ring.setBrightness(80);
  }
  ring.show();

  Serial.begin(9600);
  Particle.function("colorName",setNPColor);
}

void loop() {
  int reading = analogRead(sensorPin);

  Serial.print("Obstruction level is ");
  Serial.println(reading);
  delay(1000);

  if (reading < 300) {
   setNPColor("red");
  } else {
    setNPColor("green");
  }
}


int setNPColor(String colorName) {
//The setPixelColor function expects a uint8_t...it's just a number that is between 0-255 (2^8)
  uint8_t red=0;
  uint8_t green=0;
  uint8_t blue=0;
  if(colorName == "red") {
    red=255;
    green=0;
    blue=0;
  } else if (colorName == "green") {
    red=0;
    green=255;
    blue=0;
  // } else {
  //   red=0;
  //   green=0;
  //   blue=0; 
  }
  for(int i=0; i < ring.numPixels(); i++) { //loop through every LED in the neopixel
    ring.setPixelColor(i, red, green, blue); //set the color of the LED in position i
    ring.setBrightness(80); //adjust the brightness between 1-255. 0=off, 1=lowest, 255=highest
  }
  ring.show(); //send the colors to the NeoPixel hardware
  return 0;
}