/*
  main.c - An embedded CNC Controller with rs274/ngc (g-code) support
  Part of DriveboardFirmware

  Copyright (c) 2009-2011 Simen Svale Skogsrud

  DriveboardFirmware is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  DriveboardFirmware is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
*/

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "config.h"
#include "planner.h"
#include "stepper.h"
#include "sense_control.h"
#include "protocol.h"
#include "serial.h"


int main() {
  sei();  //enable interrupts
  serial_init();
  protocol_init();
  planner_init();      
  stepper_init();
  sense_init();
  control_init();
  
  protocol_loop();
}
