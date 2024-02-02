#include "Arc.h"
#include <bits/stdc++.h>

Arc::Arc()
{
    P1.setx(0);
    P1.sety(0);
    P2.setx(0);
    P2.sety(0);
    COUT=0;
}
Arc::Arc(Point A, Point B)
{
    P1.setx(A.getx());
    P1.sety(A.gety());
    P2.setx(B.getx());
    P2.sety(B.gety());
    COUT=sqrt((P1.getx()-P2.getx())*(P1.getx()-P2.getx())+(P1.gety()-P2.gety())*(P1.gety()-P2.gety()));
}
double Arc::getCout(){return COUT;};
void Arc::afficher(){cout<<"Arc oriente de ("<<P1.getx()<<","<<P1.gety()<<
                                ") vers ("<<P2.getx()<<","<<P2.gety()<<
                                "). Son cout est "<<COUT<<endl;
}
