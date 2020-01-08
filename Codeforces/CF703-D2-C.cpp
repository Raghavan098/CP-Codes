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

const int N = 1e4 + 100;

int n, w, v, u;
int x[N], y[N];

int32_t main(){ _
    cin >> n >> w >> v >> u;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    int done = 0;

    for (int i = 0; i < n; i++) {
        lld t1 = ((y[i] * 1.00) / u);
        lld t2 = ((x[i] * 1.00) / v);
        if (t1 > t2) {
            done = 1;
            break;
        }
    }
    lld ans;
    if (!done) {
        ans = w * 1.00 / u;
    } else {
        ans = w * 1.00 / u;
        for (int i = 0; i < n; i++) {
            lld t = (x[i] * 1.00 / v) + (((w - y[i]) * 1.00) / u);
            ans = max(ans, t);
        }
    }
    cout << setprecision(12) << ans << endl;

}
