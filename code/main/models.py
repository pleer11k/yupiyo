from django.db import models

class Topic(models.Model):
    name = models.CharField(max_length=60)
    code = models.FileField(upload_to="main/static/")
