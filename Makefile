BUILD_DIR = build
SERVER_EXEC_NAME = r-type_server
CLIENT_EXEC_NAME = r-type_client

all:
	mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR} && cmake .. && make -s

lint:
	clang-tidy $$(find . -type f -name "*.[ch]pp" | grep -v "build")

clean:
	rm -rf ${SERVER_EXEC_NAME} ${CLIENT_EXEC_NAME}

fclean:
	make -s clean
	rm -rf ${BUILD_DIR}
	rm -rf compile_commands.json

clean_cache:
	make -s fclean
	rm -rf .cpm-cache .cache CPM_modules cpm-package-lock.cmake

re:
	make -s fclean
	make -s all

.PHONY: all lint clean fclean re
