#ifndef __SPIDERMANAGER_H__
#define __SPIDERMANAGER_H__

#include <iostream>
#include <deque>
#include <map>

using namespace std;

namespace linukey{
namespace spidermanager{

class SpiderManager{
private:
    // client_id    spidername item_cnt
    map<string, map<string, int>> spideritems;

public:
    SpiderManager(){}
    void update_spideritems(const string& client_id, const string& spidername, const int& cnt);
    void get_spideritems(map<string, map<string, int>>& spideritems);

};

}
}

#endif
