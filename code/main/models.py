from django.db import models

class Chapter(models.Model):
    name = models.CharField(max_length=60)
    
    def __str__(self) -> str:
        return self.name

class Topic(models.Model):
    name = models.CharField(max_length=60)
    code = models.FileField(upload_to="main/static/")
    chapter = models.ManyToManyField(Chapter)
    
    def __str__(self) -> str:
        return self.name

class Task(models.Model):
    contest_id = models.IntegerField()
    index = models.CharField(max_length=3)
    
    def __str__(self) -> str:
        return f'{self.contest_id} {self.index}'

class Profile(models.Model):
    handle = models.CharField(max_length=30)
    
    def __str__(self) -> str:
        return self.handle