/*
 Weight scale using HX711 board and ATMEGA328-U @8Mhz internal clock
 displayed using a 16*2 LCD display
 By: Rishin patra
 Date: July 29th, 2020


 Arduino pin 
 2 -> HX711 CLK
 3 -> DAT
 5V -> VCC
 GND -> GND

 The HX711 board can be powered from 3.3v only

 For 16*2 LCD display
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 10
 * LCD D5 pin to digital pin 9
 * LCD D6 pin to digital pin 8
 * LCD D7 pin to digital pin 7
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VDD pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

*/

#include "HX711.h"
#include <LiquidCrystal.h>
#define calibration_factor -46750.0 //This value is obtained using a Calibration sketch with a known weight

#define DOUT  3
#define CLK  2

HX711 scale;
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); //This value is obtained using a Calibration sketch with a known weight
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
}

void loop() {
  float weight=0.0;
  lcd.setCursor(1, 0);
  weight=scale.get_units(3);
  lcd.clear();
  if(weight<0)//If the weight is less than 0.0 don't show 
    lcd.print(0.00, 2); //scale.get_units() returns a float
  else
    lcd.print(weight, 2); //scale.get_units() returns a float
  lcd.print(" kg"); 
  delay(50);
}
