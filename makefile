auto-compile: C.o auto-compile.o dictionary.o iniparser.o parser.o
	gcc C.o auto-compile.o dictionary.o iniparser.o parser.o -o auto-compile -lstdc++ -lpthread -g3
	-rm *.o
C.o: code/language/C.cpp
	gcc code/language/C.cpp -c -o C.o -std=c++17 -O3 -Wall -g3
auto-compile.o: code/auto-compile.cpp
	gcc code/auto-compile.cpp -c -o auto-compile.o -std=c++17 -O3 -Wall -lpthread -g3
dictionary.o: iniparser/dictionary.c
	gcc iniparser/dictionary.c -c -o dictionary.o -O3 -Wall -g3
iniparser.o: iniparser/iniparser.c
	gcc iniparser/iniparser.c -c -o iniparser.o -O3 -Wall -g3
parser.o: code/functions/parser.cpp
	gcc code/functions/parser.cpp -c -o parser.o -std=c++17 -O3 -Wall -g3
.PHONY: clean install test
install:
	ln -s auto-compile /usr/bin/auto-compile
clean:
	-rm *.o
	-rm auto-compile