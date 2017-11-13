#ifndef __LINUKEY_WEBSERVER_REQUEST__
#define __LINUKEY_WEBSERVER_REQUEST__

namespace linukey{  
namespace webserver{    
namespace request{

enum REQUEST_EXEC_{   
    GET_PROXY = 0,
};

static std::vector<std::string> REQUEST_EXEC = {  
    "getproxy", // get a proxy ip
};

static const std::string DATAEND = "%0A%0A=%0A%0A";

static const std::string HEADER =   "HTTP/1.1 200 OK\r\n"\
                                    "Connection: close\r\n"\
                                    "\r\n";

}
}
}

#endif
