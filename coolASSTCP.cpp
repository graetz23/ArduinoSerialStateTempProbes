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

void ASSTCP::displayProbe( int id ) {
  double probeA0 = _atcp->readNTCProbe( id );
  double tempA0 = _atcp->readNTCProbe_Celsius( id );
  lcd.home( ); // same as lcd.setCursor(0,0);
  lcd.print("probe A0: ");
  lcd.print( probeA0 );
  lcd.setCursor( 0, 1 ); // set cursor second line
  lcd.print("temp  A0: ");
  lcd.print( tempA0 );
} // method

void ASSTCP::displayError( ) {
  lcd.clear( ); // same as lcd.setCursor(0,0);
  lcd.home( ); // same as lcd.setCursor(0,0);
  lcd.print("error state!");
  lcd.setCursor( 0, 1 ); // set cursor second line
  double probeA0 = _atcp->readNTCProbe( 0 );
  lcd.print("try A0: ");
  lcd.print( probeA0 );
} // method

uint8_t ASSTCP::error( uint8_t command ) {

  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE

  displayError( ); // while error show error and try A0
  delay( 100 );

  return next_command;

} // method

uint8_t ASSTCP::idle( uint8_t command ) {

  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE

  // TODO Place your code for IDLE STATE or EXTEND CLASS and OVERLOAD method

  displayProbe( 0 ); // while idle

  return next_command;

} // method

uint8_t ASSTCP::running( uint8_t command ) {

  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE

  // TODO Place your code for RUNNING STATE or EXTEND CLASS and OVERLOAD method

  double temp = 0.0;

  if( command == 70 ) {
    displayProbe( 0 ); // while running
    temp = _atcp->readNTCProbe_Celsius( 0 );
    writeCommand( "A0" );
    writeData( temp );
    writeCommand( "/A0" );
  } else if( command == 71 ) {
    displayProbe( 1 ); // while running
    temp = _atcp->readNTCProbe_Celsius( 1 );
    writeCommand( "A1" );
    writeData( temp );
    writeCommand( "/A1" );
  } else if( command == 72 ) {
    displayProbe( 2 ); // while running
    temp = _atcp->readNTCProbe_Celsius( 2 );
    writeCommand( "A2" );
    writeData( temp );
    writeCommand( "/A2" );
  } else if( command == 73 ) {
    displayProbe( 3 ); // while running
    temp = _atcp->readNTCProbe_Celsius( 3 );
    writeCommand( "A3" );
    writeData( temp );
    writeCommand( "/A3" );
  } else if( command == 74 ) {
    displayProbe( 4 ); // while running
    temp = _atcp->readNTCProbe_Celsius( 4 );
    writeCommand( "A4" );
    writeData( temp );
    writeCommand( "/A4" );
  } else if( command == 75 ) {
    displayProbe( 5 ); // while running
    temp = _atcp->readNTCProbe_Celsius( 5 );
    writeCommand( "A5" );
    writeData( temp );
    writeCommand( "/A5" );
  } else {
  } // if

  return next_command;

} // method
