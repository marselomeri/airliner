#############################################################################
#
#   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name Windhover Labs nor the names of its 
#    contributors may be used to endorse or promote products derived 
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
#############################################################################

SPHINX_OPTS      ?=
SPHINX_BUILD     ?= sphinx-build
SPHINX_SOURCEDIR = .
SPHINX_BUILDDIR  = build/reference/default/docs
SPHINX_FSW_BUILD = reference/default
 
SHELL := /bin/bash

TARGET_PATHS := $(shell find config -maxdepth 2 -mindepth 2 -type d -path 'config/shared/*' -prune -o -exec expr {} : '[^/]*/\(.*\)' \; )
TARGET_NAMES := $(shell echo ${TARGET_PATHS} )

help::
	@echo $(TARGET_PATHS)
	@echo 'Specify a target to build.  Available targets are:'
	@for name in $(TARGET_NAMES); do \
            echo $$name; \
        done
	
.PHONY: help Makefile docs

$(TARGET_NAMES)::
	@echo 'Updating submodules'
	git submodule update --init --recursive
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
	(cd build/$$TARGET_PATH; cmake -DBUILDNAME:STRING=$$TARGET_PATH -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE CMAKE_BUILD_TYPE=Debug ../../..; $(MAKE) --no-print-directory);
	
	
docs-doxygen: 
	@echo 'Updating submodules'
	git submodule update --init --recursive
	mkdir -p build/${SPHINX_FSW_BUILD}; \
	(cd build/${SPHINX_FSW_BUILD}; cmake -DBUILDNAME:STRING=${SPHINX_FSW_BUILD} -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE CMAKE_BUILD_TYPE=Debug ../../..; make docs);


docs-sphinx: 
	@echo 'Updating submodules'
	git submodule update --init --recursive
	@echo 'Building $$SPHINX_FSW_BUILD.'
	mkdir -p build/${SPHINX_FSW_BUILD}; \
	(cd build/${SPHINX_FSW_BUILD}; cmake -DBUILDNAME:STRING=${SPHINX_FSW_BUILD} -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE CMAKE_BUILD_TYPE=Debug ../../..);
	@$(SPHINX_BUILD) -M html "$(SOURCE_DIR)" "$(SPHINX_BUILDDIR)" $(SPHINX_OPTS) -c build/$(SPHINX_FSW_BUILD)/docs $(O)
	@echo 'Completed'


docs: docs-doxygen docs-sphinx
	@echo 'Completed'
	

clean::
	rm -rf build