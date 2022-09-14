

#include <bits/stdc++.h>
using namespace std;
template <class T>
struct SegmentTree
{
    vector<T> t;
    int  n;

    SegmentTree(int  n)
    {
        this->n = n;
        t.assign(4 * n + 1, 0);
    }

    SegmentTree(vector<T> &a) : SegmentTree(a.size())
    {
        build(a, 1, 1, n);
    }
    void update(int ind, T new_val)
    {
        update(1, 1, n, ind, new_val);
    }
    void update(  int v, int tl, int  tr,  int pos, T new_val)
    {
        if (tl == tr)
        {
            t[v] = new_val;    //Updates a single position 
        }
        else
        {
            int  tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v * 2, tl, tm, pos, new_val);
            else
                update(v * 2 + 1, tm + 1, tr, pos, new_val);
            t[v] = combine(t[v * 2], t[v * 2 + 1]);
        }
    }
    T sum(int l, int r)
    {
        return sum(1, 1, n, l, r);
    }
    T sum(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return INF;      // -INF in max queries INF in min queries 0 in sum queries
        if (l == tl && r == tr)
        {
            return t[v];
        }
        int  tm = (tl + tr) / 2;
        return combine(sum(v * 2, tl, tm, l, min(r, tm)), sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }

    void build(vector<T> &a, int v, int tl, int tr)
    {
        if (tl == tr)
        {
            t[v] = a[tl - 1];    //The given array 0-indexed or 1-indexed
        }
        else
        {
            int  tm = (tl + tr) / 2;
            build(a, v * 2, tl, tm);
            build(a, v * 2 + 1, tm + 1, tr);
            t[v] = combine(t[v * 2], t[v * 2 + 1]);
        }
    }
    T combine(T a, T b)
    {
        return min(a, b);    //The combine function
    }
};


struct ST     // segment tree with lazy propagation sum queries addition queries.
{
#define lc (n << 1)
#define rc ((n << 1) | 1)
#define ll long long
    vector<ll> t;
    ll n;
    vector<ll> lazy;

    ST(ll n)
    {
        this->n = n;
        t.assign(4 * n + 1, 0);
        lazy.assign(4 * n + 1, 0);
    }

    ST(vector<long long> a) : ST(a.size())
    {
        build(a, 1, 1, n);
    }
    inline void push(int n, int b, int e)
    {
        if (lazy[n] == 0)
            return;
        t[n] = t[n] + lazy[n] * (e - b + 1);
        if (b != e)
        {
            lazy[lc] = lazy[lc] + lazy[n];
            lazy[rc] = lazy[rc] + lazy[n];
        }
        lazy[n] = 0;
    }
    inline long long combine(long long a, long long b)
    {
        return a + b;
    }
    inline void pull(int n)
    {
        t[n] = t[lc] + t[rc];
    }
    void build(vector<ll> &a, int n, int b, int e)
    {
        lazy[n] = 0;
        if (b == e)
        {
            t[n] = a[b-1];
            return;
        }
        int mid = (b + e) >> 1;
        build(a, lc, b, mid);
        build(a, rc, mid + 1, e);
        pull(n);
    }
    void upd(int l,int r,ll v){
        upd(1,1,n,l,r,v);
    }
    void upd(int n, int b, int e, int i, int j, long long v)
    {
        push(n, b, e);
        if (j < b || e < i)
            return;
        if (i <= b && e <= j)
        {
            lazy[n] = v; // set lazy
            push(n, b, e);
            return;
        }
        int mid = (b + e) >> 1;
        upd(lc, b, mid, i, j, v);
        upd(rc, mid + 1, e, i, j, v);
        pull(n);
    }
    void query(int l,int r){
        query(1,1,n,l,r);
    }
    long long query(int n, int b, int e, int i, int j)
    {
        push(n, b, e);
        if (i > e || b > j)
            return 0; // return null
        if (i <= b && e <= j)
            return t[n];
        int mid = (b + e) >> 1;
        return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
    }
};



template <class T> //Segment tree with lazy propagation assignment queries
struct SegmentTreeLazyAssign
{
    vector<T> t;
    vector<bool> marked;
    T n;

    SegmentTreeLazyAssign(T n)
    {
        this->n = n;
        t.assign(4 * n + 1, 0);
        marked.assign(4 * n + 1, false);
    }

    SegmentTreeLazyAssign(vector<T> &a) : SegmentTreeLazyAssign(a.size())
    {
        build(a, 1, 1, n);
    }
    void update(T i,T j, T new_val)
    {
        update(1, 1, n, i,j, new_val);
    }
    void push(int v, int l, int r)
    {
        if (marked[v])
        {
            int m = (l + r) / 2;
            t[2 * v] = t[v] / (r - l + 1) * (m - l + 1);   //For min max remove the range multipication
            t[2 * v + 1] = t[v] / (r - l + 1) * (r - m);
            marked[2 * v] = true;
            marked[2 * v + 1] = true;
            marked[v] = false;
        }
    }
    void update(T v, T tl, T tr, T i, T j, T new_val)
    {
        if (tr < i || tl > j)
        {
            return;
        }
        if (tl >= i && tr <= j)
        {
            t[v] = (tr - tl + 1) * new_val;   //For min max remove the range multipication
            marked[v] = true;
            return;
        }
        else
        {
            push(v, tl, tr);
            T tm = (tl + tr) / 2;
            update(v * 2, tl, tm, i,j, new_val);
            update(v * 2 + 1, tm + 1, tr, i,j, new_val);
            t[v] = combine(t[v * 2], t[v * 2 + 1]);
        }
    }
    T sum(T l, T r)
    {
        return sum(1, 1, n, l, r);
    }
    T sum(T v, T tl, T tr, T l, T r)
    {
        if (tr<l||tl>r)
            return 0;   //-INF in max queries INF in min queries 0 in sum queries
        if (l == tl && r == tr)
        {
            return t[v];
        }
        T tm = (tl + tr) / 2;
        push(v,tl,tr);
        return combine(sum(v * 2, tl, tm, l, min(r, tm)), sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }

    void build(vector<T> &a, T v, T tl, T tr)
    {
        if (tl == tr)
        {
            t[v] = a[tl ];
        }
        else
        {
            T tm = (tl + tr) / 2;
            build(a, v * 2, tl, tm);
            build(a, v * 2 + 1, tm + 1, tr);
            t[v] = combine(t[v * 2], t[v * 2 + 1]);
        }
    }
    T combine(T a, T b)
    {
        return (a + b);
    }
};
template <class T>
struct SegmentTreeLazyAssignIndexFind
{
    vector<T> t;
    vector<bool> marked;
    T n;

    SegmentTreeLazyAssignIndexFind(T n)
    {
        this->n = n;
        t.assign(4 * n + 1, 0);
        marked.assign(4 * n + 1, false);
    }

    SegmentTreeLazyAssignIndexFind(vector<T> &a) : SegmentTreeLazyAssignIndexFind(a.size())
    {
        build(a, 1, 1, n);
    }
    void update(T i,T j, T new_val)
    {
        update(1, 1, n, i,j, new_val);
    }
    void push(int v, int l, int r)
    {
        if (marked[v])
        {
            // int m = (l + r) / 2;
            t[2 * v] = t[v];
            t[2 * v + 1] = t[v];
            marked[2 * v] = true;
            marked[2 * v + 1] = true;
            marked[v] = false;
        }
    }
    void update(T v, T tl, T tr, T i, T j, T new_val)
    {
        if (tr < i || tl > j)
        {
            return;
        }
        if (tl >= i && tr <= j)
        {
            t[v] = new_val;
            marked[v] = true;
            return;
        }
        else
        {
            push(v, tl, tr);
            T tm = (tl + tr) / 2;
            update(v * 2, tl, tm, i,j, new_val);
            update(v * 2 + 1, tm + 1, tr, i,j, new_val);
            t[v] = combine(t[v * 2], t[v * 2 + 1]);
        }
    }
    T sum(T l, T r,T val)
    {
        return sum(1, 1, n, l, r,val);
    }
    T sum(T v, T tl, T tr, T l, T r,T val)
    {
        if (l>r)
            return -1;
        if (l == tl && r == tr)
        {
            if(t[v]>=val)return -1;    // return a value which will not interfere with answer

            while(l!=r){
                push(v,l,r);
                int m=(l+r)/2;
                if(t[2*v]<val){   //will depend on lesser or greater value we want
                    r=m;
                    v=2*v;
                }
                else{
                    l=m+1;
                    v=2*v+1;
                }
            }
            return l;
            
        }
        T tm = (tl + tr) / 2;
        push(v,tl,tr);
        int p=sum(v * 2, tl, tm, l, min(r, tm),val);
        if(p!=-1)return p;

        return sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r,val);
    }

    T sum2(T l, T r)
    {
        return sum2(1, 1, n, l, r);
    }
    T sum2(T v, T tl, T tr, T l, T r)
    {
        if (l>r)
            return INF;
        if (l == tl && r == tr)
        {
            return t[v];
        }
        T tm = (tl + tr) / 2;
        push(v,tl,tr);
        return combine(sum2(v * 2, tl, tm, l, min(r, tm)), sum2(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }

    void build(vector<T> &a, T v, T tl, T tr)
    {
        if (tl == tr)
        {
            t[v] = a[tl];
        }
        else
        {
            T tm = (tl + tr) / 2;
            build(a, v * 2, tl, tm);
            build(a, v * 2 + 1, tm + 1, tr);
            t[v] = combine(t[v * 2], t[v * 2 + 1]);
        }
    }
    T combine(T a, T b)
    {
        return min(a , b);    // min or max accordingly what we want
    }
};
template <class T>
struct SegmentTreeLazyAdd
{
    vector<T> t;
    vector<ll> marked;
    T n;

    SegmentTreeLazyAdd(T n)
    {
        this->n = n;
        t.assign(4 * n + 1, 0);
        marked.assign(4 * n + 1, 0);
    }

    SegmentTreeLazyAdd(vector<T> &a) : SegmentTreeLazyAdd(a.size())
    {
        build(a, 1, 1, n);
    }
    void update(T i,T j, T new_val)
    {
        update(1, 1, n, i,j, new_val);
    }
    void push(int v, int l, int r)
    {
        if (marked[v])
        {
            int m = (l + r) / 2;
            marked[2 * v] += marked[v];
            marked[2 * v + 1] += marked[v];
            t[2 * v] = t[2*v]+marked[v]*(m-l+1); //ignore range part for min max
            t[2 * v + 1] = t[2*v+1]+marked[v]*(r-m); // ignore range part for min max
            marked[v] = 0;
        }
    }
    void update(T v, T tl, T tr, T i, T j, T new_val)
    {
        if (tr < i || tl > j)
        {
            return;
        }
        if (tl >= i && tr <= j)
        {
            marked[v] += new_val;
            t[v] = t[v] + new_val*(tr-tl+1);   //ignore range part for min max
            return;
        }
        else
        {
            push(v, tl, tr);
            T tm = (tl + tr) / 2;
            update(v * 2, tl, tm, i,j, new_val);
            update(v * 2 + 1, tm + 1, tr, i,j, new_val);
            t[v] = combine(t[v * 2], t[v * 2 + 1]);
        }
    }
    T sum(T l, T r)
    {
        return sum(1, 1, n, l, r);
    }
    T sum(T v, T tl, T tr, T l, T r)
    {
        if (tr<l||tl>r)
            return 0;    //change for min max
        if (l == tl && r == tr)
        {
            return t[v];
        }
        T tm = (tl + tr) / 2;
        push(v,tl,tr);
        return combine(sum(v * 2, tl, tm, l, min(r, tm)), sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }

    void build(vector<T> &a, T v, T tl, T tr)
    {
        if (tl == tr)
        {
            t[v] = a[tl ];
        }
        else
        {
            T tm = (tl + tr) / 2;
            build(a, v * 2, tl, tm);
            build(a, v * 2 + 1, tm + 1, tr);
            t[v] = combine(t[v * 2], t[v * 2 + 1]);
        }
    }
    T combine(T a, T b)
    {
        return (a + b);
    }
};
int m;
void build_y(int vx, int lx, int rx, int vy, int ly, int ry, vvi &t, vvi &a)
{
    if (ly > ry)
        return;
    if (ly == ry)
    {
        if (lx == rx)
            t[vx][vy] = a[lx][ly];
        else
            t[vx][vy] = max(t[vx * 2][vy], t[vx * 2 + 1][vy]);
    }
    else
    {
        int my = (ly + ry) / 2; 
        build_y(vx, lx, rx, vy * 2, ly, my, t, a);
        build_y(vx, lx, rx, vy * 2 + 1, my + 1, ry, t, a);
        t[vx][vy] = max(t[vx][vy * 2], t[vx][vy * 2 + 1]);
    }
}

void build_x(int vx, int lx, int rx, vvi &t, vvi &a)
{
    if (lx > rx)
        return;
    if (lx != rx)
    {
        int mx = (lx + rx) / 2;
        build_x(vx * 2, lx, mx, t, a);
        build_x(vx * 2 + 1, mx + 1, rx, t, a);
    }
    build_y(vx, lx, rx, 1, 0, m - 1, t, a);
}
int sum_y(int vx, int vy, int tly, int try_, int ly, int ry, vvi &t, vvi &a)
{
    if (ly > ry)
        return -INF;
    if (ly == tly && try_ == ry)
        return t[vx][vy];
    int tmy = (tly + try_) / 2;
    return max(sum_y(vx, vy * 2, tly, tmy, ly, min(ry, tmy), t, a), sum_y(vx, vy * 2 + 1, tmy + 1, try_, max(ly, tmy + 1), ry, t, a));
}

int sum_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry, vvi &t, vvi &a)
{
    // debug(vx);
    // debug(mp(lx,rx));
    if (lx > rx)
        return -INF;
    if (lx == tlx && trx == rx)
        return sum_y(vx, 1, 0, m - 1, ly, ry, t, a);
    int tmx = (tlx + trx) / 2;
    return max(sum_x(vx * 2, tlx, tmx, lx, min(rx, tmx), ly, ry, t, a), sum_x(vx * 2 + 1, tmx + 1, trx, max(lx, tmx + 1), rx, ly, ry, t, a));
}

template <class T>
struct SegmentTreeLazyAddIndexFind
{
    vector<T> t;
    vector<ll> marked;
    T n;

    SegmentTreeLazyAddIndexFind(T n)
    {
        this->n = n;
        t.assign(4 * n + 1, 0);
        marked.assign(4 * n + 1, false);
    }

    SegmentTreeLazyAddIndexFind(vector<T> &a) : SegmentTreeLazyAddIndexFind(a.size())
    {
        build(a, 1, 1, n);
    }
    void update(T i,T j, T new_val)
    {
        update(1, 1, n, i,j, new_val);
    }
    void push(int v, int l, int r)
    {
         if (marked[v])
        {
            int m = (l + r) / 2;
            marked[2 * v] += marked[v];
            marked[2 * v + 1] += marked[v];
            t[2 * v] = t[2*v]+marked[v]; 
            t[2 * v + 1] = t[2*v+1]+marked[v]; 
            marked[v] = 0;
        }
    }
    void update(T v, T tl, T tr, T i, T j, T new_val)
    {
        if (tr < i || tl > j)
        {
            return;
        }
        if (tl >= i && tr <= j)
        {
            marked[v] +=new_val;
            t[v] += new_val;
            return;
        }
        else
        {
            push(v, tl, tr);
            T tm = (tl + tr) / 2;
            update(v * 2, tl, tm, i,j, new_val);
            update(v * 2 + 1, tm + 1, tr, i,j, new_val);
            t[v] = combine(t[v * 2], t[v * 2 + 1]);
        }
    }
    T sum(T l, T r,T val)
    {
        return sum(1, 1, n, l, r,val);
    }
    T sum(T v, T tl, T tr, T l, T r,T val)
    {
        if (l>r)
            return -1;
        if (l == tl && r == tr)
        {
            if(t[v]>=val)return -1;    // return a value which will not interfere with answer

            while(l!=r){
                push(v,l,r);
                int m=(l+r)/2;
                if(t[2*v]<val){   //will depend on lesser or greater value we want
                    r=m;
                    v=2*v;
                }
                else{
                    l=m+1;
                    v=2*v+1;
                }
            }
            return l;
            
        }
        T tm = (tl + tr) / 2;
        push(v,tl,tr);
        int p=sum(v * 2, tl, tm, l, min(r, tm),val);
        if(p!=-1)return p;

        return sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r,val);
    }

    T sum2(T l, T r)
    {
        return sum2(1, 1, n, l, r);
    }
    T sum2(T v, T tl, T tr, T l, T r)
    {
        if (l>r)
            return INF;
        if (l == tl && r == tr)
        {
            return t[v];
        }
        T tm = (tl + tr) / 2;
        // push(v,tl,tr);
        return combine(sum2(v * 2, tl, tm, l, min(r, tm)), sum2(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }

    void build(vector<T> &a, T v, T tl, T tr)
    {
        if (tl == tr)
        {
            t[v] = a[tl];
        }
        else
        {
            T tm = (tl + tr) / 2;
            build(a, v * 2, tl, tm);
            build(a, v * 2 + 1, tm + 1, tr);
            t[v] = combine(t[v * 2], t[v * 2 + 1]);
        }
    }
    T combine(T a, T b)
    {
        return min(a , b);    // min or max accordingly what we want
    }
};