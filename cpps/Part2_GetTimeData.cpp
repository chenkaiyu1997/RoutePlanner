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
int main(int argc, char** argv) {
	int lbound = 1, rbound = 5883;
	int zu = 9;
	if(argc > 1){
		zu = argv[1][0] - '0';
		lbound = zu * 1000 + 1;
		rbound = zu * 1000 + 1000;
		if(zu == 5) rbound = 5883;
	}

	string outfile = "../data/roadspeed/averagespeed" + to_string(zu) + ".txt";
	freopen(outfile.c_str(), "w", stdout);

	initroad();
	memset(RoadSpeedCount::vcnt, 0, sizeof(RoadSpeedCount::vcnt));
	memset(RoadSpeedCount::icnt, 0, sizeof(RoadSpeedCount::icnt));


	for(int tc = lbound; tc <= rbound; tc++) {
		cerr<<tc<<endl;
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
				r[++totrides].linestartnumber = i;
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
	}
	int goodcnt = 0;
	for(int i = 0; i < en; i++) {
		for(int j = 0; j < 72; j++) {
			double tmp = (double)RoadSpeedCount::vcnt[j][i] / (double)RoadSpeedCount::icnt[j][i] / 3.6;
			if(RoadSpeedCount::icnt[j][i] < 2 || tmp <= 0.5 || tmp >= 180)
				tmp = 10 / 3.6;
			else goodcnt ++;
			printf("%.2lf %d ", tmp, RoadSpeedCount::icnt[j][i]);
		}
		printf("\n");
	}
	cerr<<goodcnt<<endl;
	return 0;
}