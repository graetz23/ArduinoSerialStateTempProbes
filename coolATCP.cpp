/**
 * coolATCP - cool arduino temperature cable probe (coolATCP)
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

#include "./coolATCP.h" // base class header file

ATCP::ATCP( void ) {
  _cnst_resistance_probe = 10000;
  _cnst_resolution = 1023;
} // method

ATCP::ATCP( double resistorValue, double analogResolution ) {
  _cnst_resistance_probe = resistorValue; // TODO set this to your type of probe
  _cnst_resolution = analogResolution; // TODO set this to your kind of analog resolution
} // method

ATCP::~ATCP( void ) {
} // method

void ATCP::setup( void ) {
  _cnst_resistance_probe = 10000; // TODO set this to your type of probe
  _cnst_resolution = 1023; // TODO set this to your kind of analog resolution
} // method

void ATCP::loop( void ) {
  _val_analog = analogRead( ATCP_PIN_PROBE_0 ); // read analog pin
  _val_resistor = analog_to_Resistor( _val_analog ); // calculate resistor
  _val_kelvin = analog_to_Kelvin( _val_analog ); // calculate kelvin
  _val_celsius = kelvin_to_Celsius( _val_kelvin ); // calculate degree celsius
} // method

double ATCP::readNTCProbe( int id ) {
  double analog = analogRead( id ); // read analog value at certain input
  return analog;
} // method

double ATCP::readNTCProbe_resistor( int id ) {
  return analog_to_Resistor( readNTCProbe( id ) ); // calculate resistor
} // method

double ATCP::readNTCProbe_kelvin( int id ) {
  return analog_to_Kelvin( readNTCProbe( id ) ); // calculate kelvin
} // method

double ATCP::readNTCProbe_Celsius( int id ) {
  return kelvin_to_Celsius( analog_to_Kelvin( readNTCProbe( id ) ) );
} // method

double ATCP::analog_to_Resistor( double val_analog ) {
  return _cnst_resistance_probe /
    ( ( _cnst_resolution / val_analog ) - 1.0 );
} // method

double ATCP::analog_to_Kelvin( double val_analog ) {
  double val_kelvin =
    log( ( ( 10240000 / val_analog )
    - _cnst_resistance_probe ) );
  val_kelvin =
    1.0 / ( 0.001129148 + ( 0.000234125 * val_kelvin ) +
    ( 0.0000000876741 * val_kelvin * val_kelvin * val_kelvin ) );
  return val_kelvin;
} // method

double ATCP::kelvin_to_Celsius( double val_kelvin ) {
  return val_kelvin - 273.15;
} // method

double ATCP::get_Analog( void ) {
  return _val_analog;
} // method

double ATCP::get_Resistor( void ) {
  return _val_resistor;
} // method

double ATCP::get_Kelvin( void ) {
  return _val_kelvin;
} // method

double ATCP::get_Celsius( void ) {
  return _val_celsius;
} // method

char* ATCP::get_Analog_as_cString( void ) {
  char c_string[ 8 ]; // Buffer big enough for 7-character float
  dtostrf(_val_analog, 6, 2, c_string); // Leave room for too large numbers!
  return c_string;
} // method

char* ATCP::get_Resistor_as_cString( void ) {
  char c_string[ 8 ]; // Buffer big enough for 7-character float
  dtostrf(_val_resistor, 6, 2, c_string); // Leave room for too large numbers!
  return c_string;
} // method

char* ATCP::get_Kelvin_as_cString( void ) {
  char c_string[ 8 ]; // Buffer big enough for 7-character float
  dtostrf(_val_kelvin, 6, 2, c_string); // Leave room for too large numbers!
  return c_string;
} // method

char* ATCP::get_Celsius_as_cString( void ) {
  char c_string[ 8 ]; // Buffer big enough for 7-character float
  dtostrf(_val_celsius, 6, 2, c_string); // Leave room for too large numbers!
  return c_string;
} // method
