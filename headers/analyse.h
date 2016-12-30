#ifndef _ANALYSE_H
#define _ANALYSE_H

//#include "../headers/basic.h"

extern double money[5][6000];
extern int cnt[5][6000];
extern double driverdis[5][6000];
extern int ondelivertime[5][6000];
extern int ongoingtime[5][6000];
extern int kongtime[5][6000];
double getmoney(double dist);

double getoil(double dist);

void initanalyse();
void outputanalyse(int tc, int i);

#endif