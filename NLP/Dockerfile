From ubuntu
ARG DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install sudo -y

RUN adduser --disabled-password --gecos '' kseek
RUN adduser kseek sudo
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

RUN apt install git pip wget -y
RUN apt install jupyter -y