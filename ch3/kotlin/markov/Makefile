markov: markov.jar
	time kotlin -cp markov.jar markov.App < ../../text.txt

markov.jar: Markov.kt
	kotlinc Markov.kt -include-runtime -d markov.jar

.PHONY: clean
clean:
	rm *.jar
