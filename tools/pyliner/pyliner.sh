#!/usr/bin/env bash

# Wrapper to set up Pyliner environment and clean up after execution.
#
# Usage: bash pyliner.sh [script]
#
# If script is given Pyliner will execute the script after environment setup. Otherwise Pyliner will execute
#   interactive.py, which sets up a basic vehicle named "rocky".
#
# If a virtual environment is given, Pyliner will use it. If a script
#
# All Pyliner environment variables may be set before script execution or they will default to a value.
# Pyliner Environment Variables:
#   PYLINER_DIR     Directory to Pyliner, default to script directory.
#   PYLINER_PYTHON  Python executable to run, default to `python`.
#   PYLINER_VENV    Path to Pyliner virtual environment, if one is configured. Default to PYLINER_DIR/venv.
# Modified Environment Variables:
#   PYTHONPATH      Pyliner appends the Pyliner directory to allow import of Pyliner code.

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

# Get the directory of this script, which should be in the same place as Pyliner by default.
: ${PYLINER_DIR:=$(get_script_dir)}
# Append the current directory to the Python path so that Pyliner is accessible.
export PYTHONPATH="${PYTHONPATH:+${PYTHONPATH}:}${PYLINER_DIR}"
# Choose the variant of Python to run.
: ${PYLINER_PYTHON:=python}
# If PYLINER_VENV is unset, look for pyliner/venv by default.
: ${PYLINER_VENV:=${PYLINER_DIR}/venv}

# Look for a virtual environment and use it.
if [[ -d ${PYLINER_VENV} ]]; then
    echo "Found virtual environment."
    source ${PYLINER_VENV}/bin/activate
else
    echo "No virtual environment. Using system environment."
fi

# If a script was passed, execute it. Otherwise execute interactive.py
if [ -n "$1" ]; then
    ${PYLINER_PYTHON} $@
else
    ${PYLINER_PYTHON} -i $PYLINER_DIR/interactive.py
fi

# Deactivate the virtual environment
if [[ -d ${PYLINER_VENV} ]]; then
    deactivate
fi
