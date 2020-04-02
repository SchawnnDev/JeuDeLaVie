#include "grille.h"

int init_grille_from_file(char* filename, grille* g)
{
	FILE* pfile = NULL;
	pfile = fopen(filename, "r");

	int i, j, n, l, c, vivantes = 0, non_viables = 0;

	if (pfile == NULL) return 1; // le fichier n'existe pas

	fscanf(pfile, "%d", &l);
	fscanf(pfile, "%d", &c);

	alloue_grille(l, c, g);

	fscanf(pfile, "%d", &vivantes);
	for (n = 0; n < vivantes; ++n)
	{
		fscanf(pfile, "%d", &i);
		fscanf(pfile, "%d", &j);
		set_vivante(i, j, *g);
	}

	fscanf(pfile, "%d", &non_viables);
	for (n = 0; n < non_viables; ++n)
	{
		fscanf(pfile, "%d", &i);
		fscanf(pfile, "%d", &j);
		set_non_viable(i, j, *g);
	}

	fclose(pfile);
	return 0;
}


void copie_grille(grille gs, grille gd)
{
	int i, j;
	for (i = 0; i < gs.nbl; ++i) for (j = 0; j < gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;
}

// alloue une grille de taille l*c, et initialise toutes les cellules � mortes
void alloue_grille(int l, int c, grille* g)
{
	g->nbc = c;
	g->nbl = l;
	g->cellules = (int**)malloc(sizeof(int*) * l);
	for (int i = 0; i < l; ++i)
	{
		g->cellules[i] = (int*)malloc(sizeof(int*) * c);
		for (int j = 0; j < c; ++j) set_morte(i, j, *g);
	}
}

// lib�re une grille
void libere_grille(grille* g)
{
	for (int i = 0; i < g->nbl; ++i)
		free(g->cellules[i]);
	free(g->cellules);
}
