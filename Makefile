all:
	g++ -c fs.cpp -o fs.o
	g++ -c main.cpp -o main.o
	g++  *.o -o ~/fs
clean:
	@rm *.o
