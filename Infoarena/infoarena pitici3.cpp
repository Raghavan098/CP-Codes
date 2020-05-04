// g++ -std=c++14
/*
    "Given n dwarfs, each one having a height and a length of hands, find the maximum number of dwarfs which can get out of a hole
with height D. A dwarf can get out of the hole if he can get to a height >= D, using his hands, his height and possibly the heights of other
dwarfs"
    * Since n isn't very big, we will try to use DP to find the answer. Let dp[i][j] = maximum height we are still left with if we tried to help
dwarfs from set {1, 2, ..., i} and we got j dwarfs out of the hole.
    * Before running the DP, it's worth mentioning that it's always more optimal to help the weakest dwarfs(those with the smallest sum of height and
length of hands) so we will sort the dwarfs increasingly by this sum.
    * Therefore, the recurrence isn't very hard, dp[i][0] = sum of heights, and dp[i][j] = max(dp[1][j-1], dp[2][j-1], ..., dp[i-1][j-1]) - height[i],
as long as we can actually help dwarf i to get out of the hole. In order to avoid O(n^3) runtime, we are going to keep prefix maximum.
    * The answer will be the biggest j such that there is some dp[i][j] which can be reached
*/
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
#define __ freopen("pitici3.in","r",stdin);freopen("pitici3.out","w",stdout);
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

// #define int ll

const int N = 2020;
int dp[N][N];
int n, d;
pii arr[N];

int solve() {
    cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].fi >> arr[i].se;
        sum += arr[i].fi;
    }
    cin >> d;
    sort(arr + 1, arr + 1 + n, [](pii a, pii b) -> bool{
        return (a.fi + a.se < b.fi + b.se);
    });
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j )
    // }
    // for (int i = 1; i <= n; i++) {
    //     cout << arr[i] << " ";
    // }
    // cout << endl;   
    MEMS(dp, -1);
    dp[0][0] = sum;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        // dp[i][0] = sum;
        for (int j = 0; j < i; j++) {
            if (dp[i - 1][j] == -1) continue;
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            if (dp[i - 1][j] + arr[i].se >= d) {
                dp[i][j + 1] = max(dp[i][j + 1], dp[i - 1][j] - arr[i].fi);
                ans = max(ans, j + 1);
            }
        }
        for (int j = 0; j <= i; j++) {
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
    }
    cout << ans << endl;
    return 0;
}

int32_t main(){ _
__
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
