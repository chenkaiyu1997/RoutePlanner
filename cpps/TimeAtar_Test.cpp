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
	freopen("../data/rides_proj.txt", "r", stdin);
	freopen("../data/rides_timeastar.txt", "w", stdout);
	int totrides = 0;
	cin >> totrides;
	cout<< totrides <<endl;
	vector<roadpoint> ans;
	vector<int>cps;

	for(int i = 1; i <= 100; i++) {
		 //if(i % 100 ==0 )
		cerr<<i<<endl;
		inputride(r[i]);
		r[i].astardis = 0;
		double time = 0;
		TimeAstar(r[i].pickuptime, r[i].pickupposition, r[i].endposition, r[i].astardis, time);
		cerr << time - r[i].endtime + r[i].pickuptime << endl;
		outputride(r[i]);
	}
	return 0;
}