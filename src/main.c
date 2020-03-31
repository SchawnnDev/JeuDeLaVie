#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

#if MODECAIRO

cairo_surface_t* c_surface;

#endif

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


#if MODECAIRO

	#define SIZEX 1000
	#define SIZEY 600
		
		c_surface = cairo_create_x11_surface0(SIZEX, SIZEY);
		
#else 


	affiche_grille(g, 1, 1, 0);

#endif

	debut_jeu(&g, &gc);

	// libérer la mémoire
	libere_grille(&g);
	libere_grille(&gc);

#if MODECAIRO
	cairo_close_x11_surface(c_surface);// close the display
#endif
	return 0;
}
