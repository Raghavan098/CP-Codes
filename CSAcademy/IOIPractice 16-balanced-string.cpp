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

const int N = 55000;

int get(string s) {
    int n = s.size();
    if (n == 1) return 1;
    int a = 0, b = 0;
    if (s[0] == s[n - 1]) {
        if (s[0] == 'A') {
            a = 1;
        } else {
            b = 1;
        }
    }
    for (int i = 1; i < n; i++) {
        if (s[i] == s[i - 1] && s[i] == 'A') {
            a = 1;
        }
        if (s[i] == s[i - 1] && s[i] == 'B') {
            b = 1;
        }
    }
    if (a && b) return 0;
    if (a == 0 && b == 0) return 1;
    if (b == 1) {
        for (int i = 0; i < n; i++) {
            if (s[i] == 'A') s[i] = 'B';
            else s[i] = 'A';
        }
    }
    int done = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'B') {
            done = i;
            break;
        }
    }
    if (done == -1) return 1;
    string temp = s.substr(done, n - done) + s.substr(0, done);
    s = temp;
    vector<int> arr;
    int cnt = 0;
    for (int i = 1; i < n; i++) {
        if (s[i] == 'B') {
            arr.push_back(cnt);
            cnt = 0;
        } else {
            cnt++;
        }
    }
    arr.push_back(cnt);
    int mx = *max_element(all(arr));
    int mi = *min_element(all(arr));
    if (mx - mi > 1) return 0;
    if (mx - mi == 0) return 1;
    string nxt = "";
    for (int i : arr) {
        if (i == mx) {
            nxt += 'B';
        } else {
            nxt += 'A';
        }
    }
    // tr(s, nxt);
    return get(nxt);
}

int solve() {
    string s;
    cin >> s;
    cout << get(s) << endl;
    return 0;
}

int32_t main(){ _
    int t;
    cin >> t;
    // t = 1;
    while (t--) solve();
}
