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

class MarriageProblemRevised {
public:
	int neededMarriages(vector <string>);
};

int MarriageProblemRevised::neededMarriages(vector <string> preferences) {
	int n = preferences.size();
    int m = preferences[0].size();
    vector<int> maskman(n), maskwomen(m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (preferences[i][j] == '1') {
                maskwomen[i] |= (1 << j);
                maskman[j] |= (1 << i);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (maskwomen[i] == 0) return -1;
    }
    for (int i = 0; i < m; i++) {
        if (maskman[i] == 0) return -1;
    }
    int ans = 1e9;
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < (1 << m); j++) {
            int totmen = 0;
            int totwomen = 0;
            for (int k = 0; k < n; k++) {
                if (i & (1 << k) && maskwomen[k] != 0) {
                    totwomen |= (maskwomen[k]);
                    totmen |= (1 << k);
                }
                
            }
            for (int k = 0; k < m; k++) {
                if (j & (1 << k) && maskman[k] != 0) {
                    totmen |= (maskman[k]);
                    totwomen |= (1 << k);
                }
            }
        }
    }
    return ans;
}

// int32_t main(){ _
//     MarriageProblemRevised m;
//     int n;
//     cin >> n;
//     vector<string> arr(n);
//     for (int i = 0; i < n; i++) {
//         cin >> arr[i];
//     }
//     tr(m.neededMarriages(arr));
// }
