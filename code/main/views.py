from django.shortcuts import render, HttpResponse
from .models import Topic, Profile, Task
import requests, json

def main(request):
    data = {}
    data["topics"] = []
    for el in Topic.objects.all():
        adress = str(el.code.path)
        local = adress.split('main')[1]
        data["topics"].append([el.name, local])
    return render(request, "main.html", context=data)

def leaderboard(request):
    data = {}
    data["users"] = {}
    for p in Profile.objects.all():
        url = f"https://codeforces.com/api/user.status?handle={p.handle}"
        r = requests.get(url)
        raw = json.loads(r.text)
        l = [0 for i in range(len(Task.objects.all()))]
        print(url)
        for el in raw["result"]:
            if (el["verdict"] == "OK"):
                for i in range(len(Task.objects.all())):
                    t = Task.objects.all()[i]
                    if (el["problem"]["contestId"] == t.contest_id and el["problem"]["index"] == t.index):
                        l[i] = 1
        data["users"][p.handle] = l
        print(f"{p.handle}: {l}")

    return render(request, "tasks.html", context=data)

def test(request):
    return HttpResponse()
