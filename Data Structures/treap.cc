#define null NULL

struct node {
    int x, y, size;
    long long sum;
    node *l, *r;
    node(int k) : x(k), y(rand()), size(1),
                  l(null), r(null), sum(0) { }
};

node* relax(node* p) {
    if (p) {
        p->size = 1;
        p->sum = p->x;
        if (p->l) {
            p->size += p->l->size;
            p->sum += p->l->sum;
        }
        if (p->r) {
            p->size += p->r->size;
            p->sum += p->r->sum;
        }
    }
    return p;
}

// Puts all elements <= x in l and all elements > x in r.
void split(node* t, int x, node* &l, node* &r) {
    if (t == null) l = r = null; else {
        if (t->x <= x) {
            split(t->r, x, t->r, r);
            l = relax(t);
        } else {
            split(t->l, x, l, t->l);
            r = relax(t);
        }
    }
}

node* merge(node* l, node *r) {
    if (l == null) return relax(r);
    if (r == null) return relax(l);
    if (l->y > r->y) {
        l->r = merge(l->r, r);
        return relax(l);
    } else {
        r->l = merge(l, r->l);
        return relax(r);
    }
}

node* insert(node* t, node* m) {
    if (t == null || m->y > t->y) {
        split(t, m->x, m->l, m->r);
        return relax(m);
    }
    if (m->x < t->x) t->l = insert(t->l, m);
    else t->r = insert(t->r, m);
    return relax(t);
}

node* erase(node* t, int x) {
    if (t == null) return null;
    if (t->x == x) {
        node *q = merge(t->l, t->r);
        delete t;
        return relax(q);
    } else {
        if (x < t->x) t->l = erase(t->l, x);
        else t->r = erase(t->r, x);
        return relax(t);
    }
}

// Returns any node with the given x.
node* find(node* cur, int x) {
    while (cur != null and cur->x != x) {
        if (x < cur->x) cur = cur->l;
        else cur = cur->r;
    }
    return cur;
}

node* find_kth(node* cur, int k) {
  while (cur != null and k >= 0) {
    if (cur->l && cur->l->size > k) {
      cur = cur->l;
      continue;
    }
    if (cur->l)
      k -= cur->l->size;
    if (k == 0) return cur;
    k--;
    cur = cur->r;
  }
  return cur;
}

long long sum(node* p, int x) { // find the sum of elements <= x
    if (p == null) return 0LL;
    if (p->x > x) return sum(p->l, x);
    long long ans = (p->l ? p->l->sum : 0) + p->x + sum(p->r, x);
    assert(ans >= 0);
    return ans;
}

