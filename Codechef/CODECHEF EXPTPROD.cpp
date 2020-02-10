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

const int MOD = 1e9 + 7;
const int LOG = 31;
int power(int x, int t){
    int ans = 1;
    while(t > 0) {
        if(t & 1) ans = 1LL * ans * x % MOD;
        x = 1LL * x * x % MOD;
        t >>= 1;
    }
    return ans;
}

int solve() {
    int n, kk;
    cin >> n >> kk;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    vector<vector<int>> f(LOG, vector<int> (n));
    f[0][1] = 1;
    for (int i = 1; i <= n; i++) {
        f[1][arr[i]]++;
    }
    for (int i = 2; i < LOG; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                int z = j * k % n;
                f[i][z] = (f[i][z] + (f[i - 1][j] * f[i - 1][k]) % MOD) % MOD;
            }
        }
    }
    // for (int i = 0; i < LOG; i++) {
    //     tr(i, f[i]);
    // }
    vector<int> ans(n);
    ans[1] = 1;
    for (int i = 0; i < LOG; i++) {
        if (kk & (1LL << i)) {
            vector<int> temp(n);
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    int z = j * k % n;
                    temp[z] = (temp[z] + ans[j] * f[i + 1][k] % MOD) % MOD;
                }
            }
            ans = temp;
        }
    }
    int tot = 0;
    for (int i = 0; i < n; i++) {
        tot += (ans[i] * i) % MOD;
        tot %= MOD;
    }
    int denom = power(n, kk);
    denom = power(denom, MOD - 2);
    tot = tot * denom % MOD;
    cout << tot << endl;
}

int32_t main(){ _
    int t;
    cin >> t;
    // t = 1;
    while (t--) solve();
}
