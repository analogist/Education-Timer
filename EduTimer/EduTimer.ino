/*
* Audio-Visual Reaction Timer
* July 2017, James Wu
*/

#include <LiquidCrystal.h>
#include <Wire.h>

#define SERIAL_DEBUG 0
#define DEBOUNCE_TIME 120

#define BUTTON_GO 0
#define BUTTON_RESET 1
#define BUTTON_MODE 2

#define BUZZER 3
#define BUTTON_GO_LIGHT 4
#define GOLIGHT 5
#define BUTTON_RESET_LIGHT 6

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
  modemessage(taskmode);

	#if SERIAL_DEBUG
		Serial.begin(9600);
		while(!Serial);
	#endif

	pinMode(BUTTON_MODE, INPUT_PULLUP);
	pinMode(BUTTON_GO, INPUT_PULLUP);
	pinMode(BUTTON_RESET, INPUT_PULLUP);
  randomSeed(analogRead(A5));

  pinMode(BUZZER, OUTPUT);
  pinMode(GOLIGHT, OUTPUT);
  pinMode(BUTTON_GO_LIGHT, OUTPUT);
  pinMode(BUTTON_RESET_LIGHT, OUTPUT);
}

void loop()
{
  delay(DEBOUNCE_TIME);
  
  if(! digitalRead(BUTTON_GO))
    runtask(taskmode);
  if(! digitalRead(BUTTON_MODE)) {
    if(taskmode >= 1)
      taskmode = 0;
    else
      taskmode++;
    modemessage(taskmode);
  }
}

void runtask(int run_mode)
{
  lcd.setCursor(0, 2);
  lcd.print("Get ready!");
  digitalWrite(BUTTON_GO_LIGHT, HIGH);
  
  go_waittime = random(2000, 7000);
  delay(go_waittime);

  switch(run_mode) {
    case MODE_LIGHT:
      digitalWrite(GOLIGHT, HIGH); // GO!
      break;
    case MODE_BUZZ:
      tone(BUZZER, 440);
      break;
  }
  
  go_signaltime = millis();
  while(digitalRead(BUTTON_GO));
  go_respondtime = millis() - go_signaltime;

  switch(run_mode) {
    case MODE_LIGHT:
      digitalWrite(GOLIGHT, LOW);
      break;
    case MODE_BUZZ:
      noTone(BUZZER);
      break;
  }
  digitalWrite(BUTTON_GO_LIGHT, LOW);
  dispmessage(go_respondtime);
  waitforreset();
  modemessage(run_mode);
}

void dispmessage(unsigned long internal_respondtime)
{
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(3, 3);
  lcd.print(String (float (internal_respondtime)/1000, 3));
  lcd.print(" sec");
}

void modemessage(int run_mode)
{
  lcd.clear();
  lcd.print("Test Your Reaction!");
  lcd.setCursor(0, 1);
  switch(run_mode) {
    case MODE_LIGHT:
      lcd.print("Mode: Light");
      break;
    case MODE_BUZZ:
      lcd.print("Mode: Buzz");
      break;
  }
}

void waitforreset()
{
  digitalWrite(BUTTON_RESET_LIGHT, HIGH);
  while( digitalRead(BUTTON_RESET) );
  digitalWrite(BUTTON_RESET_LIGHT, LOW);
}

