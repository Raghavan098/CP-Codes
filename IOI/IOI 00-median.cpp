// g++ -std=c++14

/*

Today might be the chance to grasp the chance to let your talent bloom.
May be tomorrow, the day after, or next year...
May be even when you are 30. I'm not sure if physique has anything to do with it
but if you think that it will never come, it probably never will.

- Tooru Oikawa.

*/


#include<bits/stdc++.h>
#include "device.h"

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r)
{
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

int Med3(int x, int y, int z);

int get(vector<int> L, vector<int> R, vector<int> M, int a, int b, int n) {
    if ((int)L.size() == n/2) return a;
    if ((int)R.size() == n/2) return b;
    if ((int)R.size() > (int)L.size()) {
        swap(L, R);
        swap(a, b);
    }
    vector<int> X, Y;
    if ((int)L.size() > n/2) {
        
        int b2 = L[rand(0, (int)L.size() - 1)];
        for (int j = 0; j < (int)L.size(); j++) {
            int i = L[j];
            if (i == b2) continue;
            int x = Med3(a, b2, i);
            if (x == b2) {
                X.push_back(i);
            } else {
                Y.push_back(i);
            }
        }
        L.clear();
        for (int j = 0; j < (int)M.size(); j++) L.push_back(M[j]);
        L.push_back(b);
        for (int j = 0; j < (int)R.size(); j++) L.push_back(R[j]);
        R = L;
        b = a;
        a = b2;
        M = Y;
        L = X;
        return get(L, R, M, a, b, n);
    } else {
        R.push_back(b);
        int b2 = M[rand(0, (int)M.size() - 1)];
        for (int j = 0; j < (int)M.size(); j++) {
            int i = M[j];
            if (i == b2) continue;
            int x = Med3(a, b2, i);
            if (x == b2) Y.push_back(i);
            else X.push_back(i);
        }
        if ((int)Y.size() + (int)R.size() > n/2) {
            M = Y;
            L.push_back(a);
            for (auto i : X) L.push_back(i);
            a = b2;
            R.pop_back();
            return get(L, R, M, a, b, n);
        } else {
            M = X;
            for (auto i : Y) R.push_back(i);
            b = b2;
            return get(L, R, M, a, b, n);
        }
    }   
}

int Median(int n) {
    int a, b; 
    do {
        a = rand(1, n);
        b = rand(1, n);
    } while (a == b);
    vector<int> L, R, M;
    for (int i = 1; i <= n; i++) {
        if (i != a && i != b) {
            int x = Med3(a, b, i);
            if (x == a) L.push_back(i);
            else if (x == b) R.push_back(i);
            else M.push_back(i);
        }
    }
    return get(L, R, M, a, b, n);
}
