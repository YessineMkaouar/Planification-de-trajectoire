IL FAUT AVOIR MATLAB INSTALLE DANS SON PC POUR LANCER LA REPRESENTATION GRAPHIQUE 
DE CE PROJET !

CE PROJET A ETE REALISE PAR MOHAMED MKAOUAR, VIGINIE DAUL et ELIABELLE MAUDUIT 
A L'AIDE DE MATLAB ET DE C++.





********************** Si VOUS ETES UTILISATEUR		**************************************

1)Ouvrez le dossier "Pour utilisateur", puis cliquer sur l'application
"planification de trajectoire.exe"
2)après avoir selectionner le mode de planification de trajectoire
	- Si le mode choisi est 1,2,3,4,5 le remplissage des obstacles
	et des point d'entrée et de sortie sera automatique selon
	les cas tests prédéfinis par les développeurs
	- Si le mode choisi est 0, On vous donnera la main de faire
	remplissage vous même c'est à dire les coordonnées du point de départ,
	du point d'arrivée, et les coordonnèes des sommets de vos obstacles
	DANS LE SENS DIRECT (SENS CONTRAIRE DU MOUVEMENT DES AIGUILLES D'UNE MONTRE) 
	(Pour plus de details regarder la video tuto).
3)Le programme vous génèrera la trajectoire optimale.
4)Le programme vous demandera si vous vous voulez afficher la matrice du coût initiale
(coût demandé dans l'énoncé avec une valeur INFINI =9999)
5)Le programme vous demandera si vous vous voulez afficher la trajectoire qu'il faut suivre
sous cette forme :
(i1,i2) --> (j1,j2)
(j1,j2)	--> (k1,k2)
...
6)le programme va automatique ouvrir une nouvelle fenetre matlab (qu'on peut aussi y acceder à travers le dossier Matlab et puis le code se trouve dans "codeMatlab.m") ou bien aussi à gauche dans l'interface matlab qui s'affiche. 
7) cliquer sur run (et change folder s'il le demande)
8) Une figure va s'afficher où les obtacle sont colorié en jaune, le plus court chemin en rouge, et les arcs généré en noir.



******************* Si Vous êtes developpeur ou une personne interessé par le code ***********
1) Ouvrez le dossier "code du programme Planification de trajectoire"
2) Vous trouverez la dedans les differentes classes (fichiers .h et fichiers .cpp) avec des fonctions
 bien commentés
