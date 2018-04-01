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
#include "http.h"

namespace linukey{  
namespace webserver{    

typedef std::shared_ptr<boost::asio::ip::tcp::socket> shared_socket;
typedef boost::system::error_code e_code;

class WebServer{    
public:
    WebServer();
    boost::asio::io_service SERVICE;
    boost::asio::ip::tcp::acceptor ACCEPTOR;

    // 响应
    void response(shared_socket sock, std::string message);
    // 启动
    void run();

private:
    const int buffer_size = 1024;

    void accept_handle(shared_socket sock, const e_code& err);
    void write_handle(const e_code& err, size_t size);
    void read_handle(linukey::webserver::http::Request* req, shared_socket sock, char *buff, const e_code& err, size_t size);
    size_t read_complete(linukey::webserver::http::Request* req, char *buff, const e_code& err, size_t size);

// 应用方自定义
protected:

    // 路由
    virtual void router(linukey::webserver::http::Request* req, shared_socket sock);
};

} // namespace webserver
} // namespace linukey

#endif
