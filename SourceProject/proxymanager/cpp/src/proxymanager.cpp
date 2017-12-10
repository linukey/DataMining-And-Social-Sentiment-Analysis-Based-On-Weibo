#include "/usr/include/python3.5m/Python.h"
#include "../include/proxymanager.h"
#include "../../../utils/other_utils.h"
#include <fstream>
#include <set>

using namespace std;
using namespace linukey::proxy;
using namespace linukey::utils;

ProxyManager::ProxyManager(int proxy_num, 
             int proxy_min, 
             string proxyfile_path, 
             string pymodel_path):
			proxy_num(proxy_num), 
            proxy_min(proxy_min),
            proxyfile_path(proxyfile_path),
			pymodel_path(pymodel_path){
    // create proxyfile
    fstream fin(proxyfile_path, ios::app);
    fin.close();
}

int ProxyManager::init_proxypool(){
    proxypool.clear();
    // init the proxypool
    set<string> pp;
    try{
        fstream fin(proxyfile_path);
        if (fin.is_open()) {
            while(!fin.eof()){  
                char buff[1024];
                fin.getline(buff, sizeof(buff));
                string ip(buff);
                if (ip.length()){
                    pp.insert(ip);
                }
            }
        // if not find proxyfile, throw a exception
        } else throw string("not find proxyfile!");
        fin.close();
    } catch (string ex){
        cerr << ex << endl;
        return 0;
    }
    

    set<string>::iterator it = pp.begin();
    for (; it != pp.end(); ++it){
        proxypool.push_back(*it);
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

    PyObject* update_proxyfile = PyObject_GetAttrString(proxy_update, "update_proxyfile");
    if (!update_proxyfile || !PyCallable_Check(update_proxyfile)){
        cerr << "load funtion fail" << endl;    
        return -1;
    }

    PyObject* args = PyTuple_New(2);
    PyObject* arg1 = PyLong_FromLong(proxy_num);
    PyObject* arg2 = PyBytes_FromString(proxyfile_path.c_str());

    PyTuple_SetItem(args, 0, arg1);
    PyTuple_SetItem(args, 1, arg2);

    PyObject* pRet = PyObject_CallObject(update_proxyfile, args);
    
    if (!pRet){
        cerr << "run fail" << endl;
        return -1;
    }
    return 0;
}

string ProxyManager::get_ip(const string& client_id){
    if (client_proxy_pool.count(client_id)){
        double second = difftime(get_now_time(), clientmanager_pool[client_id]);
        if (second < 30 && !proxypool_exists(client_proxy_pool[client_id])){
            set_ip(client_proxy_pool[client_id]);
        }
    }

    string proxy = proxypool.front();
    proxypool.pop_front();

    client_proxy_pool[client_id] = proxy;
    clientmanager_pool[client_id] = get_now_time();

    if (proxypool.size() < proxy_min){
        update_proxyfile();
        init_proxypool();
    }

    return proxy;
}

bool ProxyManager::set_ip(string proxy){
    proxypool.push_back(proxy);
    return true;   
}

int ProxyManager::get_proxypool_size(){
    return proxypool.size();   
}

bool ProxyManager::proxypool_exists(string proxy){
    auto it = proxypool.begin();
    for (; it != proxypool.end(); ++it){
        if (*it == proxy)
            return true;    
    }
    return false;
}
