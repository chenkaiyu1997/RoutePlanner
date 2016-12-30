#include "../headers/basic.h"
#include "../headers/point.h"
#include "../headers/edge.h"
#include "../headers/kdtree.h"

Kdtree roadnodetree;
prinode::prinode(double _dist, int _id) {
	dist = _dist; id = _id;
}
bool operator< (const prinode& A, const prinode& B) {
	return A.dist < B.dist;
}	

void Kdtree::init(int _n, Point *a, int& rt) {
	n = _n;
	st = 0;
	memcpy(kdtreea, a, sizeof(kdtreea));
	rt = build(kdtreea, 1, n, 0);
}

void Kdtree::update(int u) {  
    int l = t[u].lc, r = t[u].rc;
    t[u].mn = t[u].mx = t[u].p;
    if(l){
    	t[u].mn = min(t[u].mn, t[l].mn);
    	t[u].mx = max(t[u].mx, t[l].mx);
    }
    if(r){
    	t[u].mn = min(t[u].mn, t[r].mn);
    	t[u].mx = max(t[u].mx, t[r].mx);
    }
}
int Kdtree::newnode(int id, int d, const Point& p) {
	t[++st].p = p;
	t[st].d = d;
	t[st].lc = t[st].rc = 0;
	t[st].id = id;
	update(st);
	return st;
}

int Kdtree::build(Point *a, int l, int r, int d) {
	if(l > r)return 0;

	int u = ++st;
	int mid = (l + r) / 2;
	globald = d;
	nth_element(a + l, a + mid, a + r + 1);

	t[u].d = d;
	t[u].p = a[mid];
	t[u].id = a[mid].id;
	t[u].lc = build(a, l, mid - 1, d ^ 1);
	t[u].rc = build(a, mid + 1, r, d ^ 1);
	update(u);
	return u;
}

void Kdtree::insert(int id, int u, const Point& p) {
	int& wayc = ((!t[u].d && p.x < t[u].p.x) || (t[u].d && p.y < t[u].p.y))?t[u].lc:t[u].rc;
	if(wayc == 0) 
		wayc = newnode(id, t[u].d ^ 1, p);
	else
		insert(id, wayc, p);
	update(u);
}

double Kdtree::findnearst(int u, const Point& p){
	if(p.x >= t[u].mn.x && p.x <= t[u].mx.x){
		if(p.y >= t[u].mn.y && p.y <= t[u].mx.y)
			return 0;
		return min(dis(p, Point(p.x, t[u].mn.y)) , dis(p, Point(p.x, t[u].mx.y)));
	}
	if(p.y >= t[u].mn.y && p.y <= t[u].mx.y)
		return min(dis(p, Point(t[u].mn.x, p.y)) , dis(p, Point(t[u].mx.x, p.y)));

	double x = p.x <= t[u].mn.x ? t[u].mn.x : t[u].mx.x;
	double y = p.y <= t[u].mn.y ? t[u].mn.y : t[u].mx.y;
	return dis(p, Point(x, y));
}


void Kdtree::query(int k, int u, const Point& p) {
	double dist = dis(p, t[u].p);
	if((int)q.size() < k || q.top().dist > dist) {
		if((int)q.size() >= k) q.pop();
		q.push(prinode(dist, t[u].id));
	}

	double dl = inf, dr = inf;
	int l = t[u].lc, r = t[u].rc;
	if(l) dl = findnearst(l, p);
	if(r) dr = findnearst(r, p);
	if(dl > dr) {
		swap(l, r);
		swap(dl, dr);
	}
	if(l) 
		 if((int)q.size() < k || dl < q.top().dist) 
			query(k, l, p);
	if(r) 
		 if((int)q.size() < k || dr < q.top().dist) 
			query(k, r, p);
}

void Kdtree::queryknearest(int k, const Point& p, vector<int>& ans) {
	ans.clear();
	while(!q.empty())q.pop();
	query(k, 1, p);
	while(!q.empty()) {
		prinode now = q.top();
		q.pop();
		ans.push_back(now.id);
		//cerr<<now.id << " " << now.dist<<endl;
	}
}