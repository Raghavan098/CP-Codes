/*
    -> clearly a segment tree question 
    -> no need to write a query function because we only need the total sum
    -> turn on and off a range is required.
    -> when the number of turn off's to a given range is overall 0 then we can count the sum.
    -> change the update function that accomodates all these.
    -> no need to write lazy propagation because we are not using the query function so no need to propagate anything below.
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
#define __ freopen("curent.in","r",stdin);freopen("curent.out","w",stdout);
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

vector<vector<int>> g(N);
int n;
int q, t;

struct qr {
    int day, house, type, info;
};

qr lis[2 * N];

int in[N],  out[N];

int curr;

void dfs(int v) {
    in[v] = ++curr;
    for (auto u : g[v]) {
        dfs(u);
    }
    out[v] = curr;
}

bool cmp(qr &a, qr &b) {
    if (a.day != b.day)
        return a.day < b.day;
    else {
        return a.type < b.type;
    }
}

struct node {
    int active, sum;
    node() {
        active = 0;
        sum = 0;
    }
};

node tree[4 * N];

node combine(node a, node b) {
    node ans;
    ans.sum = a.sum + b.sum;
    return ans;
}

void build(int v, int l, int r){
    if(l == r){
        tree[v].active = 0;
        tree[v].sum = 1;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m + 1, r);
    tree[v] = combine(tree[2 * v], tree[2 * v + 1]);
    tree[v].active = 0;
    return;
}


void update(int v, int tl, int tr, int l, int r, int addend) {
    // tr(v, tl, tr, l, r, addend);
    if (l > r)
        return ;
    if (l == tl && tr == r) {
        // tr(v, tl, tr);
        if (addend == 0) { // off
            // tr(v);
            tree[v].sum = 0;
            tree[v].active++;
        } else {
            if (tree[v].active > 1) {
                tree[v].active--;
            } else {
                if (l != r) {
                    tree[v].sum = tree[2 * v].sum + tree[2 * v + 1].sum;
                    tree[v].active = 0;
                } else {
                    tree[v].sum = 1;
                    tree[v].active = 0;
                }
            }
        }
    }
    else {
        int tm = (tl + tr) / 2;
        update(v * 2, tl, tm, l, min(r, tm), addend);
        update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);

        if (!tree[v].active) {
            if (tl != tr) {
                tree[v].sum = tree[2 * v].sum + tree[2 * v + 1].sum;
            } else {
                tree[v].sum = 1;
            }
        } else {
            tree[v].sum = 0;
        }
    }
}

int solve() {

    cin >> n;
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }

    cin >> q;

    for (int i = 1; i <= q; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        lis[i] = {a, b, 0, c};
    }

    cin >> t;
    for (int i = 1; i <= t; i++) {
        int d;
        cin >> d;
        lis[q + i] = {d, 0, 1, 0};
    }

    dfs(1);

    build(1, 1, n);

    sort(lis + 1, lis + 1 + q + t, cmp);

    for (int i = 1; i <= q + t; i++) {
        // tr(tree[1].sum);
        if (lis[i].type == 1) {
            cout << tree[1].sum << endl;
        } else {
            int v = lis[i].house;
            // tr(v, in[v], out[v]);
            update(1, 1, n, in[v], out[v], lis[i].info);
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
    return EXIT_SUCCESS;	
}
