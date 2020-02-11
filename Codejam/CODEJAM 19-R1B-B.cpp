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

#define sd(x) scanf("%d",&x)
#define sd2(x,y) scanf("%d%d",&x,&y)
#define sd3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define endl "\n"
#define f first
#define s second
#define pb(x) push_back(x)
#define mp(x,y) make_pair(x,y)
#define LET(x, a)  __typeof(a) x(a)
#define foreach(it, v) for(LET(it, v.begin()); it != v.end(); it++)
#define MEMS(a,b) memset(a,b,sizeof(a))
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define __ freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define all(c) c.begin(),c.end()
#define inf 1000000000000000001

#define tr(...) cout<<__FUNCTION__<<' '<<__LINE__<<" = ";trace(#__VA_ARGS__, __VA_ARGS__)

template<typename S, typename T>
ostream& operator<<(ostream& out,pair<S,T> const& p){out<<'('<<p.fi<<", "<<p.se<<')';return out;}

template<typename T>
ostream& operator<<(ostream& out,vector<T> const& v){
ll l=v.size();for(ll i=0;i<l-1;i++)out<<v[i]<<' ';if(l>0)out<<v[l-1];return out;}

template<typename T>
void trace(const char* name, T&& arg1){cout<<name<<" : "<<arg1<<endl;}

template<typename T, typename... Args>
void trace(const char* names, T&& arg1, Args&&... args){
const char* comma = strchr(names + 1, ',');cout.write(names, comma-names)<<" : "<<arg1<<" | ";trace(comma+1,args...);}

#define int ll
#define For(i, b) for(int i = 1; i <= b; i++)
#define pll pair<int, int>


int read(int a){
    int ans = 0;
    int temp = 1;
    for(int i = 0; i < 7; i++){
        ans += ((a >> i) & 1LL) * temp;
        temp *= 2;
    }
    return ans;
}

void solve(){
    int arr[7], num;
    cout << 212 << endl;
    fflush(stdout);
    cin >> num;
    arr[4] = (num >> 53);
    arr[5] = (num >> 42);
    arr[6] = (num >> 35);
    cout << 56 << endl;
    fflush(stdout);
    cin >> num;
    num -= (arr[4] << 14);
    arr[1] = (num >> 56LL);
    arr[2] = (num >> 28LL);
    arr[3] = (num >> 18LL);
    arr[1] = read(arr[1]);
    arr[2] = read(arr[2]);
    arr[3] = read(arr[3]);
    arr[4] = read(arr[4]);
    arr[5] = read(arr[5]);
    arr[6] = read(arr[6]);
    For(i, 6){
        cout << arr[i] << " ";
    }cout << endl;
    fflush(stdout);
    cin >> num;
}

int32_t main(){
    int test, w;
    cin >> test >> w;
    for(int i = 0; i < test; i++){
        solve();
    }
    return 0;
}