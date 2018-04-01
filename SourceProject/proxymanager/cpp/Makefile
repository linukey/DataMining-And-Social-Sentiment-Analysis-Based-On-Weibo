all : libproxy.a demo

.PHONY : all

libproxy.a : src/proxymanager.cpp
	g++ -c src/proxymanager.cpp -std=c++11 -lpython3.5
	ar -crv libproxy.a proxymanager.o
	rm proxymanager.o

demo : src/proxymanager.cpp demo.cpp
	g++ demo.cpp src/proxymanager.cpp -o demo -lpython3.5 -std=c++11

clean:
	rm demo
	rm libproxy.a
