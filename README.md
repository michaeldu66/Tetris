optimisation de code à faire:

pour l'ia dans la recherche de la meilleure position :
implementer tout le bordel avec le conteneur priority_queue + itérateur 
associé (mieux que ce qu'on a mis en place au début)


Fonctionnalité à faire (par ordre de priorité):

-ajouter le Hold et les nexts pièces(3 comme dans le vrai jeu)

-ajouter la fonctionnalité LEVELS : toutes les 10 lignes on augmente
le level (augmente la vitesse de descente des pièces)

-ajouter l'option LEVELS dès le début du jeu quand on commence une partie
(qui initialisera direct la vitesse des pièces)

-ajouter le déplacement lattérale durant le moment ou le tetrimino est 
presque en position finished (genre un timer avant d'enclencher le finish quand on arrive
à une bordure serait pas mal).

-fonction pour l'IA : faire une fonction qui compte le nombre de trous
et ajouter la condition sur le nombre de trous minimum (en plus du score max) 
pour prioriser telle ou telle fonnctionnalités
==> j'ai une idée pour coder la fonction de trous je le fais viteuf ce soir (10/03)

-ajouter le mode multijoueur contre l'IA : il faut séparé entre plusieurs fenêtres
la fenetre du joueur et celle de l'IA

-ajouter un bouton pour couper le son et le mettre pck ça casse les couilles 
d'écouter la musique h24.



OPTIONNELS 

-ajouter le mode multijoueur tout court contre qqn d'autre

-faire le mode réseau du jeu (reseau local ou en wifi), ya une librairies sdl pour 
ça