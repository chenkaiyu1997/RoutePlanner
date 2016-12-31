#include "../headers/edge.h"
#include "../headers/roadtime.h"

double speed[73][400005];
int vcnt[73][400005];
int icnt[73][400005];
int totcnt[400005];
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
	int badcount = 0;
	for(int i = 0; i < en; i++) {
		double averagespeed = 0;
		int hasvalue = 0;
		if(totcnt[i] < 5){
			badcount ++;
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
					speed[j][i] = averagespeed;
		}
	}
	cerr<<"bad road" << badcount<<endl;
}

