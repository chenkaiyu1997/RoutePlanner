#ifndef _TIMEASTAR_H
#define _TIMEASTAR_H

#include "../headers/basic.h"
#include "../headers/point.h"
#include "../headers/edge.h"


class timeastarnode {
public:
	double h, g;
	double dist;
	int u;
	timeastarnode();
	timeastarnode(int _u, double _g, double _dist, const roadpoint& B);
	friend bool operator< (const timeastarnode& A, const timeastarnode& B);
};

extern priority_queue<timeastarnode> q;
extern map<int, int> pre;
vector<int> TimeAstar(int ti, roadpoint& A, roadpoint& B, double& totdis, double& tottime);

#endif