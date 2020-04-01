/* 

    A very complicated problem with a very simple solution.
    first observation is that the connections for a binary tree with log(n) height.
    now when it is observered properly we can find that there are 3 cases that we should deal with:

    Case 1:
    if (arr[i] < arr[2 * i] && arr[i] < arr[2 * i + 1])

    then just keep the arr[i] in the same place and proceed to the next operation.

    Case 2:

    if (arr[2 * i] < arr[i] && arr[2 * i] < arr[2 * i + 1])

    now the only way is to swap arr[i] with arr[2 * i] and continue

    Case 3 :

    if (arr[2 * i + 1] < arr[i] && arr[2 * i + 1] < arr[2 * i])

    this is the case with problem
    we can either swap arr[i] and arr[2 * i] or not we have to take decision 
    the obvious solution to this problem is to use dp trying both the cases:

    how to try both the cases:

    take the minimum of arr[i] and arr[2 * i] let it be c. now try c in both the subtrees
    and check where is the position that it ends up being. now take the decision based on this position
    
    it makes sense to put c where the minimum position comes because we wont be affecting anything else and just 
    c will be in a better position this way

    There is one more problem with this approach. i.e, the dp seems to make the solution O(n^2)
    But on observered properly on a particular node only log(n) values can appear.

    so just use map for storing the dp value. 

    Finally the total complexity becomes O(nlog^2(n)) additional log(n) for using maps.


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

// #define int ll

const int N = 2e5 + 10;
const int inf = 1e9 + 1;
int n, arr[N];

map<pii, int> dp;

int f(int ind, int val) {
    if (dp.count({ind, val})) return dp[{ind, val}];
    int &ans = dp[{ind, val}];
    if (2 * ind > n) {
        return ans = ind;
    }
    if ((2 * ind + 1) > n) {
        if (arr[2 * ind] > val) return ans = ind;
        return ans = (2 * ind);
    }
    // case 1:
    if (val < arr[2 * ind] && val < arr[2 * ind + 1]) {
        return ans = ind;
    }
    // case 2:
    else if (arr[2 * ind] < min(val, arr[2 * ind + 1])) {
        return ans = f(2 * ind, val);
    }
    // case 3:
    else {
        int a = min(val, arr[2 * ind]);
        int b = max(val, arr[2 * ind]);
        int c = arr[2 * ind + 1];
        int t1 = f(2 * ind, a), t2 = f(2 * ind + 1, a);
        if (t1 < t2) {
            if (a == val) return ans = t1;
            return ans = f(2 * ind + 1, val);
        } else {
            if (a == val) return ans = t2;
            return ans = f(2 * ind, val);
        }
    }
}

int solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    arr[n + 1] = inf;
    for (int i = 1; i <= n; i++) {
        if (i * 2 <= n) {
            // case 1:
            if (arr[i] < arr[2 * i] && arr[i] < arr[2 * i + 1]) continue;
            // case 2: 
            else if (arr[2 * i] < min(arr[i], arr[2 * i + 1])) {
                swap(arr[i], arr[2 * i]);
            }  
            // case 3:
            else {
                int a = min(arr[i], arr[2 * i]);
                int b = max(arr[i], arr[2 * i]);
                int c = arr[2 * i + 1];
                arr[i] = c;
                int t1 = f(2 * i, a), t2 = f(2 * i + 1, a);
                if (t1 < t2) {
                    arr[2 * i] = a;
                    arr[2 * i + 1] = b;
                } else {
                    arr[2 * i] = b;
                    arr[2 * i + 1] = a;
                }
            }
        } 
    }
    for (int i = 1; i <= n; i++) {
        cout << arr[i] << " ";
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
