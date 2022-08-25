CXX=g++
CPPFLAGS=-O3 --std=c++17 -Wall -Wno-sign-compare
SOURCES=./src/* ./tests/src/*

compile:
	${CXX} -o gmls.exe ${CPPFLAGS} ${SOURCES}

examples:
	sed -i 's/#define TESTING_MODE.*/#define TESTING_MODE 0/' ./src/main.cpp
	${MAKE} compile

unit_tests:
	sed -i 's/#define TESTING_MODE.*/#define TESTING_MODE 1/' ./src/main.cpp
	${MAKE} compile

.PHONY : clean
clean:
	rm -rf *.so *.exe
