#include "Segment.h"
#include <bits/stdc++.h>

Segment::Segment() : P1(), P2() // constructeur par defaut
{
}

Segment::Segment(Point A, Point B) : P1(A), P2(B) // constructeur de la classe Segment à partir de deux points A et B
{
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
const Point &Segment::getP1() const // getter de P1
{
    return P1;
} 
const Point &Segment::getP2() const // getter de P2
{
    return P2;
}

double Segment::getLongueur() const
{
    return P1.distance(P2);
}

bool Segment::intersect(const Segment &s2) const // test d'intersection entre deux segments
{
    float x1 = P2.getx() - P1.getx();                 // x1 est la difference entre les abscisses des deux points du premier segment
    float y1 = P2.gety() - P1.gety();                 // y1 est la difference entre les ordonnees des deux points du premier segment
    float x2 = s2.getP2().getx() - s2.getP1().getx(); // x2 est la difference entre les abscisses des deux points du deuxieme segment
    float y2 = s2.getP2().gety() - s2.getP1().gety(); // y2 est la difference entre les ordonnees des deux points du deuxieme segment
    double determinant = x1 * y2 - y1 * x2;           // calcul du determinant

    return (determinant != 0);
}

bool operator==(const Segment &S1, const Segment &S2) // retourne vrai si les deux segments sont egaux
{
    if (S1.getP1() == S2.getP1() && S2.getP2() == S1.getP2())
        return true;
    else
        return false;
}

bool operator!=(const Segment &S1, const Segment &S2) // retourne vrai si les deux segments sont differents
{
    if (S1.getP1() == S2.getP1() && S2.getP2() == S1.getP2())
        return false;
    else
        return true;
}

ostream &operator<<(std::ostream &out, const Segment &S) // affichage d'un segment
{
    out << "Segment de points " << S.P1 << " et " << S.P2;
    return out;
}
