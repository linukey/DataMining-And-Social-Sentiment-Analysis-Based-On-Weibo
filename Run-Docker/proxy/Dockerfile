FROM linukey/webserver

COPY proxy.tgz /
COPY start-server.sh /

RUN cd / \
&&  tar -xzvf proxy.tgz \
&&  rm proxy.tgz \
&&  apt-get update \
&&  apt-get install python3-pip -y \
&&  pip3 install requests \
&&  cd /usr/lib \
&&  ln -s /usr/lib/python3.5/config-3.5m-x86_64-linux-gnu/libpython3.5.so libpython3.5.so \
&&  ln -s /proxy/proxymanager/cpp/libproxy.so libproxy.so \
&&  cd /proxy \
&&  sh build.sh \
