CFLAGS = -I
CC = g++

main : main.cpp connection.cpp
	$(CC) -o main -g main.cpp connection.cpp
