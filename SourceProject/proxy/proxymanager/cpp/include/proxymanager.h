#ifndef __UPDATE_PROXY_H__
#define __UPDATE_PROXY_H__

#include <iostream>
#include <queue>
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

    std::queue<std::string> proxypool;

public:
    int update_proxyfile();
    int init_proxypool();
    std::string get_ip(bool is_pre_valid);
	ProxyManager(int proxy_num, int proxy_min, std::string proxyfile_path, std::string py_model_path);
};

}// namespace proxy
}// namespace linukey

#endif
