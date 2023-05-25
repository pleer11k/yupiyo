#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

constexpr long long inf = 1e9;
constexpr long long mod = 1e9 + 7;

struct node;

node *_null;
node *root;

struct node {
    int x, y;
    node* l = _null, * r = _null;
    
    node(int _x): x(_x), y((rand() << 17) % mod) {}
};

node* merge(node* l, node* r) {
    if (l == _null) return r;
    if (r == _null) return l;
    if (l->y > r->y) {
        l->r = merge(l->r, r);
        return l;
    } else {
        r->l = merge(l, r->l);
        return r;
    }
}

void lsplit(node *t, int k, node*& l, node*& r) {
    if (t == _null) {
        l = _null; r = _null;
        return;
    }
    if (t->x <= k) {
        lsplit(t->r, k, t->r, r);
        l = t;
    } else {
        lsplit(t->l, k, l, t->l);
        r = t;
    }
}

void rsplit(node *t, int k, node*& l, node*& r) {
    if (t == _null) {
        l = _null; r = _null;
        return;
    }
    if (t->x < k) {
        rsplit(t->r, k, t->r, r);
        l = t;
    } else {
        rsplit(t->l, k, l, t->l);
        r = t;
    }
}

bool exist(node* t, int x) {
    if (t == _null) return false;
    if (t->x == x) return true;
    if (t->x > x) return exist(t->l, x);
    else return exist(t->r, x);
}

bool insert(int x) {
    if (exist(root, x)) return 0;
    node* new_node = new node(x);
    node* l, * r;
    lsplit(root, x, l, r);
    root = merge(l, merge(new_node, r));
    return 1;
}

bool erase(int x) {
    if (!exist(root, x)) return 0;
    node* l0, * r0, *l1, * r1;
    rsplit(root, x, l0, r0);
    lsplit(r0, x, l1, r1);
    root = merge(l0, r1);
    return 1;
}

void rprint(node *t) {
    if (t == _null) return;
    rprint(t->l);
    cout << t->x << " ";
    rprint(t->r);
}

int main() {
    _null = new node(inf);
    root = new node(0);

    int q; cin >> q;
    while (q --> 0) {
        string op;
        cin >> op;
        if (op == "print") {
            rprint(root);
            cout << endl;
        } else if (op == "insert") {
            int x; cin >> x;
            bool r = insert(x);
            if (r) cout << "succesfully added " << x << endl;
            else cout << x << " is already in set" << endl;
        } else if (op == "erase") {
            int x; cin >> x;
            bool r = erase(x);
            if (r) cout << "succesfully removed " << x << endl;
            else cout << "no such element" << endl;
        }
    }
}
