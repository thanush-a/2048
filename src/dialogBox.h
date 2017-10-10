#pragma once

#include "matrice_affichage.h"
#include "../lib/saisieM.h"

int dialogBox(int mode, matrix *m, char *text);

#define DIALOG_MODE_ALERT  1
#define DIALOG_MODE_CANCEL 2
#define DIALOG_MODE_YES_NO 3

#define DIALOG_RES_OK 0
#define DIALOG_RES_CANCEL 1
#define DIALOG_RES_YES 2
#define DIALOG_RES_NO 3