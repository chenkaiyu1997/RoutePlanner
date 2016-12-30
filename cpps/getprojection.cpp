#include "../headers/basic.h"
#include "../headers/point.h"
#include "../headers/edge.h"
#include "../headers/kdtree.h"
#include "../headers/getprojection.h"

roadpoint getprojection(int u, const Point& A, int v, const Point& B, const Point& C) {
	roadpoint ans;
	Point v1 = C - A;
	Point v2 = B - A;
	double dotvalue = dot(v1, v2);
	Point v3 = C - B;
	Point v4 = A - B;
	double dotvalue2 = dot(v3, v4);
	if(dotvalue <= 0 || dotvalue2 <= 0) {
		ans.u = -1;
		return ans;
	}
	double dist = pseudodis(A, B);
	double di = (dotvalue / dist) / dist;
	Point v5 = B - A;
	v5 *= di;
	ans.p = v5 + A;
	ans.u = u; ans.v = v;
	return ans;
}

vector<roadpoint> getroadpoints(const Point& p) {
	vector<roadpoint> ans;
	vector<int> cps;
	ans.clear();

	roadnodetree.queryknearest(50, p, cps);
	for(vector<int>::iterator it = cps.begin(); it!= cps.end(); it++) {
		//cerr<<*it<<" "<<b[*it]<<endl;
		for(int i = b[*it]; i != -1; i = e[i].nxt) {
			roadpoint tmp = getprojection(e[i].u, a[e[i].u], e[i].v, a[e[i].v], p);
			if(tmp.u != -1)
				ans.push_back(tmp);
		}

	}
	return ans;
}	

vector<roadpoint> getknearest(int k, const vector<roadpoint>& w, const Point& p) {
	priority_queue<prinode> q;
	while(!q.empty())q.pop();
	for(int i = 0; i < (int)w.size(); i++) {
		double dist = dis(w[i].p, p);
		q.push(prinode(-dist, i));
	}
	vector<roadpoint> ans;
	ans.clear();
	while(k && !q.empty()){
		ans.push_back(w[q.top().id]);
		q.pop();
		k--;
	}
	return ans;
}