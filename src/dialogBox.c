#include "dialogBox.h"

#define CAR_PER_LINE 60
#define BUTTON_WIDTH 9
#define MAX_BUTTONS 2

/* \fn dialogBox
 *  
 *  Ouvre un message, retourne :
 *  
 *  DIALOG_RES_OK: OK
 *  DIALOG_RES_CANCEL: ANNULER
 *  DIALOG_RES_YES: OUI
 *  DIALOG_RES_NO: NON
 *  
 *  \param mode : type de dialogBox
          DIALOG_MODE_ALERT: OK
          DIALOG_MODE_CANCEL: OK/ANNULER
          DIALOG_MODE_YES_NO: OUI/NON
 *  \param m : matrice dans laquelle va être affiché le message
 *  \param text : texte à afficher
 *  
*/
int dialogBox(int mode, matrix *m, char *text)
{
          int length = 0;
          int run = 1;
          int i, j;
          int posX = 0, posY = 0;
          char line[CAR_PER_LINE];
          COULEUR_TERMINAL fg, bg;
          int buttonSelect = 0;
          char *buttonText[MAX_BUTTONS];
          int returns[MAX_BUTTONS];

            length = strlen(text);
            
              int nbLines = 0;
              nbLines = length / CAR_PER_LINE + 1;

             int nbButtons = 0;


            
              posX = m->w / 2 - CAR_PER_LINE / 2 - 1;
              posY = m->h / 2 - (nbLines + 6) / 2;

                          debutTerminalSansR();
  while (run)
                  {
                          matrixRectangle(m, posY - 1, posX - 1, CAR_PER_LINE + 4, nbLines + 7, BLACK, WHITE, ' ');
                          matrixRectangle(m, posY, posX, CAR_PER_LINE + 2, nbLines + 5, WHITE, BLACK, ' ');

                 for (i = 0; i < nbLines; ++i)
                      {
                         for (j = 0; j < CAR_PER_LINE; ++j)
                             {
                                  line[j] = text[j + i * CAR_PER_LINE];
                             }

                                    matrixText(m, posY + i + 1, posX + 1, WHITE, BLACK, line);
                      }

                        for (i = 0; i < nbButtons; ++i)
                            {
                               if (buttonSelect == i)
                             {
                                    fg = BLACK;
                                    bg = WHITE;
                                }
                                   else
                                        {
                                            fg = WHITE;
                                            bg = RED;
                                          }

                          matrixRectangle(m, posY + nbLines + 1, posX + (CAR_PER_LINE + 2) - (BUTTON_WIDTH + 1) * i - BUTTON_WIDTH - 1, BUTTON_WIDTH, 3, fg, bg, ' ');
                          matrixText(m, posY + nbLines + 2, posX + (CAR_PER_LINE + 2) - (BUTTON_WIDTH + 1) * i - BUTTON_WIDTH - 1 + BUTTON_WIDTH / 2 - strlen(buttonText[nbButtons - i - 1]) / 2, fg, bg, buttonText[nbButtons - i - 1]);
                        }

                                      flushMatrix(m);

                                   int pressedKey = lectureFleche();
                                          switch (pressedKey)
                                          {
                                            case NO_KEY:
                                              run = 0;
                                                break;
                                            case KEY_LEFT:
                                              buttonSelect--;
                                              if (buttonSelect < 0)
                                                buttonSelect = nbButtons - 1;
                                                break;
                                            case KEY_RIGHT:
                                            buttonSelect++;
                                            if (buttonSelect >= nbButtons)
                                              buttonSelect = 0;
                                                break;
                                            default:
                                                break;
                                          }
                                        }

                                    finTerminalSansR();

                              return returns[buttonSelect];
}
