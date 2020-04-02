/**
 * cool arduino serial state temperature cable probe (coolASSTCP)
 *
 * Christian
 * graetz23@gmail.com
 * created 20200331
 * version 20200402
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
#ifndef __ARDUINO_COOLASSTCP_H__
#define __ARDUINO_COOLASSTCP_H__

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "./coolASSM.h" // the COMMANDs and STATEs ..
#include "./coolATCP.h" // cool arduino temperature cable probes

/*!
 * \brief The cool ASSM - the cool arduino serial state machine
 */
class ASSTCP : public ASSM {

public:

  /*!
   * \brief Constructor
   */
  ASSTCP( void );

  /*!
   * \brief Destructor; virtual to have it called
   */
  virtual ~ASSTCP( void );

  /*!
   * \brief Call this to set your base conditions
   */
  void setup( void );

private:

  /*!
   * \brief does all the probe reading and sending to serial job
   */
  uint8_t processing( uint8_t command );

  /*!
   * \brief cyclic called when coolASSM is in ERROR state - overloaded method
   */
  virtual uint8_t error( uint8_t command );

  /*!
   * \brief cyclic called when coolASSM is in IDLE state - overloaded method
   */
  virtual uint8_t idle( uint8_t command );

  /*!
   * \brief cyclic called when coolASSM is in RUNNING state - overloaded method
   */
  virtual uint8_t runMODE1( uint8_t command );

  ATCP* _atcp; // cable temperature probe pointer

  // some extra for visualization via I2C 20x2 LCD

  /*!
   * \brief display probe value and celsius by given ID
   * on some I2C 20x2 LCD display ..
   */
  void displayProbe( int id );

  int _mementoID;

  /*!
   * \brief display error message while in error state
   * on some I2C 20x2 LCD display ..
   */
  void displayError( ); // while error

}; // class

#endif
