# Variables dossiers
SDIR=src
ODIR=obj
BDIR=bin
IDIR=include

# Compile flags
CFLAGS= -Wall -Iinclude

# Instructions
main: main.o grille.o jeu.o io.o
	gcc $(CFLAGS) -o $(BDIR)/main $(ODIR)/main.o $(ODIR)/grille.o $(ODIR)/jeu.o $(ODIR)/io.o
main.o: $(SDIR)/main.c
	gcc $(CFLAGS) -o $(ODIR)/main.o -c $(SDIR)/main.c
grille.o: $(SDIR)/grille.c
	gcc $(CFLAGS) -o $(ODIR)/grille.o -c $(SDIR)/grille.c -Wall
jeu.o: $(SDIR)/jeu.c
	gcc $(CFLAGS) -o $(ODIR)/jeu.o -c $(SDIR)/jeu.c
io.o: $(SDIR)/io.c
	gcc $(CFLAGS) -o $(ODIR)/io.o -c $(SDIR)/io.c
dist:
	tar -c --lzma -f dist/Meyer-Paul.tar.xz grilles include src Makefile README.md
clean: 
	rm -rf $(ODIR)/*.o
	rm -rf $(BDIR)/*