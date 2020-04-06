/*
    Our dp states dp[i][j][k] = number of permutations of length i starting with j and k denoting the direction.
    the dp transistion can be found here https://github.com/mostafa-saad/MyCompetitiveProgramming/tree/master/Olympiad/CEOI/official/2002
    the main idea here is to understand the bijection in the counting. the editorial explains well.

    now build the answer from the start which is pretty straight forward.
*/

// g++ -std=c++14

/*

Today might be the chance to grasp the chance to let your talent bloom.
May be tomorrow, the day after, or next year...
May be even when you are 30. I'm not sure if physique has anything to do with it
but if you think that it will never come, it probably never will.

- Tooru Oikawa.

*/

#include<iostream>
#include<vector>

typedef long long ll;
typedef long double lld;

using namespace std;

const int N = 22;

ll dp[N][N][2];

ll f(int tot, int start, int up) {
    if (tot == 1) {
        if (start == 1) {
            return 1;
        } else {
            return 0;
        }
    }
    if (start == 1) {
        if (up == 0) return 0;
    }
    ll &ans = dp[tot][start][up];
    if (ans != -1) return ans;
    ans = 0;
    if (up == 0) {
        ans = f(tot, start - 1, up) + f(tot - 1, start - 1, !up);
    } else {
        ans = f(tot, tot - start + 1, !up);
    }
    return ans;
}

int solve() {
    int n;
    ll c;
    cin >> n >> c;

    vector<int> visited(n + 1);
    vector<int> ans;
    vector<int> curr_val(n + 1);
    ll curr = 0;
    int no = -1, dir = -1;
    for (int i = 1; i <= n; i++) {
        curr_val[i] = i;
    }
    for (int i = 0; i < n; i++) {
        int done = 0;
        // tr(i, curr, no, dir);
        for (int j = 1; j <= n; j++) {
            if (visited[j] == 1) continue;
            // tr(i, j, dir, no, curr);
            if (i == 0) {
                for (int d = 0; d < 2; d++) {
                    if ((f(n, j, d) + curr) >= c) {
                        done = 1;
                        no = j;
                        dir = d;
                        break;
                    } else {
                        curr += f(n, j, d);
                    }
                }
            } else {
                if (dir == 1 && ans.back() < j) continue;
                if (dir == 0 && ans.back() > j) continue;
                if ((f(n - i, curr_val[j], dir) + curr) >= c) {
                    done = 1;
                    no = j;
                } else {
                    curr += f(n - i, curr_val[j], dir);
                }
            }
            if (done == 1) {
                visited[no] = 1;
                ans.push_back(no);
                dir ^= 1;
                for (int k = no + 1; k <= n; k++) {
                    curr_val[k] -= 1;
                }
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}

int main(){ 
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
        for (int k = 0; k < 2; k++) dp[i][j][k] = -1;
    }
    int t;
    cin >> t;
    // t = 1;
    while (t--) solve();
}
