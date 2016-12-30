#include "../headers/basic.h"
#include "../headers/point.h"
#include "../headers/edge.h"
#include "../headers/kdtree.h"
#include "../headers/astar.h"
#include "../headers/ride.h"
#include "../headers/analyse.h"
#include "../headers/initroad.h"
#include "../headers/getprojection.h"

ride r[200005];


int main() {
	initroad();
	freopen("../data/rides_proj.txt", "r", stdin);
	freopen("../data/rides.txt", "w", stdout);
	int totrides = 0;
	cin >> totrides;
	cout<< totrides <<endl;
	vector<roadpoint> ans;
	vector<int>cps;

	for(int i = 1; i <= totrides; i++) {
		 if(i % 100 ==0 )
			cerr<<i<<endl;
		inputride(r[i]);
		r[i].astardis = 0;
		Astar(r[i].pickupposition, r[i].endposition, r[i].astardis);
		outputride(r[i]);
	}
	return 0;
}