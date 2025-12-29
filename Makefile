BUILD_DIR = build
SERVER_EXEC_NAME = r-type_server
CLIENT_EXEC_NAME = r-type_client
NETWORK_TEST_EXEC_NAME = reseauTypeTester
DEBUG = Debug
RELEASE = Release
ON = ON
OFF = OFF

all: debug

define build
	cd $(1) && \
	cmake -B ${BUILD_DIR} \
		-DCMAKE_BUILD_TYPE=$(2) \
	&& cmake --build ${BUILD_DIR} $(3) -j 
endef

debug:
	$(call build,server,$(DEBUG))
	$(call build,client,$(DEBUG))

release:
	$(call build,server,$(RELEASE))
	$(call build,client,$(RELEASE))

server:
	$(call build,server,$(DEBUG))

client:
	$(call build,client,$(DEBUG))

reseau:
	$(call build,server,$(DEBUG),--target reseau)

lint:
	clang-tidy $$(find . -type f -name "*.[ch]pp" | grep -v "build")

format:
	clang-format -i $$(find . -type f -name "*.[ch]pp" | grep -v "build")

doc:
	cd doc && mdbook build

open_doc:
	cd doc && mdbook serve --open

clean:
	rm -rf ${SERVER_EXEC_NAME} ${CLIENT_EXEC_NAME} ${NETWORK_TEST_EXEC_NAME}

fclean:
	make -s clean
	rm -rf server/${BUILD_DIR}
	rm -rf client/${BUILD_DIR}
	rm -rf index.html

clean_cache:
	make -s fclean
	rm -rf .cpm-cache .cache CPM_modules cpm-package-lock.cmake

re:
	make -s fclean
	make -s all

.PHONY: all lint clean fclean re doc open_doc reseau server client
