#include <LiquidCrystal.h>
#include "LedControl.h"

// Pins LCD
LiquidCrystal lcd(33, 31, 29, 27, 25, 23);
// Pins LED
LedControl lc=LedControl(35,39,37,1);
// Pins Joystick

const int SW_pin = 41; // digital pin connected to switch output
const int X_pin = 14; // analog pin connected to X output
const int Y_pin = 15; // analog pin connected to Y output

// delays for led display
unsigned long delaytime1=500;
unsigned long delaytime2=50;

// form the tetris blocks
byte additionalchars[5][8] = 
{
  {
    B00100,
    B01110,
    B00100,
    B01110,
    B00100,
    B01110,
    B00100,
    B01110,
  },
  {
    B00000,
    B01010,
    B11111,
    B01000,
    B11100,
    B01000,
    B11000,
    B01000,
  },
  {
    B00000,
    B01010,
    B11011,
    B00001,
    B00011,
    B00001,
    B00011,
    B00001,
  },
  {
    B00000,
    B00000,
    B01000,
    B11011,
    B10011,
    B00010,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B01010,
    B11111,
    B01010,
    B11111,
    B01010,
    B00000,
  }
};


void setup() {
  // Initialize each module

  // LCD
  // add chars (no, I won't make a four loop for 5 lines)
  
  lcd.createChar(0, additionalchars[0]);
  lcd.createChar(1, additionalchars[1]);
  lcd.createChar(2, additionalchars[2]);
  lcd.createChar(3, additionalchars[3]);
  lcd.createChar(4, additionalchars[4]);

  lcd.begin(16, 2);  // size

  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  lcd.setCursor(2, 0);
  lcd.write(byte(1));
  lcd.setCursor(4, 0);
  lcd.write(byte(2));
  lcd.setCursor(6, 0);
  lcd.write(byte(3));
  lcd.setCursor(8, 0);
  lcd.write(byte(4));
  
    lcd.setCursor(0, 1);

  lcd.print("Hello");       
// Joystick
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  // Serial.begin(9600);

  // LEDs
    /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);

}

void loop() {

  // example write to LEDs

  
  byte a[5]={B01111110,B10001000,B10001000,B10001000,B01111110};
  byte r[5]={B00010000,B00100000,B00100000,B00010000,B00111110};
  byte d[5]={B11111110,B00010010,B00100010,B00100010,B00011100};
  byte u[5]={B00111110,B00000100,B00000010,B00000010,B00111100};
  byte i[5]={B00000000,B00000010,B10111110,B00100010,B00000000};
  byte n[5]={B00011110,B00100000,B00100000,B00010000,B00111110};
  byte o[5]={B00011100,B00100010,B00100010,B00100010,B00011100};

  // now display them one by one with a small delay
  lc.setRow(0,0,a[0]);
  lc.setRow(0,1,a[1]);
  lc.setRow(0,2,a[2]);
  lc.setRow(0,3,a[3]);
  lc.setRow(0,4,a[4]);
  delay(100);
  

  // example reading from joystick

  /*
  int orIsItBoolKlick = digitalRead(SW_pin);
  int upDownX = analogRead(X_pin);
  int rightLeftY = analogRead(Y_pin);
  */

  // example writing to LCD

  /*
  lcd.setCursor(0, 0);
  lcd.print("Temp         C  ");
  // Display Temperature in F
  //lcd.print("Temp         F  ");
  lcd.setCursor(6, 0);
  // Display Temperature in C
  lcd.print(tempC);
  // Display Temperature in F
  //lcd.print(tempF);
  */
}
