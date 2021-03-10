Optmize = -O0 -pthread -Wno-unused-result -Wall -g3 -Wno-format-overflow -Werror
auto-compile: C.o auto-compile.o dictionary.o iniparser.o parser.o submission.o
	gcc C.o auto-compile.o dictionary.o iniparser.o parser.o -o auto-compile -lstdc++ -pthread -g3
	gcc C.o submission.o dictionary.o iniparser.o parser.o -o submission -lstdc++ -g3
submission.o: code/submission.cpp
	gcc code/submission.cpp -c -o submission.o -std=c++17 $(Optmize) 
C.o: code/language/C.cpp
	gcc code/language/C.cpp -c -o C.o -std=c++17 $(Optmize)
auto-compile.o: code/auto-compile.cpp
	gcc code/auto-compile.cpp -c -o auto-compile.o -std=c++17 $(Optmize)
dictionary.o: iniparser/dictionary.c
	gcc iniparser/dictionary.c -c -o dictionary.o $(Optmize) --std=c17
iniparser.o: iniparser/iniparser.c
	gcc iniparser/iniparser.c -c -o iniparser.o $(Optmize) --std=c17
parser.o: code/functions/parser.cpp
	gcc code/functions/parser.cpp -c -o parser.o -std=c++17 $(Optmize) --std=c++17
.PHONY: clean install test
install:
	ln -s auto-compile /usr/bin/auto-compile
	ln -s submission /usr/bin/submission
clean:
	-rm *.o
	-rm auto-compile
	-rm submission