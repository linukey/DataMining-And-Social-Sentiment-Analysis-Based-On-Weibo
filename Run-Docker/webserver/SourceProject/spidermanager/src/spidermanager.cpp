#include "../include/spidermanager.h"
using namespace linukey::spidermanager;

void SpiderManager::update_spideritems(const string& client_id, const string& spidername, const string& time, int cnt){
    string pre_time;
    string cur_time = time;
    bool judge = false;
    if (spideritems[client_id].count(spidername)){
        auto& v = (*spideritems[client_id][spidername]);
        cnt += str2int(v[v.size()-1].second);

        pre_time = v[v.size()-1].first; decode_utf8_time(pre_time);
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
    } else {
        cur_time = time;
        decode_utf8_time(cur_time);
        spideritems[client_id][spidername]->push_back(pair<string, string>(cur_time, int2str(cnt)));
    }
}

/*
[
    {
        "client-id":"client-one"
        "spiders":[
                    {
                        "spidername":"spider-one",
                        "items":[
                                    {"time":"2016-10-11 12:01", "value":"80"},
                                    {"time":"2016-10-12 12:01", "value":"90"}
                                ]
                    },
                    {
                        "spidername":"spider-two"
                        "items":[
                                    {"time":"2016-10-11 12:01", "value":"80"},
                                    {"time":"2016-10-12 12:01", "value":"90"}
                                ]
                    }
                  ]
    },
    [...]
]
*/

void SpiderManager::get_spideritems(string& result){
    result = "[";
    auto cit = spideritems.begin();
    for (; cit != spideritems.end();){
        string client_id = cit->first;
        result += "{\"client-id\":\""+client_id+"\",\"spiders\":";
        result += "[";

        auto sit = cit->second.begin();
        for (; sit != cit->second.end();){
            string spidername = sit->first;
            result += "{\"spider-name\":\"" + spidername + "\",\"items\":";
            result += "[";
            for (unsigned i = 0; i < sit->second->size();){
                string time = (*sit->second)[i].first;    
                string cnt  = (*sit->second)[i].second;
                if (++i == sit->second->size()) 
                    result += "{\"time\":\"" + time + "\",\"value\":\"" + cnt + "\"}";
                else 
                    result += "{\"time\":\"" + time + "\",\"value\":\"" + cnt + "\"},";
            }
            result += "]";
            if (++sit == cit->second.end()) result += "}";
            else result += "},";
        }

        result += "]";
        if (++cit == spideritems.end()) result += "}";
        else result += "},";
    }
    result += "]";
}
