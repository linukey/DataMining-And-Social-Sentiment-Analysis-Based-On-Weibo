#include "../include/request.h"
#include "../../../utils/string_utils.h"
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <vector>

using namespace std;
using namespace linukey::utils;

namespace linukey{  
namespace webserver{    
namespace request{

void extract_header(const string& headers, const string& key, string& value){
    string result = to_lower(headers);
    size_t spos = result.find(key);
    if (spos == string::npos) return;
    size_t epos = result.find("\r\n", spos);
    string kv = result.substr(spos, epos-spos);
    size_t pos;
    while (kv.length() > 0 && (pos = kv.find(" ")) != string::npos) kv.erase(pos, 1);    
    vector<string> strs;
    split_by_key(kv, ':', strs);
    value = strs[1];
}

void extract_request_line(const string& headers, map<string, string>& result){
    string req_line = headers.substr(0, headers.find("\r\n"));
    vector<string> strs;
    split_by_key(req_line, ' ', strs);
    result["method"] = strs[0];
    result["url"] = strs[1];
    result["protocol"] = strs[2];
}

void extract_request(const string& headers, Request* req){
    map<string, string> req_line;
    extract_request_line(headers, req_line);
    req->method = req_line["method"];
    req->url = req_line["url"];
    req->protocol = req_line["protocol"];
    string key = REQUEST_HEADERS[CONTENT_LENGTH];
    extract_header(headers, key, req->headers[key]);
}

void extract_datas(const string& req_datas, map<string, string>& datas){
    if (!req_datas.length()) return;
    // split data by '&'
    vector<string> v_data;
    split_by_key(req_datas, '&', v_data);
    // split data k-v by '='
    for (auto data : v_data){   
        string key = data.substr(0, data.find('='));
        string value = data.substr(data.find('=')+1);
        datas[key] = value;
    }
}

}
}
}
