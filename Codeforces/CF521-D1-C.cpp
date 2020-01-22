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
const int N = 1e5 + 100;

int n, k;
string s;

int power(int x, int t){
    int ans = 1;
    while(t > 0) {
        if(t & 1) ans = 1LL * ans * x % MOD;
        x = 1LL * x * x % MOD;
        t >>= 1;
    }
    return ans;
}
inline int sub(int a, int b){
    a %= MOD;
    b %= MOD;
    a = ((a - b) % MOD + MOD) % MOD;
    return a;
}

inline int add(int a, int b){
    a %= MOD;
    b %= MOD;
    a = (a + b) % MOD;
    return a;
}

inline int mul(int a, int b){
    a %= MOD;
    b %= MOD;
    a = (a * b) % MOD;
    return a;
}

inline int inv(int a){
    a = a % MOD;
    a = power(a, MOD - 2);
    return a;
}

int fac[N + 10], ifac[N + 10];

void init_fac(){
    fac[0] = 1;
    for(int i = 1; i < N; i++){
        fac[i] = (fac[i - 1] * i) % MOD;
    }
    ifac[N - 1] = power(fac[N - 1], MOD - 2);
    for(int i = N - 1; i >= 1; i--){
        ifac[i - 1] = (ifac[i] * i) % MOD;
    }
}

int C(int n, int m)
{
	if(n < m) return 0;
	return fac[n] * (1LL * ifac[m] * ifac[n - m] % MOD) % MOD;
}


int solve() {
    cin >> n >> k;
    cin >> s;
    vector<int> c(n);
    c[0] = s[0] - '0';
    for (int i = 1; i < n; i++) {
        int x = s[i] - '0';
        c[i] += c[i - 1];
        c[i] += x;
    }
    int ans = 0;

    
    /*

    \sum_{l=1}^{n} \sum_{i=0}^{n-l-1}\{s_i * 10^{l-1} * \binom{n-l-1}{k-1} + 
                                            s_i*10^{l-1}*\binom{n-l}{k} \}

    */
    for (int l = 1; l <= n; l++) {
        int cs = c[n - l - 1];
        ans = add(ans, mul(power(10, l - 1), mul(C(n - l - 1, k - 1), cs)));
        int val = mul(int(s[n - l] - '0'), mul(power(10, l - 1), C(n - l, k)));
        ans = add(ans, val);
    }
    cout << ans << endl;
}

int32_t main(){ _
    init_fac();
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
