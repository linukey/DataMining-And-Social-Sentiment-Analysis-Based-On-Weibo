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
namespace http{

struct Request{
    map<string, string> headers;
    map<string, string> datas;

    string host;
    string method;   
    string url;
    string protocol;
};

enum REQUEST_METHOD{
    GET = 0,
    POST
};

static vector<string> REQUEST_METHOD_STR = {
    "get",
    "post"  
};

enum REQUEST_HEADERS{
    CONTENT_LENGTH = 0,
};

static vector<string> REQUEST_HEADERS_STR = {
    "content-length",  
};

static const string HEADER = "HTTP/1.1 200 OK\r\n" \
                            "Connection: close\r\n" \
                            "Access-Control-Allow-Origin: *\r\n" \
                            "\r\n";

// help tools
void extract_header(const string& headers, const string& key, string& value);
void extract_datas(const string& req_datas, map<string, string>& datas);
void extract_request(const string& headers, Request* req);
void extract_request_line(const string& headers, map<string, string>& req_line);

}
}
}

#endif
