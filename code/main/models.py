from django.db import models

class Topic(models.Model):
    name = models.CharField(max_length=60)
    code = models.FileField(upload_to="main/static/")

class Task(models.Model):
    contest_id = models.IntegerField()
    index = models.CharField(max_length=3)

class Profile(models.Model):
    handle = models.CharField(max_length=30)
