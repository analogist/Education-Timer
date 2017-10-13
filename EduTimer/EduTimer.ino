/*
* Audio-Visual Reaction Timer
* July 2017, James Wu
*/

#include <LiquidCrystal.h>
#include <Wire.h>

#define SERIAL_DEBUG 0
#define DEBOUNCE_TIME 150

#define BUTTON_GO 0
#define BUTTON_RESET 1
#define BUTTON_MODE 2

#define BUZZER 3
#define GOLIGHT 5
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
  pinMode(BUZZER, OUTPUT);
  pinMode(GOLIGHT, OUTPUT);
  pinMode(BUTTON_GO_LIGHT, OUTPUT);
	analogWrite(BACKLIGHT, 200);
}

void loop()
{
  delay(DEBOUNCE_TIME);
  
  if(! digitalRead(BUTTON_GO))
    runtask(taskmode);
  if(! digitalRead(BUTTON_MODE)) {
    if(taskmode >= 2)
      taskmode = 0;
    else
      taskmode++;
  }
}

void runtask(int run_mode)
{
  lcd.setCursor(0, 2);
  delay(500);
  lcd.print("Get ready for ");
  
  switch(taskmode) {
    case MODE_LIGHT:
      lcd.print("light!");
      break;
  }
  
  go_waittime = random(1500, 6500);
  delay(go_waittime);

  switch(taskmode) {
    case MODE_LIGHT:
      analogWrite(BACKLIGHT, 150); // GO!
      break;
  }
  
  go_signaltime = millis();
  while(digitalRead(BUTTON_GO));
  go_respondtime = millis() - go_signaltime;
  analogWrite(BACKLIGHT, 200);
  dispmessage(run_mode, go_respondtime);
}

void dispmessage(int run_mode, unsigned long go_respondtime)
{
  lcd.setCursor(0, 3);
  lcd.print(String (float (go_respondtime)/1000, 3));
  lcd.print(" sec");
}
