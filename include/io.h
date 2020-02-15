﻿/** \file io.h
 *	\brief Fonctions pour gérer les entrées et sorties
 */
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/**
 * <p>affichage d'un trait horizontal</p>
 */
void affiche_trait(int c);

// affichage d'une ligne de la grille
void affiche_ligne(int c, int* ligne);

// affichage d'une grille
void affiche_grille(grille g);

// effacement d'une grille
void efface_grille(grille g);

// debute le jeu
void debut_jeu(grille* g, grille* gc);

// charge une grille dans un fichier
void charge_grille(grille* g, grille* gc, char* nom_fichier_grille);

#endif
