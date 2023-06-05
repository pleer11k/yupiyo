from django.shortcuts import render, HttpResponse
from .models import Topic, Profile, Task
import requests, json
from bs4 import BeautifulSoup as bs

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
    data["users"] = []

    pr = [[0, "", 0, "", 0] for i in range(len(Task.objects.all()))]
    c = 0
    for el in Task.objects.all():
        pr[c][2] = el.contest_id
        pr[c][3] = el.index
        u = f'https://codeforces.com/contest/{el.contest_id}/problem/{el.index}'
        rt = requests.get(u)
        # print(rt)
        rtxt = bs(rt.text, features="html.parser")
        # print(str(rtxt.find_all("span", {"class", "tag-box"})[-1].text).replace(" ", "").replace("\n", "")[2:])
        try:
            pr[c][0] = int(str(rtxt.find_all("span", {"class", "tag-box"})[-1].text).replace(" ", "").replace("\n", "")[2:])
        except Exception:
            pr[c][0] = 0
        # print(str(rtxt.find_all("div", {"class", "title"})[0].text))
        pr[c][1] = str(rtxt.find_all("div", {"class", "title"})[0].text)
        c += 1

    # pr
    pr.sort(key=lambda a: a[0])
    cnt = [0 for i in range(len(pr))]
    for p in Profile.objects.all():
        url = f"https://codeforces.com/api/user.status?handle={p.handle}"
        r = requests.get(url)
        raw = json.loads(r.text)
        # print(raw)
        l = [[0, f"https://codeforces.com/contest/{pr[i][2]}/problem/{pr[i][3]}", pr[i][0], pr[i][1], i] for i in range(len(pr))]
        
        # print(url)
        s = 0
        c = 0
        for el in raw["result"]:
            if (el["verdict"] == "OK"):
                for i in range(len(pr)):
                    # t = Task.objects.all()[i]
                    if (el["problem"]["contestId"] == pr[i][2] and el["problem"]["index"] == pr[i][3]):
                        l[i][0] = 1
                        s += 1
                        c += pr[i][0]
                        cnt[i] += 1
                        pr[i][4] += 1

                        # l[i][3] = el["problem"]["name"]
                        # try:
                        #     l[i][2] = el["problem"]["rating"]
                        # except Exception:
                        #     pass

        data["users"].append([p.handle, l, s, round(c / s)])
        # print(f"{p.handle}: {l}")

    
    print(*cnt)
    if (request.method == "POST"):
        if ('cnt' in request.POST):
            data["users"].sort(key=lambda a: a[2], reverse=True)
        if ('dif' in request.POST):
            data["users"].sort(key=lambda a: a[3], reverse=True)
        if ('tcnt' in request.POST):
            for el in data["users"]:
                el[1].sort(key=lambda a: cnt[a[4]])
                print(el[1])
            
    return render(request, "tasks.html", context=data)

def test(request):
    return HttpResponse()
