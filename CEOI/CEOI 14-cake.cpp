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

const int N = 3e5 + 100;

const int inf = 1e9;

int n, q, a;
int arr[N];
struct node {
    int mx, i1;
};

node t[4*N];
node combine(node a, node b) {
    node ans;
    if (a.mx > b.mx) {
        ans.mx = a.mx;
        ans.i1 = a.i1;
    } else {
        ans.mx = b.mx;
        ans.i1 = b.i1;
    }
    return ans;
}

void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = {arr[tl], tl};
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}

node get(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return {-inf, 0};
    if (l == tl && r == tr)
        return t[v];
    int tm = (tl + tr) / 2;
    return combine(get(v*2, tl, tm, l, min(r, tm)), 
                   get(v*2+1, tm+1, tr, max(l, tm+1), r));
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] = {arr[tl], tl};
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}

int findright(int v, int tl, int tr, int l, int r, int val) {
    // tr(tl, tr);
    if (tl > tr || l > r) return -1;
    if (tr < l || tl > r) return -1;
    if (tl == tr) {
        // tr(tl, t[v].mx);
        if (t[v].mx > val) return tl;
        else return -1;
    }
    int tm = (tl + tr) / 2;
    if (tl >= l && tr <= r) {
        // tr(l, r, tl, tr, t[2 * v].mx, t[2 * v + 1].mx);
        if (t[2 * v + 1].mx > val) return findright(2 * v + 1, tm + 1, tr, l, r, val);
        if (t[2 * v].mx > val) return findright(2 * v, tl, tm, l, r, val);
        return -1;
    }
    int ans = -1;
    if (r > tm) ans = findright(2 * v + 1, tm + 1, tr, l, r, val);
    if (ans == -1 && tm >= l) ans = findright(2 * v, tl, tm, l, r, val);
    return ans;
}

int findleft(int v, int tl, int tr, int l, int r, int val) {
    if (tl > tr || l > r) return -1;
    if (tr < l || tl > r) return -1;
    if (tl == tr) {
        if (t[v].mx > val) return tl;
        else return -1;
    }
    int tm = (tl + tr) / 2;
    if (tl >= l && tr <= r) {
        // tr(l, r, tl, tr, t[2 * v].mx, t[2 * v + 1].mx);
        if (t[2 * v].mx > val) return findleft(2 * v, tl, tm, l, r, val);
        if (t[2 * v + 1].mx > val) return findleft(2 * v + 1, tm + 1, tr, l, r, val);
        return -1;
    }
    int ans = -1;
    if (ans == -1 && tm >= l) ans = findleft(2 * v, tl, tm, l, r, val);
    if (ans == -1 && r > tm) ans = findleft(2 * v + 1, tm + 1, tr, l, r, val);
    // tr(tl, tr, ans);
    return ans; 
}


int solve() {
    cin >> n >> a;
    set<pii> curr;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        curr.insert({arr[i], i});
    }
    set<pii> :: iterator it;
    it = curr.end();
    it--; 
    build(arr, 1, 1, n);
    cin >> q;
    for (int i_ = 0; i_ < q; i_++) {
        char c;
        cin >> c;
        if (c == 'F') {
            int pos; cin >> pos;
            if (pos == a) {
                cout << 0 << endl;
                continue;
            } else if (pos > a) {
                auto m1 = get(1, 1, n, a + 1, pos);
                auto m2 = get(1, 1, n, 1, a - 1);
                // tr(m1.mx, m1.i1, m2.mx, m2.i1);
                if (m1.mx > m2.mx) {
                    cout << pos - 1 << endl;
                } else {
                    int where = findright(1, 1, n, 1, a - 1, m1.mx);
                    assert(where != -1);
                    cout << (pos - where - 1) << endl;
                }
            } else {
                auto m1 = get(1, 1, n, pos, a - 1);
                auto m2 = get(1, 1, n, a + 1, n);
                // tr(m1.mx, m1.i1, m2.mx, m2.i1);
                if (m1.mx > m2.mx) {
                    cout << (n - pos) << endl;
                } else {
                    int where = findleft(1, 1, n, a + 1, n, m1.mx);
                    // tr(where);
                    assert(where != -1);
                    cout << (where - pos - 1) << endl;
                }
            }
        } else {
            int pos, val;
            cin >> pos >> val;
            vector<pii> now;
            for (int i = 1; i < val; i++) {
                now.push_back(*it);
                it--;
            }
            auto lol = *it;
            now.push_back({lol.fi + 1, pos});
            curr.erase({arr[pos], pos});
            arr[pos] = lol.fi + 1;
            curr.insert({arr[pos], pos});
            // tr(pos, arr[pos]);
            update(1, 1, n, pos, arr[pos]);
            reverse(all(now));
            for (int i = 1; i < val; i++) {
                curr.erase(curr.find(now[i]));
                now[i].fi++;
                arr[now[i].se] = now[i].fi;
                curr.insert(now[i]);
                update(1, 1, n, now[i].se, now[i].fi);
            }
            it = curr.end();
            it--;
        }
        // tr(curr);
        // for (int i = 1; i <= n; i++) {
        //     cout << get(1, 1, n, i, i).mx << " ";
        // }
        // cout << endl;
    }
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
