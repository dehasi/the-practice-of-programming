.PHONY: markov
markov: markov.c
	rm markov || true
	gcc markov.c -o markov
	time ./markov < ../text.txt
	rm markov
