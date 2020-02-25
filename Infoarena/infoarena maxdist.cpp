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
#define __ freopen("maxdist.in","r",stdin);freopen("maxdist.out","w",stdout);
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

#define int ll

const int N = 2e5 + 100;

int n, q;
vector<vector<int>> g(N);
vector<int> arr;

int l;

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

int level[N];

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    level[v] = level[p] + 1;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : g[v]) {
        if (u != p)
            dfs(u, v);
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


int solve() {
    cin >> n >> q;
    arr.assign(q, 0);
    vector<int> mark(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int v, u;
        cin >> v >> u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    for (int i = 0; i < q; i++) {
        cin >> arr[i];
        mark[arr[i]] = 1;
    }
    
    preprocess(1);

    vector<int> ans2;
    int a, b, curd;
    for (int i = 0; i < q; i++) {
        if (i == 0) {
            ans2.push_back(0);
            a = arr[i], b = arr[i];
            curd = 0;
        } else {
            int na = a, nb = b;
            if (curd < dist(arr[i], a)) {
                curd = dist(arr[i], a);
                na = arr[i];
                nb = a;
            }
            if (curd < dist(arr[i], b)) {
                curd = dist(arr[i], b);
                na = arr[i];
                nb = b;
            }
            a = na, b = nb;
            ans2.push_back(curd);
        }
    }


    reverse(all(arr));
    a = -1, b = -1, curd = 0;
    for (int i = 1; i <= n; i++) {
        if (!mark[i]) {
            if (a == -1) {
                a = i, b = i, curd = 0;
            } else {
                int na = a, nb = b;
                if (curd < dist(i, a)) {
                    curd = dist(i, a);
                    na = i;
                    nb = a;
                }
                if (curd < dist(i, b)) {
                    curd = dist(i, b);
                    na = i;
                    nb = b;
                }
                a = na, b = nb;
            }
        }
        // tr(a, b, curd, i);
    }
    vector<int> ans1;
    ans1.push_back(curd);
    // tr(curd, a, b);

    for (int i = 0; i < q - 1; i++) {
        if (a == -1) {
            ans1.push_back(0);
            a = arr[i], b = arr[i];
            curd = 0;
            continue;
        }
        int na = a, nb = b;
        
        if (curd < dist(arr[i], a)) {
            curd = dist(arr[i], a);
            na = arr[i];
            nb = a;
        }
        if (curd < dist(arr[i], b)) {
            curd = dist(arr[i], b);
            na = arr[i];
            nb = b;
        }
        a = na, b = nb;
        // tr(a, b, curd);
        ans1.push_back(curd);
    }

    reverse(all(ans1));
    for (int i = 0; i < q; i++) {
        cout << ans1[i] << " " << ans2[i] << endl;
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
