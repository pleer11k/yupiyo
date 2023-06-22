from django.shortcuts import render, HttpResponse
from django.http import JsonResponse
from .models import Topic, Profile, Task, Chapter
import requests, json
import time
import datetime
from bs4 import BeautifulSoup as bs

def present_topic(request, id):
    q = open(Topic.objects.all()[id].code.path, mode='r', encoding="utf-8")
    t = []
    for l in q:
        print(l)
        if (l != '\n'): t.append(l)
        else: t.append(' ')
    print(t)
    # return HttpResponse(Topic.objects.all()[id].code)
    return render(request, 'codik.html', context={"code": t, "name": Topic.objects.all()[id].name})

def main(request):
    data = {}
    data["topics"] = {}
    for el in Chapter.objects.all():
        data["topics"][el.name] = []
    cur = 0
    for el in Topic.objects.all():
        adress = str(el.code.path)
        local = adress.split('main')[1]
        data["topics"][el.chapter.all()[0].name].append([el.name, 'main' + local, cur])
        cur += 1
    return render(request, "main.html", context=data)
    
def get_tasks():
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
    json.dump({"problems": raw["problems"]}, open('./main/jsons/problems.json', 'w'))
    return raw["problems"]



def builder():
    last_update = json.load(open('./main/jsons/data.json'))["time"]
    
    data = {}
    data["users"] = []
    data["users"] = json.load(open('./main/jsons/lists.json'))["users"]
    if (time.time() - last_update < 300):
        return data
    
    json.dump({"time": time.time()}, open('./main/jsons/data.json', 'w'))

    pr = get_tasks()
    ok = 0
    cnt = [0 for i in range(len(pr))]
    try:
        if (len(data["users"][0][1]) < len(pr)):
            ok = 1
            data["users"] = []
            for i in range(len(Profile.objects.all())):
                p = Profile.objects.all()[i]
                data["users"].append([p.handle, [[0, f'https://codeforces.com/contest/{pr[j][2]}/problem/{pr[j][3]}', pr[j][0], pr[j][1], j] for j in range(len(pr))]])
    except Exception:
        data["users"] = []
        ok = 1
        for i in range(len(Profile.objects.all())):
            p = Profile.objects.all()[i]
            data["users"].append([p.handle, [[0, f'https://codeforces.com/contest/{pr[j][2]}/problem/{pr[j][3]}', pr[j][0], pr[j][1], j] for j in range(len(pr))]])
    profile_num = 0
    for p in Profile.objects.all():
        url = f"https://codeforces.com/api/user.status?handle={p.handle}"
        time.sleep(0.5)
        r = requests.get(url)
        raw = json.loads(r.text)
        l = [[0, f"https://codeforces.com/contest/{pr[i][2]}/problem/{pr[i][3]}", pr[i][0], pr[i][1], i] for i in range(len(pr))]
        hist = json.load(open('./main/jsons/sends.json'))
        final_data = json.load(open('./main/jsons/lists.json'))
        try:
            last_saw = hist["submissions"][p.handle][0]["id"]
        except Exception:
            last_saw = 0
        if (ok): last_saw = 0
        s = 0
        c = 0
        for el in raw["result"]:
            if (el["id"] < last_saw): break
            print(el["id"])
            try:
                if (el["verdict"] == "OK"):
                    for i in range(len(pr)):
                        if (el["problem"]["contestId"] == pr[i][2] and el["problem"]["index"] == pr[i][3]):
                            data["users"][profile_num][1][i][0] = 2
                            # s += 1
                            # c += pr[i][0]
                            # cnt[i] += 1
                            # pr[i][4] += 1
                else:
                    for i in range(len(pr)):
                        if (el["problem"]["contestId"] == pr[i][2] and el["problem"]["index"] == pr[i][3]):
                            data["users"][profile_num][1][i][0] = max(data["users"][profile_num][1][i][0], 1)
            except Exception:
                pass
        
        profile_num += 1


        hist["submissions"][p.handle] = raw["result"]
        # print(hist)
        json.dump(hist, open('./main/jsons/sends.json', 'w'))
        json.dump(data, open('./main/jsons/lists.json', 'w'))

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