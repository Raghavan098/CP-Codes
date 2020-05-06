// g++ -std=c++14
/*
    A dp on trees question: https://csacademy.com/contest/ceoi-2017-day-2/task/chase/solution/
    
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
const int M = 120;

int dp1[N][M];
int dp2[N][M];

int n, k;
int arr[N];
int tot[N];

vector<vector<int>> g(N);

void dfs(int v, int p) {
    dp1[v][1] = tot[v];
    for (auto u : g[v]) {
        if (u == p) continue;
        dfs(u, v);
        int sc = tot[v] - arr[u];
        for (int i = 0; i <= k; i++) {
            dp1[v][i] = max(dp1[u][i], dp1[v][i]);
        }
        for (int i = 1; i <= k; i++) {
            dp1[v][i] = max(dp1[v][i], dp1[u][i - 1] + sc);
        }
    }

    vector<int> mx(M);
    mx[1] = tot[v];
    for (auto u : g[v]) {
        if (u == p) continue;
        int sc = tot[u] - arr[v];
        for (int i = 0; i <= k; i++) {
            dp2[u][i] = max(dp2[u][i], mx[i]);
        }
        for (int i = 1; i <= k; i++) {
            dp2[u][i] = max(dp2[u][i], mx[i - 1] + sc);
        }

        for (int i = 0; i <= k; i++) {
            mx[i] = max(mx[i], dp1[u][i]);
        }
        for (int i = 1; i <= k; i++) {
            mx[i] = max(mx[i], dp1[u][i - 1] + tot[v] - arr[u]);
        }
    }
    reverse(all(g[v]));
    for (int i = 0; i <= k; i++) {
        mx[i] = 0;
    }
    mx[1] = tot[v];
    for (auto u : g[v]) {
        if (u == p) continue;
        int sc = tot[u] - arr[v];
        for (int i = 0; i <= k; i++) {
            dp2[u][i] = max(dp2[u][i], mx[i]);
        }
        for (int i = 1; i <= k; i++) {
            dp2[u][i] = max(dp2[u][i], mx[i - 1] + sc);
        }

        for (int i = 0; i <= k; i++) {
            mx[i] = max(mx[i], dp1[u][i]);
        }
        for (int i = 1; i <= k; i++) {
            mx[i] = max(mx[i], dp1[u][i - 1] + tot[v] - arr[u]);
        }
    }
    reverse(all(g[v]));
}

void dfs2(int v, int p) {
    for (auto u : g[v]) {
        if (u == p) continue;
        for (int i = 0; i <= k; i++) {
            dp2[u][i] = max(dp2[u][i], dp2[v][i]);
        }
        for (int i = 1; i <= k; i++) {
            dp2[u][i] = max(dp2[u][i], dp2[v][i - 1] + tot[u] - arr[v]);
        }
        dfs2(u, v);
    }
}

int solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int v, u;
        cin >> v >> u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        for (auto u : g[i]) {
            tot[i] += arr[u];
        }
    }

    dfs(1, 0);
    dfs2(1, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            // tr(i, j, dp1[i][j], dp2[i][j]);
            ans = max(ans, dp1[i][j]);
            ans = max(ans, dp2[i][j]);
        }
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
