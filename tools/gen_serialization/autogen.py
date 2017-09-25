#!/usr/bin/env python

from cookiecutter.main import cookiecutter
from distutils.dir_util import copy_tree
import json
from jinja2 import Environment, FileSystemLoader
import os
from os.path import join
from shutil import copyfile, rmtree

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
for proto_msg in cookie_json["proto_msgs"]:
	pb_template = join(temp, "template.proto")
	out_template = join(temp, "{{cookiecutter.dir_name}}", proto_msg[:-3] + ".proto")
	copyfile(pb_template, out_template)

cookiecutter(temp, no_input=True, extra_context=extras, overwrite_if_exists=True)

# Walk through template directory and call cookiecutter on every dir
for root, dirs, files in os.walk(templates):
	for d in dirs:
		if d[:2] == '{{':
			continue
		cookiecutter(join(templates, d), no_input=True, extra_context=extras, overwrite_if_exists=True)

for dir in os.listdir(target):
	for f in os.listdir(dir):
		src = join(target, dir, f)
		dest = join(target, f)
		copyfile(src, dest)
	rmtree(join(target, dir))

rmtree(temp)

