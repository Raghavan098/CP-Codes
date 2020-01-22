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

int solve() {
    int n;
    cin >> n;
    vector<vector<int>> arr(n + 1);
    vector<vector<int>> rank(n + 1, vector<int> (n + 1));
    for (int i = 1; i <= n; i++) {
        arr[i].push_back(0);
        for (int j = 1; j <= n; j++) {
            int t;
            cin >> t;
            arr[i].push_back(t);
            rank[i][t] = j;
        }
    }   
    int p;
    cin >> p;
    vector<int> ans;
    if (p == 1) {
        for (int i = 1; i <= n; i++) {
            if (arr[i][1] == i) ans.pb(i);
        }
        
    } else {
        for (int i = 1; i <= n; i++) {
            int crack = 0;
            for (int j = 1; j <= n; j++) {
                int curr = rank[j][i];
                int noo = 0;
                for (int k = 1; k < curr; k++) {
                    int no = arr[j][k];
                    int temp_rank = rank[no][no];
                    // tr(i, j, k, no, temp_rank);
                    int done = 0;
                    for (int q = 1; q < temp_rank; q++) {
                        int omg = arr[no][q];
                        if (rank[j][omg] >= curr) {
                            done = 1;
                            break;
                        }
                    }
                    if (done == 0) {
                        noo = 1;
                        break;
                    }   
                }
                if (noo == 0) {
                    crack = 1;
                    break;
                }
            }
            if (crack == 1) {
                ans.push_back(i);
            }
        }
    }
    cout << (int)ans.size() << endl;
    for (auto &i : ans) {
        cout << i << " ";
    }
    cout << endl;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
