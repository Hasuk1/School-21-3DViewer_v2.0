FROM debian:latest

RUN apt-get update; \
    apt-get upgrade; \
    apt-get install -y gcc g++ libgtest-dev valgrind make googletest build-essential

RUN mkdir /home/3d_viewer
WORKDIR /home/3d_viewer

COPY . /home/3d_viewer

USER root