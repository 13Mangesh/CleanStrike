FROM frolvlad/alpine-gxx

WORKDIR /usr/src/CleanStrike

RUN apk add cmake &&\
    apk add make

COPY . .

RUN mkdir build &&\
    cd build

RUN cmake . . &&\
    make

RUN cd ..

RUN chmod +x ./dockerCommands.sh

CMD [ "./dockerCommands.sh" ]