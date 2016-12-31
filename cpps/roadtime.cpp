#include "../headers/edge.h"
#include "../headers/roadtime.h"

double speed[73][400005];
void readroadtime() {
	freopen("../data/roadspeed/averagespeed.txt", "r", stdin);
	for(int i = 0; i < en; i++) 
		for(int j = 0; j < 72; j++) 
			scanf("%lf %*d ", &speed[j][i]);
}

