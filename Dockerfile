FROM fedora:latest

WORKDIR /home/mani/rtype/

ADD . .

RUN useradd mani

RUN chown -R mani:mani /home/mani

RUN dnf install -y automake git cmake gcc gcc-c++

USER mani

RUN make fclean clean server-release

# Expose port
EXPOSE 4242

# Run server
ENTRYPOINT ["./r-type_server", "-p", "4242", "-d"]
