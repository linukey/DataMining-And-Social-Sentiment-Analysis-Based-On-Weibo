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
};

}// namespace proxy
}// namespace linukey

#endif
