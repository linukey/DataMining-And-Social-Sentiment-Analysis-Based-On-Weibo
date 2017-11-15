server : run.cpp src/webserver.cpp
	g++ run.cpp src/webserver.cpp -o run_server -lboost_system -lpthread -std=c++11 -L ../proxymanager/cpp -lproxy

clean:
	rm run_server   
