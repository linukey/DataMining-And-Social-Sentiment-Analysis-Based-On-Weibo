/*
    author: linukey
    time: 2017.11.12
    ps:
*/

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <vector>

using namespace std;
using namespace boost::asio;

namespace linukey{  
namespace webserver{    

typedef std::shared_ptr<boost::asio::ip::tcp::socket> shared_socket;
typedef boost::system::error_code e_code;

class WebServer{    
public:
    WebServer() : ACCEPTOR(SERVICE, ip::tcp::endpoint(ip::tcp::v4(), 8001)) {}
    io_service SERVICE;

private:
    ip::tcp::acceptor ACCEPTOR;
    const int buffer_size = 100000;

public:
    void start(){    
        shared_socket sock(new ip::tcp::socket(SERVICE));
        ACCEPTOR.async_accept(*sock, boost::bind(&WebServer::accept_handle, this, sock, _1));
        SERVICE.run();
    }

    void accept_handle(shared_socket sock, const e_code& err){
        if (err){
            cerr << "accept fail!" << endl;
            return;
        }

        char *buff = new char[buffer_size];       
        async_read(*sock, 
                   buffer(buff, buffer_size), 
                   bind(&WebServer::read_complete, this, buff, _1, _2),
                   bind(&WebServer::read_handle, this, sock, buff, _1, _2));
        start();
    }

    size_t read_complete(char *buff, const e_code& err, size_t size){
        if (err){
            cerr << "read_complete fail" << endl;
            return 0;
        }
        string info(buff, size);
        return info.find("dateend") == string::npos;
    }

    void write_handle(const e_code& err, size_t size){
        if (err){
            cerr << "write fail!" << endl;
            return;
        }
    }

    void write_some(shared_socket sock, string message) {
        sock->async_write_some(buffer(message), bind(&WebServer::write_handle, this, _1, _2));
    }

    void read_handle(shared_socket sock, char *buff, const e_code& err, size_t size){
        if (err){
            cerr << "read fail!" << endl;
            delete[] buff;
            sock->close();
            return;
        }

        string info(buff, size);
        delete[] buff;

        vector<string> v_data;
        string request_data = info.substr(info.find("\r\n\r\n")+4);
        if (request_data.length()){
            size_t pos = string::npos;
            size_t pre = 0;
            while ((pos = request_data.find('&', pre+1)) != string::npos){ 
                v_data.push_back(request_data.substr(pre, pos-pre));
                pre = pos;
            }
            v_data.push_back(request_data.substr(pre+1));
        }

        for (auto data : v_data){   
            string key = data.substr(0, data.find('='));
            string value = data.substr(data.find('=')+1);
            if (key == "exec"){ 
                if (value == "getproxy"){   
                    string header = "HTTP/1.1 404 OK\r\n";
                    header += "Connection: close\r\n";
                    header += "\r\n";
                    string data = "this is a proxy";
                    string response = header + data;
                    write_some(sock, header + response);
                }
            }
        }

        sock->close();
        /*
        char *next_buff = new char[buffer_size];
        async_read(*sock, 
                   buffer(next_buff, buffer_size), 
                   bind(&WebServer::read_complete, this, next_buff, _1, _2),
                   bind(&WebServer::read_handle, this, sock, next_buff, _1, _2));
        */
    }
    
};

}
}

// demo test
int main(){
    linukey::webserver::WebServer web;
    web.start();
    
    return 0;
}
