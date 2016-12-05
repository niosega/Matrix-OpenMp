all: exec

exec: main.o matrix.o timer.o testbench.o
	g++ -o exec main.o matrix.o timer.o testbench.o -std=c++11 -fopenmp -O3

main.o: main.cpp
	g++ -c main.cpp -o main.o -std=c++11 -O3
	
matrix.o: matrix.cpp matrix.h
	g++ -c matrix.cpp -o matrix.o -std=c++11 -O3

timer.o: timer.cpp timer.h
	g++ -c timer.cpp -o timer.o -std=c++11 -O3
	
testbench.o: testbench.cpp testbench.h
	g++ -c testbench.cpp -o testbench.o -std=c++11 -O3
	
test: exec
	./exec 10 10 1 1

clean:
	rm exec *.o
