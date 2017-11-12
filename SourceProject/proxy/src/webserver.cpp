/*
    author: linukey
    time: 2017.11.12
    ps:
*/

#include "../include/webserver.h"

using namespace std;
using namespace boost::asio;
using namespace linukey::webserver;

void WebServer::run(){    
    shared_socket sock(new ip::tcp::socket(SERVICE));
    ACCEPTOR.async_accept(*sock, boost::bind(&WebServer::accept_handle, this, sock, _1));
    SERVICE.run();
}

void WebServer::accept_handle(shared_socket sock, const e_code& err){
    if (err){
        cerr << "accept fail!" << endl;
        return;
    }

    char *buff = new char[buffer_size];       
    async_read(*sock, 
               buffer(buff, buffer_size), 
               bind(&WebServer::read_complete, this, buff, _1, _2),
               bind(&WebServer::read_handle, this, sock, buff, _1, _2));
    run();
}

size_t WebServer::read_complete(char *buff, const e_code& err, size_t size){
    if (err){
        cerr << "read_complete fail" << endl;
        return 0;
    }
    string info(buff, size);
    return info.find("dateend") == string::npos;
}

void WebServer::write_handle(const e_code& err, size_t size){
    if (err){
        cerr << "write fail!" << endl;
        return;
    }
}

void WebServer::write_some(shared_socket sock, string message) {
    sock->async_write_some(buffer(message), bind(&WebServer::write_handle, this, _1, _2));
}

void WebServer::read_handle(shared_socket sock, char *buff, const e_code& err, size_t size){
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
