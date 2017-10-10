#pragma once

#include "jeu.h"

#include "../lib/saisieM.h"

int mouvementLigne(jeu *j, int indice, int direction);
int mouvementColonne(jeu *j, int indice, int direction);
int mouvementLignes(jeu *j, int direction);
int mouvementColonnes(jeu *j, int direction);
int mouvement(jeu *j, int direction);

int saisieD();