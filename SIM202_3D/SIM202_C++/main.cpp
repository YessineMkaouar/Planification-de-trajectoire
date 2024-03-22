#include "trajectoire.hpp"

int main() {

    auto temps_debut = clock(); // initialisation du calcul de durée
    if (!Exemple.empty()) Exemple="/Exemples/"+Exemple;
    ifstream file("C:/Users/moham/Desktop/autres/yessine/Projects/2ATA/SIM/SIM202/SIM202_BOUGUILA_DZIRI_KHALFALLAH/SIM202_3D/SIM202_Data"+Exemple+"/input.txt"); // fichier contenant 'n_obs' puis les coordonnées de 'obj' et des 'obstacles' respectivement

    // lecture du nombre d'obstacles 'n_obs' :
    // ------------------------------------------------------------------------------------------------
    int n_obs; file>>n_obs;
    // ----------------------------------------------------------------------------------------------//

    // lecture de l'objet 'obj' :
    // ------------------------------------------------------------------------------------------------
    vector<sommet> obj;
    string line; getline(file,line); // passer la premiere ligne (vide)
    file>>obj;
    // ----------------------------------------------------------------------------------------------//

    // lecture et padding des n_obs obstacles :
    // ------------------------------------------------------------------------------------------------
    //initialisation
    vector<obstacle> obstacles; // les obstacles originaux (avant padding)
    vector<vector<obstacle>> layers_obstacles_modif={}; // les layers d'obstacles après padding.
    for(int k=0; k<n_rot ; k++)
    {
        vector<obstacle> vide={};
        layers_obstacles_modif.push_back(vide);
    }

    //boucle de lecture et padding
    for (int i = 0; i < n_obs; i++) { // Obstacle numéro i
            //lecture des sommets de l'obstacle i :
        vector<sommet> obs_sommets; // obstacles[i].sommets
        file>>obs_sommets;

            // à partir des sommets, construction et stockage de l'obstacle i ('obs') :
        obstacle obs(obs_sommets);
        obstacles.push_back(obs);
        obstacle obs_convex(to_convex(obs_sommets)); // on travaille avec l'obstacle rendu convex

            // padding de l'obstacle i et stockage :
        vector<obstacle> obs_modif = padding_3D(obj,obs_convex); // tous les layers de l'obstacle i
        for(int k=0 ; k<n_rot ; k++)
        {
            layers_obstacles_modif[k].push_back(obs_modif[k]);
        }
    }

    //affichage temps padding
    auto temps_padding = clock();
    auto duree=(temps_padding-temps_debut)/CLOCKS_PER_SEC;
    cout<<"Padding OK : "<<duree/3600<<"h "<<(duree%3600)/60<<"min "<<(duree%60)<<"s"<<endl;
    // ----------------------------------------------------------------------------------------------//

    file.close();

    // recherche du plus court chemin :
    // ------------------------------------------------------------------------------------------------
    vector<sommet> chemin ={depart,arrivee};
    if(!test_affich)
    {
        //construction graphe
        graphe G(layers_obstacles_modif,depart,arrivee);

        //affichage temps graphe
        auto temps_graphe = clock();
        duree=(temps_graphe-temps_padding)/CLOCKS_PER_SEC;
        cout<<"Graphe OK : "<<duree/3600<<"h "<<(duree%3600)/60<<"min "<<(duree%60)<<"s"<<endl;
        ofstream file_t; file_t.open("C:/Users/moham/Desktop/autres/yessine/Projects/2ATA/SIM/SIM202/SIM202_BOUGUILA_DZIRI_KHALFALLAH/SIM202_3D/SIM202_Data"+Exemple+"/output_Graphe.txt");file_t<<G;file_t.close();

        //calcul plus court chemin
        chemin= Dijkstra(G,depart,arrivee);

        //affichage temps chemin
        auto temps_chemin = clock();
        duree=(temps_chemin-temps_graphe)/CLOCKS_PER_SEC;
        cout<<"Chemin OK : "<<duree/3600<<"h "<<(duree%3600)/60<<"min "<<(duree%60)<<"s"<<endl;
    }
    // ----------------------------------------------------------------------------------------------//


    // output du programme dans un fichier (pour afficher la trajectoire avec python) :
    // ------------------------------------------------------------------------------------------------
    ofstream file_out; file_out.open("C:/Users/moham/Desktop/autres/yessine/Projects/2ATA/SIM/SIM202/SIM202_BOUGUILA_DZIRI_KHALFALLAH/SIM202_3D/SIM202_Data"+Exemple+"/output.txt"); // ouvrir le fichier

        //ecrire les choix :
    file_out<<n_rot<<endl<<test_affich<<endl<<z_obs<<endl;
        //ecrire le chemin :
    file_out<<chemin<<endl;
        //ecrire les layers des points :
    file_out<<"[";
    for(int i =0 ; (i<chemin.size()-1) ; i++)
    {
        file_out<<chemin[i].idx<<",";
    }
    file_out<<chemin[chemin.size()-1].idx<<"]"<<endl;
        //ecrire les sens de rotation (en sortant des points) :
    file_out<<"[";
    for(int i =0 ; (i<chemin.size()-1) ; i++)
    {
        file_out<<chemin[i].sens<<",";
    }
    file_out<<chemin[chemin.size()-1].sens<<"]"<<endl;
        // écrire l'objet :
    if(test_affich) file_out<<rotation(obj,z_obs)<<endl;
    else file_out<<obj<<endl;
        // écrire les obstacles avant et après padding (obstacle par obstacle)
    for (int i = 0; i < n_obs; i++) {
        file_out<<obstacles[i].sommets<<endl; //obstacle avant padding
        file_out<<layers_obstacles_modif[z_obs][i].sommets<<endl; //obstacle après padding
    }

    file_out.close();
    // ----------------------------------------------------------------------------------------------//

    auto temps_fin = clock();
    duree=(temps_fin-temps_debut)/CLOCKS_PER_SEC;
    cout<<"FIN PROGRAMME : "<<duree/3600<<"h "<<(duree%3600)/60<<"min "<<(duree%60)<<"s";
    return 0;
}
