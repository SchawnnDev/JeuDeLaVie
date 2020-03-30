#include "io.h"

#if MODECAIRO // ici on stocke les fonctions utiles a cairo

#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
// pour le tableau
#define CELL_WIDTH 30
#define CELL_HEIGHT 30
#define LEFT_MARGIN 30
#define TOP_MARGIN 30
#define LINE_WIDTH 1

extern cairo_surface_t* c_surface;

void affiche_trait(int c)
{
	// trait vertical donc variation de X
	cairo_set_source_rgb(c_surface, 1.0, 0.0, 0.0);
	cairo_move_to(c_surface, LEFT_MARGIN, TOP_MARGIN * c);
	cairo_line_to(c_surface, LEFT_MARGIN + c * CELL_WIDTH, TOP_MARGIN * c);
	cairo_set_line_width(c_surface, 1);
	cairo_stroke(c_surface);
}


void affiche_ligne(int c, int* ligne, int vieillissement)
{
	// trait vertical donc variation de X
	cairo_set_source_rgb(c_surface, 1.0, 0.0, 0.0);
	cairo_move_to(c_surface, LEFT_MARGIN * c, TOP_MARGIN);
	cairo_line_to(c_surface, LEFT_MARGIN * c, TOP_MARGIN + c * CELL_HEIGHT);
	cairo_set_line_width(c_surface, 1);
	cairo_stroke(c_surface);
}

void affiche_grille(grille g, int tempsEvolution, int voisinageCyclique, int vieillissement)
{
	const int l = g.nbl;
	const int c = g.nbc;
	char* cycliqueStr = voisinageCyclique ? "Activé" : "Désactivé";
	char* vieillissementStr = vieillissement ? "Activé" : "Désactivé";
	printf("\n");
	printf("\e[K");
	printf("Temps d'évolution: %d", tempsEvolution);
	printf(" | ");
	printf("Voisinage cyclique: %s", cycliqueStr);
	printf(" | ");
	printf("Vieillissement: %s", vieillissementStr);
	printf("\n\n");
	affiche_trait(c);
	for (int i = 1; i <= l; ++i)
	{
		affiche_ligne(c, g.cellules[i], vieillissement);
		affiche_trait(c);
	}
	printf("\n");
	return;
}

void efface_grille(grille g)
{
	cairo_t* cr;
	cr = cairo_create(c_surface);
	cairo_set_source_rgb(cr,1.0, 1.0, 1.0);
	cairo_paint(cr);
	cairo_destroy(cr);
}

void debut_jeu(grille* g, grille* gc)
{
	// variables
	char c = (char)getchar();
	int skip = 0;
	int tempsEvolution = 1;
	int voisinageCyclique = 1;
	int vieillissement = 0;
	int (*compte_voisins_vivants)(int, int, grille) = compte_voisins_vivants_cyclique;

	// run the event loop
	while (1) {
		XNextEvent(dpy, &e);
		if (e.type == Expose && e.xexpose.count < 1) {
			paint(c_surface);
		}
		else if (e.type == ButtonPress)
		{

			if(e.xkey.keycode == 36) // touche entrée
			{
				tempsEvolution++;
				evolue(g, gc, compte_voisins_vivants, vieillissement);
				efface_grille(*g);
				affiche_grille(*g, tempsEvolution, voisinageCyclique, vieillissement);
			} else
			{
				break;
			}
			
		}
	}

	cairo_surface_destroy(c_surface); // destroy cairo surface
	/*
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c)
		{
		case '\n':
		{
			if (skip)
			{
				skip = !skip;
				break;
			}
			// touche "entree" pour évoluer

			break;
		}
		case 'n':
		{
			char nom_fichier_grille[256];
			printf("Veuillez entrer un nouveau fichier grille:\n");
			scanf("%s", nom_fichier_grille);

			printf("Chargement du fichier %s...\n\n", nom_fichier_grille);
			// reset le temps
			tempsEvolution = 1;
			// liberer la grille
			libere_grille(g);
			libere_grille(gc);

			// charger & démarrer le jeu
			init_grille_from_file(nom_fichier_grille, g);
			alloue_grille(g->nbl, g->nbc, gc);
			affiche_grille(*g, 1, voisinageCyclique, vieillissement);
			//debut_jeu(g, gc);
			skip = 1; // eviter d'evoluer a la prochaine action
			printf("\n\e[2A");
			printf("\n"); // nouvelle ligne pour eviter que la ligne du bas soit plus petite que les autres
			break;
		}
		case 'c':
		{
			voisinageCyclique = !voisinageCyclique;
			compte_voisins_vivants = voisinageCyclique
				? &(compte_voisins_vivants_cyclique)
				: &(compte_voisins_vivants_non_cyclique);

			efface_grille(*g);
			affiche_grille(*g, tempsEvolution, voisinageCyclique, vieillissement);
			printf("\e[K");
			printf("\n");

			break;
		}
		case 'v':
			vieillissement = !vieillissement;
			//printf("\n\e[1A");
			efface_grille(*g);
			affiche_grille(*g, tempsEvolution, voisinageCyclique, vieillissement);
			//printf("\e[A");
			printf("\e[K");
			printf("\n");
			break;
		default:
		{
			// touche non traitée
			printf("\n\e[1A");
			break;
		}
		}
		c = (char)getchar();
	}*/
	return;
}


# else // ici on stocke les fonctions utiles au texte

void affiche_trait(int c)
{
	for (int i = 0; i < c; ++i) printf("|---");
	printf("|\n");
	return;
}

void affiche_ligne(int c, int* ligne, int vieillissement)
{
	for (int i = 0; i < c; ++i)
	{
		if (ligne[i] == 0) printf("|   ");
		else if (ligne[i] == -1) printf("| X "); // Non-viable
		else if (vieillissement) printf("| %d ", ligne[i]);
		else printf("| 0 ");
	}

	printf("|\n");
	return;
}

void affiche_grille(grille g, int tempsEvolution, int voisinageCyclique, int vieillissement)
{
	const int l = g.nbl;
	const int c = g.nbc;
	char* cycliqueStr = voisinageCyclique ? "Activé" : "Désactivé";
	char* vieillissementStr = vieillissement ? "Activé" : "Désactivé";
	printf("\n");
	printf("\e[K");
	printf("Temps d'évolution: %d", tempsEvolution);
	printf(" | ");
	printf("Voisinage cyclique: %s", cycliqueStr);
	printf(" | ");
	printf("Vieillissement: %s", vieillissementStr);
	printf("\n\n");
	affiche_trait(c);
	for (int i = 0; i < l; ++i)
	{
		affiche_ligne(c, g.cellules[i], vieillissement);
		affiche_trait(c);
	}
	printf("\n");
	return;
}

void efface_grille(grille g)
{
	printf("\n\e[%dA", g.nbl * 2 + 7);
}

void debut_jeu(grille* g, grille* gc)
{
	// variables
	char c = (char)getchar();
	int skip = 0;
	int tempsEvolution = 1;
	int voisinageCyclique = 1;
	int vieillissement = 0;
	int (*compte_voisins_vivants)(int, int, grille) = compte_voisins_vivants_cyclique;

	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c)
		{
		case '\n':
			{
				if (skip)
				{
					skip = !skip;
					break;
				}
				// touche "entree" pour évoluer
				tempsEvolution++;
				evolue(g, gc, compte_voisins_vivants, vieillissement);
				efface_grille(*g);
				affiche_grille(*g, tempsEvolution, voisinageCyclique, vieillissement);
				break;
			}
		case 'n':
			{
				char nom_fichier_grille[256];
				printf("Veuillez entrer un nouveau fichier grille:\n");
				scanf("%s", nom_fichier_grille);

				printf("Chargement du fichier %s...\n\n", nom_fichier_grille);
				// reset le temps
				tempsEvolution = 1;
				// liberer la grille
				libere_grille(g);
				libere_grille(gc);

				// charger & démarrer le jeu
				init_grille_from_file(nom_fichier_grille, g);
				alloue_grille(g->nbl, g->nbc, gc);
				affiche_grille(*g, 1, voisinageCyclique, vieillissement);
				//debut_jeu(g, gc);
				skip = 1; // eviter d'evoluer a la prochaine action
				printf("\n\e[2A");
				printf("\n"); // nouvelle ligne pour eviter que la ligne du bas soit plus petite que les autres
				break;
			}
		case 'c':
			{
				voisinageCyclique = !voisinageCyclique;
				compte_voisins_vivants = voisinageCyclique
					                         ? &(compte_voisins_vivants_cyclique)
					                         : &(compte_voisins_vivants_non_cyclique);

				efface_grille(*g);
				affiche_grille(*g, tempsEvolution, voisinageCyclique, vieillissement);
				printf("\e[K");
				printf("\n");

				break;
			}
		case 'v':
			vieillissement = !vieillissement;
			//printf("\n\e[1A");
			efface_grille(*g);
			affiche_grille(*g, tempsEvolution, voisinageCyclique, vieillissement);
			//printf("\e[A");
			printf("\e[K");
			printf("\n");
			break;
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

# endif
