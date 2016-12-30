#include "../headers/basic.h"

using namespace std;

struct point{
	int x, y;
	bool exi;
}a[N];

struct edge{
	int u, v,nxt;
	bool exi;
}e[N*2];
int en;
int b[N];
int fa[N];
bool vis[N];
double compression_rate;
int cnt[N];
int newindex[N];
int findfa(int p) {
	return p == fa[p] ? p : (fa[p] = findfa(fa[p]));
}
void addedge(int u, int v) {
	e[en].u = u;
	e[en].v=v;
	e[en].nxt = b[u];
	b[u] = en++;
}


inline double dis(const point& A, const point& B) {
	return sqrt(1.0* (A.x - B.x) * (A.x - B.x) + 1.0* (A.y - B.y) * (A.y - B.y));
}
inline double cross(double x1,double y1, double x2, double y2) {
	return x1 * y2 - x2 * y1;
}
inline double getArea(const point& p0, const point& p1, const point& p2) {
	return fabs(cross(p1.x - p0.x, p1.y - p0.y, p2.x - p0.x, p2.y - p0.y));
}

int main() {
	freopen("../data/roadraw.txt", "r", stdin);
	freopen("../data/roadmain.tmp", "w", stdout);
	int n,m;
	scanf("%d %d", &n, &m);
	memset(b, -1, sizeof(b));
	en = 0;
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i].x, &a[i].y);
		fa[i] = i;
	}
	int u,v;

	for(int i = 1; i <= m; i++) {
		scanf("%d %d", &u, &v);
		addedge(u, v);
		addedge(v, u);
		u = findfa(u); v = findfa(v);
		fa[u] = v;
	}

	int newn = 0, newm = 0;
	for(int i = 1; i <= n; i++) {
		cerr << findfa(i) << endl;
		if(findfa(i) == 189636) {
			newindex[i] = ++newn;
			a[i].exi = true;
		}
		else
			a[i].exi = false;
	}
	for(int i = 0; i < en; i++) {
		if(a[e[i].u].exi && a[e[i].v].exi && e[i].u < e[i].v){
			e[i].exi = true;
			newm ++;
		}
		else
			e[i].exi = false;
	}
	printf("%d %d\n", newn, newm);
	for(int i = 1; i <= n; i++)
		if(a[i].exi)
			printf("%d %d\n", a[i].x, a[i].y);
	for(int i = 0; i < en; i++) {
		if(a[e[i].u].exi && a[e[i].v].exi && e[i].u < e[i].v)
			printf("%d %d\n", newindex[e[i].u], newindex[e[i].v]);
	}

	// for(int i = 1; i <= n; i++) 
	// 	printf("%d\n", findfa(i));
	//printf("%d\n", n - cnt0);

	//dfs(1);

	// for(int i = 1; i )
	// for(int tc = 1; tc <= 2; tc++) {
	// 	string infile = "mytras/" + to_string(tc) + ".txt";
	// 	string outfile = "comedmytras/" + to_string(tc) + ".txt";
	// 	freopen(infile.c_str(), "r", stdin);
	// 	freopen(outfile.c_str(), "w", stdout);
	// 	int m;
	// 	scanf("%d", &m);
	// 	memset(a, 0, sizeof(a));
	// 	for(int i = 1; i <= m; i++) {
	// 		scanf("%d %d %d %d %d", &a[i].ti, &a[i].x, &a[i].y, &a[i].kong, &a[i].v);
	// 		a[i].ti += a[i-1].ti;
	// 		a[i].x += a[i-1].x;
	// 		a[i].y += a[i-1].y;
	// 	}
	// 	cnt = 2;
	// 	a[1].exi = 1; a[m].exi = 1;
	// 	Trajectory_Compression(1, m);
	// 	printf("%d\n", cnt);
	// 	for(int i = 1; i <= m; i++) {
	// 		if(a[i].exi) 
	// 			printf("%d %d %d %d %d\n", a[i].ti, a[i].x, a[i].y, a[i].kong, a[i].v);
	// 	}
	// 	compression_rate[tc] = 1.0 * cnt / m;
	// }
	return 0;
}