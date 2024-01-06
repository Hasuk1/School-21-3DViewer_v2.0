FROM debian:latest

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y gcc g++ libgtest-dev valgrind make googletest build-essential lcov && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir /home/3d_viewer
WORKDIR /home/3d_viewer

COPY . /home/3d_viewer

USER root
