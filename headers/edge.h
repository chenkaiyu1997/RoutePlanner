#ifndef _EDGE_H
#define _EDGE_H

struct edge{
	int u, v, nxt;
	double w;
};

extern edge e[N*2];
extern int en;
extern int b[N];

void addedge(int u, int v);

#endif