/*
    very common knapsack dp.
    the complexity becomes nk^2
    to make it nk we optimise the dp with deque as mentioned in http://www.algonotes.com/en/knapsacks/
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

// #define int ll

const int N = 201;
const int M = 20001;
const int inf = 1e9 + 1;
int n, k;
int b[N], c[N];
int dp[N][M];
int back[N][M];

#define piii pair<pair<int, int>, int>

struct minq {
    deque<piii> d;
    int offset;
    int l, r;
    minq() {
        offset = 0;
        l = r = 0;
    }
    void pop() {
        while (!d.empty() && d.front().fi.fi == l) d.pop_front();
        l++;
    }

    int window_size() {
        return (r - l);
    }
    void push(int x, int ii) {
        while (!d.empty() && d.back().fi.se + offset >= x) d.pop_back();
        d.push_back({{r, x - offset}, ii});
        r++;
    }

    int getmin() {
        if (d.empty()) return inf;
        return (d.front().fi.se + offset);
    }
};

int solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    cin >> k;
    
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) dp[i][j] = inf;

    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        vector<minq> arr(b[i], minq());
        for (int j = 0; j <= k; j++) {
            int m = j % b[i];
            while (arr[m].window_size() > c[i]) arr[m].pop();
            arr[m].offset++;
            arr[m].push(dp[i - 1][j], j);
            dp[i][j] = arr[m].getmin();
            back[i][j] = (j - arr[m].d.front().se) / b[i];
        }
    }   

    cout << dp[n][k] << endl;
    vector<int> ans(n);
    int cw = k, ind = n;
    while (ind >= 1) {
        int no = back[ind][cw];
        ans[ind - 1] = no;
        cw -= (no * b[ind]);
        ind--;
    }
    cout << ans << endl;

    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
    return 0;
}
