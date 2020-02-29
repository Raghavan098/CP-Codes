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

#define int ll

// const int N = 1e6 + 10;

int n, s, a, b, c;
const int MOD = 1e9 + 7;
int inv;
int power(int x, int t){
    int ans = 1;
    while(t > 0) {
        if(t & 1) ans = 1LL * ans * x % c;
        x = 1LL * x * x % c;
        t >>= 1;
    }
    return ans;
}
int ans = 0;

void recurse(int l, int r, int st) {
    if (l == r) {
        ans += st;
        ans %= MOD;
        return;
    }
    if (l > r) return;
    int midval = st;
    int mid = (l + r) / 2;
    for (int i = l + 1; i <= mid; i++) {
        midval = ((midval * a) % c + b) % c;
    }
    int rp = mid;
    int curm = midval;
    int curval = midval;
    int curright = midval;
    for (int i = mid; i >= l; i--) {
        while (rp <= r && curright <= curm) {
            curright = (curright * a % c + b) % c;
            rp++;
        }
        ans += ((rp - mid) * curm) % MOD;
        ans %= MOD;
        curval = (((curval - b) % c + c) * inv) % c;
        curm = max(curm, curval);
    }
    int lp = mid;
    curm = -1;
    curval = midval;
    int curleft = midval;
    int start = 0;
    for (int i = mid + 1; i <= r; i++) {
        curval = ((curval * a) % c + b) % c;
        curm = max(curm, curval);
        while (lp >= l && curleft < curm) {
            start |= 1;
            curleft = (((curleft - b) % c + c) * inv) % c;
            lp--;
        }
        if (start) {
            ans += ((mid - lp) * curm) % MOD;
            ans %= MOD;
        }
    }
    int nxt = ((midval * a) % c + b) % c;
    recurse(l, mid - 1, st);
    recurse(mid + 1, r, nxt);
}

int solve() {
    cin >> n >> s >> a >> b >> c;
    // int curr = s;
    // for (int i = 0; i < n; i++){
    //     cout << curr << " ";
    //     curr = (curr * a + b) % c;
    // }
    // cout << endl;
    inv = power(a, c - 2);
    recurse(1, n, s);
    cout << ans << endl;
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
