#ifndef JEU_H
#define JEU_H

#include <stdlib.h>
#include <stdio.h>

#include "matrice_affichage.h"
#include "menu.h"
#include "dialogBox.h"

#define MVT_STOP -1
#define MVT_BAS 0
#define MVT_DROITE 1
#define MVT_HAUT 2
#define MVT_GAUCHE 3

typedef struct {
    int n;
    int valMax;
    int nbCasesLibres;
    int *grille;
    int score;
} jeu;

void initialiseJeu (jeu *p, int n, int valMax);
int indiceValide (jeu *p, int i, int j);
int getVal(jeu *p, int ligne, int colonne);
void setVal(jeu * p, int ligne, int colonne, int val);

int caseVide(jeu *p, int ligne, int colonne);
void ajouteValAlea(jeu *p);

int gagne(jeu *p);
int perdu(jeu *p);
int finPartie(jeu *p);

int jouer(jeu *p, matrix *m);

#endif