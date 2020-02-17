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

void affiche_grille(grille g, int tempsEvolution, int voisinageCyclique)
{
	const int l = g.nbl;
	const int c = g.nbc;
	char* cycliqueStr = voisinageCyclique ? "Activé" : "Désactivé";
	printf("\e[K");
	printf("Temps d'évolution: %d", tempsEvolution);
	printf(" | ");
	printf("Voisinage cyclique : %s", cycliqueStr);
	printf("\n");
	affiche_trait(c);
	for (int i = 0; i < l; ++i)
	{
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}
	printf("\n");
	printf("\e[K");
	return;
}

void efface_grille(grille g)
{
	printf("\n\e[%dA", g.nbl * 2 + 5);
}

void debut_jeu(grille* g, grille* gc)
{
	// variables
	char c = (char)getchar();
	int tempsEvolution = 1;
	int voisinageCyclique = 0;
	int (*compte_voisins_vivants) (int, int, grille) = _;

	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c)
		{
		case '\n':
			{
				// touche "entree" pour évoluer
				tempsEvolution++;
				evolue(g, gc);
				efface_grille(*g);
				affiche_grille(*g, tempsEvolution, voisinageCyclique);
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

				// charger & démarrer le jeu
				init_grille_from_file(nom_fichier_grille, g);
				alloue_grille(g->nbl, g->nbc, gc);
				affiche_grille(*g, 1, voisinageCyclique);
				debut_jeu(g, gc);

				printf("\n"); // nouvelle ligne pour eviter que la ligne du bas soit plus petite que les autres
			
				return;
			}
		case 'c':
			{
				voisinageCyclique = !voisinageCyclique;
			
				break;
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