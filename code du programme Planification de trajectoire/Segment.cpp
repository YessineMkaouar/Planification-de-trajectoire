#include "Segment.h"
#include <bits/stdc++.h>

Segment::Segment() // constructeur par defaut
{
    P1.setx(0);
    P1.sety(0);
    P2.setx(0);
    P2.sety(0);
}
Segment::Segment(Point A, Point B) // constructeur de la classe Segment à partir de deux points A et B
{
    P1.setx(A.getx());
    P1.sety(A.gety());
    P2.setx(B.getx());
    P2.sety(B.gety());
}
void Segment::setP1(Point A) // setter du point P1
{
    P1.setx(A.getx());
    P1.sety(A.gety());
}
void Segment::setP2(Point B) // setter du point P2
{
    P2.setx(B.getx());
    P2.sety(B.gety());
}
Point Segment::getP1() { return P1; } // getter de P1
Point Segment::getP2() { return P2; } // getter de P2

double Segment::getLongueur() { return P1.distance(P2); }

bool Segment::intersect(Segment s2) // test d'intersection entre deux segments
{
    float x1 = P2.getx() - P1.getx();                 // x1 est la difference entre les abscisses des deux points du premier segment
    float y1 = P2.gety() - P1.gety();                 // y1 est la difference entre les ordonnees des deux points du premier segment
    float x2 = s2.getP2().getx() - s2.getP1().getx(); // x2 est la difference entre les abscisses des deux points du deuxieme segment
    float y2 = s2.getP2().gety() - s2.getP1().gety(); // y2 est la difference entre les ordonnees des deux points du deuxieme segment
    double determinant = x1 * y2 - y1 * x2;           // calcul du determinant

    return (determinant != 0);
}

bool operator==(Segment S1, Segment S2) // retourne vrai si les deux segments sont egaux
{
    if (S1.getP1() == S2.getP1() && S2.getP2() == S1.getP2())
        return true;
    else
        return false;
}

bool operator!=(Segment S1, Segment S2) // retourne vrai si les deux segments sont differents
{
    if (S1.getP1() == S2.getP1() && S2.getP2() == S1.getP2())
        return false;
    else
        return true;
}
