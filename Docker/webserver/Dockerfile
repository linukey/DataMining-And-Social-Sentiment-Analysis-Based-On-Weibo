FROM linukey/webserver

COPY proxy.tgz /

RUN cd / \
&&  tar -xzvf proxy.tgz \
&&  rm proxy.tgz \
&&  cd /usr/lib \
&&  ln -s /usr/lib/python3.5/config-3.5m-x86_64-linux-gnu/libpython3.5.so libpython3.5.so \
&&  cd /proxy \
&&  sh build.sh \
