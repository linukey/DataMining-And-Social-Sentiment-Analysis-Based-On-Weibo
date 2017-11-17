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

time_t WebServer::get_now_time(){
    return time(NULL);
}

void WebServer::accept_handle(shared_socket sock, const e_code& err){
    if (err){
        log("Fail");
        return;
    }
    
#ifdef WEBSERVER_DEBUG
    ip::tcp::endpoint remote_ep = sock->remote_endpoint();
    ip::address remote_ad = remote_ep.address();
    cerr << "主机: " << remote_ad.to_string() << " 请求proxy..." << endl;
#endif

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
    for (auto data : v_data){   
        string key = data.substr(0, data.find('='));
        string value = data.substr(data.find('=')+1);
        if (key == "exec"){ 
            exec = value;
        } else if (key == "client_id") {    
            client_id = value;
        }
    }

    bool is_pre_valid = true;
    // if first request, distribution proxymanager and remember
    if (clientmanager_pool.count(client_id) == 0){
        proxymanager_pool[client_id] = new ProxyManager(5, 2, 
        "/home/linukey/WorkSpace/DataMining-And-Social-Sentiment-Analysis-Based-On-Weibo/SourceProject/proxy/proxy_ip",
        "/home/linukey/WorkSpace/DataMining-And-Social-Sentiment-Analysis-Based-On-Weibo/SourceProject/proxy/proxymanager/py/");

#ifdef WEBSERVER_DEBUG
        cerr << "this is a new request, update proxyfile and dispach proxymanager..." << endl;
#endif
		// init proxyfile
		proxymanager_pool[client_id]->update_proxyfile();
		// init proxypool
		proxymanager_pool[client_id]->init_proxypool();

    // if not first, judge pre proxy is valid
    } else {
        // judge the pre proxy is valid or unvalid
        // if the second > 30, we thank the pre proxy is unvalid
        time_t now = get_now_time();
        time_t old = clientmanager_pool[client_id];
        double second = difftime(now, old);
        if (second > 30) {
            is_pre_valid = false;
#ifdef WEBSERVER_DEBUG
            cerr << "time > 30s, throw away pre proxy..." << endl;
#endif
        } else {
#ifdef WEBSERVER_DEBUG
            cerr << "time: " << second << endl;
#endif
        }
    }

    // response base request_exec
    if (exec == REQUEST_EXEC[GET_PROXY]){   
        string proxy = proxymanager_pool[client_id]->get_ip(is_pre_valid);
        string response = HEADER + proxy;
        clientmanager_pool[client_id] = get_now_time();
        write_some(sock, response);
#ifdef WEBSERVER_DEBUG
        cerr << "响应proxy: " << proxy << endl;
#endif
    }
}

void WebServer::log(const string& message){
    cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << " " << message << endl;
}
