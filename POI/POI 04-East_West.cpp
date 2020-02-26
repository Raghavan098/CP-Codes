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

// #define int ll
const int N = 1e6 + 100;

int n, w, z;
int p;
vector<vector<int>> g(N);
int arr[N];
int a = -1, b = -1;
vector<int> dis1, dis2;

pii dfs(int v, int par) {
    pii t = {arr[v], int(v > n - z)};
    for (auto u : g[v]) {
        if (u == par) continue;
        auto y = dfs(u, v);
        t.fi += y.fi;
        t.se += y.se;
    }
    // tr(v, t);
    if (t.fi == p && (z - t.se) >= p && a == -1) {
        a = v;
        b = par;
    }

    if (t.se >= p && t.fi == 0 && a == -1) {
        b = v;
        a = par;
    }
    return t;
}   

void dfs2(int v, int par, int typ = 0, int dist = 0) {
    // tr(v, par);
    if (arr[v] == 1) {
        dis1.push_back(dist);
    }
    if (v > n - z && typ == 1) {
        dis2.push_back(dist);
    }
    for (auto u : g[v]) {
        if (u == par) continue;
        dfs2(u, v, (typ | (u == b)), dist + 1);
    }
}



int solve() {
    cin >> n >> w >> z;
    for (int i = 1; i < n; i++) {
        int v, u;
        cin >> v >> u;
        g[u].push_back(v), g[v].push_back(u);
    }
    cin >> p;
    for (int i = 0; i < p; i++) {
        int x; cin >> x;
        arr[x]++;
    }
    dfs(1, 0);
    dfs2(a, 0);
    assert((int)dis1.size() <= (int)dis2.size());
    sort(all(dis1));
    for (int i = 1; i < (int)dis1.size(); i++) {
        dis1[i] = max(dis1[i - 1] + 1, dis1[i]);
    }
    sort(all(dis2));
    // tr(a, b, dis1, dis2);
    int ans = 0;
    reverse(all(dis1));
    for (int i = 0; i < (int)dis1.size(); i++) {
        ans = max(ans, dis1[i] + dis2[i]);
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