/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#include <Utility.h>
#include <math.h>
#include "flowVals.h"

#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
//Beginning of Auto generated function prototypes by Atmel Studio
void plotLine(int x0, int y0, float angle, int length);
float getTotalWind(float WSy, float WSx);
float getWindAngle(float WSy, float WSx);
//End of Auto generated function prototypes by Atmel Studio



#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

int lastX1;
int lastY1;
float lastAngle;

void plotLine(int x0, int y0, float angle, int length = 50) {
  if (angle == 0) return;

  int x1 = x0 + (length * cos(angle));
  int y1 = y0 + (length * sin(angle));
  lastX1 = x1;
  lastY1 = y1;
  tft.drawLine(x0, y0, x1, y1, 0xF81F);
}

void setup() {
  tft.initR(INITR_BLACKTAB);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(2, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(2, HIGH);


  set();
  Serial.begin(9600);
  tft.fillRect(0, 0, tft.width() , tft.height(), 0x0001);

}


float getTotalWind(float WSy, float WSx) {

  return sqrt(sq(WSx) + sq(WSy));
}

float getWindAngle(float WSy, float WSx) {

  if (WSy == 0)
    WSy = 1;  if (WSy == 0)
    WSy = 1;
  if (WSx == 0)
    WSx = 1;
  if (WSx == 0)
    WSx = 1;

  //// Serial.println("------");
  //// Serial.println(WSy);
  //  // Serial.println(WSx);
  return atan(WSy / WSx);

}
int x0 = 64;
int y0 = 80;

int c = 0;
float lastSpeed = 0;


void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)

  float raw0 = analogRead(A0);
  float raw1 = analogRead(A2);

  //  plotLine(x0, y0, PI/2);
  float Ywind = interpolate(flows95, (raw1 / 1023.0) * 5.0);
  float Xwind = interpolate(flows94, (raw0 / 1023.0) * 5.0);
  float totalWind = getTotalWind(Ywind, Xwind);


  // Serial.println("Xwind:");
  // Serial.println(Xwind);
  // Serial.println("Ywind");
  // Serial.println(Ywind);
  // Serial.println("totalwind:");
  //   Serial.println(totalWind);
  if (totalWind >= 1) {
    tft.setRotation(2);
    tft.setCursor(64, 10);
    tft.setTextColor(0);
    tft.print(lastSpeed);
    tft.setCursor(64, 10);

    tft.setTextColor(0xFFFFF);
    int windKMh = totalWind * 3.6;
    tft.print(String(windKMh));
    tft.print(" km/h");
    lastSpeed = windKMh;

    raw0 = analogRead(A0);
    raw1 = analogRead(A2);

    Serial.println(raw0 / 1023.0 * 5);
    Serial.println(raw1 / 1023.0 * 5);
    Serial.println("--------");

    float angle = getWindAngle(interpolate(flows95, (raw1 / 1023.0) * 5), interpolate(flows94, (raw0 / 1023.0) * 5) ) + 3 * (PI / 2);


    Xwind = interpolate(flows95, (raw1 / 1023.0) * 5);
    Ywind = interpolate(flows94, (raw0 / 1023.0) * 5);
    totalWind = getTotalWind(Ywind, Xwind);


    tft.drawLine(x0, y0, lastX1, lastY1, 0x0);
    tft.drawLine(x0, y0, lastX1, lastY1 + 1, 0x0);
    tft.drawLine(x0, y0, lastX1, lastY1 - 1  , 0x0);

    plotLine (x0, y0, angle, 50);
    Serial.println(angle * (180 / PI));
    Serial.println("-----------");
    lastAngle = angle;

    delay(100);

  }

}
