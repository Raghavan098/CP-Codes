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

// #define int ll

const int N = 1e6 + 100;

int n, k;

int arr[N];
int m, l;
vector<int> x, y;
int leftbefore[N];
int rightnxt[N];
vector<vector<int>> ind(N);

int ansleft[N], ansright[N];

int mxright[N];

int solve() {
    // MEMS(leftbefore, -1);
    // MEMS(rightnxt, -1);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    cin >> m >> l;
    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        x.push_back(t);
    }
    for (int i = 1; i < m; i++) {
        leftbefore[x[i]] = x[i - 1];
    }
    for (int i = 0; i < l; i++) {
        int t;
        cin >> t;
        y.push_back(t);
    }
    reverse(all(y));
    for (int i = 0; i < l - 1; i++) {
        rightnxt[y[i]] = y[i + 1];
    }

    for (int i = 1; i <= n; i++) {
        if (arr[i] == x[0]) {
            ansleft[i] = i;
        } else {
            int temp = leftbefore[arr[i]];
            if ((int)ind[temp].size() > 0) {
                ansleft[i] = ansleft[ind[temp].back()];
            } else {
                ansleft[i] = -1;
            }
        }
        ind[arr[i]].push_back(i);
    }

    for (int i = 1; i <= k; i++) {
        ind[i].clear();
    }

    for (int i = n; i >= 1; i--) {
        if (arr[i] == y[l - 1]) {
            ansright[i] = i;
        } else {
            int temp = rightnxt[arr[i]];
            if ((int)ind[temp].size() > 0) {
                ansright[i] = ansright[ind[temp].back()];
            } else {
                ansright[i] = -1;
            }
        }
        ind[arr[i]].push_back(i);
    }

    // for (int i = 1; i <= n; i++) {
    //     cout << ansleft[i] << " ";
    // }
    // cout << endl;
    
    // for (int i = 1; i <= n; i++) {
    //     cout << ansright[i] << " ";
    // }
    // cout << endl;
    int mx = -1;
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (ansright[i] != -1 && ansleft[i] != -1 && arr[i] == y[0]) {
            int l = ansleft[i], r = ansright[i];
            if (mxright[l - 1] > r) {
                ans.push_back(i);
            }
        }
        mxright[i] = mxright[i - 1];
        mxright[i] = max(mxright[i], ind[arr[i]][0]);
    }
    cout << (int)ans.size() << endl;
    for (int i : ans) {
        cout << i << " ";
    }
    cout << endl;
    return 0;

}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
