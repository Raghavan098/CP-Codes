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

template<typename T>
void trace(const char* name, T&& arg1){cout<<name<<" : "<<arg1<<endl;}

template<typename T, typename... Args>
void trace(const char* names, T&& arg1, Args&&... args){
const char* comma = strchr(names + 1, ',');cout.write(names, comma-names)<<" : "<<arg1<<" | ";trace(comma+1,args...);}

#define int ll

const int N = 1e5 + 100;
int n, arr[N], p;
int ans[N];
int ind = 1;
int times;
queue<int> q;
set<pii> inp;
set<int> qs, waiting;
void adv(int t) {
    while (!inp.empty() && (*inp.begin()).fi <= t) {
        auto p = *inp.begin();
        inp.erase(inp.begin());
        // tr(p, t, qs, waiting);
        if ((qs.empty() || p.se < *qs.begin()) && (waiting.empty() || p.se < *waiting.begin())) {
            q.push(p.se);
            qs.insert(p.se);
        } else {
            waiting.insert(p.se);
        }
    }
}

int32_t main(){ 
    cin >> n >> p;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        inp.insert({arr[i], i});
    }

    while (ind <= n) {
        // tr(times, waiting);
        adv(times);
        if (!q.empty()) {
            int f = q.front();
            q.pop();
            ans[f] = times + p;
            ind++;
            times = times + p;
            adv(times - 1);
            qs.erase(f);
            adv(times);
            while (!waiting.empty()) {
                auto curr = *waiting.begin();
                
                if (qs.empty() || curr < *qs.begin()) {
                    q.push(curr);
                    qs.insert(curr);
                    waiting.erase(curr);
                } else {
                    break;
                }
            }
        } else {
            times = (*inp.begin()).fi;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " " ;
    }
    cout << endl;
}
