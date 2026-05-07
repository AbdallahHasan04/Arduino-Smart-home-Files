
#include <LiquidCrystal.h>
#include "Keypad.h"
#include <string.h>

LiquidCrystal lcd(13, 12, 3, 2, 1, 0);
//input sensor ffor the temp
const int IST = A0;

const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns
char keys[ROWS][COLS] =
{
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte rowPins[ROWS] = {11, 10, 9, 8};
byte colPins[COLS] = {7, 6, 5, 4};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
  lcd.begin(16, 2);
}
void loop()
{
  lcd.setCursor(0,0);
  lcd.print("1-Timer 2-Temp");
 
  char Key = keypad.getKey();
  int num = Key - '0';
 
 if(num == 1){
  Timer();
  }

  else if(num == 2){
  Templevels();
  }
 
}

 
  void Timer() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Timer in Sec:");

  String input = ""; // To store the user input as a string
  char key;

  // Input phase
  while (true) {
    key = keypad.getKey(); // Get a key press from the keypad
    if (key) { // If a key is pressed == true
      if (key == '#') {
        break;
      } else if (isdigit(key)) { // If the key is a digit
        input += key; // Append the digit to the input string
        lcd.setCursor(0, 1);
        lcd.print(input); // Display the input on the LCD
      }
    }
  }

  // Convert the input string to an integer
  int timerSeconds = input.toInt();

  // Countdown phase
  for (int i = timerSeconds; i >= 0; i--) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time Left:");
    lcd.setCursor(0, 1);
    lcd.print(i);
    lcd.print(" sec");
    delay(1000);
  }

  // when the timer up
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time's Up!");
  delay(2000); // Display "Time's Up!" for 2 seconds
  lcd.clear();
}


void Templevels(){
  lcd.clear();
  
  float temperature_voltage = (analogRead(A0) * 5.0) / 1023.0;
  float Temp_C = temperature_voltage * 100;

  lcd.setCursor(0, 0); 
  //print the word temp:
  lcd.print("temp: ");
  lcd.print(Temp_C); 
   lcd.print(" C ");            

  delay(3000);
  lcd.clear();
}


