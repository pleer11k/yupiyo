from django.shortcuts import render, HttpResponse
from .models import Topic

def main(request):
    data = {}
    data["topics"] = []
    for el in Topic.objects.all():
        adress = str(el.code.path)
        local = adress.split('main')[1]
        data["topics"].append([el.name, local])
    return render(request, "main.html", context=data)

def test(request):
    return HttpResponse()
