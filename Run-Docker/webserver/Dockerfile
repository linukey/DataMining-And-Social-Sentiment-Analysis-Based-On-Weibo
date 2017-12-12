FROM linukey/webserver

COPY webserver.tgz /
COPY start-server.sh /

RUN cd / \
&&  tar -xzvf webserver.tgz \
&&  rm webserver.tgz \
&&  apt-get update \
&&  apt-get install python3-pip -y \
&&  pip3 install requests \
&&  cd /usr/lib \
&&  ln -s /usr/lib/python3.5/config-3.5m-x86_64-linux-gnu/libpython3.5.so libpython3.5.so \
&&  cd /SourceProject/webserver \
&&  sh build.sh \
&&  cd /usr/lib \
&&  ln -s /SourceProject/proxymanager/cpp/libproxy.so libproxy.so \
&&  ln -s /SourceProject/spidermanager/libspidermanager.so libspidermanager.so \
