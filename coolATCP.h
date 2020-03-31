/**
 * coolATCP - cool arduino cable temperature probe (coolATCP)
 *
 * Christian
 * graetz23@gmail.com
 * created 20191222
 * version 20200331
 *
 * MIT License
 *
 * Copyright (c) 2019-2020 coolATCP Christian (graetz23@gmail.com)
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
#ifndef __ARDUINO_coolATCP_H__
#define __ARDUINO_coolATCP_H__

#include <Arduino.h>

#define ATCP_DEBUG true;

#define ATCP_PIN_PROBE_0 A0 // TODO let this be an array
#define ATCP_PIN_PROBE_0_ID 0 // TODO let this be an array
#define ATCP_PIN_PROBE_1 A1 // TODO let this be an array
#define ATCP_PIN_PROBE_1_ID 1 // TODO let this be an array
#define ATCP_PIN_PROBE_2 A2 // TODO let this be an array
#define ATCP_PIN_PROBE_2_ID 2 // TODO let this be an array
#define ATCP_PIN_PROBE_3 A3 // TODO let this be an array
#define ATCP_PIN_PROBE_3_ID 3 // TODO let this be an array
#define ATCP_PIN_PROBE_4 A4 // TODO let this be an array
#define ATCP_PIN_PROBE_4_ID 4 // TODO let this be an array
#define ATCP_PIN_PROBE_5 A0 // TODO let this be an array
#define ATCP_PIN_PROBE_5_ID 5 // TODO let this be an array

/**
 * The cool ATCP - cool arduino cable temperature probe
 */
class ATCP {

private:

  double _cnst_resistance_probe; // the increments of the analog input

  double _cnst_resolution; // the increments of the analog input

  double _val_analog; // the analog value

  double _val_resistor; // the resistor value

  double _val_celsius; // the calculated degree celsius

  double _val_kelvin; // the calculated kelvin

public:

  /*!
   * \brief Constructor used for 10 k Ohm and an analog resolution of 1024.
   */
  ATCP( void );

  /*!
   * \brief Destructor
   */
  virtual ~ATCP( void );

  /*!
   * \brief Call this to set your base conditions
   */
  virtual void setup( void );

  /*!
   * \brief call this to update the measurement and internal calculations
   */
  virtual void loop( void );

  /*!
   * \brief call this to read the analog value of a NTC probe of certain ID;
   * e.g. id = 0 => input A0 on arduino.
   */
   double readNTCProbe( int id );

   /*!
    * \brief call this to read the resistor value of a NTC probe of certain ID.
    */
   double readNTCProbe_resistor( int id );

   /*!
    * \brief call this to read the kelvin value of a NTC probe of certain ID.
    */
   double readNTCProbe_kelvin( int id );

   /*!
    * \brief call this to read the temperature value in degree celsius  of a
    * NTC probe of certain ID.
    */
   double readNTCProbe_Celsius( int id );

  /*!
   * \brief calculates the resistor value in Ohm from the analog value
   * \param needs the analog value
   * \return the resistor value
   */
  double analog_to_Resistor( double val_analog );

  /*!
   * \brief calculates the kelvin from the analog value
   * \param needs the analog value
   * \return the kelvin
   */
  double analog_to_Kelvin( double val_analog );

  /*!
   * \brief calculates the degree celsius from the kelvin
   * \param needs the kelvin
   * \return the degree celsius
   */
  double kelvin_to_Celsius( double val_kelvin );

  /*!
   * \brief Getter for the analog value
   * \return analog value
   */
  double get_Analog( void );

  /*!
   * \brief Getter for the resistor
   * \return resistor
   */
  double get_Resistor( void );

  /*!
   * \brief Getter for the kelvin
   * \return kelvin
   */
  double get_Kelvin( void );

  /*!
   * \brief Getter for the degree celsius
   * \return degree celsius
   */
  double get_Celsius( void );

  /*!
   * \brief Getter for the analog value as string
   * \return analog value as char string
   */
  char* get_Analog_as_cString( void );

  /*!
   * \brief Getter for the resistor value in Ohm as string
   * \return the resistor value in Ohm as char string
   */
  char* get_Resistor_as_cString( void );

  /*!
   * \brief Getter for the kelvin as string
   * \return kelvin as char string
   */
  char* get_Kelvin_as_cString( void );

  /*!
   * \brief Getter for the degree celsius as string
   * \return degree celsius as char string
   */
  char* get_Celsius_as_cString( void );

}; // class

#endif
