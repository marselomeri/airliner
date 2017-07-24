#!/usr/bin/env python

from cookiecutter.main import cookiecutter
import os
from shutil import copyfile, rmtree

extras = {"app_name": "AE"}

base = os.getcwd()
target = os.path.join(base, 'src')

if os.path.exists(target):
	rmtree(target)

os.mkdir(target)
os.chdir(target)

templates = os.path.join(base, 'templates')
for root, dirs, files in os.walk(templates):
	for d in dirs:
		if d[:2] == '{{':
			continue
		cookiecutter(os.path.join(templates, d), no_input=True, extra_context=extras, overwrite_if_exists=True)

for dir in os.listdir(target):
	for f in os.listdir(dir):
		src = os.path.join(target, dir, f)
		dest = os.path.join(target, f)
		copyfile(src, dest)
	rmtree(os.path.join(target, dir))

