/*
  protocol.c - Driveboard protocol parser.
  Part of DriveboardFirmware

  Copyright (c) 2014 Stefan Hechenberger

  DriveboardFirmware is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version. <http://www.gnu.org/licenses/>

  DriveboardFirmware is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
*/


#ifndef protocol_h
#define protocol_h


// commands, handled in serial.c
#define CMD_STOP 1
#define CMD_RESUME 2
#define CMD_STATUS 3
#define CMD_SUPERSTATUS 4
#define CMD_CHUNK_PROCESSED 5
#define CMD_RASTER_DATA_START 16
#define CMD_RASTER_DATA_END 17
#define STATUS_END 6


// commands, handled in protocol.c
#define CMD_NONE 'A'
#define CMD_LINE 'B'
#define CMD_DWELL 'C'
#define CMD_RASTER 'D'

#define CMD_REF_RELATIVE 'E'
#define CMD_REF_ABSOLUTE 'F'

#define CMD_HOMING 'G'

#define CMD_SET_OFFSET_TABLE 'H'
#define CMD_SET_OFFSET_CUSTOM 'I'
#define CMD_SEL_OFFSET_TABLE 'J'
#define CMD_SEL_OFFSET_CUSTOM 'K'

#define CMD_AIR_ENABLE 'L'
#define CMD_AIR_DISABLE 'M'
#define CMD_AUX_ENABLE 'N'
#define CMD_AUX_DISABLE 'O'
// #define CMD_AUX2_ENABLE 'P'
// #define CMD_AUX2_DISABLE 'Q'

#define PARAM_TARGET_X 'x'
#define PARAM_TARGET_Y 'y'
#define PARAM_TARGET_Z 'z'
#define PARAM_FEEDRATE 'f'
#define PARAM_INTENSITY 's'
#define PARAM_DURATION 'd'
#define PARAM_PIXEL_WIDTH 'p'
#define PARAM_OFFTABLE_X 'h'
#define PARAM_OFFTABLE_Y 'i'
#define PARAM_OFFTABLE_Z 'j'
#define PARAM_OFFCUSTOM_X 'k'
#define PARAM_OFFCUSTOM_Y 'l'
#define PARAM_OFFCUSTOM_Z 'm'


// status: error markers
#define STOPERROR_OK ' '

#define STOPERROR_SERIAL_STOP_REQUEST '!'
#define STOPERROR_RX_BUFFER_OVERFLOW '"'

#define STOPERROR_LIMIT_HIT_X1 '$'
#define STOPERROR_LIMIT_HIT_X2 '%'
#define STOPERROR_LIMIT_HIT_Y1 '&'
#define STOPERROR_LIMIT_HIT_Y2 '*'
#define STOPERROR_LIMIT_HIT_Z1 '+'
#define STOPERROR_LIMIT_HIT_Z2 '-'

#define STOPERROR_INVALID_MARKER '#'
#define STOPERROR_INVALID_DATA ':'
#define STOPERROR_INVALID_COMMAND '<'
#define STOPERROR_INVALID_PARAMETER '>'
#define STOPERROR_TRANSMISSION_ERROR '='


// status: info markers
#define INFO_IDLE_YES 'A'
#define INFO_DOOR_OPEN 'B'
#define INFO_CHILLER_OFF 'C'

// status:  info params
#define INFO_POS_X 'x'
#define INFO_POS_Y 'y'
#define INFO_POS_Z 'z'
#define INFO_VERSION 'v'
#define INFO_BUFFER_UNDERRUN 'w'
#define INFO_STACK_CLEARANCE 'u'

#define INFO_HELLO '~'

// super status:
#define INFO_OFFCUSTOM_X 'a'
#define INFO_OFFCUSTOM_Y 'b'
#define INFO_OFFCUSTOM_Z 'c'
#define INFO_FEEDRATE 'g'
#define INFO_INTENSITY 'h'
#define INFO_DURATION 'i'
#define INFO_PIXEL_WIDTH 'j'



// Initialize the parser.
void protocol_init();

// Main firmware loop.
// Processes serial rx buffer and queues commands for stepper interrupt.
void protocol_loop();

// Called to make protocol_idle report
// (super)status the next time it runs.
void protocol_request_status();
void protocol_request_superstatus();

// called when rx serial buffer empty
void protocol_mark_underrun();

// called whenever protocol loop is waiting
void protocol_idle();


#endif
