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
	freopen("../data/rides.txt", "r", stdin);
	int totrides;
	cin >> totrides;
	for(int i = 1; i <= totrides; i++)
		inputride(r[i]);
	int i = 1;
	int fx[5];
	fx[0] = 0; fx[1] = 6*3600; fx[2] = 12 * 3600; fx[3] = 18*3600; fx[4] = 24*3600;
	int cnt;
	for(int tc = 1; tc <= 4; tc++) {
		string outfile = "../data/rides/ride" + to_string(tc) + ".txt";
		freopen(outfile.c_str(), "w", stdout);
		cnt = 0;
		int initi = i;
		for(;i <= totrides && r[i].pickuptime<= fx[tc]; i++){
			cnt ++;
		}
		i = initi;
		cout<<cnt<<endl;
		for(;i <= totrides && r[i].pickuptime<= fx[tc]; i++){
			r[i].pickuptime -= 300 + fx[tc - 1];
			outputride(r[i]);
		}
	}
	return 0;
}