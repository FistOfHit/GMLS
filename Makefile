CXX=g++-10
CXXFLAGS=-O3 --std=c++2a -Wall -Wno-sign-compare
SOURCES=./src/* ./tests/src/*

compile:
	${CXX} -o gmls.exe ${CXXFLAGS} ${SOURCES}

examples:
	sed -i 's/#define TESTING_MODE.*/#define TESTING_MODE 0/' ./src/main.cpp
	${MAKE} compile

unit_tests:
	sed -i 's/#define TESTING_MODE.*/#define TESTING_MODE 1/' ./src/main.cpp
	${MAKE} compile

.PHONY : clean
clean:
	rm -rf *.so *.exe
