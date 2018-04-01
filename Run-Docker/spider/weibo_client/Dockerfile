FROM linukey/scrapy-redis

COPY spider.tgz /root
COPY run_crawl.sh /

RUN cd /root \
&&  tar -xzvf spider.tgz \
&&  rm spider.tgz \
