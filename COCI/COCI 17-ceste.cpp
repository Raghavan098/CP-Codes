/*
    It is obvious that no greedy solution will pass. So we'll have a node for every time that is possible to reach here.
    But the number of states will be very huge.
    as an optimization we have to note that when a node is reached with more distance then the time at which I am reaching should be definitely less.
    Now use this in the dijkstra and then the total number of nodes that is visited becomes very less so it will pass
*/

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

const int N = 2020;

struct edg {
    int v, t, c;
};

vector<vector<edg>> g(N);
int n, m;
ll ans[N];
const ll INF = 1e18;
unordered_map<int, int> d[N];
int tim[N];
void dijkstra(int s) {
    for (int i = 1; i <= n; i++) {
        ans[i] = INF;
        tim[i] = 2000*2000 + 10;
    }
    d[s][0] = 0;
    priority_queue<pair<int, pii>, vector<pair<int, pii>>, greater<pair<int, pii>>> q;
    q.push({0, {0, s}});
    while (!q.empty()) {
        int v = q.top().se.se;
        int d_v = q.top().fi;
        int t_v = q.top().se.fi;
        ans[v] = min(ans[v], 1LL * d_v * t_v);
        q.pop();
        if (d_v != d[v][t_v])
            continue;

        if (tim[v] <= t_v) continue;
        tim[v] = t_v;

        for (auto &edge : g[v]) {
            int to = edge.v;
            int tim = t_v + edge.t;
            int len = edge.c;
            if (d[to].count(tim)) {
                if (d[to][tim] > d_v + len) {
                    d[to][tim] = d_v + len;
                    q.push({d[to][tim], {tim, to}});
                }
            } else {
                d[to][tim] = d_v + len;
                q.push({d[to][tim], {tim, to}});
            }
        }
    }
    for (int i = 1;  i<= n; i++) {
        if (ans[i] == INF) {
            ans[i] = -1;
        }
    }
}

int solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, t, c; 
        cin >> a >> b >> t >> c;
        g[a].push_back({b, t, c});
        g[b].push_back({a, t, c});
    }   
    dijkstra(1);
    for (int i = 2; i <= n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
