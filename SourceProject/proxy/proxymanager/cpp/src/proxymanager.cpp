#include "/usr/include/python3.5m/Python.h"
#include "../include/proxymanager.h"
#include <fstream>
#include <set>

using namespace std;
using namespace linukey::proxy;

ProxyManager::ProxyManager(int proxy_num, 
             int proxy_min, 
             string proxyfile_path, 
             string pymodel_path):
			proxy_num(proxy_num), 
            proxy_min(proxy_min),
			proxyfile_path(proxyfile_path),
			pymodel_path(pymodel_path){}

int ProxyManager::init_proxypool(){
    // init the proxypool
    fstream fin(proxyfile_path);
    set<string> pp;
    if (fin.is_open()) {
        char buff[1024];
        while(!fin.eof()){  
            fin.getline(buff, sizeof(buff));
            string ip(buff);
            if (ip.length()){   
                pp.insert(ip);
            }
        }
    // if not find proxy_ip, throw a exception
    } else throw string("not find proxy_ip!");

    fin.close();

    set<string>::iterator it = pp.begin();
    for (; it != pp.end(); ++it){   
        proxypool.push(*it);
    }

    return proxypool.size();
}

int ProxyManager::update_proxyfile(){
    Py_Initialize();

    PyRun_SimpleString("import sys");
    PyRun_SimpleString(string("sys.path.append('" + pymodel_path + "')").c_str());

    PyObject* proxy_update = PyImport_ImportModule("proxy_update");
    if (!proxy_update){
        cerr << "import fail" << endl;
        return -1;
    }

    PyObject* update_proxy_ip = PyObject_GetAttrString(proxy_update, "update_proxy_ip");
    if (!update_proxy_ip || !PyCallable_Check(update_proxy_ip)){
        cerr << "load funtion fail" << endl;    
        return -1;
    }

    PyObject* args = PyTuple_New(2);
    PyObject* arg1 = PyLong_FromLong(proxy_num);
    PyObject* arg2 = PyBytes_FromString(proxyfile_path.c_str());

    PyTuple_SetItem(args, 0, arg1);
    PyTuple_SetItem(args, 1, arg2);

    PyObject* pRet = PyObject_CallObject(update_proxy_ip, args);
    
    if (!pRet){
        cerr << "run fail" << endl;
        return -1;
    }
    return 0;
}

string ProxyManager::get_ip(bool is_pre_valid){
    if (!is_pre_valid){
        proxypool.pop();
        if (proxypool.size() < proxy_min){
#ifdef WEBSERVER_DEBUG
            cerr << "update proxyfile..." << endl;
#endif
            update_proxyfile();
        }
    } else {
        string proxy = proxypool.front();
        proxypool.push(proxy);
        proxypool.pop();
    }
    return proxypool.front();
}
