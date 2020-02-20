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


const int N = 1e5 + 199;

lld t[4*N];
lld combine(lld a, lld b) {
    return a * b;
}

void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = 1.0;
    } else {
        int tm = (tl + tr) / 2;
        build(v*2, tl, tm);
        build(v*2+1, tm+1, tr);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}


void update(int v, int tl, int tr, int pos, lld new_val) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}

struct event {
    int a, h, l, r, s, ind;
};

int n, m;

map<int, vector<event>> sweepin, sweepout, sweepoutleft;
map<int, vector<pii>> shrooms;

lld ans[N];

int solve() {
    cin >> n >> m;
    set<int> all;
    for (int i = 1; i <= n; i++) {
        int a, h, l, r;
        cin >> a >> h >> l >> r;
        int s = 100 - l - r;
        sweepin[a].push_back({a, h, l, r, s, i});
        sweepout[a + h].push_back({a, h, l, r, s, i});
        sweepoutleft[a - h].push_back({a, h, l, r, s, i});
        all.insert(a);
        all.insert(a + h);
        all.insert(a - h);
    }
    build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        int b, z;
        cin >> b >> z;
        shrooms[b].push_back({z, i});
        ans[i] = z;
        all.insert(b);
    }
    for (auto i : all) {
        for (auto s : shrooms[i]) {
            ans[s.se] *= t[1];
        }
        for (auto j : sweepin[i]) {
            lld fallinleft = (j.l + j.s + 0.00) / 100.00;
            update(1, 1, n, j.ind, fallinleft);
        }


        for (auto j : sweepout[i]) {
            update(1, 1, n, j.ind, 1.0);
        }
    }
    build(1, 1, n);
    for (auto it = all.rbegin(); it != all.rend(); it++) {
        int i = *it;
        for (auto s : shrooms[i]) {
            ans[s.se] *= t[1];
        }
        for (auto j : sweepin[i]) {
            lld fallinright = (j.r + j.s + 0.00) / 100.00;
            update(1, 1, n, j.ind, fallinright);
        }

        for (auto j : sweepoutleft[i]) {
            update(1, 1, n, j.ind, 1.0);
        }
    }

    lld final_ans = 0.0;
    for (int i = 1; i <= m; i++) {
        final_ans += ans[i];
    }

    cout << fixed << setprecision(12) << final_ans << endl;

    return 0;

}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
