#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <stdlib.h>

#include "jeu.h"
#include "../lib/color.h"
#include "matrice_affichage.h"

#ifdef OLD_VERSION
COULEUR_TERMINAL choisirCouleur(int nombre, COULEUR_TERMINAL liste_couleurs[], int nb_couleurs);
void dessinerLigne(int largeur, jeu *p, int numLigne, COULEUR_TERMINAL listeCouleurs[], int nbCouleurs);
void affichageCouleur(jeu *p);

#else

COULEUR_TERMINAL choisirCouleur(int nombre);
void afficherCaseMatrice(jeu *p, matrix *m, int ligne, int colonne);
void affichageMatrice(jeu *p, matrix *m);
#endif

#endif