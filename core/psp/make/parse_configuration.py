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
from __builtin__ import False

__author__ = 'Mathew Benson'

""" 
Utilities for parsing and returning the CFE Table Name from a json file.

Usage:
python parse_configuration.py [path to json file]
"""

import sys
import json
import os
import jinja2
import filecmp

# Load the local configuration file
if len(sys.argv) == 3:
    configFileName = sys.argv[1]
    outputPath = sys.argv[2]
    with open(configFileName, 'r') as configFile:
        config = json.load(configFile)
        
        # Iterate through the modules
        for moduleName in config['modules']:
            objModule = config['modules'][moduleName]
            
            # Get the base directory of the definition file
            dirBase = os.path.abspath(os.path.dirname(objModule['definition']))
            
            # Iterate through the code_templates 
            if 'code_templates' in objModule.keys():
                for code_template_name in objModule['code_templates']:
                    objCodeTemplate = objModule['code_templates'][code_template_name]
                
                    # Get the template directory
                    dirTemplate = os.path.dirname(os.path.join(dirBase, objCodeTemplate['template']))
                
                    # Get the template filename
                    fileNameTemplate = os.path.basename(objCodeTemplate['template'])
                
                    j2_env = jinja2.Environment(loader=jinja2.FileSystemLoader(dirTemplate))
                    
                    output = j2_env.get_template(fileNameTemplate).render(objModule)
                    
                    # If there is an existing file, only write the file if the contents have changed.
                    writeFile = True
                    outFileName = os.path.join(outputPath, objCodeTemplate['output'] )
                    if os.path.exists(outFileName):
                        # It does exist.  Now load it.
                        with open(outFileName, 'r') as outFile:
                            oldData = outFile.read()
                            if oldData == output:
                                writeFile = False
                            
                    if writeFile:
                        # Save the results
                        with open(outFileName, "w") as outputFile:
                            outputFile.write(output)
            
            # Iterate through tables 
            if 'tables' in objModule.keys():
                # Create the tables/<appName> directory
                cmakeOutput = ""
                tableOutputPath = os.path.join(outputPath, 'tables', moduleName)                
                if not os.path.exists(tableOutputPath):
                    os.makedirs(tableOutputPath)
                
                for tableTypeName in objModule['tables']:
                    objTableType = objModule['tables'][tableTypeName]
                    
                    # Get the template directory
                    templateDirectory = os.path.dirname(os.path.join(dirBase, objTableType['template']))
                
                    # Get the template filename
                    templateFileName = os.path.basename(objTableType['template'])

                    j2Env = jinja2.Environment(loader=jinja2.FileSystemLoader(templateDirectory))
                    
                    if '0' in objTableType.keys():
                        # This is an array of tables.  Iterate through all the array elements.
                        tblIdx = 0;
                        while True:
                            if str(tblIdx) not in objTableType.keys():
                                # Done parsing tables
                                break
                            #output = j2_env.get_template(fileNameTemplate).render(objModule)
                            #Path("/my/directory").mkdir(parents=True, exist_ok=True)
                           
                            objData = {
                                "data": objModule,
                                "instance": str(tblIdx)
                            }

                            objTableInstance = objTableType[str(tblIdx)]

                            output = j2Env.get_template(templateFileName).render(objData)
                    
                            # If there is an existing file, only write the file if the contents have changed.
                            writeFile = True
                            outFileName = os.path.join(tableOutputPath, objTableInstance['file_name'] + ".c")
                            if os.path.exists(outFileName):
                                # It does exist.  Now load it.
                                with open(outFileName, 'r') as outFile:
                                    oldData = outFile.read()
                                    if oldData == output:
                                        writeFile = False
                            
                            if writeFile:
                                # Save the results
                                with open(outFileName, "w") as outputFile:
                                    outputFile.write(output)

                            tblName = os.path.splitext(os.path.basename(outFileName))[0]
                            adjustedSourceFilePath = os.path.join(*(outFileName.split(os.path.sep)[3:]))

                            cmakeOutput = cmakeOutput + "add_airliner_app_table(" + moduleName + " NAME " + tblName + " SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/" + adjustedSourceFilePath + ")\n\n";
                    
                            tblIdx = tblIdx + 1
                            
                cmakeListFileName = os.path.join(tableOutputPath, "CMakeLists.txt")
                # Now write the cmake file.  If there is an existing file, only write the file if the contents 
                # have changed.
                writeFile = True
                if os.path.exists(cmakeListFileName):
                    # It does exist.  Now load it.
                    with open(cmakeListFileName, 'r') as cmakeFile:
                        oldCmakeFile = cmakeFile.read()
                        if oldCmakeFile == cmakeOutput:
                            writeFile = False
                            
                if writeFile:
                    # Save the results
                    with open(cmakeListFileName, "w") as cmakeFile:
                        cmakeFile.write(cmakeOutput)        
        