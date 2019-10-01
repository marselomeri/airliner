"""
 
    Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
 
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
 
  1. Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
  3. Neither the name Windhover Labs nor the names of its contributors 
     may be used to endorse or promote products derived from this software
     without specific prior written permission.
 
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.

"""

__author__ = 'Mathew Benson'

""" 
Utilities for parsing and returning the CFE Table Name from a json file.

Usage:
python get_table_name.py [path to json file]
"""

import sys
import json
import os

CONFIG_FILE_NAME = 'config.json'

def mergeParentConfig(mergedConfig, absConfigBase, absCurrentDir):
    # Can we go further up?
    if absCurrentDir != absConfigBase:
        # Yes.  Go further.  Get the parent directory of the current directory
        absParentPath = os.path.abspath(os.path.join(absCurrentDir, '..'))
        
        # Merge the parent object
        mergedConfig = mergeParentConfig(mergedConfig, absConfigBase, absParentPath)
    
    # Now merge the current config file.  First, is there even a configuration 
    # file here?
    cfgFileNameCurrent = os.path.join(absCurrentDir, CONFIG_FILE_NAME)
    if os.path.exists(cfgFileNameCurrent):
        # It does exist.  Now load it.
        with open(cfgFileNameCurrent, 'r') as cfgFileCurrent:
            # Load the JSON object.
            cfgCurrent = json.load(cfgFileCurrent)
            
            # Iterate through the module objects, so we only merge in what the 
            # local configuration file defined as being part of the build.  In other
            # words, if this current configuration file defines module 'xyz', but
            # the local configuration file does not, don't merge that module in.
            for module_name in mergedConfig['modules']:
                # Is this module in the configuration file we're about to merge?
                if module_name in cfgCurrent['modules']:
                    # It is.  Merge it.
                    merge(cfgCurrent['modules'][module_name], mergedConfig['modules'][module_name])
    
    return mergedConfig
    

def merge(source, destination):
    """
    run me with nosetests --with-doctest file.py

    >>> a = { 'first' : { 'all_rows' : { 'pass' : 'dog', 'number' : '1' } } }
    >>> b = { 'first' : { 'all_rows' : { 'fail' : 'cat', 'number' : '5' } } }
    >>> merge(b, a) == { 'first' : { 'all_rows' : { 'pass' : 'dog', 'fail' : 'cat', 'number' : '5' } } }
    True
    """
    for key, value in source.items():
        if isinstance(value, dict):
            # get node or create one
            node = destination.setdefault(key, {})
            merge(value, node)
        else:
            destination[key] = value

    return destination


# Load the local configuration file
if len(sys.argv) == 2:
    localConfigFileName = sys.argv[1]
    with open(localConfigFileName, 'r') as localConfigFile:
        localConfig = json.load(localConfigFile)
    
        # Iterate through the modules
        for module_name in localConfig['modules']:
            objModule = localConfig['modules'][module_name]
        
            # Get the definition base path
            defPath = objModule['definition']
        
            # Open the definition file for this module
            with open(defPath, 'r') as defFile:
                defObj = json.load(defFile)
            
                # Deep merge this definition object into the 'module/<name>/' object of the local config.
                merge(defObj, objModule)
    
        # Get the base directory, i.e. "../../../.."
        configBase = localConfig['config_base']
        
        # Get the absolute path of the base directory, i.e. "/home/mbenson/git/airliner"
        absConfigBase = os.path.abspath(configBase)
    
        # Get absolute directory of the local config file, 
        # i.e. "/home/mbenson/git/airliner/config/bebop2/sitl/target"
        absLocalDir = os.path.dirname(os.path.abspath(localConfigFileName))
    
        # Recursively merge config files from the parent, starting with the config base
        localConfig = mergeParentConfig(localConfig, absConfigBase, absLocalDir)
        
        print json.dumps(localConfig, indent=4)