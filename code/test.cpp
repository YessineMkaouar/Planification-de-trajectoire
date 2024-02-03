#include <iostream>
#include "Point.h"
#include "Segment.h"
#include "Vecteur.h"
#include "Obstacle.h"
#include "Arc.h"

int main() {
    // Test de la classe Point
    std::cout << "***** Test de la classe Point *****" << std::endl;
    Point p1(1.0, 1.0);
    Point p2(3.0, 4.0);
    std::cout << "Point p1: " << p1 << std::endl;
    std::cout << "Point p2: " << p2 << std::endl;
    std::cout << "Distance entre p1 et p2: " << p1.distance(p2) << std::endl;
    std::cout << "p1 == p2: " << (p1 == p2) << std::endl;
    std::cout << "L'abscisse de p1: " << p1.getx() << std::endl;
    std::cout << "L'ordonnee de p1: " << p1.gety() << std::endl;
    p1.setx(2.0);
    std::cout << "Nouvelle abscisse de p1: " << p1.getx() << std::endl;
    std::cout << "Point p1: " << p1 << std::endl;

    // Test de la classe Segment
    std::cout << "***** ************************* *****" << std::endl;
    std::cout << "***** Test de la classe Segment *****" << std::endl;
    Segment s1(p1, p2);
    Point p3(3.0, 1.0);
    Point p4(1.0, 1.0);
    Segment s2(p3, p4);
    std::cout << "Segment s1: " << s1 << std::endl;
    std::cout << "Segment s2: " << s2 << std::endl;
    std::cout << "Longueur de s1: " << s1.getLongueur() << std::endl;
    std::cout << "Intersection entre s1 et s2: " << s1.intersect(s2) << std::endl;

  /*  // Test de la classe Vecteur
    Vecteur v1(p1, p2);
    std::cout << "Vecteur v1: (" << v1.getX() << ", " << v1.getY() << ")" << std::endl;
    std::cout << "Norme de v1: " << v1.norme() << std::endl;

    // Test de la classe Obstacle
    std::vector<Point> points_obstacle = {Point(0.0, 0.0), Point(2.0, 0.0), Point(2.0, 2.0), Point(0.0, 2.0)};
    Obstacle obstacle(points_obstacle);
    std::cout << "Nombre de sommets de l'obstacle: " << obstacle.get_nbs() << std::endl;
    std::vector<Segment> aretes_obstacle = obstacle.aretes();
    std::cout << "Nombre d'arêtes de l'obstacle: " << aretes_obstacle.size() << std::endl;

    // Test de l'intersection
    Segment test_segment(Point(-1.0, -1.0), Point(3.0, 3.0));
    std::cout << "Intersection avec le segment de test: " << obstacle.intersect(test_segment) << std::endl;

    // Autres tests...
     */
    return 0;
}
