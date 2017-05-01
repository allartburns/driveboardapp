/*
  sense_control.h - sensing and controlling inputs and outputs
  Part of DriveboardFirmware

  Copyright (c) 2011-2016 Stefan Hechenberger

  DriveboardFirmware is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  DriveboardFirmware is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
*/

#ifndef sense_control_h
#define sense_control_h

#include <stdbool.h>
#include "config.h"


void sense_init();
#ifdef SENSE_INVERT
  #define SENSE_X1_LIMIT ((LIMIT_PIN >> X1_LIMIT_BIT) & 1)
  #define SENSE_X2_LIMIT ((LIMIT_PIN >> X2_LIMIT_BIT) & 1)
  #define SENSE_Y1_LIMIT ((LIMIT_PIN >> Y1_LIMIT_BIT) & 1)
  #define SENSE_Y2_LIMIT ((LIMIT_PIN >> Y2_LIMIT_BIT) & 1)
#ifdef ENABLE_3Axis
  #define SENSE_Z1_LIMIT ((LIMIT_PIN >> Z1_LIMIT_BIT) & 1)
  #define SENSE_Z2_LIMIT ((LIMIT_PIN >> Z2_LIMIT_BIT) & 1)
#endif
  #define SENSE_CHILLER_OFF ((SENSE_PIN >> CHILLER_BIT) & 1)
  #define SENSE_DOOR_OPEN ((SENSE_PIN >> DOOR1_BIT) & 1)|((SENSE_PIN >> DOOR2_BIT) & 1)
#else
  #define SENSE_X1_LIMIT !((LIMIT_PIN >> X1_LIMIT_BIT) & 1)
  #define SENSE_X2_LIMIT !((LIMIT_PIN >> X2_LIMIT_BIT) & 1)
  #define SENSE_Y1_LIMIT !((LIMIT_PIN >> Y1_LIMIT_BIT) & 1)
  #define SENSE_Y2_LIMIT !((LIMIT_PIN >> Y2_LIMIT_BIT) & 1)
#ifdef ENABLE_3AXIS
  #define SENSE_Z1_LIMIT !((LIMIT_PIN >> Z1_LIMIT_BIT) & 1)
  #define SENSE_Z2_LIMIT !((LIMIT_PIN >> Z2_LIMIT_BIT) & 1)
#endif
  #define SENSE_CHILLER_OFF !((SENSE_PIN >> CHILLER_BIT) & 1)
  #define SENSE_DOOR_OPEN !((SENSE_PIN >> DOOR_BIT) & 1)
#endif


void control_init();

void control_laser_intensity(uint8_t intensity);  //0-255 is 0-100%
uint8_t control_get_intensity();

void control_air_assist(bool enable);
void control_aux_assist(bool enable);

#endif
