#ifndef _POINT_H
#define _POINT_H

#include "../headers/basic.h"

class Point{
public:
	int x, y;
	int id;
	Point();
	Point(int _x, int _y);
	void operator*= (double tmp);
	void operator/= (double tmp);
	friend bool operator< (const Point& A, const Point& B);
	friend Point operator- (const Point& A, const Point& B);
	friend Point operator+ (const Point& A, const Point& B);
	friend double dis(const Point& A,const Point& B);
	friend double pseudodis(const Point& A, const Point& B);
	friend Point min(const Point& A, const Point& B);
	friend Point max(const Point& A, const Point& B);
	friend double dot(const Point& A, const Point& B);
};

class roadpoint{
public:
	Point p;
	int u, v;
};


extern int globald;
extern const double inf;
extern const double PI;
extern const double CH;
extern Point a[N];

#endif