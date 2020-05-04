// g++ -std=c++14

/*
    maintain a set for each node denoting all the edges that start from this subtree and go out of this subtree.
    start a dfs and when moving up take the set with biggest size out of all the subtrees and merge all the others into this 
    total complexity is O(n*log^2(n))
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
#define __ freopen("disrupt.in","r",stdin);freopen("disrupt.out","w",stdout);
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
const int N = 50002;

int n, m;

vector<vector<int>> g(N);
vector<vector<int>> rem(N);

multiset<int> vals[N];

int l;
int timer;
vector<int> tin, tout;
vector<vector<int>> up;
int sub[N], big[N];
int level[N];

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    level[v] = level[p] + 1;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    sub[v]++;
    
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v);
            sub[v] += sub[u];
            if (sub[u] > sub[big[v]]) {
                big[v] = u;
            }
        }
    }



    tout[v] = ++timer;
}

bool is_ancetor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancetor(u, v))
        return u;
    if (is_ancetor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancetor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(n + 1);
    tout.resize(n + 1);
    timer = 0;
    l = ceil(log2(n)) + 1;
    up.assign(n + 1, vector<int>(l + 2));
    dfs(root, root);
}

int dist(int u,int v)
{
	return level[u] + level[v] - 2*level[lca(u,v)];
}

multiset<int> *ptr[N];
int ans[N];

void dfs2(int v, int p) {
    if (big[v] == 0) {
        ptr[v] = new multiset<int>();
        for (auto i : vals[v]) {
            ptr[v] -> insert(i);
        }
        if (ptr[v] -> empty()) {
            ans[v] = -1;
        } else {
            ans[v] = *(ptr[v] -> begin());
        }
        return;
    }
    
    for (auto u : g[v]) {
        if (u == p) continue;
        dfs2(u, v);
        if (big[v] == u) {
            ptr[v] = ptr[u];
        }
    }
    for (auto i : vals[v]) {
        ptr[v] -> insert(i);
    }

    for (auto u : g[v]) {
        if (u == p || u == big[v]) continue;
        for (auto i : *ptr[u]) {
            ptr[v] -> insert(i);
        }
    }
    for (auto i : rem[v]) {
        ptr[v] -> erase(ptr[v] -> find(i));
        ptr[v] -> erase(ptr[v] -> find(i));
    }
    if (ptr[v] -> empty()) {
        ans[v] = -1;
    } else {
        ans[v] = *(ptr[v] -> begin());
    }
}


int solve() {
    cin >> n >> m;
    vector<pii> edges;
    for (int i = 0; i < n -1; i++) {
        int v, u;
        cin >> v >> u;
        g[v].push_back(u);
        g[u].push_back(v);
        edges.push_back({v, u});
    }   
    preprocess(1);
    for (int i = 0; i < m; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        vals[v].insert(w);
        vals[u].insert(w);
        int lc = lca(v, u);
        rem[lc].push_back(w);
    }
    dfs2(1, 0);
    for (auto i : edges) {
        if (up[i.fi][0] == i.se) {
            cout << ans[i.fi] << endl;
        } else {
            cout << ans[i.se] << endl;
        }
    }
    return 0;
}

int32_t main(){ _
__
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
