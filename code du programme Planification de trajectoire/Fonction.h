#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include "Vecteur.h"
#include "Arc.h"
#include "Segment.h"
#include "Graphe.h"
#include "obstacle.h"
#include "Vecteur.h"
#include <bits/stdc++.h>
#include <iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include <cmath>
#include <math.h>
#include <string>
using namespace std;
const double INFINIE=9999;          //Cette valeur INFINIE peut etre changer au souhait de son utilisateur

/*#####################################################*/


//////////////////////////////////////////////////////////////// Fonction qui teste si un point appartient à un segment
bool testin(Segment S1,Point s)
{
double EPSILON=0.01;
Vecteur V1(S1.getP1(),S1.getP2());
Vecteur V2(S1.getP1(),s);
Vecteur V3(S1.getP2(),s);
double xa=S1.getP1().getx();
double ya=S1.getP1().gety();
double xb=S1.getP2().getx();
double yb=S1.getP2().gety();
double xc=s.getx();
double yc=s.gety();
bool test1=((xc-xa)*(yb-ya)-(yc-ya)*(xb-xa)<EPSILON);

bool test2=((abs(xc-xa)-abs(xb-xa))<EPSILON);
bool test3=((xc-xa)*(xb-xa)>=0);
bool test4=((abs(yc-ya)-abs(yb-ya))<EPSILON);
bool test5=((yc-ya)*(yb-ya)>=0);
bool test=(((test1&&test2)&&(test3&&test4))&&test5);

return (test || s==S1.getP1()) || s==S1.getP2();
}

///////////////////////////////////////////////////////////////////////// Fonction qui retourne l'angle entre deux segments
double vectcos(Segment s1,Segment s2){
	Vecteur V1(s1.getP1(),s1.getP2());
	Vecteur V2(s2.getP1(),s2.getP2());
	return cos(V1.angle(V2));
}

/////////////////////////////////////////////////////////// Fonction qui retourne L'inverse d'un segment
Segment inverse(Segment S)
{
	Segment aux(S.getP2(),S.getP1());
	return aux;
}

///////////////////////////////////////////////////////// Fonction qui determine le point d'intersection entre deux segments
Point determinIntersect(Segment S1,Segment S2)
{
const double EPSILON=0.01;

struct ppoint{
  double x,y;
  ppoint(double _x,double _y):x(_x),y(_y){}
};
struct vvecteur{
  double x,y;
  ppoint a,b;
  vvecteur(ppoint _a,ppoint _b):a(_a),b(_b)
  {
    x=b.x-a.x;
    y=b.y-a.y;
  }
  double vecto(vvecteur autre){
    return (x*autre.y-y*autre.x);
  }
  double norme(){
    return sqrt(x*x+y*y);
  }
};

  double x1,y1,x2,y2;
  x1=S1.getP1().getx();
  y1=S1.getP1().gety();
  x2=S1.getP2().getx();
  y2=S1.getP2().gety();
  ppoint a1(x1,y1);
  ppoint a2(x2,y2);
  vvecteur A(a1,a2);

  double xx1,yy1,xx2,yy2;
  xx1=S2.getP1().getx();
  yy1=S2.getP1().gety();
  xx2=S2.getP2().getx();
  yy2=S2.getP2().gety();
  ppoint b1(xx1,yy1);
  ppoint b2(xx2,yy2);
  vvecteur B(b1,b2);
  double resX,resY;

  double a=(double)A.vecto(vvecteur(a1,b1))/A.norme();
  double b=(double)A.vecto(vvecteur(a1,b2))/A.norme();
  double nouveauB=B.norme()+(B.norme()*b)/(a-b);
  double vraiRapport=nouveauB/B.norme();
  resX=(double)b1.x+(double)B.x*vraiRapport;
  resY=(double)b1.y+(double)B.y*vraiRapport;
  Point P(resX,resY);
  return P;
}



/////////////////////////////////////////////////////////// Fonction qui teste si deux segment s'intersectent
bool upgradedintersection(Segment S1 , Segment S2)
{
    Point s=determinIntersect(S1,S2);
    return (testin(S1,s)) && (testin(S2,s));
}
//////////////////////////////////////////////////////////// Fonction qui retourne si un segment est dans une liste de segments données
bool seginlist(Segment S,vector <Segment> L)
{
	for(int i=0;i<L.size();i++){if((S==L[i])||(inverse(S)==L[i])) return true;}
		return false;
}
//////////////////////////////////////////////////////////// Fonction qui retourne si un sommet est dans une listes de sommets données
bool sinlistsom(Point s,vector <Point> L)
{
    for(int i=0;i<L.size();i++){if(s==L[i]) return true;}
        return false;
}
/////////////////////////////////////////////////////////// Fonction qui verifie si un segment traverse un obstacle Dans le cas convexe (Parfois non convexe)
bool traverse_Cas_Convexe(Obstacle Obs, Segment S)
{
    int res=0;
    set<pair<double,double> > V;
    for(int i=0;i<Obs.aretes().size();i++)
    {
        if (upgradedintersection(Obs.aretes()[i],S))
                {
                pair<double,double> P;
                P= make_pair(determinIntersect(Obs.aretes()[i],S).getx(),determinIntersect(Obs.aretes()[i],S).gety());
                V.insert(P);}
    }
    return (V.size()>=2);
}

/////////////////////////////////////////////////////   Fonction qui verifie si un segment traverse un obstacle Dans le cas non convexe
bool traverse_optimisant_cas_non_Convexe(Obstacle Obs,Segment S)
{
    for(int i=0;i<Obs.aretes().size();i++)
    {
        Segment Seg=Obs.aretes()[i];
    if (upgradedintersection(Seg,S))
    {
        Point P=determinIntersect(Seg,S);
        if (!sinlistsom(P,Obs.get_som())) return true;
    }
    }
return false;
}

///////////////////////////////////////////////////// Fonction qui verifie si un segment traverse un obstacle
bool traverse(Obstacle Obs,Segment S)
{
    return traverse_optimisant_cas_non_Convexe(Obs,S) || traverse_Cas_Convexe(Obs,S);
}
//////////////////////////////////////////////////////////// Fonction qui verifie si un segment dans un obstacle peut être relier ou pas
bool relier(Obstacle ob,Segment S)
{
    bool test1= sinlistsom(S.getP1(),ob.get_som());
    bool test2= sinlistsom(S.getP2(),ob.get_som());
    test1= test1 && test2;
    if (test1==false) return false;

    test2=seginlist(S,ob.aretes())||seginlist(inverse(S),ob.aretes());
    vector<Segment> L=ob.ToutSegmentPossible();
    for(int i=0;i<L.size();i++)
    {
        if (upgradedintersection(S,L[i]))
            {
        Point P=determinIntersect(S,L[i]);
        if (sinlistsom(P,ob.get_som())==false) return false;
            }
    }
    return true;
}

////////////////////////////////////////////////////////////// Cette fonction retourne un fichier txt qui contient les coordonnées des points du graphe
void dessinerGraphe(Graphe G,ofstream &flux)
{

    flux<<"x = [";
    for (int i=0;i<G.getN()-1;i++)
    {
        flux<<G.getSommets()[i].getx()<<" ";
    }
    int i=G.getN()-1;
    flux<<G.getSommets()[i].getx()<<"];"<<endl;
    flux<<"y = [";
    for (int i=0;i<G.getN()-1;i++)
    {
        flux<<G.getSommets()[i].gety()<<" ";
    }
    flux<<G.getSommets()[i].gety()<<"];"<<endl;
    flux<<"plot(x,y,'.k','MarkerSize', 30)"<<endl;

}
/////////////////////////////////////////////////////////////////// Cette fonction retourneun fichier txt qui contient les coordonné des points d'un obstacle

void dessinerObstacles(vector<Obstacle> O,ofstream &fluxx)
{


    for(int i=0;i<O.size();i++)
    {
        Obstacle Obs(O[i].get_som());
        fluxx<<"x_obs";
        fluxx<<i;
        fluxx<<"=[";

                    for(int j=0;j<Obs.get_nbs()-1;j++)
                        {fluxx<<Obs.get_som()[j].getx()<<" ";
                        }


        fluxx<<Obs.get_som()[Obs.get_nbs()-1].getx()<<"];"<<endl;
        fluxx<<"y_obs";
        fluxx<<i;
        fluxx<<"=[";
                    for(int j=0;j<Obs.get_nbs()-1;j++)
                        {fluxx<<Obs.get_som()[j].gety()<<" ";

                        }
        fluxx<<Obs.get_som()[Obs.get_nbs()-1].gety()<<"];"<<endl;
        fluxx<<"h"<<i<<"=fill(x_obs"<<i<<",y_obs"<<i<<",'y-');"<<endl;
        fluxx<<"h"<<i<<"FaceColor = [0 0.25 0.25];"<<endl;
    }
}

#endif // FONCTION_H_INCLUDED
