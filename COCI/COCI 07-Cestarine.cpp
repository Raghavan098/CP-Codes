/*
    if the condition that entrance != exit is not there then the answer is sort both the arrays and calulate the value
    otherwise one observation is that max distance that a number will be away from sorted position is only atmax 2 
    that is if the position of element in sorted array is i then in the final matching the position will be atmax i+2 or i-2 that's ti
    now use dp to get the best value
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

#define int ll

const int N = 1e5 + 10;

int n;
vector<int> a, b;

int dp[N];

int f(int ind) {
    if (ind == 0) return 0;
    int &ans = dp[ind];
    if (ans != -1) return ans;
    ans = 1e12;
    for (int k = 0; k < 3; k++) {
        if (ind - k <= 0) break;
        vector<int> t1, t2;
        for (int i = ind; i >= ind - k; i--) {
            t1.push_back(a[i]);
            t2.push_back(b[i]);
        }
        sort(all(t1));
        sort(all(t2));
        do {
            // tr(ind, t1, t2);
            int done = 0;
            for (int i = 0; i <= k; i++) {
                if (t1[i] == t2[i]) done = 1; 
            }
            if (!done) {
                int temp = 0;
                for (int i = 0; i <= k; i++) {
                    temp += abs(t1[i] - t2[i]);
                }
                ans = min(ans, temp + f(ind - k - 1));
            }
        } while(next_permutation(all(t2)));
    }
    // tr(ind, ans);
    return ans;
}

int solve() {
    cin >> n;
    a.push_back(0);
    b.push_back(0);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a.push_back(x);
        b.push_back(y);
    }
    sort(all(a));
    sort(all(b));
    MEMS(dp, -1);
    cout << f(n) << endl;
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
