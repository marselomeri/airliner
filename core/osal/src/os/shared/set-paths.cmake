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
 
set(OSAL_SHARED_SRC 
    ${CMAKE_CURRENT_LIST_DIR}/osapi-binsem.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-clock.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-common.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-countsem.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-dir.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-errors.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-file.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-filesys.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-fpu.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-heap.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-idmap.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-interrupts.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-module.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-mutex.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-network.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-printf.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-queue.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-select.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-sockets.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-task.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-time.c
    ${CMAKE_CURRENT_LIST_DIR}/osapi-timebase.c
)
