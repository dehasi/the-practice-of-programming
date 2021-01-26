.PHONY: test
test: markov
	./markov < ../ch3/text.txt > out
	awk -f markov-test.awk ../ch3/text.txt out

markov: ../ch3/C/markov.c
	gcc ../ch3/C/markov.c -o markov

.PHONY: clean
clean:
	rm markov  out || true
