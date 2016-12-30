#ifndef _GETPROJECTION_H
#define _GETPROJECTION_H

// #include "../headers/basic.h"
// #include "../headers/point.h"
// #include "../headers/edge.h"


roadpoint getprojection(int u, const Point& A, int v, const Point& B, const Point& C);

vector<roadpoint> getroadpoints(const Point& p);

vector<roadpoint> getknearest(int k, const vector<roadpoint>& w, const Point& p);

#endif