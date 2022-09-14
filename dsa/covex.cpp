class line
{
public:
    ll m=0;
    ll c=0;
    ll val(ll v)
    {
        return m * v + c;
    }
};
class node
{
public:
    line a;
    node *left = NULL;
    node *right = NULL;
};
class cvxtrick
{
public:
    node *root = new node;
    void init(ll p)
    {
        mx = p;
        root->a.m = 0;
        root->a.c = 0;
    }
    ll mx;
    void add_line(ll m1, ll c)
    {
        node *curr = root;
        ll l = 0;
        ll r = mx;
        line p = {m1, c};
        line p1 = p;
        while (l <= r)
        {

            ll m = (r + l) / 2;
            // debug(m);
            if (curr->a.val(l) >= p.val(l) && curr->a.val(r) >= p.val(r))
            {
                break;
            }   
            else if (curr->a.val(l) <= p.val(l) && curr->a.val(r) <= p.val(r))
            {
                curr->a = p;
                break;
            }
            bool mid = (curr->a.val(m) < p.val(m));
            bool lf = (curr->a.val(l) < p.val(l));

            if (mid)
            {
                swap(curr->a, p);
                // break;
            }
            if (mid == lf)
            {
                l = m + 1;
                if (curr->right == NULL)
                {
                    curr->right = new node;
                    curr = curr->right;
                    curr->a=p;
                    // debug(l);
                    break;
                }
                curr = curr->right;
                // break;/
            }
            else
            {
                r = m;
                if (curr->left == NULL)
                {
                    curr->left = new node;
                    curr = curr->left;
                    curr->a=p;
                    // debug(l);
                    break;
                }
                curr = curr->left;
            }
        }
    }
    ll find_val(ll x)
    {
        node *curr = root;
        ll l = 0;
        ll r = mx;
        ll ans = 0;
        while (l <= r)
        {
            // p=p1;
            if (curr == NULL)
            {
                break;
            }
            else
            {
                ll m = (r + l) / 2;
                ans = max(ans, curr->a.val(x));
                if (x > m)
                {
                    l = m + 1;
                    curr = curr->right;
                }
                else
                {
                    r = m;
                    curr = curr->left;
                }
            }
        }
        return ans;
    }
};


// for applying convex hull but with limits on each line in a range like line in valid from (0-r);
class line
{
public:
    ll m=-INF;
    ll c=-INF;
    ll val(ll v)
    {
        if(m==-INF){
            return -1e18;
        }
        return m * v + c;
    }
};

ll mx;
vector<line> t;
void add(int v,int l,int r,line val,int ind){
    if(l>ind)return;
    if(r<=ind){
        while(l<=r){
            ll m=(l+r)/2;
            bool mid = (t[v].val(m)<val.val(m));
            bool lf = (t[v].val(l)<val.val(l));
            if(mid){
                swap(t[v],val);
            }
            if(lf!=mid){
                r=m;
                v=2*v;
            }
            else{
                v=2*v+1;
                l=m+1;
            }
        }
        return;
    }
    else{
         ll m=(l+r)/2;
        add(2*v,l,m,val,ind);
        add(2*v+1,m+1,r,val,ind);

    }
}
ll get(int ind){
    ll ans=-INF;
    int v=1;
    int l=0;
    int r=mx;
    while(l<r){
        // debug(v);
        // debug(l);
        // debug(r);
        ans=max(ans,t[v].val(ind));
        ll m=(l+r)/2;
        if(ind<=m){
            v=2*v;
            r=m;
        }
        else{
            v=2*v+1;
            l=m+1;
        }
    }
    debug(v);
    debug(t[v].m);
    debug(t[v].c);
    ans=max(ans,t[v].val(ind));
    return ans;
}
