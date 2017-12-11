#ifndef __SPIDERMANAGER_H__
#define __SPIDERMANAGER_H__

#include <iostream>
#include <deque>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include "../../utils/string_utils.h"

using namespace linukey::utils;
using namespace std;

namespace linukey{
namespace spidermanager{

class SpiderManager{
private:
    // client_id spidername time cnt
    map<string, map<string, vector<pair<string, string> >* > > spideritems;

public:
    SpiderManager(){}
    void update_spideritems(const string& client_id, const string& spidername, const string& time, int cnt);
    void get_spideritems(string& result);

};

}
}

#endif
