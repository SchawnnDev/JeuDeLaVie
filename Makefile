# Variables dossiers
SDIR=src
ODIR=obj
BDIR=bin
IDIR=include
LDIR=lib
VER=5.0
MODE=CAIRO

# -> Iinclude pour les fichiers .h
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -ljeu -L lib/ -lcairo -lm -lX11

# Compile flags 
CFLAGS= $(CPPFLAGS) -Wall

# Vflags
vpath %.c $(SDIR)
vpath %.h $(IDIR)
vpath %.o $(ODIR)

# Instructions
main: main.o grille.o jeu.o io.o
	@mkdir -p $(BDIR)
	@mkdir -p $(LDIR)

	ar -crv $(LDIR)/libjeu.a $(ODIR)/jeu.o $(ODIR)/grille.o
	ranlib $(LDIR)/libjeu.a

	gcc -DMODE$(MODE) $(CFLAGS) -o $(BDIR)/main $(ODIR)/main.o $(ODIR)/grille.o $(ODIR)/jeu.o $(ODIR)/io.o $(LDFLAGS)

	rm -rf $(ODIR)/

%.o: %.c
	@mkdir -p $(ODIR)
	gcc -DMODE$(MODE) $(CFLAGS) -o $(ODIR)/$@ -c $<

dist:
	@mkdir -p dist
	tar -c --lzma -f dist/MeyerPaul-GoL-$(VER).tar.xz grilles include src Makefile Doxyfile README.md

clean:
	rm -rf $(LDIR)/
	rm -rf $(ODIR)/
	rm -rf $(BDIR)/
	rm -rf dist/
	rm -rf doc/

doc:
	@doxygen

help:
	@echo "======== Help Jeu de la Vie $(VER) ========"
	@echo "./bin/main <grille>: éxécuter le programme"
	@echo "make: compiler le programme"
	@echo "make clean: effacer les fichiers générés"
	@echo "make dist: créer une archive du projet"
	@echo "make doc: générér la documentation doxygen"
	@echo "make help: afficher l'aide"