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
#define __ freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
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

const int N = 1e5 + 100;

vector<int> arr;
int n, m;

int solve() {
    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        char c;
        cin >> c;
        arr.push_back(x);
    }
    if (n == 1) {
        cout << 0.00 << endl;
        return 0;
    }
    sort(arr.begin(), arr.end());

    vector<int> b;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) b.push_back(arr[i]);
        else b.push_back(2 * m - arr[i]);
    }
    sort(b.begin(), b.end());
    vector<lld> target;
    lld gap = (2.0 * m) / (1.0 * n);
    lld curr = b[0];   
    target.push_back(0.0);
    for (int i = 1; i < n; i++) {
        curr += gap;
        target.push_back((lld)b[i] - curr);
    }
    sort(target.begin(), target.end());
    lld ans = (target.back() - target[0]) / 2.0;
    cout << fixed << setprecision(12) << ans << endl;
    return 0;
}   

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
