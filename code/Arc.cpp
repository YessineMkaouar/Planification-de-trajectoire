#include "Arc.h"
#include <iostream>
#include <cmath>

Arc::Arc() : COUT(0)
{
    // Les membres P1 et P2 sont déja initialisés avec leur constructeur par défaut
}

Arc::Arc(Point A, Point B) : COUT(sqrt((A.getx() - B.getx()) * (A.getx() - B.getx()) + (A.gety() - B.gety()) * (A.gety() - B.gety())))
{
    P1.setx(A.getx());
    P1.sety(A.gety());
    P2.setx(B.getx());
    P2.sety(B.gety());
}

double Arc::getCout()
{
    return COUT;
}

void Arc::afficher() const
{
    std::cout << "Arc oriente de (" << P1.getx() << "," << P1.gety() <<
        ") vers (" << P2.getx() << "," << P2.gety() <<
        "). Son cout est " << COUT << std::endl;
}
