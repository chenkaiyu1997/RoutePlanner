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
	int ti;
	printf("Input time: 0h to 23h: \t");
	scanf("%d", &ti);
	if(ti > 23 || ti < 0){
		printf("time error!");
		return 0;
	}
	ti *= 3600;
	printf("Input the start Point: input example:\n");
	printf("121.509 31.305 and 121.6 31.19\n");
	double tmpx, tmpy;
	roadpoint startPoint, endPoint;
	printf("Startpoint: ");
	cin >>  tmpx >> tmpy;
	//tmpx = 121.509;tmpy = 31.305;
	startPoint.p.x = (int)(tmpx * 100000);
	startPoint.p.y = (int)(tmpy * 100000);
	printf("Destination: ");

	cin >> tmpx >> tmpy;
	//tmpx = 121.6;tmpy = 31.19;
	endPoint.p.x = (int)(tmpx * 100000);
	endPoint.p.y = (int)(tmpy * 100000);

	initroad();
	readroadtime2();
	vector<roadpoint> ans;
	vector<int>cps;
	vector<int>path;
	ans = getroadpoints(startPoint.p);
	if(ans.size() == 0) {
		printf("Too far from road! Please try again");
		return 0;
	}
	else{
		ans = getknearest(1, ans, startPoint.p);
		startPoint = ans[0];
	}


	ans = getroadpoints(endPoint.p);
	if(ans.size() == 0) {
		printf("Too far from road! Please try again");
		return 0;
	}
	else{
		ans = getknearest(1, ans, endPoint.p);
		endPoint = ans[0];
	}

	double timedis, time;
	path = TimeAstar(ti, startPoint, endPoint, timedis, time);
	printf("Estimated time %dmin %ds, distance %dm \n", (int)time/60, (int)time % 60, (int)timedis);
	printf("Printing path...done");
	freopen("../data/toshow.txt", "w", stdout);

	// cout<<m<<endl;
	// for(int i = 1; i <= m; i++) {
	// 	printf("%d %d %d %d %d\n", ridea[i].ti - ridea[i-1].ti, ans[i].x - ans[i-1].x, ans[i].y - ans[i-1].y, ridea[i].kong, ridea[i].v);
	// }
	int len = path.size();
	cout << len + 1 << endl;
	printf("%d %d %d %d\n", startPoint.p.x, startPoint.p.y, a[path[0]].x, a[path[0]].y);
	for(int i = 0; i < len - 1; i++)
		printf("%d %d %d %d\n", a[path[i]].x, a[path[i]].y , a[path[i + 1]].x, a[path[i + 1]].y);
	printf("%d %d %d %d\n", a[path[len - 1]].x, a[path[len - 1]].y, endPoint.p.x, endPoint.p.y);

	cout<<1<<endl;
	printf("%d %d\n", startPoint.p.x, startPoint.p.y);
	cout<<0<<endl;
	return 0;
}