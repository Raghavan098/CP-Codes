/*
    https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Balkan/official/2011/trapezoid-sol.pdf
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

#define int ll

const int N = 2e5 + 10;

const int MOD = 30013;

int n;
map<int, int> comp;

struct tra {
    int a, b, c, d, ind;
};

vector<tra> trap;
struct node {
    int mx, cnt;
    node() {
        mx = 0;
        cnt = 0;
    }
};


node t[4*N];

node combine(node a, node b) {
    node ans;
    if (a.mx == b.mx) {
        ans.mx = a.mx;
        ans.cnt = (0LL + a.cnt + b.cnt) % MOD;
    } else if (a.mx > b.mx) {
        ans = a;
    } else {
        ans = b;
    }
    return ans;
}

node query(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return node();
    if (l == tl && r == tr)
        return t[v];
    int tm = (tl + tr) / 2;
    return combine(query(v*2, tl, tm, l, min(r, tm)), 
                   query(v*2+1, tm+1, tr, max(l, tm+1), r));
}

void update(int v, int tl, int tr, int pos, node new_val) {
    if (tl == tr) {
        t[v] = combine(new_val, t[v]);
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}

node dp[N];

int solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        trap.push_back({a, b, c, d, i});
        comp[c]; comp[d];
    }
    
    int curr = 1;
    for (auto &i : comp) {
        i.se = curr;
        curr++;
    }

    for (auto &i : trap) {
        // i.a = comp[i.a];
        // i.b = comp[i.b];
        i.c = comp[i.c];
        i.d = comp[i.d];
    }

    sort(all(trap), [](tra a, tra b) -> bool {
        return a.a < b.a;
    });

    map<int, pair<tra, int>> event;

    for (auto i : trap) {
        event[i.a].fi = i;
        event[i.a].se = 1;
    }

    int ans1 = 0, ans2 = 0;

    for (auto ind : event) {
        int i = ind.fi;
        if (event[i].se == 1) {
            auto t = event[i].fi;

            dp[ind.se.fi.ind] = query(1, 1, curr, 1, t.c);
            dp[ind.se.fi.ind].mx++;

            if (dp[ind.se.fi.ind].mx == 1) {
                dp[ind.se.fi.ind].cnt++;
            }

            event[t.b] = {t, 2};
            if (dp[ind.se.fi.ind].mx > ans1) {
                ans1 = dp[ind.se.fi.ind].mx;
                ans2 = dp[ind.se.fi.ind].cnt;
            } else if (dp[ind.se.fi.ind].mx == ans1) {
                ans2 = (0LL + ans2 + dp[ind.se.fi.ind].cnt) % MOD;
            }
        }

        if (event[i].se == 2) {
            auto t = event[i].fi;
            update(1, 1, curr, t.d, dp[t.ind]);
        }   
    }

    cout << ans1 << " " << ans2 << endl;


    return 0;
    
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
    return EXIT_SUCCESS;	
}
