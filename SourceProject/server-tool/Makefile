run_server:control/*.cpp
	g++ control/*.cpp -o run_server -lboost_system -L lib -lwebserver -L ../proxymanager/cpp -lproxy -L ../spidermanager -lspidermanager -lpthread -std=c++11 -lpython3.5

clean:
	rm run_server
