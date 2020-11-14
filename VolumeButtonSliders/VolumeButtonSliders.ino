#include <Keyboard.h>
#include <Key.h>
#include <Keypad.h>

const int NUM_SLIDERS = 4;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3};
int analogSliderVals[NUM_SLIDERS];

const byte ROWS = 3;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', '#', '!', '@'}
};

byte rowPins[ROWS] = {8, 7, 6};
byte columnPins[COLS] = {5, 4, 3, 2};

Keypad kpd = Keypad(makeKeymap(keys), rowPins, columnPins, ROWS, COLS);

void setup() 
{
  for(int i = 0; i < NUM_SLIDERS; i++)
  {
    pinMode(analogInputs[i], INPUT);
  }
  Serial.begin(9600);
  kpd.setHoldTime(500);
  Keyboard.begin();
}

void loop() 
{
  updateSliderValues();
  sendSliderValues();
  delay(10);
  /*
  char key = kpd.getKey();
  if (key != NO_KEY)
  {
    Keyboard.print(key);
  }
  */
}

void updateSliderValues()
{
  for(int i = 0; i < NUM_SLIDERS; i++)
  {
    analogSliderVals[i] = analogRead(analogInputs[i]);
  }
}

void sendSliderValues()
{
  String builtString = String("");

  for(int i = 0; i < NUM_SLIDERS; i++)
  {
    builtString += String((int)analogSliderVals[i]);

    if(i < NUM_SLIDERS - 1)
    {
      builtString += String("|");
    }
  }

  Serial.println(builtString);
}

void printSliderValues() 
{
  for (int i = 0; i < NUM_SLIDERS; i++) 
  {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderVals[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) 
    {
      Serial.write(" | ");
    } 
    else 
    {
      Serial.write("\n");
    }
  }
}
