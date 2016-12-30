#include "../headers/basic.h"
#include "../headers/analyse.h"

double money[5][6000];
int cnt[5][6000];
double driverdis[5][6000];
int ondelivertime[5][6000];
int ongoingtime[5][6000];
int kongtime[5][6000];


double getmoney(double dist) {
	if(dist < 3000)
		return 14;
	return 14 + (dist - 3000) / 1000 * 2.4;
}

double getoil(double dist) {
	return dist / 1000 * 0.5;
}

void initanalyse() {
	memset(money, 0, sizeof(money));
	memset(cnt, 0, sizeof(cnt));
	memset(driverdis, 0, sizeof(driverdis));
	memset(ongoingtime, 0, sizeof(ongoingtime));
	memset(ondelivertime, 0, sizeof(ondelivertime));
	memset(kongtime, 0, sizeof(kongtime));
}

void outputanalyse(int tc, int i){
	printf("%d %d %d %d %.2lf %.2lf\n", ondelivertime[tc][i], ongoingtime[tc][i], kongtime[tc][i], cnt[tc][i], driverdis[tc][i], money[tc][i]);
}