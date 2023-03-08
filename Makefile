all:
	        gcc -ggdb -Wall --pedantic src/*.c -o bin/progr
dij:
	        gcc -Wall --pedantic dijkstra_test/*.c -o bin/dijTest

