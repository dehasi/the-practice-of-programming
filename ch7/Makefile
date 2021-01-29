antispam: antispam.c  eprintf.o
	gcc antispam.c eprintf.o -o antispam
	./antispam ABC CBA AAA

eprintf.o: ../ch4/4.7_eprintf/eprintf.h ../ch4/4.7_eprintf/eprintf.c
	gcc -c ../ch4/4.7_eprintf/eprintf.c -o eprintf.o

.PHONY: clean
clean:
	rm antispam || true
	rm *.o || true
