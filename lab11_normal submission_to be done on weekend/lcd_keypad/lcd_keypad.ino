#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(27, 28, 29, 37, 36, 35);
const int RED_led = 30;
const int BLUE_led = 40;

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = { 3, 4, 5, 6 };
byte colPins[COLS] = { 7, 8, 9 };

Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
    pinMode(RED_led, OUTPUT);
    pinMode(BLUE_led, OUTPUT);

    Serial.begin(9600); // Initialize serial communication for debugging

    lcd.begin(16, 2);
    lcd.print("Calculator");
    delay(3000);
    lcd.clear();
}

void loop() {
  calculator();
}

void calculator() {
  String input;
  char customKey;
  lcd.setCursor(0, 0);
  lcd.print("First Number:");
  input = getInput(2);  // Get 2-digit input
  Serial.println("First Number: " + input); // Debugging print

  int firstNumber = input.toInt();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Operation:");
  customKey = getKeypadInput();
  Serial.println("Operation: " + String(customKey)); // Debugging print
  delay(500);

  char operation = customKey;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Second Number:");
  input = getInput(2);  // Get 2-digit input
  Serial.println("Second Number: " + input); // Debugging print

  int secondNumber = input.toInt();
  float result;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Result:");

  if (operation == '*') {
    result = firstNumber * secondNumber;
  } else if (operation == '#') {
    result = (float)firstNumber / (float)secondNumber;
  }

  lcd.setCursor(0, 1);
  lcd.print(result, 2); // Display the result with two decimal places
  Serial.println(result); // Debugging print
  delay(5000);
  lcd.clear();
  setup();
}

String getInput(int maxLength) {
  String input = "";
  char customKey;
  while (input.length() < maxLength) {
    customKey = customKeypad.getKey();
    if (customKey) {
      lcd.setCursor(input.length(), 1);
      lcd.print(customKey);
      input += customKey;
      delay(500);
    }
  }
  return input;
}

char getKeypadInput() {
  char customKey;
  while (true) {
    customKey = customKeypad.getKey();
    if (customKey) {
      return customKey;
    }
  }
}
