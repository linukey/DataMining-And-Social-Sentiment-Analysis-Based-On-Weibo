/*
    author: linukey
    time: 2017.11.12
    ps:
*/

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <queue>
#include <fstream>
#include <map>
#include <set>
#include "../lib/include/http.h"
#include "../lib/include/webserver.h"
#include "../../proxymanager/cpp/include/proxymanager.h"
#include "../../spidermanager/include/spidermanager.h"
#include "../../utils/file_utils.h"

using namespace std;
using namespace linukey::webserver;
using namespace boost::asio;
using namespace linukey::webserver::http;
using namespace linukey::proxy;
using namespace linukey::utils;
using namespace linukey::spidermanager;


class MyServer : public WebServer {
public:
    MyServer() {
        proxymanager = new ProxyManager(10, 5, "../proxymanager/proxyfile", "../proxymanager/py");
        proxymanager->update_proxyfile();
        proxymanager->init_proxypool();
        spidermanager = new SpiderManager();
    }

    // 实现自己的路由
    void router(linukey::webserver::http::Request* req, shared_socket sock) override {
#ifdef WEBSERVER_DEBUG
        printf("%s request %s \n", req->host.c_str(), req->url.c_str());
#endif
        if (req->url == "/get_proxy"){
            const string& client_id = req->datas["client_id"];
            string proxy = proxymanager->get_ip(client_id);
            response(sock, proxy);

        } else if (req->url == "/get_task"){
            string task;
            spidermanager->get_spideritems(task);
            response(sock, task);

        } else if (req->url == "/update_spider"){
            string client_id = req->datas["client_id"];
            string spidername = req->datas["spidername"];
            string cnt = req->datas["cnt"];
            string time = req->datas["time"];
            if (client_id.empty() || spidername.empty() || cnt.empty() || time.empty()){
                response(sock, "report fail!");
            } else {
                stringstream ss(cnt);
                int cnt;
                ss >> cnt;
                spidermanager->update_spideritems(client_id, spidername, time, cnt);
                response(sock, "report success");
            }

        } else if (req->url == "/") {
            string filename = "resource/spiderManager.html";
            string html = read_all(filename);
            response(sock, html);

        } else {
            string filename = "resource" + req->url;
            string html = read_all(filename);
            if (html.empty()){
                response(sock, "404");
            } else {
                response(sock, html);
            }
        }

        delete req;
    }

    linukey::proxy::ProxyManager* proxymanager;
    linukey::spidermanager::SpiderManager* spidermanager;
};

int main(){
    MyServer server;
    server.run();
    
    return 0;
}
