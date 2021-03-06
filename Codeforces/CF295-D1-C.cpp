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

const int N = 55;
const int MOD = 1e9 + 7;

int fac[N + 10], ifac[N + 10];

int power(int x, int t){
    int ans = 1;
    while(t > 0) {
        if(t & 1) ans = 1LL * ans * x % MOD;
        x = 1LL * x * x % MOD;
        t >>= 1;
    }
    return ans;
}

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


int a[2];
int n, k;
pair<int, int> dp[N][N][2]; // fi -> ways, se -> dist

struct node {
    int x, y, dist, side;
};



int solve() {
    init_fac();
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[x != 50]++;
    }
    queue<node> q;
    q.push({a[0], a[1], 0, 0});
    dp[a[0]][a[1]][0].fi = 1;
    while (!q.empty()) {
        auto f = q.front();
        if (f.side == 1 && f.x == a[0] && f.y == a[1]) {
            cout << dp[a[0]][a[1]][1].se << endl << dp[a[0]][a[1]][1].fi << endl;
            return 0;
        }
        q.pop();
        int nxt = f.side ^ 1;
        int x2 = a[0] - f.x;
        int y2 = a[1] - f.y;
        for (int i = 0; i <= f.x; i++) {
            for (int j = 0; j <= f.y; j++) {
                if (i == 0 && j == 0) continue;
                int totx = i + x2;
                int toty = j + y2;
                int ways = C(f.x, i) * C(f.y, j) % MOD;
                if (i * 50 + j * 100 <= k) {
                    if (dp[totx][toty][nxt].fi == 0) {
                        dp[totx][toty][nxt].fi = ways * dp[f.x][f.y][f.side].fi % MOD;
                        dp[totx][toty][nxt].se = f.dist + 1;
                        q.push({totx, toty, f.dist + 1, nxt});
                    } 
                    else if (dp[totx][toty][nxt].se = f.dist + 1) {
                        dp[totx][toty][nxt].fi += ways * dp[f.x][f.y][f.side].fi % MOD;
                        dp[totx][toty][nxt].fi %= MOD;
                    }
                }
            }
        }
    }
    cout << -1 << endl << 0 << endl;
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
