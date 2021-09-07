CFLAGS = -I
CC = g++ -std=c++20
FILE = (wildcard *.cpp)

main : libXMM.so.1
	$(CC) -Wall -g -c main.cpp -o main.o
	$(CC) -g -o main main.o -L. -lXMM


libXMM.so.1 : XMM.o
	$(CC) -shared -Wl,-soname,libXMM.so.1 -o libXMM.so.1 XMM.o -lc 
	#/sbin/ldconfig -n . \
	ln -sf libXMM.so.1 libXMM.so

XMM.o : window.o connection.o gcontex.o
	ld -Ur  window.o connection.o gcontex.o -o XMM.o

gcontex.o : gcontex.cpp connection.cpp
	$(CC) -c -g -Wall -fPIC gcontex.cpp

window.o : window.cpp connection.cpp
	$(CC) -c -g -Wall -fPIC window.cpp

connection.o : connection.cpp
	$(CC) -c -g -Wall -fPIC connection.cpp

.PHONY : clear

clear : 
	rm window.o
	rm connection.o
	rm gcontex.o
	rm libXMM.so.1
	rm libXMM.so
	rm XMM.o
	rm main.o
	rm main


