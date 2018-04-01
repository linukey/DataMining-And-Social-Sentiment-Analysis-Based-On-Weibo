SOURCE_NAME="../SourceProject/spider"
PACK_NAME="spider/weibo_client/spider.tgz"

rm ${PACK_NAME} 2>/dev/null
tar -zcvf  ${PACK_NAME} ${SOURCE_NAME}

SOURCE_NAME="../SourceProject/server-tool ../SourceProject/proxymanager ../SourceProject/spidermanager ../SourceProject/utils"
PACK_NAME="webserver/server-tool.tgz"

rm ${PACK_NAME} 2>/dev/null
tar -zcvf  ${PACK_NAME} ${SOURCE_NAME}
