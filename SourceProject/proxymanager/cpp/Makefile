all : libproxy.so demo

.PHONY : all

libproxy.so : src/proxymanager.cpp
	g++ -fPIC -shared -o libproxy.so src/proxymanager.cpp -std=c++11 -lpython3.5

demo : src/proxymanager.cpp demo.cpp
	g++ demo.cpp src/proxymanager.cpp -o demo -lpython3.5 -std=c++11

clean:
	rm demo
	rm libproxy.so
