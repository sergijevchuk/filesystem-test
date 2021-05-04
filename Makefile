all:
	g++ -c fs.cpp -o fs.o
	g++ -c main.cpp -o main.o
	g++  *.o -o fs
mkfs:
	g++ -c fs.cpp -o fs.o
	g++ -c mkfs.cpp -o mkfs.o
	g++ fs.o mkfs.o -o mkfs
clean:
	@rm *.o
