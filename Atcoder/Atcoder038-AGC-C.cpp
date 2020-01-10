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

const int N = 1e6 + 100;
const int MOD = 998244353;

int n, arr[N];
int cnt[N];
int f[N], g[N];
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


int c2(int x) {
    int temp = (x * (x - 1)) / 2;
    return temp % MOD;
}

int32_t main(){ _
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        cnt[arr[i]]++;
    }
    int ans = 0;
    for (int i = N - 1; i >= 1; i--) {
        int s = 0;
        for (int j = i; j < N; j += i) {
            f[i] = sub(f[i], f[j]);
            f[i] = add(f[i], mul(s, mul(cnt[j], j)));
            f[i] = add(f[i], mul(c2(cnt[j]), mul(j, j)));
            s = add(s, mul(cnt[j], j));
        }
        ans = add(ans, mul(f[i], inv(i)));
    }
    cout << ans << endl;
}