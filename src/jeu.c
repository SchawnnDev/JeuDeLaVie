#include "jeu.h"

int compte_voisins_vivants_cyclique(int i, int j, grille g)
{
	int v = 0, l = g.nbl, c = g.nbc;
	v += est_vivante(modulo(i - 1, l), modulo(j - 1, c), g);
	v += est_vivante(modulo(i - 1, l), modulo(j, c), g);
	v += est_vivante(modulo(i - 1, l), modulo(j + 1, c), g);
	v += est_vivante(modulo(i, l), modulo(j - 1, c), g);
	v += est_vivante(modulo(i, l), modulo(j + 1, c), g);
	v += est_vivante(modulo(i + 1, l), modulo(j - 1, c), g);
	v += est_vivante(modulo(i + 1, l), modulo(j, c), g);
	v += est_vivante(modulo(i + 1, l), modulo(j + 1, c), g);

	return v;
}

int compte_voisins_vivants_non_cyclique(int i, int j, grille g)
{
	int v = 0, l = g.nbl, c = g.nbc;

	v += (i - 1 >= 0 && j - 1 >= 0) ? est_vivante(i - 1, j - 1, g) : 0;
	v += (i - 1 >= 0) ? est_vivante(i - 1, j, g) : 0;
	v += (i - 1 >= 0 && j + 1 < c) ? est_vivante(i - 1, j + 1, g) : 0;
	v += (j - 1 >= 0) ? est_vivante(i, j - 1, g) : 0;
	v += (j + 1 < c) ? est_vivante(i, j + 1, g) : 0;
	v += (i + 1 < l && j - 1 >= 0) ? est_vivante(i + 1, j - 1, g) : 0;
	v += (i + 1 < l) ? est_vivante(i + 1, j, g) : 0;
	v += (i + 1 < l && j + 1 < c) ? est_vivante(i + 1, j + 1, g) : 0;

	return v;
}

void evolue(grille* g, grille* gc, int (*compte_voisins_vivants)(int, int, grille), int vieillissement, int* tempsEvolution)
{
	copie_grille(*g, *gc); // copie temporaire de la grille
	int i, j, l = g->nbl, c = g->nbc, v;
	(*tempsEvolution)++;

	for (i = 0; i < l; i++)
	{
		for (j = 0; j < c; ++j)
		{

			if (est_non_viable(i, j, *g))
				continue;
			
			v = compte_voisins_vivants(i, j, *gc);
			if (est_vivante(i, j, *g))
			{
				// evolution d'une cellule vivante
				if (v != 2 && v != 3)
				{
					set_morte(i, j, *g);
				}
				// si cellule non morte et vieillissement activé, alors augmenter l'âge de la cellule
				else if(vieillissement)
				{
					g->cellules[i][j]++;

					//Une cellule meurt de viellesse quand son âge dépasse 8 pas de temps.
					if(g->cellules[i][j] > 8) set_morte(i, j, *g);

				} else {
					// si vieillissement désactivé remettre à 1 (vivante)
					g->cellules[i][j] = 1;
				}
				
				continue;
			}

			// evolution d'une cellule morte
			if (v == 3) set_vivante(i, j, *g);
			
		}
	}
	return;
}
