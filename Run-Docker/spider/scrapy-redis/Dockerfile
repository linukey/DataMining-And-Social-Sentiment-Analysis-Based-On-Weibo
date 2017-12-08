FROM ubuntu

# install python3 & python3-pip
RUN apt update \
&&  apt install python3 -y \
&&  apt install python3-pip -y \
# install vim
&&  apt install vim -y \
# install scrapy & scrapy-redis
&&  pip3 install scrapy \
&&  pip3 install scrapy-redis \
# clean
&&  rm -rf /var/lib/apt/lists/* \
&&  apt purge -y --auto-remove python3-pip \
