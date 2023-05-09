CURRENT_DIR = $(shell pwd)
HDR = $(CURRENT_DIR)/headers
SRC = $(CURRENT_DIR)/src
CTN = $(SRC)/containers

CXXFLAGS = -I $(CURRENT_DIR) -I $(SRC) -I $(HDR)
CXX = g++ -std=c++20 -D__INCLUDE__ASIO
FILE = (wildcard *.cpp)


main : libXMM.so.1
	$(CXX) $(CXXFLAGS) -Wall -g -c main.cpp -o main.o
	$(CXX) -g -o main main.o -L. -lXMM


libXMM.so.1 : XMM.o
	$(CXX) -shared -Wl,-soname,libXMM.so.1 -o libXMM.so.1 XMM.o -lc 
	sudo /sbin/ldconfig 
	ln -sf libXMM.so.1 libXMM.so

XMM.o : window.o connection.o gcontext.o asioconnection.o 
	ld -Ur  window.o connection.o gcontext.o -o XMM.o

gcontext.o : src/gcontext.cpp src/connection.cpp
	$(CXX) -c -g $(CXXFLAGS) -Wall -fPIC src/gcontext.cpp

window.o : src/window.cpp src/connection.cpp
	$(CXX) -c -g $(CXXFLAGS) -Wall -fPIC src/window.cpp

connection.o : src/connection.cpp
	$(CXX) -c -g $(CXXFLAGS) -Wall -fPIC src/connection.cpp

connection_asio.o : src/asioconnect.cpp
	$(CXX) -c -g $(CXXFLAGS) -Wall -fPIC src/connection_asio.cpp

.PHONY : clear

clear : 
	rm window.o || true
	rm connection.o || true
	rm asioconnect.o || true
	rm gcontext.o || true
	rm libXMM.so.1 || true
	rm libXMM.so || true
	rm XMM.o || true
	rm main.o || true
	rm main || true


