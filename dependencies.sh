#!/bin/sh

# Install g++
RUN apt-get update && \
    apt-get -y install gcc mono-mcs && \
    rm -rf /var/lib/apt/lists/*

# Install openssl
sudo apt-get install libssl