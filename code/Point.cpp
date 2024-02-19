#include "Point.h"
#include <bits/stdc++.h>
Point::Point() : x(0), y(0)
{
}
Point::Point(double x, double y) : x(x), y(y)
{
}
void Point::setx(double x) { this->x = x; }  // D�finit la valeur de la coordonn�e x du point.
void Point::sety(double y) { this->y = y; }  // D�finit la valeur de la coordonn�e y du point.
double Point::getx() const { return x; }         // Renvoie la valeur de la coordonn�e x du point.
double Point::gety() const { return y; }       // Renvoie la valeur de la coordonn�e y du point.
double Point::distance(const Point &P) const // Calcule la distance entre ce point et un autre point donn�.

{
    double dx = x - P.x;
    double dy = y - P.y;
    return sqrt(dx * dx + dy * dy);
}
int Point::get_index() const {
    return index;
}

void Point::set_index(int idx) {
    index = idx;
}

bool operator==(Point P1, Point P2) // V�rifie si deux points sont �gaux en comparant leurs coordonn�es.
{
    return (std::abs(P1.x - P2.x) < 0.01 && std::abs(P1.y - P2.y) < 0.01);
}

bool operator!=(Point P1, Point P2) // V�rifie si deux points sont diff�rents en comparant leurs coordonn�es.
{
    return !(P1 == P2);
}
bool operator<(const Point &P1, const Point &P2) {
    // Comparaison bas�e sur les coordonn�es x et y
    if (P1.x < P2.x)
        return true;
    if (P1.x > P2.x)
        return false;
    // Si les coordonn�es x sont �gales, comparez les coordonn�es y
    return P1.y < P2.y;
}


ostream &operator<<(ostream &out, const Point &P) // Surcharge de l'op�rateur de flux de sortie pour afficher les coordonn�es du point.
{
    out << "(" << P.x << "," << P.y << ")";
    return out;
}


