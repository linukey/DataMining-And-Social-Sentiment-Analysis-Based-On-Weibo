HADOOP_HOME=
STREAMING_HOME=

INPUT=/user/linukey/input
OUTPUT=/user/linukey/output

WORK_DIR=weibo_comment_task

${HADOOP_HOME}/bin/hadop fs -rmr ${OUTPUT}

${HADOOP_HOME}/bin/hadoop jar ${STREAMING_HOME}/hadoop-streaming.jar \
    -jobconf mapred.job.name="weibo_comment_extract" \
    -jobconf mapred.job.priority="HIGH" \
    -jobconf mapred.job.map.capacity="2" \
    -jobconf mapred.job.reduce.capacity="2" \
    -jobconf mapred.map.tasks="2" \
    -jobconf mapred.reduce.tasks="2" \

    -file ${WORK_DIR}/map.sh \
    -file ${WORK_DIR}/red.sh \
    -file ${WORK_DIR}/weibocomment.sh \
    -file ${WORK_DIR}/weibouser.sh \
    -file ${WORK_DIR}/comment_strategy.sh \

    -input ${INPUT} \
    -output ${OUTPUT} \

    -mapper "sh map.sh" \
    -reducer "sh red.sh"
