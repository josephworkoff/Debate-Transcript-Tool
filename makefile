main: main.o speech.o event.o
	g++ -o main main.o speech.o event.o

main.o: main.cpp speech.h event.h
	g++ -c main.cpp

speech.o: speech.cpp speech.h
	g++ -c speech.cpp

event.o: event.cpp event.h
	g++ -c event.cpp

clean:
	\rm -f *.o main
