FROM linukey/scrapy-redis

COPY weibo.tgz /root
COPY run_crawl.sh /
COPY pause_crawl.sh /

RUN cd /root \
&&  tar -xzvf weibo.tgz \
&&  rm weibo.tgz \
