/*
    author: linukey
    time: 2017.11.12
    ps:
*/

#ifndef __LINUKEY_WEBSERVER_H__
#define __LINUKEY_WEBSERVER_H__

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <queue>
#include <fstream>
#include <map>
#include <set>
#include "../../proxymanager/cpp/include/proxymanager.h"

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
    const int buffer_size = 1024;
    //std::map<std::string, linukey::proxy::ProxyManager*> proxymanager_pool;
    linukey::proxy::ProxyManager* proxymanager;
    // key=client_id value=proxy
    std::map<std::string, std::string> client_proxy_pool;
    // key=client_id value=live_time
    std::map<std::string, time_t> clientmanager_pool;

private:
    void accept_handle(shared_socket sock, const e_code& err);
    size_t read_complete(char *buff, const e_code& err, size_t size);
    void write_handle(const e_code& err, size_t size);
    void write_some(shared_socket sock, std::string message);
    void read_handle(shared_socket sock, char *buff, const e_code& err, size_t size);
    time_t get_now_time();

private:
    void response(shared_socket sock, std::string request);
    void log(const std::string& message);

public:
    int all = 0;
    void run();
};

} // namespace webserver
} // namespace linukey

#endif
