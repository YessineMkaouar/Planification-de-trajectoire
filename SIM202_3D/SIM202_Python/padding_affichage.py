import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np
import mpl_toolkits.mplot3d.art3d as art3d

Exemple="" # nom du dossier de l'exemple, sinon vide
z_graph=-1 # -1 : tous les arcs. sinon, le layer z_graph seulement
D2=0 # affichage en 2D (=1) ou 3D (=0)

D2=D2*(z_graph!=-1)
# lecture :
###############################################################################
Exemple="/Exemples/"*(Exemple!="")+Exemple
f = open('../SIM202_Data'+Exemple+'/output.txt', 'r')

    # lecture des choix :
n_rot_calcul=int(f.readline().strip())
test_affich=int(f.readline().strip())
z_obs=int(f.readline().strip())

    # lecture du meilleur chemin :
chemin = np.array(eval(f.readline().strip()))
layers_chemin=np.array(eval(f.readline().strip())) 
sens_chemin=np.array(eval(f.readline().strip())) # sens de rotation

    # lecture de l'objet :
obj = np.array(eval(f.readline().strip()))
A=np.sum(obj,axis=0)/len(obj) ## centre de gravité de l'objet

    # lecture des obstacles avant et après padding :
obs=[]
obs_modif=[]
for i,line in enumerate(f):
    if (i%2==0):
        obs.append(np.array(eval(line.strip())))
    else :
        obs_modif.append(np.array(eval(line.strip())))
    
f.close()

    # lecture du graphe :
f_graphe=open('../SIM202_Data'+Exemple+'/output_Graphe.txt', 'r')
graphe_ch=f_graphe.read()
graphe=eval(graphe_ch)
f_graphe.close()
###############################################################################
###############################################################################

# affichage :
###############################################################################

    # création des polygones (pour l'affichage de l'objet et des obstacles) :
obj_polygon = patches.Polygon(obj, linewidth=1, edgecolor='k', facecolor='r',zorder=2)
obs_modif_polygon=[]
obs_polygon=[]
for i in range(len(obs)):
    obs_modif_polygon.append(patches.Polygon(obs_modif[i], linewidth=1, edgecolor='k', linestyle =':', facecolor='none',zorder=2))
    obs_polygon.append(patches.Polygon(obs[i], linewidth=1, edgecolor='k', facecolor='g',zorder=2))

    # figure et axe :
if((test_affich)|(D2)):
    fig, ax = plt.subplots()
else :
    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')
    
    # ajout des éléments à l'axe (pour l'affichage) :
        
ax.plot(chemin[0][0], chemin[0][1], 'x', color='r', markersize=7, linewidth=3,zorder=6) # depart        
ax.plot(chemin[-1][0], chemin[-1][1], 'x', color='r', markersize=7, linewidth=3,zorder=6) #arrivee

if(D2): # le plus court chemin
    ax.plot(chemin[:,0], chemin[:,1],color='r',zorder=8) 
else:
    ax.plot(chemin[:,0], chemin[:,1],layers_chemin,color='r',zorder=8) 

ax.add_patch(obj_polygon) # l'objet
if(not((test_affich)|(D2))):
    art3d.pathpatch_2d_to_3d(obj_polygon,z=z_obs)
    
ax.scatter(A[0],A[1], color='k', s=1,zorder=7) # centre de l'objet

for i in range(len(obs)) : # les obstacles
    ax.add_patch(obs_modif_polygon[i])
    if(not((test_affich)|(D2))):
        art3d.pathpatch_2d_to_3d(obs_modif_polygon[i],z=z_obs)
    ax.add_patch(obs_polygon[i])
    if(not((test_affich)|(D2))):
        art3d.pathpatch_2d_to_3d(obs_polygon[i],z=z_obs)
    
if(not(test_affich)) : 
    for arc in graphe: # le graphe
        if((z_graph==-1)&(not(D2))):
            ax.plot3D([arc[0][0],arc[1][0]], [arc[0][1],arc[1][1]],[arc[0][2],arc[1][2]], color='b',markersize=1,zorder=7)
        elif ((arc[0][2]==z_graph) & (arc[1][2]==z_graph) & (not(D2))):
            ax.plot3D([arc[0][0],arc[1][0]], [arc[0][1],arc[1][1]],[arc[0][2],arc[1][2]], color='b',markersize=1,zorder=7)
        elif ((arc[0][2]==z_graph) & (arc[1][2]==z_graph) & D2):
            ax.plot([arc[0][0],arc[1][0]], [arc[0][1],arc[1][1]], color='b',markersize=1,zorder=7)

    # options d'affichage :
if(D2):
    ax.set_aspect('equal', 'datalim') # repère normé

###############################################################################
###############################################################################

plt.show()