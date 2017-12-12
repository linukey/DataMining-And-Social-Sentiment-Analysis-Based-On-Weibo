#ifndef __FILE_UTILS_H__
#define __FILE_UTILS_H__

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <fstream>

using namespace std;

namespace linukey{
namespace utils{

static string read_all(const string& filename){
    ifstream fin(filename);
    if (fin.is_open()){
        fin.seekg(0, ios::end);
        int length = fin.tellg();
        fin.seekg(0, ios::beg);
        char* buff = new char[length];
        fin.read(buff, length);
        fin.close();
        return string(buff, length);
    }
    return "";
}

}
}

#endif
