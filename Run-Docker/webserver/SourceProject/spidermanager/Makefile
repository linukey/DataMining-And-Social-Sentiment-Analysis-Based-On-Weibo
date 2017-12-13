all : libspidermanager.so demo

.PHONY : all

libspidermanager.so : src/spidermanager.cpp
	g++ -fPIC -shared -o libspidermanager.so src/spidermanager.cpp -std=c++11

demo : src/spidermanager.cpp demo.cpp
	g++ demo.cpp src/spidermanager.cpp -o demo -std=c++11

clean:
	rm demo
	rm libspidermanager.so
