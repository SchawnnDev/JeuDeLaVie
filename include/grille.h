/** \file grille.h
 *	\brief Fonctions pour gérer les grilles de cellules
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * \struct grille
 * \brief Objet grille
 *
 * Structure de la grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
 */
typedef struct
{
	int nbl; /*!< Entier représentant le nombre de lignes que contient la grille. */
	int nbc; /*!< Entier représentant le nombre de colonnes que contient la grille. */
	int** cellules; /*!< Pointeur d'un pointeur sur un tableau à deux entrées contenant une valeur pour chaque case de la grille */
} grille;

/**
 * \fn void alloue_grille (int l, int c, grille* g)
 * \brief Alloue une grille de taille l*c, et initialise toutes les cellules à mortes
 *
 * \param l Entier représentant le nombre de lignes que contient la grille.
 * \param c Entier représentant le nombre de colonnes que contient la grille.
 * \param g Pointeur sur la grille concernée
 */
void alloue_grille(int l, int c, grille* g);

/**
 * \fn void libere_grille (grille* g)
 * \brief Libère la grille g.
 *
 * \param g Pointeur sur la grille concernée
 */
void libere_grille(grille* g);

/**
 * \fn int init_grille_from_file(char* filename, grille* g)
 * \brief Initialise une grille en chargeant un fichier grille.txt
 *
 * \param filename Pointeur sur une chaîne contenant le nom du fichier de la grille
 * \param g Pointeur sur la grille concernée
 * \return S'il y'a une erreur ou pas
 */
int init_grille_from_file(char* filename, grille* g);

/**
 * \fn static inline void set_vivante(int i, int j, grille g)
 * \brief Rend vivante la cellule (i,j) de la grille g
 *
 * \param i Entier représentant le numéro de la ligne de la cellule
 * \param j Entier représentant le numéro de la colonne de la cellule
 * \param g Grille concernée
 */
static inline void set_vivante(int i, int j, grille g) { g.cellules[i][j] = 1; }

/**
 * \fn static inline void set_morte(int i, int j, grille g)
 * \brief Rend morte la cellule (i,j) de la grille g
 *
 * \param i Entier représentant le numéro de la ligne de la cellule
 * \param j Entier représentant le numéro de la colonne de la cellule
 * \param g Grille concernée
 */
static inline void set_morte(int i, int j, grille g) { g.cellules[i][j] = 0; }

/**
 * Rend non-viable la cellule (i,j) de la grille g
 * @param[in]  i Ligne de la cellule
 * @param[in]  j Colonne de la cellule
 * @param[out] g Grille
 */
static inline void set_non_viable(int i, int j, grille g) { g.cellules[i][j] = -1; }

/**
 * \fn static inline int est_vivante(int i, int j, grille g)
 * \brief Teste si la cellule (i,j) de la grille g est vivante
 *
 * \param i Entier représentant le numéro de la ligne de la cellule
 * \param j Entier représentant le numéro de la colonne de la cellule
 * \param g Grille concernée
 *
 * \return Retourne un entier 1 si la cellule est vivante et un 0 si elle ne l'est pas
 */
static inline int est_vivante(int i, int j, grille g) { return g.cellules[i][j] >= 1; }

/**
 * \fn static inline int est_viable(int i, int j, grille g)
 * \brief Teste si la cellule (i,j) de la grille g est viable
 *
 * \param i Entier représentant le numéro de la ligne de la cellule
 * \param j Entier représentant le numéro de la colonne de la cellule
 * \param g Grille concernée
 *
 * \return Retourne un entier 1 si la cellule est viable et un 0 si elle ne l'est pas
 */
static inline int est_non_viable(int i, int j, grille g) { return g.cellules[i][j] == -1; }

/**
 * \fn void copie_grille(grille gs, grille gd)
 * \brief Recopie la grille gs dans la grille gd (sans allocation)
 *
 * \param gs Objet grille source
 * \param gd Objet grille destination
 */
void copie_grille(grille gs, grille gd);

#endif
