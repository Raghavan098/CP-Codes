/*

    * There has to be n^2 number of quries.
    * Now for every query find the largest subrectange that this cell contains and then find the prefix sum for this cell.
    
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
#include "treasure.h"
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

const int N = 102;
int ask(int i, int j, int q, int p) {
    return countTreasure(i, j, q, p);
    // cout << i << " " << j << " " << q << " " << p << endl;
    // fflush(stdout);
    // int x; cin >> x;
    // return x;
}

int sum[N][N];



void findTreasure(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i <= ((n + 1) / 2) && j <= ((n + 1) / 2)) {
                sum[i][j] = ask(i, j, n, n);
            } else if (i <= ((n + 1) / 2)) {
                sum[i][j] = sum[i][1] - ask(i, 1, n, j - 1);
            } else if (j <= ((n + 1) / 2)) {
                sum[i][j] = sum[1][j] - ask(1, j, i - 1, n);
            } else {
                sum[i][j] = ask(1, 1, i - 1, j - 1) + sum[1][j] + sum[i][1] - sum[1][1];
            }
            // cout << sum[i][j] << endl;
        }
        // cout << endl;
    }
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         cout << sum[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    vector<string> ans;
    for (int i = 1; i <= n; i++) {
        string temp;
        for (int j = 1; j <= n; j++) {
            if ((sum[i][j] - sum[i + 1][j] - sum[i][j + 1] + sum[i + 1][j + 1]) == 1) {
                Report(i, j);
            } 
        }
        ans.push_back(temp);
    }
    // cout << "END\n";
    // for (int i = 0; i < n; i++) {
    //     cout << ans[i] << endl;
    // }
}