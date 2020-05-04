/*
problem description : 
 given an array A of N integers. Find how many pairs of indices (i ,j) such that i <= j and the number 
 of different bits in A[i] and A[j] binary representations is exactly equal to 4. (1 <= N <= 10^5 ,0 <= A[i] < 2^20)
sample case :
 N = 4 ,A = {15 ,0 ,10 ,5}
 pairs that differ by exactly 4 bits are (1 ,2) and (3 ,4) ,so answer = 2.
a naive solution would be for each element flip every possible 4 bits and check if there exists an element
with that value this solution works in N*(20C4) which is not fast enough to pass.
lets create a dp[d][m] that stores the number of elements from the array that we can modify their value by flipping exactly d bits to be equal to m.
instead of flipping 4 bits for each element we can divide a number c into 2 halves a = (n>>10) and b = n&((1<<10)-1) so that c = (a*2^10)+b 
now flip at most 4 bits in a and increase dp[d][m_a*2^10+b] by 1 where m_a is the modified a and d is # of diff bits between a and m_a
then for the second half flip at most 4 bits and add to the answer dp[4-d][a*2^10+m_b] where m_b is modified b and d is # of diff bits between b and m_b
this will be equivalent to flipping all 4 bits for each element.
time complexity : O(N*2^10)
because of tight tl we will have to do loop unrolling manually or by using pragma.
since the 2 inner loops are really simple they can be unrolled and would save processing time.
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
#define pb(x) push_back(x)
#define mp(x,y) make_pair(x,y)
#define MEMS(a,b) memset(a,b,sizeof(a))
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define __ freopen("aiacubiti.in","r",stdin);freopen("aiacubiti.out","w",stdout);
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


const int N = (1 << 20) + 10;

int n, arr[N];
int dp[5][N];

int popcount[N];

int solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < 1024; i++) {
        popcount[i] = __builtin_popcount(i);
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int up = ((arr[i] >> 10) << 10), low = (arr[i] & (1023));
        for (int j = 0; j < 1024; j++) {
            int d = popcount[low ^ j];
            if (d <= 4) {
                ans += dp[4 - d][up | j];
            }
        }
        for (int j = 0; j < 1024; j++) {
            int d = popcount[(up >> 10) ^ j];
            if (d <= 4) {
                dp[d][j << 10 | low]++;
            }
        }
    }
    cout << ans << endl;
    return 0;

}

int32_t main(){ _
__
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
