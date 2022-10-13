FROM nginx

MAINTAINER Aleksey Kadnikov aka manhunte <manhunte@student.21-school.ru>

ENV TZ=Europe/Moscow

COPY ./entrypoint.sh /entry.sh
RUN apt update -y && \
    apt upgrade -y && \
    apt install -y \
    texinfo  \
    texlive  \
    texlive-lang-cyrillic && \
    chmod +x /entry.sh &&\
    mkdir /var/docs

ENTRYPOINT ["/entry.sh"]
