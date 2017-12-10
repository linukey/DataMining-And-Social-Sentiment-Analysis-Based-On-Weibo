#include "string_utils.h"
#include "other_utils.h"

using namespace linukey::utils;

int main(){
    //string str = "&&data=haha&&*&&method=get&&";
    string str = "asdfsdf";
    vector<string> result;
    split_by_key(str, '&', result);
    for (int i = 0; i < result.size(); ++i){
        cout << result[i] << endl;
    }

    
    return 0;
}
