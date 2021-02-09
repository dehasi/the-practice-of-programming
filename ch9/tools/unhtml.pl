#!/usr/bin/env perl
# unhtml.pl: delete HTML tags

while (<>) {
    $str .= $_;       # collect all input into a single string
}
$str =~ s/<[^>]*>//g; # delete <...>
$str =~ s/&nbsp;/ /g; # replace &nbsp; by blank
$str =~ s/\s+/\n/g;   # compress white space
print $str;
