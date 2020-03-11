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
#define __ freopen("sabin.in","r",stdin);freopen("sabin.out","w",stdout);
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


int n, m, q, k, p;
unordered_map<string, int> cnt;
vector<string> marr;

int get_cnt(int len, vector<int> &a) {
    if (len == 0) return n;
    if (len == p + 1) return 0;
    string temp = "";
    for (int i = 1; i <= len; i++) {
        for (int j = 0; j < k; j++) {
            temp += marr[a[j]][i - 1];
        }
    }
    // tr(temp, cnt[temp], len);
    return cnt[temp];
}

int solve() {
    cin >> n >> k >> m >> p >> q;
    for (int i = 0; i < n; i++) {
        vector<string> a;
        for (int j = 0; j < k; j++) {
            string temp;
            cin >> temp;
            a.push_back(temp);
        }
        string temp = "";
        for (int len = 1; len <= p; len++) {
            for (int j = 0; j < k; j++) {
                temp += a[j][len - 1];
            }
            cnt[temp]++;
        }
    }
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        marr.push_back(s);
    }

    for (int i_ = 0; i_ < q; i_++) {
        int len;
        cin >> len;
        vector<int> qs;
        for (int i = 0; i < k; i++) {
            int j; cin >> j;
            qs.push_back(j - 1);
        }
        int a = get_cnt(len, qs);
        int b = get_cnt(len + 1, qs);
        cout << a - b << endl;
    }
    return 0;
}

int32_t main(){ _
__
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
