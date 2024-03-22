import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np
import matplotlib.animation as animation
import os
import streamlit as st  # Importation de la bibliothèque Streamlit pour la création de l'interface utilisateur

# paramètres de l'affichage :
###############################################################################
#Exemples=os.listdir("C:\Users\moham\Desktop\autres\yessine\Projects\2ATA\SIM\SIM202\SIM202_BOUGUILA_DZIRI_KHALFALLAH\SIM202_3D\SIM202_Data\Exemples") # Pour afficher tous les exemples
Exemples=["Exemple 4 - Copie"] # Liste des noms des dossiers des exemples a afficher (sinon vide)

n_discret_rot=320 # discretisation de la rotation dans le chemin
n_discret_translation = 320 # discretisation de la translation dans le chemin
hold=0.05 # temps d'attente entre les frames de l'animation (en ms)

# Calcul PPCM (on en aura besion pour l'affichage) :
###############################################################################
def decomp(n):
    L = dict()
    k = 2
    while n != 1:
        exp = 0
        while n % k == 0:
            n = n // k
            exp += 1
        if exp != 0:
            L[k] = exp
        k = k + 1
        
    return L

def _ppcm(a,b):
    Da = decomp(a)
    Db = decomp(b)
    p = 1
    for facteur , exposant in Da.items():
        if facteur in Db:
            exp = max(exposant , Db[facteur])
        else:
            exp = exposant
        
        p *= facteur**exp
        
    for facteur , exposant in Db.items():
        if facteur not in Da:
            p *= facteur**exposant
            
    return p

def ppcm(L):
    while len( L ) > 1:
        a = L[-1]
        L.pop()
        b = L[-1]
        L.pop()
        L.append( _ppcm(a,b) )
        
    return L[0]

# fonction qui fait la rotation de l'objet
###############################################################################
def rotate(obj,k) : 
    theta=2*np.pi*k/n_discret_rot
    Rot_matrix=np.array([[np.cos(theta),-np.sin(theta)],[np.sin(theta),np.cos(theta)]])
    
    G_old=np.sum(obj,axis=0)/len(obj) ## centre de l'objet initial
    
    return (obj-G_old).dot(Rot_matrix.T) + G_old

# préparation de l'affichage d'un exemple choisi
def affichage_exemple(Exemple):
    # lecture :
    ###########
    Exemple="/Exemples/"*(Exemple!="")+Exemple
    f = open('C:/Users/moham/Desktop/autres/yessine/Projects/2ATA/SIM/SIM202/SIM202_BOUGUILA_DZIRI_KHALFALLAH/SIM202_3D/SIM202_Data'+Exemple+'/output.txt')
    
        # lecture des choix :
    n_rot_calcul=int(f.readline().strip())
    test_affich=int(f.readline().strip())
    z_obs=int(f.readline().strip())
    
        # lecture du meilleur chemin :
    chemin = np.array(eval(f.readline().strip())) # points
    layers_chemin=np.array(eval(f.readline().strip()))*(n_discret_rot//n_rot_calcul) # layers
    sens_chemin=np.array(eval(f.readline().strip())) # sens de rotation
    
        # lecture de l'objet :
    obj = np.array(eval(f.readline().strip()))
    
        # lecture des obstacles avant et après padding :
    obs=[]
    obs_modif=[]
    for i,line in enumerate(f):
        if (i%2==0):
            obs.append(np.array(eval(line.strip())))
        else :
            obs_modif.append(np.array(eval(line.strip())))
        
    f.close()
    
    # préparation du chemin pour l'affichage (discrétisation) :
    ###########################################################
    dl = np.sum((chemin[0]-chemin[-1])**2)**0.5 / n_discret_translation; 
            # variation curviligne (pour régler la vitesse de déplacement)
    
    objet_rot_anim=[obj for i in range(int(hold*3000))] # la direction de l'objet en chaque point du chemin
    chemin_anim=[chemin[0] for i in range(int(hold*3000))] # l'ensemble des points du chemin
    for i in range(len(chemin)-1) :
        A = chemin[i] ; B = chemin[i+1]
        idx_A=layers_chemin[i] ; idx_B=layers_chemin[i+1]
        if (idx_A!=idx_B): # rotation dans A de idx_A a idx_B
            sens=sens_chemin[i]
            k=idx_A;
            while(k!=idx_B) :
                # ajout de l'objet tourné
                chemin_anim.append(list(A))
                objet_rot_anim.append(rotate(obj,k))
                k=(k+sens)%n_discret_rot
                
        if((B[0]-A[0])!=0) : # translation (droite non verticale)
            alpha = (B[1]-A[1])/(B[0]-A[0])           # pente de la droite AB
            c = (A[1]*B[0]-A[0]*B[1])/(B[0]-A[0])    # constante de la droite AB                             
            sens = np.sign(B[0]-A[0])                 # sens de déplacement dans la direction x
            dx = sens*dl/(1+alpha**2)**0.5            # variation suivant x
            
            x=A[0]                      # initialisation
            while(x*sens<B[0]*sens) :   # boucle le long du segment AB
                chemin_anim.append([x, alpha*x+c])
                objet_rot_anim.append(rotate(obj, idx_B))
                x+=dx
        else :  # translation (droite verticale)
            sens = np.sign(B[1]-A[1])                 # sens de déplacement dans la direction y
            dy = sens*dl                              # variation suivant y
            
            y=A[1]                      # initialisation
            while(y*sens<B[1]*sens) :   # boucle le long du segment AB
                chemin_anim.append([A[0], y])
                objet_rot_anim.append(rotate(obj, idx_B))
                y+=dy
    # hold a la fin :
    chemin_anim+=[chemin[-1] for i in range(int(hold*3000))]
    objet_rot_anim+=[obj for i in range(int(hold*3000))]
    
    return obj,obs,obs_modif,chemin_anim,objet_rot_anim,chemin

# affichage :
###############################################################################

    # figure et axe :
nombre=int(np.ceil(np.sqrt(len(Exemples))))
fig, axs = plt.subplots((len(Exemples)-1)//nombre+1,nombre)

chemin_anim_exp=[]
objet_rot_anim_exp=[]
G_exp=[]
point_exp=[]
patch_exp=[]
longueur_exp=[]
for exp in range(len(Exemples)) : # boucle sur les exemples
    Exemple=Exemples[exp]
    l=exp//nombre;c=exp%nombre # coordonnées
    if (len(Exemples)>2) :
        ax=axs[l,c]
    elif (len(Exemples)==2) :
        ax=axs[c]
    else :
        ax=axs
   
        #les elements relatifs a l'exemple
    obj,obs,obs_modif,chemin_anim,objet_rot_anim,chemin=affichage_exemple(Exemple)
    chemin_anim_exp.append(chemin_anim);objet_rot_anim_exp.append(objet_rot_anim);
    
    longueur_exp.append(len(chemin_anim))
    
        # création des polygones (pour l'affichage de l'objet et des obstacles) :
    obs_modif_polygon=[]
    obs_polygon=[]
    for i in range(len(obs)):
        obs_modif_polygon.append(patches.Polygon(obs_modif[i], linewidth=0.5,
                        edgecolor='k', linestyle =':', facecolor='none',zorder=1))
        obs_polygon.append(patches.Polygon(obs[i], linewidth=1, edgecolor='k',
                        facecolor='g',zorder=1))
        
        # ajout des éléments à l'axe (pour l'affichage) :
            
    ax.plot(chemin_anim[0][0], chemin_anim[0][1], 'x', color='r', markersize=7, linewidth=3,zorder=6) # depart       
    ax.plot(chemin_anim[-1][0], chemin_anim[-1][1], 'x', color='r', markersize=7, linewidth=3,zorder=6) # arrivee  
    
    ax.plot(chemin[:,0], chemin[:,1],color='r',linewidth=1.2, linestyle='-.',zorder=5) # chemin
    
    patch_exp.append(patches.Polygon(obj, linewidth=1, edgecolor='k', facecolor='r',
                            zorder=3)) ;ax.add_patch(patch_exp[exp]) # objet
    
    for i in range(len(obs)) : # les obstacles
        #ax.add_patch(obs_modif_polygon[i]) # obstacle avec padding
        ax.add_patch(obs_polygon[i]) # obstacle (original)
    
        # options d'affichage :
    ax.set_aspect('equal', 'datalim') # repère normé
    #ax.margins(0.1)
    
        # preparation pour l'animation :
    point, = ax.plot([], [], 'o', color='k', markersize=1.2,zorder=6) ; point_exp.append(point)
    G_exp.append(np.sum(obj,axis=0)/len(obj)) ## centre de gravité de l'objet
    
# l'animation :
###############################################################################
def init(exp):
        point_exp[exp].set_data([], [])
        return point_exp[exp],patch_exp[exp]
    
def animate(j,exp):
        i=j%longueur_exp[exp]
        obj_i=objet_rot_anim_exp[exp][i]-G_exp[exp]+chemin_anim_exp[exp][i]
        A_i=chemin_anim_exp[exp][i]
        patch_exp[exp].set_xy(obj_i)
        point_exp[exp].set_data(A_i[0],A_i[1])
        return point_exp[exp],patch_exp[exp]
    
def init_finale() :
    return tuple(init(exp)[0] for exp in range(len(Exemples)))+tuple(init(exp)[1] for exp in range(len(Exemples)))
def animate_finale(i) :
    return tuple(animate(i,exp)[0] for exp in range(len(Exemples)))+tuple(animate(i,exp)[1] for exp in range(len(Exemples)))

longueur=ppcm(longueur_exp.copy())
ani=animation.FuncAnimation(fig, animate_finale, longueur, init_func=init_finale,
                                  interval=hold, blit=True,repeat=True)

plt.show()
    ###############################################################################
    ###############################################################################



st.write("""
# Interface Graphique - Planification de trajectoire
## Projet SIM202
""")  # Affichage du titre et de la description de l'interface graphique

depart=(0,0)  # Initialisation du point de départ

with st.sidebar:
    pt_depart = st.text_input("Veuillez entrer le point de départ : ")  # Champ de saisie pour la taille de la population
    depart_submit_button = st.button(label="Entrer")  # Bouton de soumission pour la taille de la population
    if depart_submit_button :
        depart = pt_depart  # Mise à jour de la taille de la population si le bouton est cliqué

    pt_arrivee = st.text_input("Veuillez entrer le point d'arrivée : ")  # Champ de saisie pour le nombre d'itérations
    arrivee_submit_button = st.button(label="Entrer")  # Bouton de soumission pour le nombre d'itérations
    if arrivee_submit_button :
        arrivee = pt_arrivee # Mise à jour du nombre d'itérations si le bouton est cliqué

    from PIL import Image  # Importation de la bibliothèque PIL pour le traitement d'images
    img = Image.open("logo_enit.png")  # Chargement de l'image
    new_size = (500, 500)
    img = img.resize(new_size)  # Redimensionnement de l'image
    st.image(img, caption="ENIT", use_column_width=True)  # Affichage de l'image

option = st.selectbox(
    'Quelle map voulez-vous choisir ? 👇',
    ('Map 1', 'Map 2', 'Map 3'),
    index=None, 
    placeholder="Selectionnez une map...",) # Sélection de la map à afficher parmi les options disponibles

submit_button = st.button("Afficher la trajectoire optimale")  # Bouton de soumission

def generate_response(user_input, nb_pop, nb_iter):
    L = user_input.split()  # Conversion de la saisie utilisateur en liste d'entiers
    L = [int(x) for x in L]
    create_file(L=L, nbr_population=nb_pop, nbr_iteration=nb_iter)  # Création d'un fichier avec l'ensemble, la taille de la population et le nombre d'itérations
    response = run_genetic_algorithm()  # Exécution de l'algorithme génétique et récupération de la réponse
    return response

L1 = user_input.split()  # Séparation de la saisie utilisateur en liste d'éléments
compteur = 0
for element in L1:
    if element.isdigit() or (element[0] == '-' and element[1:].isdigit()):
        compteur += 1  # Comptage du nombre d'entiers dans la liste

compteur1 = 0
nombre_temporaire = ''


if submit_button:  # Si le bouton "Envoyer" est cliqué
    try:
        response = generate_response(user_input, int(nb_pop_input), int(nb_iter_input))  # Générer la réponse en utilisant la saisie utilisateur, la taille de population et le nombre d'itérations
        solution = generate_sequence(response)  # Générer la séquence à partir de la réponse
        fitness = calculate_sum(response)  # Calculer la somme de la réponse (fitness)
        st.write("La taille de l'ensemble de départ : ")
        st.write(compteur)  # Afficher la taille de l'ensemble initial
        st.write("La solution est : ")
        st.write(solution)  # Afficher la solution trouvée
        st.write("Résultat = {}".format(fitness))  # Afficher le résultat (fitness)

        for caractere in str(solution):
            if caractere.isdigit() or (caractere == '-' and nombre_temporaire == ''):
                nombre_temporaire += caractere  # Construire le nombre temporaire caractère par caractère
            elif nombre_temporaire:
                compteur1 += 1  # Comptage du nombre d'entiers dans la séquence
                nombre_temporaire = ''

        # Vérification pour le dernier nombre dans la chaîne
        if nombre_temporaire:
            compteur1 += 1

        st.write("Taille de l'ensemble trouvé : ")
        st.write(compteur1)  # Afficher la taille de l'ensemble trouvé
    except subprocess.CalledProcessError as e:
        st.write("Veuillez changer la taille de la population ou bien le nombre d'itérations.")  # Afficher un message d'erreur en cas d'erreur lors de l'exécution de l'algorithme génétique

img = Image.open("cover_enit.jpg")  # Chargement de l'image

st.image(img, caption="ENIT", use_column_width=True)  # Afficher l'image avec une légende