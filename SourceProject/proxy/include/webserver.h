/*
    author: linukey
    time: 2017.11.12
    ps:
*/

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <queue>
#include <fstream>
#include <map>
#include <set>

namespace linukey{  
namespace webserver{    

typedef std::shared_ptr<boost::asio::ip::tcp::socket> shared_socket;
typedef boost::system::error_code e_code;

class WebServer{    
public:
    WebServer();
    boost::asio::io_service SERVICE;

private:
    boost::asio::ip::tcp::acceptor ACCEPTOR;
    const int buffer_size = 100000;

    /*
    * two question:
    * 1. Guarantee each ip average usage time
    * 2. Guarantee will not have more than one client using an ip
    * 3. if client is more than ip, removed more client to wiat queue
    * 
    * there use two queue to solve first question
    * there use a map that remember which client use which ip, to solve second question
    *
    * when a client request a ip, give this client one ip, and use the map to remember this client and ip
    * when this client request a new ip, to freed this ip from proxy_use_pool to proxy_unuse_pool
    */
    std::queue<std::string> proxy_unuse_pool;
    std::map<std::string, std::string> proxy_client_ip;
    std::queue<pair<shared_socket, string>> wait_client;

private:
    void accept_handle(shared_socket sock, const e_code& err);
    size_t read_complete(char *buff, const e_code& err, size_t size);
    void write_handle(const e_code& err, size_t size);
    void write_some(shared_socket sock, std::string message);
    void read_handle(shared_socket sock, char *buff, const e_code& err, size_t size);

private:
    void response(shared_socket sock, std::string request);
    std::string get_ip(const std::string& client_id);

public:
    void run();
};

} // namespace webserver
} // namespace linukey
