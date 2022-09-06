FROM mowijo/cpp-cassandra-development:v2

RUN ( \
  cd /tmp && \
  git clone https://github.com/pistacheio/pistache.git pistache && \
  cd pistache && \
  mkdir build && \
  cd build && \
  cmake -GNinja ../ && \
  ninja && \
  cp -rf src/libpistache.* /usr/local/lib && \
  cp -rf /tmp/pistache/include/pistache/ /usr/local/include && \
  cd /tmp && \
  rm -rf pistache \
)

RUN ldconfig /etc/ld.so.conf.d

# git@github.com:mowijo/cpp-cassandra-pistache-development.git
