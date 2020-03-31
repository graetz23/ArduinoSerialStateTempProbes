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
#include <Servo.h>
#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>

#include "./coolASSTCP.h" // base class header file

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

ASSTCP::ASSTCP( void ) {
  //_state = ASSM_STATE_IDLE; // initial STATE is IDLE due to not reacting
  //_command = ASSM_CMD_NULL; // set COMMAND to NO (NULL) COMMAND
  //_helper = new ASSM_HELPER( ); // use internal helper ..
  _atcp = new ATCP( );
} // method

ASSTCP::~ASSTCP( void ) {
  delete _atcp;
} // method

// here you can add your code or
// overload the class and next the methods

void ASSTCP::setup( void ) {

  // initialize the lcd for testing ..
  lcd.init();
  lcd.backlight();
  lcd.home( ); // same as lcd.setCursor(0,0);
  lcd.print("setup ..");
  delay(500);
  lcd.clear( ); // clear lcd display
  lcd.home( ); // same as lcd.setCursor(0,0);

  Serial.begin( SERIAL_BAUD ); // set up serial
  delay(10); // 10 ms
} // method

uint8_t ASSTCP::error( uint8_t command ) {

  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE

  // TODO Place your code for ERROR STATE or EXTEND CLASS and OVERLOAD method

  return next_command;

} // method

uint8_t ASSTCP::idle( uint8_t command ) {

  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE

  // TODO Place your code for IDLE STATE or EXTEND CLASS and OVERLOAD method

  double probeA0 = _atcp->readNTCProbe( 0 );
  double tempA0 = _atcp->readNTCProbe_Celsius( 0 );

  lcd.home( ); // same as lcd.setCursor(0,0);

  // double probeA0 = atcp.readNTCProbe( 0 );
  lcd.print("probe A0: ");
  lcd.print( probeA0 ); // TODO read and set tempearture of A0
  lcd.setCursor( 0, 1 ); // same as lcd.setCursor(0,0);
  // double tempA0 = atcp.readNTCProbe_Celsius( 0 );
  lcd.print("temp  A0: ");
  lcd.print( tempA0 ); // TODO read and set tempearture of A1

  String tempA0_str = _helper->d2str( tempA0 );

  writeCommand( "A0" );
  writeData( tempA0_str );
  writeCommand( "/A0" );

  // at the end arduino sends a DONE command
  writeCommand( ASSM_CMD_DONE );


  return next_command;

} // method

uint8_t ASSTCP::running( uint8_t command ) {

  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE

  // TODO Place your code for RUNNING STATE or EXTEND CLASS and OVERLOAD method

  return next_command;

} // method
