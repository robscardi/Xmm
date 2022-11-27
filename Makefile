CURRENT_DIR = $(shell pwd)

CXXFLAGS = -I $(CURRENT_DIR) -I $(CURRENT_DIR)/src
CXX = g++ -std=c++20 
FILE = (wildcard *.cpp)


main : libXMM.so.1
	$(CXX) $(CXXFLAGS) -Wall -g -c main.cpp -o main.o
	$(CXX) -g -o main main.o -L. -lXMM


libXMM.so.1 : XMM.o
	$(CXX) -shared -Wl,-soname,libXMM.so.1 -o libXMM.so.1 XMM.o -lc 
	sudo /sbin/ldconfig 
	ln -sf libXMM.so.1 libXMM.so

XMM.o : window.o connection.o gcontext.o
	ld -Ur  window.o connection.o gcontext.o -o XMM.o

gcontext.o : src/gcontext.cpp src/connection.cpp
	$(CXX) -c -g $(CXXFLAGS) -Wall -fPIC src/gcontext.cpp

window.o : src/window.cpp src/connection.cpp
	$(CXX) -c -g $(CXXFLAGS) -Wall -fPIC src/window.cpp

connection.o : src/connection.cpp
	$(CXX) -c -g $(CXXFLAGS) -Wall -fPIC src/connection.cpp

.PHONY : clear

clear : 
	rm window.o
	rm connection.o
	rm gcontext.o
	rm libXMM.so.1
	rm libXMM.so
	rm XMM.o
	rm main.o
	rm main


