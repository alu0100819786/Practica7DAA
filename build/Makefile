OBJECTS = main.o
CFLAGS = -c -std=c++17

default: $(OBJECTS)
	g++  $(OBJECTS) -o vrp -g
	mv *.o ../objects
	mv vrp ../bin

main.o: ../src/main.cpp
	g++ $(CFLAGS) ../src/main.cpp


.PHONY: clean
clean:
	rm -rf ../objects/*.o
	rm -rf ../bin/*
	clear