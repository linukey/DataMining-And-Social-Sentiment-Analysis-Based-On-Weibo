/*
    author: linukey
    time: 2017.11.12
    ps:
*/

#include "../include/webserver.h"
#include "../include/request.h"
#include "../../utils/string_utils.h"
#include "../../utils/other_utils.h"
#include "../../utils/file_utils.h"
#include <fstream>
#include <set>
#include <string>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <vector>
#include <sstream>

using namespace std;
using namespace boost::asio;
using namespace linukey::webserver;
using namespace linukey::webserver::request;
using namespace linukey::proxy;
using namespace linukey::utils;
using namespace linukey::spidermanager;

#define WEBSERVER_DEBUG

WebServer::WebServer() : ACCEPTOR(SERVICE, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8001)) {
    proxymanager = new ProxyManager(10, 3, "../proxymanager/proxyfile", "../proxymanager/py");
    proxymanager->update_proxyfile();
    proxymanager->init_proxypool();
    spidermanager = new SpiderManager();
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
        string data = request.substr(request.find("\r\n\r\n") + 4);    
        stringstream ss(req->headers[REQUEST_HEADERS[CONTENT_LENGTH]]);
        int content_length;
        ss >> content_length;
        if (data.size() == content_length) {
            extract_datas(data, req->datas);
            return false;
        } else return true;
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
#ifdef WEBSERVER_DEBUG
        cout << "request:" << req->url << endl;
#endif
    if (req->url == "/get_proxy"){
        const string& client_id = req->datas["client_id"];
        string proxy = proxymanager->get_ip(client_id);
        string response = HEADER + proxy;
        write_some(sock, response);

    } else if (req->url == "/get_task"){
        string task;
        spidermanager->get_spideritems(task);
        string response = HEADER + task;
        write_some(sock, response);

    } else if (req->url == "/update_spider"){
        string client_id = req->datas["client_id"];
        string spidername = req->datas["spidername"];
        string cnt = req->datas["cnt"];
        string time = req->datas["time"];
        if (client_id.empty() || spidername.empty() || cnt.empty() || time.empty()){
            write_some(sock, HEADER + "report fail!");
        } else {
            stringstream ss(cnt);
            int cnt;
            ss >> cnt;
            spidermanager->update_spideritems(client_id, spidername, time, cnt);
            write_some(sock, HEADER + "report succes!");
        }

    } else if (req->url == "/") {
        string filename = "html/spiderManager.html";
        string html = read_all(filename);
        write_some(sock, HEADER + html);

    } else {
        string filename = "html" + req->url;
        string html = read_all(filename);
        if (html.empty()){
            write_some(sock, HEADER + "403");
        } else {
            write_some(sock, HEADER + html);
        }
    }

    delete req;
}

void WebServer::log(const string& message){
    cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << " " << message << endl;
}
