/** \file jeu.h
 *	\brief Fonctions pour gérer le jeu
 */
#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
 * \fn static inline int modulo(int i, int m)
 * \brief Modulo modifié pour traiter correctement les bords i=0 et j=0 dans le calcul des voisins avec bords cycliques
 *
 * \param i Entier
 * \param m Entier
 *
 * \return Retourne le modulo amélioré
 */
static inline int modulo(int i, int m) { return (i + m) % m; }

/**
 * \fn void compte_voisins_vivants_cyclique(int i, int j, grille g)
 * \brief Compte le nombre de voisins vivants de la cellule (i,j) (les bords sont cycliques.)
 *
 * \param l Entier représentant le nombre de lignes que contient la grille.
 * \param c Entier représentant le nombre de colonnes que contient la grille.
 * \param g Grille concernée
 */
int compte_voisins_vivants_cyclique(int i, int j, grille g);

/**
 * \fn void compte_voisins_vivants_non_cyclique(int i, int j, grille g)
 * \brief Compte le nombre de voisins vivants de la cellule (i,j) (les bords sont non cycliques.)
 *
 * \param l Entier représentant le nombre de lignes que contient la grille.
 * \param c Entier représentant le nombre de colonnes que contient la grille.
 * \param g Grille concernée
 */
int compte_voisins_vivants_non_cyclique(int i, int j, grille g);

/**
 * \fn void evolue(grille* g, grille* gc, int (*compte_voisins_vivants) (int, int, grille))
 * \brief Fait évoluer la grille g d'un pas de temps
 *
 * \param g Pointeur sur la grille principal de l'état actuel
 * \param gc Pointeur sur une seconde grille qui contiendra l'évolution de g
 * \param compte_voisins_vivants Fonction de calcul des voisins vivants (cyclique ou non cyclique)
 * \param vieillissement Affiche ou non l'age des cellules
 */
void evolue(grille* g, grille* gc, int (*compte_voisins_vivants) (int, int, grille), int vieillissement);

#endif
