/**
 * cool arduino serial state temperature cable probe (coolASSTCP)
 *
 * Christian
 * graetz23@gmail.com
 * created 20200331
 * version 20200331
 *
 * MIT License
 *
 * Copyright (c) 2020 coolASSTCP Christian (graetz23@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>

#include "./coolASSM.h" // cool arduino serial state machine
#include "./coolATCP.h" // cool arduino temperature cable probes

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup( ) {
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.home( ); // same as lcd.setCursor(0,0);
  lcd.print("setup ..");
  delay(500);
  lcd.clear( ); // clear lcd display
  lcd.home( ); // same as lcd.setCursor(0,0);
  Serial.begin(9600);
} // method

void loop( ) {
  lcd.home( ); // same as lcd.setCursor(0,0);
  lcd.print("temp A0: ");
  lcd.print( 12.34 ); // TODO read and set tempearture of A0
  lcd.setCursor( 0, 1 ); // same as lcd.setCursor(0,0);
  lcd.print("temp A1: ");
  lcd.print( 56.78 ); // TODO read and set tempearture of A1
  delay( 100 ); // 10 ms
} // method
