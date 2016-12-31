#include "../headers/basic.h"
#include "../headers/point.h"
#include "../headers/edge.h"
#include "../headers/kdtree.h"
#include "../headers/astar.h"
#include "../headers/analyse.h"
#include "../headers/initroad.h"
#include "../headers/getprojection.h"
#include "../headers/Map_Matching.h"


int RoadSpeedCount::vcnt[73][400005];
int RoadSpeedCount::icnt[73][400005];

void HMM::makerectA(tranode * ridea, int n) {
	//Get zdis
	for(int i = 2; i <= n; i++) {
		zdis[i] = dis(ridea[i-1].p, ridea[i].p);
	}

	//Get xdis
	for(int i = 2; i <= n ; i++) {
		//if(i % 100 == 0)
		//	cerr<<i<<endl;
		int len1 = z[i-1].size(), len2 = z[i].size();
		for(int j = 0; j < len1; j++)
			for(int k = 0; k < len2; k ++) {
				if(z[i-1][j].p.x == z[i][k].p.x && z[i-1][j].p.y == z[i][k].p.y)
					xdis[i][k][j] = 0;
				else if(z[i-1][j].u == z[i][k].u || z[i-1][j].v == z[i][k].v){
					xdis[i][k][j] = dis(z[i-1][j].p, z[i][k].p);
				}
				else if(z[i-1][j].u == z[i][k].v || z[i-1][j].v == z[i][k].u){
					xdis[i][k][j] = dis(z[i-1][j].p, z[i][k].p);
				}
				else{
					Astar(z[i-1][j], z[i][k], xdis[i][k][j]);
				//	cerr<<xdis[i][k][j]<<endl;
				}
			}
	}

	//Get beta;
	// alldata.clear();
	// for(int i = 2; i <= n ; i++)
	// 	alldata.push_back(fabs(zdis[i] - xdis[i][0][0]));
	// int len = alldata.size();
	// nth_element(alldata.begin(), alldata.begin() + len/2, alldata.end());
	// beta = alldata[len/2] / log(2);
	// if(beta < 1e-8) beta = 0.1;
	// //beta = 10;
	// //getA
	// cerr<<"beta = " << beta;
	beta = 1;
	for(int i = 2; i <= n ; i++) {
		int len1 = z[i-1].size(), len2 = z[i].size();
		for(int j = 0; j < len1; j++)
			for(int k = 0; k < len2; k ++) {
				double tmp = fabs(zdis[i] - xdis[i][k][j]);
				rectA[i][k][j] = log( (1.0 / beta) * exp(-tmp / beta) );
			}
	}

}

double HMM::getprob(double dist) {
	double coa = 1.0 / sqrt(2 * PI) / alpha;
	double cob = dist / alpha;
	return coa * exp(-0.5 * cob * cob);
}

void HMM::makerectB(tranode* ridea, int n) {
	// alldata.clear();
	// //get alpha
	// for(int i = 1; i <= n; i++) {
	// 	int len = z[i].size();
	// 	if(len == 0)cerr<<"error"<<endl;
	// 	alldata.push_back(dis(z[i][0].p, ridea[i].p));
	// }

	// int len = alldata.size();
	// nth_element(alldata.begin(), alldata.begin() + len/2, alldata.end());
	// alpha = alldata[len/2] * 1.5;
	// //alpha = 100;	
	// cerr<<"alpha = " << alpha;
	alpha = 5;
	for(int i = 1; i <= n; i++) {
		int len = z[i].size();
		for(int j = 0; j < len; j++) 
			rectB[i][j] = log(getprob(dis(z[i][j].p, ridea[i].p)));
	}
}


void HMM::viterbi(int n) {
	for(int j = 0; j < (int)z[1].size(); j++)
		f[1][j] = rectB[1][j];
	for(int i = 2; i <= n ; i++) {
		int len1 = z[i].size(), len2 = z[i - 1].size();
		for(int j = 0; j < len1; j++){
			double maxvalue = 1e-200;
			for(int k = 0; k < len2; k ++) {
				double tmp = f[i-1][k] + rectA[i][j][k] + rectB[i][j];
				if(maxvalue < tmp) {
					maxvalue = tmp;
					viterbipre[i][j] = k;
				}
			}
			f[i][j] = maxvalue;
		}
	}
	double ans = -inf;
	int ansj = 0;
	for(int j = 0; j < (int)z[n].size(); j++)
		if(ans < f[n][j]){
			ans = f[n][j];
			ansj = j;
		}
	vans[n] = ansj;
	for(int i = n; i >= 2; i--) {
		vans[i-1] = viterbipre[i][vans[i]];
	}
}


vector<Point> HMM::mapmatching(tranode* ridea, int n) {
	//cerr << "in!" << endl;
	memset(shandiao, 0, sizeof(shandiao));
	vector<Point> ans;
	int newn = 0;
	for(int i = 1; i <= n; i++) {	
		//cerr << "innner i = " << i << endl;
		z[++newn] = getroadpoints(ridea[i].p);
		if(z[newn].size() == 0){
			shandiao[i] = true;
			newn--;
			continue;
		}	
		z[newn] = getknearest(20, z[newn], ridea[i].p);
		while(z[newn].size() > 0 && dis(z[newn][(int)z[newn].size() - 1].p, ridea[i].p) > 50)z[newn].pop_back();
		if(z[newn].size() == 0){
			shandiao[i] = true;
			newn--;
		}
	}
	//cerr<<newn<<" "<< n <<endl;
	if(newn <= 1)return ans;
	makerectA(ridea, newn);
	makerectB(ridea, newn);
	viterbi(newn);

	ans.clear();
	//ans.push_back(Point(0,0));
	int j = 0;
	for(int i = 1; i <= n; i++) {
		if(shandiao[i]);
			//ans.push_back(ridea[i].p);
		else{
			j++;
			//ans.push_back(z[j][vans[j]].p);
			int edgenumber = z[j][vans[j]].edgenumber;
			int dir = a[e[edgenumber].u].x < a[e[edgenumber].v].x;
			if(j == 1) 
				dir ^= z[j][vans[j]].p.x < z[j+1][vans[j+1]].p.x;
			else 
				dir ^= z[j-1][vans[j-1]].p.x < z[j][vans[j]].p.x;
			//if(dir > 1) cerr<<"error";
			RoadSpeedCount::icnt[ridea[i].ti / 1200][z[j][vans[j]].edgenumber ^ dir] ++;
			RoadSpeedCount::vcnt[ridea[i].ti / 1200][z[j][vans[j]].edgenumber ^ dir] += ridea[i].v;
		}
	}
	//cerr<<"mapmatchingdone"<<endl;
	return ans;
}
