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
using namespace linukey::webserver::request;
using namespace linukey::proxy;

WebServer::WebServer() : ACCEPTOR(SERVICE, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8001)) {}

void WebServer::run(){    
    shared_socket sock(new ip::tcp::socket(SERVICE));
    ACCEPTOR.async_accept(*sock, boost::bind(&WebServer::accept_handle, this, sock, _1));
    SERVICE.run();
}

void WebServer::accept_handle(shared_socket sock, const e_code& err){
    if (err){
        log("Fail");
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
        log("Fail");
        return 0;
    }

    return string(buff, size).find(DATAEND) == string::npos;
}

void WebServer::write_handle(const e_code& err, size_t size){
    if (err){
        log("Fail");
        return;
    }
}

void WebServer::write_some(shared_socket sock, string message) {
    sock->async_write_some(buffer(message), bind(&WebServer::write_handle, this, _1, _2));
}

void WebServer::read_handle(shared_socket sock, char *buff, const e_code& err, size_t size){
    if (err){
        log("Fail");
        return;
    }

    // the dataend is %0A%0A=%0A%0A , plus & = 14
    string request(buff, size-14);
    delete[] buff;

    // response to client
    response(sock, request);

	// http_request, must close
    sock->close();
}

void WebServer::response(shared_socket sock, std::string request){  
    // get the request data
    vector<string> v_data;
    string request_data = request.substr(request.find("\r\n\r\n") + 4);

    // split data by '&'
    if (request_data.length()){
        size_t pos = string::npos;
        size_t pre = 0;
        while ((pos = request_data.find('&', pre+1)) != string::npos){ 
            v_data.push_back(request_data.substr(pre, pos-pre));
            pre = pos;
        }
        v_data.push_back(request_data.substr(pre+1));
    }

    // split data k-v by '='
    string client_id;
    string exec;
    bool is_pre_valid;
    for (auto data : v_data){   
        string key = data.substr(0, data.find('='));
        string value = data.substr(data.find('=')+1);
        if (key == "exec"){ 
            exec = value;
        } else if (key == "client_id") {    
            client_id = value;
        } else if (key == "is_pre_valid"){
            if (value == "0") is_pre_valid = false;
            else is_pre_valid = true;
        }
    }

    // if first request, distribution proxymanager and remember
    if (clientmanager_pool.count(client_id) == 0){
        clientmanager_pool[client_id] = 1;   
        proxymanager_pool[client_id] = new ProxyManager(5, 2, 
        "/home/linukey/WorkSpace/DataMining-And-Social-Sentiment-Analysis-Based-On-Weibo/SourceProject/proxy/proxy_ip",
        "/home/linukey/WorkSpace/DataMining-And-Social-Sentiment-Analysis-Based-On-Weibo/SourceProject/proxy/proxymanager/py/");
		// init proxyfile
		proxymanager_pool[client_id]->update_proxyfile();
		// init proxypool
		proxymanager_pool[client_id]->init_proxypool();

    // if not first, refresh live_time
    } else {
        clientmanager_pool[client_id] = 1;
    }

    // response base request_exec
    if (exec == REQUEST_EXEC[GET_PROXY]){   
        string proxy = proxymanager_pool[client_id]->get_ip(is_pre_valid);
        string response = HEADER + proxy;
        write_some(sock, response);
    }
}

void WebServer::log(const string& message){
    cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << " " << message << endl;
}
