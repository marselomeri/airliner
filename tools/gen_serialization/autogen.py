#!/usr/bin/env python

from cookiecutter.main import cookiecutter
from distutils.dir_util import copy_tree
import json
from jinja2 import Environment, FileSystemLoader
import os
from os.path import join
from shutil import copyfile, rmtree
import subprocess

extras = {"autogen_version": "0.0.0.1"}

# Get pathing info
base = os.getcwd()
target = join(base, 'src')
templates = join(base, 'templates')
temp = join(base, "temp")

# Remove working dirs if they exist
if os.path.exists(target):
	rmtree(target)
if os.path.exists(temp):
	rmtree(temp)

# Make working dirs
os.mkdir(temp)
os.mkdir(target)

with open("cookiecutter.json", 'r') as f:
	cookie_json = json.load(f)

for app, app_data in cookie_json["Airliner"]["apps"].iteritems():
    print app
    app_dir = join(target, app)
    os.mkdir(app_dir)
    temp = join(base, "temp", app)

    # Need to change current working dir to desired cookiecutter output dir
    os.chdir(app_dir)

    # Need to copy templates into temp dir
    copy_tree(templates, temp)

    app_cookie = app_data
    app_cookie["autogen_version"] = ""
    app_cookie["_extensions"] = ["jinja2.ext.do", "jinja2.ext.loopcontrols"]
    
            
    with open(join(temp, "cookiecutter.json"), "w") as cc:
        json.dump(app_cookie, cc, indent=4)
    
    # Copy proto template file for every proto msg
    for proto_msg, proto_data in app_data["proto_msgs"].iteritems():
	    pb_template = join(temp, "template.proto")
	    pb_py_template = join(temp, "py_template.proto")
	    out_template = join(temp, "{{cookiecutter.autogen_version}}", proto_data["proto_msg"][:-3] + ".proto")
	    py_out_template = join(temp, "{{cookiecutter.autogen_version}}", "_py_" + proto_data["proto_msg"][:-3] + ".proto")
	    copyfile(pb_template, out_template)
	    copyfile(pb_py_template, py_out_template)

    cookiecutter(temp, no_input=True, extra_context=extras, overwrite_if_exists=True)


    # Cleanup
    for dir in os.listdir(app_dir):
	    for f in os.listdir(dir):
		    src = join(app_dir, dir, f)
		    dest = join(app_dir, f)
		    if f[:4] == "_py_":
			    subprocess.call(['protoc', "-I", join(app_dir, dir), '--python_out=' + app_dir, src])
		    copyfile(src, dest)
	    rmtree(join(app_dir, dir))

    # Organize python files
    py_out = join(app_dir, "python_pb")
    os.mkdir(py_out)
    for f in os.listdir(app_dir):
	    src = join(app_dir, f)
	    dest = join(py_out, f[4:])
	    if f[:4] == "_py_":
		    if f[-2:] == "py":
			    copyfile(src, dest)
		    os.remove(src)

rmtree(temp)

