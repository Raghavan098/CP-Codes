/*
    - http://codeforces.com/blog/entry/57637?#comment-413356 (Problem 3)
*/

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
#define MEMS(a,b) memset(a,b,sizeof(a))
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define __ freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define all(c) c.begin(),c.end()
#define pii pair<int, int>

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r)
{
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

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
template <typename T>
ostream &operator<<(ostream &out, multiset<T> const &v) {
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


const int N = 3003;

int dp[N][N][3];

int n, m;
string arr[N];
string s = "RGW";
int hori_valid(int i, int j) {
    int done = 0;
    for (int k = j - 1; k < j + 2; k++) {
        if (k < 0 || k >= m || arr[i][k] != s[k - j + 1]) {
            done = 1;
            break;
        }
    }
    return (done == 0);
}

int vert_valid(int i, int j) {
    int done = 0;
    for (int k = i - 1; k < i + 2; k++) {
        if (k < 0 || k >= n || arr[k][j] != s[k - i + 1]) {
            done = 1;
            break;
        }
    }
    return (done == 0);
}

// 0-> noting 1-> hori, 2 -> vertical

int f(int i, int j, int k) {
    if (i >= n || i < 0 || j >= m || j < 0) return 0;
    int &ans = dp[i][j][k];
    if (ans != -1) return ans;
    ans = 0;
    if (k == 0) {
        if (hori_valid(i, j)) {
            ans = 1 + f(i - 1, j + 1, 1);
        }
        if (vert_valid(i, j)) {
            ans = max(ans, 1 + f(i - 1, j + 1, 2));
        }
        ans = max(ans, f(i - 1, j + 1, 0));
    } else if (k == 1) {
        if (hori_valid(i, j)) {
            ans = 1 + f(i - 1, j + 1, 1);
        }
        ans = max(ans, f(i - 1, j + 1, 0));
    } else {
        if (vert_valid(i, j)) {
            ans = 1 + f(i - 1, j + 1, 2);
        }
        ans = max(ans, f(i - 1, j + 1, 0));
    }
    return ans;
}

int solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    MEMS(dp, -1);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += f(i, 0, 0);
    }
    for (int j = 1; j < m; j++) {
        ans += f(n - 1, j, 0);
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
