/**
 * Arduino serial state temperature cable probe (ASSTCP)
 *
 * Christian
 * graetz23@gmail.com
 * created 20200331
 * version 20200402
 *
 * MIT License
 *
 * Copyright (c) 2020 ASSTCP Christian (graetz23@gmail.com)
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

#include "./ASSTCP.h" // base class header file

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

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
  lcd.print("coolASSTCP");
  lcd.setCursor(0,1);
  lcd.print(".. setup");
  delay(500);
  lcd.clear( ); // clear lcd display
  lcd.home( ); // same as lcd.setCursor(0,0);

  Serial.begin( SERIAL_BAUD ); // set up serial
  delay(10); // 10 ms
} // method

void ASSTCP::displayProbe( int id ) {
  // double probeAx = _atcp->readNTCProbe( id );
  double tempAx = _atcp->readNTCProbe_Celsius( id );
  String id_str = "";
  if ( id == 0 ) {
    id_str = "A0";
  } else if( id == 1 ) {
    id_str = "A1";
  } else if( id == 2 ) {
    id_str = "A2";
  } else if( id == 3 ) {
    id_str = "A3";
  } else if( id == 4 ) {
    id_str = "A4";
  } else if( id == 5 ) {
    id_str = "A5";
  } else {
    id_str = "Ax";
  } // if
  lcd.home( ); // same as lcd.setCursor(0,0);
  lcd.print("ASSTCP - ");
  lcd.print(_helper->state_to_String( _state ));
  lcd.print("    "); // blanking some
  lcd.setCursor( 0, 1 ); // set cursor second line
  lcd.print("temp ");
  lcd.print(id_str);
  lcd.print(" ");
  lcd.print( tempAx );
  lcd.print("     "); // blanking some
} // method

void ASSTCP::displayError( ) {
  lcd.clear( ); // same as lcd.setCursor(0,0);
  lcd.home( ); // same as lcd.setCursor(0,0);
  lcd.print("error state!");
  lcd.print("    "); // blanking some
  lcd.setCursor( 0, 1 ); // set cursor second line
  double probeA0 = _atcp->readNTCProbe( 0 );
  lcd.print("try A0 ");
  lcd.print( probeA0 );
  lcd.print("    "); // blanking some
} // method

uint8_t ASSTCP::processing( uint8_t command ) {

  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE

  double temp = 0.0;

  if( command == 70 ) {
    _mementoID = 0; // only used for repeating last request on display
    temp = _atcp->readNTCProbe_Celsius( _mementoID );
    writeData_starting( "A0" );
    writeData( temp );
    writeData_stopping( "A0" );
  } else if( command == 71 ) {
    _mementoID = 1; // only used for repeating last request on display
    temp = _atcp->readNTCProbe_Celsius( _mementoID );
    writeData_starting( "A1" );
    writeData( temp );
    writeData_stopping( "A1" );
  } else if( command == 72 ) {
    _mementoID = 2; // only used for repeating last request on display
    temp = _atcp->readNTCProbe_Celsius( _mementoID );
    temp = _atcp->readNTCProbe_Celsius( 2 );
    writeData_starting( "A2" );
    writeData( temp );
    writeData_stopping( "A2" );
  } else if( command == 73 ) {
    _mementoID = 3; // only used for repeating last request on display
    temp = _atcp->readNTCProbe_Celsius( _mementoID );
    writeData_starting( "A3" );
    writeData( temp );
    writeData_stopping( "A3" );
  } else if( command == 74 ) {
    _mementoID = 4; // only used for repeating last request on display
    temp = _atcp->readNTCProbe_Celsius( _mementoID );
    writeData_starting( "A4" );
    writeData( temp );
    writeData_stopping( "A4" );
  } else if( command == 75 ) {
    _mementoID = 5; // only used for repeating last request on display
    temp = _atcp->readNTCProbe_Celsius( _mementoID );
    writeData_starting( "A5" );
    writeData( temp );
    writeData_stopping( "A5" );
  } else {
    // do nothing ..
  } // if

  displayProbe( _mementoID ); // while running

  return next_command; // do not self command - NULL

} // method


uint8_t ASSTCP::error( uint8_t command ) {

  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE

  displayError( ); // while error show error and try A0
  delay( 250 );

  return next_command;

} // method

uint8_t ASSTCP::idle( uint8_t command ) {

  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE

  _mementoID = 0; // A0; mmeber only used for having nice displaying ..

  displayProbe( _mementoID ); // while idle

  // processing( command ); // let arduino in IDLE also respond to sensor request

  return next_command;

} // method

uint8_t ASSTCP::runMODE1( uint8_t command ) {

  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE

  processing( command ); // does all the job of using coolATCP ..

  // if( command != _command )
  //   lcd.clear( ); // quick help on changing states ..

  return next_command;

} // method
