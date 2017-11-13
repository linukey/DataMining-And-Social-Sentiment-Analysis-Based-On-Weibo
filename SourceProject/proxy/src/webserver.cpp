/*
    author: linukey
    time: 2017.11.12
    ps:
*/

#include "../include/webserver.h"
#include "../include/request.h"
#include <fstream>
#include <set>

using namespace std;
using namespace boost::asio;
using namespace linukey::webserver;

WebServer::WebServer() : ACCEPTOR(SERVICE, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8001)) {
    fstream fin("./proxy_ip");
    set<string> proxy_pool;
    if (fin.is_open()) {
        char buff[1024];
        while(!fin.eof()){  
            fin.getline(buff, sizeof(buff));
            string ip(buff);
            if (ip.length()){   
                proxy_pool.insert(ip);
            }
        }
    } else throw string("not find proxy_ip!");
    set<string>::iterator it = proxy_pool.begin();
    for (; it != proxy_pool.end(); ++it){   
        proxy_unuse_pool.push(*it);
    }
}

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

    string request(buff, size);
    delete[] buff;

    // response to client
    response(sock, request);

    sock->close();
}

void WebServer::response(shared_socket sock, std::string request){  
    // unpack request data split '&'
    vector<string> v_data;
    string request_data = request.substr(request.find("\r\n\r\n") + 4);
    if (request_data.length()){
        size_t pos = string::npos;
        size_t pre = 0;
        while ((pos = request_data.find('&', pre+1)) != string::npos){ 
            v_data.push_back(request_data.substr(pre, pos-pre));
            pre = pos;
        }
        v_data.push_back(request_data.substr(pre+1));
    }

    string client_id;
    string exec;
    for (auto data : v_data){   
        string key = data.substr(0, data.find('='));
        string value = data.substr(data.find('=')+1);
        if (key == "exec"){ 
            exec = value;
        } else if (key == "client_id") {    
            client_id = value;
        }
    }

    // response base request_exec
    if (exec == REQUEST_EXEC[GET_PROXY]){   
        string header = "HTTP/1.1 200 OK\r\n";
        header += "Connection: close\r\n";
        header += "\r\n";

        string data = get_ip(client_id);
        if (data.empty()){  
            wait_client.push(pair<shared_socket, string>(sock, client_id));
            continue;
        }

        string response = header + data;
        write_some(sock, header + response);
    }
}

string WebServer::get_ip(const string& client_id){   
    string ip = proxy_client_ip[client_id];

    // put the ip not use into the pool
    if (!ip.empty()) {    
        proxy_unuse_pool.push(ip);
        proxy_client_ip[client_id].clear();

        if (!wait_client.empty()){  
            string header = "HTTP/1.1 200 OK\r\n";
            header += "Connection: close\r\n";
            header += "\r\n";

            string data = proxy_unuse_pool.front();
            proxy_unuse_pool.pop();

            string response = header + data;
            write_some(sock, header + response);
        }
    }
    if (proxy_unuse_pool.empty()){
        return "";
    }
    string top = proxy_unuse_pool.front();
    proxy_unuse_pool.pop();
    return proxy_client_ip[client_id] = top;
}
