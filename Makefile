BUILD_DIR = build
SERVER_EXEC_NAME = r-type_server
CLIENT_EXEC_NAME = r-type_client

all:
	mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR} && cmake .. && make -s

clean:
	rm -rf ${SERVER_EXEC_NAME} ${CLIENT_EXEC_NAME}

fclean:
	make -s clean
	rm -rf ${BUILD_DIR}

re:
	make -s fclean
	make -s all
