#ifndef ARC_H_INCLUDED
#define ARC_H_INCLUDED

#include <iostream>
#include <cmath> // Pour les opérations mathématiques
#include "Segment.h"

class Arc : public Segment
{
private:
    double COUT; // cout d'un arc (évidemment sa norme 2)

public:
    Arc();
    Arc(Point P1, Point P2);
    double getCout();
    void afficher()const;
};

#endif // ARC_H_INCLUDED

