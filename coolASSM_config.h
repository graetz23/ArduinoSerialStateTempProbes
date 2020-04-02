/**
 * coolASSM - cool arduino serial state machine
 *
 * Christian
 * graetz23@gmail.com
 * created 20190511
 * version 20200402
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
#ifndef __ARDUINO_COOLASSM_HELPER_H__
#define __ARDUINO_COOLASSM_HELPER_H__

#include <Arduino.h>

// simple STATE and some load indicator that flashes differently in each state;
// if true, the defined PIN (default 13, where all small arduino boards have a
// built in LED) will will light up and flash differently in each STATE. For the
// ERROR STATE it will light permanently, for IDLE STATE it will flash like a
// hearbeat with 60 bpms, and for _all_ run MODE STATEs it will flash for 10
// milliseonds; last let arduino take a general delay of 20 ms in total.
#define ASSM_LED_ACTV       true // false; PIN can be used for electronics
#define ASSM_LED_PIN        13 // define you PIN if you soldered differently

// define the baud rate the arduino should run its serial ..
// #define SERIAL_BAUD                      2400  // Baudrate
// #define SERIAL_BAUD                      4800  // Baudrate
#define SERIAL_BAUD                         9600  // Baudrate
// #define SERIAL_BAUD                      19200  // Baudrate
// #define SERIAL_BAUD                      38400  // Baudrate
// #define SERIAL_BAUD                      57600  // Baudrate
// #define SERIAL_BAUD                      115200  // Baudrate

/**
 * \brief the cool ASSM COMMANDs as IDs and STRINGs
 */
#define ASSM_CMD_NULL        0 // NULL or NO COMMAND; is handled as a CMD
#define ASSM_CMD_NULL_STR    "NULL"
#define ASSM_CMD_SNA         1 // service not available (SNA); go error state
#define ASSM_CMD_SNA_STR     "SNA"
#define ASSM_CMD_PING        2 // send a PING and try get a PONG response
#define ASSM_CMD_PING_STR    "PING"
#define ASSM_CMD_PONG        3 // send a PONG for a PING receive
#define ASSM_CMD_PONG_STR    "PONG"
#define ASSM_CMD_AKNW        4 // ACKNOWLEDGE a received command
#define ASSM_CMD_AKNW_STR    "AKNW"
#define ASSM_CMD_RUN         5 // signal to WAIT to CLIENT or SERVER
#define ASSM_CMD_RUN_STR     "RUN"
#define ASSM_CMD_WAIT        6 // signal to WAIT to CLIENT or SERVER
#define ASSM_CMD_WAIT_STR    "WAIT"
#define ASSM_CMD_EVENT       7 // signal an EVENT to CLIENT or SERVER
#define ASSM_CMD_EVENT_STR   "EVENT"
#define ASSM_CMD_DONE        8 // send a STOP to CLIENT or SERVER
#define ASSM_CMD_DONE_STR    "DONE"
#define ASSM_CMD_STOP        9 // send a STOP to CLIENT or SERVER
#define ASSM_CMD_STOP_STR    "STOP"
#define ASSM_CMD_STATUS      10 // request the STATUS of CLIENT or SERVER
#define ASSM_CMD_STATUS_STR  "STATUS"
// define different RUN MODES ..
#define ASSM_CMD_RNMD1      11 // let arduino do something while in run MODE 1
#define ASSM_CMD_RNMD1_STR  "RNMD1"
#define ASSM_CMD_RNMD2      12 // let arduino do something while in run MODE 2
#define ASSM_CMD_RNMD2_STR  "RNMD2"
#define ASSM_CMD_RNMD3      13 // let arduino do something while in run MODE 3
#define ASSM_CMD_RNMD3_STR  "RNMD3"
#define ASSM_CMD_RNMD4      14 // let arduino do something while in run MODE 4
#define ASSM_CMD_RNMD4_STR  "RNMD4"
#define ASSM_CMD_RNMD5      15 // let arduino do something while in run MODE 5
#define ASSM_CMD_RNMD5_STR  "RNMD5"
#define ASSM_CMD_RNMD6      16 // let arduino do something while in run MODE 6
#define ASSM_CMD_RNMD6_STR  "RNMD6"
#define ASSM_CMD_RNMD7      17 // let arduino do something while in run MODE 7
#define ASSM_CMD_RNMD7_STR  "RNMD7"
// CONNECT and DISCONNECT COMMANDs; not really necessary
#define ASSM_CMD_CNCT     18 // CONNECT and ready for COMMANDs
#define ASSM_CMD_CNCT_STR "CNCT"
#define ASSM_CMD_DCNT     19 // DISCONNECT from SERVER
#define ASSM_CMD_DCNT_STR "DCNT"
// ALL other COMMAND values are application specific and should be defined in
// by extending the this class. In parallel one should overload the methods
 // of error, idle, and run_MODE1, run_MODE2, .. ,run_MODE7.

/*!
 * \brief The cool ASSM STATEs
 */
#define ASSM_STATE_ERROR        0
#define ASSM_STATE_ERROR_STR    "ERROR"
#define ASSM_STATE_IDLE         1
#define ASSM_STATE_IDLE_STR     "IDLE"
// the defined run MODES of arduino to do different jobs
#define ASSM_STATE_MODE1      11
#define ASSM_STATE_MODE1_STR  "MODE1"
#define ASSM_STATE_MODE2      12
#define ASSM_STATE_MODE2_STR  "MODE1"
#define ASSM_STATE_MODE3      13
#define ASSM_STATE_MODE3_STR  "MODE1"
#define ASSM_STATE_MODE4      14
#define ASSM_STATE_MODE4_STR  "MODE1"
#define ASSM_STATE_MODE5      15
#define ASSM_STATE_MODE5_STR  "MODE1"
#define ASSM_STATE_MODE6      16
#define ASSM_STATE_MODE6_STR  "MODE1"
#define ASSM_STATE_MODE7      17
#define ASSM_STATE_MODE7_STR  "MODE7"


/*!
 * a Helper for converting COMMANDs and STATEs from ID to String & vice versa
 */
class ASSM_HELPER {

public:

  /*!
   * \brief Constructor
   */
  ASSM_HELPER( void );

  /*!
   * \brief Destructor
   */
  virtual ~ASSM_HELPER( void );

  /*!
   * \brief read a COMMAND as integer and hand back the matching string
   * \return the COMMAND as string
   */
  String command_to_String( uint8_t Command );

  /*!
   * \brief read a COMMAND as string and hand back the matching integer
   * \return the COMMAND as unsigned integer
   */
  uint8_t command_to_Integer( String Command );

  /*!
   * \brief read a STATE as integer and hand back the matching string
   * \return the STATE as string
   */
  String state_to_String( uint8_t state );

  /*!
   * \brief read a STATE as string and hand back the matching integer
   * \return the STATE as unsigned integer
   */
  uint8_t state_to_Integer( String state );

  /*!
   * \brief receives a string and adds some marking to be a command
   * \return the string as command
   */
  String mark_as_Command( String command );

  /*!
   * \brief converts a double to a String
   * \param the double value
   * \return the correspoding string; e.g. "16.84"
   */
   String d2str( double d );

private: // some stuff that's not so interesting

  const char _markerHead = '<';
  const char _markerFoot = '>';

  const String _markerCommand = "CMD_";

  /*!
   * \brief converts a char array into an integer
   * \param the char array keeping a one or more digit number
   * \return the correspoding integer
   */
  int a2i( const char* s );

}; // class

#endif
