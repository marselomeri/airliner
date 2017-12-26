"""Apps.py registers applications to django project
"""
# -*- coding: utf-8 -*-
from __future__ import unicode_literals
from django.apps import AppConfig


class PollsConfig(AppConfig):
    """!
    Groundcontrol application is registered.
    """
    ## define application name
    name = 'groundcontrol'
