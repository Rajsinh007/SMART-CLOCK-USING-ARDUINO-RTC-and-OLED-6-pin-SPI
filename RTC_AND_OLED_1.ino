/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using SPI to communicate
 4 or 5 pins are required to interface.

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <DS3231.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
/////////////////ALARM////////////////////////////////////////////////////////
int setHour = 18; // Set hours to wake (military time)
int setMin = 36; // Set minute to wake
int setHour1 = 18; // Set hours to wake (military time)
int setMin1 = 37; // Set minute to wake
/////////////////////////////////////////////////////////////////////////////////

DS3231  rtc(SDA, SCL);
Time  t;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9 //SDA
#define OLED_CLK   10 //SCL
#define OLED_DC    11 //DC
#define OLED_CS    12 //CS if u have seven pins OLED SPI
#define OLED_RESET 13 //RES
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/* Comment out above, uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  &SPI, OLED_DC, OLED_RESET, OLED_CS);
*/

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

void setup() {
  Serial.begin(9600);
  rtc.begin();
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever

    pinMode(8, OUTPUT);
  }


  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.setCursor(0,0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
 display.println("WELCOME!!!");
 
    
    display.display();
  delay(4000);


    
  /*if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }*/
}

void loop() {
  t = rtc.getTime();
  
  // Send date over serial connection
  Serial.print("Today is the ");
  Serial.print(t.date, DEC);
  Serial.print(". day of ");
  Serial.print(rtc.getMonthStr());
  Serial.print(" in the year ");
  Serial.print(t.year, DEC);
  Serial.println(".");
  
  // Send Day-of-Week and time
  Serial.print("It is the ");
  Serial.print(t.dow, DEC);
  Serial.print(". day of the week (counting monday as the 1th), and it has passed ");
  Serial.print(t.hour, DEC);
  Serial.print(" hour(s), ");
  Serial.print(t.min, DEC);
  Serial.print(" minute(s) and ");
  Serial.print(t.sec, DEC);
  Serial.println(" second(s) since midnight.");
   
display.clearDisplay();

    display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);/*
  display.println("Hacks Clock!");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println("not a bomb");*/
  
display.setTextColor(WHITE);

 display.setTextSize(2);
 display.print(t.hour, DEC);
    display.print(':');
    display.print(t.min, DEC);
    display.print(':');
    display.print(t.sec, DEC);
    display.println(); 
  
  
  
  display.setTextColor(WHITE);
  display.print(t.date, DEC);
    display.print(':');
    display.print(rtc.getMonthStr());
    display.print(':');
    display.print(t.year, DEC);
    display.println();

    display.print("DOW:");
    display.print(t.dow, DEC);
    display.println();
    
 display.display();
  delay(1000);
Alarm();
}
void Alarm(){
  if (t.hour == setHour && t.hour == setHour1 && t.min <= setMin1 && t.min >= setMin)
{ // Check if it's time to wake up!
  
  digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
}
 else{
  digitalWrite(8, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
     }
}
