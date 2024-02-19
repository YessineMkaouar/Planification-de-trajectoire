#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include "Point.h"
#include "Segment.h"
#include "Vecteur.h"
#include "Obstacle.h"
#include "Arc.h"
#include "Graphe.h"
#include "fonctions.h"
const double INFINIE = std::numeric_limits<double>::max();

int main()
{
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

    // Test de la classe Vecteur
    std::cout << "***** ************************* *****" << std::endl;
    std::cout << "***** Test de la classe Vecteur *****" << std::endl;
    Vecteur v1(p1, p2);
    std::cout << "Vecteur v1: (" << v1.getX() << ", " << v1.getY() << ")" << std::endl;
    std::cout << "Norme de v1: " << v1.norme() << std::endl;
    Vecteur v2(1.0, 1.0);
    std::cout << "Produit scalaire entre v1 et v2: " << v1.produitScalaire(v2) << std::endl;
    std::cout << "Angle entre v1 et v2: " << v1.angle(v2) << std::endl;
    std::cout << "v1 est aigu avec v2: " << v1.estAigu(v2) << std::endl;
    std::cout << "v1 est perpendiculaire a v2: " << v1.estPerpendiculaire(v2) << std::endl;

    // Test de la classe Obstacle
    std::cout << "***** ************************** *****" << std::endl;
    std::cout << "***** Test de la classe Obstacle *****" << std::endl;
    std::vector<Point> points_obstacle = {Point(0.0, 0.0), Point(2.0, 0.0), Point(2.0, 2.0), Point(0.0, 2.0)};
    Obstacle obstacle(points_obstacle);
    std::cout << "Nombre de sommets de l'obstacle: " << obstacle.get_nbs() << std::endl;
    std::vector<Segment> aretes_obstacle = obstacle.aretes();
    std::cout << "Nombre d'aretes de l'obstacle: " << aretes_obstacle.size() << std::endl;
    for (int i = 0; i < aretes_obstacle.size(); i++)
    {
        std::cout << "Aretes " << i << ": " << aretes_obstacle[i] << std::endl;
    }

    // Test de l'intersection entre deux segments
    std::cout << "***** ********************************************* *****" << std::endl;
    std::cout << "***** Test point d'intersection entre deux segments *****" << std::endl;
    double x1 = 0.0, y1 = 1.0;
    double x2 = 4.0, y2 = 3.0;
    double x3 = 0.0, y3 = 0.0;
    double x4 = 3.0, y4 = 4.0;
    Point p = obstacle.point_intersec(x1, y1, x2, y2, x3, y3, x4, y4);
    std::cout << "Point d'intersection entre les segments (" << x1 << ", " << y1 << ") -> (" << x2 << ", " << y2 << ") et (" << x3 << ", " << y3 << ") -> (" << x4 << ", " << y4 << "): " << p << std::endl;

    // Test de l'intersection d'un arc avec l'obstacle en au moins 2 points
    std::cout << "***** ***************************************************************** *****" << std::endl;
    std::cout << "***** Test d'intersection d'un arc avec l'obstacle en au moins 2 points *****" << std::endl;
    Arc arc(Point(-0.5, 0.5), Point(2.5, 1.0));
    std::cout << "Intersection entre l'arc et l'obstacle: " << obstacle.intersect(arc) << std::endl;

    // Test de la fonction ToutSegmentPossible
    std::cout << "***** ************************** *****" << std::endl;
    std::cout << "***** Test de ToutSegmentPossible *****" << std::endl;
    std::vector<Segment> segments_possibles = obstacle.ToutSegmentPossible();
    std::cout << "Nombre de segments possibles: " << segments_possibles.size() << std::endl;
    for (int i = 0; i < segments_possibles.size(); i++)
    {
        std::cout << "Segment " << i << ": " << segments_possibles[i] << std::endl;
    }
    // Test de la classe Graphe
    std::cout << "***** ************************** *****" << std::endl;
    std::cout << "***** Test de la classe Graphe *****" << std::endl;
    // Création de quelques points pour tester
    Point A(0, 0);
    Point B(1, 0);
    Point C(1, 2);
    Point D(3,0);
    Point E(3,2);
    Point F(5,1);
    Point G(4,4);
    Point H(7,0);
    Point I(5,3);

    // Création d'un vecteur de points
    std::vector<Point> points = {A, B, C, D, E, F,G,H,I};

    // Création d'un graphe avec ces points
    Graphe monGraphe(points);

    // Affichage du graphe
    monGraphe.afficher();

    // Obtention de la liste des arcs du graphe
    vector<Arc> arcs = monGraphe.getArcs();
    cout << "Liste des arcs du graphe : " << endl;
    for (const Arc& arc : arcs) {
        arc.afficher();
        cout << endl;  // Ajoute un saut de ligne apr�s chaque arc
}

    // Obtention de la liste des sommets du graphe
    vector<Point> sommets = monGraphe.getSommets();
    cout << "Liste des sommets du graphe : " << endl;
    for (const Point& sommet : sommets) {
        cout << sommet << endl;
    }

    // Obtention du nombre de sommets dans le graphe
    int nombreDeSommets = monGraphe.getN();
    cout << "Nombre de sommets dans le graphe : " << nombreDeSommets << endl;
    //tester les fonctions
    // Cr�ez des objets Segment et Obstacle pour les tests
    Point p11(0, 0);
    Point p21(1, 0);
    Point p31(2, 0);
    Point p41(1, -1);

    Segment segment11(p11, p21);
    Segment segment21(p31, p41);

    std::vector<Point> obstaclePoints = {p11, p21, p31};
    Obstacle obstacle1(obstaclePoints);

    // Testez les fonctions
    bool testResult1 = testin(segment11, p31);
    std::cout << "Resultat du test 1 : " << testResult1 << std::endl;

    double cosResult = vectcos(segment11, segment21);
    std::cout << "Resultat du test 2 (cosinus) : " << cosResult << std::endl;

    Segment inverseResult = inverse(segment11);
    std::cout << "Resultat du test 3 (inverse) : (" << inverseResult.getP1().getx() << "," << inverseResult.getP1().gety() << ") -> ("
          << inverseResult.getP2().getx() << "," << inverseResult.getP2().gety() << ")" << std::endl;

    Point intersectionPoint = determinIntersect(segment11, segment21);
    std::cout << "Resultat du test 4 (point intersection) : (" << intersectionPoint.getx() << "," << intersectionPoint.gety() << ")" << std::endl;


    bool upgradedIntersectionResult = upgradedintersection(segment11, segment21);
    std::cout << "Resultat du test 5 (intersection upgraded) : " << upgradedIntersectionResult << std::endl;

    bool traverseConvexeResult = traverse_Cas_Convexe(obstacle1, segment11);
    std::cout << "Resultat du test 6 (traverse convexe) : " << traverseConvexeResult << std::endl;

    std::cout << "Test de la fonction traverse_optimisant_cas_non_Convexe :" << std::endl;
    bool traverseNonConvexeResult = traverse_optimisant_cas_non_Convexe(obstacle1, segment11);
    std::cout << "Resultat : " << (traverseNonConvexeResult ? "true" : "false") << std::endl;

    std::cout << "\nTest de la fonction traverse :" << std::endl;
    bool traverseResult = traverse(obstacle1, segment11);
    std::cout << "Resultat : " << (traverseResult ? "true" : "false") << std::endl;

    std::cout << "\nTest de la fonction relier :" << std::endl;
    bool relierResult = relier(obstacle1, segment11);
    std::cout << "Resultat : " << (relierResult ? "true" : "false") << std::endl;

    std::vector<std::vector<double>> MatCout(monGraphe.getN(), std::vector<double>(monGraphe.getN(), 0)); // Matrice des couts

    std::vector<Point> obstaclePoints1 = {B, C, D, E,F,G,H};
    Obstacle obs(obstaclePoints1);
    pair<double, vector<Point>> pairs = dijkstra(monGraphe, A, I,obs);
    cout<<"la distance minimale est "<<pairs.first<<endl;
    vector<Point> path=pairs.second;

}
