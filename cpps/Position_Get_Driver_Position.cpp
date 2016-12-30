#include "../headers/basic.h"
#include "../headers/point.h"
#include "../headers/edge.h"
#include "../headers/kdtree.h"
#include "../headers/astar.h"
#include "../headers/analyse.h"
#include "../headers/initroad.h"
#include "../headers/getprojection.h"


struct rp{
	int ti;
	int x, y;
	int v, kong;
}rpa[100005];

Point position[4][6000];

int main() {
	initroad();
	vector<roadpoint> ans;
	vector<int> cps;

	memset(position,0,sizeof(position));
	for(int tc = 1; tc <= 5883; tc++) {
		if(tc % 100 == 0)
			cerr<<tc<<endl;
		string infile = "../data/Trajectory/" + to_string(tc) + ".txt";
		freopen(infile.c_str(), "r", stdin);
		int m;
		scanf("%d", &m);
		memset(rpa, 0, sizeof(rpa));
		for(int i = 1; i <= m; i++) {
			scanf("%d %d %d %d %d", &rpa[i].ti, &rpa[i].x, &rpa[i].y, &rpa[i].kong, &rpa[i].v);
			rpa[i].ti += rpa[i-1].ti;
			rpa[i].x += rpa[i-1].x;
			rpa[i].y += rpa[i-1].y;
		}
		for(int i = 1; i <= m; i++) {
			rpa[i].x /= 10;
			rpa[i].y /= 10;
		}
		for(int i = 1; i <= m; i++) {
			if(position[rpa[i].ti / (6*3600)][tc].x == 0)
				position[rpa[i].ti / (6*3600)][tc] = Point(rpa[i].x, rpa[i].y);
		}
	}
	for(int tc = 0; tc < 4; tc++) {
		string outfile = "../data/driverpositions/driverposition" + to_string(tc + 1) + ".txt";
		freopen(outfile.c_str(), "w", stdout);
		printf("%d\n", 5883);
		for(int i = 1; i <= 5883; i++) {
			if(i % 100 == 0)
				cerr<<i<<endl;
			if(position[tc][i].x == 0) {
				position[tc][i] = Point(rpa[1].x, rpa[1].y);
			}
			ans = getroadpoints(position[tc][i]);
			if(ans.size() == 0) {
				roadnodetree.queryknearest(100, position[tc][i], cps);
				for(int j = 0; j < 100; j++){
					position[tc][i] = a[cps[j]];
					ans = getroadpoints(position[tc][i]);
					if(ans.size() > 0) break;
				}	
				if(ans.size() == 0)cerr<<"ERROR!";
			}
			ans = getknearest(1, ans, position[tc][i]);
			printf("%d %d %d %d\n", ans[0].p.x, ans[0].p.y, ans[0].u, ans[0].v);
		}
	}
	return 0;
}