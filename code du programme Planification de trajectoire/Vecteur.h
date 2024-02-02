#ifndef VECTEUR_H_INCLUDED
#define VECTEUR_H_INCLUDED
#include "Segment.h"

class Vecteur : public Segment
{
private:
    double X;                      //1ere composante du vecteur
    double Y;                     //2eme composante du vecteur
public:
    Vecteur();                      //constructeur d'un vecteur nul
    Vecteur(Point P1, Point P2);    //constructeur d'un vecteur à partir de deux points
    Vecteur(double X,double Y);     //constructeur d'un vecteur à partir de deux coordonnées
    double getX();                  //getter de la 1ere composante du vecteur
    double getY();                  //getter de la 1ere composante du vecteur
    bool estNul();  //Retourne 1 si le vecteur est nul
    double norme(); //Retourne la norme du vecteur
    double produitScalaire(Vecteur &Y); //Retourne le produit scalaire du vecteur avec un autre V
    double angle(Vecteur & V); //Retourne l'angle que fait le vecteur avec un autre V
    bool estAigu(Vecteur & V); //Retourne 1 si l'angle est Aigu, 0 sinon
    bool estPerpendiculaire(Vecteur & V); //Retourne 1 si le vecteur est perpendiculaire à un autre V
};


#endif // VECTEUR_H_INCLUDED
