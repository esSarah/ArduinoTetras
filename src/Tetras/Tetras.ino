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

int orientations[4] = {94,62, 118, 60 };
// form the tetris blocks
byte blocks[5][4][4] = 
{
  {
    {
      B0010,
      B0010,
      B0010,
      B0010,
    },
    {
      B0000,
      B0000,
      B1111,
      B0000,
    },
    {
      B0100,
      B0100,
      B0100,
      B0100,
    },
    {
      B0000,
      B1111,
      B0000,
      B0000,
    },
  },
  {
    {
      B0110,
      B0100,
      B0100,
      B0000,
    },
    {
      B0000,
      B0111,
      B0001,
      B0000,
    },
    {
      B0000,
      B0010,
      B0010,
      B0110,
    },
    {
      B0000,
      B1000,
      B1110,
      B0000,
    },
  },
  {
    {
      B0110,
      B0010,
      B0010,
      B0000,
    },
    {
      B0000,
      B0001,
      B0111,
      B0000,
    },
    {
      B0000,
      B0100,
      B0100,
      B0110,
    },
    {
      B0000,
      B1110,
      B1000,
      B0000,
    },
  },
  {
    {
      B0100,
      B0110,
      B0010,
      B0000,
    },
    {
      B0000,
      B0110,
      B0011,
      B0000,
    },
    {
      B0000,
      B0100,
      B0110,
      B0010,
    },
    {
      B0000,
      B1100,
      B0110,
      B0000,
    },
  },
  {
    {
      B0000,
      B0110,
      B0110,
      B0000,
    },
    {
      B0000,
      B0110,
      B0110,
      B0000,
    },
    {
      B0000,
      B0110,
      B0110,
      B0000,
    },
    {
      B0000,
      B0110,
      B0110,
      B0000,
    },
  }
};
byte additionalchars[5][8] = 
{
  {
    B01100,
    B01100,
    B01100,
    B01100,
    B01100,
    B01100,
    B01100,
    B01100,
  },
  {
    B00000,
    B01111,
    B01111,
    B01100,
    B01100,
    B01100,
    B01100,
    B00000,
  },
  {
    B00000,
    B11110,
    B11110,
    B00110,
    B00110,
    B00110,
    B00110,
    B00000,
  },
  {
    B00000,
    B11000,
    B11000,
    B11110,
    B11110,
    B00110,
    B00110,
    B00000,
  },
  {
    B00000,
    B00000,
    B11110,
    B11110,
    B11110,
    B11110,
    B00000,
    B00000,
  }
};

byte wallMatrix[8]
{
    B0000000,
    B0000000,
    B0000000,
    B0000000,
    B0000000,
    B0000000,
    B0000000,
    B0000000,
};

byte LedMatrix[8]
{
    B0000000,
    B0000000,
    B0000000,
    B0000000,
    B0000000,
    B0000000,
    B0000000,
    B0000000,
};

int Position[8]
{
   1,
   2,
   4,
   8,
  16,
  32,
  64,
  128
};

static void testPicture()
{
  paintPoint(0,0);
  paintPoint(0,2);
  paintPoint(0,4);
  paintPoint(0,6);
  paintPoint(1,1);
  paintPoint(1,3);
  paintPoint(1,5);
  paintPoint(2,0);
  paintPoint(2,2);
  paintPoint(2,4);
  paintPoint(3,1);
  paintPoint(3,3);
  paintPoint(4,0);
  paintPoint(4,2);
  paintPoint(5,1);
  paintPoint(6,0);
  
  printLEDs();
}

static void paintPoint(int x, int y)
{
  if(x>=0&&x<8)
  {
    x=7-x;
    if(y>=0&&y<8)
    {
      y=7-y;
      LedMatrix[x] = LedMatrix[x]|Position[y];
    }
  }
}

static void printLEDs()
{
  for(int i=0; i < 8; i++)
  {
    lc.setRow(0,i,LedMatrix[i]);
    LedMatrix[i]= B0000000;
  }
}

void setup() 
{
  // Initialize each module

  // LCD
  // add chars (no, I won't make a four loop for 5 lines)
  
  lcd.createChar(1, additionalchars[0]);
  lcd.createChar(2, additionalchars[1]);
  lcd.createChar(3, additionalchars[2]);
  lcd.createChar(4, additionalchars[3]);
  lcd.createChar(5, additionalchars[4]);

  lcd.begin(16, 2);  // size

  lcd.setCursor(0, 0);
  lcd.write(byte(1));
  lcd.setCursor(2, 0);
  lcd.write(byte(2));
  lcd.setCursor(4, 0);
  lcd.write(byte(3));
  lcd.setCursor(6, 0);
  lcd.write(byte(4));
  lcd.setCursor(8, 0);
  lcd.write(byte(5));
  
  lcd.setCursor(0, 1);

  lcd.print("               ");       
// Joystick
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);

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

  // only for debugging
  //  Serial.begin( 9600);

}

void loop() 
{

  // example write to LEDs
  int x=0;
  int y=0;
  // blocktype
  for(int i=3; i < 5; i++)
  {
    //orientation
    for(int j=0; j < 4; j++)
    {
      //line
      for(int k=0; k < 4; k++)
      {
        //pixel
        for(int l=0; l < 4; l++)
        {
          if((blocks[i][j][k]&Position[l])!=0)
          {
            paintPoint(x+k,y+l);
          };
        };
      }

      // once per orientation 
      printLEDs();
      //testPicture();
      lcd.setCursor(0, 1);
      lcd.write(byte(i+1));
      lcd.setCursor(2, 1);
      lcd.write(orientations[j]);       
      delay(1000);

    }
  }
}


