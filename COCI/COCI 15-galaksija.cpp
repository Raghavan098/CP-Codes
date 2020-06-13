/*
    https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2016/contest4_solutions/solutions.pdf
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

// #define int ll

const int N = 1e5 + 100;

int n;
vector<pair<pii, int>> edg;
vector<vector<pii>> g(N);
int val[N];
map<int, int> cnt[N];
int parent[N];
int size[N];
vector<int> nodes[N];
vector<ll> ans;
ll curr = 0;


void dfs(int v, int p, int z) {
    val[v] = z;
    for (auto u : g[v]) {
        if (u.fi == p) continue;
        dfs(u.fi, v, z ^ u.se);
    }
}

void merge(int a, int b) {
    a = parent[a];
    b = parent[b];
    if (size[a] > size[b]) {
        swap(a, b);
    }
    for (auto i : nodes[a]) {
        if (cnt[b].count(val[i])) {
            curr += cnt[b][val[i]];
        }
        parent[i] = b;
    }
    ans.push_back(curr);
    for (auto i : nodes[a]) {
        nodes[b].push_back(i);
        cnt[b][val[i]]++;
    }
    size[b] += size[a];
    size[a] = 0;
    nodes[a].clear();
    cnt[a].clear();
}

int solve() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b, z;
        cin >> a >> b >> z;
        edg.push_back({{a, b}, z});
        g[a].push_back({b, z});
        g[b].push_back({a, z});
    }
    dfs(1, 0, 0);
    vector<int> ind;
    for (int i = 0; i < n - 1; i++) {
        int x;
        cin >> x;
        x--;
        ind.push_back(x);
    }
    reverse(all(ind));
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        size[i] = 1;
        nodes[i].push_back(i);
        cnt[i][val[i]] = 1;
    }

    for (auto i : ind) {
        int a = edg[i].fi.fi;
        int b = edg[i].fi.se;
        merge(a, b);
    }
    reverse(all(ans));
    ans.push_back(0);
    for (auto i : ans) {
        cout << i << "\n";
    }
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
