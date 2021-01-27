#!/bin/sh

/usr/bin/g++ -g $(find ./source -type f -iregex '.*\.cpp') -o ./app -lssl -lcrypto -pthread