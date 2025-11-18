BUILD_DIR = build
SERVER_EXEC_NAME = r-type_server
CLIENT_EXEC_NAME = r-type_client
SRC_FILES := $(shell find . -type f -name "*.[ch]pp" | grep -v "build")

all:
	mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR} && cmake .. && make -s

lint:
	@for file in $(SRC_FILES); do \
		clang-tidy $$file; \
	done

clean:
	rm -rf ${SERVER_EXEC_NAME} ${CLIENT_EXEC_NAME}

fclean:
	make -s clean
	rm -rf ${BUILD_DIR}

clean_cache:
	make -s fclean
	rm -rf .cpm-cache .cache

re:
	make -s fclean
	make -s all
