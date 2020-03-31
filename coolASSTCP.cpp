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

#include "./coolASSTCP.h" // base class header file

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

  return next_command;

} // method

uint8_t ASSTCP::running( uint8_t command ) {

  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE

  // TODO Place your code for RUNNING STATE or EXTEND CLASS and OVERLOAD method

  /// some easy example for a fake sensor / data Processing
  if( ASSM_DEBUG_SHOW_RUNNING_INTERNAL ) {
    display( "RUNNING ->" );
    delay(ASSM_DEBUG_DISPLAY_SHOW);
    display( _helper->state_to_String( _state ) );
    delay(ASSM_DEBUG_DISPLAY_SHOW);
    display( _helper->command_to_String( _command ) );
    delay(ASSM_DEBUG_DISPLAY_SHOW);
    display( "" );
    delay(ASSM_DEBUG_DISPLAY_BLANK);
  } // if

  // if arduino is in runnig state and client sends
  // EVENT as command, arduino responds with three
  // WAIT commands to simulate a sensor requesting
  if( command == ASSM_CMD_EVENT ) {

    int cnt = 0;
    while( cnt < 3 ) {
      // write a <WAIT> command
      writeCommand( ASSM_CMD_WAIT );
      cnt++;
      delay( 1000 ); // wait a second
    } // loop

    // afterwards arduino responds with an UNIQUE
    // command, writes the data back to the client by:
    // <DATA>1;2;3;4;5;6;7;8;9;0</DATA>
    writeCommand( "DATA" );
    writeData( "1;2;3;4;5;6;7;8;9;0" );
    writeCommand( "/DATA" );

    // at the end arduino sends a DONE command
    writeCommand( ASSM_CMD_DONE );

  } // if

  return next_command;

} // method
