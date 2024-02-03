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

public:
    Point();                                              // constructeur de la classe Point
    Point(double x, double y);                            // constructeur de la classe Point
    double getx();                                        // getter de l'abcisse
    double gety();                                        // getter de l'ordonnée
    void setx(double x);                                  // setter de l'abcisse
    void sety(double y);                                  // setter de l'ordonnée
    double distance(const Point &P);                      // distance entre deux points
    friend ostream &operator<<(ostream &, const Point &); // affichage d'un point
    friend bool operator==(Point, Point);                 // comparaison entre deux points
    friend bool operator!=(Point, Point);
};

#endif // POINT_H_INCLUDED
