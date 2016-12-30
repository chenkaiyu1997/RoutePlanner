#include "../headers/basic.h"


using namespace std;
double thre = 10;
struct point{
	int x, y;
	bool exi;
}a[N];

struct edge{
	int u, v,nxt;
	bool exi;
}e[N*6];
int en;
int b[N];
int fa[N];
bool vis[N];
double compression_rate;
int deg[N];
int newindex[N];
void addedge(int u, int v) {
	e[en].u = u;
	e[en].v = v;
	e[en].nxt = b[u];
	e[en].exi = true;
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


void Trajectory_Compression(const vector<int>& v, const vector<int>& path, int l, int r) {
	a[v[l]].exi = true;a[v[r]].exi = true;

	double dist = dis(a[v[l]], a[v[r]]);
	if(dist < 1e-8) {
		if(r - l + 1 <= 2)return;
		int i = l + 1;
		a[v[i]].exi = true;
		Trajectory_Compression(v, path, l, i);
		Trajectory_Compression(v, path, i, r);
		return;
	}
	for(int i = l + 1; i < r; i++) {
		double area = getArea(a[v[l]], a[v[r]], a[v[i]]);
		if(area / dist >= thre) {
			a[v[i]].exi = true;
			Trajectory_Compression(v, path, l, i);
			Trajectory_Compression(v, path, i, r);
			return;
		}
	}
	if(r - l + 1 > 2){
		addedge(v[l], v[r]);
		addedge(v[r], v[l]);
		for(int i = l; i < r; i++)
			e[path[i]].exi = false;
	}
}

vector<int> emptyvector;
void dfs(int u, int fa, vector<int> v, vector<int> path) {
	vis[u] = 1;
	v.push_back(u);
	if(deg[u] == 1 && v.size() != 1){
		Trajectory_Compression(v, path, 0, (int)v.size() - 1);
		return;
	}
	for(int i = b[u]; i!=-1; i = e[i].nxt) {
		if(e[i].v == fa) continue;
		if(deg[e[i].v] > 2) {
			v.push_back(e[i].v);
			path.push_back(i);
			Trajectory_Compression(v, path, 0, (int)v.size() - 1);
			if(!vis[e[i].v])
				dfs(e[i].v, u, emptyvector, emptyvector);
			v.pop_back();
			path.pop_back();
		}
		if(!vis[e[i].v]) {
			path.push_back(i);
			dfs(e[i].v, u, v, path);
			path.pop_back();
		}

	}
}
int mmain() {
	freopen("../data/roadmain.tmp", "r", stdin);
	freopen("../data/road.txt", "w", stdout);
	int n,m;
	scanf("%d %d", &n, &m);
	memset(b, -1, sizeof(b));
	en = 0;
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i].x, &a[i].y);
		a[i].exi = false;
	}
	int u,v;
	memset(deg, 0,sizeof(deg));
	for(int i = 1; i <= m; i++) {
		scanf("%d %d", &u, &v);
		addedge(u, v);
		addedge(v, u);
		deg[u] ++;
		deg[v] ++;
	}

	memset(vis, 0, sizeof(vis));
	emptyvector.clear();

	for(int i = 1; i <= n; i++)
		if(!vis[i] && (deg[i] == 1 || deg[i] > 2 ))
			dfs(i, 0, emptyvector, emptyvector);
	int newn = 0, newm = 0;
	for(int i = 1; i <= n; i++)
		if(a[i].exi == true)
			newn ++;
	for(int i = 0; i < en; i++)
		if(e[i].exi &&  e[i].u < e[i].v && a[e[i].u].exi && a[e[i].v].exi)
			newm ++;
	printf("%d %d\n", newn, newm);

	int newindexcnt = 0;
	for(int i = 1; i <= n; i++)
		if(a[i].exi == true){
			printf("%d %d\n", a[i].x, a[i].y);
			newindex[i] = ++newindexcnt;
		}

	for(int i = 0; i < en; i++)
		if(e[i].exi && e[i].u < e[i].v  && a[e[i].u].exi && a[e[i].v].exi) 
			printf("%d %d\n",newindex[e[i].u], newindex[e[i].v]);
	return 0;
}


register char *_sp __asm__("rsp");
int main(){
	const int size=64*1024*1024;
	static char *sys, *mine(new char[size]+size-4096);
	sys=_sp;
	_sp=mine;
	
	mmain();
	
	_sp=sys;
}