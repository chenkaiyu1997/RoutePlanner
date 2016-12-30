#include "../headers/basic.h"
#include "../headers/point.h"
#include "../headers/analyse.h"

using namespace std;


struct rp{
	int ti;
	int x, y;
	int v, kong;
}rpa[100005];

struct ride {
	int pickuptime;
	int endtime;
	double totdis;
}r[1005];

bool cmp(const ride& A, const ride& B){
	return A.pickuptime < B.pickuptime;
}


int main() {
	initanalyse();

	int totrides = 0;

	for(int tc = 1; tc <= 5883; tc++) {
		//cerr<<tc<<" ";
		string infile = "../data/Trajectory/" + to_string(tc) + ".txt";
		freopen(infile.c_str(), "r", stdin);
		int m;
		scanf("%d", &m);
		cerr<<m<<" ";
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
		bool zairen = false;
		totrides = 0;
		for(int i = 2; i <= m; i++) {
			//printf("%d\n", rpa[i].ti);
			driverdis[rpa[i].ti / 21600 + 1][tc] += dis(Point(rpa[i].x, rpa[i].y), Point(rpa[i-1].x, rpa[i-1].y));
			if(zairen == false && rpa[i-1].kong == 1 && rpa[i].kong == 0){
				r[++totrides].pickuptime = rpa[i].ti;
				r[totrides].totdis = 0;
				zairen = true;
				continue;
			}
			if(zairen) {
				r[totrides].totdis += dis(Point(rpa[i].x, rpa[i].y), Point(rpa[i-1].x, rpa[i-1].y));
				//printf("pdis = %.2lf\n", dis(Point(rpa[i].x, rpa[i].y), Point(rpa[i-1].x, rpa[i-1].y))); 
			}
			if(zairen==true && rpa[i-1].kong == 0 && rpa[i].kong == 1) {
				r[totrides].endtime = rpa[i].ti;
				zairen = false;
				if(r[totrides].endtime - r[totrides].pickuptime < 20) totrides--;
				//printf("dis = %.2lf\n", r[totrides].totdis);
			}
		}
		if(zairen == true) totrides--;

		for(int j = 1; j <= totrides; j++) {
			int ti = r[j].pickuptime / 21600 + 1;
			money[ti][tc] += getmoney(r[j].totdis) - getoil(r[j].totdis);
			cnt[ti][tc] ++;
			ondelivertime[ti][tc] += r[totrides].endtime - r[totrides].pickuptime;
		}
	}
	for(int ti = 1; ti <= 4; ti++){
		string tmpstring = "../data/results/Task1result" + to_string(ti) + ".txt";
		freopen(tmpstring.c_str(), "w", stdout);
		for(int i = 1;i <= 5883; i++)
			outputanalyse(ti, i);
	}
}