#include "../headers/basic.h"
#include "../headers/point.h"
#include "../headers/edge.h"
#include "../headers/kdtree.h"
#include "../headers/astar.h"
#include "../headers/analyse.h"
#include "../headers/initroad.h"
#include "../headers/getprojection.h"
#include "../headers/Map_Matching.h"
#include "../headers/ride.h"


ride r[10005];
tranode rpa[10005];
HMM hmm;
int main() {
	freopen("../data/averagespeed.txt", "w", stdout);
	initroad();
	memset(RoadSpeedCount::vcnt, 0, sizeof(RoadSpeedCount::vcnt));
	memset(RoadSpeedCount::icnt, 0, sizeof(RoadSpeedCount::icnt));


	for(int tc = 1; tc <= 3; tc++) {
		string infile = "../data/Trajectory/" + to_string(tc) + ".txt";
		freopen(infile.c_str(), "r", stdin);
		int m;
		scanf("%d", &m);
		memset(rpa, 0, sizeof(rpa));
		for(int i = 1; i <= m; i++) {
			scanf("%d %d %d %d %d", &rpa[i].ti, &rpa[i].p.x, &rpa[i].p.y, &rpa[i].kong, &rpa[i].v);
			rpa[i].ti += rpa[i-1].ti;
			rpa[i].p.x += rpa[i-1].p.x;
			rpa[i].p.y += rpa[i-1].p.y;
		}
		for(int i = 1; i <= m; i++) {
			rpa[i].p.x /= 10;
			rpa[i].p.y /= 10;
		}
		int totrides = 0;
		bool zairen = false;
		for(int i = 2; i <= m; i++) {
			//printf("%d\n", rpa[i].ti);

			if(zairen == false && rpa[i-1].kong == 1 && rpa[i].kong == 0){
				r[totrides].linestartnumber = i;
				r[totrides].ridedis = 0;
				zairen = true;
			}
			if(zairen==true && rpa[i-1].kong == 0 && rpa[i].kong == 1) {
				r[totrides].lineendnumber = i - 1;
				hmm.mapmatching(rpa + r[totrides].linestartnumber, i - r[totrides].linestartnumber);
				zairen = false;
				if(r[totrides].endtime - r[totrides].pickuptime < 20) totrides--;
			}
		}
		if(zairen == true) totrides--;
		if(tc % 100 == 0)
			cerr<<tc<<" "<<totrides<<endl;
	}
	for(int i = 0; i < en; i++) {
		for(int j = 0; j < 72; j++) {
			printf("%lf %d ", (double)RoadSpeedCount::vcnt[j][i] / (double)RoadSpeedCount::icnt[j][i], RoadSpeedCount::icnt[j][i]);
		}
		printf("\n");
	}
	return 0;
}