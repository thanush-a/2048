#include "affichage.h"
#include "matrice_affichage.h"
#include "util.h"
#include <string.h>

#ifdef OLD_VERSION



/*! \fn choisirCouleur
 *    
 *  Choisit et renvoi une couleur dans un tableau de couleurs en fonction de la puissance de 2 d'un nombre
 *    
 *  \param nombre : nombre en fonction duquel on choisit la couleur
 *  \param listeCouleurs : liste des couleurs dans laquelle on va en choisir une couleur
 *  \param nbCouleurs : nombre de couleurs dans listeCouleurs
 *    
*/
            COULEUR_TERMINAL choisirCouleur(int nombre, COULEUR_TERMINAL *listeCouleurs, int nbCouleurs)
{
    

    
    /**
     * Nous cherchons à résoudre nombre = 2^x + 2
     * Pourquoi 2^x ? La principe de jeu est de fonctionner avec des puissances de 2.
     * Pourquoi + 2 ? Parce que si on l'enlèverai, on renverrai la couleur n°2 
     * pour le nombre 2, or ce nombre est censé faire renvoyer la couleur n°0.
     */
     
                    // Trouver la puissance de 2 qui correspond au nombre
                    nombre = nombre >> 2;
                    int puissance = 0;
                    while (nombre >> puissance)
                    {
                        puissance++;
                    }

    /*
        On choisit une couleur dans listeCouleurs
        en fonction de la puissance du chiffre dans
        la case actuelle, si la puissance est plus 
        grande que le tableau on recommence au 
        début du tableau (grace au modulo).
    */
    return listeCouleurs[puissance%nbCouleurs];
}

/*! \fn dessinerLigne
 *    
 *  Dessine une ligne d'une ligne de cases
 *    
 *  \param largeur : largeur (espaces)
 *  \param p : pointeur sur la partie que l’on souhaite afficher
 *  \param numLigne : numéro de la ligne de cases (dans le tableau du jeu)
 *  \param listeCouleurs : liste des couleurs dans laquelle on va en choisir une
 *  \param nbCouleurs : nombre de couleurs dans listeCouleurs
 *    
*/
void dessinerLigne(int largeur, jeu *p, int numLigne, COULEUR_TERMINAL *listeCouleurs, int nbCouleurs)
{
            int i, j;
            COULEUR_TERMINAL couleurCase;
            int nombre;

                     for (i = 0; i < p->n; ++i)
                            {
                                 nombre = p->grille[numLigne*p->n + i];

                    if (nombre != 0)
                            couleurCase = choisirCouleur(nombre, listeCouleurs, nbCouleurs);
                else
                         couleurCase = BLACK;

                    for (j = 0; j < largeur; ++j)
                        {
                          color_printf(WHITE, couleurCase, " ");
                            }
            }

            printf("\n");
        }

/*! \fn affichageCouleur
 *  
 *  Affiche la grille à l'écran
 *  
 *  \param p : pointeur sur la partie que l’on souhaite afficher
 *  
*/
void affichageCouleur(jeu *p)
{
            int i, j, k;
        
            int nombre; // Nom que contient la case
            int nbChiffres; // Nombre de chiffres dans nombre

                COULEUR_TERMINAL listeCouleurs[] = {CYAN, GREEN, BLUE, MAGENTA, YELLOW, RED}; // Liste des couleurs utilisées
                int nbCouleurs = 6; // Nombre de couleurs utilisées
                COULEUR_TERMINAL couleurCase; // Couleur utilisée pour la case

                    int largeurCase = 5; // Doit être impaire
                    int hauteurCase = 3; // Doit être impaire

                    // Il nous faut une hauteur et une largeur impaire
                    if (largeurCase%2 == 0)
                        largeurCase++;
                    if (hauteurCase%2 == 0)
                        hauteurCase++;

    for (i = 0; i < p->n; ++i)
    {

        /******************************* */
        // Premieres lignes de la case

        for (j = 0; j < hauteurCase / 2; ++j)
        {
            dessinerLigne(largeurCase, p, i, listeCouleurs, nbCouleurs);
        }

        /******************************* */
        // Ligne qui contient le numero

        for (j = 0; j < p->n; ++j)
        {
            nombre = p->grille[i*p->n + j];

            if (nombre != 0)
            {
                couleurCase = choisirCouleur(nombre, listeCouleurs, nbCouleurs);

                // Trouver le nombre de chiffres dans nombre
                nbChiffres = nbDigits(nombre);

                /*
                    `+ !(nbChiffres % 2 == 1)` : explications
                    
                    Si le nombre de chiffres est impair, on pourra le centrer
                    il y aura donc autant d'espaces à sa droite qu'à sa gauche.
                    
                    Si le nombre de chiffres est pair, on ne pourra pas le centrer
                    il y aura donc un espace de plus à sa droite qu'à sa gauche
                */
                for (k = 0; k < largeurCase / 2 - nbChiffres / 2; k++)
                    color_printf(WHITE, couleurCase, " ");

                color_printf(WHITE, couleurCase, "%d", nombre);

                for (k = 0; k < largeurCase / 2 - nbChiffres / 2 + !(nbChiffres % 2 == 1); k++)
                    color_printf(WHITE, couleurCase, " ");
            }

            else
            {
                couleurCase = BLACK;

                for (k = 0; k < largeurCase / 2; k++)
                        color_printf(WHITE, couleurCase, " ");
                color_printf(WHITE, couleurCase, ".");
                for (k = 0; k < largeurCase / 2; k++)
                        color_printf(WHITE, couleurCase, " ");
            }
        }

        printf("\n");

        /* ****************************** */
        // Dernieres lignes de la case

        for (j = 0; j < hauteurCase / 2; ++j)
        {
            dessinerLigne(largeurCase, p, i, listeCouleurs, nbCouleurs);
        }
    }

    printf("\n");
}

#else

static COULEUR_TERMINAL listeCouleurs[] = {CYAN, GREEN, BLUE, MAGENTA, YELLOW, RED};
static const int nbCouleurs = 6;
static int largeurCase = 7;
static int hauteurCase = 3;




/*! \fn choisirCouleur
 *    
 *  Choisit et renvoi une couleur dans un tableau de couleurs en fonction de la puissance de 2 d'un nombre
 *    
 *  \param nombre : nombre en fonction duquel on choisit la couleur
 *  \param listeCouleurs : liste des couleurs dans laquelle on va en choisir une
 *  \param nbCouleurs : nombre de couleurs dans listeCouleurs
 *    
*/


COULEUR_TERMINAL choisirCouleur(int nombre)
{
    /**
     * On cheche à résoudre nombre = 2^x + 2
     * Pourquoi 2^x ? Parce que le jeu fonctionne avec des puissances de 2.
     * Pourquoi + 2 ? Parce que si on l'enlèverai, on renverrai la couleur n°2 
     * pour le nombre 2, or ce nombre est censé faire renvoyer la couleur n°0.
     */
    
    if(nombre == 0)
        return BLACK;
     
    // Trouver la puissance de 2 qui correspond au nombre
    nombre = nombre >> 2;
                int puissance = 0;
                    while (nombre >> puissance)
                     {
                    puissance++;
                }




    /*
        On choisit qui est dans listeCouleurs
        en fonction du chiffre dans
        la case actuelle, si la puissance est plus 
        grande que le tableau on recommence au 
        début du tableau (grace au modulo).
    */
    return listeCouleurs[puissance%nbCouleurs];
}




void affichageCaseMatrice(jeu *p, matrix *m, int ligne, int colonne)
        {
                int i = 0;
                while (largeurCase * i * p->n < m->w && hauteurCase * i * p->n < m->h)
                        ++i;
                --i;

                        hauteurCase *= i;
                        largeurCase *= i;

                            if (largeurCase%2 == 0)
                                largeurCase--;
                                
                            if (hauteurCase%2 == 0)
                                hauteurCase--;

                        int val = getVal(p, ligne, colonne);
                        int nbChiffres = nbDigits(val);
                        COULEUR_TERMINAL couleur = choisirCouleur(val);

    matrixRectangle(m, ligne*hauteurCase + ((m->h - hauteurCase * p->n) / 2), colonne*largeurCase + ((m->w - largeurCase * p->n) / 2), largeurCase, hauteurCase ,couleur, couleur, ' ');

                     if(val != 0)
                       matrixInt(m, ligne*hauteurCase + hauteurCase/2 + ((m->h - hauteurCase * p->n) / 2),  colonne*largeurCase + largeurCase/2 - nbChiffres/2 + ((m->w - largeurCase * p->n) / 2), WHITE, couleur, val);
                     else
                    matrixPixel(m, ligne*hauteurCase + hauteurCase/2 + ((m->h - hauteurCase * p->n) / 2),  colonne*largeurCase + largeurCase/2 - nbChiffres/2 + ((m->w - largeurCase * p->n) / 2), WHITE, couleur, '.');
        }   









/*! \fn affichageMatrice
 *  
 *  Affiche la grille à l'écran
 *  
 *  \param p : pointeur sur la partie que l’on souhaite afficher
 *  \param m : pointeur sur la matrice d'affichage
 */
    void affichageMatrice(jeu *p, matrix *m)
        {
                int i, j;
                   //	char *nom_util[5];
        
            clearMatrix(m);
                 matrixText(m, 0, 0, WHITE, BLACK, "Bon Courage !! Utilisez les boutons ↑haut,↓bas,→droite,←gauche ");
                 // matrixText(m, 1,0, WHITE, BLUE ,*nom_util);
                 matrixText(m, 2, 0, WHITE, BLACK, "Total de points : ");
                 matrixInt(m, 2, 19, WHITE, BLACK, p->score);

                    for(i = 0; i < p->n; i++)
                            {
                                for(j = 0; j < p->n; j++)
                                    {
                                        affichageCaseMatrice(p, m, i, j);
                                    }
                            }

                flushMatrix(m);
        }

#endif
