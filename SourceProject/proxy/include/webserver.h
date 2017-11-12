/*
    author: linukey
    time: 2017.11.12
    ps:
*/

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <vector>

namespace linukey{  
namespace webserver{    

typedef std::shared_ptr<boost::asio::ip::tcp::socket> shared_socket;
typedef boost::system::error_code e_code;

class WebServer{    
public:
    WebServer() : ACCEPTOR(SERVICE, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8001)) {}
    boost::asio::io_service SERVICE;

private:
    boost::asio::ip::tcp::acceptor ACCEPTOR;
    const int buffer_size = 100000;

private:
    void accept_handle(shared_socket sock, const e_code& err);
    size_t read_complete(char *buff, const e_code& err, size_t size);
    void write_handle(const e_code& err, size_t size);
    void write_some(shared_socket sock, std::string message);
    void read_handle(shared_socket sock, char *buff, const e_code& err, size_t size);

private:
    void response(shared_socket sock, std::string request);

public:
    void run();
};

} // namespace webserver
} // namespace linukey
