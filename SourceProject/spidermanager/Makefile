all : libspidermanager.a demo

.PHONY : all

libspidermanager.a : src/spidermanager.cpp
	g++ -c src/spidermanager.cpp -std=c++11
	ar -crv libspidermanager.a spidermanager.o
	rm spidermanager.o

demo : src/spidermanager.cpp demo.cpp
	g++ demo.cpp src/spidermanager.cpp -o demo -std=c++11

clean:
	rm demo
	rm libspidermanager.a
