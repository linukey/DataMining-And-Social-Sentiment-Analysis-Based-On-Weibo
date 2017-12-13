#include "include/proxymanager.h"

using namespace std;
using namespace linukey::proxy;

int main(){
	ProxyManager proxy(5, 
                2,
				"/home/linukey/WorkSpace/DataMining-And-Social-Sentiment-Analysis-Based-On-Weibo/SourceProject/proxy/proxy_ip",
				"/home/linukey/WorkSpace/DataMining-And-Social-Sentiment-Analysis-Based-On-Weibo/SourceProject/proxy/proxymanager/py/");
	proxy.update_proxyfile();
    proxy.init_proxypool();
	

	return 0;
}
