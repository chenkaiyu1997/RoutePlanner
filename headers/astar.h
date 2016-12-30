#ifndef _ASTAR_H
#define _ASTAR_H

// #include "../headers/basic.h"
// #include "../headers/point.h"
// #include "../headers/edge.h"


class astarnode {
public:
	double h, g;
	int u;
	astarnode();
	astarnode(int _u, double _g, const roadpoint& B);
	friend bool operator< (const astarnode& A, const astarnode& B);
};

extern priority_queue<astarnode> q;
extern map<int, int> pre;
vector<int> Astar(roadpoint& A, roadpoint& B, double& totdis);

#endif