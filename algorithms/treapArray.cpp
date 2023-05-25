#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

constexpr long long inf = 1e9;
constexpr long long mod = 1e9 + 7;

// массив с добавлением и удалением элементов по индексу

struct node;

node *_null;
node *root;

struct node {
    int x, y;
    node* l = _null, * r = _null;
    
    node(int _x = inf): x(_x), y(x != inf) {}
};

void update(node* t) {
    if (t == _null) return;
    t->y = t->l->y + t->r->y + 1;
}

node* merge(node* l, node* r) {
    if (l == _null) return r;
    if (r == _null) return l;
    if (rand() & 1) {
        l->r = merge(l->r, r);
        update(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        update(r);
        return r;
    }
}

void lsplit(node *t, int k, node*& l, node*& r) {
    if (t == _null) {
        l = _null; r = _null;
        return;
    }
    if (t->l->y + 1 <= k) {
        lsplit(t->r, k - t->l->y - 1, t->r, r);
        update(t);
        l = t;
    } else {
        lsplit(t->l, k, l, t->l);
        update(t);
        r = t;
    }
}

void rsplit(node *t, int k, node*& l, node*& r) {
    if (t == _null) {
        l = _null; r = _null;
        return;
    }
    if (t->l->y + 1 < k) {
        rsplit(t->r, k - t->l->y - 1, t->r, r);
        update(t);
        l = t;
    } else {
        rsplit(t->l, k, l, t->l);
        update(t);
        r = t;
    }
}

void insert(int p, int x) {
    node* new_node = new node(x);
    node* l, * r;
    lsplit(root, p, l, r);
    root = merge(l, merge(new_node, r));
}

void erase(int x) {
    node* l0, * r0, *l1, * r1;
    rsplit(root, x, l0, r0);
    lsplit(r0, 1, l1, r1);
    root = merge(l0, r1);
}

void rprint(node *t) {
    if (t == _null) return;
    rprint(t->l);
    cout << t->x << " ";
    rprint(t->r);
}

int main() {
    _null = new node(inf);
    root = _null;

    int q; cin >> q;
    while (q --> 0) {
        string op;
        cin >> op;
        if (op == "insert") {
            int p, x; cin >> p >> x;
            insert(--p, x);
            cout << "succesfully added " << x << endl;
        } else if (op == "erase") {
            int p; cin >> p;
            erase(p);
            cout << "succesfully removed from pos " << p << endl;
        }
        rprint(root);
        cout << endl;
    }
}
