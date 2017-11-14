#ifndef __UPDATE_PROXY_H__
#define __UPDATE_PROXY_H__

#include <iostream>

namespace linukey{
namespace proxy{

class Proxy{
private:
    int proxy_num;
    std::string proxy_path;
	std::string py_model_path;
public:
    /*
    * param proxy_num: the count of proxy we use
    * param proxy_path: the proxy_pool file path
    * return: the count of proxy actual
    */
    int update_proxy();
	Proxy(int proxy_num, std::string proxy_path, std::string py_model_path);
};

}// namespace proxy
}// namespace linukey

#endif
