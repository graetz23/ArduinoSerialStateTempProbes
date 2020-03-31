/**
 * coolASSM - cool arduino serial state machine
 *
 * Christian
 * graetz23@gmail.com
 * created 20190511
 * version 20200331
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
#define ASSM_CMD_AKNWLDG     4 // ACKNOWLEDGE a received command
#define ASSM_CMD_AKNWLDG_STR "AKNWLDG"
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
#define ASSM_CMD_CONNECT     21 // CONNECT and ready for COMMANDs
#define ASSM_CMD_CONNECT_STR "CONNECT"
#define ASSM_CMD_DISCNCT     22 // DISCONNECT from SERVER
#define ASSM_CMD_DISCNCT_STR "DISCNCT"
// TODO add your own messages here ..
#define ASSM_CMD_EXAMPLE     42
#define ASSM_CMD_EXAMPLE_STR "EXAMPLE"

/*!
 * \brief The cool ASSM STATEs
 */
#define ASSM_STATE_ERROR        0
#define ASSM_STATE_ERROR_STR    "ERROR"
#define ASSM_STATE_IDLE         1
#define ASSM_STATE_IDLE_STR     "IDLE"
#define ASSM_STATE_RUNNING      2
#define ASSM_STATE_RUNNING_STR  "RUNNING"

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

private: // some stuff that's not so interesting

  const char _markerHead = '<';
  const char _markerFoot = '>';

  const String _markerCommand = "CMD_";

  /*!
   * \brief converts a char array into an integer
   * \param the cahr array keeping a one or more digit number
   * \return the correspoding integer
   */
  int a2i( const char* s );

}; // class

#endif
