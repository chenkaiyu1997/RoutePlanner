#include "../headers/basic.h"
#include "../headers/point.h"
#include "../headers/ride.h"

using namespace std;


struct rp{
	int ti;
	int x, y;
	int v, kong;
}rpa[100005];

ride r[300005];

bool cmp(const ride& A, const ride& B){
	return A.pickuptime < B.pickuptime;
}
int main() {
	freopen("../data/rides_raw.txt", "w", stdout);
	int totrides = 0;
	for(int tc = 1; tc <= 5883; tc++) {
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
		bool zairen = false;
		for(int i = 2; i <= m; i++) {
			//printf("%d\n", rpa[i].ti);

			if(zairen == false && rpa[i-1].kong == 1 && rpa[i].kong == 0){
				r[++totrides].pickuptime = rpa[i].ti;
				r[totrides].pickupposition.p = Point(rpa[i].x, rpa[i].y);
				r[totrides].linestartnumber = i;
				r[totrides].ridedis = 0;
				zairen = true;
			}

			if(zairen) {
				r[totrides].ridedis += dis(Point(rpa[i].x, rpa[i].y), Point(rpa[i-1].x, rpa[i-1].y));
				//printf("pdis = %.2lf\n", dis(Point(rpa[i].x, rpa[i].y), Point(rpa[i-1].x, rpa[i-1].y))); 
			}
			if(zairen==true && rpa[i-1].kong == 0 && rpa[i].kong == 1) {
				r[totrides].endtime = rpa[i].ti;
				r[totrides].endposition.p = Point(rpa[i].x, rpa[i].y);
				r[totrides].drivernum = tc;
				r[totrides].lineendnumber = i - 1;
				zairen = false;
				if(r[totrides].endtime - r[totrides].pickuptime < 20) totrides--;
			}
		}
		if(zairen == true) totrides--;
		if(tc % 100 == 0)
			cerr<<tc<<" "<<totrides<<endl;
	}
	sort(r+1, r+totrides+1, cmp);
	printf("%d\n", totrides);
	for(int i = 1; i <= totrides; i++)
		outputride(r[i]);
}