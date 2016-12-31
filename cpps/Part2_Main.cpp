#include "../headers/basic.h"
#include "../headers/point.h"
#include "../headers/edge.h"
#include "../headers/kdtree.h"
#include "../headers/ride.h"
#include "../headers/analyse.h"
#include "../headers/initroad.h"
#include "../headers/getprojection.h"
#include "../headers/roadtime.h"
#include "../headers/timeastar.h"

ride r[200005];


int main() {
	initroad();
	readroadtime();
	freopen("../data/rides.txt", "r", stdin);
	int totrides = 0;
	cin >> totrides;
	cout<< totrides <<endl;
	vector<roadpoint> ans;
	vector<int>cps;

	for(int i = 1; i <= 1000; i++) {
		 //if(i % 100 ==0 )
		inputride(r[i]);
		double timedis = 0;
		double time = 0;
		TimeAstar(r[i].pickuptime, r[i].pickupposition, r[i].endposition, timedis, time);
		cerr << 1 - fabs(r[i].ridedis - r[i].astardis) / r[i].ridedis << "\t" << 1 - fabs(r[i].ridedis - timedis ) / r[i].ridedis;
		cerr << "\t"<<fabs(time - r[i].endtime + r[i].pickuptime) / (double)(r[i].endtime - r[i].pickuptime) << endl;
	}
	return 0;
}