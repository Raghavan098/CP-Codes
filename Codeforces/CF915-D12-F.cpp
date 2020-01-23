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

const int N = 1e6 + 100;


int parent[N];
int siz[N];
void make_set(int x) {
    parent[x] = x;
    siz[x] = 1;
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
        if(siz[a] < siz[b]) {
            swap(a,b);
        }
        parent[b] = a;
        siz[a] += siz[b];
    }
}


vector<vector<int>> g(N);
int n;
vector<pii> arr;
vector<int> inserted;
int ans = 0; 
void insert(pii item) {
    int tot = 0;
    inserted[item.se] = 1;
    // tr(item);
    for (int v : g[item.se]) {
        if (inserted[v] == 1) {
            int x = siz[find_set(v)];
            ans += (tot * x * item.fi); 
            tot += x;
            ans += x * item.fi;
            // tr(v, x, ans, tot);
        }
    }
    for (int v  : g[item.se]) {
        if (inserted[v] == 1) {
            union_sets(v, item.se);
        }
    }
}

void calc(vector<pii> arr) {
    for (int i = 1; i <= n; i++) {
        make_set(i);
    }
    inserted.clear();
    inserted.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        insert(arr[i]);
    }

}

int solve() {
    cin >> n;
    arr.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].fi;
        arr[i].se = i;
    }
    for (int i = 0; i < n - 1; i++) {
        int v, u;
        cin >> u >> v;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    sort(arr.begin(), arr.end());
    calc(arr);
    // tr(ans);
    int final_ans = ans;
    ans = 0;
    reverse(arr.begin() + 1, arr.end());
    calc(arr);
    final_ans -= ans;

    cout << final_ans << endl;
}   

int32_t main(){ _
    int t;
    t = 1;
    while (t--) solve();
}
