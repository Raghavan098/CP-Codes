/*
    https://csacademy.com/contest/ioi-2016-training-round-2/task/increasing_subarrays/solution/
    basic idea is to maintain two pointers using the deque and construct answer from the back.
    in my solution ans[i] contains the length of maximum subarray that can be constructed from i
    we somehow maintain blocks (using the deque) of the increasing indices from i and main the cost of the blocks simultaniously
    now ans[i] is lenght of all the blocks in the deque + the max length in the final block (ie block after the end of deque) which can be binary searched 
    
*/

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

#define int ll

const int N = 1e6 + 10;

int n, arr[N];
int m;
int rp[N];

int cumu[N], ans[N];
int cost[N];

void gen() {
    n = rand(1, 100);
    m = rand(1, 100);
    for (int i = 1; i <= n; i++) {
        arr[i] = rand(1, 100);
    }
}

int solve() {
    // gen();
    // cout << n << " " << m << endl;
    // for (int i = 1; i <= n; i++) {
    //     cout << arr[i] << " ";
    // }
    // cout << endl;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i <= n; i++) {
        cumu[i] += arr[i];
        cumu[i] += cumu[i - 1];
    }
    stack<int> s;
    arr[n + 1] = 1e9 + 1e15 + 10;
    s.push(n + 1);
    for (int i = n; i >= 1; i--) {
        while (!s.empty() && arr[s.top()] <= arr[i]) s.pop();
        rp[i] = s.top();
        s.push(i);
        cost[i] = arr[i] * (rp[i] - i) - (cumu[rp[i] - 1] - cumu[i - 1]);
    }
    int tot = 0;
    deque<int> d;
    int curr_cost = 0;
    for (int i = n; i >= 1; i--) {
        while (!d.empty() && d.front() < rp[i]) {
            curr_cost -= cost[d.front()];
            d.pop_front();
        }
        d.push_front(i);
        curr_cost += cost[i];
        while (!d.empty() && curr_cost > m) {
            curr_cost -= cost[d.back()];
            d.pop_back();
        }
        int l;
        if (d.empty()) l = i;
        else l = rp[d.back()];
        int x = l;
        int r = rp[l] - 1;
        int mid, aa = -1;
        while (l <= r) {
            mid = (l + r) / 2;
            int cc = arr[x] * (mid - x + 1) - (cumu[mid] - cumu[x - 1]);
            if (curr_cost + cc <= m) {
                aa = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (aa != -1) {
            ans[i] = aa - i + 1;
        } else {
            if (d.empty()) ans[i] = 1;
            else ans[i] = rp[d.back()] - i;
        }
        tot += ans[i];
    }
    cout << tot << endl;
    return 0;
}

int32_t main(){ 
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
