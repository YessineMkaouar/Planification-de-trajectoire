#include "Vecteur.h"
#include <bits/stdc++.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define M_PI            3.14159265358979323846  /* pi */

Vecteur::Vecteur()   // constructeur d'un vecteur par défaut (vecteur nul)
{
    P1.setx(0);
    P1.sety(0);
    P2.setx(0);
    P2.sety(0);
    X=0;
    Y=0;
}
Vecteur::Vecteur(Point A, Point B)  // constructeur d'un vecteur à partir de deux points
{
    P1.setx(A.getx());
    P1.sety(A.gety());
    P2.setx(B.getx());
    P2.sety(B.gety());
    X=P1.getx()-P2.getx();
    Y=P1.gety()-P2.gety();
}
Vecteur::Vecteur(double XX, double YY) 
{
    P1.setx(XX);
    P1.sety(0);
    P2.setx(0);
    P2.sety(YY);
    X=XX;
    Y=YY;
}
double Vecteur::getX(){return X;}
double Vecteur::getY(){return Y;}
bool Vecteur::estNul()
{
    return (X*X+Y*Y==0);
}
double Vecteur::norme(){return (sqrt(X*X+Y*Y));}
double Vecteur::produitScalaire(Vecteur &V)
{
    return (X*V.X+Y*V.Y);
}
double Vecteur::angle(Vecteur &V)
{
    double ps=X*V.X+Y*V.Y;
    double n1=sqrt(X*X+Y*Y);
    double n2=sqrt(V.X*V.X+V.Y*V.Y);

    return acos(ps/(n1*n2));
}

bool Vecteur::estAigu(Vecteur & V)
{
    double ps=X*V.X+Y*V.Y;
    double n1=sqrt(X*X+Y*Y);
    double n2=sqrt(V.X*V.X+V.Y*V.Y);
    double angle=acos(ps/(n1*n2));
    return (abs(angle)<=M_PI/2);
}

bool Vecteur::estPerpendiculaire(Vecteur & V)
{
    return (X*V.X+Y*V.Y==0);
}
