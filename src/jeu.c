#include "jeu.h"



/*! \fn initialiseJeu
 * Alloue la grille de la variable jeu passée par adresse.
 * Initialise les cases de la grille avec des cases vides (valeurs nulles)
 * Initialise les champs n et valMax avec les valeurs passées en paramètre
 *
 * \param p : pointeur sur une partie de 2048
 * \param n : taille de la grille
 * \param valMax : valeur à atteindre pour gagner
 */
 
void initialiseJeu (jeu *p, int n, int valMax)
        {
                p->n = n;
                p->valMax = valMax;
                p->nbCasesLibres = n * n;
                p->grille = calloc(n*n, sizeof(int));
                p->score = 0;
    
                 if(p->grille == NULL)
                {
                    fprintf(stderr, "Impossible d'allouer la memoire\n");
                    exit(EXIT_FAILURE);
                }
            }

/*! \fn libereMemoire
 * Libère la mémoire allouée pour la grille du jeu passé par adresse.
 *
 * \param p : pointeur sur une partie de 2048
 */
            void libereMemoire(jeu *p)
            {
                free(p->grille);
                p->grille = NULL;
                p->n = p->nbCasesLibres = p->valMax = p->score = -1;
            }

/*! \fn indiceValide
 * Fonction retournant 1 si la case (i,j) existe, 0 sinon.
 *
 */
            int indiceValide (jeu *p, int i, int j)
                {
                    // Si i < taille max ET j < taille max ET i >= 0 ET j >= 0
                    return (i < p->n) && (j < p->n) && (i >= 0) && (j >= 0);
                }

/*! \fn getVal
 * Fonction retournant la valeur de la case (ligne,colonne) de la partie p,
 * ou -1 si la case n’existe pas.
 *
 * \param p : pointeur sur la partie en cours
 * \param ligne : entier correspondant au numéro de ligne
 * \param colonne : entier correspondant au numéro de colonne
 */
        int getVal(jeu *p, int ligne, int colonne)
                {
                    if(indiceValide(p, ligne, colonne))
                    {
        // Retourne la valeur de la case (ligne, colonne)
        
        /**
         * Explications :
         * Une ligne a une longueur `p->n`, donc accéder à la ligne i c'est
         * accéder aux cases mémoires de décalage i*p->n par rapport au 
         * début du tableau.
         */
                            return p->grille[p->n * ligne + colonne];
                        }
                        else
                        {
                            return -1;
                        }
                    }

/*! \fn setVal
 * Fonction modifiant la valeur de la case (ligne,colonne) de la partie p, avec la valeur val
 *
 * \param p : pointeur sur la partie en cours
 * \param ligne : entier correspondant au numéro de ligne
 * \param colonne : entier correspondant au numéro de colonne
 * \param val : entier à mettre dans la case (i,j) (si elle existe)
 */
void setVal(jeu * p, int ligne, int colonne, int val)
{
    if(indiceValide(p, ligne, colonne))
    {
        if(getVal(p, ligne, colonne) == 0 && val != 0)
            p->nbCasesLibres--;
        else if(getVal(p, ligne, colonne) != 0 && val == 0)
            p->nbCasesLibres++;
        
        p->grille[p->n * ligne + colonne] = val;
    }
}

/*! \fn caseVide
 * 
 * Retourne 1 si la case est vide, 0 sinon
 
 * \param p : pointeur sur la partie en cours
 * \param ligne : entier correspondant au numéro de ligne
 * \param colonne : entier correspondant au numéro de colonne
 */
int caseVide(jeu * p, int ligne, int colonne)
{
    return (indiceValide(p, ligne, colonne)) ? getVal(p, ligne, colonne) == 0 : 0;
}

/*! \fn ajouteValAlea
 *  
 *  Ajoute la valeur 2 ou 4 dans une case vide aléatoire
 *  
 *  \param p : pointeur sur la partie en cours
 *  
*/
void ajouteValAlea(jeu *p)
{
    if(p->nbCasesLibres > 0)
    {
        int i, j, count = 0;
        int *tab = calloc(p->n*p->n, sizeof(int));
        
        for (i = 0; i < p->n; i++)
        {
            for (j = 0; j < p->n; j++)
            {
                if (getVal(p, i, j) == 0)
                {
                    tab[count] = i * p->n + j;
                    count++;
                }
            }
        }
        
        p->grille[tab[rand() % count]] = 2*(rand() % 2 + 1);
        p->nbCasesLibres--;
        
        free(tab);
        tab = NULL;
    }
}

/*!
 * \fn gagne
 * Retourne 1 si la partie est gagnée, 0 sinon.
 *
 * \param p : pointeur sur la partie en cours
 */
int gagne(jeu * p)
{
    int i = 0;
    
    for(i = (p->n * p->n) - 1; i >= 0; i--)
        if(p->grille[i] >= p->valMax)
            return 1;
    
    return 0;
}

/*!
 * \fn perdu
 * Retourne 1 si la partie est perdue, 0 sinon.
 *
 * \param p : pointeur sur la partie en cours
 */
int perdu(jeu *p)
{
    int i, j;
    if(p->nbCasesLibres <= 0 && !gagne(p))
    {
        for(i = p->n - 1; i >= 0; i--)
        {
            for(j = p->n - 1; j >= 0; j--)
            {
                if(
                    (getVal(p, i, j) == getVal(p, i+1, j))
                 || (getVal(p, i, j) == getVal(p, i, j+1))
                )
                    return 0;
            }
        }
        
        return 1;
    } else {
        return 0;
    }
}

/**
 * \fn finParie
 * Retourne 1 si la partie est finie (gagnée ou perdue), 0 sinon.
 * 
 * \param p : pointeur sur la partie en cours
 */
int finPartie(jeu *p)
{
    return gagne(p) || perdu(p);
}

/**
 * Jouer à une partie de 2048
 * 
 * \param p : pointeur sur la partie en cours
 * \param p : pointeur sur la matrice d'affichage
 */
#define NB_BUTTONS_MENU_PAUSE 3

int jouer(jeu *p, matrix *m)
{
    int run = 1, mouvementChoisi = 0;
    menuChoice choice;
    int saved = 1;
    int rep;

    menuButton button[NB_BUTTONS_MENU_PAUSE];
    button[0].choice = RESUME;
    button[0].text = "Retour au jeu";
    button[1].choice = SAVE;
    button[1].text = "Sauvegarder";
    button[2].choice = EXIT;
    button[2].text = "Menu";

    debutTerminalSansR();

    while (run)
    {
        affichageMatrice(p, m);

        if(finPartie(p))
        {
            sleep(1);

            if(gagne(p))
            {
                dialogBox(DIALOG_MODE_ALERT, m, "Vous avez gagne !");
            } else { // Si la partie est finie et que c'est pas gagné, c'est que c'est perdu
                dialogBox(DIALOG_MODE_ALERT, m, "Vous avez perdu !");
            }
            run = 0;
        } else {
             int mouvementChoisi = saisieD();
            if(mouvementChoisi == MVT_STOP)
            {
                finTerminalSansR(); // Sans ça un double debutTerminalSansR se fait dans menu()
                choice = menu(m, button, NB_BUTTONS_MENU_PAUSE);
		if (choice == EXIT)
		{
		run = 0;
		}
	     else if (choice == SAVE)
                {
                    sauvegarde(p);
                    saved = 1;
                }
                debutTerminalSansR(); // Sans ça un double finTerminalSansR se fait dans menu()
            } else {
                if(mouvement(p, mouvementChoisi))
                {
                    ajouteValAlea(p);
                    saved = 0;
                }
            }
        }
    }

    finTerminalSansR();
}
