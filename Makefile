# Variables dossiers
SDIR=src
ODIR=obj
BDIR=bin
IDIR=include
VER=4.0

# -> Iinclude pour les fichiers .h
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11

# Compile flags 
CFLAGS= $(CPPFLAGS) -Wall

# Instructions
main: main.o grille.o jeu.o io.o
	@mkdir -p bin
	gcc $(CFLAGS) -o $(BDIR)/main $(ODIR)/main.o $(ODIR)/grille.o $(ODIR)/jeu.o $(ODIR)/io.o $(LDFLAGS)
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
	tar -c --lzma -f dist/MeyerPaul-GoL-$(VER).tar.xz grilles include src Makefile Doxyfile README.md
clean: 
	rm -rf $(ODIR)/
	rm -rf $(BDIR)/
	rm -rf dist/
	rm -rf doc/
doc:
	@doxygen
help:
	@echo "======== Help Jeu de la Vie $(VER) ========"
	@echo "make: compiler le programme"
	@echo "make clean: effacer les fichiers générés"
	@echo "make dist: créer une archive du projet"
	@echo "make doc: générér la documentation doxygen"
	@echo "make help: afficher l'aide"