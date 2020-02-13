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
#define inf 1000000000000000001
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

vector<vector<pii>> g;
vector<int> mark;
vector<int> visited;
vector<int> ans;
vector<int> ptr;
int nn, m;
int conn;
int n;

void dfs(int v) {
    visited[v] = conn;

    while (ptr[v] < (int)g[v].size()) {
        pii nxt = g[v][ptr[v]];
        ptr[v]++;
        if (mark[nxt.se]) continue;
        mark[nxt.se] = 1;
        dfs(nxt.fi);
    }

    ans.push_back(v);
}

int solve() {

    cin >> nn >> m;
    g.clear();
    g.resize(nn + 2);
    int arb = nn + 1;
    for (int i = 1; i <= m; i++) {
        int v, u;
        cin >> v >> u;
        g[v].push_back({u, i}), g[u].push_back({v, i});
    }
    int pre = m;
    int cnt = 0;
    for (int i = 1; i <= nn; i++) {
        if ((int)g[i].size() & 1) {
            g[arb].push_back({i, ++m});
            g[i].push_back({arb, m});
        } else {
            cnt++;
        }
    }
    ans.clear();
    mark.clear();
    mark.resize(m + 1);
    visited.clear();
    visited.resize(nn + 2);
    ptr.clear();
    ptr.resize(nn + 2);
    int yes = g[arb].size();
    n = nn + 1;
    conn = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            conn++;
            dfs(i);
        }
    }

    cout << cnt << endl;
    int k = ans.size();
    reverse(all(ans));
    for (int i = 1; i < k; i++) {
        if (ans[i] != arb && ans[i - 1] != arb && visited[ans[i]] == visited[ans[i - 1]]) {
            cout << ans[i - 1] << " " << ans[i] << endl;
        }
    }
    
    return 0;

}

int32_t main(){ _
    int t;
    cin >> t;
    // t = 1;
    while (t--) solve();
}
