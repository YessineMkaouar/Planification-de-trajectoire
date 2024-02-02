#ifndef ARC_H_INCLUDED
#define ARC_H_INCLUDED

#include <iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include "Segment.h"

using namespace std;
class Arc : public Segment
{
private:
    double COUT;        //cout d'un arc (évidemment sa norme 2)
public:
    Arc();
    Arc(Point P1,Point P2);
    double getCout();
    void afficher();
};

#endif // ARC_H_INCLUDED
