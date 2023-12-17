FROM debian:latest

RUN apt-get update; \
    apt-get upgrade; \
    apt-get install -y gcc g++ libgtest-dev valgrind make googletest build-essential
    
RUN mkdir /home/smart_calc
WORKDIR /home/smart_calc

COPY . /home/smart_calc

USER root

ENTRYPOINT ["make", "valgrind"]