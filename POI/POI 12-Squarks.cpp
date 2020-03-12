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


int n, m;
multiset<int> st;

vector<int> arr;
vector<vector<int>> ans;

inline void gen(int a, int b, int c) {
    multiset<int> tst = st;
    tst.erase(tst.find(a + b));
    tst.erase(tst.find(a + c));
    tst.erase(tst.find(b + c));

    vector<int> tans;
    tans.reserve(n);
    tans.push_back(a); tans.push_back(b); tans.push_back(c);
    for (int i = 3; i < n; i++) {
        if (tst.empty()) return;    
        int nxt = *tst.begin() - a;
        if (nxt < tans.back()) return;
        tans.push_back(nxt);
        for (int j = i - 1; j >= 0; j--) {
            auto it = tst.find(nxt + tans[j]);
            if (it == tst.end()) {
                return;
            }
            tst.erase(it);
        }
    }
    ans.push_back(tans);
}

int solve() {
    scanf("%d", &n);
    m = n * (n - 1) / 2;
    arr.resize(m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &arr[i]);
        st.insert(arr[i]);
    }
    sort(arr.begin(), arr.end());

    for (int i = 2; i < n; i++) {
        int ab = arr[0];
        int ac = arr[1];
        int bc = arr[i];
        if (i > 2 && arr[i] == arr[i - 1]) continue;
        if ((ab + ac + bc) % 2 == 0) {
            int abc = (ab + ac + bc) / 2;
            gen(abc - bc, abc - ac, abc - ab);
        }
    }
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", ans[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int32_t main(){ 
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
