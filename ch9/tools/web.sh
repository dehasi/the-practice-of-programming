#!/bin/sh
# web: retrieve web page and format its text, ignoring HTML

./geturl.tcl $1 | ./unhtml.pl | ./fmt.awk
