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
#define inf 1000000000000000001
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

const int AL = 5;

int t, f;
int cnt;

int get(int ind) {
    cnt++;
    cout << ind << endl;
    fflush(stdout);
    char ans;
    cin >> ans;
    int tt = ans - 'A' + 1;
    return tt;
}

int solve() {
    cnt = 0;
    int fac[6];
    fac[0] = 1;
    for (int i = 1; i <= AL; i++) {
        fac[i] = fac[i - 1] * i;
    }
    vector<int> ind;
    vector<int> pref;
    for (int i = 1, j = 1; j <= fac[AL]; i += AL, j++) {
        ind.push_back(i);
    }
    ind.pop_back();
    for (int i = 1; i <= AL; i++) {
        map<vector<int>, vector<int>> curr;
        for (auto j : ind) {
            auto tp = pref;
            int k = get(j + i - 1);
            tp.push_back(k);
            curr[tp].push_back(j);
        }
        int req = fac[AL - i];
        if ((int)pref.size() >= AL - 2) {
            for (auto j : curr) {
                pref = j.fi;
                ind = j.se;
                break;
            }
            continue;
        }
        for (auto j : curr) {
            if ((int)j.se.size() == (req - 1)) {
                pref = j.fi;
                ind = j.se;
                break;
            }
        }
    }
    swap(pref[AL - 1], pref[AL - 2]);
    for (auto i : pref) {
        cout << (char)('A' + (i - 1));
    }
    cout << endl;
    fflush(stdout);
    char verd;
    cin >> verd;
    assert(verd == 'Y');
    return 0;
}

int32_t main(){ 
    cin >> t >> f;
    // t = 1;
    while (t--) solve();
}