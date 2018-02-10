#include <Arduino.h>


#include <Utility.h>
#include <math.h>
#include "flowVals.h"

#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

/*
void plotLine(int x0, int y0, float angle, int length);
float getTotalWind(float WSy, float WSx);
float getWindAngle(float WSy, float WSx);
*/


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

	Serial.begin(9600);

	set();
	tft.fillRect(0, 0, tft.width() , tft.height(), 0);

}


float getTotalWind(float WSy, float WSx) {

	return sqrt(sq(WSx) + sq(WSy));
}

float getWindAngle(float WSy, float WSx) {

	return atan(WSy / WSx);

}
int x0 = 64;
int y0 = 80;

int c = 0;
float lastSpeed = 0;

float raw0;
float raw1;

float Xwind;
float Ywind;

float totalWind;
float angle;

void loop() {
	digitalWrite(LED_BUILTIN, HIGH);

	/*
	raw0 = analogRead(A0);
	raw1 = analogRead(A2);
	*/
	raw0 = 2.4;
	raw1 = 2.6;
	Ywind = interpolate(flows95, (raw1 / 1023.0) * 5.0);
	Xwind = interpolate(flows94, (raw0 / 1023.0) * 5.0);
	totalWind = getTotalWind(Ywind, Xwind);
	angle = getWindAngle(Ywind, Xwind );


	if (Xwind >= 2 || Ywind >= 2) {
		tft.setRotation(2);
		tft.setCursor(64, 10);
		tft.setTextColor(0);
		tft.print(lastSpeed);
		tft.setCursor(64, 10);

		tft.setTextColor(0xFFFFF);
		int windKMh = totalWind * 3.6;
		lastSpeed = windKMh;
		tft.print(String(windKMh));
		//	tft.print(" km/h");



		tft.drawLine(x0, y0, lastX1, lastY1, 0x0);


		plotLine (x0, y0, angle, 50);
		Serial.println(angle * (180 / PI));
		Serial.println("!!!!!!!!!!!!!!!!!!!!!");

		Serial.println(Xwind);
		Serial.println(Ywind);
		Serial.println("!!!!!!!!!!!!!!!!!!!!!");
		lastAngle = angle;
		delay(100);

	}

}
