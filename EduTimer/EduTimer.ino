/*
* Audio-Visual Reaction Timer
* July 2017, James Wu
*/

#include <LiquidCrystal.h>
#include <Wire.h>

#define DEBUGGING 0
#define DEBOUNCE_TIME 80

#define BUTTON_RESPONSE 2
#define BUTTON_MODE 4
#define BUTTON_RESET 5

#define BUZZER 3
#define BACKLIGHT 6

bool stimmode 0;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup()
{
	lcd.begin(20, 4);
	lcd.print("Test Your Reaction!");
	lcd.setCursor(0, 1);
	lcd.print("Mode: Light");


	#if DEBUGGING
		Serial.begin(9600);
		while(!Serial);
	#endif

	pinMode(BUTTON_MODE, INPUT_PULLUP);
	pinMode(BUTTON_RESPONSE, INPUT_PULLUP);
	pinMode(BUTTON_RESET, INPUT_PULLUP);

	pinMode(BACKLIGHT, OUTPUT);

	analogWrite(BACKLIGHT, 70);
}

void loop()
{
	
}

void dispmessage(stimmode)
{
	
}