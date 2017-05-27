SHELL := /bin/bash

TARGET_PATHS := $(shell find config -maxdepth 2 -mindepth 2 -type d -path 'config/shared/*' -prune -o -exec expr {} : '[^/]*/\(.*\)' \; )
TARGET_NAMES := $(shell echo ${TARGET_PATHS} | tr / _ )


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
	mkdir -p build/$$TARGET_PATH/host; \
	(cd build/$$TARGET_PATH/host; cmake -DBUILDNAME:STRING=$$TARGET_PATH -DBUILD_TARGET:STRING=HOST ../../../..; $(MAKE) -j);\
	mkdir -p build/$$TARGET_PATH/target; \
	(cd build/$$TARGET_PATH/target; cmake -DBUILDNAME:STRING=$$TARGET_PATH -DBUILD_TARGET:STRING=TARGET ../../../..; $(MAKE) -j);
	

clean::
	rm -rf build
