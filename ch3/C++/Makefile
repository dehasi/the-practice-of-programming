.PHONY: markov
markov: markov.cpp
	rm markov || true
	g++ markov.cpp -o markov
	time ./markov < ../text.txt
	rm markov

.PHONY: markov_list
markov_list: markov_list.cpp
	rm markov_list || true
	g++ markov_list.cpp -o markov_list
	time ./markov_list < ../text.txt
	rm markov_list
