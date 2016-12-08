all: exec

exec: main.o matrix.o timer.o testbench.o
	g++ -o exec main.o matrix.o timer.o testbench.o -std=c++11 -fopenmp -O3

main.o: main.cpp
	g++ -c main.cpp -o main.o -std=c++11 -O3 -fopenmp
	
matrix.o: matrix.cpp matrix.h
	g++ -c matrix.cpp -o matrix.o -std=c++11 -O3 -fopenmp

timer.o: timer.cpp timer.h
	g++ -c timer.cpp -o timer.o -std=c++11 -O3 -fopenmp
	
testbench.o: testbench.cpp testbench.h
	g++ -c testbench.cpp -o testbench.o -std=c++11 -O3 -fopenmp
	
test: exec
	./exec 10 100

clean:
	rm exec *.o results.csv
