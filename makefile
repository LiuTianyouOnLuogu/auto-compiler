auto-compile: C.o auto-compile.o dictionary.o iniparser.o s2v.o v2s.o
	gcc C.o auto-compile.o dictionary.o iniparser.o s2v.o v2s.o -o auto-compile -lstdc++
C.o: code/language/C.cpp
	gcc code/language/C.cpp -c -o C.o -std=c++11 -O3 -Wall
auto-compile.o: code/auto-compile.cpp
	gcc code/auto-compile.cpp -c -o auto-compile.o -std=c++11 -O3 -Wall
dictionary.o: iniparser/dictionary.c
	gcc iniparser/dictionary.c -c -o dictionary.o -O3 -Wall
iniparser.o: iniparser/iniparser.c
	gcc iniparser/iniparser.c -c -o iniparser.o -O3 -Wall
s2v.o: code/functions/s2v.cpp
	gcc code/functions/s2v.cpp -c -o s2v.o -std=c++11 -O3 -Wall
v2s.o: code/functions/v2s.cpp
	gcc code/functions/v2s.cpp -c -o v2s.o -std=c++11 -O3 -Wall
.PHONY: clean install
install:
	ln -s auto-compile /usr/bin/auto-compile
clean:
	rm *.o
	rm auto-compile