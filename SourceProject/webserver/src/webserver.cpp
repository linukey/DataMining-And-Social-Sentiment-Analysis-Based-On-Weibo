/*
    author: linukey
    time: 2017.11.12
    ps:
*/

#include "../include/webserver.h"
#include "../include/request.h"
#include "../../utils/string_utils.h"
#include "../../utils/other_utils.h"
#include <fstream>
#include <set>
#include <string>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <vector>

using namespace std;
using namespace boost::asio;
using namespace linukey::webserver;
using namespace linukey::webserver::request;
using namespace linukey::proxy;
using namespace linukey::utils;

#define WEBSERVER_DEBUG

WebServer::WebServer() : ACCEPTOR(SERVICE, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8001)) {
    proxymanager = new ProxyManager(1, 1, 
    "../proxymanager/proxyfile",
    "../proxymanager/py");

    proxymanager->update_proxyfile();
    proxymanager->init_proxypool();
}

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

#ifdef WEBSERVER_DEBUG
    ip::tcp::endpoint remote_ep = sock->remote_endpoint();
    ip::address remote_ad = remote_ep.address();
    cerr << "主机: " << remote_ad.to_string() << " 发出请求..." << endl;
#endif

    char *buff = new char[buffer_size];       
    Request* req = new Request();
    async_read(*sock, 
               buffer(buff, buffer_size), 
               bind(&WebServer::read_complete, this, req, buff, _1, _2),
               bind(&WebServer::read_handle, this, req, sock, buff, _1, _2));

    run();
}

size_t WebServer::read_complete(Request* req, char *buff, const e_code& err, size_t size){
    if (err) {
        log("Fail");
        return 0;
    }
    string request(buff, size);
    if (req->method.empty()){
        cout << "no method" << endl;
        if (request.find("\r\n\r\n") != string::npos){
            extract_request(request, req);
            if (to_lower(req->method) == "get") return false;
            else if (to_lower(req->method) == "post"){
                stringstream ss(req->headers[REQUEST_HEADERS[CONTENT_LENGTH]]);
                int content_length;
                ss >> content_length;
                if (content_length == 0) return false;
                else return true;
            }
        } else return true;
    } else {
        cout << "yes method" << endl;
        string data = request.substr(request.find("\r\n\r\n") + 4);    
        stringstream ss(req->headers[REQUEST_HEADERS[CONTENT_LENGTH]]);
        int content_length;
        ss >> content_length;
        if (data.size() == content_length) {
            extract_datas(data, req->datas);
            return false;
        }
        else return true;
    }
}

void WebServer::read_handle(Request* req, shared_socket sock, char *buff, const e_code& err, size_t size){
    if (err){
        log("Fail");
        return;
    }
    delete[] buff;
    response(req, sock);
    sock->close();
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

void WebServer::response(Request* req, shared_socket sock){
    if (req->url == "/get_proxy"){
        const string& client_id = req->datas["client_id"];
        if (proxymanager->client_proxy_pool.count(client_id)){
            // judge the pre proxy is valid or unvalid, if the second > 30, we thank the pre proxy is unvalid
            double second = difftime(get_now_time(), proxymanager->clientmanager_pool[client_id]);
            if (second > 30) {
#ifdef WEBSERVER_DEBUG
                cerr << "time > 30s, throw away pre proxy..." << endl;
#endif
            } else {
                if (!proxymanager->proxypool_exists(proxymanager->client_proxy_pool[client_id]))
                    proxymanager->set_ip(proxymanager->client_proxy_pool[client_id]);
#ifdef WEBSERVER_DEBUG
                cerr << "time: " << second << endl;
#endif
            }
        }

        string proxy = proxymanager->get_ip();
        if (proxy.empty()){
            //pass
        }
        string response = HEADER + proxy;
        proxymanager->client_proxy_pool[client_id] = proxy;
        proxymanager->clientmanager_pool[client_id] = get_now_time();
        write_some(sock, response);
#ifdef WEBSERVER_DEBUG
        cerr << "响应proxy: " << proxy << endl;
#endif
    
    } else if (req->url == "/get_task"){
        string html = 
        "<html>" \
            "<head>" \
                "<title> crawl </title>" \
            "</head>" \
            "<body>" \
                "hello world" \
            "</body>" \
        "</html>" ;
        string response = HEADER + html;
        write_some(sock, response);
#ifdef WEBSERVER_DEBUG
        cerr << "响应task: " << response << endl;
#endif
    }
}

void WebServer::log(const string& message){
    cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << " " << message << endl;
}
