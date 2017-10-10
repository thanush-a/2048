#include "menu.h"

/* \fn mennu
 *    
 *    Affiche un menu et attend que l'utilisateur choisisse un boutton
 *    
 *    \param *m : matrice dans laquelle va être affiché le menu
 *    \param button[] : liste des bouttons à afficher
 *    \param nbButton : nombre de bouttons à afficher
 *    
*/

int menu(matrix *m, menuButton button[], int nbButtons)
{
	

	int run = 1, // Si à 0, on sort du menu
		pressedKey = 0,
		buttonSelect = 0, // Numero du boutton selectionné
		i = 0;

	int buttonHeight = 6; // taille de menu height
	int buttonWidth = 45; // taille de menu width

    
    

    
    COULEUR_TERMINAL fg;
    COULEUR_TERMINAL bg;

    debutTerminalSansR();

    while (run)
    {
        

        //clearMatrix(m);

        // Fond du menu
        matrixRectangle(m, m->h / 2 - nbButtons * (buttonHeight + 1) / 2 - 1, m->w / 2 - buttonWidth / 2 - 1, buttonWidth + 2, nbButtons * (buttonHeight + 1) + 1, 
GREEN, 
BLACK, //Background-color fond de menu
 ' ');

        /* Affichage des bouttons */
        for (i = 0; i < nbButtons; i ++)
        {
            // On regle la couleur du boutton en fonction de s'il est selectionné ou pas
            if (i == buttonSelect) {
                fg = BLACK; //Color police menu selectionner
                bg = WHITE; //Background-color pour le menu selectionner
            } else {
                fg = BLUE;  //Color police du menu 
                bg = WHITE; // Background-color des 3 menu 
            }

            // Affichage du rectangle et du texte
            matrixRectangle(m, i * (buttonHeight + 1) + m->h / 2 - nbButtons * (buttonHeight + 1) / 2, m->w / 2 - buttonWidth / 2, buttonWidth, buttonHeight, fg, bg, ' ');
            matrixText(m, i * (buttonHeight + 1) + (buttonHeight / 2) + m->h / 2 - nbButtons * (buttonHeight + 1) / 2, buttonWidth / 2 - strlen(button[i].text) / 2 + m->w / 2 - buttonWidth / 2, fg, bg, button[i].text);
        }

        flushMatrix(m);

        // Lecture du clavier
        int pressedKey = lectureFleche();
        switch (pressedKey)
        {
            case NO_KEY:
                run = 0;
                break;
            case KEY_UP:
                if (buttonSelect > 0)
                    buttonSelect--;
                else
                    buttonSelect = nbButtons - 1;
                break;
            case KEY_DOWN:
                if (buttonSelect < nbButtons - 1)
                    buttonSelect++;
                else
                    buttonSelect = 0;
                break;
            default:
                break;
        }
    }

    finTerminalSansR();

    return button[buttonSelect].choice;
}
