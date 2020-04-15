// g++ -std=c++14

/*

    * The main idea comes when you finally try to root the tree at e.
    * after you root the tree at e you see that there are two cases to take care:
    * For a query e, v
    *   -> The removed edge does not lie in the path from v to root. Then the answer is simply 'escaped'
    *   -> Otherwise go through all the ancestors till the removed edge and see what is the nearest shop. 
    *       to find this fast maintain the jump pointers of 2^i th parent and update the answer in log n steps.
    * See the implementation for  more details.

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
const int LOG = 20;
const int inf = 1e18;
int n, s, q, e;
int val[N];
int shop[N];
vector<vector<pii>> g(N);
int lp[N], rp[N];
int tim;
pii edges[N];
int parent[N], up[N][LOG], jval[N][LOG];
int lenj[N][LOG];
int best[N];

void dfs0(int v, int p, int len, int par_edg = 0) {
    tim++;
    parent[v] = p;
    up[v][0] = p;
    for (int i = 1; i < LOG; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    lenj[v][0] = par_edg;
    for (int i = 1; i < LOG; i++) {
        int x = up[v][i - 1];
        lenj[v][i] = lenj[v][i - 1] + lenj[x][i - 1];
    }
    lp[v] = tim;
    val[v] = len;
    for (auto u : g[v]) {
        if (u.fi == p) continue;
        dfs0(u.fi, v, len + u.se, u.se);
    }
    rp[v] = tim;
}
int dfs1(int v, int p, int len) {
    if (shop[v] == 1) {
        best[v] = v;
    }
    for (auto u : g[v]) {
        if (u.fi == p) continue;
        int x = dfs1(u.fi, v, len + u.se);
        if (x != 0) {
            if (val[best[v]] > val[x]) {
                best[v] = x;
            }
        }
    }
    return best[v];
}

bool is_anss(int v, int u) { // if v is ansistor of u
    return (lp[u] >= lp[v] && rp[u] <= rp[v]);
}



int solve() {
    cin >> n >> s >> q >> e;
    for (int i = 0; i < n - 1; i ++) {
        int v, u, w;
        cin >> v >> u >> w;
        g[v].push_back({u, w});
        g[u].push_back({v, w});
        edges[i + 1] = {u, v};
    }   
    for (int i = 0; i < s; i++) {
        int x;
        cin >> x;
        shop[x] = 1;
    }   
    val[0] = inf;
    dfs0(e, 0, 0);
    dfs1(e, 0, 0);
    for (int i = 1; i <= n; i++) { // now best[i] becomes distance to the nearest shop in the subtree of i
        if (best[i] != 0)
            best[i] = val[best[i]] - val[i];
        else 
            best[i] = inf;
    }
    for (int i = 1; i <= n; i++) {
        if (up[i][0] == 0) {
            jval[i][0] = best[i];
        } else {
            jval[i][0] = min(best[i], lenj[i][0] + best[up[i][0]]);
        }
    }
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            if (up[i][j] == 0) {
                jval[i][j] = jval[i][j - 1];
            } else {
                jval[i][j] = min(jval[i][j - 1], lenj[i][j - 1] + jval[up[i][j - 1]][j - 1]);
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int e, v;
        cin >> e >> v;
        int a = edges[e].fi;
        int b = edges[e].se;
        if (parent[a] == b) {
            swap(a, b);
        }
        if (!is_anss(b, v)) {
            cout << "escaped\n";
        } else {
            int curr = v;
            int ans = best[v];
            int pre = 0;
            for (int i = LOG - 1; i >= 0; i--) {
                if (!is_anss(up[curr][i], a) && up[curr][i] != 0) {
                    ans = min(ans, jval[curr][i] + pre);
                    pre += lenj[curr][i];
                    curr = up[curr][i];
                }
            }
            if (ans == inf) {
                cout << "oo" << endl;
            } else {
                cout << ans << endl;
            }
        }
    }

    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
