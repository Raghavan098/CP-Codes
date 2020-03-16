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

// #define int ll

const int N = 2e5 + 100;

int n, k;
int cnt[N];
vector<vector<pii>> g(N);

int centroid;

int subcnt[N];
int dist[N];
int more;

void dfs0(int v, int p) {
    subcnt[v] += cnt[v];
    for (auto u : g[v]) {
        if (u.fi == p) continue;
        dfs0(u.fi, v);
        subcnt[v] += subcnt[u.fi];
    }

    int pcnt = k - subcnt[v];
    if (pcnt > more) {
        return;
    }
    for (auto u : g[v]) {
        if (u.fi == p) continue;
        if (subcnt[u.fi] > more) return;
    }
    centroid = v;
}

void dfs1(int v, int p, int dd) {
    dist[v] = dd;
    for (auto u : g[v]) {
        if (u.fi == p) continue;
        dfs1(u.fi, v, dd + u.se);
    }
}

int solve() {
    cin >> k >> n;
    more = (k + 1) / 2;
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    
    for (int i = 0; i < n - 1; i++) {
        int v, u, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    dfs0(1, 0);

    dfs1(centroid, 0, 0);

    ll ans = 0;
    
    for (int i = 1; i <= n; i++) {
        ans += 1LL * cnt[i] * dist[i];
    }
    
    cout << ans << endl;
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
