###############
# DIRECTORIES #
###############
CURRENT_DIR = $(shell pwd)
HDR = $(CURRENT_DIR)/headers
SRC = $(CURRENT_DIR)/sources
CTN = $(SRC)/containers
BUILD = $(CURRENT_DIR)/build


###############
# FLAGS       #
###############
CXXFLAGS = -I $(CURRENT_DIR) -I $(SRC) -I $(HDR) -I $(CTN)
CXX = g++ -std=c++20 -D__INCLUDE__ASIO -o $(BUILD)/$@
FILE = (wildcard *.cpp)


main : libXMM.so.1
	$(CXX) $(CXXFLAGS) -Wall -g -c main.cpp -o $(BUILD)/main.o
	$(CXX) -g -o $(BUILD)/main $(BUILD)/main.o -L. -lXMM

libXMM.so.1 : XMM.o
	$(CXX) -shared -Wl,-soname,libXMM.so.1 -o $(BUILD)/libXMM.so.1 $(BUILD)/XMM.o -lc 
	sudo /sbin/ldconfig 
	ln -sf $(BUILD)/libXMM.so.1 libXMM.so

XMM.o : window.o connection.o gcontext.o
	ld -Ur  $(BUILD)/window.o $(BUILD)/connection.o $(BUILD)/gcontext.o -o $(BUILD)/XMM.o

gcontext.o : $(SRC)/gcontext.cpp init
	$(CXX) -c -g $(CXXFLAGS) -Wall -fPIC $(SRC)/gcontext.cpp

window.o : $(SRC)/window.cpp init
	$(CXX) -c -g $(CXXFLAGS) -Wall -fPIC $(SRC)/window.cpp

connection.o : $(SRC)/connection.cpp init
	$(CXX) -c -g $(CXXFLAGS) -Wall -fPIC $(SRC)/connection.cpp

connection_asio.o : $(SRC)/connection_asio.cpp init
	$(CXX) -c -g $(CXXFLAGS) -Wall -fPIC $(SRC)/connection_asio.cpp

.PHONY : clear
.PHONY : init
init : 
	mkdir -p $(BUILD)

clear :
	rm -r $(BUILD) || true;
	rm libXMM.so;
