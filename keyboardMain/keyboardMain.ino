#include <LiquidCrystal.h>
#include <Keyboard.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const int buttonZeroPin = 0;   // D0
const int buttonOnePin  = 1;   // D1

char bits[9] = "________";
int bitIndex = 0;

bool lastReadingZero = HIGH;
bool lastReadingOne  = HIGH;


unsigned long lastChangeTimeZero = 0;
unsigned long lastChangeTimeOne  = 0;

const unsigned long debounceDelay = 40;

void setup() {
  pinMode(buttonZeroPin, INPUT_PULLUP);
  pinMode(buttonOnePin, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Binary Input");

  updateDisplay();

  Keyboard.begin();
}

void loop() {
  handleButton(buttonZeroPin, '0',
               lastReadingZero, stableStateZero, lastChangeTimeZero);

  handleButton(buttonOnePin, '1',
               lastReadingOne, stableStateOne, lastChangeTimeOne);
}

void handleButton(int pin, char bitChar,
                  bool &lastReading,
                  bool &stableState,
                  unsigned long &lastChangeTime) {
  bool reading = digitalRead(pin);

  if (reading != lastReading) {
    lastChangeTime = millis();
    lastReading = reading;
  }

  if ((millis() - lastChangeTime) > debounceDelay) {
    if (reading != stableState) {
      stableState = reading;

      if (stableState == LOW) {
        appendBit(bitChar);
      }
    }
  }
}

void appendBit(char bitChar) {
  if (bitIndex < 8) {
    bits[bitIndex] = bitChar;
    bitIndex++;
    updateDisplay();
  }

  if (bitIndex == 8) {
    processByte();
    delay(1000);
    resetBits();
    updateDisplay();
  }
}

void processByte() {
  byte value = 0;

  for (int i = 0; i < 8; i++) {
    value <<= 1;
    if (bits[i] == '1') {
      value |= 1;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Byte: ");
  lcd.print(value);

  lcd.setCursor(0, 1);

  if (value == 8) {
    lcd.print("Backspace");
    Keyboard.write(KEY_BACKSPACE);
  } else if (value == 13) {
    lcd.print("Return");
    Keyboard.write(KEY_RETURN);
  } else if (value == 32) {
    lcd.print("Space");
    Keyboard.write(' ');
  } else if (value >= 33 && value <= 126) {
    char outChar = (char)value;
    lcd.print("Char: ");
    lcd.print(outChar);
    Keyboard.write(outChar);
  } else {
    lcd.print("Ignored");
  }
}

void resetBits() {
  for (int i = 0; i < 8; i++) {
    bits[i] = '_';
  }
  bits[8] = '\0';
  bitIndex = 0;
}

void updateDisplay() {
  lcd.setCursor(0, 0);
  lcd.print("Binary Input    ");

  lcd.setCursor(0, 1);
  lcd.print(bits);
  lcd.print("        ");
}