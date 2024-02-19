#ifndef SEGMENT_H_INCLUDED
#define SEGMENT_H_INCLUDED

#include "Point.h"
#include <iostream>

class Segment
{
protected:
    Point P1, P2; // P1 et P2 sont les deux points qui d�finissent le segment
public:
    Segment();                                  // constructeur par defaut
    Segment(Point P1, Point P2);                // constructeur de la classe Segment
    const Point &getP1() const;                 // getter de P1
    const Point &getP2() const;                 // getter de P2
    void setP1(Point P1);                       // setter de P1
    void setP2(Point P2);                       // setter de P2
    double getLongueur() const;                 // calcul de la longueur du segment
    bool intersect(const Segment &other) const; // test d'intersection entre deux segments
    friend bool operator==(const Segment &s1, const Segment &s2); // comparaison entre deux segments
    friend bool operator!=(const Segment &s1, const Segment &s2);
    friend std::ostream &operator<<(std::ostream &out, const Segment &s); // affichage d'un segment
};

#endif // SEGMENT_H_INCLUDED


