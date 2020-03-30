#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>

#define SIZEX 1000
#define SIZEY 600

#include "grille.h"
#include "io.h"
#include "jeu.h"

void paint(cairo_surface_t* surface)
{
	// create cairo mask
	cairo_t* cr;
	cr = cairo_create(surface);

	// background
	cairo_set_source_rgb(cr, 5, 220.0, 220.0); // gainsboro
	cairo_paint(cr);

	// line
	cairo_set_source_rgb(cr,255.0, 0.0, 0.0);
	cairo_move_to(cr, 10.0, 50.0);
	cairo_line_to(cr, 100.0, 50.0);
	cairo_set_line_width(cr, 1);
	cairo_stroke(cr);

	// text

	cairo_select_font_face(cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 32.0);
	cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
	cairo_move_to(cr, 10.0, 50.0);
	cairo_show_text(cr, "Hello, world");


	// filled rectangle
	cairo_rectangle(cr, 30, 30, 100, 50);
	cairo_set_source_rgb(cr, 0.0, 1.0, 0.0);
	cairo_fill(cr);

	cairo_destroy(cr); // destroy cairo mask
}


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	int cairo = 1;

	grille g, gc;

	// charger & démarrer le jeu
	init_grille_from_file(argv[1], &g);


	if(cairo)
	{
		// X11 display
		Display* dpy;
		Window rootwin;
		Window win;
		XEvent e;
		int scr;

		// init the display
		if (!(dpy = XOpenDisplay(NULL))) {
			fprintf(stderr, "ERROR: Could not open display\n");
			exit(1);
		}

		scr = DefaultScreen(dpy);
		rootwin = RootWindow(dpy, scr);

		win = XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0,
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

		XStoreName(dpy, win, "Jeu de la vie");
		XSelectInput(dpy, win, ExposureMask | ButtonPressMask);
		XMapWindow(dpy, win);

		// create cairo surface
		cairo_surface_t* cs;
		cs = cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

		// run the event loop
		while (1) {
			XNextEvent(dpy, &e);
			if (e.type == Expose && e.xexpose.count < 1) {
				paint(cs);
			}
			else if (e.type == ButtonPress) break;
		}

		cairo_surface_destroy(cs); // destroy cairo surface
		XCloseDisplay(dpy); // close the display
	}

	
	alloue_grille(g.nbl, g.nbc, &gc);
	affiche_grille(g, 1, 1, 0);
	debut_jeu(&g, &gc);

	// libérer la mémoire
	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
