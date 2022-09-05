FROM mowijo/cpp-cassandra-development:v1

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
  ldconfig && \
  cd /tmp && \
  rm -rf pistache \
)

# git@github.com:mowijo/cpp-cassandra-pistache-development.git
