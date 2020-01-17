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

const int N = 800;

int g[N][N];
int gc[N][N];
int n, m;

int color[N];
int is_bip = 1;

int alone[N];

int a = 0, b = 0;

int dp[N][N];

void dfs(int v, int c) {
    if (color[v] != 0) {
        if (color[v] != c) {
            is_bip = 0;
            return;
        } else {
            return;
        }
    } else {
        color[v] = c;
        if (c == 1) a++;
        else b++;
    }
    int nxt = (c == 1)? 2: 1;
    for (int j = 1; j <= n; j++) {
        if (j != v && gc[v][j] == 1) {
            dfs(j, nxt);
        }
    }
}

int32_t main(){ _
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int v, y;
        cin >> v >> y;
        g[v][y] = 1;
        g[y][v] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <=n; j++) {
            if (i != j) {
                if (!g[i][j]) {
                    gc[i][j] = 1;
                    gc[j][i] = 1;
                    alone[i] = 1;
                    alone[j] = 1;
                }
            }
        }
    }
    vector<pair<int, int>> comp;
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            a = 0, b = 0;
            dfs(i, 1);
            comp.push_back({a, b});
        }
    }
    if (is_bip == 0) {
        cout << -1 << endl;
    } else {
        int k = comp.size();
        dp[0][0] = 1;
        for (int i = 1; i <= k; i++) {
            for (int j = 0; j < N; j++) {
                if ((j - comp[i - 1].fi) >= 0 && dp[i - 1][j - comp[i - 1].fi] == 1) {
                    dp[i][j] = 1;
                }
                if ((j - comp[i - 1].se) >= 0 && dp[i - 1][j - comp[i - 1].se] == 1) {
                    dp[i][j] = 1;
                }
            }
        }
        auto c2 = [](int x) -> int {
            return ((x * (x - 1)) / 2);
        };
        int ans = inf;
        for (int i = 0; i < N; i++) {
            if (dp[k][i] == 1) {
                ans = min(ans, c2(i) + c2(n - i));
            }
        }
        cout << ans << endl;
    }
}
