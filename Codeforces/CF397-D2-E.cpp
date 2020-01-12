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

template<typename T>
void trace(const char* name, T&& arg1){cout<<name<<" : "<<arg1<<endl;}

template<typename T, typename... Args>
void trace(const char* names, T&& arg1, Args&&... args){
const char* comma = strchr(names + 1, ',');cout.write(names, comma-names)<<" : "<<arg1<<" | ";trace(comma+1,args...);}

#define int ll

const int N = 3e5 + 100;
const int MOD = 1e9 + 7;
int n;
vector<vector<int>> g(N);

struct node {
    int a, b, c;
    node() {
        a = 0, b = 0, c = 0;
    }

    void modify() {
        a = (a % MOD + MOD) % MOD;
        c = (c % MOD + MOD) % MOD;
    }
    
};
ostream& operator<<(ostream &output, const node &a ) { 
    output << "a:" << a.a << ", b:" << a.b << ", c:" << a.c;
    return output;            
}

node t[4 * N];
node lazy[4 * N];
int in[N], out[N];
int height[N];
int timer;

node combine(node a, node b) {
    node c;
    c.a = (a.a + b.a) % MOD;
    c.c = (a.c + b.c) % MOD;
    c.modify();
    return c;
}

void push(int v) {
    t[v * 2].a += lazy[v].a;
    lazy[2 * v].a += lazy[v].a;
    t[2 * v + 1].a += lazy[v].a;
    lazy[2 * v + 1].a += lazy[v].a;
    lazy[v].a = 0;
    
    t[v * 2].c += lazy[v].c;
    lazy[2 * v].c += lazy[v].c;
    t[2 * v + 1].c += lazy[v].c;
    lazy[2 * v + 1].c += lazy[v].c;
    lazy[v].c = 0;
    t[2 * v].modify();
    lazy[2 * v].modify();
    t[2 * v + 1].modify();
    lazy[2 * v + 1].modify();
}

void update(int v, int tl, int tr, int l, int r, int addend, int k_addend) {
    if (l > r)
        return;
    if (l == tl && tr == r) {
        t[v].a += addend;
        t[v].c += k_addend;
        lazy[v].a += addend;
        lazy[v].c += k_addend;
        t[v].modify();
        lazy[v].modify();
    }
    else {
        if(lazy[v].c != 0){
            push(v);
        }
        int tm = (tl + tr) / 2;
        update(v * 2, tl, tm, l, min(r, tm), addend, k_addend);
        update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend, k_addend);
        t[v] = combine(t[v * 2], t[v * 2 + 1]);
    }
}
node query(int v, int tl, int tr, int l, int r) {
    if (l > r) {
        node c;
        c.a = 0;
        c.b = 0;
        c.c = 0;
        return c;
    }
    if (l <= tl && tr <= r)
        return t[v];
    if(lazy[v].c != 0){
        push(v);
    }
    int tm = (tl + tr) / 2;
    return combine(query(v * 2, tl, tm, l, min(r, tm)), query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}

void dfs(int v, int p, int h) {
    timer++;
    in[v] = timer;
    height[v] = h;
    for (auto u : g[v]) {
        if (u == p) continue;
        dfs(u, v, h + 1);
    }
    out[v] = timer;
}

int32_t main(){ _
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int v, u;
        cin >> u;
        v = i;
        g[v].pb(u), g[u].pb(v);
    }
    dfs(1, 0, 0);
    // for (int i = 1; i <= n; i++) {
    //     tr(i, in[i], out[i]);
    // }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int v, x, k;
            cin >> v >> x >> k;
            update(1, 1, n, in[v], out[v], x + height[v] * k, k);
        } else {
            int v;
            cin >> v;
            auto q = query(1, 1, n, in[v], in[v]);
            // tr(v, q);
            int ans = (q.a - (((height[v] * q.c) % MOD)) % MOD + MOD) % MOD;
            cout << ans << endl;
        }
    }
}
