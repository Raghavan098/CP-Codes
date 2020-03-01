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
#define __ freopen("desc.in","r",stdin);freopen("desc.out","w",stdout);
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

const int inf = 1e12;

int solve() {
    int n, k;
    cin >> n >> k;
    vector<int> div;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            div.push_back(i);
            if ((n / i) != i) {
                div.push_back(n / i);
            }
        }
    }
    sort(all(div));
    map<int, int> inv;
    // tr(div);
    int m = div.size();
    for (int i = 0; i < m; i++) {
        inv[div[i]] = i;
    }
    vector<vector<int>> dp(m + 1, vector<int> (m + 1));
    dp[0][0] = 1;
    for (int i = 1; i < m; i++) {
        dp[i][i] = 1;
        for (int j = i - 1; j >= 0; j--) {
            if (div[i] % div[j] == 0) {
                int x = div[i] / div[j];
                dp[i][j] += dp[inv[x]][j];
                dp[i][j] += dp[i][j + 1];
            } else {
                dp[i][j] = dp[i][j + 1];
            }
        }
    }
    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < m; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    int curr = n;
    vector<int> ans;
    int cp = 1;
    while (k) {

        int j = inv[curr];
        if (j == cp && k == 1) {
            ans.push_back(div[j]);
            break;
        }
        int x = -1;
        if (curr % div[cp] == 0) {
            x = inv[curr / div[cp]];
        }
        if (x != -1 && curr % div[cp] == 0 && dp[x][cp] < k) {
            k -= dp[x][cp];
            cp++;
        } else if (x != -1 && curr % div[cp] == 0) {
            ans.push_back(div[cp]);
            curr /= div[cp];
        } else {
            cp++;
        }
    }
    cout << dp[m - 1][0] << endl;
    cout << ans << endl;
    // tr(ans);
    return 0;
}

int32_t main(){ _
__
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
