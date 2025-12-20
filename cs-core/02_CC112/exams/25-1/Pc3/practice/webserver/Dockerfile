FROM ubuntu:22.04

RUN apt-get update && \
  apt-get install -y \
  build-essential \
  cmake \
  libboost-system-dev \
  libboost-date-time-dev

COPY server.cpp /app/server.cpp

WORKDIR /app
RUN g++ -std=c++11 -pthread server.cpp -o server -lboost_system

EXPOSE 8080
CMD ["./server"]
