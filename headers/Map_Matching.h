#ifndef MAP_MATCHING_H
#define MAP_MATCHING_H

#include "../headers/basic.h"
#include "../headers/point.h"

class tranode {
public:
	Point p;
	int ti, kong, v;
};

class RoadSpeedCount{
public:
	static int vcnt[72][300005];
	static int icnt[72][300005]; 
};

class HMM{
public:
	vector<roadpoint> z[20000];
	bool shandiao[20000];
	double rectA[20000][25][25];
	double rectB[20000][25];
	double alpha, beta;
	double zdis[20000];
	double xdis[20000][25][25];
	vector<double> alldata;

	int viterbipre[20000][25];
	int vans[20000];
	double f[20000][25];

	void makerectA(tranode* ridea, int n);
	double getprob(double dist);
	void makerectB(tranode* ridea, int n);
	void viterbi(int n);
	vector<Point> mapmatching(tranode* ridea, int n);

};

#endif