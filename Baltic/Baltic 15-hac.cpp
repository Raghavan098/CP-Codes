
// the hacker will get ceil(n/2) systems and the operator will get n/2 systems. both of these will 
// form a contineous sequence in a circular way.

// The one and only observation that is required in this problem is that if the hacker chooses 
// a system to hack then the operator has complete control over the interval that he will get 
// (ofcourse the interval should not contain the system choosen by the hacker). Once this observation
// is made everything else is straight forward.

// let's prove that the operator has complete control: 
// assume that n is even (odd case is also same)
// suppose hacker chooses some x system and the operator sees that he needs the interval that 
// starts at distance d from x to the left. Now the operator will choose the system that is 
// at distance 2 * d from x to the left. If the hacker now chooses the left of his interval then 
// operator will choose right, and vice versa. 



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

const int N = 1e6 + 199;
int n;
int arr[N], cumu[N];
int tot;
int ans = 0;
int solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[n + i] = arr[i];
        tot += arr[i];
    }
    for (int i = 1; i <= 2 * n; i++) {
        cumu[i] = cumu[i - 1] + arr[i];
    }
    deque<pii> d;
    int prev;
    for (int i = 1; i <= n - (n / 2) + 1; i++) {
        int x = cumu[i + n/2 - 1] - cumu[i - 1];
        while (!d.empty() && d.back().fi < x) d.pop_back();
        d.push_back({x, i});
        prev = i;
    }

    for (int i = 1; i <= n; i++) {
        if (!d.empty() && d.front().se == i) d.pop_front();
        int k = d.front().fi;
        // tr(i, k);
        ans = max(ans, tot - k);
        prev++;
        int x = cumu[prev + n/2 - 1] - cumu[prev - 1];
        while (!d.empty() && d.back().fi < x) d.pop_back();
        d.push_back({x, prev});
    }
    cout << ans << endl;
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
