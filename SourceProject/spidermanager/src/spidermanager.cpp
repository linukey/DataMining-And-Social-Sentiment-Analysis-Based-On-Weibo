#include "../include/spidermanager.h"

using namespace linukey::spidermanager;

void SpiderManager::update_spideritems(const string& client_id, const string& spidername, const int& cnt){
    spideritems[client_id][spidername] += cnt;
}

void SpiderManager::get_spideritems(map<string, map<string, int>>& spideritems){
    spideritems = this->spideritems;
}
