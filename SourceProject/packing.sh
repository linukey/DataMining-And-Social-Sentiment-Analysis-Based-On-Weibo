SOURCE_NAME="weibo"
PACK_NAME="weibo.tgz"

rm ${PACK_NAME} 2>/dev/null

tar -zcvf  ${PACK_NAME} ${SOURCE_NAME}
