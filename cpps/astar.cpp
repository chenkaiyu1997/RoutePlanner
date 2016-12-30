#include "../headers/basic.h"
#include "../headers/point.h"
#include "../headers/edge.h"
#include "../headers/kdtree.h"
#include "../headers/astar.h"

astarnode::astarnode(){}
astarnode::astarnode(int _u, double _g, const roadpoint& B){
	h = dis(B.p, a[_u]);
	g = _g;
	u = _u;
}
bool operator< (const astarnode& A, const astarnode& B) {
	return A.h + A.g > B.h + B.g;
}


priority_queue<astarnode> q;
map<int, int> pre;


vector<int> Astar(roadpoint& A, roadpoint& B, double& totdis) {
	while(!q.empty()) q.pop();
	pre.clear();
	q.push(astarnode(A.u, dis(A.p, a[A.u]), B));
	q.push(astarnode(A.v, dis(A.p, a[A.v]), B));
	pre[A.u] = 0; pre[A.v] = 0;
	vector<int> path2;
	vector<int> path;
	path.clear();path2.clear();

	while(!q.empty()) {
		astarnode now = q.top();
		q.pop();
		for(int i = b[now.u]; i != -1; i = e[i].nxt) {
			if(e[i].v == B.u || e[i].v == B.v) {
				path2.push_back(e[i].v);
				totdis = now.g + e[i].w;
				if(e[i].v == B.u)
					totdis += dis(B.p, a[B.u]);
				else
					totdis += dis(B.p, a[B.v]);
				for(int j = now.u; j != 0; j = pre[j])
					path2.push_back(j);
				for(int i = (int)path2.size() - 1; i >= 0; i--)
					path.push_back(path2[i]);
				return path;
			}
			if(pre.count(e[i].v))continue;
			pre[e[i].v] = now.u;
			q.push(astarnode(e[i].v, now.g + e[i].w , B));
		}
	}
	return path;
}