import subprocess

###############################################################################
# lecture du fichier svg

f_drawing=open('Drawing.sketchpad.svg','r')
for i in range(3) :
    f_drawing.readline()
    
line=f_drawing.readline().strip()
svg=[]
n_sommets_all=0
while(line!="</svg>") :
    # lecture des elements importants :
    elements=line.split("\"")
    if(' d=' in elements):
        sommets=elements[elements.index(' d=')+1].strip() 
        # traiter les sommets :
        for i in range(4):
            idx=sommets.find(' ')
            sommets=sommets[idx+1:]
    elif(' points=' in elements):
        sommets=elements[elements.index(' points=')+1].strip().replace(","," ")
    translation=elements[elements.index(' transform=')+1].strip()[6:] 

    # traiter la translation :
    translation=eval(translation)[-2:]    

    # translater les sommets :
    sommets_float=[ (-1)**i*(float(sommets.split(" ")[i]) + translation[i%2])
                   for i in range(len(sommets.split(" "))) ]
    sommets_str=[str(s) for s in sommets_float]
    sommets=' '.join(sommets_str)
    
    # ajouter les sommets translatés :
    svg.append(sommets)
    
    # mise a jour du nombre total de sommets :
    n_sommets_all+=len(sommets_float)
    
    line=f_drawing.readline().strip()
    
f_drawing.close() # sortie : 'svg'

###############################################################################
# lecture du fichier input existant

f=open('input.txt','r')

    # lecture de n_obs
n_obs=f.readline().strip() ; n_obs=int(n_obs)

    # lecture de obj
obj=[]
while(True):
    line=f.readline()
    if(line.strip()=="STOP") :
        break
    obj.append(line)
    # lecture des obstacles
obstacles=[]
for i in range(n_obs):
    obs=[]
    while(True):
        line=f.readline()
        if(line.strip()=="STOP") :
            break
        obs.append(line)
    obstacles.append(obs)
f.close() # sortie : 'n_obs', 'obj', 'obstacles'

#######################################################################
# lecture des nouveaux inputs (s'il y en a)

## si input='' --> on prend la valeur existante dans le fichier input.txt
## si input='svg' --> on prend la valeur dans le fichier svg
## si input='C' --> l'input est un cercle dont on définit la position et le rayon
## si input='STOP' --> on ne change pas le reste des valeurs du fichier input.txt
## si input=SVG' --> on prend toutes les valeurs restantes du fichier svg
### la taille n_obs doit etre cohérente dans le cas de lecture du fichier svg

n_svg=len(svg)
all_svg=''
compt_svg=0

    # input : n_obs
    ###############
n_obs_new=input("Le nombre d'obstacles = ").strip()
if(n_obs_new!=''):
    n_obs=int(n_obs_new)

    # input : obj
    #############
obj_new=input("L'objet : ").strip()
if(obj_new=='SVG'): #toutes les valeurs suivantes seront svg
    all_svg='SVG'
if ( (obj_new=='svg') | (all_svg=='SVG') ) : # si on prendra la valeur du svg
    obj_new=svg[compt_svg%n_svg]
    compt_svg+=1
if(obj_new=='C'):
    input_str=input('x = ')+"\n"+input("y = ")+"\n"+input("rayon = ")
    result = subprocess.run(['python', 'gener_cercle.py'],input=input_str.encode(), stdout=subprocess.PIPE)
    obj_new=result.stdout.decode().strip()
if(obj_new!=''): # si il y a modification
        ##format plusieurs lignes :
    obj=obj_new.split('\n')
    obj=[i+'\n' for i in obj]
        ## format une ligne :
    if(len(obj)==1): 
        obj_new=obj_new.split(' ')
        obj = [obj_new[0]+" "+obj_new[1]+"\n"]
        for i in range(2,len(obj_new),2):
            if ((obj_new[i],obj_new[i+1])==(obj_new[i-2],obj_new[i-1])):
                continue
            obj.append(obj_new[i]+" "+obj_new[i+1]+"\n")

        if(input("Sens de l'objet : ").strip()!="-") :
            obj = obj[::-1]

    # input : obstacles
    ###################
obs_new=""
for i in range(n_obs) :
    if(all_svg==''):
        obs_new=input("L'obstacle "+str(i+1)+" : ").strip()
    if(obs_new=='SVG'): #toutes les valeurs suivantes seront svg
        all_svg='SVG'
    if(obs_new=="STOP"): # arreter la modification
        break
    if ( (obs_new=='svg') | (all_svg=='SVG') ) : # si on prendra la valeur du svg
        obs_new=svg[compt_svg%n_svg]
        compt_svg+=1
    if(obs_new=='C'):
        input_str=input('x = ')+"\n"+input("y = ")+"\n"+input("rayon = ")
        result = subprocess.run(['python', 'gener_cercle.py'],input=input_str.encode(), stdout=subprocess.PIPE)
        obs_new=result.stdout.decode().strip()
    if(obs_new!=''): # si il y a modification
            ##format plusieurs lignes : --inutile en général--
        obs=obs_new.split('\n')
        if(i<len(obstacles)):
            obstacles[i]=[j+'\n' for j in obs]
        else :
            obstacles.append([j+'\n' for j in obs])
            ## format une ligne : 
        if(len(obs)==1): 
            obs_new=obs_new.split(' ')
            obs = [obs_new[0]+" "+obs_new[1]+"\n"]
            for j in range(2,len(obs_new),2):
                if ((obs_new[j],obs_new[j+1])==(obs_new[j-2],obs_new[j-1])):
                    continue
                obs.append(obs_new[j]+" "+obs_new[j+1]+"\n")
            if(input("Sens de l'obstacle "+str(i+1)+" : ").strip()!="-") :
                obstacles[i] = obs[::-1]
            else:
                obstacles[i]=obs

#####################################################################
    # mise a jour du fichier input.txt

f=open('input.txt','w')

f.write(str(n_obs)+'\n')
f.writelines(obj)
for i in range(n_obs):
    f.write("STOP\n")
    f.writelines(obstacles[i])
f.write("STOP")

f.close()