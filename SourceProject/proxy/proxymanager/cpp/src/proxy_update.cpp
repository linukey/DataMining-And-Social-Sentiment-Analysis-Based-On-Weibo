#include "/usr/include/python3.5m/Python.h"
#include "../include/proxy_update.h"

using namespace std;
using namespace linukey::proxy;

Proxy::Proxy(int proxy_num, string proxy_path, string py_model_path):
			proxy_num(proxy_num), 
			proxy_path(proxy_path),
			py_model_path(py_model_path){}

int Proxy::update_proxy(){
    Py_Initialize();

    PyRun_SimpleString("import sys");
    PyRun_SimpleString(string("sys.path.append('" + py_model_path + "')").c_str());

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
    PyObject* arg2 = PyBytes_FromString(proxy_path.c_str());

    PyTuple_SetItem(args, 0, arg1);
    PyTuple_SetItem(args, 1, arg2);

    PyObject* pRet = PyObject_CallObject(update_proxy_ip, args);
    
    if (!pRet){
        cerr << "run fail" << endl;
        return -1;
    }


    return 0;
}
