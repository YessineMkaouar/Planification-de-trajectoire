#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include "Vecteur.h"
#include "Arc.h"
#include <bits/stdc++.h>
#include <iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
using namespace std;
class Graphe
{
private:
    vector <Arc> listeArc;           //contient tous les arc du graphe
    vector<Point> Sommets;          //contient tous les sommets du graphe
public:
    Graphe();                       //constructeur du graphe
    Graphe(vector <Point>);         //constructeur du graphe
    vector<Arc> getArcs();          //getter de la liste des arcs
    vector<Point> getSommets();     //getter de la liste des getSommets
    void afficher();                //affichage de la graphe
    int getN();                     //getter du nombre de sommet
    std::vector<int> getNeighbors(int sommet) const;
};


#endif // GRAPHE_H_INCLUDED
