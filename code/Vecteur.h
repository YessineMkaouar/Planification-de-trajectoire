#ifndef VECTEUR_H_INCLUDED
#define VECTEUR_H_INCLUDED
#include "Segment.h"

class Vecteur : public Segment
{
private:
    double X; // 1ere composante du vecteur
    double Y; // 2eme composante du vecteur
public:
    Vecteur();                                       // constructeur d'un vecteur nul
    Vecteur(Point P1, Point P2);                     // constructeur d'un vecteur � partir de deux points
    Vecteur(double X, double Y);                     // constructeur d'un vecteur � partir de deux coordonn�es
    double getX() const;                             // getter de la 1ere composante du vecteur
    double getY() const;                             // getter de la 1ere composante du vecteur
    bool estNul() const;                             // Retourne 1 si le vecteur est nul
    double norme() const;                            // Retourne la norme du vecteur
    double produitScalaire(const Vecteur &Y) const;  // Retourne le produit scalaire du vecteur avec un autre V
    double angle(const Vecteur &V) const;            // Retourne l'angle que fait le vecteur avec un autre V
    bool estAigu(const Vecteur &V) const;                  // Retourne 1 si l'angle est Aigu, 0 sinon
    bool estPerpendiculaire(const Vecteur &V) const; // Retourne 1 si le vecteur est perpendiculaire � un autre V
    double pd_vect(const Vecteur &V) const;          // Retourne le produit vectoriel du vecteur avec un autre V
};

#endif // VECTEUR_H_INCLUDED


