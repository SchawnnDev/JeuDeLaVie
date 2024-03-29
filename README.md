
# Jeu de la Vie
Ce projet est un devoir de la S3 Informatique à l'UFR Math/info de Strasbourg
Il traite sur le Jeu de la Vie, qui est un automate cellulaire, et est écrit en C.

# Installation
Pour installer le Jeu de la Vie sur votre ordinateur, veuillez suivre les instructions ci-dessous.

## Fichiers
Il faut tout d'abord télécharger la dernière version de ce projet, vous pouvez soit télécharger un fichier zip sur le gitlab ou procéder par un clone.
~~~{.sh}
git clone <lien>
~~~
La structure du projet se présente comme cela :

- bin/ => Dossier contenant l'exécutable
- dist/ => Dossier contenant les archives
- doc/ => Dossier contenant la documentation (doxygen)
- grilles/ => Dossier contenant les fichiers grilles
- include/ => Dossier contenant les fichiers d'entête
- lib/ => Dossier contenant la librairie
- obj/ => Dossier contenant les fichiers binaires
- src/ => Dossier contenant les fichiers sources
- Makefile => Fichier config Make
- Doxyfile => Fichier config Doxygen

## Compilation
### Prérequis

- Le compilateur C (gcc, MinGW pour Windows)
- Le programme Make
- Le programme Doxygen (pour la documentation)
- Le programme Tar (pour la génération d'archives)
- Pour le mode graphique, les librairies cairo et X11

### Générer l'exécutable

Le programme peut être compilé dans deux modes différents. Pour choisir ce mode il suffit de le préciser lors de l’exécution du makefile. Pour compiler le programme et générer l'exécutable il suffit d'exécuter la commande:
~~~{.sh}
make MODE=TEXTE # Affichage textuel dans la console
ou
make MODE=CAIRO # Affichage graphique dans une fenêtre
~~~
L’exécutable est générée dans le dossier bin/.

### Générer la documentation
Pour générer la documentation il suffit d'exécuter la commande:
~~~{.sh}
make doc
~~~
La documentation est générée avec le programme Doxygen, et crée le dossier doc/html/. Pour la consulter, il suffit d'ouvrir le fichier index.html avec un navigateur web (chrome, firefox, etc...)

### Générer une archive

Pour générer une archive il suffit d'exécuter la commande:
~~~{.sh}
make dist
~~~
L'archive est générée avec le programme Tar dans le dossier dist/.

### Nettoyer le projet

Pour nettoyer le dossier racine, et supprimer tout fichier généré par une compilation, il suffit d'exécuter la commande:
~~~{.sh}
make clean
~~~

# Utilisation
## Version texte
### Démarrage
Après avoir compilé le programme, l'exécutable à été générée dans le dossier bin/. 
Le programme a pour arguments, le nom du fichier de la grille, il suffit donc d'exécuter la commande:
~~~{.sh}
./bin/main nom_fichier_grille.txt
~~~

### Commandes
Lorsque l'application est démarrée il est possible d’exécuter des commandes.

- c => Activer/désactiver le comptage cyclique
- v => Activer/désactiver le vieillissement
- o => Vérifie si la colonie est oscillante et affiche le temps si c'est le cas
- n => Changer de grille
- q => Quitter le programme

### Evolution

Pour faire évoluer les cellules, il suffit d'appuyer sur la touche entrée. 

## Version graphique
### Démarrage
Après avoir compilé le programme, l'exécutable à été générée dans le dossier bin/. 
Le programme a pour arguments, le nom du fichier de la grille, il suffit donc d'exécuter la commande:
~~~{.sh}
./bin/main nom_fichier_grille.txt
~~~

Une fenêtre s'ouvrira et les instructions y seront notées.

### Commandes
Comme pour la version texte, il est possible d'exécuter des commandes qui sont ici, des touches à presser.

- touche c => Activer/désactiver le comptage cyclique
- touche  v => Activer/désactiver le vieillissement
- touche o => Vérifier si la colonie est oscillante et afficher le temps si c'est le cas
- touche n => Changer de grille
- clique droit souris => Quitter le programme

### Evolution

Pour faire évoluer les cellules, il suffit de faire un clique gauche sur la souris.

# Versions

Le programme se divise en 5 versions, elles sont toutes disponibles dans les tag du dépôt git.

Voici l'évolution de la partie graphique: 

![Evolution de la partie graphique du jeu de la vie](http://schawnndev.fr/files/gol_evolution.gif)