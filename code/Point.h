#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream> //pour convertir un string en int
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
class Point
{
private:
    double x, y;
    int index;

public:
    Point();                                              // constructeur de la classe Point
    Point(double x, double y);                            // constructeur de la classe Point
    double getx() const;                                        // getter de l'abcisse
    double gety() const;                                        // getter de l'ordonn�e
    void setx(double x);                                  // setter de l'abcisse
    void sety(double y);                                  // setter de l'ordonn�e
    double distance(const Point &P) const;
    int get_index() const; // M�thode pour obtenir l'index
    void set_index(int idx); // M�thode pour d�finir l'index                     // distance entre deux points
    friend ostream &operator<<(std::ostream &, const Point &); // affichage d'un point
    friend bool operator==(Point, Point);                 // comparaison entre deux points
    friend bool operator!=(Point, Point);
    friend bool operator<(const Point &P1, const Point &P2);
};

#endif // POINT_H_INCLUDED


