#include "Obstacle.h"
#include "Point.h"
#include "Segment.h"
#include <vector>
#include "Vecteur.h"

Obstacle::Obstacle() : nbs(0), som(std::vector<Point>()), Tab(std::vector<Segment>()) {} // constructeur par défaut

Obstacle::Obstacle(const std::vector<Point> &T) : som(T), nbs(T.size()), Tab(std::vector<Segment>()) // constructeur à partir d'une liste de points
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
            Segment S(som[i], som[j]); // Création d'un segment entre les points i et j
            V.push_back(S); // Ajout du segment au vecteur
        }
    }

    return V; // Retourne la liste des segments possibles dans l'obstacle
}
