#include "trajectoire.hpp"

double M_PI = 3.14159265358979323846;

// choix des paramètres du code :
// ------------------------------------------------------------------------------------------------
string Exemple="Exemple 1 - Labryinth"; // nom du dossier de l'exemple, sinon vide
sommet depart(141,-162), arrivee(423,-314) ; // les points de depart et d'arrivée
int test_affich = 0 ; // 0 -> calcul du chemin ; 1 -> test de l'affichage

    // rotation :
int n_rot = 8 ; // discrétisation de la rotation 360° (par defaut 1 --> objet ne tourne pas)
long double cout_tour = 0.01 ; // le coût (en distance) d'un tour discrétisé

int z_obs = 0 ; // le layer du padding à afficher (0 par défaut)
// ----------------------------------------------------------------------------------------------//

//implementation de la classe sommet :
// ------------------------------------------------------------------------------------------------
sommet& sommet::operator = (const sommet &S){
    Sx=S.Sx;
    Sy=S.Sy;
    idx=S.idx;
    sens=S.sens;
    return (*this);
}

ostream& operator << (ostream& out, const sommet& S)
{
    out<<"("<<S.Sx<<","<<S.Sy<<","<<S.idx<<","<<S.sens<<")";
    return out;
}

long double produit_scalaire(const sommet& A, const sommet& B){//produit scalaire
    return(A.Sx*B.Sx+A.Sy*B.Sy);
}

long double determinant(const sommet& A, const sommet& B){
    return (A.Sx*B.Sy-A.Sy*B.Sx);
}

sommet operator + (const sommet& S1,const sommet& S2)
{
    return(sommet(S1.Sx+S2.Sx, S1.Sy+S2.Sy,S1.idx));
}

sommet operator - (const sommet& S1,const sommet& S2)
{
    return(sommet(S1.Sx-S2.Sx, S1.Sy-S2.Sy, S1.idx));
}

sommet operator * (const sommet& S,const long double& a)
{
    return sommet(S.Sx*a,S.Sy*a,S.idx);
}

sommet operator / (const sommet& S,const long double& a)
{
    if(a==0) cout<<"! division par 0 "<<S<<endl;
    return sommet(S.Sx/a,S.Sy/a,S.idx);
}

bool sommet::operator == (const sommet &S) const
{
    return ((S.Sx==Sx) && (S.Sy==Sy) && (S.idx==idx));
}
// ----------------------------------------------------------------------------------------------//

//implementation de la classe segment :
// ------------------------------------------------------------------------------------------------
segment::segment(const sommet& A, const sommet& B) {
    deb=A;
    fin=B;
}

long double segment::longueur()const{
    return sqrt(pow(deb.Sx-fin.Sx,2) + pow(deb.Sy-fin.Sy,2));
}

sommet segment::normal()const{// normale au segment
    long double Nx=(fin-deb).Sy;
    long double Ny=(deb-fin).Sx;
    sommet O=0;
    sommet N(Nx, Ny,deb.idx);
    segment nor=segment(O,N);
    if(N==sommet()) cout<<"segment("<<deb<<","<<fin<<endl;
    return N/nor.longueur();
}

bool segment::intersects_segment(const segment& seg_obs)const{ //true : il y a intersection

    long double eps=1e-10; //erreur

    sommet U=(fin-deb)/longueur(), V=normal(); //nouvelle base

    //les extremites du segment *this dans la nouvelle base :
    sommet A,B;
    A=sommet(produit_scalaire(deb,U), produit_scalaire(deb,V));
    B=sommet(produit_scalaire(fin,U), produit_scalaire(fin,V));

    //les extremites du segment seg_obs dans la nouvelle base :
    sommet A_obs,B_obs;
    A_obs=sommet(produit_scalaire(seg_obs.deb,U), produit_scalaire(seg_obs.deb,V));
    B_obs=sommet(produit_scalaire(seg_obs.fin,U), produit_scalaire(seg_obs.fin,V));

    //calcul des coordonnées x,y du point d'intersection des droites :
    long double y=A.Sy, alpha=(A_obs.Sx-B_obs.Sx)/(A_obs.Sy-B_obs.Sy),
    c=(A_obs.Sx*B_obs.Sy-A_obs.Sy*B_obs.Sx)/(B_obs.Sy-A_obs.Sy),
    x=alpha*y+c, signe=(A_obs.Sy-B_obs.Sy)/abs(A_obs.Sy-B_obs.Sy);

    if( ( min(A_obs.Sy,B_obs.Sy) <= y ) && ( y <= max(A_obs.Sy,B_obs.Sy) ) &&
        ( min(A.Sx,B.Sx)         <= x ) && ( x <= max(A.Sx,B.Sx)       ) )     return true ;

    return false;
}

ostream& operator << (ostream& out, const segment& seg)
{
    out<<"["<<seg.deb<<","<<seg.fin<<"]";
    return out;
}
// ----------------------------------------------------------------------------------------------//

//implementation de la classe obstacle :
// ------------------------------------------------------------------------------------------------
obstacle::obstacle(const vector<sommet>& _sommets):sommets(_sommets){
    auto n=sommets.size();
    for(int i=0;i<n;i++){
        sommet A=sommets[i];
        sommet B=sommets[(i+1)%n];
        segment arete(A,B);
        normales.push_back(arete.normal());
    }
}

vector<int> obstacle::position(const segment& seg) const { // seg est un segment A,B
    long double eps=1e-10; //erreur
    vector<int> pos={-1,-1}; //initialisation
    auto n=sommets.size();

    // chercher les points du bord
    for (int i=0 ; i<n ; i++ )
    {
        if ( (fabs(seg.deb.Sx-sommets[i].Sx)<eps) && (fabs(seg.deb.Sy-sommets[i].Sy)<eps) ) pos[0]=i; // A sur le bord
        if ( (fabs(seg.fin.Sx-sommets[i].Sx)<eps) && (fabs(seg.fin.Sy-sommets[i].Sy)<eps) ) pos[1]=i; // B sur le bord

    }
    if ( (pos[0]>=0) && (pos[1]>=0) ) return pos ; //les 2 points sont au bord


    // chercher les points extérieurs
    for (int i=0 ; i<n ; i++ )
    {
        segment seg_obs = segment(sommets[i], sommets[(i+1)%n]);
        sommet normale_obs=seg_obs.normal();

        sommet A_vecteur = seg.deb-sommets[i]; // vecteur S_i,A
        sommet B_vecteur = seg.fin-sommets[i]; // vecteur S_i,B

        if( (produit_scalaire(A_vecteur,normale_obs)>eps) && (pos[0]==-1) ) pos[0]=-2 ; // on considère les points du bord non-sommets comme intérieurs
        if( (produit_scalaire(B_vecteur,normale_obs)>eps) && (pos[1]==-1) ) pos[1]=-2 ; // meme commentaire
    }
    return pos;
}

bool obstacle::intersect(const segment& seg)const
{
    auto n=sommets.size();
    vector<int> pos= position(seg);

    if ( (pos[0]==-1) || (pos[1]==-1) )  return true ; // un point est interieur

    if ( (pos[0]>=0) && (pos[1]>=0) ) // les 2 points sont au bord
    {
        int idx=pos[0];
        segment prec(seg.deb,sommets[(n+idx-1)%n]), suiv(seg.deb,sommets[(idx+1)%n]) ;
        return !(sont_alignes(seg.deb,seg.fin,sommets[(n+idx-1)%n]) || sont_alignes(seg.deb,seg.fin,sommets[(idx+1)%n]) );
    }

    if ( (pos[0]==-2) && (pos[1]==-2) ) // les deux points sont extérieurs
    {
        for(int counter=0 ; counter<n ; counter++)
        {
            segment seg_obs0(sommets[counter],sommets[(counter+1)%n]);
            if (seg.intersects_segment(seg_obs0)) return true;
        }
    }
    if ( ( (pos[0]==-2) && (pos[1]>=0) ) || ( (pos[1]==-2) && (pos[0]>=0) ) ) // un point est a l'exterieur strict, l'autre est sur le bord
    {
        int index=pos[1]*(pos[1]>=0) + pos[0]*(pos[0]>=0); // position du point au bord
        //on verifie que seg ne coupe aucun segment de l'obstacle
        for (int j=0; j<n ; j++)
        {
            if ( (index!=j) && (index!=(j+1)%n) )
            {
                segment seg_obs1(sommets[j],sommets[(j+1)%n]);
                if (seg.intersects_segment(seg_obs1)) return true ;
            }
        }
    }

    return false;
}

ostream& operator << (ostream& out, const vector<sommet>& sommets)
{
    out<<"[";
    for (int i = 0; i < sommets.size(); i++) {
        out<<"["<<sommets[i].Sx<<","<<sommets[i].Sy<<"]";
        if(i<(sommets.size()-1)) out<<",";
    }
    out<<"]";
    return out;
}

istream& operator >> (istream& in, vector<sommet>& sommets)
{
    long double x, y; string line; //variables intermédiaires
    while (getline(in, line)) { // Lecture de chaque ligne
        if (line=="STOP") break; // les éléments (objet/obstacles) sont séparés par une ligne STOP
        stringstream ss(line); ss >> x >> y; // Lecture des nombres de la ligne
        sommets.push_back(sommet(x, y)); // ajouter le sommet a l'objet
    }
    return in;
}
// ----------------------------------------------------------------------------------------------//

//implementation de la classe arc :
// ------------------------------------------------------------------------------------------------
arc::arc(sommet A, sommet B){
    deb=A;
    fin=B;
    segment seg=segment(A,B);
    int positif=(A.idx>B.idx)*(n_rot+B.idx-A.idx) + (A.idx<B.idx)*(B.idx-A.idx);
    int negatif=(B.idx>A.idx)*(n_rot+A.idx-B.idx) + (B.idx<A.idx)*(A.idx-B.idx);
    longueur=seg.longueur()+( (A.sens>0)*positif + (A.sens<0)*negatif )*cout_tour;
}

ostream& operator << (ostream& out,const arc& arc_){
    out<<"["<<arc_.deb<<","<<arc_.fin<<","<<arc_.longueur<<"]";
    return out;
}
// ----------------------------------------------------------------------------------------------//

//implementation de la classe graphe :
// ------------------------------------------------------------------------------------------------
graphe::graphe(const vector<vector<obstacle>>& layers_obs, const sommet& point_depart, const sommet& point_arrivee) {
    //ajout des points de depart et d'arrivee
    ajouter_noeud(point_depart);
    ajouter_noeud(point_arrivee);

    //ajout des sommets des obstacles
    for(int k=0; k<n_rot;k++) // boucle sur les layers
    {
        for(const auto& obs : layers_obs[k]) // boucles sur les obstacles dans un layer k
        {
            for(const auto& S : obs.sommets)
            {
                ajouter_noeud(S);
            }
        }
    }

    ofstream f_noeuds;f_noeuds.open("../../SIM202_Data"+Exemple+"/noeuds.txt");f_noeuds<<noeuds;f_noeuds.close();

    //ajout des arcs possibles :
    ///auto end = chrono::high_resolution_clock::now();auto time_taken = (long double)chrono::duration_cast<chrono::nanoseconds>(end - end).count();
    for(int i=0; i< noeuds.size(); i++)
    {
        for(int j =0;j<noeuds.size();j++)
        {
            ///auto start = chrono::high_resolution_clock::now(); //pour l'estimation du temps de calcul

            int i_idx=noeuds[i].idx, j_idx = noeuds[j].idx;

            if( (j>i) && (i_idx==j_idx) && !(noeuds[i]==noeuds[j]) ) // deux sommets (différents) dans le meme layer
            {
                vector<obstacle> obstacles = layers_obs[j_idx];

                int B3=0;
                for(const auto& obs:obstacles)
                {
                    if(obs.intersect(segment(noeuds[i],noeuds[j])))
                    {
                        B3=1;
                        break;
                    }
                }

                if(!B3) ajouter_arc(arc(noeuds[i],noeuds[j]));
            }

            if( (i_idx!=j_idx) && ((noeuds[i].Sx != noeuds[j].Sx) || (noeuds[i].Sy != noeuds[j].Sy)) ) // deux sommets (différents) dans deux layers différents
            {
                int B3_positif=0, B3_negatif=0;

                // l'objet peut tourner dans la position noeuds[i] :
                for(int k=i_idx ; k!=j_idx ; k=(k+1)%n_rot) // dans le sens positif
                {
                    vector<obstacle> obstacles = layers_obs[k];
                    for(const auto& obs:obstacles)
                    {
                        if(obs.position(segment(noeuds[i],sommet()))[0]==-1) // le sommet i est intérieur à un obstacle
                        {
                            B3_positif=1;
                            break;
                        }
                    }
                    if(B3_positif) break;
                }
                for(int k=i_idx ; k!=j_idx ; k=(n_rot+k-1)%n_rot) //dans le sens negatif
                {
                    vector<obstacle> obstacles = layers_obs[k];
                    for(const auto& obs:obstacles)
                    {
                        if(obs.position(segment(noeuds[i],sommet()))[0]==-1) // le sommet i est intérieur à un obstacle
                        {
                            B3_negatif=1;
                            break;
                        }
                    }
                    if(B3_negatif) break;
                }

                // l'objet peut translater de noeuds[i] à noeuds[j] dans le layer j_idx :
                vector<obstacle> obstacles = layers_obs[j_idx];
                for(const auto& obs:obstacles)
                {
                    if(obs.intersect(segment(noeuds[i],noeuds[j])))
                    {
                        B3_positif=1; B3_negatif=1;
                        break;
                    }
                }

                // verification et ajout du (meilleur) arc :
                if(!(B3_positif) && !(B3_negatif))
                {
                    arc arc_positif(noeuds[i],noeuds[j]), arc_negatif(sommet(noeuds[i].Sx,noeuds[i].Sy,noeuds[i].idx,-1),noeuds[j]);

                    if(arc_positif.longueur<arc_negatif.longueur) ajouter_arc(arc_positif);
                    else ajouter_arc(arc_negatif);
                }
                else
                {
                    if(!B3_positif) ajouter_arc(arc(noeuds[i],noeuds[j]));
                    if(!B3_negatif) ajouter_arc(arc(sommet(noeuds[i].Sx,noeuds[i].Sy,noeuds[i].idx,-1),noeuds[j]));
                }
            }

                ///pour l'estimation du temps de calcul :
            /*auto end = chrono::high_resolution_clock::now();int k=(j+1)+i*noeuds.size();
            time_taken=(long double)time_taken*(k-1)+ (long double)chrono::duration_cast<chrono::nanoseconds>(end - start).count();time_taken=(long double)time_taken/k;
            cout << "Time taken by program is : " << fixed
                         << time_taken*1e-9 << setprecision(9); cout<<"sec"<<endl;*/
        }
    }
}

void graphe::ajouter_noeud(const sommet& N){
    noeuds.push_back(N);
}

void graphe::ajouter_arc(const arc& A){
    arcs.push_back(A);
}

int graphe::voisins(sommet A, sommet B) const
{
    for(auto arc_i : arcs)
    {
        if ((arc_i.deb==A)&&(arc_i.fin==B)) return arc_i.deb.sens; // 'A -> B' arc
        if ((arc_i.deb==B)&&(arc_i.fin==A)&&(A.idx==B.idx)) return 1; // meme layer => 'B -> A' arc
    }
    return 0;
}

ostream& operator << (ostream& out,const graphe& graphe_){
    out<<"[";
    auto n=graphe_.arcs.size();
    for(int i=0; i<(n-1) ; i++){
        out<<graphe_.arcs[i]<<",";
    }
    out<<graphe_.arcs[n-1]<<"]";
    return out;
}
// ----------------------------------------------------------------------------------------------//

//implementation des fonctions :
// ------------------------------------------------------------------------------------------------
bool sont_alignes(const sommet& A, const sommet& B, const sommet& C) {
    long double aire = (B.Sx - A.Sx) * (C.Sy - A.Sy) - (C.Sx - A.Sx) * (B.Sy - A.Sy);
    return (aire == 0);
}

vector<sommet> to_convex(const vector<sommet>& sommets)
{
    //initialisation :
    long long i=0 ; auto n=sommets.size();
    vector<sommet> sommets_convex=sommets;
    while(i<n)
    {
        sommet A=sommets_convex[(n+i-1)%n];
        sommet I=sommets_convex[(n+i)%n];
        sommet B=sommets_convex[(n+i+1)%n]; // fixe
        while(non_convexes(segment(A,I),segment(I,B)))
        {
            sommets_convex.erase(sommets_convex.begin()+((n+i)%n)); //enlever sommet I
            if(i>=0) i--;
            n--;
            I=sommets_convex[(n+i)%n]; ///I=A;
            A=sommets_convex[(n+i-1)%n];
            //B=sommets_convex[(i+1)%n]; // fixe
        }
        i++;
    }

    return sommets_convex;
}

bool non_convexes(const segment& seg_prec,const segment& seg_suiv)
{
    sommet norm_prec=seg_prec.normal(), norm_suiv=seg_suiv.normal();
    return (determinant(norm_prec,norm_suiv)<0);
}

obstacle padding(const vector<sommet>& objet, const obstacle& obs)
{
// INPUT :
//      objet : l'objet qui se déplace. Le centre de gravité est le point qui définira la trajectoire
//      obs : l'obstacle sur lequel on fera le padding
// OUTPUT :
//      obs_modif : l'obstacle modifié avec la technique de padding

    int idx_layer=objet[0].idx; // numero de layer dans lequel on fait le padding
    vector<sommet> obj= to_convex(objet);
    sommet A(0,0,idx_layer);
    for (int i = 0; i <objet.size() ; i++) {
        A=A+(objet[i]/objet.size());
    }
    auto n=obj.size();

    obj.insert(obj.end(), obj.begin(), obj.end()); // obj se repete deux fois
    vector<sommet> S=obs.sommets;
    sommet ajout(0,0,idx_layer);

    // initialisation :
    sommet N_i = *(obs.normales.end()-1); // normale du dernier segment
    int idxPtProche_i,idxPtProche_precedent = trouverIdxPtProche(obj,N_i,*(S.end()-1));
    vector<sommet> S_modif={(A-obj[idxPtProche_precedent])+S[0]};

    //boucle sur les segments :
    for (int i = 0; i < S.size(); i++) {
        N_i=obs.normales[i];
        idxPtProche_i = trouverIdxPtProche(obj,N_i,S[i]);
        sommet S_modif_i=*(S_modif.end()-1);

        if(idxPtProche_i<idxPtProche_precedent) idxPtProche_i+=n; // pour que la boucle suivante ait un sens
        
        for (int j = idxPtProche_precedent + 1; j < (idxPtProche_i+1) ; j++) { // modification d'un coin
            ajout =(S_modif_i + obj[idxPtProche_precedent])- obj[j];

            // pour interdire trois points alignés (inutile de mettre le deuxième) :
            if(S_modif.size()>=2) if(sont_alignes(ajout,*(S_modif.end()-1),*(S_modif.end()-2))) S_modif.pop_back();

            S_modif.push_back(ajout);

        }

        ajout=(A-obj[idxPtProche_i])+S[(i+1)%S.size()];

        // pour interdire trois points alignés (inutile de mettre le deuxième) :
        if(S_modif.size()>=2) if(sont_alignes(ajout,*(S_modif.end()-1),*(S_modif.end()-2))) S_modif.pop_back();

        S_modif.push_back(ajout); // modification de S_i+1 (et donc du segment i)


        idxPtProche_precedent=idxPtProche_i; //mise a jour pour la prochaine itération
    }

    //construire l'obstacle apres padding :
    S_modif.pop_back();
    obstacle obs_modif(S_modif);

    return obs_modif;
}

vector<obstacle> padding_3D(const vector<sommet>& objet, const obstacle& obs)
{
    vector<obstacle> obs_modif={};
    for(int k=0 ; k<n_rot ; k++)
    {
        vector<sommet> objet_tourne= rotation(objet, k); // objet tourné d'un angle k*360/n_rot
        obs_modif.push_back(padding(objet_tourne,obs));
    }
    return obs_modif;
}

int trouverIdxPtProche(const vector<sommet>& obj, const sommet& N_i, const sommet& S_i )
{
    int idx = 0;
    for (int j = 0; j < obj.size(); j++) {
        long double distance_j = produit_scalaire(N_i,(obj[j]-S_i));// distance de obj[j] au segment
        long double distance_idx = produit_scalaire(N_i,(obj[idx]-S_i));// distance de obj[idx] au segment
        if(distance_j < distance_idx) idx=j;
    }
    return idx;
}

vector<sommet> Dijkstra(const graphe &G, const sommet &start, const sommet &end) {

    // definition des ensembles :

        // les noeuds :
    map<int,sommet> V = {}; // la totalité les noeuds
    map<int,sommet> S = {{1,start}}; // les noeuds parcourus
    map<int,sommet> T = {}; // les noeuds restants
        // les étiquettes :
    map<int,long double> l = {}; // les distances par rapport à start
    map<int,sommet> p = {}; // l'ensemble des 'noeud précédent'

    // initialisation :

    for(int compt=1;compt<=G.noeuds.size();compt++) V[compt]=G.noeuds[compt-1]; // la totalité les noeuds

    for (auto x : V) { // étiquettes initiales
        if (G.voisins(start,x.second)) { // 'x' voisin de 'start' => étiqueter 'x'
            l[x.first] = arc(sommet(start.Sx,start.Sy,start.idx,G.voisins(start,x.second)),x.second).longueur;
            p[x.first] = sommet(start.Sx,start.Sy,start.idx,G.voisins(start,x.second));
        }
        else // 'x' non voisin de 'start' => distance infinie
        {
            l[x.first] = 1000000;
            p[x.first]=start;
        }

        if (!(x.second==start)) T[x.first]=x.second; // les noeuds restants
    }

    // recherche du plus court chemin (de 'start' vers tous les noeuds) :

    while (T.size()>0) {
        //trouver 'i' l'index (dans 'T') du minimum de 'l' et retourner sa valeur 'min' = l[i]
        int i=T.begin()->first;
        long double min = l[T.begin()->first];
        map<int,sommet>::iterator it=T.begin();
        for (;it!=T.end();it++) {
            if (l[it->first]<=min)  {
                min=l[it->first];
                i=it->first;
            }
        }

        // déplacer le sommet i de T a S :
        S[i]=T[i];
        T.erase(i);

        // trouver les voisins (dans 'T') de S[i], le noeud actif
        map<int,sommet> J = {}; // l'ensemble des voisins
        for (auto x : T) {
            if (G.voisins(S[i],x.second))
                J[x.first]=sommet(x.second.Sx,x.second.Sy,x.second.idx,G.voisins(S[i],x.second));
        }

        // étiqueter les voisins de S[i] par 'S[i], l[i]+distance_i' si c'est mieux
        map<int,sommet>::iterator itr;
        for (itr=J.begin();itr!=J.end();itr++) {
            if (l[itr->first]>(l[i]+arc(sommet(S[i].Sx,S[i].Sy,S[i].idx,itr->second.sens),itr->second).longueur)) {
                p[itr->first]=sommet(S[i].Sx,S[i].Sy,S[i].idx,itr->second.sens);
                l[itr->first]=l[i]+arc(sommet(S[i].Sx,S[i].Sy,S[i].idx,itr->second.sens),itr->second).longueur;
            }
        }
    }

    vector<sommet> res = {end}; // initialisation du plus court chemin

    // output du plus court chemin (start -> end) :

    sommet _som = end;
    while (!(_som==start)) {
        int m = find_key(V,_som);
        res.insert(res.begin(),p[m]);
        _som = p[m];
    }
    return res;
}

int find_key(const map<int,sommet>& _map,const sommet& val) {
    for (auto itr : _map) {
        if (itr.second==val) return itr.first;
    }
    return -1;
}

vector<sommet> rotation(const vector<sommet>& obj, const int& k)
{
    sommet G_old(0,0);  // centre de gravité de l'objet initial
    for (int i = 0; i <obj.size() ; i++) {
        G_old=G_old+(obj[i]/obj.size());
    }

    vector<sommet> obj_rot;
    for(auto S : obj)
    {
        sommet S_centred=S-G_old;
        long double theta=2*M_PI*k/n_rot;
        sommet S_rot=sommet(cos(theta)*S_centred.Sx-sin(theta)*S_centred.Sy, sin(theta)*S_centred.Sx+cos(theta)*S_centred.Sy)+G_old;
        S_rot.idx=k;
        obj_rot.push_back(S_rot);
    }
    return obj_rot;
}
// ----------------------------------------------------------------------------------------------//