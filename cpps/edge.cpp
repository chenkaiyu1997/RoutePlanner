#include "../headers/basic.h"
#include "../headers/point.h"
#include "../headers/edge.h"

edge e[N*2];
int en;
int b[N];

void addedge(int u, int v) {
	e[en].u = u;
	e[en].v = v;
	e[en].nxt = b[u];
	e[en].w = dis(a[u], a[v]);
	b[u] = en++;
}