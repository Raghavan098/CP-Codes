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

struct edg {
    int x, y, g, s;
    bool operator < (const edg e) const {
        return (mp(g, mp(s, mp(x, y)))) < mp(e.g, mp(e.s, mp(x, y)));
    }
};

const int N = 203;

int n, m, G, S;
vector<set<edg>> g(N);


int parent[N];
int size[N];
void make_set(int x) {
    parent[x] = x;
    size[x] = 1;
}
int find_set(int v) {
    if(v == parent[v]) {
        return v;
    }
    return parent[v] = find_set(parent[v]);
}
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if(a != b) {
        if(size[a] < size[b]) {
            swap(a,b);
        }
        parent[b] = a;
        size[a] += size[b];
    }
}


int ed, mx;
edg thisone;

vector<set<edg>> tree(N);

int dfs(int v, int p) {
    if (v == ed) {
        return 1;
    }

    for (auto i : tree[v]) {
        if (i.y == p) continue;
        if (dfs(i.y, v)) {
            if (mx < i.s) {
                mx = i.s;
                thisone = i;
            }
            return 1;
        }
    }
    return 0;
}

int ans = -1;

void dfs2(int v, int p) {
    for (auto i : tree[v]) {
        if (i.y == p) continue;
        ans = max(ans, i.s);
        dfs2(i.y, v);
    }
}

int solve() {

    cin >> n >> m >> G >> S;
    vector<edg> inp;
    for (int i = 0; i < m; i++) {
        int v, u, a, b;
        cin >> v >> u >> a >> b;
        g[v].insert({u, v, a, b});
        g[u].insert({v, u, a, b});
        inp.push_back({u, v, a, b});
    }

    sort(all(inp));

    for (int i = 1; i <= n; i++) {
        make_set(i);
    }

    int comp = n;

    ll glob = 4e18;

    for (auto e : inp) {
        int a = find_set(e.x);
        int b = find_set(e.y);
        if (a == b) {
            ed = e.y;
            mx = -1;
            dfs(e.x, 0);
            if (mx > e.s) {
                int p = thisone.x;
                int q = thisone.y;
                tree[p].erase(thisone);
                swap(thisone.x, thisone.y);
                tree[q].erase(thisone);
                tree[e.x].insert(e);
                auto ee = e;
                swap(ee.x, ee.y);
                tree[e.y].insert(ee);
            }

        } else {
            comp--;
            union_sets(e.x, e.y);
            tree[e.x].insert(e);
            auto ee = e;
            swap(ee.x, ee.y);
            tree[e.y].insert(ee);
        }

        if (comp == 1) {
            ans = -1;
            dfs2(1, 0);
            glob = min(glob, 1LL * ans * S + 1LL * e.g * G);
        }
    }
    if (glob == 4e18) {
        cout << -1 << endl;
    } else {
        cout << glob << endl;
    }
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
