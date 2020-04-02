#include "io.h"

#if MODECAIRO // ici on stocke les fonctions utiles a cairo

#include <string.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

// pour le tableau
#define LEFT_MARGIN 30
#define TOP_MARGIN 50
#define LINE_WIDTH 2
#define TABLE_WIDTH 450
#define TABLE_HEIGHT 400

extern cairo_surface_t* c_surface;
XClassHint *classHint;

cairo_surface_t* cairo_create_x11_surface0(int x, int y)
{
	Display* dsp;
	Drawable da;
	int screen;
	cairo_surface_t* sfc;

	if ((dsp = XOpenDisplay(NULL)) == NULL)
	{
		printf("Cant open display\n");
		exit(1);
	}
	// screen par defaut
	screen = DefaultScreen(dsp);
	// tester avec des pixels blancs
	da = XCreateSimpleWindow(dsp, DefaultRootWindow(dsp), 1, 1, x, y, 0, 0x1, 0x1);
	XSelectInput(dsp, da, ExposureMask | ButtonPressMask | KeyPressMask);
	XMapWindow(dsp, da);

	classHint = XAllocClassHint();
	if (classHint) {
		classHint->res_name = "Jeu de la vie";
		classHint->res_class = "Jeu de la vie";
		XSetClassHint(dsp, da, classHint);
		XFree(classHint);
	}

	// ajouter le nom
	XStoreName(dsp, da, "Jeu de la vie");

	sfc = cairo_xlib_surface_create(dsp, da, DefaultVisual(dsp, screen), x, y);
	cairo_xlib_surface_set_size(sfc, x, y);

	return sfc;
}

void cairo_close_x11_surface(cairo_surface_t* sfc)
{
	Display* dsp = cairo_xlib_surface_get_display(sfc);
	cairo_surface_destroy(sfc);
	XCloseDisplay(dsp);
}

void affiche_trait(int c, double cellHeight)
{
	cairo_t* cr;
	cr = cairo_create(c_surface);
	// trait horizontal donc variation de X
	cairo_set_source_rgb(cr, 0.5554, 0.542, 0.9);
	cairo_move_to(cr, LEFT_MARGIN, TOP_MARGIN + cellHeight * c);
	cairo_line_to(cr, LEFT_MARGIN + TABLE_WIDTH, TOP_MARGIN + cellHeight * c);
	cairo_set_line_width(cr, LINE_WIDTH);
	cairo_stroke(cr);
	
	cairo_destroy(cr);
}

void affiche_ligne(int c, double cellWidth)
{
	cairo_t* cr;
	cr = cairo_create(c_surface);
	// trait vertical donc variation de Y
	cairo_set_source_rgb(cr, 0.2445, 0.5544554, 0.5544554);
		
	// ajout des cases

	cairo_move_to(cr, LEFT_MARGIN + c * cellWidth, TOP_MARGIN);
	cairo_line_to(cr, LEFT_MARGIN + c * cellWidth, TOP_MARGIN + TABLE_HEIGHT);
	cairo_set_line_width(cr, LINE_WIDTH);
	cairo_stroke(cr);
	cairo_destroy(cr);
}

void affiche_grille(grille g, int vieillissement)
{
	const int l = g.nbl; // nombre de cases horizontales
	const int c = g.nbc; // nombre de cases verticales

	cairo_t* cr;
	cr = cairo_create(c_surface);

	const double cellHeight = (double)TABLE_HEIGHT / (double)l;
	const double cellWidth = (double)TABLE_WIDTH / (double)c;

	// affichage des lignes
	
	for (int i = 0; i <= l ; ++i)
		affiche_trait(i, cellHeight);

	for (int i = 0; i <= c; ++i)
		affiche_ligne(i, cellWidth);

	// affichage des grilles
	
	cairo_t* cr_grilles;
	cr_grilles = cairo_create(c_surface);
	// trait vertical donc variation de Y
	cairo_set_source_rgb(cr_grilles, 0.2445, 0.5544554, 0.5544554);


	// valeurs pour texte si vieillissement

	if (vieillissement)
	{

		cairo_set_source_rgb(cr, 0.14, 0.4, 0.8);
		cairo_select_font_face(cr, "Arial",
			CAIRO_FONT_SLANT_NORMAL,
			CAIRO_FONT_WEIGHT_BOLD);

		cairo_set_font_size(cr, 30);

	}

	for(int i = 0; i < l ; ++i) // lignes
	{
		int* ligne = g.cellules[i];
		
		for (int j = 0; j < c; ++j) // colonnes
		{

			// ne rien afficher
			if (ligne[j] == 0) continue;

			if (ligne[j] == -1)
			{
				// dessiner un X

				// diagonale 1
				cairo_move_to(cr_grilles, LEFT_MARGIN +  j * cellWidth, TOP_MARGIN + i * cellHeight);
				cairo_line_to(cr_grilles, LEFT_MARGIN + (j + 1) * cellWidth, TOP_MARGIN + (i + 1) * cellHeight);
				cairo_set_line_width(cr_grilles, LINE_WIDTH);
				cairo_stroke(cr_grilles);

				// diagonale 2
				cairo_move_to(cr_grilles, LEFT_MARGIN + (j + 1) * cellWidth, TOP_MARGIN + i * cellHeight);
				cairo_line_to(cr_grilles, LEFT_MARGIN + j * cellWidth, TOP_MARGIN + (i + 1) * cellHeight);
				cairo_set_line_width(cr_grilles, LINE_WIDTH);
				cairo_stroke(cr_grilles);

				continue;
			}

			cairo_rectangle(cr_grilles, LEFT_MARGIN + j * cellWidth, TOP_MARGIN + i * cellHeight, cellWidth, cellHeight);
			cairo_set_source_rgb(cr_grilles, 0.2445, 0.5544554, 0.5544554);
			cairo_fill(cr_grilles);

			if (vieillissement)
			{ // afficher chiffres
				cairo_set_font_size(cr, 10);
				// on ajoute 0.5 pour atteindre la moitié
				cairo_move_to(cr, LEFT_MARGIN + (j + 0.5) * cellWidth, TOP_MARGIN + (i + 0.5) * cellHeight);

				// converter int to string
				char str[12];
				sprintf(str, "%d", ligne[j]);
				cairo_show_text(cr, str);
				continue;
			}

		}
	}

	cairo_destroy(cr_grilles);
	cairo_destroy(cr);
	return;
}

void affiche_texte(int tempsEvolution, int voisinageCyclique, int vieillissement)
{
	cairo_t* cr;
	cr = cairo_create(c_surface);
	cairo_set_source_rgb(cr, 0.2445, 0.0544554, 0.5544554);
	//cairo_set_source_rgb(cr, 0.2445, 0.5544554, 0.5544554);
	cairo_select_font_face(cr, "Arial",
		CAIRO_FONT_SLANT_NORMAL,
		CAIRO_FONT_WEIGHT_BOLD);

	cairo_set_font_size(cr, 30);
	cairo_move_to(cr, LEFT_MARGIN, TOP_MARGIN - 18);
	cairo_show_text(cr, "Jeu de la Vie");

	char* temps_str = malloc(sizeof(char) * 10); // on admet que le temps ne sera plus grand que 10 chars
	sprintf(temps_str, "%d", tempsEvolution);
	char* temps = concat("• Temps: ", temps_str);
	char* voisinage = concat("• Voisinage cyclique: ", (voisinageCyclique ? "activé" : "désactivé"));
	char* vieillissementStr = concat("• Vieillissement: ", (vieillissement ? "activé" : "désactivé"));



	const int infoTitleHeight = TOP_MARGIN + 18;
	const int commandsTitleHeight = infoTitleHeight * 2 + 27 * 3;
	const int leftMargin = LEFT_MARGIN * 2 + TABLE_WIDTH;

	cairo_set_font_size(cr, 24);
	cairo_move_to(cr, leftMargin, infoTitleHeight);
	cairo_show_text(cr, "Informations :");

	cairo_set_font_size(cr, 16);
	cairo_move_to(cr, leftMargin, infoTitleHeight + 27);
	cairo_show_text(cr, temps);

	cairo_move_to(cr, leftMargin, infoTitleHeight + 27 * 2);
	cairo_show_text(cr, voisinage);

	cairo_move_to(cr, leftMargin, infoTitleHeight + 27 * 3);
	cairo_show_text(cr, vieillissementStr);

	cairo_set_font_size(cr, 24);
	cairo_move_to(cr, leftMargin, commandsTitleHeight);
	cairo_show_text(cr, "Commandes :");

	cairo_set_font_size(cr, 16);

	int commandsCount = 5;
	char** commands = malloc(sizeof(char) * commandsCount * 64);

	commands[0] = "• clic gauche => Faire évoluer les cellules";
	commands[1] = "• touche c => Activer / désactiver le comptage cyclique";
	commands[2] = "• touche v => Activer / désactiver le vieillissement";
	commands[3] = "• touche n => Changer de grille";
	commands[4] = "• clic droit => Quitter le programme";


	for(int i = 0; i < commandsCount; ++i)
	{
		cairo_move_to(cr, leftMargin, commandsTitleHeight + 27 * (i + 1));
		cairo_show_text(cr, *(commands + i));
	}

	// free

	free(commands);
	free(voisinage);
	free(vieillissementStr);
	free(temps_str);
	free(temps);
	cairo_destroy(cr);
	
}

void efface_grille(grille g)
{
	cairo_t* cr;
	cr = cairo_create(c_surface);
	cairo_set_source_rgb(cr, 0.811, 0.796, 0.886);
	cairo_paint(cr);
	cairo_destroy(cr);
}

void debut_jeu(grille* g, grille* gc)
{

	// variables
	int skip = 0;
	int tempsEvolution = 1;
	int voisinageCyclique = 1;
	int vieillissement = 0;
	int (*compte_voisins_vivants)(int, int, grille) = compte_voisins_vivants_cyclique;
	Display* const dsp = cairo_xlib_surface_get_display(c_surface);
	XEvent e;
	
	// run the event loop
	efface_grille(*g);
	affiche_grille(*g, vieillissement);
	affiche_texte(tempsEvolution, voisinageCyclique, vieillissement);
	
	while (1) {
		// Clear the background
		
		XNextEvent(cairo_xlib_surface_get_display(c_surface), &e);

		if (e.type == Expose && e.xexpose.count < 1) {
			affiche_grille(*g, vieillissement);
			affiche_texte(tempsEvolution, voisinageCyclique, vieillissement);
		} else if (e.type == ButtonPress) {

			if (e.xbutton.button == 1) {
				tempsEvolution++;
				evolue(g, gc, compte_voisins_vivants, vieillissement);
				efface_grille(*g);
				affiche_grille(*g, vieillissement);
				affiche_texte(tempsEvolution, voisinageCyclique, vieillissement);
			} else if (e.xbutton.button == 3) {
				break; // on stoppe l'application
			}
			
		} else if (e.type == KeyPress)
		{

			printf("Key: %d\n", e.xkey.keycode);

			if (e.xkey.keycode == XKeysymToKeycode(dsp, 'v')) // touche v
			{
				vieillissement = !vieillissement;
				efface_grille(*g);
				affiche_grille(*g, vieillissement);
				affiche_texte(tempsEvolution, voisinageCyclique, vieillissement);
			} else if (e.xkey.keycode == XKeysymToKeycode(dsp, 'c')) // touche c
			{
				voisinageCyclique = !voisinageCyclique;
				compte_voisins_vivants = voisinageCyclique
					? &(compte_voisins_vivants_cyclique)
					: &(compte_voisins_vivants_non_cyclique);

				efface_grille(*g);
				affiche_grille(*g, vieillissement);
				affiche_texte(tempsEvolution, voisinageCyclique, vieillissement);
			} else if (e.xkey.keycode == XKeysymToKeycode(dsp, 'n')) // touche n
			{
				drawInputZone("", "");
				int exit = 0;
				int erreurInitialisation = 0;
				FILE* testFile = NULL;
				KeySym key;
				char inputBuffer[255];

				do {
					char numeroGrille[10] = "";
					char fichierGrille[100] = "grilles/grille";

					while (1) {
						XNextEvent(cairo_xlib_surface_get_display(c_surface), &e);
						if (e.type == KeyPress && XLookupString(&e.xkey, inputBuffer, 256, &key, 0) == 1) {
							if (e.xkey.keycode == 36 || e.xkey.keycode == 104) {
								break;
							} else if (e.xkey.keycode == XKeysymToKeycode(dsp, XK_Delete) || e.xkey.keycode == XKeysymToKeycode(dsp, XK_BackSpace)) { // Effacer le dernier caractère de la chaine
								numeroGrille[strlen(numeroGrille) - 1] = '\0'; 
							} else if (e.xkey.keycode == XKeysymToKeycode(dsp, XK_Escape)) { // ESC pour annuler
								exit = 1;
								break;
							} else {
								strcat(numeroGrille, inputBuffer);
							}
							drawInputZone(numeroGrille, "");
						}
					}

					if (!exit) {
						strcat(fichierGrille, numeroGrille);
						strcat(fichierGrille, ".txt");
						testFile = fopen(fichierGrille, "r");
						
						if (testFile != NULL) {
							libere_grille(g);
							libere_grille(gc);
							erreurInitialisation = init_grille_from_file(fichierGrille, g);
							
							if (erreurInitialisation)
								drawInputZone("", "grille introuvable");
							
							fclose(testFile);
							testFile = NULL;
						}
						else {
							erreurInitialisation = 1;
							drawInputZone("", "fichier introuvable");
						}
					}
				} while (erreurInitialisation && !exit);

				if (!exit) {
					tempsEvolution = 1; // Réinitialisation du temps
					alloue_grille(g->nbl, g->nbc, gc);
				}

				efface_grille(*g);
				affiche_grille(*g, vieillissement);
				affiche_texte(tempsEvolution, voisinageCyclique, vieillissement);
			
			}
			
		}
	}

	return;
}

void drawInputZone(char* input, char* error) {
	const int x = LEFT_MARGIN * 2 + TABLE_WIDTH;
	const int y = (TOP_MARGIN + 18) * 2 + 27 * 3 + 7.5 * 27 ; // 27 * 3 = nombre d'infos
	cairo_t* cr;
	cr = cairo_create(c_surface);

	char inputLabel[256];
	
	if (strcmp(error, "") == 0)
		sprintf(inputLabel, "Grille a charger:");
	else
		sprintf(inputLabel, "Grille a charger [%s]:", error);

	cairo_text_extents_t extentsInput;
	cairo_text_extents_t extentsInputLabel;

	// couvrir la partie texte sans effacer toute la grille
	cairo_set_source_rgb(cr, 0.811, 0.796, 0.886);
	cairo_rectangle(cr, x - 20, y - 20, x + 100, y + 10);
	cairo_fill(cr);

	cairo_select_font_face(cr, "Arial",
		CAIRO_FONT_SLANT_NORMAL,
		CAIRO_FONT_WEIGHT_BOLD);

	cairo_set_font_size(cr, 18);

	cairo_set_source_rgb(cr, 0.2445, 0.0544554, 0.5544554);

	cairo_move_to(cr, x, y);
	cairo_show_text(cr, inputLabel);

	cairo_text_extents(cr, inputLabel, &extentsInputLabel);

	cairo_move_to(cr, x + extentsInputLabel.width + 2, y);
	cairo_show_text(cr, input);

	cairo_text_extents(cr, input, &extentsInput);

	int inputOffset = x + extentsInputLabel.width + 5 + extentsInput.width;
	cairo_move_to(cr, inputOffset, y - 15);
	cairo_set_line_width(cr, 1);
	cairo_line_to(cr, inputOffset, y + 10);
	cairo_stroke(cr);

	cairo_destroy(cr);
}


char* concat(const char* s1, const char* s2)
{
	char* result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
	// in real code you would check for errors in malloc here
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

# else // ici on stocke les fonctions utiles au texte

void affiche_trait(int c)
{
	for (int i = 0; i < c; ++i) printf("|---");
	printf("|\n");
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
}

# endif
