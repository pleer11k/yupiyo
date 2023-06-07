from django.shortcuts import render, HttpResponse
from django.http import JsonResponse
from .models import Topic, Profile, Task
import requests, json
import time
from bs4 import BeautifulSoup as bs

def main(request):
    data = {}
    data["topics"] = []
    for el in Topic.objects.all():
        adress = str(el.code.path)
        local = adress.split('main')[1]
        data["topics"].append([el.name, 'main' + local])
    return render(request, "main.html", context=data)
    
def get_tasks():
    raw = json.load(open('yupiyo/main/jsons/problems.json'))
    c = len(raw["problems"])
    t = []
    for i in range(c, len(Task.objects.all())):
        el = Task.objects.all()[i]
        pr = [0, "", 0, "", 0]
        pr[2] = el.contest_id
        pr[3] = el.index
        u = f'https://codeforces.com/contest/{el.contest_id}/problem/{el.index}'
        rt = requests.get(u)
        # print(rt)
        rtxt = bs(rt.text, features="html.parser")
        try:
            pr[0] = int(str(rtxt.find_all("span", {"class", "tag-box"})[-1].text).replace(" ", "").replace("\n", "")[2:])
        except Exception:
            pr[0] = 0
        pr[1] = str(rtxt.find_all("div", {"class", "title"})[0].text)
        c += 1
        t.append(pr)
        raw["problems"].append(pr)
    json.dump({"problems": raw["problems"]}, open('yupiyo/main/jsons/problems.json', 'w'))
    return raw["problems"]

def builder():
    data = {}
    data["users"] = []

    pr = get_tasks()

    pr.sort(key=lambda a: a[0])
    cnt = [0 for i in range(len(pr))]
    for p in Profile.objects.all():
        url = f"https://codeforces.com/api/user.status?handle={p.handle}"
        time.sleep(0.7)
        r = requests.get(url)
        raw = json.loads(r.text)
        l = [[0, f"https://codeforces.com/contest/{pr[i][2]}/problem/{pr[i][3]}", pr[i][0], pr[i][1], i] for i in range(len(pr))]
        
        s = 0
        c = 0
        for el in raw["result"]:
            try:
                if (el["verdict"] == "OK"):
                    for i in range(len(pr)):
                        # t = Task.objects.all()[i]
                        if (el["problem"]["contestId"] == pr[i][2] and el["problem"]["index"] == pr[i][3]):
                            l[i][0] = 2
                            s += 1
                            c += pr[i][0]
                            cnt[i] += 1
                            pr[i][4] += 1
                else:
                    for i in range(len(pr)):
                        # t = Task.objects.all()[i]
                        if (el["problem"]["contestId"] == pr[i][2] and el["problem"]["index"] == pr[i][3]):
                            l[i][0] = max(l[i][0], 1)
            except Exception:
                pass

        data["users"].append([p.handle, l, s, round(c / max(1, s))])
        # print(f"{p.handle}: {l}")

    
    data["mod"] = str(data["users"])
    return data

def leaderboard(request):
    return render(request, "tasks.html", context=builder())

def jsonleaderboard(request):
    return JsonResponse(builder())

def table(request):
    return render(request, "table.html")


import os
def test(request):
    raw = json.load(open('./main/jsons/problems.json'))
    c = len(raw["problems"])
    t = []
    for i in range(c, len(Task.objects.all())):
        el = Task.objects.all()[i]
        pr = [0, "", 0, "", 0]
        pr[2] = el.contest_id
        pr[3] = el.index
        u = f'https://codeforces.com/contest/{el.contest_id}/problem/{el.index}'
        rt = requests.get(u)
        # print(rt)
        rtxt = bs(rt.text, features="html.parser")
        try:
            pr[0] = int(str(rtxt.find_all("span", {"class", "tag-box"})[-1].text).replace(" ", "").replace("\n", "")[2:])
        except Exception:
            pr[0] = 0
        pr[1] = str(rtxt.find_all("div", {"class", "title"})[0].text)
        c += 1
        t.append(pr)
        raw["problems"].append(pr)
    json.dump({"problems": raw["problems"]}, open('yupiyo/main/jsons/problems.json', 'w'))
    return HttpResponse(str(raw["problems"]))