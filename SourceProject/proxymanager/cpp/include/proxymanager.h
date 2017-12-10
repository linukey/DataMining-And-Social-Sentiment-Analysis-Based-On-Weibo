#ifndef __UPDATE_PROXY_H__
#define __UPDATE_PROXY_H__

#include <iostream>
#include <deque>
#include <map>

namespace linukey{
namespace proxy{

class ProxyManager{
private:
    /* construct */
    int proxy_num;
    int proxy_min;
    std::string proxyfile_path;
	std::string pymodel_path;

    std::deque<std::string> proxypool;

public:
    int update_proxyfile();
    int init_proxypool();
    int get_proxypool_size();
    bool proxypool_exists(std::string proxy);
    std::string get_ip();
    bool set_ip(std::string proxy);
	ProxyManager(int proxy_num, int proxy_min, std::string proxyfile_path, std::string py_model_path);

    // key=client_id value=proxy
    std::map<std::string, std::string> client_proxy_pool;
    // key=client_id value=live_time
    std::map<std::string, time_t> clientmanager_pool;

};

}// namespace proxy
}// namespace linukey

#endif
