#include <DFRobotDFPlayerMini.h>
#include <PullupButtonSensor.h>
#include <SoftwareSerial.h>

byte BUTTONS_PINS[] = {2, 3, 4, 5};
const byte BUTTONS_PINS_COUNT = sizeof(BUTTONS_PINS) / sizeof(byte);
PullupButtonSensor buttons[BUTTONS_PINS_COUNT];

byte RELAYS_PINS[] = {6, 7, 8, 9};
const byte RELAYS_PINS_COUNT = sizeof(RELAYS_PINS) / sizeof(byte);

SoftwareSerial SSerial(10, 11);
DFRobotDFPlayerMini audio{};

void ProcessButtonPress(byte number)
{
  static byte state = 0;

  if ((state >> number) & 1)
  {
    audio.play(3);
    digitalWrite(RELAYS_PINS[number], HIGH);
  }
  else
  {
    audio.play(2);
    digitalWrite(RELAYS_PINS[number], LOW);
  }

  state ^= (1 << number);
}

void setup()
{
  for (byte i = 0; i < RELAYS_PINS_COUNT; ++i)
  {
    pinMode(RELAYS_PINS[i], OUTPUT);
    digitalWrite(RELAYS_PINS[i], HIGH);
  }

  for (byte i = 0; i < BUTTONS_PINS_COUNT; ++i)
  {
    buttons[i].SetPin(BUTTONS_PINS[i]);
  }

  if (!audio.begin(Serial1))
  {
    // audio fail
    while (1)
    {
    }
  }

  audio.play(1);
}

void loop()
{
  for (byte i = 0; i < BUTTONS_PINS; ++i)
  {
    if (buttons[i].GetState() == ButtonState::HAS_BEEN_PRESSED)
    {
      ProcessButtonPress(i);
    }
  }
}
