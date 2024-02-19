#include "Obstacle.h"
#include "Point.h"
#include "Segment.h"
#include <vector>
#include "Vecteur.h"

Obstacle::Obstacle() : nbs(0), som(std::vector<Point>()), Tab(std::vector<Segment>()) {} // constructeur par d�faut

Obstacle::Obstacle(const std::vector<Point> &T) : som(T), nbs(T.size()), Tab(std::vector<Segment>()) // constructeur � partir d'une liste de points
{
  for (int i = 0; i < nbs; i++) // on parcourt les sommets de l'obstacle
  {
    if (i < nbs - 1)
    {
      Tab.push_back(Segment(T[i], T[i + 1]));
    }
    if (i == nbs - 1)
    {
      Tab.push_back(Segment(T[i], T[0]));
    }
  }
}

int Obstacle::get_nbs() const { return nbs; } // retourne le nombre de sommets de l'obstacle

// void Obstacle::add_som(Point P){som.push_back(P);nbs+=1;}

vector<Point> Obstacle::get_som() const { return som; } // retourne la liste des sommets de l'obstacle

vector<Segment> Obstacle::aretes() const // retourne la liste des segments ( aretes ) de l'obstacle
{
  return Tab;
}

Point Obstacle::point_intersec(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) const // retourne le point d'intersection entre deux segments
{
  Point a1(x1, y1);
  Point a2(x2, y2);
  Vecteur A(a1, a2);

  Point b1(x3, y3);
  Point b2(x4, y4);
  Vecteur B(b1, b2);

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

double Obstacle::determinant(const Vecteur &V1, const Vecteur &V2) const
{
  return V1.getX() * V2.getY() - V1.getY() * V2.getX();
}

bool Obstacle::intersect(const Arc &AB) const // Verifie si un arc coupe l'obtacle en au moins 2 points
{
  int nbre = 0;
  std::vector<Point> aux = som;
  aux.push_back(som[0]);

  for (int i = 0; i < nbs; i++)
  {
    if (i < nbs - 1)
    {
      Vecteur V1(aux[i], aux[i + 1]);
      Vecteur V2(AB.getP1(), AB.getP2());

      if (determinant(V1, V2) != 0)
      {
        Point Pt = point_intersec(aux[i].getx(), aux[i].gety(), aux[i + 1].getx(), aux[i + 1].gety(),
                                  AB.getP1().getx(), AB.getP1().gety(), AB.getP2().getx(), AB.getP2().gety());

        Vecteur VP1(Pt, aux[i]);
        Vecteur VP2(Pt, aux[i + 1]);

        if (V1.norme() == VP1.norme() + VP2.norme())
        {
          nbre += 1;
        }
      }
    }
  }

  return (nbre >= 2);
}

std::vector<Segment> Obstacle::ToutSegmentPossible() // Genere une liste de tous les segments qu'on peut dessiner dans un obstacle
{
    std::vector<Segment> V; // Vecteur pour stocker les segments possibles

    for (int i = 0; i < nbs - 1; i++)
    {
        for (int j = i + 1; j < nbs; j++)
        {
            Segment S(som[i], som[j]); // Cr�ation d'un segment entre les points i et j
            V.push_back(S); // Ajout du segment au vecteur
        }
    }

    return V; // Retourne la liste des segments possibles dans l'obstacle
}


