// g++ -std=c++14
/*
    The main idea is to convert this the query type of (x, y) to (par[x], z) until we reach the root
    This can be done using by binary search in each node by maintaing some information
        I maintained information like what is the index of this child, what is the first time this child will be visited and cumulative sums of how many times will i - 1 be visited before visiting i

    (I believe there are much simpler solution than this)
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
#define __ freopen("arb3.in","r",stdin);freopen("arb3.out","w",stdout);
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

int n, q;
int arr[N];
vector<vector<int>> g(N);
vector<vector<int>> sums(N);
vector<vector<int>> first(N);
int ind[N];
int par[N];
void dfs0(int v, int p) {
    vector<int> child;
    vector<int> fc, cs;
    int c = 0;
    for (auto u : g[v]) {
        if (u == p) continue;
        dfs0(u, v);
        child.push_back(u);
        c++;
    }
    sort(all(child), [](int a, int b) -> bool{
        return arr[a] < arr[b];
    });
    reverse(all(child));
    fc.push_back(1);
    for (int i = 1; i < c; i++) {
        int curr = arr[child[i]];
        int prev = arr[child[i - 1]];
        int tmp = fc[i - 1] + ((prev - curr) * i) + 1;
        fc.push_back(tmp);
    }
    cs.push_back(0);
    for (int i = 1; i < c; i++) {
        int tmp = (fc[i] - fc[i - 1]) / i;
        cs.push_back(tmp + cs[i - 1]);
    }
    sums[v] = cs;
    first[v] = fc;
    for (int i = 0; i < c; i++) {
        ind[child[i]] = i;
    }
}

int recur(int v, int t) {
    if (v == 1) return t;
    int p = par[v];
    if ((int)first[p].size() == 1) return recur(par[v], t);
    int i = ind[v];
    if (t == 1) return recur(par[v], first[p][i]);
    int c = (int)first[p].size();
    int l = i, r = c - 1;
    int mid, ans = c;
    while (l <= r) {
        mid = (l + r) / 2;
        int tmp = sums[p][mid] - sums[p][i] + (i != 0);
        if (tmp >= t) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    int tim = first[p][ans - 1];
    int x = sums[p][ans - 1] - sums[p][i] + (i != 0);
    // tr(tim, x);
    int rem = t - x;
    tim += (rem - 1) * ans;
    tim += (i + 1);
    if (i == 0 && t < first[p][1]) tim--;
    // tr(ans, v, tim);
    return recur(par[v], tim);

}

int solve() {
    cin >> n >> q;
    for (int i = 2; i <= n; i ++) {
        int p;
        cin >> p;
        g[p].push_back(i);
        g[i].push_back(p);
        par[i] = p;
    }
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    dfs0(1, 0);
    for (int i = 0; i < q; i++) {
        int v, t;
        cin >> v >> t;
        cout << recur(v, t) << endl;
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
