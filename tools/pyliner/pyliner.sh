#!/usr/bin/env bash

# Taken from https://www.ostricher.com/2014/10/the-right-way-to-get-the-directory-of-a-bash-script/
get_script_dir () {
     SOURCE="${BASH_SOURCE[0]}"
     # While $SOURCE is a symlink, resolve it
     while [ -h "$SOURCE" ]; do
          DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
          SOURCE="$( readlink "$SOURCE" )"
          # If $SOURCE was a relative symlink (so no "/" as prefix, need to resolve it relative to the symlink base directory
          [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE"
     done
     DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
     echo "$DIR"
}

PYLINER_DIR=$(get_script_dir)
export PYTHONPATH="${PYTHONPATH:+${PYTHONPATH}:}${PYLINER_DIR}"
PYTHON=python

source venv/bin/activate
if [ -z "$1" ]; then
    ${PYTHON} -i $PYLINER_DIR/interactive.py
else
    ${PYTHON} $@
fi
deactivate