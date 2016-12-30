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
	freopen("../data/rides_raw.txt", "r", stdin);
	freopen("../data/rides_proj.txt", "w", stdout);
	int totrides = 0;
	cin >> totrides;
	cout<< totrides <<endl;
	vector<roadpoint> ans;
	vector<int>cps;

	for(int i = 1; i <= totrides; i++) {
		 if(i % 100 ==0 )
			cerr<<i<<endl;
		inputride(r[i]);
		ans = getroadpoints(r[i].pickupposition.p);
		if(ans.size() == 0) {
			roadnodetree.queryknearest(100, r[i].pickupposition.p, cps);
			for(int j = 0; j < 100; j++){
				r[i].pickupposition.p = a[cps[j]];
				ans = getroadpoints(r[i].pickupposition.p);
				if(ans.size() > 0) break;
			}	
			if(ans.size() == 0)cerr<<"ERROR!";
		}
		ans = getknearest(1, ans, r[i].pickupposition.p);
		r[i].pickupposition = ans[0];

		ans = getroadpoints(r[i].endposition.p);
		if(ans.size() == 0) {
			roadnodetree.queryknearest(100, r[i].endposition.p, cps);
			for(int j = 0; j < 100; j++){
				r[i].endposition.p = a[cps[j]];
				ans = getroadpoints(r[i].endposition.p);
				if(ans.size() > 0) break;
			}	
			if(ans.size() == 0)cerr<<"ERROR!";
		}
		ans = getknearest(1, ans, r[i].endposition.p);
		r[i].endposition = ans[0];

		outputride(r[i]);
	}
	return 0;
}