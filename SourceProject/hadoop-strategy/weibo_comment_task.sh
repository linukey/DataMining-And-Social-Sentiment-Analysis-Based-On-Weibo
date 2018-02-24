TASK_NAME=vip_group

HADOOP=/home/users/chenguodong02/influence/hadoop-client/hadoop/bin/hadoop
INPUT=/user/ccdb/rd/chenguodong02/weibo/input
OUTPUT=/user/ccdb/rd/chenguodong02/weibo/output

$HADOOP fs -rmr ${OUTPUT}

$HADOOP streaming \
    -input "${INPUT}" \
	-output "${OUTPUT}" \
    -jobconf mapred.job.name="$TASK_NAME" \
    -jobconf mapred.job.priority="HIGH" \
    -jobconf mapred.max.reduce.failures.percent="10" \
    -jobconf mapred.job.map.capacity="50" \
    -jobconf mapred.map.tasks="50" \
    -jobconf mapred.job.reduce.capacity="50" \
    -jobconf mapred.reduce.tasks="50" \
    -inputformat org.apache.hadoop.mapred.lib.NLineInputFormat \
    -file comment_strategy.py \
    -file weibocomment.py \
    -file weibouser.py \
    -file red.sh \
    -cacheArchive /user/ccdb/rd/chenguodong02/python.tgz#. \
    -mapper "cat" \
    -reducer "red.sh"
