#pragma once

#include "matrice_affichage.h"
#include "../lib/color.h"
#include "../lib/saisieM.h"

typedef enum
{
	PLAY,
	LOAD,
	EXIT,
	RESUME,
	SAVE
} menuChoice;

typedef struct
{
	menuChoice choice;
	char *text;
} menuButton;

int menu(matrix *m, menuButton button[], int nbButtons);
