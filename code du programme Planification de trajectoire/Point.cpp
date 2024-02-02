#include "Point.h"
#include <bits/stdc++.h>
Point::Point() : x(0), y(0)
{
}
Point::Point(double x, double y) : x(x), y(y)
{
}
void Point::setx(double x) { this->x = x; } // Définit la valeur de la coordonnée x du point.
void Point::sety(double y) { this->y = y; } // Définit la valeur de la coordonnée y du point.
double Point::getx() { return x; }          // Renvoie la valeur de la coordonnée x du point.
double Point::gety() { return y; }          // Renvoie la valeur de la coordonnée y du point.
double Point::distance(const Point &P)      // Calcule la distance entre ce point et un autre point donné.
{
    double dx, dy;
    dx = x - P.x;
    dy = y - P.y;
    return sqrt(dx * dx + dy * dy);
}

bool operator==(Point P1, Point P2) // Vérifie si deux points sont égaux en comparant leurs coordonnées.
{
    if (abs(P1.x - P2.x) < 0.01 && abs(P1.y - P2.y) < 0.01)
        return true;
    else
        return false;
}

bool operator!=(Point P1, Point P2) // Vérifie si deux points sont différents en comparant leurs coordonnées.
{
    if (abs(P1.x - P2.x) < 0.1 && abs(P1.y - P2.y) < 0.1)
        return false;
    else
        return true;
}

ostream &operator<<(ostream &out, const Point &P) // Surcharge de l'opérateur de flux de sortie pour afficher les coordonnées du point.
{
    out << "(" << P.x << "," << P.y << ")";
    return out;
}
