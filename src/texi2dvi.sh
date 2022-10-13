#!/bin/bash

#docker rm -f tex2dvi && \
docker rmi -f manhunte/tex2dvi:v1
docker build . -t manhunte/tex2dvi:v1 -f ./Dockerfile
docker run --name tex2dvi --rm -v "`pwd`/docs":/var/docs -w /var/docs manhunte/tex2dvi:v1
