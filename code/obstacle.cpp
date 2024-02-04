#include "Obstacle.h"
#include "Point.h"
#include "Segment.h"
#include <vector>
#include "Vecteur.h"

Obstacle::Obstacle() // constructeur par défaut ( Obstacle vide)
{
  nbs = 0;
  vector<Point> V;
  vector<Segment> VV;
  som = V;
  Tab = VV;
}
Obstacle::Obstacle(vector<Point> T) // constructeur à partir d'une liste de points
{
  som = T;
  nbs = T.size();
  for (int i = 0; i < nbs; i++) // Création d'un tableau Tab avec les bords de l'Obstacle
  {
    if (i < nbs - 1)
    {
      Tab.push_back(Segment(T[i], T[i + 1])); // ajout des segments ( les bords ) dans le vecteur Tab
    }
    if (i == nbs - 1)
    {
      Tab.push_back(Segment(T[i], T[0])); // ajout du dernier segment reliant le dernier point au premier
    }
  };
};

int Obstacle::get_nbs() const { return nbs; } // retourne le nombre de sommets de l'obstacle

// void Obstacle::add_som(Point P){som.push_back(P);nbs+=1;}

vector<Point> Obstacle::get_som() const { return som; } // retourne la liste des sommets de l'obstacle

vector<Segment> Obstacle::aretes() // retourne la liste des segments ( aretes ) de l'obstacle
{
  return Tab;
}
///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//// La partie du code suivant détermine le point d'intersection entre deux segments ////////
////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

Point point_intersec(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
  Point a1(x1, y1);
  Point a2(x2, y2);
  Vecteur A(a1, a2); // vecteur A

  Point b1(x3, y3);
  Point b2(x4, y4);
  Vecteur B(b1, b2); // vecteur B

  Vecteur temp_vecteur1(a1, b1);
  Vecteur temp_vecteur2(a1, b2);

  double a = static_cast<double>(A.pd_vect(temp_vecteur1)) / A.norme();
  double b = static_cast<double>(A.pd_vect(temp_vecteur2)) / A.norme();

  double nouveauB = B.norme() + (B.norme() * b) / (a - b);
  double resX, resY;
  double vraiRapport = nouveauB / B.norme();

  resX = b1.getx() + B.getX() * vraiRapport;
  resY = b1.gety() + B.getY() * vraiRapport;
  Point P11(resX, resY);
  return P11;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

double determinant(Vecteur V1, Vecteur V2)
{
  return V1.getX() * V2.getY() - V1.getY() * V2.getX();
}

bool Obstacle::intersect(Arc AB) // Verifie si un arc coupe l'obtacle en au moins 2 points
{
  int nbre = 0;                 // nombre de fois ou le segment intersecte la droite
  vector<Point> aux = som;      // aux est un vecteur qui contient les sommets de l'obstacle
  aux.push_back(som[0]);        // ajout du premier point à la fin du vecteur
  for (int i = 0; i < nbs; i++) // on parcourt les sommets de l'obstacle
  {
    Vecteur V1(aux[i], aux[i + 1]);     // vecteur V1 qui contient les coordonnées des points i et i+1
    Vecteur V2(AB.getP1(), AB.getP2()); // vecteur V2 qui contient les coordonnées des points P1 et P2 de l'arc
    if (determinant(V1, V2) != 0)
    {
      Point Pt = point_intersec(aux[i].getx(), aux[i].gety(), aux[i + 1].getx(), aux[i + 1].gety(), AB.getP1().getx(), AB.getP1().gety(), AB.getP2().getx(), AB.getP2().gety());
      Vecteur VP1(Pt, aux[i]);
      Vecteur VP2(Pt, aux[i + 1]);
      cout << VP1.norme() << " &&&& " << VP2.norme() << " ==== " << V1.norme() << endl;
      cout << Pt << endl;
      cout << (determinant(VP1, VP2) != 0);
      if (V1.norme() == VP1.norme() + VP2.norme())
      {
        nbre += 1;
      }
    }
  }
  cout << nbre;
  return (nbre >= 2);
}

// on mets la normal vers l'extérieur pour un Obstacle convexe
/* vector<Segment> & normal(Point & B){
     Point M = mid(S1,S2);
     S = seg(M,S);
     float ps = prod_euc(normal, S);
     if (ps>o) normal = -normal;
    return *this;
 }
*/

vector<Segment> Obstacle::ToutSegmentPossible() // Genere une lise de tous les segment qu'on peut dessiner dans un obstacle
{
  vector<Segment> V;
  for (int i = 0; i < nbs - 1; i++)
  {
    for (int j = i + 1; j < nbs; j++)
    {
      Segment S(som[i], som[j]);
      V.push_back(S);
    }
  }
  return V; // retourne la liste des segments possibles dans l'obstacle
}
