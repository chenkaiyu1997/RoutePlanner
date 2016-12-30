#include "../headers/basic.h"
#include "../headers/initroad.h"
#include "../headers/point.h"
#include "../headers/edge.h"
#include "../headers/kdtree.h"


void initroad() {
	int n,m;
	freopen("../data/road.txt", "r", stdin);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i].x, &a[i].y);
		a[i].id = i;
	}
	int rt;
	roadnodetree.init(n, a, rt);
	en = 0;
	memset(b, -1, sizeof(b));
	int u, v;
	for(int i = 1; i <= m; i++) {
		scanf("%d %d", &u, &v);
		addedge(u, v);
		addedge(v, u);
	}
}