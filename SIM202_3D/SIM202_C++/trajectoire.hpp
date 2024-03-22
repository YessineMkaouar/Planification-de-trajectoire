#ifndef TRAJECTOIRE_HPP_INCLUDED
#define TRAJECTOIRE_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include "algorithm"
#include "limits"
#include <fstream>
#include "string"
#include <sstream>
#include "time.h"
#include "chrono" //pour l'estimation du temps de calcul
#include "bits/stdc++.h" //pour l'estimation du temps de calcul

using namespace std;

// les classes :
// ------------------------------------------------------------------------------------------------
class sommet{
public:
    long double Sx,Sy; //coordonnées
    int idx; // indice du layer 0 <= idx < n_rot
    int sens; // sens de rotation (à utiliser dans le graphe uniquement)

    sommet(const long double& x=0,const long double& y=0,const int& i=0, const int& sens_=1): Sx(x),Sy(y),idx(i),sens(sens_) {};  //constructeur de classe sommet
    sommet& operator = (const sommet& S); //opérateur d'affectation
    bool operator == (const sommet &S) const; //operator de comparaison =
};
ostream& operator << (ostream& out, const sommet& S);//operator de flux pour la classe sommet
long double produit_scalaire(const sommet& A, const sommet& B);//produit scalaire
long double determinant(const sommet& A, const sommet& B); //determinant
sommet operator + (const sommet& S1,const sommet& S2); //opérateur d'addition
sommet operator - (const sommet& S1,const sommet& S2); //opérateur de différence
sommet operator * (const sommet& S,const long double& a); //operateur de multiplication
sommet operator / (const sommet& S,const long double& a); //operateur de division

class segment{
public:
    sommet deb;
    sommet fin;

    segment(const sommet& A=sommet(), const sommet& B=sommet()); //constructeur de classe segment
    long double longueur() const; //longueur de segment
    sommet normal()const; //normale au segment
    bool intersects_segment(const segment& seg_obs)const; //verifie l'intersection avec un segment d'un obstacle
};
ostream& operator << (ostream& out, const segment& seg);//operator de flux pour la classe segment

class obstacle {
public:
    vector<sommet> sommets;
    vector<sommet> normales;

    obstacle(const vector<sommet>& _sommets);//constructeur de classe obstacle
    vector<int> position(const segment& seg) const;
    bool intersect (const segment& seg)const;//detection d'intersection entre un segment et l'obstacle
};
ostream& operator << (ostream& out, const vector<sommet>& sommets);//operator de flux out pour les objets
istream& operator >> (istream& in, vector<sommet>& sommets);//operator de flux in pour les objets

class arc{
public:
    sommet deb;
    sommet fin;
    long double longueur;

    arc(sommet A, sommet B);//constructeur de classe arc
};
ostream& operator << (ostream& out,const arc& arc_);//operator de flux pour la classe arc

class graphe{
public:
    vector<sommet> noeuds;
    vector<arc> arcs;

    graphe(const vector<vector<obstacle>>& layers_obs={}, const sommet& depart=sommet(), const sommet& arrivee=sommet());//constructeur de classe graphe
    void ajouter_noeud(const sommet& N); //ajout d'un noeud au graphe
    void ajouter_arc(const arc& A); //ajout d'un arc au graphe
    int voisins(sommet A, sommet B) const; //retourne true ssi A et B sont voisins
};
ostream& operator << (ostream& out,const graphe& graphe_);//operator de flux pour la classe graphe
// ----------------------------------------------------------------------------------------------//

// les fonctions :
// ------------------------------------------------------------------------------------------------
bool sont_alignes(const sommet& A, const sommet& B, const sommet& C);
    // vérifie que 3 points sont alignés

bool non_convexes(const segment& seg_prec,const segment& seg_suiv);
    // vérifie que les deux segments forment une partie non convexe

vector<sommet> to_convex(const vector<sommet>& sommets);
    // transforme un objet quelconque en un objet convexe

obstacle padding(const vector<sommet>& objet, const obstacle& obs);
    // fonction de padding

vector<obstacle> padding_3D(const vector<sommet>& objet, const obstacle& obs);
    // fonction de padding 3D

int trouverIdxPtProche(const vector<sommet>& obj, const sommet& N_i, const sommet& S_i );
    // cherche l'indice du sommet de obj le plus proche du segment passant par S_i et ayant pour normale extérieure N_i

vector<sommet> Dijkstra(const graphe &G, const sommet &start, const sommet &end);
    // implementation de l'algorithme de Dijkstra

int find_key(const map<int,sommet>& _map,const sommet& val);
    // trouve l'indice du sommet 'val' dans '_map'

vector<sommet> rotation(const vector<sommet>& obj, const int& i);
    // faire la rotation de obj d'un angle 360*i/n_rot
// ----------------------------------------------------------------------------------------------//

// les paramètres du code (variables globales) :
// ------------------------------------------------------------------------------------------------
extern int n_rot, z_obs, test_affich;
extern long double cout_tour;
extern sommet depart, arrivee;
extern string Exemple;
// ----------------------------------------------------------------------------------------------//

#endif // TRAJECTOIRE_HPP_INCLUDED
