CXX=g++-10
CXXFLAGS=--std=c++20 -O2 -Wall -Wno-sign-compare
SOURCES=./grid/* ./cycling/* ./smoothers/* ./common/*
INCLUDES=-Icommon/* -Icycling/* -Igrid/grid.h -Ismoothers/*

make:
	${CXX} -o gmls.exe ${CXXFLAGS} ${SOURCES} ${INCLUDES}

clean:
	rm -rf *.so *.exe
