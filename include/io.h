/** \file io.h
 *	\brief Fonctions pour gérer les entrées et sorties
 */
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/**
 * \fn void affiche_trait(int c)
 * \brief Affichage d'un trait horizontal
 *
 * \param c Entier représentant le nombre de colonnes de longueur qu'aura le trait horizontal
 */
void affiche_trait(int c);

// 
/**
 * \fn void affiche_ligne(int c, int* ligne)
 * \brief Affichage d'une ligne de la grille
 *
 * \param c Entier représentant le nombre de colonnes de longueur qu'aura la ligne
 * \param ligne Poiteur sur un tableau d'entier contenant l'état des cellules de la ligne
 */
void affiche_ligne(int c, int* ligne);

/**
 * \fn void affiche_grille(grille g)
 * \brief Affichage d'une grille
 *
 * \param g Objet grille que l'on souhaite afficher
 */
void affiche_grille(grille g);

/**
 * \fn void efface_grille(grille g)
 * \brief Effacement d'une grille
 *
 * \param g Objet grille que l'on souhaite effacer
 */
void efface_grille(grille g);

/**
 * \fn void debut_jeu(grille* g, grille* gc)
 * \brief Démarrer le jeu
 *
 * \param g Pointeur sur la grille principale
 * \param gc Pointeur sur une seconde grill qui contient l'évolution de la première grille
 */
void debut_jeu(grille* g, grille* gc);

/**
 * \fn void charge_grille(grille* g, grille* gc, char* nom_fichier_grille)
 * \brief Charge une grille dans un fichier
 *
 * \param g Pointeur sur la grille dans laquelle doit être chargé les informations que contient le fichier nom_fichier_grille
 * \param gc Pointeur sur une seconde grille qui contient le même nombre de colonnes et lignes que la première grille et qui servira d'évolution de la première grille
 * \param nom_fichier_grille Nom du fichier contenant des informations sur une grille
 */
void charge_grille(grille* g, grille* gc, char* nom_fichier_grille);

#endif
