#include "../headers/basic.h"
#include "../headers/point.h"

Point::Point(){}
Point::Point(int _x, int _y){
	x = _x;
	y = _y;
	id = 0;
}
void Point::operator*= (double tmp) {
	x *= tmp;
	y *= tmp;
}
void Point::operator/= (double tmp) {
	x /= tmp;
	y /= tmp;
}

bool operator< (const Point& A, const Point& B) {
	if(globald)
		return A.y < B.y;
	return A.x < B.x;
}
Point operator- (const Point& A, const Point& B) {
	return Point(A.x - B.x, A.y - B.y);
}
Point operator+ (const Point& A, const Point& B) {
	return Point(A.x + B.x, A.y + B.y);
}
double dis(const Point& A,const Point& B) {
	double tmp1 = 1.0 * (A.x - B.x) / 1e5 * cos(PI * (A.y + B.y) / 1e5 / 360) * CH;
	tmp1 *= tmp1;
	double tmp2 = 1.0 * (A.y - B.y) / 1e5 * CH;
	tmp2 *= tmp2;
	return sqrt(tmp1 + tmp2);
}
double pseudodis(const Point& A, const Point& B) {
	return sqrt(1.0 * (A.x - B.x) * (A.x - B.x) + 1.0 * (A.y - B.y) * (A.y - B.y)); 
}
Point min(const Point& A, const Point& B) {
	return Point(min(A.x, B.x), min(A.y, B.y));
}
Point max(const Point& A, const Point& B) {
	return Point(max(A.x, B.x), max(A.y, B.y));
}
double dot(const Point& A, const Point& B) {
	return 1.0 * A.x * B.x + 1.0 * A.y * B.y;
}

//Global Variables
int globald = 0;
const double inf = 1e100;
const double PI = 3.1415926535897932;
const double CH = 6371000.0 * 2 * PI / 360;
Point a[N];

