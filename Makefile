.POSIX:
.SUFFIXES:

.SUFFIXES: .cpp .o
.cpp.o:
	c++ -c -std=c++17 $<

all: main

check:
	./main

main: main.o
	c++ $< -o $@

main.o: main.cpp tree.h

clean:
	rm -f main.o main
