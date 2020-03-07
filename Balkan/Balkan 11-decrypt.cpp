// we can see here that R[0] can be found if (M[a ^ R[1]] == M[b ^ R[1] ^ R[0]]) or (M[c ^ R[2]] == M[d ^ R[2] ^ R[0]])
// for some a, b, c, d that we query. So we can use this idea and keep querying until we get all Rs. As far as I saw it takes around 140~ queries
// to get all of Rs now after this everything becomes determistic. just query for the unknown values of M 

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

// #include "decrypt.h"

int query(int x);
void solution(int R[], int M[]);
vector<int> perm;
vector<int> testR;
vector<int> order = {1, 2, 4, 3, 6, 7, 5};
int ind = 0;
// int query(int x) {
//     int lol = x;
//     for (int i = 0; i < 3; i++) {
//         if (order[ind] & (1 << i)) {
//             lol ^= testR[i];
//         }
//     }
//     return perm[lol];
// }

// void solution(int R[], int M[]) {

// }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r)
{
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

const int L = 256;
vector<vector<pii>> inv(L);
int R[3];
int M[L];

void trySolve(int y) {
    for (int i = 0; i < (int)inv[y].size(); i++) {
        for (int j = 0; j < (int)inv[y].size(); j++) {
            if (inv[y][i].se == 1) {
                if (inv[y][j].se == 3) {
                    R[1] = inv[y][i].fi ^ inv[y][j].fi;
                }
                if (inv[y][j].se == 5) {
                    R[2] = inv[y][i].fi ^ inv[y][j].fi;
                }
            }
            if (inv[y][i].se == 2) {
                if (inv[y][j].se == 3) {
                    R[0] = inv[y][i].fi ^ inv[y][j].fi;
                }
                if (inv[y][j].se == 6) {
                    R[2] = inv[y][i].fi ^ inv[y][j].fi;
                }
            }
            if (inv[y][i].se == 4) {
                if (inv[y][j].se == 5) {
                    R[0] = inv[y][i].fi ^ inv[y][j].fi;
                }
                if (inv[y][j].se == 6) {
                    R[1] = inv[y][i].fi ^ inv[y][j].fi;
                }
            }
        }
    }
}

void decrypt() {
    // for (int i = 0; i < L; i++) {
    //     perm.push_back(i);
    // }
    // for (int i = 0; i < 3; i++) {
    //     int x = rand(0, L - 1);
    //     testR.push_back(x);
    // }
    // shuffle(all(perm), rng);
    MEMS(R, -1);
    MEMS(M, -1);
    int rem = 320;
    for (int i_ = 0; i_ < 320; i_++) {
        int x = rand(0, L - 1);
        int y = query(x);
        inv[y].push_back({x, order[ind]});
        ind++;
        ind %= 7;
        trySolve(y);
        int done = 0;
        for (int i = 0; i < 3; i++) {
            if (R[i] == -1) {
                done = 1;
            }
        }
        if (done == 0) {
            rem -= (i_ + 1);
            break;
        }
    }
    for (int i = 0; i < 3; i++) {
        assert(R[i] != -1);
    }

    for (int i = 0; i < L; i++) {
        for (auto j : inv[i]) {
            int curr = j.fi;
            for (int k = 0; k < 3; k++) {
                if (j.se & (1 << k)) {
                    curr ^= R[k];
                }
            }
            // tr(curr, i);
            M[curr] = i;
        }
    }

    for (int i = 0; i < L; i++) {
        if (M[i] == -1) {
            int val = 0;
            for (int j = 0; j < 3; j++) {
                if (order[ind] & (1 << j)) {
                    val ^= R[j];
                }
            }
            int k = i ^ val;
            M[i] = query(k);
            ind++;
            ind %= 7;
        }
    }
    for (int i = 0; i < L; i++) {
        assert(M[i] != -1);
    }
    solution(R, M);
}


int main() {
    decrypt();
}