# Variables dossiers
SDIR=src
ODIR=obj
BDIR=bin
IDIR=include

# Compile flags -> Iinclude pour les fichiers .h
CFLAGS= -Wall -Iinclude

# Instructions
main: main.o grille.o jeu.o io.o
	@mkdir -p bin
	gcc $(CFLAGS) -o $(BDIR)/main $(ODIR)/main.o $(ODIR)/grille.o $(ODIR)/jeu.o $(ODIR)/io.o
main.o: $(SDIR)/main.c
	@mkdir -p obj
	gcc $(CFLAGS) -o $(ODIR)/main.o -c $(SDIR)/main.c
grille.o: $(SDIR)/grille.c
	@mkdir -p obj
	gcc $(CFLAGS) -o $(ODIR)/grille.o -c $(SDIR)/grille.c
jeu.o: $(SDIR)/jeu.c
	@mkdir -p obj
	gcc $(CFLAGS) -o $(ODIR)/jeu.o -c $(SDIR)/jeu.c
io.o: $(SDIR)/io.c
	@mkdir -p obj
	gcc $(CFLAGS) -o $(ODIR)/io.o -c $(SDIR)/io.c
dist:
	@mkdir -p dist
	tar -c --lzma -f dist/Meyer-Paul.tar.xz grilles include src Makefile README.md
clean: 
	rm -rf $(ODIR)/
	rm -rf $(BDIR)/
	rm -rf dist/