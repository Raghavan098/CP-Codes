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
#define inf 1e15
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

int n, a;
int d[N], c[N];

int arr[N];

pair<int, int> t[4*N];
pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
    pii ans;
    ans.fi = max(a.fi, b.fi);
    ans.se = min(a.se, b.se);
    return ans;
}

void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = make_pair(a[tl], a[tl]);
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}

pair<int, int> get(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return make_pair(-inf, inf);
    if (l == tl && r == tr)
        return t[v];
    int tm = (tl + tr) / 2;
    return combine(get(v*2, tl, tm, l, min(r, tm)), 
                   get(v*2+1, tm+1, tr, max(l, tm+1), r));
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] = make_pair(new_val, 1);
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}

int f[N];

int lp[N], rp[N];
int32_t main(){ _
    cin >> n >> a;
    for (int i = 1; i <= n; i++) {
        cin >> d[i] >> c[i];
        arr[i] = a - c[i];
        arr[i] += arr[i - 1];
    }
    build(arr, 1, 0, n);
    for (int i = 2; i <= n; i++) {
        f[i] = (d[i - 1] - d[i]) * (d[i - 1] - d[i]);
    }
    stack<int> s;
    s.push(0);
    for (int i = 1; i <= n; i++) {
        while (s.top() != 0 && f[s.top()] <= f[i]) s.pop();
        lp[i] = s.top() + 1;
        s.push(i);
    }
    while (!s.empty()) s.pop();
    s.push(n + 1);
    for (int i = n; i >= 1; i--) {
        while (s.top() != (n + 1) && f[s.top()] <= f[i]) s.pop();
        rp[i] = s.top() - 1;
        s.push(i);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int temp_ans;
        auto p1 = get(1, 0, n, max(0LL, lp[i] - 2), max(0LL, i - 2));
        auto p2 = get(1, 0, n, i, rp[i]);
        temp_ans = p2.fi - p1.se - f[i]; 
        ans = max(ans, temp_ans);
    }
    for (int i = 1; i <= n; i++) {
        ans = max(ans, arr[i] - arr[i - 1]);
    }
    cout << ans << endl;
}