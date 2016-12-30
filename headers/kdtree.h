#ifndef _KDTREE_H
#define _KDTREE_H

//#include "../headers/basic.h"
// #include "../headers/point.h"

class prinode {
public:
	double dist;
	int id;
	prinode(double _dist, int _id);
	friend bool operator< (const prinode& A, const prinode& B);	
};

class Kdtree {
public:
	double nowans;
	struct node {
		int d, lc, rc;
		int id;
		Point mn, mx, p;
	}t[N * 2];
	int st;
	int n;
	Point kdtreea[N];

	priority_queue<prinode> q;
	vector<int> ans;
	void init(int _n, Point *a, int& rt);

	void update(int u);
	
	int newnode(int id, int d, const Point& p);

    int build(Point *a, int l, int r, int d);

    void insert(int id, int u, const Point& p);

    double findnearst(int u, const Point& p);

	void query(int k, int u, const Point& p);

	void queryknearest(int k, const Point& p, vector<int>& ans);
};
extern Kdtree roadnodetree;

#endif

