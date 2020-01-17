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

int n, m;
vector<int> visited;
int curr;
vector<string> arr;
void dfs(int v) {
    curr++;
    visited[v] = 1;
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0 && arr[v][i] == 'Y') {
            dfs(i);
        }
    }
}

class TheCitiesAndRoadsDivTwo {
public:
    int find(vector<string> map) {
        //tr(map);
        arr = map;
		n = map.size();
        visited.resize(n);
        vector<int> comps;
        for (int i = 0; i < n; i++) {
            if (visited[i] == 0) {
                curr = 0;
                dfs(i);
                comps.push_back(curr);
            }
        }
        long long ans = 0;
        int k = comps.size();
        if (k == 1) {
            return 1;
        }
        ans = 1;
        for (int i = 0; i < k - 2; i++) {
            ans = ans * n;
        }
        for (int i = 0; i < k; i++) {
            ans = ans * comps[i];
        }
        return ans;
    }
};

int32_t main(){ _
    int n;
    cin >> n;
    vector<string> a;
    for (int i = 0; i < n; i++) {
        string temp;
        cin >> temp;
        a.push_back(temp);
    }
    TheCitiesAndRoadsDivTwo c;
    cout << c.find(a) << endl;
}
