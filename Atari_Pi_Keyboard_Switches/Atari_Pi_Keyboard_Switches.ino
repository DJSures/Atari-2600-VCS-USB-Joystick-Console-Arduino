#include "Keyboard.h"

// ***********************************************************************
// **                                                                   **
// ** Keyboard USB HID for Teensy or Pro Micro                          **
// ** By DJ Sures (Synthiam.com) (c)2019                                **
// **                                                                   **
// ** Updated: November 15, 2019                                        **
// **                                                                   **
// ***********************************************************************

// uncomment to use for serial terminal debugging rather than usb hid device
// this is so you can see the ascii values to verify
//#define SERIAL_DEBUG

#define SWITCH_COLOR 2
#define SWITCH_DIFFICULTY_1 3
#define SWITCH_DIFFICULTY_2 4
#define SWITCH_SELECT 5
#define SWITCH_START 6

bool _last_color = true;
bool _last_difficulty_1 = true;
bool _last_difficulty_2 = true;
bool _last_select = true;
bool _last_start = true;

void setup() {

#ifdef SERIAL_DEBUG
  Serial.begin(9600);
#else
  Keyboard.begin();
#endif

  pinMode(SWITCH_COLOR, INPUT_PULLUP);
  pinMode(SWITCH_DIFFICULTY_1, INPUT_PULLUP);
  pinMode(SWITCH_DIFFICULTY_2, INPUT_PULLUP);
  pinMode(SWITCH_SELECT, INPUT_PULLUP);
  pinMode(SWITCH_START, INPUT_PULLUP);
}

void loop() {

#ifdef SERIAL_DEBUG

  Serial.print(!digitalRead(SWITCH_COLOR));
  Serial.print(!digitalRead(SWITCH_DIFFICULTY_1));
  Serial.print(!digitalRead(SWITCH_DIFFICULTY_2));
  Serial.print(!digitalRead(SWITCH_SELECT));
  Serial.print(!digitalRead(SWITCH_START));
  Serial.print("\r\n");

#else

  bool color = digitalRead(SWITCH_COLOR);
  bool difficulty_1 = digitalRead(SWITCH_DIFFICULTY_1);
  bool difficulty_2 = digitalRead(SWITCH_DIFFICULTY_2);
  bool select = digitalRead(SWITCH_SELECT);
  bool start = digitalRead(SWITCH_START);

  if (color != _last_color) {

    if (color)
      Keyboard.write('1'); // left thumb
    else
      Keyboard.write('2'); // right thumb

    _last_color = color;
  }

  if (difficulty_1 != _last_difficulty_1) {

    if (difficulty_1)
      Keyboard.write('3'); // left trigger
    else
      Keyboard.write('4'); // left shoulder

    _last_difficulty_1 = difficulty_1;
  }

  if (difficulty_2 != _last_difficulty_2) {

    if (difficulty_2)
      Keyboard.write('5'); // right trigger
    else
      Keyboard.write('6'); // right shoulder

    _last_difficulty_2 = difficulty_2;
  }

  if (select != _last_select) {

    if (!select)
      Keyboard.press('7'); // select
    else
      Keyboard.release('7');

    _last_select = select;
  }

  if (start != _last_start) {

    if (!start)
      Keyboard.press('8'); // start
    else
      Keyboard.release('8');

    _last_start = start;
  }

#endif

  delay(50);
}
