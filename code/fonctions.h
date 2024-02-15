#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include <iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include <cmath>
#include <math.h>
#include <string>
#include <algorithm>
#include "Segment.h"
#include "Obstacle.h"
#include "Graphe.h"

bool testin(Segment S1, Point s);
double vectcos(Segment s1, Segment s2);
Segment inverse(Segment S);
Point determinIntersect(Segment S1, Segment S2);
bool upgradedintersection(Segment S1, Segment S2);
bool seginlist(Segment S, std::vector<Segment> L);
bool traverse_Cas_Convexe(Obstacle Obs, Segment S);
bool traverse_optimisant_cas_non_Convexe(Obstacle Obs, Segment S);
bool traverse(Obstacle Obs, Segment S);
bool relier(Obstacle ob, Segment S);
vector<Point> Dijkstra(Graphe &G, Point &P, Point &Q, Obstacle &obs);


#endif // FONCTIONS_H_INCLUDED
