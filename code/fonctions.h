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
pair<double, vector<Point>> dijkstra(Graphe& graph, Point source, Point destination,Obstacle& obs) ;
void afficherChemin(const vector<Point> &chemin);
double distanceWithObstacles(const Point& p1, const Point& p2, const vector<Obstacle>& obstacles) ;


#endif // FONCTIONS_H_INCLUDED