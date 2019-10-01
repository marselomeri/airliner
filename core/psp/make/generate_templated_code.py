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
import jinja2

# Load the local configuration file
if len(sys.argv) == 3:
    configFileName = sys.argv[1]
    outputPath = sys.argv[2]
    with open(configFileName, 'r') as configFile:
        config = json.load(configFile)
        
        # Iterate through the modules
        for module_name in config['modules']:
            objModule = config['modules'][module_name]
            
            # Get the base directory of the definition file
            dirBase = os.path.abspath(os.path.dirname(objModule['definition']))
            
            # Iterate through the code_templates 
            for code_template_name in objModule['code_templates']:
                objCodeTemplate = objModule['code_templates'][code_template_name]
                
                # Get the template directory
                dirTemplate = os.path.dirname(os.path.join(dirBase, objCodeTemplate['template']))
                
                # Get the template filename
                fileNameTemplate = os.path.basename(objCodeTemplate['template'])
                
                j2_env = jinja2.Environment(loader=jinja2.FileSystemLoader(dirTemplate), trim_blocks=True)
                
                output = j2_env.get_template(fileNameTemplate).render(objModule)
                
                # Save the results
                with open(os.path.join(outputPath, objCodeTemplate['output'] ), "w") as outputFile:
                    outputFile.write(output)
                    