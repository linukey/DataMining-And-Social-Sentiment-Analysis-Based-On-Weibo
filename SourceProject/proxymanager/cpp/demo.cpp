#include "include/proxymanager.h"

using namespace std;
using namespace linukey::proxy;

int main(){
	ProxyManager proxy(5, 
                2,
				"/home/linukey/WorkSpace/DataMining-And-Social-Sentiment-Analysis-Based-On-Weibo/SourceProject/proxymanager/proxyfile",
				"/home/linukey/WorkSpace/DataMining-And-Social-Sentiment-Analysis-Based-On-Weibo/SourceProject/proxymanager/py");

	proxy.update_proxyfile();
    proxy.init_proxypool();

	return 0;
}
