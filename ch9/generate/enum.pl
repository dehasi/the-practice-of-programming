# enum.pl: generate error strings from enum+comments

print "/* machine-generated; do not edit. */\n\n";
print "char *errs[] = {\n";

while(<>) {
    chop;                       # remove newline
    if (/^\s*(E[a-z0-9]+),?/) { # first word is E...
        $name = $1;             # save name
        s/.*\/\* *//;           #remove up to /*
        s/ *\*\///;             # remove */
        print "\t\"$_\", /* $name */\n";
    }
}
print "};\n"
