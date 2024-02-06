#include <iostream>
#include "Point.h"
#include "Segment.h"
#include "Vecteur.h"
#include "Arc.h"
#include "Graphe.h"
#include "obstacle.h"
#include "fonctions.h"
#include<bits/stdc++.h>
#include <sstream>
using namespace std;



int main()
{   cout<<"Bienvenue dans notre projet planification de la trajectoire "<<endl<<endl;
cout<<"Avant de commencer, il est necessaire d'avoir MATLAB installe sur votre PC."<<endl;
cout<<"-------------------------------------------------------------------"<<endl;
cout<<" Si vous voulez entrer vos coordonnees et vos obstacle � la main taper 0 "<<endl;
cout<<" Si vous voulez essayer nos tests proposes taper 1, 2, 3, 4, 5 "<<endl;
char reponse;
cin>>reponse;
 vector<Point> V1;                                   //Vecteur_contenant_tous_les_points
 vector<Obstacle> ListeOb;                                //Vecteur_contenant_tous_les_obstacles;
switch(reponse){
    case '0' :
    {
        cout<<"veuiller saisir les coordonn�e du point de depart s�parees par un espace"<<endl;
        double a,b;
        cin>>a>>b;
        Point O(a,b);
        cout<<endl<<"veuiller saisir les coordonnees du point d'arrivee s�parees par un espace"<<endl;
        cin>>a>>b;
        Point S(a,b);


        V1.push_back(O);
        V1.push_back(S);
        cout<<endl<<"Combien d'obstacle avez vous ?"<<endl;
        int nbreobs,nbresom;
        cin>>nbreobs;

        cout<<endl<<"(VEUILLEZ REMPLIR LES OBSTACLES DANS LE SENS DIRECT)"<<endl;
        for(int i=0;i<nbreobs;i++)
        {

            vector<Point> V; //Vecteur contenant les sommets de l'obstacle

            cout<<"Combien de sommets a l'obstacle "<<i<<endl;
            cin>>nbresom;
            cout<<endl;
             for(int j=0;j<nbresom;j++)
             {
                cout<<"veuiller saisir les coordonn�e du point"<<j<<" de l'obstacle "<<i<<" s�parees par un espace"<<endl;
                double a,b;
                cin>>a>>b;
                O.setx(a);
                O.sety(b);
                V1.push_back(O);
                V.push_back(O);
             }

            Obstacle Obs(V);
            ListeOb.push_back(Obs);
        }
    break;
    }

case '1' :
     // Test 1 ///////////////////////////
   //////////////////////////////////////////////////////////////////////

{   Point A(1,1);
    Point B(2,1);
    Point C(2,2);
    Point D(1,2);
    Point O(0,0);
    Point S(4,4);
    vector<Point> V;
    V.push_back(A);
    V.push_back(B);
    V.push_back(C);
    V.push_back(D);
    Obstacle Obs(V);
    ListeOb.push_back(Obs);
    V1.push_back(O);
    V1.push_back(S);
    V1.push_back(A);
    V1.push_back(B);
    V1.push_back(C);
    V1.push_back(D);
    break;
}



case '2' :
{


   // Test 2 ///////////////////////////
   //////////////////////////////////////////////////////////////////////
    Point O(0,1);
    Point S(13,1);

    Point A21(2,3);
    Point B21(4,3);
    Point C21(4,5);
    Point D21(2,5);
    vector<Point> V21;
    V21.push_back(A21);
    V21.push_back(B21);
    V21.push_back(C21);
    V21.push_back(D21);
    Obstacle Obs21(V21);
    ListeOb.push_back(Obs21);

    Point A22(2,-1);
    Point B22(2,-3);
    Point C22(4,-3);
    Point D22(4,-1);
    vector<Point> V22;
    V22.push_back(A22);
    V22.push_back(B22);
    V22.push_back(C22);
    V22.push_back(D22);
    Obstacle Obs22(V22);
    ListeOb.push_back(Obs22);

    Point A23(7,-7);
    Point B23(11,-7);
    Point C23(11,7);
    Point D23(7,7);
    vector<Point> V23;
    V23.push_back(A23);
    V23.push_back(B23);
    V23.push_back(C23);
    V23.push_back(D23);
    Obstacle Obs23(V23);
    ListeOb.push_back(Obs23);

    V1.push_back(O);
    V1.push_back(S);
    V1.push_back(A21);
    V1.push_back(B21);
    V1.push_back(C21);
    V1.push_back(D21);
    V1.push_back(A22);
    V1.push_back(B22);
    V1.push_back(C22);
    V1.push_back(D22);
    V1.push_back(A23);
    V1.push_back(B23);
    V1.push_back(C23);
    V1.push_back(D23);

    break;

}


case '3' :
    {

    Point A31(0,-1);
    Point B31(3,-5);
    Point C31(7,1);
    Point D31(2,-3);
    Point O(-1,0);
    Point S(9,-1);

    vector<Point> V31;
    V31.push_back(A31);
    V31.push_back(B31);
    V31.push_back(C31);
    V31.push_back(D31);
    Obstacle Obs31(V31);
    ListeOb.push_back(Obs31);

    Point A32(2,-1);
    Point B32(7,2);
    Point C32(-2,2);
    vector<Point> V32;
    V32.push_back(A32);
    V32.push_back(B32);
    V32.push_back(C32);
    Obstacle Obs32(V32);
    ListeOb.push_back(Obs32);


    V1.push_back(O);
    V1.push_back(S);
    V1.push_back(A31);
    V1.push_back(B31);
    V1.push_back(C31);
    V1.push_back(D31);
    V1.push_back(A32);
    V1.push_back(B32);
    V1.push_back(C32);
    break;
    }

case '4' :
    {
    Point A41(0,4);
    Point B41(6,4);
    Point C41(6,10);
    Point D41(0,10);
    Point O(-5,6);
    Point S(16,-5);

    vector<Point> V41;
    V41.push_back(A41);
    V41.push_back(B41);
    V41.push_back(C41);
    V41.push_back(D41);
    Obstacle Obs41(V41);
    ListeOb.push_back(Obs41);

    Point A42(0,-2);
    Point B42(0,-8);
    Point C42(6,-8);
    Point D42(6,-2);

    vector<Point> V42;
    V42.push_back(A42);
    V42.push_back(B42);
    V42.push_back(C42);
    V42.push_back(D42);
    Obstacle Obs42(V42);
    ListeOb.push_back(Obs42);

    Point A43(7,-2);
    Point B43(9,-2);
    Point C43(9,-5);
    Point D43(12,-5);
    Point E43(12,7);
    Point F43(9,7);
    Point G43(9,4);
    Point H43(7,4);

    vector<Point> V43;
    V43.push_back(A43);
    V43.push_back(B43);
    V43.push_back(C43);
    V43.push_back(D43);
    V43.push_back(E43);
    V43.push_back(F43);
    V43.push_back(G43);
    V43.push_back(H43);
    Obstacle Obs43(V43);
    ListeOb.push_back(Obs43);

    Point A44(14,-4);
    Point B44(14,-7);
    Point C44(18,-7);
    Point D44(18,-4);
    Point E44(17,-4);
    Point F44(16,-6);
    Point G44(15,-4);

    vector<Point> V44;
    V44.push_back(A44);
    V44.push_back(B44);
    V44.push_back(C44);
    V44.push_back(D44);
    V44.push_back(E44);
    V44.push_back(F44);
    V44.push_back(G44);
    Obstacle Obs44(V44);
    ListeOb.push_back(Obs44);

    V1.push_back(O);
    V1.push_back(S);
    V1.push_back(A41);
    V1.push_back(B41);
    V1.push_back(C41);
    V1.push_back(D41);
    V1.push_back(A42);
    V1.push_back(B42);
    V1.push_back(C42);
    V1.push_back(D41);
    V1.push_back(A43);
    V1.push_back(B43);
    V1.push_back(C43);
    V1.push_back(D43);
    V1.push_back(E43);
    V1.push_back(F43);
    V1.push_back(G43);
    V1.push_back(H43);
    V1.push_back(A44);
    V1.push_back(B44);
    V1.push_back(C44);
    V1.push_back(D44);
    V1.push_back(E44);
    V1.push_back(F44);
    V1.push_back(G44);
    break;

    }

case '5' :
    {
    Point O(0,0);
    Point S(17,0);

    Point A51(1,1);
    Point B51(4,1);
    Point C51(4,4);
    Point D51(2,4);
    Point E51(2,5);
    Point F51(4,5);
    Point G51(4,6);
    Point H51(1,6);
    Point I51(1,3);
    Point J51(3,3);
    Point K51(3,2);
    Point L51(1,2);

    vector<Point> V51;
    V51.push_back(A51);
    V51.push_back(B51);
    V51.push_back(C51);
    V51.push_back(D51);
    V51.push_back(E51);
    V51.push_back(F51);
    V51.push_back(G51);
    V51.push_back(H51);
    V51.push_back(I51);
    V51.push_back(J51);
    V51.push_back(K51);
    V51.push_back(L51);
    Obstacle Obs51(V51);
    ListeOb.push_back(Obs51);

    Point A52(6,1);
    Point B52(9,1);
    Point C52(9,2);
    Point D52(8,2);
    Point E52(8,5);
    Point F52(9,5);
    Point G52(9,6);
    Point H52(6,6);
    Point I52(6,5);
    Point J52(7,5);
    Point K52(7,2);
    Point L52(6,2);

    vector<Point> V52;
    V52.push_back(A52);
    V52.push_back(B52);
    V52.push_back(C52);
    V52.push_back(D52);
    V52.push_back(E52);
    V52.push_back(F52);
    V52.push_back(G52);
    V52.push_back(H52);
    V52.push_back(I52);
    V52.push_back(J52);
    V52.push_back(K52);
    V52.push_back(L52);
    Obstacle Obs52(V52);
    ListeOb.push_back(Obs52);


    Point A53(11,1);
    Point B53(12,1);
    Point C53(12,5);
    Point D53(13,3);
    Point E53(14,5);
    Point F53(14,1);
    Point G53(15,1);
    Point H53(15,6);
    Point I53(11,6);

    vector<Point> V53;
    V53.push_back(A53);
    V53.push_back(B53);
    V53.push_back(C53);
    V53.push_back(D53);
    V53.push_back(E53);
    V53.push_back(F53);
    V53.push_back(G53);
    V53.push_back(H53);
    V53.push_back(I53);
    Obstacle Obs53(V53);
    ListeOb.push_back(Obs53);


    Point A54(1+5,-1);
    Point B54(1+5,-3);
    Point C54(2+5,-3);
    Point D54(2+5,-2);
    Point E54(3+5,-2);
    Point F54(3+5,-4);
    Point G54(1+5,-4);
    Point H54(1+5,-7);
    Point I54(4+5,-7);
    Point J54(4+5,-6);
    Point K54(2+5,-6);
    Point L54(2+5,-5);
    Point M54(4+5,-5);
    Point N54(4+5,-1);

    vector<Point> V54;
    V54.push_back(A54);
    V54.push_back(B54);
    V54.push_back(C54);
    V54.push_back(D54);
    V54.push_back(E54);
    V54.push_back(F54);
    V54.push_back(G54);
    V54.push_back(H54);
    V54.push_back(I54);
    V54.push_back(J54);
    V54.push_back(K54);
    V54.push_back(L54);
    V54.push_back(M54);
    V54.push_back(N54);
    Obstacle Obs54(V54);
    ListeOb.push_back(Obs54);




    V1.push_back(O);
    V1.push_back(S);
    V1.push_back(A51);
    V1.push_back(B51);
    V1.push_back(C51);
    V1.push_back(D51);
    V1.push_back(E51);
    V1.push_back(F51);
    V1.push_back(G51);
    V1.push_back(H51);
    V1.push_back(I51);
    V1.push_back(J51);
    V1.push_back(K51);
    V1.push_back(L51);
    V1.push_back(A52);
    V1.push_back(B52);
    V1.push_back(C52);
    V1.push_back(D52);
    V1.push_back(E52);
    V1.push_back(F52);
    V1.push_back(G52);
    V1.push_back(H52);
    V1.push_back(I52);
    V1.push_back(J52);
    V1.push_back(K52);
    V1.push_back(L52);
    V1.push_back(A53);
    V1.push_back(B53);
    V1.push_back(C53);
    V1.push_back(D53);
    V1.push_back(E53);
    V1.push_back(F53);
    V1.push_back(G53);
    V1.push_back(H53);
    V1.push_back(I53);
    V1.push_back(A54);
    V1.push_back(B54);
    V1.push_back(C54);
    V1.push_back(D54);
    V1.push_back(E54);
    V1.push_back(F54);
    V1.push_back(G54);
    V1.push_back(H54);
    V1.push_back(I54);
    V1.push_back(J54);
    V1.push_back(K54);
    V1.push_back(L54);
    V1.push_back(M54);
    V1.push_back(N54);


    break;


    }

   }


    //////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////



Graphe G(V1);           //la graphe contenant tous les points


double MatCout[G.getN()][G.getN()]; // Matrice des couts

//////////////////////////////////////////////////// Ce morceau de code modifie la matrice du cout avec les poids demand� dans l'�nonc�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////



for(int i=0;i<G.getN();i++)
    {
     for(int j=0;j<G.getN();j++)
    {
    Point P1(G.getSommets()[i].getx(),G.getSommets()[i].gety());

    Segment Mij(G.getSommets()[i],G.getSommets()[j]);
    MatCout[i][j]=Mij.getLongueur();
         for(int k=0;k<ListeOb.size();k++)
           {
                Obstacle obs(ListeOb[k].get_som());
                if (traverse(obs,Mij)==true){MatCout[i][j]=INFINIE;}
                if (seginlist(Mij,obs.aretes())||seginlist(inverse(Mij),obs.aretes())){MatCout[i][j]=Mij.getLongueur();}
               if (relier(obs,Mij)){MatCout[i][j]=Mij.getLongueur();}
           for(int h=0;h<obs.ToutSegmentPossible().size();h++)
           {
               if (Mij==obs.ToutSegmentPossible()[h]) {if (!seginlist(Mij,obs.aretes())) MatCout[i][j]=INFINIE;}
           }
           }
    }
    }


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  DIJSKESTRA ///////////////////////////////////////////////////////////


int Nbs=G.getN();
double dist[Nbs];
int par[Nbs];
bool vis[Nbs];
int st=0;
int fi=1;

    set<pair<double,int> > ss;
    for(int i=0;i<Nbs;i++){
        dist[i]=INFINIE;
        par[i]=0;
        vis[i]=0;
    }
    dist[st]=0;
    par[st]=-1;
    ss.insert({dist[st],st});
    while(!ss.empty()){
        pair<double,int> fr = *(ss.begin());
        ss.erase(ss.begin());
        if(vis[fr.second])continue;
        vis[fr.second]=1;
        for(int j=0;j<Nbs;j++){
            if(abs(MatCout[fr.second][j])<=0.00001)continue;
            if(vis[j])continue;
            if(dist[j]>dist[fr.second]+MatCout[fr.second][j]){
                par[j]=fr.second;
                dist[j]= dist[fr.second]+MatCout[fr.second][j];
                ss.insert({dist[j],j});
            }
        }
    }
    vector<pair<int,int> > resultat;
    vector<int> path;
    if(!(dist[fi]>=INFINIE));
    path.push_back(fi);
    while(par[fi]!=-1){
        path.push_back(par[fi]);
        fi=par[fi];

    }
    for(int i=path.size()-1;i>0;i--){
        resultat.push_back({path[i],path[i-1]});
    }

vector<pair<int,int> > PlusCourtChemin=resultat;

///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// DESSIN DU PLUS COURT CHEMIN //////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////// Fonction qui retourne un fichier txt contenant le code matlab pour le dessin
/* ofstream flux;
flux.open("Matlab/codeMatlab.m");
if (flux)
    {
    flux<<"%la matrice des cout initiale"<<endl;
    flux<<"M = [";
    for (int i=0;i<G.getN()-1;i++)
    {
        for (int j=0;j<G.getN();j++)
        {
            flux<<MatCout[i][j]<< " ";
        }
    flux<<";"<<endl;
    }
    int i=G.getN()-1;
     for (int j=0;j<G.getN();j++)
        {
            flux<<MatCout[i][j]<< " ";
        }
    flux<<"];"<<endl;

flux<<endl<<"%Les Points du graphe"<<endl<<endl;
dessinerGraphe(G,flux);                     //dessin de tous Le Graphe



                                            //dessin de tous les arcs possibles
flux<<"n=length(x);"<<endl;
flux<<"A=ones(n,n);"<<endl;
flux<<"for ligne = 1:n"<<endl;
flux<<"\tfor colonne = 1:n"<<endl;
flux<<"\t\tif ((M(ligne,colonne)==0) | (M(ligne,colonne) > 9000))"<<endl;
flux<<"\t\t\tA(ligne,colonne)=0;"<<endl;
flux<<"\t\tend"<<endl;
flux<<"\tend"<<endl;

flux<<"end"<<endl<<endl;

flux<<"hold on;"<<endl;
flux<<"for i = 1:n"<<endl;
flux<<"\tfor j = 1:n"<<endl;
flux<<"\t\tx1=[0 0];"<<endl;
flux<<"\t\ty1=[0 0];"<<endl;
flux<<"\t\tif (A(i,j)==1)"<<endl;
flux<<"\t\t\tx1(1)=x(i);"<<endl;
flux<<"\t\t\ty1(1)=y(i);"<<endl;
flux<<"\t\t\tx1(2)=x(j);"<<endl;
flux<<"\t\t\ty1(2)=y(j);"<<endl;
flux<<"\t\t\tplot(x1,y1,'k-','linewidth',1);"<<endl;
flux<<"\t\tend"<<endl;
flux<<"\tend"<<endl;
flux<<"end"<<endl;

flux<<endl<<"%Les Points des obstacles"<<endl<<endl;
dessinerObstacles(ListeOb,flux);               //dessin de tous les obstacles

                                                        // DESSIN DU PLUS COURT CHEMIN
        flux<<endl<<"%Le plus court Chemin"<<endl;
        flux<<"PCC_x = [";
        for(int i=0;i<PlusCourtChemin.size();i++)
        {
        Point P1 =G.getSommets()[PlusCourtChemin[i].first];
        Point P2 =G.getSommets()[PlusCourtChemin[i].second];
        flux<<P1.getx()<<" "<<P2.getx()<<" ";
        }
        flux<<G.getSommets()[1].getx();
        flux<<"];"<<endl;

        flux<<"PCC_y = [";
        for(int i=0;i<PlusCourtChemin.size();i++)
        {
        Point P1 =G.getSommets()[PlusCourtChemin[i].first];
        Point P2 =G.getSommets()[PlusCourtChemin[i].second];
        flux<<P1.gety()<<" "<<P2.gety()<<" ";
        }
        flux<<G.getSommets()[1].gety();
        flux<<"];"<<endl;
        flux<<"plot(PCC_x,PCC_y,'r-','linewidth',2);"<<endl;
        flux<<"plot(PCC_x(1),PCC_y(1),'.r','MarkerSize', 40)"<<endl;
        flux<<"plot(PCC_x(length(PCC_x)),PCC_y(length(PCC_y)),'.r','MarkerSize', 40)"<<endl;
    }

else
{
    cout<<"ERREUR : Impossible d'ouvrir le fichier"<<endl;
}


///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////  AFFICHAGE FINAL
cout<<"---------Votre trajectoire est totalement planifie et on vous a trouv� le plus court chemin !! ------------"<<endl<<endl<<endl<<endl<<endl<<endl;

// affichage des matrice de cout

cout<<"Voulez vous afficher la matrice du cout initiale ? (Y/N)"<<endl;

char reponse1;
cin>>reponse1;
if (reponse1=='Y'){

    for (int i=0;i<G.getN();i++)
    {
        for (int j=0;j<G.getN();j++)
        {
            cout<<MatCout[i][j]<< "   |    ";
        }
        cout<<endl;
    }
}


cout<<endl<<endl<<endl<<"-------------------------------------------------------------------"<<endl;
cout<<"Voulez vous afficher les coordonn�es des points du plus court chemin ? (Y/N)"<<endl;
char reponse2;
cin>>reponse2;
if (reponse2=='Y'){
for(int i=0;i<PlusCourtChemin.size();i++)
{
    cout<<G.getSommets()[PlusCourtChemin[i].first]<<"-->"<<G.getSommets()[PlusCourtChemin[i].second]<<endl;
}
}
system("Matlab/codeMatlab.m");
cout<<endl<<"*  *  *  *  *  *  *  *  *  *  *  *  *  *  *"<<endl<<"Merci d'avoir untilis� notre programme :)"<<endl;
bool closing;
cin>>closing;
exit(1); */
    return 0;
}
