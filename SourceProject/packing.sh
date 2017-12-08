SOURCE_NAME="spider"
PACK_NAME="spider.tgz"

rm ${PACK_NAME} 2>/dev/null

tar -zcvf  ${PACK_NAME} ${SOURCE_NAME}

SOURCE_NAME="proxy"
PACK_NAME="proxy.tgz"

rm ${PACK_NAME} 2>/dev/null

tar -zcvf  ${PACK_NAME} ${SOURCE_NAME}
