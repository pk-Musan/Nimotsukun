nimotsu: main.o state.o
	g++ -Wall -o nimotsu main.o state.o
state.o: state.cpp
	g++ -Wall -c state.cpp
main.o: main.cpp
	g++ -Wall -c main.cpp
clean:
	rm -f *.o main