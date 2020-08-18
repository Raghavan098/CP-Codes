/*

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


const int N = 310;

int mx[] = {1, -1, 0, 0};
int my[] = {0, 0, 1, -1};

int n;
vector<string> arr;
pii starta, startb;

pii distA[N][N];
pii distB[N][N];

vector<vector<pii>> indA(N * N + 1), indB(N * N + 1);

int dp[2][N][N];

bool valid(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < n && arr[x][y] != '#');
}

int solve() {
    arr.clear();
    indA.clear();
    indB.clear();
    cin >> n;
    indA.resize(n * n + 2);
    indB.resize(n * n + 2);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        arr.push_back(s);
        for (int j = 0; j < n; j++) {
            if (s[j] == 'A') {
                starta = {i, j};
            }
            if (s[j] == 'B') {
                startb = {i, j};
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            distA[i][j] = {-1, -1};
            distB[i][j] = {-1, -1};
        }
    }

    queue<pii> q;


    indA[0].push_back(starta);
    distA[starta.fi][starta.se] = {0, 0};
    q.push(starta);

    while (!q.empty()) {

        pii f = q.front();
        q.pop();

        int currd = distA[f.fi][f.se].fi;

        for (int i = 0; i < 4; i++) {
            int x = f.fi + mx[i];
            int y = f.se + my[i];
            if (valid(x, y) && (distA[x][y] == make_pair(-1, -1))) {
                distA[x][y].fi = currd + 1;
                distA[x][y].se = indA[currd + 1].size();
                indA[currd + 1].push_back({x, y});
                q.push({x, y});
            } 
        }
    }


    indB[0].push_back(startb);
    distB[startb.fi][startb.se] = {0, 0};
    q.push(startb);

    while (!q.empty()) {

        pii f = q.front();
        q.pop();

        int currd = distB[f.fi][f.se].fi;

        for (int i = 0; i < 4; i++) {
            int x = f.fi + mx[i];
            int y = f.se + my[i];
            if (valid(x, y) && (distB[x][y] == make_pair(-1, -1))) {
                distB[x][y].fi = currd + 1;
                distB[x][y].se = indB[currd + 1].size();
                indB[currd + 1].push_back({x, y});
                q.push({x, y});
            } 
        }
    }

    int tot_dist = distA[startb.fi][startb.se].first;
    // tr(tot_dist);
    if (tot_dist % 2 == 1) {
        cout << 'A' << endl;
        return 0;
    }

    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                dp[i][j][k] = -1;
            }
        }
    }

    for (int k = tot_dist / 2; k >= 0; k--) {
        int p = k % 2;
        int q = !p;
        for (int i = 0; i < (int)indA[k].size(); i++) {
            for (int j = 0; j < (int)indB[k].size(); j++) {
                if (k == tot_dist / 2) {
                    if (indA[k][i] == indB[k][j]) {
                        dp[p][i][j] = 0;
                    } else {
                        dp[p][i][j] = 1;
                    }
                } else {
                    for (int x = 0; x < 4; x++) {
                        int nx = indA[k][i].fi + mx[x];
                        int ny = indA[k][i].se + my[x];
                        int done = 1;
                        if (valid(nx, ny) && (distA[nx][ny].fi == (k + 1)) && (distB[nx][ny].fi == (tot_dist - k - 1))) {
                            done = 0;
                            int nxtdista = distA[nx][ny].se;
                            for (int y = 0; y < 4; y++) {
                                int nnx = indB[k][j].fi + mx[y];
                                int nny = indB[k][j].se + my[y];

                                if (valid(nnx, nny) && (distB[nnx][nny].fi == (k + 1)) && (distA[nnx][nny].fi == (tot_dist - k - 1))) {
                                    int nxtdistb = distB[nnx][nny].se;
                                    if (dp[q][nxtdista][nxtdistb] == 0) {
                                        done = 1;
                                        break;
                                    }
                                }
                            }
                        }
                        if (valid(nx, ny) && done == 0) {
                            dp[p][i][j] = 1;
                            break;
                        } else {
                            dp[p][i][j] = 0;
                        }
                    }
                }
            }
        }
        if (k == 0) {
            if (dp[p][0][0] == 1) {
                cout << "A" << endl;
            } else {
                cout << "B" << endl;
            }
        }
    }

    return 0;




}

int32_t main(){ _
    int t;
    cin >> t;
    // t = 1;
    while (t--) solve();
    return EXIT_SUCCESS;	
}
