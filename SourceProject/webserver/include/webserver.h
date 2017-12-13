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
#include "http.h"
#include "../../proxymanager/cpp/include/proxymanager.h"
#include "../../spidermanager/include/spidermanager.h"

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

    linukey::proxy::ProxyManager* proxymanager;
    linukey::spidermanager::SpiderManager* spidermanager;

private:
    void accept_handle(shared_socket sock, const e_code& err);
    void write_handle(const e_code& err, size_t size);
    void write_some(shared_socket sock, std::string message);
    size_t read_complete(linukey::webserver::http::Request* req, char *buff, const e_code& err, size_t size);
    void read_handle(linukey::webserver::http::Request* req, shared_socket sock, char *buff, const e_code& err, size_t size);

private:
    void router(linukey::webserver::http::Request* req, shared_socket sock);
    void log(const std::string& message);

public:
    void run();
};

} // namespace webserver
} // namespace linukey

#endif
