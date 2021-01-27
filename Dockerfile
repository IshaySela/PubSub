FROM ubuntu

COPY ./source ./source
COPY ./dependencies.sh ./dependencies.sh

RUN [ "./dependencies.sh" ]

EXPOSE 8080

CMD [ "./app" ]