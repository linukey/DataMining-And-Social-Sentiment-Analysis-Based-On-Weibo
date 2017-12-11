#include "../include/spidermanager.h"
using namespace linukey::spidermanager;

void SpiderManager::update_spideritems(const string& client_id, const string& spidername, const string& time, int cnt){
    string pre_time;
    string cur_time = time;
    bool judge = false;
    if (spideritems[client_id].count(spidername)){
        auto& v = (*spideritems[client_id][spidername]);
        cnt += str2int(v[v.size()-1].second);

        pre_time = v[v.size()-1].first;
        decode_utf8_time(pre_time);       
        decode_utf8_time(cur_time);       

        vector<string> tmp1;
        vector<string> tmp2;

        split_by_key(pre_time, ' ', tmp1);
        pre_time = tmp1[1];
        split_by_key(pre_time, ':', tmp2);
        string pre_min = tmp2[1];

        split_by_key(cur_time, ' ', tmp1);
        cur_time = tmp1[1];
        split_by_key(cur_time, ':', tmp2);
        string cur_min = tmp2[1];

        if (pre_min == cur_min) judge = true;
    } else {
        spideritems[client_id][spidername] = new vector<pair<string, string>>();
    }
    if (judge) {
        auto& v = (*spideritems[client_id][spidername]);
        v[v.size()-1].second = int2str(cnt);
    } else spideritems[client_id][spidername]->push_back(pair<string, string>(time, int2str(cnt)));
}

void SpiderManager::get_spideritems(string& result){
    result = "{";
    auto cit = spideritems.begin();
    for (; cit != spideritems.end();){
        string client_id = cit->first;
        result += "\"" + client_id + "\":{";
        auto sit = cit->second.begin();
        for (; sit != cit->second.end();){
            string spidername = sit->first;
            result += "\"" + spidername + "\":{";
            for (unsigned i = 0; i < sit->second->size();){
                string time = (*sit->second)[i].first;    
                string cnt  = (*sit->second)[i].second;
                if (++i == sit->second->size()) result += "\"" + time + "\":" + "\"" + cnt + "\"";
                else result += "\"" + time + "\":" + "\"" + cnt + "\",";
            }    
            if (++sit == cit->second.end()) result += "}";
            else result += "},";
        }
        if (++cit == spideritems.end()) result += "}";
        else result += "},";
    }
    result += "}";
}
