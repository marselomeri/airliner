SHELL := /bin/bash

TARGET_PATHS := $(shell find config -maxdepth 2 -mindepth 2 -type d -path 'config/shared/*' -prune -o -exec expr {} : '[^/]*/\(.*\)' \; )
TARGET_NAMES := $(shell echo ${TARGET_PATHS} )


help::
	@echo $(TARGET_PATHS)
	@echo 'Specify a target to build.  Available targets are:'
	@for name in $(TARGET_NAMES); do \
            echo $$name; \
        done
	

$(TARGET_NAMES)::
	@echo 'Building '$@'.'
	@idx=1; \
	for name in $(TARGET_NAMES); do \
            if [ "$$name" == "$@" ] ; then \
                break; \
            fi; \
            ((idx++)); \
        done; \
	TARGET_PATH=$$(echo ${TARGET_PATHS} | cut -d " " -f $$idx); \
	mkdir -p build/$$TARGET_PATH; \
	(cd build/$$TARGET_PATH; cmake -DBUILDNAME:STRING=$$TARGET_PATH -G"Eclipse CDT4 - Unix Makefiles" -DNATIVE_BUILD=${NATIVE_BUILD} -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE CMAKE_BUILD_TYPE=Debug ../../..; $(MAKE) -j 4);
	

clean::
	rm -rf build
