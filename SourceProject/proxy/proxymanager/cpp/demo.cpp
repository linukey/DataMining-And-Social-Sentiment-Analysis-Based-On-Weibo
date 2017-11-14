#include "include/proxy_update.h"

using namespace std;
using namespace linukey::proxy;

int main(){
	Proxy proxy(5, 
				"/home/linukey/WorkSpace/DataMining-And-Social-Sentiment-Analysis-Based-On-Weibo/SourceProject/proxy/proxy_ip",
				"/home/linukey/WorkSpace/DataMining-And-Social-Sentiment-Analysis-Based-On-Weibo/SourceProject/proxy/proxymanager/py/");
	proxy.update_proxy();
	

	return 0;
}
