# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models

# Create your models here.

class Scorecard(models.Model):
    iteration = models.IntegerField()
    name = models.TextField()
    score = models.IntegerField()

    def __str__(self):
        return self.name