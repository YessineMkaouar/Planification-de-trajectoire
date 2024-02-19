#include "fonctions.h"
#include "Graphe.h"
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <string>
using namespace std;
const double INFINIE = 9999;
bool testin(Segment S1, Point s)
{
    double EPSILON = 0.01;
    Vecteur V1(S1.getP1(), S1.getP2());
    Vecteur V2(S1.getP1(), s);
    Vecteur V3(S1.getP2(), s);
    double xa = S1.getP1().getx();
    double ya = S1.getP1().gety();
    double xb = S1.getP2().getx();
    double yb = S1.getP2().gety();
    double xc = s.getx();
    double yc = s.gety();
    bool test1 = ((xc - xa) * (yb - ya) - (yc - ya) * (xb - xa) < EPSILON);

    bool test2 = ((abs(xc - xa) - abs(xb - xa)) < EPSILON);
    bool test3 = ((xc - xa) * (xb - xa) >= 0);
    bool test4 = ((abs(yc - ya) - abs(yb - ya)) < EPSILON);
    bool test5 = ((yc - ya) * (yb - ya) >= 0);
    bool test = (((test1 && test2) && (test3 && test4)) && test5);

    return (test || s == S1.getP1()) || s == S1.getP2();
}

///////////////////////////////////////////////////////////////////////// Fonction qui retourne l'angle entre deux segments
double vectcos(Segment s1, Segment s2)
{
    Vecteur V1(s1.getP1(), s1.getP2());
    Vecteur V2(s2.getP1(), s2.getP2());
    return cos(V1.angle(V2));
}

/////////////////////////////////////////////////////////// Fonction qui retourne L'inverse d'un segment
Segment inverse(Segment S)
{
    Segment aux(S.getP2(), S.getP1());
    return aux;
}

///////////////////////////////////////////////////////// Fonction qui determine le point d'intersection entre deux segments
Point determinIntersect(Segment S1, Segment S2)
{
    const double EPSILON = 0.01;

    struct ppoint
    {
        double x, y;
        ppoint(double _x, double _y) : x(_x), y(_y) {}
    };
    struct vvecteur
    {
        double x, y;
        ppoint a, b;
        vvecteur(ppoint _a, ppoint _b) : a(_a), b(_b)
        {
            x = b.x - a.x;
            y = b.y - a.y;
        }
        double vecto(vvecteur autre)
        {
            return (x * autre.y - y * autre.x);
        }
        double norme()
        {
            return sqrt(x * x + y * y);
        }
    };

    double x1, y1, x2, y2;
    x1 = S1.getP1().getx();
    y1 = S1.getP1().gety();
    x2 = S1.getP2().getx();
    y2 = S1.getP2().gety();
    ppoint a1(x1, y1);
    ppoint a2(x2, y2);
    vvecteur A(a1, a2);

    double xx1, yy1, xx2, yy2;
    xx1 = S2.getP1().getx();
    yy1 = S2.getP1().gety();
    xx2 = S2.getP2().getx();
    yy2 = S2.getP2().gety();
    ppoint b1(xx1, yy1);
    ppoint b2(xx2, yy2);
    vvecteur B(b1, b2);
    double resX, resY;

    double a = (double)A.vecto(vvecteur(a1, b1)) / A.norme();
    double b = (double)A.vecto(vvecteur(a1, b2)) / A.norme();
    double nouveauB = B.norme() + (B.norme() * b) / (a - b);
    double vraiRapport = nouveauB / B.norme();
    resX = (double)b1.x + (double)B.x * vraiRapport;
    resY = (double)b1.y + (double)B.y * vraiRapport;
    Point P(resX, resY);
    return P;
}

/////////////////////////////////////////////////////////// Fonction qui teste si deux segment s'intersectent
bool upgradedintersection(Segment S1, Segment S2)
{
    Point s = determinIntersect(S1, S2);
    return (testin(S1, s)) && (testin(S2, s));
}
//////////////////////////////////////////////////////////// Fonction qui retourne si un segment est dans une liste de segments donn�es
bool seginlist(Segment S, std::vector<Segment> L)
{
    for (int i = 0; i < L.size(); i++)
    {
        if ((S == L[i]) || (inverse(S) == L[i]))
            return true;
    }
    return false;
}
//////////////////////////////////////////////////////////// Fonction qui retourne si un sommet est dans une listes de sommets données
bool sinlistsom(Point s, std::vector<Point> L)
{
    for (int i = 0; i < L.size(); i++)
    {
        if (s == L[i])
            return true;
    }
    return false;
}
/////////////////////////////////////////////////////////// Fonction qui verifie si un segment traverse un obstacle Dans le cas convexe (Parfois non convexe)
bool traverse_Cas_Convexe(Obstacle Obs, Segment S)
{
    int res = 0;
    set<pair<double, double>> V;
    for (int i = 0; i < Obs.aretes().size(); i++)
    {
        if (upgradedintersection(Obs.aretes()[i], S))
        {
            pair<double, double> P;
            P = make_pair(determinIntersect(Obs.aretes()[i], S).getx(), determinIntersect(Obs.aretes()[i], S).gety());
            V.insert(P);
        }
    }
    return (V.size() >= 2);
}

/////////////////////////////////////////////////////   Fonction qui verifie si un segment traverse un obstacle Dans le cas non convexe
bool traverse_optimisant_cas_non_Convexe(Obstacle Obs, Segment S)
{
    for (int i = 0; i < Obs.aretes().size(); i++)
    {
        Segment Seg = Obs.aretes()[i];
        if (upgradedintersection(Seg, S))
        {
            Point P = determinIntersect(Seg, S);
            if (!sinlistsom(P, Obs.get_som()))
                return true;
        }
    }
    return false;
}

///////////////////////////////////////////////////// Fonction qui verifie si un segment traverse un obstacle
bool traverse(Obstacle Obs, Segment S)
{
    return traverse_optimisant_cas_non_Convexe(Obs, S) || traverse_Cas_Convexe(Obs, S);
}
//////////////////////////////////////////////////////////// Fonction qui verifie si un segment dans un obstacle peut �tre relier ou pas
bool relier(Obstacle ob, Segment S)
{
    bool test1 = sinlistsom(S.getP1(), ob.get_som());
    bool test2 = sinlistsom(S.getP2(), ob.get_som());
    test1 = test1 && test2;
    if (test1 == false)
        return false;

    test2 = seginlist(S, ob.aretes()) || seginlist(inverse(S), ob.aretes());
    vector<Segment> L = ob.ToutSegmentPossible();
    for (int i = 0; i < L.size(); i++)
    {
        if (upgradedintersection(S, L[i]))
        {
            Point P = determinIntersect(S, L[i]);
            if (sinlistsom(P, ob.get_som()) == false)
                return false;
        }
    }
    return true;
}

////////////////////////////////////////////////////////////// Cette fonction retourne un fichier txt qui contient les coordonn�es des points du graphe
void dessinerGraphe(Graphe G, ofstream &flux)
{

    flux << "x = [";
    for (int i = 0; i < G.getN() - 1; i++)
    {
        flux << G.getSommets()[i].getx() << " ";
    }
    int i = G.getN() - 1;
    flux << G.getSommets()[i].getx() << "];" << endl;
    flux << "y = [";
    for (int i = 0; i < G.getN() - 1; i++)
    {
        flux << G.getSommets()[i].gety() << " ";
    }
    flux << G.getSommets()[i].gety() << "];" << endl;
    flux << "plot(x,y,'.k','MarkerSize', 30)" << endl;
}
/////////////////////////////////////////////////////////////////// Cette fonction retourneun fichier txt qui contient les coordonn� des points d'un obstacle

void dessinerObstacles(vector<Obstacle> O, ofstream &fluxx)
{

    for (int i = 0; i < O.size(); i++)
    {
        Obstacle Obs(O[i].get_som());
        fluxx << "x_obs";
        fluxx << i;
        fluxx << "=[";

        for (int j = 0; j < Obs.get_nbs() - 1; j++)
        {
            fluxx << Obs.get_som()[j].getx() << " ";
        }

        fluxx << Obs.get_som()[Obs.get_nbs() - 1].getx() << "];" << endl;
        fluxx << "y_obs";
        fluxx << i;
        fluxx << "=[";
        for (int j = 0; j < Obs.get_nbs() - 1; j++)
        {
            fluxx << Obs.get_som()[j].gety() << " ";
        }
        fluxx << Obs.get_som()[Obs.get_nbs() - 1].gety() << "];" << endl;
        fluxx << "h" << i << "=fill(x_obs" << i << ",y_obs" << i << ",'y-');" << endl;
        fluxx << "h" << i << "FaceColor = [0 0.25 0.25];" << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////// La fonction Dijkstra qui utulise l'algorithme de Dijkstra :

pair<double, vector<Point>> dijkstra(Graphe& graph, Point source, Point destination,Obstacle& obs) {
    vector<Point> sommets=graph.getSommets();
    int V = sommets.size();
    vector<pair<Point, int>> pairs;
    for (int i = 0; i < sommets.size(); ++i) {
        pairs.push_back(make_pair(sommets[i], i));
    }
    vector<int> pred(V, -1); // Tableau pour stocker les prédécesseurs de chaque sommet
    vector<double> dist(V, 9999.); // Tableau pour stocker les distances les plus courtes
    vector<bool> visited(V, false); // Tableau pour marquer les sommets visités
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min-heap pour choisir le sommet suivant
    int i=0;
    for(int z =0;z<V;z++){
        if (pairs[z].first==source){dist[pairs[z].second] = 0;
        i=z;}
    }

    pq.push({0, i});
    int etape=0;
    int d;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
        int g;
        for(int z =0;z<V;z++){
        if (pairs[z].first==destination){g=z;}
        }
        // Si le nœud actuel est le nœud de destination, retourne sa distance minimale depuis la source
        if (u ==g )  {d=u ;break;}
        cout<<"step"<<etape<<":"<<endl;
        Point Q=pairs[u].first;
        cout<<"le point actuel est "<<Q<<endl;

        vector<Point> Neighbors;
        for(int z =0;z<V;z++){
        if (pairs[z].first!=Q){Neighbors.push_back(pairs[z].first);}
        }
        for (const auto& P : Neighbors) {
            cout<<P<<endl;
            Arc M=Arc(P,Q);
            int v ;
            for(int z =0;z<V;z++){
            if (pairs[z].first==P){v=z;}
            }
            double  weight=M.getLongueur();
            if (traverse(obs,M)==true){weight=9999;}
            if (seginlist(M,obs.aretes())||seginlist(inverse(M),obs.aretes())){weight=M.getLongueur();}
            if (relier(obs,M)){weight=M.getLongueur();}
            if (dist[u] < 10000 && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pred[v] = u;
                pq.push({dist[v], v});
            }

        }

    etape++;}
    vector<Point> cheminOptimal;
    int g = pred[d];
    cheminOptimal.push_back(destination);
    while (g != -1) {
        cheminOptimal.push_back(pairs[g].first);
        g = pred[g];
    }
    reverse(cheminOptimal.begin(), cheminOptimal.end());
    cout << "Chemin optimal :" << endl;
    for (const auto& point : cheminOptimal) {
    cout << point << "   ";
    }
    cout << endl;

    // Si le nœud de destination n'a pas été atteint, retourne une distance infinie
    return make_pair(dist[d], cheminOptimal);
}