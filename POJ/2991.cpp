// g++ -std=c++14

/*

Today might be the chance to grasp the chance to let your talent bloom.
May be tomorrow, the day after, or next year...
May be even when you are 30. I'm not sure if physique has anything to do with it
but if you think that it will never come, it probably never will.

- Tooru Oikawa.

*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream> 
#include <iomanip> 

typedef long long ll;
typedef double lld;
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
#define inf 1000000000000000001
#define pii pair<int, int>
const int N = 110000;
#define X first
#define Y second
#define pt pair<lld, lld>
pt t[4 * N];
lld ang[4 * N];
int lazy[4 * N];
int arr[N];
int n, c;
lld curr[N];
const lld PI = acos(-1.00);

lld get_rad(lld deg) {
    return ((deg * PI) / 180.0);
}

pt combine(pt a, pt b) {
    pt ans = mp(a.X + b.X, a.Y + b.Y);
    return ans;
}

void build(int v, int l, int r){
    ang[v] = 0;
    if(l == r){
        t[v].X = 0;
        t[v].Y = (arr[l]);
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m + 1, r);
    t[v] = combine(t[2 * v], t[2 * v + 1]);
    return;
}

void update_coor(int v, lld angg) {
    pt curr = t[v];
    t[v].X = curr.X * cos(angg) - curr.Y * sin(angg);
    t[v].Y = curr.X * sin(angg) + curr.Y * cos(angg);
}

void push(int v) {
    ang[v * 2] += ang[v];
    ang[v * 2 + 1] += ang[v];
    update_coor(2 * v, ang[v]);
    update_coor(2 * v + 1, ang[v]);
    ang[v] = 0;
}

void update(int v, int tl, int tr, int l, int r, lld addend) {
    if (l > r)
        return;
    if (l == tl && tr == r) {
        ang[v] += addend;
        update_coor(v, addend);
    }
    else {
        push(v);
        int tm = (tl + tr) / 2;
        update(v * 2, tl, tm, l, min(r, tm), addend);
        update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);
        t[v] = combine(t[v * 2], t[v * 2 + 1]);
    }
}

pt query(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return mp(0.0, 0.0);
    if (l <= tl && tr <= r)
        return t[v];
    push(v);
    int tm = (tl + tr) / 2;
    return combine(query(v * 2, tl, tm, l, min(r, tm)), query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
};


int main() { 
    int t = 0;
    while (scanf("%d %d", &n, &c) != EOF) {
        if (t != 0) {
            printf("\n");
        }
        t++;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &arr[i]);
        }
        build(1, 1, n);
        for (int i = 1; i <= n; i++) {
            curr[i] = PI;
        }
        for (int q_ = 0; q_ < c; q_++) {
            int ind, rot;
            scanf("%d %d", &ind, &rot);
            lld rotr = get_rad(rot);
            lld delta = rotr - curr[ind];
            curr[ind] = rotr;
            update(1, 1, n, ind + 1, n, delta);
            pt ans_curr = query(1, 1, n, 1, n);
            printf("%.2lf %.2lf\n", ans_curr.X, ans_curr.Y);
        }
    }
    
}
