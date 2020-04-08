/*
    Imagine a rectangle something like this 
            3
       _____________
      |             |
    0 |             | 2
      |_____________|   
            1
    

    now to go from the corner 1 to corner 2
    then the connections from (1 to 0), (1 to 3) and (1, 2) should not be blocked.

    how to check if a particular path is blocked?

    add an edge between two circles if the distance between them is less than the radius of the 
    of the visitor.

    now can see the blocks and see if the visitor will reach anywhere with a bunch of conditions

    to handle multiple queries sort all the edges and then keep adding them in DSU

    once two sides of rectangle are in the same component then we know that the max radius of the visitor that can pass through this connection.

    see implementation of the details.
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

#define int ll

const long double eps = 1e-12;
const long double infl = 1e20;

template <class T>
inline int sgn(const T & x) {
	return (x > eps) - (x < -eps);
}
template <class T>
struct Point {
 	T x, y;

	Point() : x(0), y(0) {

	}

	Point(const T & x, const T & y) : x(x), y(y) {

	}

	long double length() const {
		return sqrtl(x * x + y * y);
	}

	T length2() const {
		return x * x + y * y;
	}

	long double distance(const Point & rhs) const {
		return (rhs - *this).length();
	}

 	T cross(const Point & lhs, const Point & rhs) const {
		return (lhs - *this) * (rhs - *this);
	}

	T dot(const Point & lhs, const Point & rhs) const {
		return (lhs - *this) & (rhs - *this);
	}

	long double distance_to_line(const Point & p, const Point & q) const {
		if (p == q) return distance(p);
		else return fabsl(cross(p, q) / p.distance(q));
	}

	long double distance_to_segment(const Point & p, const Point & q) const {
		if (p == q) return distance(p);
		else if (p.dot(q, *this) < 0) return distance(p);
		else if (q.dot(p, *this) < 0) return distance(q);
		else return distance_to_line(p, q);
	}

	bool on_line(const Point & p, const Point & q) const {
		return sgn(cross(p, q)) == 0;
	}

	bool on_halfline(const Point & p, const Point & q, const bool & inclusive = true) const {
		if (*this == p) return inclusive;
		else return on_line(p, q) && sgn(p.dot(q, *this)) >= 0;
	}

	bool on_segment(const Point & p, const Point & q, const bool & inclusive = true) const {
		if (*this == p || *this == q) return inclusive;
		else return on_line(p, q) && sgn(dot(p, q)) <= 0;
	}

	bool in_triangle(const Point & u, const Point & v, const Point & w, const bool & inclusive = true) const {
		Point p[3] = {u, v, w};
		if (sgn(u.cross(v, w)) < 0) reverse(p, p + 3);
		for (int i = 0; i < 3; i++) {
			if (on_segment(p[i], p[(i + 1) % 3])) return inclusive;
			else if (sgn(cross(p[i], p[(i + 1) % 3])) < 0) return false;
		}
		return true;
	}

	bool in_angle(const Point & o, const Point & p, const Point & q, const bool & inclusive = true) const {
		if (on_halfline(o, p) || on_halfline(o, q)) return inclusive;
		int vs = sgn(o.cross(p, q)), ss = sgn(o.dot(p, q));
		if (vs == 0 && ss > 0) return false;
		int vp = sgn(o.cross(p, *this)), vq = sgn(o.cross(*this, q));
		if (sgn(o.cross(p, q)) >= 0) return vp > 0 && vq > 0;
		else return vp > 0 || vq > 0;
	}

	Point operator + (const Point & rhs) const {// returns a+b(vector addition)
		return Point(x + rhs.x, y + rhs.y);
	}

	Point operator - (const Point & rhs) const {// Returns a-b(vector subtraction)
		return Point(x - rhs.x, y - rhs.y);
	}

	T operator * (const Point & rhs) const { 	// cross product
		return x * rhs.y - y * rhs.x;
	}

	T operator & (const Point & rhs) const { 	// dot product
		return x * rhs.x + y * rhs.y;
	}

	Point operator * (const T & rhs) const {	// multiplication with constant
		return Point(x * rhs, y * rhs);
	}

	Point operator / (const T & rhs) const {	// division with constant
		return Point(x / rhs, y / rhs);
	}

	bool operator == (const Point & rhs) const {// returns true if points are located at the same point.
		return x == rhs.x && y == rhs.y;
	}

	bool operator != (const Point & rhs) const {// returns true if points are not located at same point.
		return x != rhs.x || y != rhs.y;
	}

	inline int quadrant() const {				// returns quadrant defined from 0 to 7 (-1 if origin). Used in operator <
		if (x == 0 && y == 0) return -1;
		else if (x < 0 && y < 0) return 0;
		else if (x == 0 && y < 0) return 1;
		else if (x > 0 && y < 0) return 2;
		else if (x > 0 && y == 0) return 3;
		else if (x > 0 && y > 0) return 4;
		else if (x == 0 && y > 0) return 5;
		else if (x < 0 && y > 0) return 6;
		else return 7;
	}

	bool operator < (const Point & rhs) const {	//used for sorting the points in counter clockwise order.
		int lq = quadrant(), rq = rhs.quadrant();
		if (lq != rq) {
			return lq < rq;
		} else {
			int s = sgn(*this * rhs);
			return s != 0 ? s > 0 : sgn(length2() - rhs.length2()) < 0;
		}
	}
};
const int N = 2200;

struct circle {
    int x, y, r;
};
int n, m, w, h;
vector<circle> arr;

int inter (int r, int x, int y, int r2, int x2, int y2){
    if (1LL * (r + r2) * (r + r2) > 1LL * (x - x2) * (x - x2) + 1LL * (y - y2) * (y - y2))
        return 1;
    return 0;
}

int get_dist(int i, int j) {
    int l = 0, r = 1e9;
    int mid, ans = 0;
    while (l <= r) {    
        mid = (l + r) / 2;
        if (inter(arr[i].r + mid, arr[i].x, arr[i].y, arr[j].r + mid, arr[j].x, arr[j].y)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return 2 * ans;
}

int parent[N];
int size[N];

void make_set(int x) {
    parent[x] = x;
    size[x] = 1;
}

int find_set(int v) {
    if(v == parent[v]) {
        return v;
    }
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if(a != b) {
        if(size[a] < size[b]) {
            swap(a,b);
        }
        parent[b] = a;
        size[a] += size[b];
    }
}


int solve() {
    cin >> n >> m >> w >> h;
    for (int i = 0; i < n; i++) {
        int x, y, r;
        cin >> x >> y >> r;
        arr.push_back({x, y, r});
    }

    vector<pair<int, pii>> edges;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            auto dist = (int)get_dist(i, j);
            edges.push_back({dist, {i + 1, j + 1}});
        }
    }
    Point<lld> lb, rb, lt, rt;
    lb.x = 0, lb.y = 0;
    rb.x = w, rb.y = 0;
    lt.x = 0, lt.y = h;
    rt.x = w, rt.y = h;
    vector<pair<Point<lld>, Point<lld>>> corners = {{lb, lt}, {lb, rb}, {rt, rb}, {lt, rt}} ;
    for (int i = 0; i < n; i++) {
        Point<lld> p;
        p.x = arr[i].x;
        p.y = arr[i].y;
        for (int j = 0; j < 4; j++) {
            int dist = p.distance_to_line(corners[j].first, corners[j].second);
            edges.push_back({dist - arr[i].r, {i + 1, n + 1 + j}});
        }
    }

    for (int i = 1; i <= n + 4; i++) {
        make_set(i);
    }

    vector<vector<int>> mat(4, vector<int> (4, -1));

    sort(all(edges));
    // tr(edges);
    lld curr = 0.0;
    for (auto &e : edges) {
        curr = e.first;
        union_sets(e.second.first, e.second.second);
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                int x = find_set(n + i + 1);
                int y = find_set(n + j + 1);
                if (x == y && (mat[i][j] < 0)) {
                    mat[i][j] = (int)curr;
                    mat[j][i] = (int)curr;
                }
            }
        }
    }
    for (int i_ = 0; i_ < m; i_++) {
        int rad, pos;
        cin >> rad >> pos;
        rad *= 2;
        pos--;
        string ans = "";
        if (pos == 0) {
            if (rad < min({mat[0][3], mat[0][2], mat[0][1]})) {
                ans += '4';
            }
            if (rad < min({mat[0][2], mat[3][2], mat[0][1], mat[1][3]})) {
                ans += '3';
            }
            if (rad < min({mat[1][2], mat[3][1], mat[0][1]})) {
                ans += '2';
            }
            ans += '1';
        } else if (pos == 1) {
            if (rad < min({mat[1][2], mat[3][1], mat[0][1]})) {
                ans += '1';
            }
            if (rad < min({mat[1][2], mat[3][2], mat[0][2]})) {
                ans += '3';
            }
            if (rad < min({mat[1][2], mat[3][0], mat[0][2], mat[1][3]})) {
                ans += '4';
            }
            ans += '2';
        } else if (pos == 2) {
            if (rad < min({mat[0][2], mat[3][2], mat[0][1], mat[1][3]})) {
                ans += '1';
            }
            if (rad < min({mat[1][2], mat[3][2], mat[0][2]})) {
                ans += '2';
                // tr(mat[2]);
            }
            if (rad < min({mat[1][3], mat[3][2], mat[0][3]})) {
                // tr(rad, mat[3]);
                ans += '4';
            }
            ans += '3';
        } else {
            if (rad < min({mat[0][3], mat[0][2], mat[0][1]})) {
                ans += '1';
            }
            if (rad < min({mat[1][2], mat[3][0], mat[0][2], mat[1][3]})) {
                ans += '2';
            }
            if (rad < min({mat[1][3], mat[3][2], mat[0][3]})) {
                ans += '3';
            }
            ans += '4';
        }
        sort(all(ans));
        cout << ans << endl;
    }
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
}
