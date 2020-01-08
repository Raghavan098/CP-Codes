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

const int N = 2e5 + 100;
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

vector<vector<int>> C(N);
int n, x, y;
vector<pair<int, pair<int, int>>> comp;

int32_t main(){ _
    init_fac();
    cin >> n >> x >> y;
    for (int i = 0; i < n; i++) {
        int c, w;
        cin >> c >> w;
        C[c].push_back(w);
    }
    for (int i = 1; i <= n; i++) {
        sort(all(C[i]));
    }
    for (int i = 1; i <= n; i++) {
        if ((int)C[i].size() == 0) continue;
        int miw = C[i][0];
        int tmp = 0;
        int done = -1;
        for (int j = 0; j < (int)C[i].size(); j++) {
            if ((C[i][j] + miw) <= x) {
                tmp++;
            } else {
                done = j;
                break;
            }
        }
        comp.push_back({miw, {tmp, i}});
        if (done == -1) continue;
        for (int j = done; j < (int)C[i].size(); j++) {
            comp.push_back({C[i][j], {1, i}});
        }
    }
    sort(all(comp));
    if (!(int)comp.size()) {
        cout << 0 << endl;
        return 0;
    }
    vector<int> final(N);
    int miw = comp[0].fi;
    final[comp[0].se.se] += comp[0].se.fi;
    int d1 = -1;
    int d2 = -1;
    for (int j = 1; j < (int)comp.size(); j++) {
        if (comp[j].se.se != comp[0].se.se) {
            d1 = comp[j].se.se;
            d2 = comp[j].fi;
            break;
        }
    }
    int tot = comp[0].se.fi;
    for (int i = 1; i < (int)comp.size(); i++) {
        if (comp[0].se.se != comp[i].se.se) {
            if (miw + comp[i].fi <= y) {
                final[comp[i].se.se] += comp[i].se.fi;
                tot += comp[i].se.fi;
            }
        } else {
            if (d1 != -1) {
                if (d2 + comp[i].fi <= y) {
                    final[comp[i].se.se] += comp[i].se.fi;
                    tot += comp[i].se.fi;
                }
            }
        }
    }
    int ans = fac[tot];
    for (int i = 0; i < N; i++) {
        ans = (ans * ifac[final[i]]) % MOD;
    }
    cout << ans << endl;
}
