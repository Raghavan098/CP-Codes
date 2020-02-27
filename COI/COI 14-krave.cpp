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

#define int ll

const int N = 1e5 + 99;
const int inf = 1e9;

set<int> th[4 * N];
set<int> tv[4 * N];

int n, a, b;

pii combine(pii a, pii b) {
    pii ans = {max(a.fi, b.fi), min(a.se, b.se)};
    return ans;
}

pii queryh(int v, int tl, int tr, int pos, int val) {
    if (tl > pos || tr < pos) return {-inf, inf};
    int tm = (tl + tr) / 2;
    pii curr = {-inf, inf};
    if (!th[v].empty()) {
        auto it = th[v].lower_bound(val);
        if (it != th[v].end()) {
            curr.se = *it;
        }
        if (it != th[v].begin()) {
            it--;
            curr.fi = *it;
        }
    }
    // tr(v, curr, tl, tr);
    if (tl == tr) return curr;
    return combine(curr, combine(
        queryh(2 * v, tl, tm, pos, val), queryh(2 * v + 1, tm + 1, tr, pos, val)
    ));
}

pii queryv(int v, int tl, int tr, int pos, int val) {
    if (tl > pos || tr < pos) return {-inf, inf};
    int tm = (tl + tr) / 2;
    pii curr = {-inf, inf};
    if (!tv[v].empty()) {
        auto it = tv[v].lower_bound(val);
        if (it != tv[v].end()) {
            curr.se = *it;
        }
        if (it != tv[v].begin()) {
            it--;
            curr.fi = *it;
        }
    }
    if (tl == tr) return curr;
    return combine(curr, combine(
        queryv(2 * v, tl, tm, pos, val), queryv(2 * v + 1, tm + 1, tr, pos, val)
    ));
}

void updateh(int v, int tl, int tr, int l, int r, int val) {
    if (tr < l || tl > r) return;
    if (tl >= l && tr <= r) {
        th[v].insert(val);
        return;
    }
    int tm = (tl + tr) / 2;
    updateh(2 * v, tl, tm, l, min(r, tm), val);
    updateh(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, val);
}

void updatev(int v, int tl, int tr, int l, int r, int val) {
    if (tr < l || tl > r) return;
    if (tl >= l && tr <= r) {
        tv[v].insert(val);
        return;
    }
    int tm = (tl + tr) / 2;
    updatev(2 * v, tl, tm, l, min(r, tm), val);
    updatev(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, val);
}

pii get_hori(int x, int y) {
    return queryh(1, 0, a, x, y);
}

pii get_vert(int x, int y) {
    return queryv(1, 0, b, y, x);
}

void add_hori(int l, int r, int y) {
    updateh(1, 0, a, l, r, y);
}

void add_vert(int l, int r, int x) {
    updatev(1, 0, b, l, r, x);
}

int solve() {
    cin >> a >> b;
    cin >> n;
    add_hori(0, a, b);
    add_hori(0, a, 0);
    add_vert(0, b, 0);
    add_vert(0, b, a);
    for (int i_ = 0; i_ < n; i_++) {
        int x, y, d;
        cin >> x >> y >> d;
        auto hori = get_hori(x, y);
        auto vert = get_vert(x, y);
        // tr(hori, vert);
        int curr_area = (hori.se - hori.fi) * (vert.se - vert.fi);
        if (d == 1) {
            int ar1 = (hori.se - y) * (vert.se - vert.fi);
            int ar2 = (y - hori.fi) * (vert.se - vert.fi);
            if (ar1 > ar2) swap(ar1, ar2);
            cout << ar1 << " " << ar2 << endl;
            add_hori(vert.fi, vert.se, y);
        } else {
            int ar1 = (hori.se - hori.fi) * (x - vert.fi);
            int ar2 = (hori.se - hori.fi) * (vert.se - x);
            if (ar1 > ar2) swap(ar1, ar2);
            cout << ar1 << " " << ar2 << endl;
            add_vert(hori.fi, hori.se, x);
        }
    }
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
