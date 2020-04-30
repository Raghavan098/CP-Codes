/*

    for each index j we will calculate the answer. 
    suppose the cumulative sums at j are (c1, c2.. ck) for k strings.
    it is easy to see that number of good substrings that start at j are number of (c1, c2.. ck) after j
    there is just one more condition left to check. That is no where in between the subarray sum should go negative.
    so for each of the string we'll see the nearest position where the subarray sum will go negative
    then we'll just count the number (c1, c2, ... ck) in before that nearest position

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
#define __ freopen("cbs.in","r",stdin);freopen("cbs.out","w",stdout);
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

#define int ll
const int N = 5e4 + 100;
int n, k;

string arr[20];
int cumu[20][N];

int dp[20][N];

map<vector<int>, vector<int>> ind;

int near[20];

int get_cnt(vector<int> &ss, int l, int r) {
    auto lower = lower_bound(ind[ss].begin(), ind[ss].end(), l);
    auto upper = lower_bound(ind[ss].begin(), ind[ss].end(), r);
    if (upper == ind[ss].end()) {
        upper--;
    } else if (*upper > r) {
        upper--;
    }
    int x = upper - lower + 1;
    if (x <= 0) return 0;
    return x;
}

int solve() {
    cin >> k >> n;
    for (int i = 1; i <= k; i++) {
        cin >> arr[i];
        arr[i] = '#' + arr[i];
    }
    vector<int> temp(k, 0);
    ind[temp].push_back(0);
    for (int j = 1; j <= n; j++) {
        vector<int> curr;
        for (int i = 1; i <= k; i++) {
            cumu[i][j] = cumu[i][j - 1];
            if (arr[i][j] == ')') cumu[i][j]--;
            else cumu[i][j]++;
            curr.push_back(cumu[i][j]);
        }
        ind[curr].push_back(j);
    }

    for (int i = 1; i <= k; i++) {
        stack<int> s;
        s.push(n);
        for (int j = n - 1; j >= 0; j--) {
            while (!s.empty() && cumu[i][s.top()] >= cumu[i][j]) s.pop();
            if (s.empty()) {
                dp[i][j] = n + 1;
            } else {
                dp[i][j] = s.top();
                // tr(cumu[i][j], cumu[i][s.top()], i, j, s.top());
            }
            // tr(cumu[i][j], dp[i][j], i, j);
            s.push(j);
        }
    }

    // for (int i = 1; i <= k; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         cout << cumu[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    // for (int i = 1; i <= k; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // cout << endl;

    int ans = 0;
    for (int j = 0; j < n; j++) {
        int mx = n;
        int done = 0;
        for (int i = 1; i <= k; i++) {
            mx = min(mx, dp[i][j] - 1);
        }
        if (done) continue;
        vector<int> curr;
        for (int i = 1; i <= k; i++) {
            curr.push_back(cumu[i][j]);
        }

        int cnt = get_cnt(curr, j, mx);
        // tr(j, mx, cnt, curr);
        ans += (cnt - 1);
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
