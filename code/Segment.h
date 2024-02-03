#ifndef SEGMENT_H_INCLUDED
#define SEGMENT_H_INCLUDED

#include "Point.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;
class Segment
{
protected:
    Point P1, P2; // P1 et P2 sont les deux points qui définissent le segment
public:
    Segment();                                // constructeur par defaut
    Segment(Point P1, Point P2);              // constructeur de la classe Segment
    Point getP1();                            // getter de P1
    Point getP2();                            // getter de P2
    void setP1(Point P1);                     // setter de P1
    void setP2(Point P2);                     // setter de P2
    double getLongueur();                     // calcul de la longueur du segment
    bool intersect(Segment);                  // test d'intersection entre deux segments
    friend bool operator==(Segment, Segment); // comparaison entre deux segments
    friend bool operator!=(Segment, Segment);
    friend ostream &operator<<(ostream &, const Segment &); // affichage d'un segment
};
#endif // SEGMENT_H_INCLUDED
