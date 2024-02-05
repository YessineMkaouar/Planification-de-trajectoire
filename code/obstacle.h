#ifndef OBSTACLEH
#define OBSTACLEH

#include <vector>
#include "Vecteur.h"
#include "Point.h"
#include "Segment.h"
#include "Arc.h"
using namespace std;

class Obstacle

{
private:
    int nbs;             // nombre de sommet de l'obstacle
    vector<Point> som;   // vecteur contenant les sommets de l'obstacle
    vector<Segment> Tab; // vecteur contenant l'ensemble des aretes (segments) de l'obstacle

public:
    Obstacle(); // constructeur de la classe Obstacle
    Obstacle(const std::vector<Point>&); // constructeur de la classe Obstacle
    int get_nbs() const; // getter du nombre de sommets
    std::vector<Point> get_som() const; // getter des sommets
    std::vector<Segment> aretes() const; // getter des aretes
    bool intersect(const Arc& AB) const; // test d'intersection entre un arc et l'obstacle
    std::vector<Segment> ToutSegmentPossible(); // retourne l'ensemble des segments possibles
    Point point_intersec(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) const; // retourne le point d'intersection entre deux segments
    double determinant(const Vecteur& V1, const Vecteur& V2) const ; // retourne le determinant entre deux vecteurs
};
#endif
