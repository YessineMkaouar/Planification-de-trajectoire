#include "Obstacle.h"
#include "Point.h"
#include "Segment.h"
#include <vector>
#include "Vecteur.h"
//constructeur

Obstacle::Obstacle()
{nbs=0;
vector<Point> V;
vector<Segment> VV;
som=V;
Tab=VV;
}
Obstacle::Obstacle(vector <Point> T)
{
	som=T;
	nbs=T.size();
for(int i=0;i<nbs;i++)
{	if(i<nbs-1)
{

	Tab.push_back(Segment(T[i],T[i+1]));
}
	if(i==nbs-1)
	{
		Tab.push_back(Segment(T[i],T[0]));
	}
};
};



// création d'un tableau avec les bords de l'Obstacle

int Obstacle::get_nbs() const {return nbs;}

//void Obstacle::add_som(Point P){som.push_back(P);nbs+=1;}


vector<Point> Obstacle::get_som() const {return som;}


vector<Segment> Obstacle::aretes(){
    return Tab;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//// La FONTION SUIVANTE CALCULE L'intersecgtion entre deux segment///////////
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
struct PPoint{
  double x,y;
  PPoint(double _x,double _y):x(_x),y(_y){}
};
struct VVecteur{
  double x,y;
  PPoint a,b;
  VVecteur(PPoint _a,PPoint _b):a(_a),b(_b)
  {
    x=b.x-a.x;
    y=b.y-a.y;
  }
  double vecto(VVecteur autre){
    return (x*autre.y-y*autre.x);
  }
  double norme(){
    return sqrt(x*x+y*y);
  }
};
Point point_intersec(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{

  PPoint a1(x1,y1);
  PPoint a2(x2,y2);
  VVecteur A(a1,a2);

  PPoint b1(x3,y3);
  PPoint b2(x4,y4);
  VVecteur B(b1,b2);

  double a=(double)A.vecto(VVecteur(a1,b1))/A.norme();
  double b=(double)A.vecto(VVecteur(a1,b2))/A.norme();

  double nouveauB=B.norme()+(B.norme()*b)/(a-b);
  double resX,resY;
  double vraiRapport=nouveauB/B.norme();

  resX=(double)b1.x+(double)B.x*vraiRapport;
  resY=(double)b1.y+(double)B.y*vraiRapport;
  Point P11(resX,resY);
  return P11;
}

double determinant(Vecteur V1, Vecteur V2)
    {return V1.getX()*V2.getY()-V1.getY()*V2.getX();}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
bool Obstacle::intersect(Arc AB)
{
    int nbre=0; // nombre de fois ou le segment intersecte la droite
    vector<Point> aux=som;
    aux.push_back(som[0]);
    for(int i=0;i<nbs;i++){
        Vecteur V1(aux[i],aux[i+1]);
        Vecteur V2(AB.getP1(),AB.getP2());
        if(determinant(V1,V2)!=0)
        {
            Point Pt=point_intersec(aux[i].getx(),aux[i].gety(),aux[i+1].getx(),aux[i+1].gety(),AB.getP1().getx(),AB.getP1().gety(),AB.getP2().getx(),AB.getP2().gety());
            Vecteur VP1(Pt,aux[i]);
            Vecteur VP2(Pt,aux[i+1]);
            cout<<VP1.norme()<<" &&&& "<<VP2.norme()<<" ==== " <<V1.norme()<<endl;
            cout<<Pt<<endl;
            cout<<(determinant(VP1,VP2)!=0);
            if (V1.norme()==VP1.norme()+VP2.norme()) {nbre+=1;}
        }
    }
    cout<<nbre;
    return(nbre>=2);
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

vector<Segment> Obstacle::ToutSegmentPossible()
{   vector<Segment> V;
    for(int i=0;i<nbs-1;i++)
    {
        for(int j=i+1;j<nbs;j++)
        {
           Segment S(som[i],som[j]);
           V.push_back(S);
        }
    }
    return V;
}
