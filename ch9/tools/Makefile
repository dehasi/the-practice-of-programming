.PNONY: web
web: web.sh unhtml.pl geturl.tcl split.awk
	./web.sh http://wiki.c2.com/?WikiWikiWeb

.PNONY: unhtml
unhtml: unhtml.pl
	@ ./geturl.tcl http://wiki.c2.com/?WikiWikiWeb | ./unhtml.pl

.PNONY: geturl
geturl: geturl.tcl
	@ ./geturl.tcl http://wiki.c2.com/?WikiWikiWeb

.PNONY: fmt
fmt: fmt.awk
	@cat ../../ch3/text.txt | ./fmt.awk

.PNONY: split
split: split.awk
	@cat ../../ch3/text.txt | ./split.awk

