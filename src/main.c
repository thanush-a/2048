#include "affichage.h"
#include "matrice_affichage.h"
#include "jeu.h"
#include "mouvement.h"
#include "menu.h"
#include "sauvegarder.h"
#include "dialogBox.h"

#include "../lib/saisieM.h"
#include "../lib/color.h"

#include <stdio.h>

#define DIM_JEU 4
#define FIN_JEU 2048
#define NB_BUTTONS_MENU 3

int main()
{
    srand(time(NULL));
    
    
    
    jeu j;
    matrix m;

    // Liste des bouttons du menu donc 3
    menuButton button[NB_BUTTONS_MENU];
    button[0].choice = PLAY;
    button[0].text = "Nouvelle partie";
    button[1].choice = LOAD;
    button[1].text = "Continuer la partie";
    button[2].choice = EXIT;
    button[2].text = "Quitter";

    int winW, winH;
    getWinSize(&winW, &winH);

    initialiseJeu(&j, DIM_JEU, FIN_JEU);
    initMatrix(&m, winW, winH - 1);

    menuChoice choice;
    
   // char nom_util[5];
        
     //   printf("Votre nom en 5 lettres: ");
       // scanf("%s",nom_util);
        
 
    do
    {
        clearMatrix(&m);
        choice = menu(&m, button, NB_BUTTONS_MENU);

        switch(choice)
        {
            case PLAY:
                initialiseJeu(&j, DIM_JEU, FIN_JEU);
                ajouteValAlea(&j);
                ajouteValAlea(&j);
                jouer(&j, &m);
                break;
            case LOAD:
                charger(&j);
                jouer(&j, &m);
                break;
            default: break;
        }

    } while (choice != EXIT);

    freeMatrix(&m);
    libereMemoire(&j);

    clearScreen();

    return 0;
}