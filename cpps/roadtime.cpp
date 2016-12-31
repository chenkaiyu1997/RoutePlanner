#include "../headers/edge.h"
#include "../headers/roadtime.h"

double speed[73][400005];
int vcnt[73][400005];
int icnt[73][400005];
int totcnt[400005];
double speedpattern[] = {15,18.8889,17.5,14.7222,18.3333,17.2222,20,20.2778,15.5556,15.5556,17.5,12.5,18.3333,20.5556,24.4444,23.6111,19.1667,23.6111,22.5,21.3889,18.6111,14.4444,5.27778,5,5.83333,7.5,8.33333,9.16667,6.11111,3.33333,4.44444,4.44444,5.55556,4.72222,3.61111,3.88889,3.33333,2.5,5.55556,5.55556,4.72222,6.11111,4.44444,5.55556,3.61111,5,4.44444,5,5.83333,6.94444,9.72222,15.5556,10.5556,15,5.83333,4.16667,6.38889,13.3333,13.6111,13.6111,15,12.7778,13.8889,13.0556,14.1667,13.8889,12.7778,15.8333,14.4444,16.3889,16.1111,14.1667};
double standardaverage = 11.61;
void readroadtime() {
	memset(vcnt,0 , sizeof(vcnt));
	memset(icnt,0 , sizeof(icnt));
	memset(totcnt,0 , sizeof(totcnt));
	memset(speed,0 , sizeof(speed));

	for(int fileid = 0; fileid <= 5; fileid ++) {
		string filename = "../data/roadspeed/averagespeed" + to_string(fileid) +".txt";
		freopen(filename.c_str(), "r", stdin);
		for(int i = 0; i < en; i++) 
			for(int j = 0; j < 72; j++) {
				int tmpv, tmpi;
				scanf("%d %d ", &tmpv, &tmpi);
				vcnt[j][i] += tmpv;
				icnt[j][i] += tmpi;
				totcnt[i] += tmpi;
			}
	}

	for(int i = 0; i < en; i++) 
		for(int j = 0; j < 72; j++)
			if(icnt[j][i] != 0)
				speed[j][i] = vcnt[j][i] / icnt[j][i] / 3.6;

	for(int i = 0; i < en; i++) {
		double averagespeed = 0;
		int hasvalue = 0;
		if(totcnt[i] < 5){
			// Roads that are hardly taken
			for(int j = 0; j < 72; j++) 
				speed[j][i] = 10 / 3.6;
		}
		else{ 
			// Fill speed with average speed
			for(int j = 0; j < 72; j++){
				if(speed[j][i] != 0) hasvalue ++;
				averagespeed = averagespeed + speed[j][i];
			}
			averagespeed = averagespeed / hasvalue;
			for(int j = 0; j < 72; j++)
				if(speed[j][i] == 0)
					speed[j][i] = averagespeed / standardaverage * speedpattern[j];
		}
	}
	freopen("../data/roadspeed/averagespeed.txt", "w", stdout);
	for(int i = 0; i < en; i++) {
		for(int j = 0; j < 72; j++)
			printf("%.2lf ", speed[j][i]);
		printf("\n");
	}
}

void readroadtime2() {
	freopen("../data/roadspeed/averagespeed.txt", "r", stdin);
	for(int i = 0; i < en; i++) 
		for(int j = 0; j < 72; j++)
			scanf("%lf ", &speed[j][i]);
}

