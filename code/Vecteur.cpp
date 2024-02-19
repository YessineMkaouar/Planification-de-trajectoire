#include "Vecteur.h"
#include <bits/stdc++.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define M_PI 3.14159265358979323846 /* pi */

Vecteur::Vecteur() : X(0), Y(0) // constructeur d'un vecteur par d�faut (vecteur nul)
{
}
Vecteur::Vecteur(Point A, Point B) : X(A.getx() - B.getx()), Y(A.gety() - B.gety()) // constructeur d'un vecteur � partir de deux points
{
    P1.setx(A.getx());
    P1.sety(A.gety());
    P2.setx(B.getx());
    P2.sety(B.gety());
}
Vecteur::Vecteur(double XX, double YY) : X(XX), Y(YY) // constructeur d'un vecteur � partir de deux coordonn�es
{
    P1.setx(XX);
    P1.sety(0);
    P2.setx(0);
    P2.sety(YY);
}
double Vecteur::getX() const { return X; } // getter de la 1ere composante du vecteur
double Vecteur::getY() const { return Y; } // getter de la 2eme composante du vecteur
bool Vecteur::estNul() const              // Retourne 1 si le vecteur est null
{
    return (X * X + Y * Y == 0);
}
double Vecteur::norme() const { return (sqrt(X * X + Y * Y)); } // Retourne la norme du vecteur

double Vecteur::produitScalaire(const Vecteur &V) const // Retourne le produit scalaire d'un vecteur avec un autre vecteur V
{
    return (X * V.X + Y * V.Y);
}
double Vecteur::angle(const Vecteur &V) const // Retourne l'angle que fait le vecteur avec un autre vecteur V
{
    double ps = X * V.X + Y * V.Y;
    double n1 = sqrt(X * X + Y * Y);
    double n2 = sqrt(V.X * V.X + V.Y * V.Y);

    return acos(ps / (n1 * n2));
}

bool Vecteur::estAigu(const Vecteur &V) const // Retourne 1 si l'angle est Aigu, 0 sinon
{
    double ps = X * V.X + Y * V.Y;
    double n1 = sqrt(X * X + Y * Y);
    double n2 = sqrt(V.X * V.X + V.Y * V.Y);
    double angle = acos(ps / (n1 * n2));
    return (abs(angle) <= M_PI / 2);
}

bool Vecteur::estPerpendiculaire(const Vecteur &V) const // Retourne 1 si le vecteur est perpendiculaire � un autre vecteur V
{
    return (X * V.X + Y * V.Y == 0);
}

double Vecteur::pd_vect(const Vecteur &V) const // Retourne le produit vectoriel d'un vecteur avec un autre vecteur V
{
    return (X * V.Y - Y * V.X);
}

