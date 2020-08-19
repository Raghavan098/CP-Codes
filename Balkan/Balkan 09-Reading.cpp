/*
    very simple dp -> current score and previous letter. But since the current score is huge ~= 1e9 and the dp transisition is all linear we can apply matrix expoenetiation to this.
    
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

const int sz = 156;
const int L = 26;
const int MOD = 1e9 + 7;

int n, m;
int adj[L][L];

int add(int a, int b)
{
	int res = a + b;
	if(res >= MOD)
		return res - MOD;
	return res;
}

int mul(int a, int b)
{
	long long res = a;
	res *= b;
	if(res >= MOD)
		return res % MOD;
	return res;
}


struct matrix
{
    int SZ;
    vector<vector<int>> arr;
    matrix(int s){
        SZ = s;
        arr.resize(s, vector<int>(s));
    }
	void reset()
	{
		for(int i = 0; i < SZ; i++){
            for(int j = 0; j < SZ; j++){
                arr[i][j] = 0;
            }
        }
	}

	void makeiden()
	{
		reset();
		for(int i=0;i<SZ;i++)
		{
			arr[i][i] = 1;
		}
	}

	matrix operator + (const matrix &o) const
	{
		matrix res(o.SZ);
		for(int i=0;i<SZ;i++)
		{
			for(int j=0;j<SZ;j++)
			{
				res.arr[i][j] = add(arr[i][j], o.arr[i][j]);
			}
		}
		return res;
	}

	matrix operator * (const matrix &o) const
	{
		matrix res(o.SZ);
		for(int i=0;i<SZ;i++)
		{
			for(int j=0;j<SZ;j++)
			{
				res.arr[i][j] = 0;
				for(int k=0;k<SZ;k++)
				{
					res.arr[i][j] = add(res.arr[i][j] , mul(arr[i][k] , o.arr[k][j]));
				}
			}
		}
		return res;
	}

	void print(){
		for(int i = 0; i < SZ; i++){
			for(int j = 0; j < SZ; j++){
				cout << arr[i][j] << " ";
			}cout << endl;
		}
	}
};

matrix power(matrix a, int b)
{
	matrix res = a;
    b--;
	while(b)
	{
		if(b & 1)
		{
			res = res * a;
		}
		a = a * a;
		b >>= 1;
	}
	return res;
}

vector<int> multiply_vector(matrix &a, vector<int> &b){
    int SZ = a.SZ;
    vector<int> ans(a.SZ);
    for(int i = 0; i < SZ; i++){
        int curr = 0;
        for(int j = 0; j < SZ; j++){
            curr = (curr + (b[j] * a.arr[i][j]) % MOD) % MOD;
        }
        ans[i] = curr;
    }
    return ans;
}

vector<int> multiply_vector(vector<int> &b, matrix &a){
    int SZ = a.SZ;
    vector<int> ans(a.SZ);
    for(int i = 0; i < SZ; i++){
        int curr = 0;
        for(int j = 0; j < SZ; j++){
            curr = add(curr, mul(a.arr[j][i], b[j]));
        }
        ans[i] = curr;
    }
    return ans;
}

int solve() {
    cin >> n >> m;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            adj[i][j] = 1;
        }
    }
    for (int i = 0; i < m; i++) {
        char a, b;
        int f;
        cin >> a >> b >> f;
        adj[int(a - 'a')][int(b - 'a')] = f;
        adj[int(b - 'a')][int(a - 'a')] = f;
    }

    matrix m(sz);
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            m.arr[i][(adj[i][j] - 1) * L + j] += 1;
        }
    }

    for (int i = 1; i < 5; i++) {
        for (int j = 0; j < L; j++) {
            m.arr[i * L + j][(i - 1) * L + j] += 1;
        }
    }

    for (int i = 0; i < L; i++) {
        m.arr[5 * L][i] += 1;
    }
    m.arr[5 * L][5 * L] += 1;

    vector<int> curr(sz);
    for (int i = 0; i < L; i++) {
        curr[i] = 1;
    }

    auto res = power(m, n);

    // tr(res.arr == m.arr);
    
    auto vec = multiply_vector(res, curr);

    // tr(vec);

    int ans = 0;
    for (int i = 0; i < L; i++) {
        ans += vec[i];
        ans %= MOD;
    }
    ans += vec[5 * L];
    ans %= MOD;
    cout << ans << endl;

    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
    return EXIT_SUCCESS;	
}
