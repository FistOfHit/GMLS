CXX=g++-10
CXXFLAGS=--std=c++20 -O2 -Wall -Wno-sign-compare
SOURCES=./grid/grid.cc ./cycling/cycling.cc ./smoothers/smoothers.cc
INCLUDES=-Icommon -Icycling -Igrid -Ismoothers

make:
	${CXX} -o gmls.exe ${CXXFLAGS} ${SOURCES} ${INCLUDES}

clean:
	rm -rf *.so *.exe
