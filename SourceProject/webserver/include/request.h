#ifndef __LINUKEY_WEBSERVER_REQUEST__
#define __LINUKEY_WEBSERVER_REQUEST__

#include <string>
#include <map>
#include <vector>
#include <set>

using std::string;
using std::map;
using std::vector;
using std::set;

namespace linukey{  
namespace webserver{    
namespace request{

enum REQUEST_EXEC_{   
    GET_PROXY = 0,
    GET_TASK,
};

static vector<string> REQUEST_EXEC = {  
    "getproxy", // get a proxy ip
    "gettask", // get crawl task state
};

enum REQUEST_METHOD_{
    GET = 0,
    POST
};

static vector<string> REQUEST_METHOD = {
    "get",
    "post"  
};

enum REQUEST_HEADERS_{
    CONTENT_LENGTH = 0,
};

static vector<string> REQUEST_HEADERS = {
    "content-length",  
};

static const string DATAEND = "%0A%0A=%0A%0A";

static const string HEADER =   "HTTP/1.1 200 OK\r\n"\
                                    "Connection: close\r\n"\
                                    "\r\n";

struct Request{
    Request(){}
    ~Request(){}
    map<string, string> headers;
    map<string, string> datas;

    string method;   
    string url;
    string protocol;
};

void extract_header(const string& headers, const string& key, string& value);
void extract_datas(const string& req_datas, map<string, string>& datas);
void extract_request(const string& headers, Request* req);
void extract_request_line(const string& headers, map<string, string>& req_line);

}
}
}

#endif
