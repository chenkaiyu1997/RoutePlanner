#include "../headers/basic.h"
#include "../headers/point.h"
#include "../headers/edge.h"
#include "../headers/kdtree.h"
#include "../headers/astar.h"
#include "../headers/analyse.h"
#include "../headers/initroad.h"
#include "../headers/getprojection.h"
#include "../headers/ride.h"

Point ordera[N];
Kdtree ordertree;

struct ordernode {
	int ti;
	roadpoint u, v;
	double dist;
};
ride r[5][80000];

struct onholdnode {
	int driverid;
	vector<int> path;
	Point pos;
	int orderid;
	int lastupdate;
	int pathpoint;
	onholdnode(){};
	onholdnode(int _driverid, const Point& A, const vector<int>& path2,int _o, int ti) {
		driverid = _driverid;
		pos = A;
		path = path2;
		orderid = _o;
		lastupdate = ti;
		pathpoint = 0;
	}
	friend bool operator< (const onholdnode& A, const onholdnode& B) {
		return A.driverid < B.driverid;
	}
};
list<onholdnode> onholdq;


roadpoint pos[5][6000];
int rn[5];
struct eventnode{
	int ti;
	int driverid;
	roadpoint pos;
	eventnode(){}
	eventnode(int _ti, int _driverid, const roadpoint& A) {
		pos = A;
		ti = _ti;
		driverid = _driverid;
	}
	friend bool operator< (const eventnode& A, const eventnode& B) {
		return A.ti > B.ti;
	}
};

void initorder() {
	for(int tc = 1; tc <= 4; tc++) {
		string tmpstring = "../data/rides/ride" + to_string(tc) + ".txt";
		freopen(tmpstring.c_str(), "r", stdin);
		cin >> rn[tc];
		for(int i = 1; i <= rn[tc]; i++)
			inputride(r[tc][i]);
	}
	for(int tc = 1; tc <= 4; tc++) {
		string tmpstring = "../data/driverpositions/driverposition" + to_string(tc) + ".txt";
		freopen(tmpstring.c_str(), "r", stdin);
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++)
			scanf("%d %d %d %d", &pos[tc][i].p.x, &pos[tc][i].p.y, &pos[tc][i].u, &pos[tc][i].v);
	}
}


set<int> de[6000];
priority_queue<eventnode> taskq;
void pushtask(int tc, int driverid, int ti, double mindist, int tochoose) {
	de[driverid].insert(tochoose);
	double dist = r[tc][tochoose].astardis;
	mindist += dist;
	money[tc][driverid] += getmoney(dist) - getoil(mindist);
	cnt[tc][driverid] ++;
	driverdis[tc][driverid] += mindist;
	ondelivertime[tc][driverid] += (int)round(dist / (40 / 3.6));
	ongoingtime[tc][driverid] += (int)round((mindist - dist) / (40 / 3.6));
	taskq.push(eventnode((int)round(mindist / (40 / 3.6)) + ti, driverid, r[tc][tochoose].endposition));
}


int main() {

	initroad();
	initorder();
	initanalyse();

	int totcars = 5883;
	for(int tc = 1; tc <= 4; tc++) {
		for(int i = 1; i <= 5883; i++)
			de[i].clear();
		string tmpstring = "../data/results/Task2_2result" + to_string(tc) + ".txt";
		freopen(tmpstring.c_str(), "w", stdout);

		while(!taskq.empty())taskq.pop();
		onholdq.clear();

		for(int i = 1; i <= totcars; i++) {
			taskq.push(eventnode(0, i, pos[tc][i]));
		}
		int nn = 0;
		for(int i = 1; i <= rn[tc] && r[tc][i].pickuptime < 0; i++) {
			ordera[++nn] = r[tc][i].pickupposition.p;
			ordera[nn].id = nn;
		}
		int rt;
		ordertree.init(nn, ordera, rt);
		vector<int> cps;
		vector<int> path;
		vector<int> minpath;
		for(nn = nn + 1; nn <= rn[tc]; nn++) {
			if(nn % 1000 == 0)cerr<<nn<<endl;
			ordertree.insert(nn, 1, r[tc][nn].pickupposition.p);
			while(!taskq.empty() && taskq.top().ti <= r[tc][nn].pickuptime){
				//cerr<<'.';
				eventnode now = taskq.top();
				taskq.pop();

				int k = 10;
				ordertree.queryknearest(k, now.pos.p, cps);

				//if(cps.size() != 10)cerr<<"error";
				double mindist = inf;
				int tochoose;
				for(int i = 0; i < k; i++) {
					double dist;
					path = Astar(now.pos, r[tc][cps[i]].pickupposition, dist);
					if(dist < mindist && de[now.driverid].count(cps[i]) == 0) {
						mindist = dist;
						tochoose = cps[i];
						minpath = path;
					}
				}
				if(dis(r[tc][cps[k - 1]].pickupposition.p, now.pos.p) > 3000) {
					onholdq.push_back(onholdnode(now.driverid, now.pos.p, minpath, tochoose, now.ti));
				}
				else {
					pushtask(tc, now.driverid, now.ti, mindist, tochoose);
				}
			}
			for(list<onholdnode>::iterator it = onholdq.begin(); it != onholdq.end(); it++) {
				//cerr<<',';
				int togotime = r[tc][nn].pickuptime - it -> lastupdate;
				kongtime[tc][it->driverid] += togotime;
				it -> lastupdate = r[tc][nn].pickuptime;
				double totdis = togotime * (10 / 3.6);

				while(totdis >= 0) {
					for(;it -> pathpoint < (int)(it -> path.size());it -> pathpoint++) {
						Point t0 = it -> pos;
						if(t0.x < 12100000 || t0.x > 12200000 || t0.y < 3000000 || t0.y > 3200000)
							cerr<<"error"<<t0.x << " " << t0.y<<endl;
						Point t1 = a[it -> path[it -> pathpoint]];
						double dist = dis(t0, t1);
						if(dist > 1 && totdis < dist){
							double aoft1 = totdis / dist;
							double aoft0 = 1 - aoft1;
							t0 *= aoft0;
							t1 *= aoft1;
							it -> pos = t0 + t1;
							totdis -= dist;
							break;
						}
						totdis -= dist;
						it -> pos = t1;
					}
					if(it -> pathpoint >= (int)(it -> path.size())){
						it -> pos = r[tc][it -> orderid].pickupposition.p;
						break;
					}
				}
				roadpoint currentroadpoint;
				currentroadpoint.p = it -> pos;
				if(it -> pathpoint == 0)
					currentroadpoint.u = it -> path[it ->  pathpoint];
				else
					currentroadpoint.u =  it -> path[it -> pathpoint - 1];

				if(it -> pathpoint >= (int)(it -> path.size()))
					currentroadpoint.v = it -> path[it ->  pathpoint - 1];
				else 
					currentroadpoint.v =  it -> path[it ->  pathpoint];


				if(dis(r[tc][nn].pickupposition.p, it -> pos) < 3000) {
					double mindist;
					Astar(currentroadpoint, r[tc][nn].pickupposition, mindist);
					pushtask(tc, it -> driverid, r[tc][nn].pickuptime, mindist, nn);
					onholdq.erase(it);
				}
				else if(dis(r[tc][it -> orderid].pickupposition.p, it -> pos) < 3000) {
					double mindist;
					Astar(currentroadpoint, r[tc][it -> orderid].pickupposition, mindist);
					pushtask(tc, it -> driverid, r[tc][nn].pickuptime, mindist, it -> orderid);
					onholdq.erase(it);
				}
			}
		}
		for(int i = 1;i <= totcars; i++)
			outputanalyse(tc, i);
	}
	return 0;
}