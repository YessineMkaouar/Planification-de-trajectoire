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
    int nbs;             // nombre de sommet de l'obstacle
    vector<Point> som;   // vecteur contenant les sommets de l'obstacle
    vector<Segment> Tab; // vecteur contenant l'ensemble des aretes (segments) de l'obstacle

public:
    Obstacle();                            // constructeur de obstacle par defaut
    Obstacle(vector<Point>);               // constructeur de obstacle à partir d'une liste de points
    int get_nbs() const;                   // retourne le nombre de sommets de l'obstacle
    vector<Point> get_som() const;         // retourne la liste des sommets de l'obstacle
    vector<Segment> aretes();              // liste avec les aretes
    bool intersect(Arc AB);                // Verifie si un arc coupe l'obtacle en au moins 2 points
    vector<Segment> ToutSegmentPossible(); // Genere une lise de tous les segment qu'on peut dessiner dans un obstacle
};
#endif
