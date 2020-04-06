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

const int N = 17;
string arr[N];
int dp[(1 << N)];
int freq[N][26];
int n;
const int inf = 1e9 + 1;

int f(int msk) {

    int &ans = dp[msk];
    if (ans != -1) {
        return ans;
    }
    ans = 0;
    int here[26];
    for (int i = 0; i < 26; i++) {
        here[i] = inf;
    }
    for (int i = 0; i < n; i++) {
        if (msk & (1 << i)) {
            for (int j = 0; j < 26; j++) {
                here[j] = min(here[j], freq[i][j]);
            }
        }
    }
    int overlap = 0;
    for (int i = 0; i < 26; i++) {
        overlap += here[i];
    }
    // tr(msk, overlap);
    if (__builtin_popcount(msk) == 1) {
        return ans = overlap;
    }
    ans = inf;
    for (int i = (msk - 1) & msk; i > 0; i = (i - 1) & (msk)) {
        ans = min(ans, f(i) + f(msk^i) - overlap);
    }
    return ans;
}
int solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        for (auto c : arr[i]) {
            int q = c - 'a';
            freq[i][q]++;
        }
    }
    MEMS(dp, -1);
    cout << f((1 << n) - 1) + 1 << endl;
}   

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
