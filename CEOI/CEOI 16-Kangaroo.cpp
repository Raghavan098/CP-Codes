/*

    component DP - Problem (new topic)
    https://codeforces.com/blog/entry/47764

    dp[i][j] -> number of ways of permutations till i with j components present. 
    basic idea is everytime we can either add new components or merge two existing components
    merging of two components is always valid because we are adding values in the increasing order and both the components will have end points whose value is less than current value.
    
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
#define __ freopen("kangaroo.in","r",stdin);freopen("kangaroo.out","w",stdout);
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

const int N = 2020;
const int MOD = 1e9 + 7;
int n, cs, cf;
int dp[N][N];

int f(int ind, int comp) {
    if (ind > n) return (comp == 1);
    if (comp < 0) return 0;
    int &ans = dp[ind][comp];
    if (ans != -1) return ans;
    ans = 0;
    if (ind == cs || ind == cf) {
        ans = f(ind + 1, comp + 1); // make a new component
        ans = (0LL + ans + f(ind + 1, comp)) % MOD; // just join with the existing component
        return ans;
    } else {
        // joining existing components;
        ans = (1LL * f(ind + 1, comp - 1) * (comp - 1)) % MOD;
        // adding new component;
        int pos = comp + 1; // available positions. 
        if (ind > cs) pos--;
        if (ind > cf) pos--;
        ans = (0LL + ans + 1LL * f(ind + 1, comp + 1) * pos) % MOD;
        return ans;
    }
}

int solve() {
    cin >> n >> cs >> cf;
    MEMS(dp, -1);
    cout << f(1, 0) << endl;
    return 0;
}

int32_t main(){ _
// __
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
