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
temp = join(base, 'temp')

# Remove working dirs if they exist
if os.path.exists(target):
	rmtree(target)
if os.path.exists(temp):
	rmtree(temp)

# Make working dirs
os.mkdir(temp)
os.mkdir(target)

# Need to change current working dir to desired cookiecutter output dir
os.chdir(target)

# Need to copy templates into temp dir
copy_tree(templates, temp)

with open(join(temp, "cookiecutter.json"), 'r') as f:
	cookie_json = json.load(f)

# Copy proto template file for every proto msg
for proto_msg, proto_data in cookie_json["proto_msgs"].iteritems():
	pb_template = join(temp, "template.proto")
	pb_py_template = join(temp, "py_template.proto")
	out_template = join(temp, "{{cookiecutter.autogen_version}}", proto_data["proto_msg"][:-3] + ".proto")
	py_out_template = join(temp, "{{cookiecutter.autogen_version}}", "_py_" + proto_data["proto_msg"][:-3] + ".proto")
	copyfile(pb_template, out_template)
	copyfile(pb_py_template, py_out_template)

cookiecutter(temp, no_input=True, extra_context=extras, overwrite_if_exists=True)


# Cleanup
for dir in os.listdir(target):
	for f in os.listdir(dir):
		src = join(target, dir, f)
		dest = join(target, f)
		if f[:4] == "_py_":
			subprocess.call(['protoc', "-I", join(target, dir), '--python_out=' + target, src])
		copyfile(src, dest)
	rmtree(join(target, dir))

# Organize python files
py_out = join(target, "python_pb")
os.mkdir(py_out)
for f in os.listdir(target):
	src = join(target, f)
	dest = join(py_out, f[4:])
	if f[:4] == "_py_":
		if f[-2:] == "py":
			copyfile(src, dest)
		os.remove(src)

rmtree(temp)

