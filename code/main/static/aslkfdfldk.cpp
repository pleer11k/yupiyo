#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

constexpr long double eps = 1e-7;
constexpr long long inf = 1e16;
const long double pi = acos(-1);

struct vec;
struct point;
int dist(point, point);

struct point {
    int x, y;

    point(int _x = 0, int _y = 0): x(_x), y(_y) {}

    friend istream& operator>>(istream& in, point& v) {in >> v.x >> v.y; return in;}
    friend ostream& operator<<(ostream& out, const point& v) {out << v.x << " " << v.y; return out;}
};

struct vec {
    int x, y, l;

    vec(int _x = 0, int _y = 0): x(_x), y(_y), l(sqrt(x * x + y * y)) {}
    vec(point a): x(a.x), y(a.y), l(sqrt(x * x + y * y)) {}
    vec(point a, point b): x(b.x - a.x), y(b.y - a.y), l(sqrt(x * x + y * y)) {}
    vec(vec a, vec b): x(b.x - a.x), y(b.y - a.y), l(sqrt(x * x + y * y)) {}

    vec operator+(vec b) {return vec(x + b.x, y + b.y);}
    vec operator-(vec b) {return vec(x - b.x, y - b.y);}
    vec operator-() {return vec(-x, -y);}
    vec operator*(int k) {return vec(x * k, y * k);}
    int operator&(vec b) {return x * b.x + y * b.y;}
    int operator^(vec b) {return x * b.y - y * b.x;}
    vec operator/(int k) {return vec(x / k, y / k);}
    friend istream& operator>>(istream& in, vec& v) {in >> v.x >> v.y; v.l = sqrt(v.x * v.x + v.y * v.y); return in;}
    friend ostream& operator<<(ostream& out, const vec& v) {out << v.x << " " << v.y; return out;}

    point to_point() {point t(x, y); return t;}
};

struct line {
    int a, b, c;

    line(int _a = 0, int _b = 0, int _c = 0): a(_a), b(_b), c(_c) {}
    line(point p1, point p2): a(p1.y - p2.y), b(p2.x - p1.x), c(vec(p1) ^ vec(p2)) {}
    line(vec p1, vec p2): a(p1.y - p2.y), b(p2.x - p1.x), c(p1 ^ p2) {}
};

vec cross(line l1, line l2) {
    if (l1.a / l2.a == l1.b / l2.b) return vec(-inf, -inf);
    return vec((l2.c * l1.b - l1.c * l2.b) / (l1.a * l2.b - l2.a * l1.b), 
    (l2.a * l1.c - l1.a * l2.c) / (l1.a * l2.b - l2.a * l1.b));
}

struct segment {
    point p1, p2;
    int l = 0;

    segment(point _p1 = {}, point _p2 = {}): p1(_p1), p2(_p2), l(dist(p1, p2)) {}

    bool contain_point(point p) {
        return dist(p1, p) + dist(p2, p) == l;
    }
};

int dist(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int dist(line l, point p) {
    return abs(l.a * p.x + l.b * p.y + l.c) / sqrt(l.a * l.a + l.b * l.b);
}

int dist(segment s, point p) {
    line l(s.p1, s.p2);
    int d1 = dist(l, p);
    vec h = vec(l.b, -l.a);
    h = h / h.l * sqrt(dist(p, s.p1) * dist(p, s.p1) - d1 * d1) + s.p1;
    if (abs(dist(h.to_point(), p) - d1) > eps) {
        h = h - s.p1; h = -h; h = h + s.p1;
    }
    if (s.contain_point(h.to_point())) return d1;
    else return min(dist(p, s.p1), dist(p, s.p2));
}

struct circle {
    point c; int r;

    circle(point _c = {}, int _r = 0): c(_c), r(_r) {}

    vector<vec> cross(line l) {
        int d = dist(l, c);
        if (d > r) return {};
        if (abs(d - r) < eps) {
            vec n(l.a, l.b);
            n = n / n.l * d;
            n = n + vec(c);
            if (n.x * l.a + n.y * l.b + l.c > eps) {n = n - vec(c); n = -n; n = n + vec(c);}
            return {n};
        }
        vec n(l.a, l.b);
        n = n / n.l * d;
        n = n + vec(c);
        if (n.x * l.a + n.y * l.b + l.c > eps) {n = n - vec(c); n = -n; n = n + vec(c);}
        vec p1(-l.b, l.a), p2(l.b, -l.a);
        int del = sqrt(r * r - d * d);
        p1 = p1 / p1.l * del + n; p2 = p2 / p2.l * del + n;
        if (p1.x * l.a + p1.y * l.b + l.c > eps) {p1 = p1 - n; p1 = -p1; p1 + n;}
        if (p2.x * l.a + p2.y * l.b + l.c > eps) {p2 = p2 - n; p2 = -p2; p2 + n;}
        return {p1, p2};
    }

    vector<vec> tangentPoints(point p) {
        if (dist(c, p) < r) return {};
        if (abs(dist(c, p) - r) < eps) return {p};
        int d1 = dist(c, p);
        int dt = sqrt(d1 * d1 - r * r);
        int h = r * dt / d1;
        int l = sqrt(r * r - h * h);
        vec r(c, p);
        r = r / r.l * l;
        vec p1(-r.y, r.x), p2(r.y, -r.x);
        p1 = p1 / p1.l * h; p2 = p2 / p2.l * h;
        p1 = p1 + r + vec(c); p2 = p2 + r + vec(c);
        return {p1, p2};
    }
};

vector<vec> cross(circle a, circle b) {
    if (dist(a.c, b.c) > a.r + b.r) return {};
    if (abs(dist(a.c, b.c) + min(a.r, b.r) - max(a.r, b.r)) < eps) {
        if (a.r < b.r) swap(a, b);
        vec p(a.c, b.c);
        p = p / p.l * a.r + vec(a.c);
        return {p};
    }
    auto cpc = a.c;
    b.c.x -= a.c.x; b.c.y -= a.c.y;
    a.c = {0, 0};
    line l(-2 * b.c.x, -2 * b.c.y, b.c.x * b.c.x + b.c.y * b.c.y + a.r * a.r - b.r * b.r);
    auto res = a.cross(l);
    for (auto el : res) el = el + vec(cpc);
    return res;
}

struct ngon {
    int n;
    vector<point> pts;

    ngon(int _n = 0, vector<point> _pts = {}): n(_n), pts(_pts) {}

    int area() {
        vector<vec> vecs;
        for(auto el : pts) vecs.push_back(vec(el));
        vecs.push_back(vecs[0]);
        int area = 0;
        for (int i = 0; i < n; i++) {area += vecs[i] ^ vecs[i + 1];}
        return abs(area) / 2;
    }
};