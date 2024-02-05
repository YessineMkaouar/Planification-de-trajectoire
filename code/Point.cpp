#include "Point.h"
#include <bits/stdc++.h>
Point::Point() : x(0), y(0)
{
}
Point::Point(double x, double y) : x(x), y(y)
{
}
void Point::setx(double x) { this->x = x; }  // Définit la valeur de la coordonnée x du point.
void Point::sety(double y) { this->y = y; }  // Définit la valeur de la coordonnée y du point.
double Point::getx() const { return x; }         // Renvoie la valeur de la coordonnée x du point.
double Point::gety() const { return y; }       // Renvoie la valeur de la coordonnée y du point.
double Point::distance(const Point &P) const // Calcule la distance entre ce point et un autre point donné.
{
    double dx = x - P.x;
    double dy = y - P.y;
    return sqrt(dx * dx + dy * dy);
}

bool operator==(Point P1, Point P2) // Vérifie si deux points sont égaux en comparant leurs coordonnées.
{
    return (std::abs(P1.x - P2.x) < 0.01 && std::abs(P1.y - P2.y) < 0.01);
}

bool operator!=(Point P1, Point P2) // Vérifie si deux points sont différents en comparant leurs coordonnées.
{
    return !(P1 == P2);
}

ostream &operator<<(ostream &out, const Point &P) // Surcharge de l'opérateur de flux de sortie pour afficher les coordonnées du point.
{
    out << "(" << P.x << "," << P.y << ")";
    return out;
}
