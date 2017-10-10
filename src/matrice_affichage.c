#include "matrice_affichage.h"
#include "util.h"
#include <string.h>

// #define DEBUG

/**
 * Initialise une matrice d'affichage.
 * 
 * \param m : Pointeur vers la matrice à initialiser
 * \param w : La largeur de la matrice, en caractères
 * \param h : La hauteur de la matrice, en caractères
 */
void initMatrix(matrix *m, int w, int h)
{
    m->w = w;
    m->h = h;
    
    m->p = calloc(w*h, sizeof(pixel));
    if(m->p == NULL)
    {
        fprintf(stderr, "\nError : Can't allocate memory (init matrix).\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * Libère la mémoire allouée pour la matrice.
 * 
 * \param m : Pointeur vers la matrice à libérer
 */
void freeMatrix(matrix *m)
{
    free(m->p);
    m->p = NULL;
    m->w = m->h = 0;
}

/**
 * Affiche une matrice à l'écran
 * 
 * \param m : Pointeur vers la matrice à afficher
 */
void flushMatrix(matrix *m)
{
    #ifndef DEBUG
        CLEAR();
    #else
        printf("\n\n\n");
    #endif
    
    int line, col;
    pixel *p;

    #ifdef DEBUG
        printf("m->h = %d\nm->w = %d\n", m->h, m->w);
    #endif

    for (line = 0; line < m->h; ++line)
    {
        for (col = 0; col < m->w; ++col)
        {
            p = getPixelMatrix(m, line, col);

            if(p != NULL)
                color_printf(p->fg, p->bg, "%c", (p->c < 32) ? ' ' : p->c);
            else
            {
                #ifdef DEBUG
                    printf("\nError : Out of matrix (flush).\n");
                #endif
                exit(EXIT_FAILURE);
            }
        }
        printf("\n");
    }
}



/**
 * Retourne 1 si l'indice passé est dans le système de coordonées de la matrice,
 * 0 sinon.
 * 
 * \param m : Pointeur vers la matrice courante
 * \param ligne : Ligne de la case de la matrice à tester
 * \param colonne : Colonne de la case de la matrice à tester
 */
int coordInMatrix(matrix *m, int ligne, int colonne)
{
    return (ligne >= 0) && (ligne < m->h) && (colonne >= 0) && (colonne < m->w);
}




/**
 * Retourne un pointeur vers le pixel demandé.
 * 
 * \param m : Pointeur vers la matrice courante
 * \param ligne : Ligne sur la matrice du pixel demandé
 * \param colonne : Colonne sur la matrice du pixel demandé
 */
pixel* getPixelMatrix(matrix *m, int ligne, int colonne)
{
    if(coordInMatrix(m, ligne, colonne))
        return &m->p[m->w * ligne + colonne];
    else
    {
        #ifdef DEBUG
            printf("\nAlert : Pixel is not in the matrix (getPixelMatrix(m, %d, %d))\n", ligne, colonne);
        #endif
        return NULL;
    }
}



/**
 * Modifie la valeur d'un pixel de la matrice.
 * 
 * \param m : Pointeur vers la matrice à modifier
 * \param ligne : Ligne de la case de la matrice à modifier
 * \param colonne : Colonne de la case de la matrice à modifier
 * \param fg : Couleur du texte de la case
 * \param bg : Couleur de l'arrière plan de la case
 * \param c : Caractère affiché pour cette case
 * 
 * Retourne 1 si la modification a réussie, 0 sinon.
 */
int matrixPixel(matrix *m, int ligne, int colonne, COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, char c)
{
    pixel *p = getPixelMatrix(m, ligne, colonne);
    if (p != NULL) 
    {
        p->fg = fg;
        p->bg = bg;
        p->c = c;
        
        return 1;
    }  
    
    return 0;
}




/**
 * Ajoute un texte dans la matrice
 * 
 * \param m : Pointeur vers la matrice à modifier
 * \param ligne : Ligne de la 1ère case de la matrice où afficher le texte
 * \param colonne : Colonne de la 1ère case de la matrice où afficher le texte
 * \param fg : Couleur du texte
 * \param bg : Couleur de l'arrière plan du texte
 * \param s : Chaîne à affichier
 * 
 * Retourne 1 si la modification a réussie, -1 si le texte a dépassé, 0 sinon.
 */
int matrixText(matrix *m, int ligne, int colonne, COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, char* s)
{
    if (!coordInMatrix(m, ligne, colonne))
    {
        #ifdef DEBUG
            printf("\nAlert : Text is not in matrix (matrixText)\n");
            return 0;
        #endif
    }

    int length = strlen(s), i;
    pixel *p;

    for (i = 0; i < length; ++i)
    {
        p = getPixelMatrix(m, ligne, colonne + i);

        if (p != NULL)
        {
            p->fg = fg;
            p->bg = bg;
            p->c = s[i];
        }
    }

    return 0;
}



/**
 * Efface le contenu de la matrice
 * 
 * \param m : Pointeur vers la matrice à modifier
 */
void clearMatrix(matrix *m)
{
    int ligne, colonne;
    for(ligne = 0; ligne < m->h; ligne++)
    {
        for(colonne = 0; colonne < m->w; colonne++)
        {
            matrixPixel(m, ligne, colonne, BLACK, BLACK, '\0');
        }
    }
}




/**
 * Dessine un rectangle sur la matrice
 * 
 * \param m : Pointeur vers la matrice à modifier
 * \param ligne : Ligne de la 1ère case de la matrice où afficher le rectangle
 * \param colonne : Colonne de la 1ère case de la matrice où afficher le rectangle
 * \param w : Largeur du rectangle
 * \param h : Hauteur du rectangle
 * \param fg : Couleur du rectangle
 * \param bg : Couleur de l'arrière plan du rectangle
 * \param s : Chaîne à affichier
 * 
 * Retourne 1 si la modification a réussie, -1 si le rectangle a dépassé, 0 sinon.
 */
int matrixRectangle(matrix *m, int ligne, int colonne, int w, int h, COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, char c)
{
    if (!coordInMatrix(m, ligne, colonne))
    {
        #ifdef DEBUG
            printf("\nAlert : Rect is not in matrix (matrixRectangle)\n");
            return 0;
        #endif
    }

    int i, j;

    for (i = 0; i < h; ++i)
    {
        for (j = 0; j < w; ++j)
        {
            if (coordInMatrix(m, i, j))
            {
                matrixPixel(m, ligne+i, colonne+j, fg, bg, c);
            }
        }
    }
    
    return 0;
}

/**
 * Ecrit un entier sur la matrice
 * 
 * \param m : Pointeur vers la matrice à modifier
 * \param ligne : Ligne de la 1ère case de la matrice où afficher le rectangle
 * \param colonne : Colonne de la 1ère case de la matrice où afficher le rectangle
 * \param w : Largeur du rectangle
 * \param h : Hauteur du rectangle
 * \param fg : Couleur du rectangle
 * \param bg : Couleur de l'arrière plan du rectangle
 * \param s : Chaîne à affichier
 * 
 * Retourne -1 si l'entier a dépassé, 1 si la modification a réussie,  0 sinon.
 */
int matrixInt(matrix *m, int ligne, int colonne, COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, int e)
{
    char strScore[12] = "0";

    sprintf(strScore, "%d", e);

    return matrixText(m, ligne, colonne, fg, bg, strScore);
}
