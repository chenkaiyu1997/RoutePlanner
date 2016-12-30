#ifndef RIDE_H
#define RIDE_H

#include "../headers/point.h"

class ride {
public:
	int pickuptime;
	int endtime;
	roadpoint pickupposition;
	roadpoint endposition;
	int drivernum;
	int linestartnumber;
	int lineendnumber;
	double ridedis;
	double astardis;
};

void inputride(ride& A);
void outputride(const ride& A);


#endif