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

const int R = 2002;
const int C = 202;
const int INF = 1e9;
int r, c;
int cost[R][C];
int d[R][2][R][2];

int cumu[R][C];

inline int get_cost(int r, int a, int b) {
    if (a > b) swap(a, b);
    return (cumu[r][b] - cumu[r][a - 1]);
}

vector<pair<pair<int, bool>, int>> get_list(int x, int y) {
    int ori, opp;
    vector<pair<pair<int, bool>, int>> ans;
    if (y == 0) ori = 1, opp = c;
    else ori = c, opp = 1;
    if (x != 1) {
        ans.push_back({{x - 1, y}, cost[x - 1][ori]});
    }
    if (x != r) {
        ans.push_back({{x + 1, y}, cost[x + 1][ori]});
    }
    ans.push_back({{x, y ^ 1}, get_cost(x, ori, opp) - cost[x][ori]});
    return ans;
}

void dijkstra(int v, int t) {
    for (int i = 1; i <= r; i++) {
        for (int j = 0; j < 2; j++) {
            d[v][t][i][j] = INF;
        }
    }
    d[v][t][v][t] = 0;
    using piii = pair<int, pair<int, bool>>;
    priority_queue<piii, vector<piii>, greater<piii>> q;
    q.push({0, {v, t}});
    while (!q.empty()) {
        pii u = q.top().second;
        int d_u = q.top().first;
        q.pop();
        if (d_u != d[v][t][u.fi][u.se])
            continue;
        auto adj = get_list(u.fi, u.se);
        for (auto &edge : adj) {
            auto &to = edge.first;
            int len = edge.second;
            if (d[v][t][u.fi][u.se] + len < d[v][t][to.fi][to.se]) {
                d[v][t][to.fi][to.se] = d[v][t][u.fi][u.se] + len;
                q.push({d[v][t][to.fi][to.se], to});
            }
        }
    }
}

inline int get_dist(int t1, int r1, int t2, int r2) {
    return d[r1][t1][r2][t2];
}

int solve() {
    scanf("%d%d", &r, &c);
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            scanf("%d", &cost[i][j]);
            cumu[i][j] = (cumu[i][j - 1] + cost[i][j]);
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 1; j <= r; j++) {
            dijkstra(j, i);
        }
    }
    int q;
    scanf("%d", &q);
    ll ans = cost[1][1];
    int px = 1, py = 1;
    int x, y;
    for (int i = 1; i <= q; i++) {
        cin >> x >> y;
        ll d1 = 0ll + get_cost(px, 1, py) + get_dist(0, px, 0, x) + get_cost(x, 1, y) - cost[px][py] - cost[x][1];
        ll d2 = 0ll + get_cost(px, py, c) + get_dist(1, px, 0, x) + get_cost(x, 1, y) - cost[px][py] - cost[x][1];
        ll d3 = 0ll + get_cost(px, 1, py) + get_dist(0, px, 1, x) + get_cost(x, y, c) - cost[px][py] - cost[x][c];
        ll d4 = 0ll + get_cost(px, py, c) + get_dist(1, px, 1, x) + get_cost(x, y, c) - cost[px][py] - cost[x][c];
        

        ll temp = min(min(d1, d2), min(d3, d4));
        if (x == px) {
            temp = min(temp, 0LL + get_cost(px, y, py) - cost[px][py]);
        }
        ans += temp;
        px = x, py = y;
    }
    printf("%lld", ans);
    return 0;
}

int32_t main(){ 
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
