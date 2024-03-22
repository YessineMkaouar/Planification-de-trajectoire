##################################################################
# Guide d'exécution du programme de planification de trajectoire #
##################################################################

Dans le cadre général, l'utilisateur a besoin de fournir un fichier `input.txt` `SIM202_3D\SIM202_Data\` et les paramètres de calcul (`depart`, `arrivee`, `n_rot` le nombre d'angles discrétisant un tour complet, `cout_tour` le coût en distance d'une rotation élémentaire, `test_affich`=0, `Exemple`="") dans le fichier `SIM202_3D\SIM202_C++\trajectoire.cpp`. Il exécutera par la suite les fichiers `SIM202_3D\SIM202_C++\main.cpp` et `SIM202_3D\SIM202_Python\affichage_anime.py` dans l'ordre afin d'obtenir le résultat souhaité. 

Pour des raisons pratiques, on fournit ici un guide pour la génération d'un bon INPUT, pour le test des différentes étapes du programme et pour un affichage un peu plus avancé.

RQ :
On pourra trouver plusieurs exemples déjà préparés dans le dossier "SIM202_3D\SIM202_Data\Exemples". Pour afficher tous ces exemples à la fois, il suffit d'exécuter `SIM202_3D\SIM202_Python\affichage_anime.py` avec le paramètre `Exemples` précisé.
Pour travailler avec l'un de ces exemples, il suffit de :
 - exécuter `SIM202_3D\SIM202_Python\affichage_anime.py` avec le paramètre `Exemples`=["NOM_DOSSIER"], si on veut afficher le résultat de cet exemple directement.
 - mettre le paramètre `Exemple`="NOM_DOSSIER" dans `SIM202_3D\SIM202_C++\trajectoire.cpp` et suivre les étapes 2 et 3, si on veut tester le calcul avant d'afficher son résultat.

1- Génération de l'INPUT :
##########################

Le programme prend en donnée le nombre d'obstacle, suivi des sommets de l'objet et des différents obstacles (il s'agit d'une discrétisation de l'objet/obstacle qui peut être de forme quelconque).

RQ1 : Un moyen simple de construire ces sommets serait de dessiner l'objet et l'obstacle sur le site `https://sketch.io/sketchpad/` (il est préférable de dessiner dans le sens de rotation horaire) et d'enregistrer le dessin en format SVG.

RQ2: On pourra se servir du fichier `gener_cercle.py` pour générer un cercle discrétisé. Ce fichier s'exécute de façon automatique si on écrit "C" comme donnée (voir le paragraphe suivant).

La génération de l'INPUT se fait en exécutant le fichier `gener_INPUT.py`. après avoir donné le nombre d'obstacles, plusieurs possibilités se présentent pour la donnée de l'objet et des obstacles:
	* On veut changer/ajouter la valeur manuellement : écrire les sommets sous la forme "x1 y1 x2 y2 ... xn yn"
	* On veut changer/ajouter la valeur par le moyen de `gener_cercle.py` : écrire "C" puis les paramètres du cercle
	* On veut changer/ajouter la valeur à partir du fichier SVG : écrire "svg"
	* On veut changer/ajouter toutes le valeurs suivantes à partir du fichier SVG : écrire "SVG"
	* On ne veut pas changer la valeur (par rapport à `ìnput.txt`) : appuyer sur la touche `Entrée`
	* On ne veut plus rien changer : écrire "STOP"
Dans les cas où on va changer la valeur, il faut indiquer le sens dans lequel les sommets sont ordonnées. Le sens est considéré horaire par défaut (dans ce cas appuyer sur la touche `Entrée`), si c'est pas le cas il faudra écrire "-".

2- Test du padding et choix du départ et de l'arrivée :
#######################################################

Avant de lancer le calcul du plus court chemin (nécessitant beaucoup de temps), il faut vérifier que le padding se fait de façon correcte (sinon corriger le sens des sommets) et choisir la position des points de départ et d'arrivée. Pour ce faire, il suffit d'exécuter le fichier `SIM202_3D\SIM202_C++\main.cpp` en ayant choisi le paramètre `test_affich`=1 et ensuite afficher les obstacles en exécutant le fichier `SIM202_3D\SIM202_Python\padding_affichage.py`.

3- Génération de l'OUTPUT et affichage :
########################################

Afin de générer l'OUTPUT, il suffit d'exécuter le fichier `SIM202_3D\SIM202_C++\main.cpp` avec le paramètre `test_affich`=0 et ensuite le fichier `SIM202_3D\SIM202_Python\affichage_anime.py` afin de visualiser la trajectoire de l'objet (de façon animée).
On pourra également visualiser le graphe construit en exécutant le fichier `SIM202_3D\SIM202_Python\padding_affichage.py`.