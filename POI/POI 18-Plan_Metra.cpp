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

// #define int ll

const int N = 5e5 + 100;

vector<vector<pii>> g(N);
int n;
int a[N], b[N];
const int inf = 1e9 + 10;
int visited[N];
int dist[N];
int solve() {
    cin >> n;
    for (int i = 2; i <= n - 1; i++) {
        cin >> a[i];
    }
    for (int i = 2; i <= n - 1; i++) {
        cin >> b[i];
    }  
    if (n == 2) {
        cout << "TAK\n";
        cout << 1 << " " << 2 << " " << 5 << endl;
        return 0;
    } 
    map<int, int> diff;
    for (int i = 2; i <= n - 1; i++) {
        diff[abs(a[i] - b[i])]++;
    }
    int cliche = ((diff.begin() -> fi) == 0);
    if ((int)diff.size() == 1 && !cliche) {
        cout << "TAK\n";
        cout << 1 << " " << n << " " << diff.begin() -> fi << endl;
        for (int i = 2; i <= n - 1; i++) {
            if (a[i] > b[i]) {
                cout << n << " " << i << " " << b[i] << endl;
            } else {
                cout << 1 << " " << i << " " << a[i] << endl;
            }
        }
        return 0;
    }
    int mi = inf;
    vector<int> arr;
    int cnt = 0;
    for (int i = 2; i <= n - 1; i++) {
        if (a[i] + b[i] < mi) {
            mi = a[i] + b[i];
            cnt = 1;
            arr.clear();
            arr.push_back(i);
        } else if (a[i] + b[i] == mi) {
            cnt++;
            arr.push_back(i);
        }
    }

    sort(arr.begin(), arr.end(), [](int i, int j) {
        return a[i] < a[j];
    });

    // tr(arr, mi);
    map<int, int> present;
    
    present[mi] = n;
    present[-mi] = 1;
    for (int i : arr) {
        present[a[i] - b[i]] = i;
    }

    for (int i = 2; i <= n - 1; i++) {
        if (!present.count(a[i] - b[i])) {
            // tr(i, a[i], b[i]);
            cout << "NIE\n";
            return 0;
        }
    }
    
    int curr = 0;
    int prev = 1;
    for (int i = 1; i < (int)arr.size(); i++) {
        if (a[arr[i]] == a[arr[i - 1]]) {
            cout << "NIE\n";
            return 0;
        }
    }
    // tr(arr);
    cout << "TAK\n";
    for (int i : arr) {
        cout << prev << " " << i << " " << a[i] - curr << endl;
        curr = a[i];
        visited[i] = 1;
        prev = i;
        dist[i] = a[i];
    }
    cout << prev << " " << n << " " << b[prev] << endl;
    dist[n] = mi;
    for (int i = 2; i <= n - 1; i++) {
        if (visited[i]) continue;
        int x = a[i] - b[i];
        cout << i << " " << present[x] << " " << a[i] - dist[present[x]] << endl;
    }
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
