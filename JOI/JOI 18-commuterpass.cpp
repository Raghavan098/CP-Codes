// g++ -std=c++14

/*
    There are 3 ways that u can reach v
    one way is that directly reaching u -> v without overlapping any edge of the path from s to t
    other way is :
        u -> i -> j -> v
        i to j is a path from s to t

        or u -> i -> j -> v
        i to j is a path from t to s
    
    since we know that all the shortest paths from s to t forms a dag write dp on dag to compute the values for case 2 and 3
*/


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
const int N = 1e5 + 100;
int n, m;
const int INF = 1e18;
int ans = INF;

void dijkstra(int s, vector<int> & d, vector<vector<pii>> &g) {
    d.resize(n + 1, INF);
    d[s] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int v = q.top().second;
        int d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : g[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                q.push({d[to], to});
            }
        }
    }
}
vector<vector<pii>> g(N);
int s, t, a, b;
vector<int> ds, dt, da, db;
int dp[N];
int tot;

int f(int v) {
    if (dp[v] != -1) return dp[v];
    int &as = dp[v];
    as = db[v];
    for (auto u : g[v]) {
        if ((ds[v] + u.se + dt[u.fi]) == tot) {
            as = min(as, f(u.fi));
        }
    }
    ans = min(ans, da[v] + as);
    return as;
}

int f2(int v) {
    if (dp[v] != -1) return dp[v];
    int &as = dp[v];
    as = db[v];
    for (auto u : g[v]) {
        if ((dt[v] + u.se + ds[u.fi]) == tot) {
            as = min(as, f2(u.fi));
        }
    }
    ans = min(ans, da[v] + as);
    return as;
}

void work() {
    dijkstra(s, ds, g);
    dijkstra(t, dt, g);
    dijkstra(a, da, g);
    dijkstra(b, db, g);
    tot = ds[t];
    MEMS(dp, -1);
    ans = da[b];
    f(s);
    MEMS(dp, -1);
    f2(t);
}


int solve() {
    cin >> n >> m;
    cin >> s >> t >> a >> b;
    for (int i = 0; i < m; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        g[v].push_back({u, w});
        g[u].push_back({v, w});
    }
    work();
    cout << ans << endl;
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
