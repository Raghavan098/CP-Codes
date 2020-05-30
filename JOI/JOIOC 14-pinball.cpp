/*
    solution is divided into two parts.
    first atleast one in the choosen subset of the answer should have l = 1
    and r = m
    and the solution will always be some sort of a triangle pointing downwards interms of 'c'
    so solve both left and right using dp 

    refer: https://github.com/SpeedOfMagic/CompetitiveProgramming/blob/master/JOIOC/14-pinball.cpp 
    for detailed explanation 
*/

#include<bits/stdc++.h>

typedef long long ll;
typedef long double lld;
using namespace std;

#define endl "\n"
#define fi first
#define se second
#define MEMS(a,b) memset(a,b,sizeof(a))
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define __ freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define all(c) c.begin(),c.end()
#define pii pair<int, int>

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r)
{
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

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
template <typename T>
ostream &operator<<(ostream &out, multiset<T> const &v) {
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

const int N = 1e6 + 10;

struct node {
    int l, r, c, cost;

};

int dpl[N];
int dpr[N];
const int inf = 1e18;
int t[4*N];

void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = inf;
    } else {
        int tm = (tl + tr) / 2;
        build(v*2, tl, tm);
        build(v*2+1, tm+1, tr);
        t[v] = min(t[v*2], t[v*2+1]);
    }
}

int get(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return inf;
    if (l == tl && r == tr)
        return t[v];
    int tm = (tl + tr) / 2;
    return min(get(v*2, tl, tm, l, min(r, tm)), 
                   get(v*2+1, tm+1, tr, max(l, tm+1), r));
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        if (t[v] < new_val) return;
        t[v] = new_val; 
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = min(t[v*2], t[v*2+1]);
    }
}

int n, m;

node arr[N];

int solve() {
    cin >> n >> m;
    map<int, int> comp;
    for (int i = 1; i <= n; ++i) {
        int l, r, c, cost;
        cin >> l >> r >> c >> cost;
        arr[i] = {l, r, c, cost};
        comp[l];
        comp[r];
        comp[c];
    }
    int curr = 1;
    for (auto &i : comp) {
        i.se = curr++;
    }
    build(1, 1, N - 1);
    for (int i = 1; i <= n; i++) {
        if (arr[i].l == 1) {
            dpl[i] = arr[i].cost;
        } else {
            int cost = arr[i].cost;
            int bef = get(1, 1, N - 1, comp[arr[i].l], comp[arr[i].r]);
            dpl[i] = cost + bef;
        }
        update(1, 1, N - 1, comp[arr[i].c], dpl[i]);
    }

    build(1, 1, N - 1);
    int ans = inf;

    for (int i = 1; i <= n; i++) {
        if (arr[i].r == m) {
            ans = min(ans, dpl[i]);
            dpr[i] = arr[i].cost;
        } else {
            int cost = arr[i].cost;
            int bef = get(1, 1, N - 1, comp[arr[i].l], comp[arr[i].r]);
            ans = min(ans, dpl[i] + bef);
            dpr[i] = cost + bef;
        }
        update(1, 1, N - 1, comp[arr[i].c], dpr[i]);
    }

    for (int i = 1; i <= n; i++) {
        if (arr[i].l == 1 && arr[i].r == m) {
            ans = min(ans, arr[i].cost);
        } 
    }
    if (ans != inf)
        cout << ans << endl;
    else {
        cout << -1 << endl;
    }
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
