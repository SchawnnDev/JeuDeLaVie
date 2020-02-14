#include "io.h"

void affiche_trait(int c)
{
	for (int i = 0; i < c; ++i) printf("|---");
	printf("|\n");
	return;
}

void affiche_ligne(int c, int* ligne)
{
	for (int i = 0; i < c; ++i)
		if (ligne[i] == 0) printf("|   ");
		else printf("| O ");
	printf("|\n");
	return;
}

void affiche_grille(grille g)
{
	const int l = g.nbl;
	const int c = g.nbc;
	printf("\n");
	affiche_trait(c);
	for (int i = 0; i < l; ++i)
	{
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}
	printf("\n");
	return;
}

void efface_grille(grille g)
{
	printf("\n\e[%dA", g.nbl * 2 + 5);
}

void debut_jeu(grille* g, grille* gc)
{
	char c = (char)getchar();
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c)
		{
		case '\n':
			{
				// touche "entree" pour évoluer
				evolue(g, gc);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
		case 'n':
			{
				char nom_fichier_grille[256];
				printf("Veuillez entrer un nouveau fichier grille:\n");
				scanf("%s", nom_fichier_grille);

				printf("Chargement du fichier %s...\n\n", nom_fichier_grille);

				// liberer la grille
				libere_grille(g);
				libere_grille(gc);

				charge_grille(g, gc, nom_fichier_grille);

				printf("\n"); // nouvelle ligne pour eviter que la ligne du bas soit plus petite que les autres
			
				return;
			}
		default:
			{
				// touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = (char)getchar();
	}
	return;
}

void charge_grille(grille* g, grille* gc, char* nom_fichier_grille)
{
	init_grille_from_file(nom_fichier_grille, g);
	alloue_grille(g->nbl, g->nbc, gc);

	affiche_grille(*g);

	debut_jeu(g, gc);
}
