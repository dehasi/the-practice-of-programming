clean:
	@rm *.o 2>/dev/null || true
	@rm binary_search_test 2>/dev/null || true
	@rm quicksort 2>/dev/null || true
	@rm libraries 2>/dev/null || true
	@rm arrays* 2>/dev/null || true


binary_search_test: 2.1_Searching/2.1_binary_search_test.c 2.1_Searching
	gcc -I. 2.1_Searching/2.1_binary_search_test.c 2.1_Searching/2.1_binary_search.c -o binary_search_test
	./binary_search_test
	rm binary_search_test

quicksort: 2.2_Sorting/2.2_quicksort.c
	gcc 2.2_Sorting/2.2_quicksort.c -g3 -o quicksort
	./quicksort

quicksort_test: 2.2_Sorting/2.2_quicksort.c 2.2_Sorting
	gcc -I. 2.2_Sorting/2.2_quicksort.c 2.2_Sorting/2.2_quicksort_test.c -o quicksort_test
	./quicksort_test || true
	rm quicksort_test

libraries: 2.3_libraries.c
	gcc 2.3_libraries.c -o libraries -Wno-empty-body
	time ./libraries

arrays: 2.6_growing_arrays/array.c
	gcc 2.6_growing_arrays/array.c -o arrays
	time ./arrays

arrays2: 2.6_growing_arrays/array2.c
	gcc 2.6_growing_arrays/array2.c -o arrays2
	time ./arrays2

list: 2.7_Lists/linked_list.c
	gcc 2.7_Lists/linked_list.c -o linked_list
	time ./linked_list

tree: 2.8_Trees/tree.c
	gcc 2.8_Trees/tree.c -o tree
	time ./tree

.PHONY: tree_test
tree_test: 2.8_Trees/tree.c 2.8_Trees
	gcc -I. 2.8_Trees/tree.c 2.8_Trees/test_tree.c -o test_tree
	./test_tree || true
	rm test_tree

.PHONY: hashtable_test
hashtable_test: 2.9_Hash_tables/hashtable.c
	gcc -I. 2.9_Hash_tables/hashtable.c 2.9_Hash_tables/test_hashtable.c -o test_hashtable
	./test_hashtable || true
	rm test_hashtable

download:
	wget http://github.com/Tuplanolla/cheat/raw/1.0.4/cheat.h
	wget http://github.com/Tuplanolla/cheat/raw/1.0.4/cheats.h
	wget http://github.com/Tuplanolla/cheat/raw/1.0.4/example.c
	wget http://github.com/Tuplanolla/cheat/raw/1.0.4/examples.c

.PHONY: binary_search_test quicksort clean
