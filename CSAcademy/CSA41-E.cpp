// g++ -std=c++14

/*

Today might be the chance to grasp the chance to let your talent bloom.
May be tomorrow, the day after, or next year...
May be even when you are 30. I'm not sure if physique has anything to do with it
but if you think that it will never come, it probably never will.

- Tooru Oikawa.

*/


#include<bits/stdc++.h>

typedef long long ll;
typedef long double lld;
using namespace std;

#define endl "\n"
#define fi first
#define se second
#define pb(x) push_back(x)
#define mp(x,y) make_pair(x,y)
#define MEMS(a,b) memset(a,b,sizeof(a))
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define __ freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define all(c) c.begin(),c.end()
#define pii pair<int, int>
#define tr(...) cout<<__FUNCTION__<<' '<<__LINE__<<" = ";trace(#__VA_ARGS__, __VA_ARGS__)
template<typename S, typename T>
ostream& operator<<(ostream& out,pair<S,T> const& p){out<<'('<<p.fi<<", "<<p.se<<')';return out;}

template<typename T>
ostream& operator<<(ostream& out,vector<T> const& v){
ll l=v.size();for(ll i=0;i<l-1;i++)out<<v[i]<<' ';if(l>0)out<<v[l-1];return out;}

template <typename T>
ostream &operator<<(ostream &out, set<T> const &v) {
    for (auto i = v.begin(); i != v.end(); i++)
        out << (*i) << ' ';
    return out;
}
template <typename T, typename V>
ostream &operator<<(ostream &out, map<T, V> const &v) {
    for (auto i = v.begin(); i != v.end(); i++)
        out << "\n" << (i->first) <<  ":"  << (i->second);
    return out;
}

template<typename T>
void trace(const char* name, T&& arg1){cout<<name<<" : "<<arg1<<endl;}

template<typename T, typename... Args>
void trace(const char* names, T&& arg1, Args&&... args){
const char* comma = strchr(names + 1, ',');cout.write(names, comma-names)<<" : "<<arg1<<" | ";trace(comma+1,args...);}

const int N = 1e5 + 100;

int n, m, arr[N];
const int inf = 1e9;


pii t[4 * N];
int lazy[4 * N];

void build(int v, int l, int r){
    if(l == r){
        t[v] = {arr[l], arr[l]};
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m + 1, r);
    t[v].fi = min(t[2 * v].fi, t[2 * v + 1].fi);
    t[v].se = max(t[2 * v].se, t[2 * v + 1].se);
    return;
}

void push(int v) {
    t[v * 2].fi += lazy[v];
    t[v * 2].se += lazy[v];
    lazy[v * 2] += lazy[v];
    t[v * 2 + 1].fi += lazy[v];
    t[v * 2 + 1].se += lazy[v];
    lazy[v * 2 + 1] += lazy[v];
    lazy[v] = 0;
}

void update(int v, int tl, int tr, int l, int r, int addend) {
    if (l > r)
        return;
    if (l == tl && tr == r) {
        t[v].fi += addend;
        t[v].se += addend;
        lazy[v] += addend;
    }
    else {
        if(lazy[v] != 0){
            push(v);
        }
        int tm = (tl + tr) / 2;
        update(v * 2, tl, tm, l, min(r, tm), addend);
        update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);
        t[v].fi = min(t[2 * v].fi, t[2 * v + 1].fi);
        t[v].se = max(t[2 * v].se, t[2 * v + 1].se);
    }
}
pii comb(pii a, pii b) {
    pii ans = {min(a.fi, b.fi), max(a.se, b.se)};
    return ans;
}
pii query(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return {inf, -inf};
    if (l <= tl && tr <= r)
        return t[v];
    if(lazy[v] != 0){
        push(v);
    }
    int tm = (tl + tr) / 2;
    return comb(query(v * 2, tl, tm, l, min(r, tm)), query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}

int get_right(int v, int tl, int tr, int val) {
    if (tl == tr) return tl;
    if (lazy[v] != 0) push(v);
    int mid = (tl + tr) / 2;
    int lc = 2 * v;
    int rc = lc + 1;
    if (t[rc].se >= val) {
        return get_right(rc, mid + 1, tr, val);
    } else {
        return get_right(lc, tl, mid, val);
    }
}

int get_left(int v, int tl, int tr, int val) {
    if (tl == tr) return tl;
    if (lazy[v] != 0) push(v);
    int mid = (tl + tr) / 2;
    int lc = 2 * v;
    int rc = lc + 1;
    if (t[lc].fi <= val) {
        return get_left(lc, tl, mid, val);
    } else {
        return get_left(rc, mid + 1, tr, val);
    }
}

int solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    sort(arr + 1, arr + 1 + n);
    reverse(arr + 1,  arr + 1 + n);
    build(1, 1, n);
    int i;
    for (i = 1; i <= m; i++) {
        int x; cin >> x;
        if (x > n) break;
        auto currr = query(1, 1, n, 1, x);
        int curr = currr.fi;
        if (curr == 0) break;

        int ansr, ansl;
        ansr = get_right(1, 1, n, curr);
        ansl = get_left(1, 1, n, curr);
        update(1, 1, n, 1, ansl - 1, -1);
        int rem = x - ansl + 1;
        update(1, 1, n, max(1, ansr - rem + 1), ansr, -1);
    }
    cout << i - 1 << endl;
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
