#!/usr/bin/env python

from cookiecutter.main import cookiecutter
import os
from shutil import copyfile, rmtree

extras = {"app_name": "VC"}

base = os.getcwd()
target = os.path.join(base, 'output')

if os.path.exists(target):
	rmtree(target)

os.mkdir(target)
os.chdir(target)

template = os.path.join(base, 'template')
cookiecutter(template, no_input=True, extra_context=extras, overwrite_if_exists=True)


