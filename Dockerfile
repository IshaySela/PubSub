FROM ubuntu:20.04

# install dependecies
RUN apt-get update && \
    apt-get install -y --no-install-recommends g++ && \
    apt-get install -y --no-install-recommends libssl-dev && \
    rm -rf /var/lib/apt/lists/*

# Copy the project.
COPY ./source ./source

RUN /usr/bin/g++ -g $(find ./source -type f -iregex '.*\.cpp') -o ./app -lssl -lcrypto -pthread

EXPOSE 8080

CMD [ "./app" ]