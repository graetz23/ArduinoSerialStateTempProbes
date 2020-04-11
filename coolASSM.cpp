/**
 * coolASSM - cool arduino serial state machine
 *
 * Christian
 * graetz23@gmail.com
 * created 20190511
 * version 20200404
 *
 * MIT License
 *
 * Copyright (c) 2019-2020 coolASSM Christian (graetz23@gmail.com)
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

#include "./coolASSM.h" // base class header file

ASSM::ASSM( void ) {
  if( ASSM_LED_ACTV ) {
    pinMode( ASSM_LED_PIN, OUTPUT ); // arduino's built-in LED for flashing
  } // if
  _state = ASSM_STATE_IDLNG; // initial STATE is IDLE due to not reacting
  _command = ASSM_CMD_NULL; // set COMMAND to NO (NULL) COMMAND
  _helper = new ASSM_HELPER( ); // use internal helper ..
} // method

ASSM::~ASSM( void ) {
  delete _helper;
} // method

void ASSM::setup( void ) {
  Serial.begin( SERIAL_BAUD ); // set up serial
  delay(10); // 10 ms
} // method

ASSM_HELPER* ASSM::get_ASSM_HELPER( void ) {
  return _helper; // if one needs the helper outside cool ASSM ..
} // method

void ASSM::display( String s ) {
  // String sstate = _helper->state_to_String( _state );
  // const char* cstate = sstate.c_str();
  // String scmmnd = _helper->command_to_String( _command );
  // const char* ccmmnd = scmmnd.c_str();
  // you can drive some display here
  // e.g. an liquid crystal 20x2 lcd
} // method

void ASSM::welcome( ) {
  // print some welcome message to display here
  delay(250); // 500 ms
} // method

void ASSM::ready( ) {
  // print some ready messsafe to display here
  delay(750); // 500 ms
} // method

void ASSM::writeData( String tag, bool data ) {
  String head = _helper->mark_as_Data_starting( tag );
  String foot = _helper->mark_as_Data_stopping( tag );
  String data_str = String(data);
  String send = head + data_str + foot;
  const char* cstr = send.c_str( );
  Serial.write( cstr );
} // method

void ASSM::writeData( String tag, int data ) {
  String head = _helper->mark_as_Data_starting( tag );
  String foot = _helper->mark_as_Data_stopping( tag );
  String data_str = String(data);
  String send = head + data_str + foot;
  const char* cstr = send.c_str( );
  Serial.write( cstr );
} // method

void ASSM::writeData( String tag, float data, int digits, int precision ) {
  String head = _helper->mark_as_Data_starting( tag );
  String foot = _helper->mark_as_Data_stopping( tag );
  String data_str = _helper->toStr( data, digits, precision );
  String send = head + data_str + foot;
  const char* cstr = send.c_str( );
  Serial.write( cstr );
} // method

void ASSM::writeData( String tag, double data, int digits, int precision ) {
  String head = _helper->mark_as_Data_starting( tag );
  String foot = _helper->mark_as_Data_stopping( tag );
  String data_str = _helper->toStr( data, digits, precision );
  String send = head + data_str + foot;
  const char* cstr = send.c_str( );
  Serial.write( cstr );
} // method

void ASSM::writeData( String tag, String data ) {
  String head = _helper->mark_as_Data_starting( tag );
  String foot = _helper->mark_as_Data_stopping( tag );
  String send = head + data + foot;
  const char* cstr = send.c_str( );
  Serial.write( cstr );
} // method

void ASSM::writeCommand( uint8_t command ) {
  writeCommand( _helper->command_to_String( command ) );
} // method

void ASSM::writeCommand( String command ) {
  String str = _helper->mark_as_State_or_Command( command );
  const char* cstr = str.c_str( );
  Serial.write( cstr );
} // method

void ASSM::writeState( uint8_t state ) {
 writeState( _helper->state_to_String( state ) );
} // method

void ASSM::writeState( String state ) {
  String str = _helper->mark_as_State_or_Command( state );
  const char* cstr = str.c_str( );
  Serial.write( cstr );
} // method

// read the received State from serial
uint8_t ASSM::readCommand( ) {
  const byte numChars = 32;
  char receivedChars[numChars]; // an array to store the received data
  static byte ndx = 0;
  static boolean isReceiving = false;
  char rc;
  uint8_t cmd = ASSM_CMD_NULL;
  if( Serial.available( ) > 0 ) {
    while( Serial.available( ) > 0 ) {
      rc = Serial.read( );
      if( isReceiving == true ) {
        if( rc != _markerFoot ) {
            receivedChars[ ndx ] = rc;
            ndx++;
            if( ndx >= numChars ) {
                ndx = numChars - 1;
            } // if
        } else {
            receivedChars[ ndx ] = '\0'; // terminate the string
            isReceiving = false;
            ndx = 0;
        } // if
      } // if
      else if( rc == _markerHead )
      { // found a beginning
         isReceiving = true;
      } // if
    } // loop
    cmd = a2i( receivedChars );
  } // if
  return cmd;
} // method

/**
 * running the recevied command
 */
void ASSM::loop( ) {

  uint8_t command = readCommand( ); // read and filter a command from serial
  uint8_t command_internal = command;

  bool isProcessingInternally = true;
  while( isProcessingInternally ) {

    uint8_t state = process_command( command_internal );
    command_internal = process_state( state );

    if( command_internal == ASSM_CMD_NULL ) {
      isProcessingInternally = false;
    } // if

  } // loop

} // method

uint8_t ASSM::process_command( uint8_t command ) {

  _command = command; // copy to internal member variable

  uint8_t state = ASSM_STATE_ERROR; // initial state is always last state

  switch( _command ) {
    // process the COMMAND SNA - State Not Available; we are in ERROR state ..
    case ASSM_CMD_SNA:
      state = ASSM_STATE_ERROR; // keep ERROR state as fundamental STATE .. ;-)
      break;
    // process the COMMAND PING
    case ASSM_CMD_PING:
      if( _state == ASSM_STATE_ERROR ) {
        state = ASSM_STATE_IDLNG;
      } else {
        state = _state; // keep same STATE ..
      }// if
      writeCommand( ASSM_CMD_PONG ); // ALWAYS answer a PING with a PONG
    break;
    // process the COMMAND PONG
    case ASSM_CMD_PONG:
      if( _state == ASSM_STATE_ERROR ) {
        state = ASSM_STATE_IDLNG;
      } else {
        state = _state; // keep same STATE ..
      }// if
      writeCommand( ASSM_CMD_PING ); // ALWAYS answer a PONG with a PING
    break;
    // process the COMMAND ACKNOWLEDGE; not really something to do here ..
    case ASSM_CMD_AKNW:
      state = _state;
    break;
    // process the COMMAND RUN; now some working task should be processed
    case ASSM_CMD_RUN:
      if( _state == ASSM_STATE_MODE1 ) {
        state = _state; // keep same STATE ..
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else if( _state == ASSM_STATE_MODE2 ) {
        state = _state; // keep same STATE ..
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else if( _state == ASSM_STATE_MODE3 ) {
        state = _state; // keep same STATE ..
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else if( _state == ASSM_STATE_MODE4 ) {
        state = _state; // keep same STATE ..
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else if( _state == ASSM_STATE_MODE5 ) {
        state = _state; // keep same STATE ..
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else if( _state == ASSM_STATE_MODE6 ) {
        state = _state; // keep same STATE ..
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else if( _state == ASSM_STATE_MODE7 ) {
        state = _state; // keep same STATE ..
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else {
        state = _state; // keep same STATE ..
      } // if
    break;
    // process the COMMAND STOP; leave some working task and return to IDLE
    case ASSM_CMD_STOP:
      if( _state == ASSM_STATE_MODE1 ) {
        state = ASSM_STATE_IDLNG;
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else if( _state == ASSM_STATE_MODE2 ) {
        state = ASSM_STATE_IDLNG;
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else if( _state == ASSM_STATE_MODE3 ) {
        state = ASSM_STATE_IDLNG;
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else if( _state == ASSM_STATE_MODE4 ) {
        state = ASSM_STATE_IDLNG;
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else if( _state == ASSM_STATE_MODE5 ) {
        state = ASSM_STATE_IDLNG;
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else if( _state == ASSM_STATE_MODE6 ) {
        state = ASSM_STATE_IDLNG;
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else if( _state == ASSM_STATE_MODE7 ) {
        state = ASSM_STATE_IDLNG;
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else {
        state = _state; // keep same STATE ..
      }// if
    break;
    // process the COMMAND WAIT; may be stop some processing task ..
    case ASSM_CMD_WAIT:
      state = _state; // keep same STATE ..
    break;
    // process the COMMAND EVNT; may be do something while processing ..
    case ASSM_CMD_EVNT:
      state = _state; // keep same STATE ..
      writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
    break;
    // process the COMMAND STAT
    case ASSM_CMD_STAT:
      state = _state; // keep same STATE ..
      writeState( _state ); // ALWAYS tell about the current STATE
    break;

    // process the COMMAND run MODEs
    // process COMMAND run MODE 1
        case ASSM_CMD_RMD1:
      if(_state != ASSM_STATE_ERROR ) {
        state = ASSM_STATE_MODE1; // only if we are not in ERROR ..
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else {
        state = _state; // keep same STATE ..
      }// if
    break;

    // process COMMAND run MODE 2
    case ASSM_CMD_RMD2:
      if(_state != ASSM_STATE_ERROR ) {
        state = ASSM_STATE_MODE2; // only if we are not in ERROR ..
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else {
        state = _state; // keep same STATE ..
      }// if
    break;

    // process COMMAND run MODE 3
    case ASSM_CMD_RMD3:
      if(_state != ASSM_STATE_ERROR ) {
        state = ASSM_STATE_MODE3; // only if we are not in ERROR ..
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else {
        state = _state; // keep same STATE ..
      }// if
    break;

    // process COMMAND run MODE 4
    case ASSM_CMD_RMD4:
      if(_state != ASSM_STATE_ERROR ) {
        state = ASSM_STATE_MODE4; // only if we are not in ERROR ..
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else {
        state = _state; // keep same STATE ..
      }// if
    break;

    // process COMMAND run MODE 5
    case ASSM_CMD_RMD5:
      if(_state != ASSM_STATE_ERROR ) {
        state = ASSM_STATE_MODE5; // only if we are not in ERROR ..
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else {
        state = _state; // keep same STATE ..
      }// if
    break;

    // process COMMAND run MODE 6
    case ASSM_CMD_RMD6:
      if(_state != ASSM_STATE_ERROR ) {
        state = ASSM_STATE_MODE6; // only if we are not in ERROR ..
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else {
        state = _state; // keep same STATE ..
      }// if
    break;

    // process COMMAND run MODE 7
    case ASSM_CMD_RMD7:
      if(_state != ASSM_STATE_ERROR ) {
        state = ASSM_STATE_MODE7; // only if we are not in ERROR ..
        writeCommand( ASSM_CMD_AKNW ); // answer with a ACKNOWLEDGE
      } else {
        state = _state; // keep same STATE ..
      }// if
    break;

    // process the COMMAND CNCT
    case ASSM_CMD_CNCT: // obviously useless
      // may be one want to CONNECT and DISCONNECT while IDLE / RUNNING ..
      state = _state; // keep same STATE ..
    break;
    // process the COMMAND DCNT
    case ASSM_CMD_DCNT: // obviously useless
      // may be one want to CONNECT and DISCONNECT while IDLE / RUNNING ..
      state = _state; // keep same STATE ..
    break;

    // process no (NULL) or an unknown COMMAND
    default: // NULL command
      state = _state;  // keep same STATE ..
    break;

  } // switch

  return state; // hand back next STATE by processed COMMAND
} // method

uint8_t ASSM::process_state( uint8_t state ) {

  _state = state; // copy to internal member variable

  uint8_t next_command = ASSM_CMD_NULL; // return no command

  switch( _state ) {

    case ASSM_STATE_ERROR: // SNA - State Not Available
      next_command = ASSM_CMD_NULL;
      if( ASSM_LED_ACTV ) {
        led_on( ); // switch STATE indicator permanently on ..
      } // if
      next_command = error( _command );
      break;

    case ASSM_STATE_IDLNG: // IDLE around, and around, and arountthe world
      next_command = ASSM_CMD_NULL;
      if( ASSM_LED_ACTV ) {
        led_heartBeat( 100 ); // 60 bpm heartbeat; 200 blink + 800 wait
      } // if
      next_command = idle( _command );
    break;

    case ASSM_STATE_MODE1: // run MODE 1
      next_command = ASSM_CMD_NULL;
      if( ASSM_LED_ACTV ) {
        led_blink( 1 ); // let flash 20 milliseonds as load indicator ..
      } // if
      next_command = runMODE1( _command );
    break;

    case ASSM_STATE_MODE2: // run MODE 2
      next_command = ASSM_CMD_NULL;
      if( ASSM_LED_ACTV ) {
        led_blink( 1 ); // let flash 20 milliseonds as load indicator ..
      } // if
      next_command = runMODE2( _command );
    break;

    case ASSM_STATE_MODE3: // run MODE 3
      next_command = ASSM_CMD_NULL;
      if( ASSM_LED_ACTV ) {
        led_blink( 1 ); // let flash 20 milliseonds as load indicator ..
      } // if
      next_command = runMODE3( _command );
    break;

    case ASSM_STATE_MODE4: // run MODE 4
      next_command = ASSM_CMD_NULL;
      if( ASSM_LED_ACTV ) {
        led_blink( 1 ); // let flash 20 milliseonds as load indicator ..
      } // if
      next_command = runMODE4( _command );
    break;

    case ASSM_STATE_MODE5: // run MODE 5
      next_command = ASSM_CMD_NULL;
      if( ASSM_LED_ACTV ) {
        led_blink( 1 ); // let flash 20 milliseonds as load indicator ..
      } // if
      next_command = runMODE5( _command );
    break;

    case ASSM_STATE_MODE6: // run MODE 6
      next_command = ASSM_CMD_NULL;
      if( ASSM_LED_ACTV ) {
        led_blink( 1 ); // let flash 20 milliseonds as load indicator ..
      } // if
      next_command = runMODE6( _command );
    break;

    case ASSM_STATE_MODE7: // run MODE 7
      next_command = ASSM_CMD_NULL;
      if( ASSM_LED_ACTV ) {
        led_blink( 1 ); // let flash 20 milliseonds as load indicator ..
      } // if
      next_command = runMODE7( _command );
    break;

    default:
      next_command = ASSM_CMD_NULL;
    break;

  } // switch

  return next_command;
} // method

void ASSM::led_on(  ) {
  digitalWrite( ASSM_LED_PIN, HIGH ); // sets the digital pin LED on
} // method

void ASSM::led_off(  ) {
  digitalWrite( ASSM_LED_PIN, LOW ); // sets the digital pin LED on
} // method

void ASSM::led_blink( int duration ) {
  if( duration < 1 ) {
    duration = 1;
  } // if
  led_on( ); // sets the digital pin LED on
  delay( duration );            // waits for a moment in ECU time
  led_off( );  // sets the digital pin LED off
  delay( duration );            // waits for a moment in ECU time
} // method

void ASSM::led_heartBeat( int interval ) {
  if( interval < 100 ) {
    interval = 100; // arduino on steroids; 200 ms equals 300 bpm ..
  } // if
  led_blink( 25 );
  delay( 50 );
  led_blink( 25 );
  delay( interval );
} // method

int ASSM::a2i(const char *s)
{
  int sign=1;
  if(*s == '-'){
    sign = -1;
    s++;
  } // if
  int num=0;
  while(*s){
    num=((*s)-'0')+num*10;
    s++;
  } // loop
  return num*sign;
} // method

// here you can add your code or
// overload the class and next the methods

uint8_t ASSM::error( uint8_t command ) {
  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE
  // TODO Place your code for ERROR STATE or EXTEND CLASS and OVERLOAD method
  return next_command;
} // method

uint8_t ASSM::idle( uint8_t command ) {
  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE
  // TODO Place your code for IDLE STATE or EXTEND CLASS and OVERLOAD method
  return next_command;
} // method

uint8_t ASSM::runMODE1( uint8_t command ) {
  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE
  // TODO your code for run MODE 1 STATE or EXTEND CLASS and OVERLOAD method
  return next_command;
} // method

uint8_t ASSM::runMODE2( uint8_t command ) {
  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE
  // TODO your code for run MODE 2 STATE or EXTEND CLASS and OVERLOAD method
  return next_command;
} // method

uint8_t ASSM::runMODE3( uint8_t command ) {
  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE
  // TODO your code for run MODE 3 STATE or EXTEND CLASS and OVERLOAD method
  return next_command;
} // method

uint8_t ASSM::runMODE4( uint8_t command ) {
  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE
  // TODO your code for run MODE 4 STATE or EXTEND CLASS and OVERLOAD method
  return next_command;
} // method

uint8_t ASSM::runMODE5( uint8_t command ) {
  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE
  // TODO your code for run MODE 5 STATE or EXTEND CLASS and OVERLOAD method
  return next_command;
} // method

uint8_t ASSM::runMODE6( uint8_t command ) {
  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE
  // TODO your code for run MODE 6 STATE or EXTEND CLASS and OVERLOAD method
  return next_command;
} // method

uint8_t ASSM::runMODE7( uint8_t command ) {
  uint8_t next_command = ASSM_CMD_NULL; // in general KEEP this STATE
  // TODO Replace code for eun MODE7 or EXTEND CLASS and OVERLOAD method
  /// some easy example for a fake sensor / data Processing
  if( ASSM_DEBUG_SHOW_RUNNING_INTERNAL ) {
    display( "RNMD 7 ->" );
    delay(ASSM_DEBUG_DISPLAY_SHOW);
    display( _helper->state_to_String( _state ) );
    delay(ASSM_DEBUG_DISPLAY_SHOW);
    display( _helper->command_to_String( _command ) );
    delay(ASSM_DEBUG_DISPLAY_SHOW);
    display( "" );
    delay(ASSM_DEBUG_DISPLAY_BLANK);
  } // if

  // if arduino is in runnig state and client sends
  // EVNT as command, arduino responds with three
  // WAIT commands to simulate a sensor requesting
  if( command == ASSM_CMD_EVNT ) {
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
    writeData( "DATA", "1.2;3.4;5.6" );
    // at the end arduino sends a DONE command
    writeCommand( ASSM_CMD_DONE );
  } // if

  return next_command;
} // method
