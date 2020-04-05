/** \file io.h
 *	\brief Fonctions pour gérer les entrées et sorties
 */
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

#if MODECAIRO

#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

	#define SIZEX 1050
	#define SIZEY 500

 /*
  * Sources: https://www.cypherpunk.at/files/2014/11/cairo_xlib_simple.c
  * \fn cairo_surface_t* cairo_create_x11_surface0(int x, int y)
  * \brief Ouvre une fenêtre X11 ete crée la surface de base cairo sur cette fenêtre
  * 
  * \param x Largeur de la fenêtre
  * \param y Hauteur de la fênetre
  * 
  * \return Retourne un pointeur vers une surface Xlib cairo valid.
  */
cairo_surface_t* cairo_create_x11_surface0(int x, int y);

/*
 * \fn void cairo_close_x11_surface()
 * \brief Detruit la surface cairo XLib et ferme la connection X.
 */
void cairo_close_x11_surface();

/**
 * \fn void affiche_trait(int c)
 * \brief Affichage d'un trait horizontal
 *
 * \param c Entier représentant le nombre de colonnes de longueur qu'aura le trait horizontal
 * \param cellHeight Hauteur d'une cellule du tableau
 */
void affiche_trait(int c, double cellHeight);

// 
/**
 * \fn void affiche_ligne(int c, int* ligne)
 * \brief Affichage d'une ligne de la grille
 *
 * \param c Entier représentant le nombre de colonnes de longueur qu'aura la ligne
 * \param cellWidth Largeur d'une cellule du tableau
 */
void affiche_ligne(int c, double cellWidth);

/*
 * \fn void affiche_texte(int tempsEvolution, int voisinageCyclique, int vieillissement)
 * \brief Affichage du texte sur la fenetre cairo
 * \param tempsEvolution Le temps d'évolution de la grille
 * \param voisinageCyclique Activer ou désactiver le voisinage cyclique
 * \param vieillissement Affiche ou non l'age des cellules
 * \param tempsOscillation Pas de temps par oscillation
 */
void affiche_texte(int tempsEvolution, int voisinageCyclique, int vieillissement, int tempsOscillation);

/**
 * \fn void affiche_grille(grille g)
 * \brief Affichage d'une grille
 *
 * \param g Objet grille que l'on souhaite afficher
 * \param vieillissement Affiche ou non l'age des cellules
 */
void affiche_grille(grille g, int vieillissemnt);

/**
 * \fn char* concat(const char* s1, const char* s2)
 * \brief Concatène deux chaînes de caractères ensemble (ne pas oublier de free après utilisation)
 *
 * \param s1 Première chaîne de caractères
 * \param s1 Deuxième chaîne de caractères
 * \return Les deux chaînes de caractères concactenés
 */
char* concat(const char* s1, const char* s2);

/**
 * \fn void drawTextInput(char* input, char* error)
 * \brief Affichage d'une zone d'input pour le changement de grille
 *
 * \param input Chaine de caractères contenant un input
 * \param error Chaine de caractères contenant une erreur
 */
void drawInputZone(char* input, char* error);

#else

 /**
  * \fn void affiche_trait(int c)
  * \brief Affichage d'un trait horizontal
  *
  * \param c Entier représentant le nombre de colonnes de longueur qu'aura le trait horizontal
  */
void affiche_trait(int c);

/**
 * \fn void affiche_ligne(int c, int* ligne)
 * \brief Affichage d'une ligne de la grille
 *
 * \param c Entier représentant le nombre de colonnes de longueur qu'aura la ligne
 * \param ligne Poiteur sur un tableau d'entier contenant l'état des cellules de la ligne
 * \param vieillissement Affiche ou non l'age des cellules
 */
void affiche_ligne(int c, int* ligne, int vieillissement);

/**
 * \fn void affiche_grille(grille g)
 * \brief Affichage d'une grille
 *
 * \param g Objet grille que l'on souhaite afficher
 * \param tempsEvolution Le temps d'évolution de la grille
 * \param voisinageCyclique Activer ou désactiver le voisinage cyclique
 * \param vieillissement Affiche ou non l'age des cellules
 * \param tempsOscillation Pas de temps par oscillation
 */
void affiche_grille(grille g, int tempsEvolution, int voisinageCyclique, int vieillissement, int tempsOscillation);

#endif

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

#endif