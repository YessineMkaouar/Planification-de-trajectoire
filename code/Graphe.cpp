#include "Graphe.h"
#include <iostream>

Graphe::Graphe() {
    vector <Arc> V;
    vector<Point> S;
    listeArc = V;
    Sommets = S;
}

Graphe::Graphe(vector<Point> V) {
    Sommets = V;
    int size = V.size();
    int i;
    for (i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            listeArc.push_back(Arc(V[i], V[j]));
        }
    }
}

void Graphe::afficher() {
    cout << "Le graphe est donne par" << endl;
    for (int i = 0; i < listeArc.size(); i++) {
        listeArc[i].afficher();
    }
}

vector<Arc> Graphe::getArcs() {
    return listeArc;
}

vector<Point> Graphe::getSommets() {
    return Sommets;
}

int Graphe::getN() {
    set<pair<double, double>> Ens;
    for (int i = 0; i < listeArc.size(); i++) {
        pair<double, double> Pair1 = make_pair(listeArc[i].getP1().getx(), listeArc[i].getP1().gety());
        pair<double, double> Pair2 = make_pair(listeArc[i].getP2().getx(), listeArc[i].getP2().gety());
        Ens.insert(Pair1);
        Ens.insert(Pair2);
    }
    return Ens.size();}
std::vector<Point> Graphe::getNeighbors(Point sommet) const {
    std::vector<Point> neighbors;
    for (const Arc &arc : listeArc) {
        if (arc.getP1().getx() == sommet.getx()||arc.getP1().gety() == sommet.gety()) neighbors.push_back(arc.getP2());
        else if (arc.getP2().getx() == sommet.getx()||arc.getP2().gety() == sommet.gety()) neighbors.push_back(arc.getP1());
    }
    neighbors.erase(neighbors.begin());
    return neighbors;
}


