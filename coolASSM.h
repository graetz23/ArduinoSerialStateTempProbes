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
#ifndef __ARDUINO_COOLASSM_H__
#define __ARDUINO_COOLASSM_H__

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "./coolASSM_config.h" // the COMMANDs and STATEs ..

#define ASSM_DEBUG                          false
#define ASSM_DEBUG_SHOW_COMMAND             false
#define ASSM_DEBUG_SHOW_COMMAND_INTERNAL    false
#define ASSM_DEBUG_SHOW_STATE               false
#define ASSM_DEBUG_SHOW_STATE_INTERNAL      false
#define ASSM_DEBUG_SHOW_RUNNING_INTERNAL    false
#define ASSM_DEBUG_DISPLAY_SHOW             200
#define ASSM_DEBUG_DISPLAY_BLANK            100

/*!
 * \brief The cool ASSM - the cool arduino serial state machine
 */
class ASSM {

protected:

  uint8_t _command; // current command of cool ASSM

  uint8_t _state; // current state of cool ASSM

  ASSM_HELPER* _helper; // COMMAND and STATE processing helper

public:

  /*!
   * \brief Constructor
   */
  ASSM( void );

  /*!
   * \brief Destructor; virtual to have it called
   */
  virtual ~ASSM( void );

  /*!
   * \brief take this to arduino's setup method; it connects the serial
   * and sends a PING to client
   */
  virtual void setup( );

  /*!
   * \brief display a welcome message for showing interactivity; not necessary
   */
  virtual void welcome( );

  /*!
   * \brief display a ready message for showing interactivity; not necessary
   */
  virtual void ready( );

  /*!
   * \brief take this to arduino's loop method to drive the state machine
   */
  void loop( );

protected:
  /*!
   * \brief cyclic called when coolASSM is in ERROR state - overload method
   */
  virtual uint8_t error( uint8_t command );

  /*!
   * \brief cyclic called when coolASSM is in IDLE state - overload method
   */
  virtual uint8_t idle( uint8_t command );

  /*!
   * \brief cyclic called when coolASSM is in run MODE 1 state - overload method
   */
  virtual uint8_t runMODE1( uint8_t command );

  /*!
   * \brief cyclic called when coolASSM is in run MODE 1 state - overload method
   */
  virtual uint8_t runMODE2( uint8_t command );

  /*!
   * \brief cyclic called when coolASSM is in run MODE 1 state - overload method
   */
  virtual uint8_t runMODE3( uint8_t command );

  /*!
   * \brief cyclic called when coolASSM is in run MODE 1 state - overload method
   */
  virtual uint8_t runMODE4( uint8_t command );

  /*!
   * \brief cyclic called when coolASSM is in run MODE 1 state - overload method
   */
  virtual uint8_t runMODE5( uint8_t command );

  /*!
   * \brief cyclic called when coolASSM is in run MODE 1 state - overload method
   */
  virtual uint8_t runMODE6( uint8_t command );

  /*!
   * \brief cyclic called when coolASSM is in run MODE 1 state - overload method
   */
  virtual uint8_t runMODE7( uint8_t command );

  /*!
   * \brief Returns the HELPER for using it outside cool ASSM ..
   * \return the pointer to the internal, private STATE / COMMAND helper
   */
  ASSM_HELPER* get_ASSM_HELPER( void );

  /*!
   * \brief Read one byte from the serial and cast it to an Order
   * \return the order received
   */
  uint8_t readCommand( );

  /*!
  * \brief Send a state to the CLIENT; pattern: <STATE/>
  * \param The STATE number
   */
  void writeState( uint8_t state );

  /*!
  * \brief Send a state to the CLIENT; pattern: <STATE/>
  * \param The STATE number as some string
   */
  void writeState( String state );

  /*!
   * \brief Send a command to the CLIENT; pattern: <CMD/>
   * \param The COMMAND number
   */
  void writeCommand( uint8_t command );

  /*!
   * \brief Send a command to the CLIENT; pattern: <CMD/>
   * \param The COMMAND as some string
   */
  void writeCommand( String command );

  /*!
   * \brief Send some tag and data to CLIENT
   * \param the bare data .. <TAG>DATA</TAG>
   */
  void writeData( String tag, bool data );

  /*!
   * \brief Send some tag and data to CLIENT
   * \param the bare data .. <TAG>DATA</TAG>
   */
  void writeData( String tag, int data );

  /*!
   * \brief Send some tag and data to CLIENT
   * \param the bare data .. <TAG>DATA</TAG>
   */
  void writeData( String tag, float data, int digits, int precision );

  /*!
   * \brief Send some tag and data to CLIENT
   * \param the bare data .. <TAG>DATA</TAG>
   */
  void writeData( String tag, double data, int digits, int precision );

  /*!
   * \brief Send some tag and data to CLIENT
   * \param the bare data .. <TAG>DATA</TAG>
   */
  void writeData( String tag, String data );

  /*!
   * \brief Display some string including current STATE and COMMAND
   */
  void display( String s );

private: // some stuff that's not so interesting

  /*!
   * \brief Handing the RECEIVED or NEXT COMMAND and CURRENT STATE
   * \param receives a COMMAND and a STATE changes to the NEXT STATE
   * \return the NEXT STATE
   */
  uint8_t process_command( uint8_t command );

  /*!
  * \brief Handing the CURRENT COMMAND and NEXT STATE
   * \param receives a STATE and a COMMAND and MAY change to the NEXT COMMAND
   * \return may return the NEXT COMMAND, INSTEAD of RECEIVED COMMAND
   */
  uint8_t process_state( uint8_t state );

  /*!
   * \brief let LED go HIGH
   */
   void led_on( );

   /*!
    * \brief let LED go LOW
    */
    void led_off( );

  /*!
   * \brief let LED go HIGH -> delay -> LOW -> delay
   */
   void led_blink( int duration );

   /*!
    * \brief let LED blink like a heat beat by certain interval
    */
    void led_heartBeat( int interval );


  /*!
   * \brief Listen the serial and decode the message received
   */

  const char _markerHead = '<';
  const char _markerPref = '/';
  const char _markerFoot = '>';
  // const String _markerCommand = "CMD_"; // deprecated

  /*!
   * \brief converts a char array into an integer
   * \param the cahr array keeping a one or more digit number
   * \return the correspoding integer
   */
  int a2i( const char *s );

}; // class

#endif
