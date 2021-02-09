#!/usr/bin/env tclsh
# geturl.tcl: retrieve a document from URL
# input has form [http://]abc.def.com[/whatever...]

regsub "http://" $argv "" argv ;# remove http:// if present
regsub "/" $argv " " argv      ;# replace leading / with blank

set so [socket [lindex $argv 0] 80] ;# make network connection
set q "/[lindex $argv 1]"

puts $so "GET $q HTTP/1.0\n\n"  ;# send request
flush $so
while {[gets $so line] >= 0 && $line != ""} {} ;# skip header
puts [read $so]                 ;# read and print reply
