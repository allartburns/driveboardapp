__author__ = 'jet <jet@allartburns.org>'

import math
import sys
import re
import os.path
import StringIO


class NGCParser:
    """Parse subset of G-code that we can implement on the Lasersaur.
       from https://github.com/nortd/lasersaur/wiki/gcode

       TODO: need to somehow parse non cut/traverse commands

    G0 X1 Y1 traverse the head to 1,1
      G0 F100 sets the traverse speed to 100mm/min
    G1 X1 Y1 cut the head to 1,1
      G1 F100 sets the cut speed to 100mm/min
    G4 pierce (TBD)
    G10 set offsets
      G10 L20 P0 - set table offset (G54) to current location
      G10 L20 P1 - set custom offset (G55) to current location
      G10 L2 P0 X20 Y20 - set table offset (G54) to 20,20
      G10 L2 P1 X220 Y140 - set custom offset (G55) to 220,140
    G30 homing cycle
    G54 use table switch offset
    G55 use custom swich offset
    G90 absolute coordinates
    G91 relative cooridantes
    M80 air assist enable
    M81 air assist disable
    M82 aux1 enable
    M83 aux1 disable
    M84 aux2 enable
    M85 aux2 disable

    S spindle speed == intensity
    
    Fake G-code:
    ! immediately stop operation, pause mode
    ~ contine, exit pause mode
    ? get full status string
    """



    def __init__(self):

        self.boundaries = {'#000000':[]}
        self.black_boundaries = self.boundaries['#000000']
        self.re_findall_attribs = re.compile('(S|F|X|Y|Z)(-?[0-9]+\.?[0-9]*(?:e-?[0-9]*)?)').findall
        self.prev_motion_was_seek = True
        self.paths = []
        self.current_path = []
        self.g0target = []

    def parse(self, ngcstring):


        intensity = 0.0
        feedrate = 1000.0
        self.g0target = [0.0, 0.0, 0.0]


        lines = ngcstring.split('\n')
        for line in lines:
            line = line.replace(' ', '')
            if line.startswith('G0'):
                self.parseG0(line)
            elif line.startswith('G1'):
                self.parseG1(line)
            elif line.startswith('S'):
                self.parseS(line)
            else:
                self.wontParse(line)

        job = {'head':{}, 'passes':[], 'items':[], 'defs':[]}

        for path in self.paths:
            job['defs'].append({"kind":"path",
                                "data":path})

        return job


    def parseG0(self, line):
        # we parse all the G0 commands but only care about the last
        # one before a cut
        print("parse G0 " + line);
        attribs = self.re_findall_attribs(line[2:])
        for attr in attribs:
            if attr[0] == 'X':
                self.g0target[0] = float(attr[1])
            elif attr[0] == 'Y':
                self.g0target[1] = float(attr[1])
            elif attr[0] == 'Z':
                self.g0target[2] = float(attr[1])
            elif attr[0] == 'F':
                self.feedrate = float(attr[1])
        self.prev_motion_was_seek = True
        return

    def parseG1(self, line):
        print("parse G1 " + line);
        if self.prev_motion_was_seek:
            # go to the last G0
            self.paths.append([[self.g0target[0], self.g0target[1], self.g0target[2]]])
            self.current_path = self.paths[-1]
            self.prev_motion_was_seek = False

        target = [0.0, 0.0, 0.0]
        attribs = self.re_findall_attribs(line[2:])
        for attr in attribs:
            if attr[0] == 'X':
                target[0] = float(attr[1])
            elif attr[0] == 'Y':
                target[1] = float(attr[1])
            elif attr[0] == 'Z':
                target[2] = float(attr[1])
            elif attr[0] == 'S':
                intensity = float(attr[1])
            elif attr[0] == 'F':
                feedrate = float(attr[1])
        self.current_path.append([target[0], target[1], target[2]])
        return

    def parseS(self, line):
        attribs = self.re_findall_attribs(line)
        for attr in attribs:
            if attr[0] == 'S':
                intensity = float(attr[1])
        return

    def wontParse(self, line):
        return

