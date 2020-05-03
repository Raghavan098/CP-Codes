// https://codeforces.com/blog/entry/59657?#comment-433683
/*
    https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2010_solutions/candies-sol.pdf
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

const int N = 101;
const int B = 7001;
const int MOD = 1e9 + 7;
int dp[N * B];
int n, arr[N];

vector<int> vals;
int ks[2 * N * B];
int sum = 0;

void add(int i) {
    for (int j = sum; j >= arr[i]; j--) {
        ll lol = dp[j - arr[i]] + dp[j];
        int x = lol / MOD;
        lol -= (x * MOD);
        while (lol > MOD) lol -= MOD;
        dp[j] = lol;
    }
}

void rem(int i) {
    for (int j = arr[i]; j <= sum; j++) {
        ll lol = dp[j] - dp[j - arr[i]];
        while (lol > MOD) lol -= MOD;
        while (lol < 0) lol += MOD;
        dp[j] = lol;
    }
}

int solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        sum += arr[i];
        add(i);
    }

    int ind = 1;
    int val = 0;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        rem(i);

        int cnt_crr = 0;
        for (int j = 1; j < N * B; j++) {
            if (dp[j] != 0) {
                cnt_crr++;
            }
        }

        if (cnt_crr > cnt) {
            cnt = cnt_crr;
            ind = i;
            val = arr[i];
        } else if (cnt_crr == cnt) {
            if (val > arr[i]) {
                val = arr[i];
                ind = i;
            }
        }
        add(i);
    }

    for (int i = 1; i <= n; i++) {
        if (i == ind) continue;
        vals.push_back(arr[i]);
        vals.push_back(-arr[i]);
    }

    int m = vals.size();
    ks[700000] = 1;
    int l = 0;
    int r = 0;
    // tr(vals);
    for (int i = 0; i < m; i++) {
        if (vals[i] > 0) {
            r += vals[i];
            for (int j = r; j >= l; j--) {
                int lol = ks[j -vals[i] + 700000] | ks[j + 700000];
                ks[j + 700000] = lol;
            }
        } else {
            l += vals[i];
            for (int j = l; j <= r; j++) {
                int lol = ks[j -vals[i] + 700000] | ks[j + 700000];
                ks[j + 700000]  = lol;
            }
        }
        // tr(l, r);

    }

    for (int i = 1; i <= 700000; i++) {
        if (ks[i + 700000] == 0) {
            cout << val << " " << i << endl;
            return 0;
        }
    }

    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
