#ifndef OBSTACLEH
#define OBSTACLEH

#include <vector>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <math.h>
#include <iostream>
#include "Point.h"
#include "Segment.h"
#include "vecteur.h"
#include "Arc.h"
using namespace std;

class Obstacle

{
private:
    int nbs; // nombre de sommet de l'obstacle
    vector<Point> som; // ensemble des sommets de l'obstacle
    vector<Segment> Tab; // ensemble des aretes de l'obstacle

public :
    Obstacle();                 //constructeur de obstacle
    Obstacle(vector <Point>);   //constructeur de obstacle
    int get_nbs() const;        //nombre de sommets
    vector<Point> get_som() const;      //retourne la liste des sommets de l'obstacle
    vector<Segment> aretes(); // liste avec les aretes
    bool intersect(Arc AB); //Verifie si un arc coupe l'obtacle en au moins 2 points
    vector<Segment> ToutSegmentPossible(); // Génère une lise de tous les segment qu'on peut dessiner dans un obstacle
};
#endif
