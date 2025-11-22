BUILD_DIR = build
SERVER_EXEC_NAME = r-type_server
CLIENT_EXEC_NAME = r-type_client
DEBUG = Debug
RELEASE = Release

all: debug

define build
	cmake -B ${BUILD_DIR} -DCMAKE_BUILD_TYPE=$(1)
	cmake --build ${BUILD_DIR} -j 
endef

debug:
	$(call build,$(DEBUG))
	ln -s -f ${BUILD_DIR}/compile_commands.json .

release:
	$(call build,$(RELEASE))

lint:
	clang-tidy $$(find . -type f -name "*.[ch]pp" | grep -v "build")

format:
	clang-format -i $$(find . -type f -name "*.[ch]pp" | grep -v "build")

doc:
	cd doc && mdbook build

open_doc:
	cd doc && mdbook serve --open

clean:
	rm -rf ${SERVER_EXEC_NAME} ${CLIENT_EXEC_NAME}

fclean:
	make -s clean
	rm -rf ${BUILD_DIR}
	rm -rf compile_commands.json index.html

clean_cache:
	make -s fclean
	rm -rf .cpm-cache .cache CPM_modules cpm-package-lock.cmake

re:
	make -s fclean
	make -s all

.PHONY: all lint clean fclean re doc open_doc
