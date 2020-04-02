/*
    first thing is to get a dp solution of complexity O(nk^2)
    the states for the above dp are node, count of taken nodes.

    we can easily build this dp using knapasack type dp.

    the next optimisation for making it O(nk + n^2) is:
    suppose we have processed k child 
    trees with number of nodes s and we 
    process k+1 child tree, with m nodes.
    then (i, j) has only s * m states, 
    note that these are the number of paths
    from the current child tree to those 
    already processed, as all pass through 
    x, this is the number of lca between 
    those two sets.


    Since each pair of nodes has a unique 
    lca, the number of states reviewed by 
    all nodes is O(n^2).
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

const int N = 1e4 + 2;
vector<vector<pii>> g(N);
int dp[2][N][N]; // 0-> for coming back, 1 -> staying
int n, k, x;
const int inf = 1e9 + 1;
int sub[N];

void dfs(int v, int p) {
    sub[v] = 1;
    dp[0][v][1] = 0;
    dp[1][v][1] = 0;
    for (auto u : g[v]) {
        if (u.fi == p) continue;
        dfs(u.fi, v);
        sub[v] += sub[u.fi];
    }
    int c = 1;
    for (auto u : g[v]) {
        if (u.fi == p) continue;
        for (int j = c; j >= 1; j--) {
            for (int i = 0; i <= min(sub[u.fi], k) && j + i <= k; i++) {
                dp[1][v][j + i] = min(dp[1][v][j + i], dp[1][u.fi][i] + dp[0][v][j] + u.se);
                dp[1][v][j + i] = min(dp[1][v][j + i], dp[0][u.fi][i] + dp[1][v][j] + 2 * u.se);

                dp[0][v][j + i] = min(dp[0][v][j + i], dp[0][u.fi][i] + dp[0][v][j] + 2 * u.se);
            }
        }
        c += sub[u.fi];
    }
    dp[0][v][0] = dp[1][v][0] = 0;
}

int solve() {
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++) 
            for (int k = 0; k < 2; k++) 
                dp[k][i][j] = inf;

    cin >> n >> k >> x;
    for (int i = 0; i < n - 1; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    dfs(x, 0);
    cout << dp[1][x][k] << endl;
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
