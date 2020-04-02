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

#include "./coolASSM_config.h" // base class header file

ASSM_HELPER::ASSM_HELPER( void ) {
} // method

ASSM_HELPER::~ASSM_HELPER( void ) {
} // method

String ASSM_HELPER::command_to_String( uint8_t command ) {
	String str = "";
  switch( command ) {

    case ASSM_CMD_NULL :
	     str = ASSM_CMD_NULL_STR;
	  break;

    case ASSM_CMD_SNA :
	     str = ASSM_CMD_SNA_STR;
	   break;

    case ASSM_CMD_PING :
 	     str = ASSM_CMD_PING_STR;
 	   break;
    case ASSM_CMD_PONG :
 	     str = ASSM_CMD_PONG_STR;
 	   break;

    case ASSM_CMD_AKNW :
 	     str = ASSM_CMD_AKNW_STR;
 	  break;

    case ASSM_CMD_RUN :
 	    str = ASSM_CMD_RUN_STR;
 	  break;

    case ASSM_CMD_WAIT :
 	    str = ASSM_CMD_WAIT_STR;
 	   break;

    case ASSM_CMD_EVENT :
 	    str = ASSM_CMD_EVENT_STR;
    break;

    case ASSM_CMD_DONE :
 	    str = ASSM_CMD_DONE_STR;
 	  break;

    case ASSM_CMD_STOP :
 	    str = ASSM_CMD_STOP_STR;
	  break;

    case ASSM_CMD_STATUS :
 	    str = ASSM_CMD_STATUS_STR;
 	   break;

    case ASSM_CMD_CNCT :
 	    str = ASSM_CMD_CNCT_STR;
 	  break;

    case ASSM_CMD_RNMD1 :
 	    str = ASSM_CMD_RNMD1_STR;
 	  break;

    case ASSM_CMD_RNMD2 :
 	    str = ASSM_CMD_RNMD2_STR;
 	  break;

    case ASSM_CMD_RNMD3 :
 	    str = ASSM_CMD_RNMD3_STR;
 	  break;

    case ASSM_CMD_RNMD4 :
 	    str = ASSM_CMD_RNMD4_STR;
 	  break;

    case ASSM_CMD_RNMD5 :
 	    str = ASSM_CMD_RNMD5_STR;
 	  break;

    case ASSM_CMD_RNMD6 :
 	    str = ASSM_CMD_RNMD6_STR;
 	  break;

    case ASSM_CMD_RNMD7 :
 	    str = ASSM_CMD_RNMD7_STR;
 	  break;

    case ASSM_CMD_DCNT :
 	    str = ASSM_CMD_DCNT_STR;
 	  break;

    // if COMMAND is unkown, show the given COMMAND as a number
    default :
	    char cstr[12];
	    sprintf(cstr, "%d", command);
	    str = String(cstr);
	  break;
  } // switch
  return str;
} // method

String ASSM_HELPER::state_to_String( uint8_t state ) {
  String str = "";
  switch( state ) {

    case ASSM_STATE_ERROR :
      str = ASSM_STATE_ERROR_STR;
    break;

    case ASSM_STATE_IDLE :
      str = ASSM_STATE_IDLE_STR;
    break;

    case ASSM_STATE_MODE1 :
      str = ASSM_STATE_MODE1_STR;
    break;

    case ASSM_STATE_MODE2 :
      str = ASSM_STATE_MODE2_STR;
    break;

    case ASSM_STATE_MODE3 :
      str = ASSM_STATE_MODE3_STR;
    break;

    case ASSM_STATE_MODE4 :
      str = ASSM_STATE_MODE4_STR;
    break;

    case ASSM_STATE_MODE5 :
      str = ASSM_STATE_MODE5_STR;
    break;

    case ASSM_STATE_MODE6 :
      str = ASSM_STATE_MODE6_STR;
    break;

    case ASSM_STATE_MODE7 :
      str = ASSM_STATE_MODE7_STR;
    break;

    // if STATE is unkown, show the given STATE as a number
    default :
      char cstr[12];
      sprintf(cstr, "%d", state);
      str = String(cstr);
    break;

  } // switch
  return str;
} // method

uint8_t ASSM_HELPER::state_to_Integer( String state ) {
  uint8_t integer = 0;
  const char* cstate = state.c_str( );
  if( strcmp( cstate, ASSM_STATE_ERROR_STR ) == 0 ) {
    integer = ASSM_STATE_ERROR;
  } else if( strcmp( cstate, ASSM_STATE_IDLE_STR ) == 0 ) {
    integer = ASSM_STATE_IDLE;
  } else if( strcmp( cstate, ASSM_STATE_MODE1_STR ) == 0 ) {
    integer = ASSM_STATE_MODE1;
  } else if( strcmp( cstate, ASSM_STATE_MODE2_STR ) == 0 ) {
    integer = ASSM_STATE_MODE2;
  } else if( strcmp( cstate, ASSM_STATE_MODE3_STR ) == 0 ) {
    integer = ASSM_STATE_MODE3;
  } else if( strcmp( cstate, ASSM_STATE_MODE4_STR ) == 0 ) {
    integer = ASSM_STATE_MODE4;
  } else if( strcmp( cstate, ASSM_STATE_MODE5_STR ) == 0 ) {
    integer = ASSM_STATE_MODE5;
  } else if( strcmp( cstate, ASSM_STATE_MODE6_STR ) == 0 ) {
    integer = ASSM_STATE_MODE6;
  } else if( strcmp( cstate, ASSM_STATE_MODE7_STR ) == 0 ) {
    integer = ASSM_STATE_MODE7;
  } // if
  return integer;
} // method

String ASSM_HELPER::mark_as_State_or_Command( String state_or_command ) {
  return String( _markerHead ) +
         state_or_command +
         String( _markerPref ) +
         String( _markerFoot );
} // method

String ASSM_HELPER::mark_as_Data_starting( String individual_data_command ) {
  return String( _markerHead ) +
         individual_data_command +
         String( _markerFoot );
} // method

String ASSM_HELPER::mark_as_Data_stopping( String individual_data_command ) {
  return String( _markerHead ) +
         String( _markerPref ) +
         individual_data_command +
         String( _markerFoot );
} // method

int ASSM_HELPER::a2i(const char *s)
{
  int sign=1;
  if(*s == '-'){
    sign = -1;
    s++;
  }
  int num=0;
  while(*s){
    num=((*s)-'0')+num*10;
    s++;
  }
  return num*sign;
} // method

String ASSM_HELPER::d2str( double d ) {
  char c[12];
  sprintf( c,"%d", d);
  String str = "";
  str = String( c );
  return str;
} // method
