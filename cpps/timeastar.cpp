#include "../headers/basic.h"
#include "../headers/point.h"
#include "../headers/edge.h"
#include "../headers/kdtree.h"
#include "../headers/roadtime.h"
#include "../headers/timeastar.h"


timeastarnode::timeastarnode(){}
timeastarnode::timeastarnode(int _u, double _g, double _dist, const roadpoint& B){
	h = dis(B.p, a[_u]) / 25; // Time lowerbound
	g = _g;
	u = _u;
	dist = _dist;
}
bool operator< (const timeastarnode& A, const timeastarnode& B) {
	return A.h + A.g > B.h + B.g;
}


priority_queue<timeastarnode> q;
map<int, int> pre;


vector<int> TimeAstar(int ti, roadpoint& A, roadpoint& B, double& totdis, double& tottime) {
	while(!q.empty()) q.pop();
	pre.clear();
	double tmpu = dis(A.p, a[A.u]);
	double tmpv = dis(A.p, a[A.v]); 
	q.push(timeastarnode(A.u, tmpu / speed[ti][A.edgenumber], tmpu, B));
	q.push(timeastarnode(A.v, tmpv / speed[ti][A.edgenumber], tmpv, B));
	pre[A.u] = 0; pre[A.v] = 0;
	vector<int> path2;
	vector<int> path;
	path.clear();path2.clear();

	while(!q.empty()) {
		timeastarnode now = q.top();
		q.pop();
		for(int i = b[now.u]; i != -1; i = e[i].nxt) {
			if(e[i].v == B.u || e[i].v == B.v) {
				path2.push_back(e[i].v);
				tottime = now.g + e[i].w / speed[ti][i];
				totdis = now.dist + e[i].w;
				if(e[i].v == B.u){
					tmpu = dis(B.p, a[B.u]);
					totdis += tmpu;
					tottime += tmpu / speed[ti][B.edgenumber];
				}
				else{
					tmpv = dis(B.p, a[B.v]);
					totdis += tmpv;
					tottime += tmpv / speed[ti][B.edgenumber];
				}
				for(int j = now.u; j != 0; j = pre[j])
					path2.push_back(j);
				for(int i = (int)path2.size() - 1; i >= 0; i--)
					path.push_back(path2[i]);
				return path;
			}
			if(pre.count(e[i].v))continue;
			pre[e[i].v] = now.u;
			q.push(timeastarnode(e[i].v, now.g + e[i].w / speed[ti][i], now.dist + e[i].w , B));
		}
	}
	return path;
}