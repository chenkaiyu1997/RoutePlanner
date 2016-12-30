#include "../headers/ride.h"

void inputride(ride& A) {
	scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %lf %lf", &A.pickuptime,
	 &A.pickupposition.p.x, &A.pickupposition.p.y, &A.pickupposition.u,
	  &A.pickupposition.v, &A.endtime, &A.endposition.p.x,
	   &A.endposition.p.y, &A.endposition.u, &A.endposition.v,
	    &A.drivernum, &A.linestartnumber, &A.lineendnumber, &A.ridedis, &A.astardis);
}
void outputride(const ride& A) {
	printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %.3lf %.3lf\n", A.pickuptime,
	 A.pickupposition.p.x, A.pickupposition.p.y, A.pickupposition.u,
	  A.pickupposition.v, A.endtime, A.endposition.p.x,
	   A.endposition.p.y, A.endposition.u, A.endposition.v,
	    A.drivernum, A.linestartnumber, A.lineendnumber, A.ridedis, A.astardis);
}