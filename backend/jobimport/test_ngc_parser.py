#!/usr/bin/python

import io

from ngc_parser import NGCParser

tolerance = 0.08
preColor = {}
postColor = {}

fin = open("test.ngc"); 
ngc_string = fin.read();  
fin.close() 

ngc_string = unicode(ngc_string)
ngcParser = NGCParser()
forced_unit = 0

parse_results = ngcParser.parse(ngc_string)

print (parse_results)

