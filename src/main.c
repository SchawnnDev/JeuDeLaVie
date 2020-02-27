#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;

	// charger & démarrer le jeu
	init_grille_from_file(argv[1], &g);
	alloue_grille(g.nbl, g.nbc, &gc);
	affiche_grille(g, 1, 1);
	debut_jeu(&g, &gc);

	// libérer la mémoire
	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
