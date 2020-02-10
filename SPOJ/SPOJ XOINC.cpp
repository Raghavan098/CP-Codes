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

const int N = 2002;
const int inf = 2e9 + 1;
int dp[N][N][2][2];
int n;
int arr[N];


int sum(int i, int j) {
    return arr[j] - arr[i - 1];
}

int solve() {

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    reverse(arr + 1, arr + 1 + n);
    for (int i = 1; i <= n; i++) {
        arr[i] += arr[i - 1];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < 2; k++) {
                for (int p = 0; p < 2; p++) {
                    dp[i][j][k][p] = inf;
                }
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            dp[0][i][0][j] = 0;
            dp[0][i][1][j] = 0;
        }
    }
    int ans = -inf;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int p = 0; p < 2; p++) {
                int k = j * 2;
                if (i - j >= 0 && dp[i - j][k][1 ^ p][p] != inf) {
                    dp[i][j][p][p] = dp[i - j][k][1 ^ p][p] + sum(i - j + 1, i);
                    dp[i][j][p][1 ^ p] = dp[i - j][k][1 ^ p][1 ^ p];
                    if (i == n && j <= 2 && p == 0) ans = max(ans, dp[i][j][0][0]);
                }
            }
        }
        for (int j = 1; j <= n; j++) {
            for (int p = 0; p < 2; p++) {
                if (dp[i][j][p][p ^ 1] > dp[i][j - 1][p][p ^ 1]) {
                    dp[i][j][p][p] = dp[i][j - 1][p][p];
                    dp[i][j][p][p ^ 1] = dp[i][j - 1][p][p ^ 1];
                }
            }
        }
    }

    cout << ans << endl;
    
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
