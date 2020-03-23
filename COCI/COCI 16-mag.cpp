/*
 it can be proven that the path will consist of only ones or just a single 2 in the path.
 now just compute the longest path that consists of only ones using dp. Compute both for the subtree as well
 the paths from the parent using two dfs's. 
 using this information compute the max length path that contains only 1's and exatly one 2.
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

const int N = 1e6 + 100;

int n;
vector<int> g[N];
int arr[N];

int dp_down[N], dp_up[N];
int parent[N];
int ans0 = 0;

void setabc(int &a, int &b, int c) {
    if (c > a) {
        b = a;
        a = c;
    } else if (c > b) {
        b = c;
    }
}

void dfs0(int v, int p) {
     parent[v] = p;
    int curr = (arr[v] == 1);
    int a = 0, b = 0;
    for (auto u : g[v]) {
        if (u == p)  continue;
        dfs0(u, v);
        curr = max(curr, dp_down[u] + 1);
        setabc(a, b, dp_down[u]);
    }
    if (arr[v] == 1) {
        dp_down[v] = curr;
        ans0 = max(ans0, a + b + 1);
    }
}

void dfs1(int v, int p, int mx_len = 0) {
    // tr(v, mx_len);
    dp_up[v] = mx_len;
    if (arr[v] == 1) {
        multiset<int> child;
        child.insert(mx_len);
        for (auto u : g[v]) {
            if (u == p) continue;
            child.insert(dp_down[u]);
        }

        for (auto u : g[v]) {
            if (u == p) continue;
            child.erase(child.find(dp_down[u]));
            int heremx = *child.rbegin() + 1;
            dfs1(u, v, heremx);
            child.insert(dp_down[u]);
        }

    } else {
        for (auto u : g[v]) {
            if (u == p) continue;
            dfs1(u, v, 0);
        }
    }
}

int cmp(int a, int b, int c, int d) {
    return (1LL * a * d < 1LL * c * b);
}

const int inf = 1e9 + 1;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r)
{
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}


void gen() {
    n = rand(1e5, 1e5);
    vector<int> curr = {0};
    vector<int> parent(n + 1);
    for (int i = 1; i <= n; i++) {
        int kk = curr.size();
        int p = curr[rand(0, kk - 1)];
        // int p = curr.back();
        parent[i] = p;
        curr.push_back(i);
        if (i > 1) {
            g[parent[i]].push_back(i);
            g[i].push_back(parent[i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        int temp = rand(1, 10);
        if (temp > 5) {
            arr[i] = rand(1, 1e9);
        } else {
            arr[i] = 1;
        }
        // arr[i] = rand(1, 1);
    }
    // cout << n << endl;
}

int solve() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int v, u;
        cin >> v >> u;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    // gen();
    dfs0(1, 0);
    dfs1(1, 0);

    if (ans0 == 0) {
        int mi = inf;
        for (int i = 1; i <= n; i++) {
            mi = min(mi, arr[i]);
        }
        cout << mi << "/1" << endl;
    } else {
        int a = 1, b = ans0;
        for (int i = 1; i <= n; i++) {
            vector<int> pth;
            for (auto j : g[i]) {
                if (j == parent[i]) continue;
                pth.push_back(dp_down[j]);
            }
            pth.push_back(dp_up[i]);
            sort(all(pth));
            reverse(all(pth));
            // tr(i, pth, a, b);
            if ((int)pth.size() == 1) {
                int c = arr[i], d = pth[0] + 1;
                if (!cmp(a, b, c, d)) {
                    a = c, b = d;
                }
            } else {
                int c = arr[i], d = 1 + pth[0] + pth[1];
                if (!cmp(a, b, c, d)) {
                    a = c, b = d;
                }
            }
        }
        assert(b != 0 && a != 0);
        int g = __gcd(a, b);
        a /= g;
        b /= g;
        cout << a << "/" << b << endl;
    }
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
