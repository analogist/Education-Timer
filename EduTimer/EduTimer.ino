/*
* Audio-Visual Reaction Timer
* July 2017, James Wu
*/

#include <LiquidCrystal.h>
#include <Wire.h>

#define SERIAL_DEBUG 0
#define DEBOUNCE_TIME 80

#define BUTTON_GO 2
#define BUTTON_MODE 4
#define BUTTON_RESET 5

#define BUZZER 3
#define BACKLIGHT 6

#define MODE_LIGHT 0
#define MODE_BUZZ 1
#define MODE_INTERFERE 2

// Runtime variables
int taskmode = MODE_LIGHT;
bool taskstart = false;
bool gosignal = false;
unsigned long go_waittime = 0;
unsigned long go_signaltime = 0;
unsigned long go_respondtime = 0;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup()
{
	lcd.begin(20, 4);
	lcd.print("Test Your Reaction!");
	lcd.setCursor(0, 1);
	lcd.print("Mode: Light");

	#if SERIAL_DEBUG
		Serial.begin(9600);
		while(!Serial);
	#endif

	pinMode(BUTTON_MODE, INPUT_PULLUP);
	pinMode(BUTTON_GO, INPUT_PULLUP);
	pinMode(BUTTON_RESET, INPUT_PULLUP);
  randomSeed(analogRead(A5));

	pinMode(BACKLIGHT, OUTPUT);
	analogWrite(BACKLIGHT, 200);
}

void loop()
{
  if(! digitalRead(BUTTON_GO))
  {
  delay(DEBOUNCE_TIME);
  
  runtask(taskmode);
  }
}

unsigned long runtask(int run_mode)
{
  lcd.setCursor(0, 2);
  delay(500);
  lcd.print("Get ready for ");
  switch(taskmode) {
    case MODE_LIGHT:
      lcd.print("light!");
      break;
  }
  
  go_waittime = random(1500, 5000);
  delay(go_waittime);
  analogWrite(BACKLIGHT, 100); // GO!
  go_signaltime = millis();
  while(digitalRead(BUTTON_GO));
  go_respondtime = millis() - go_signaltime;
  analogWrite(BACKLIGHT, 200);
  lcd.setCursor(0, 3);
  lcd.print(go_respondtime);
  lcd.print(" millisec");

  return go_respondtime;
}

void dispmessage(int run_mode)
{
	
}
