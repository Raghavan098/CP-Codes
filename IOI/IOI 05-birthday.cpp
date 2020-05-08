// g++ -std=c++14

// https://www.oi.edu.pl/old/ioi/downloads/ioi2005-tasks-and-solutions-a5.pdf

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

const int N = 1e6 + 100;

int n, arr[N];
int brr[N];

int get() {
    for (int i = 0; i < n; i++) {
        brr[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        int x = (arr[i] - i + n) % n;
        brr[x]++;
    }
    int cnt = 0;
    int tot = 0;
    for (int i = 0; i < n; i++) {
        if (brr[i]) {
            cnt = 0;
        } else {
            cnt++;
        }
        tot = max(tot, cnt);
    }
    cnt = 0;
    for (int i = 0; i < n; i++) {
        if (brr[i]) break;
        cnt++;
    }
    for (int i = n - 1; i >= 0; i--) {
        if (brr[i]) break;
        cnt++;
    }

    tot = max(tot, cnt);
    return (n - tot) / 2;
    
}

int solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        arr[x - 1] = i;
    }
    int ans = get();
    reverse(arr, arr + n);
    ans = min(ans, get());
    cout << ans << endl;
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
