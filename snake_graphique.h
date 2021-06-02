#ifndef __GRAPHIQUE__
#define __GRAPHIQUE__

#include <stdio.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include "snake.h"

#define TAILLE_CASE 21
#define LONGUEUR (TAILLE_CASE * M)
#define HAUTEUR (TAILLE_CASE * N)
#define HAUTEUR_FEN (HAUTEUR + 3 * TAILLE_CASE)

/*
Cette fonction a pour paramètre l'adresse d'un monde mon.
afficher_quadrillage affiche le quadrillage du monde mon dans la fenêtre MLV.
*/
void afficher_quadrillage(Monde *mon);
/*
Cette fonction a pour paramètre l'adresse d'une pomme pom.
afficher_pomme affiche la pomme pom en fonction de ses coordonnées.
*/
void afficher_pomme(Pomme *pom);
/*
Cette fonction a pour paramètre l'adresse d'un monde mon et celle d'un
MLV_Image image. afficher_serpent affiche la tete du serpent
pointé par ser dans la fenetre MLV. image désigne une image d'un des deux
serpents (vert ou bleu).
*/
void afficher_tete_serp(Serpent *ser, MLV_Image *image);
/*
Cette fonction a pour paramètre l'adresse d'un monde mon et celle d'un
MLV_Image image. afficher_serpent affiche le corps du serpent
pointé par ser dans la fenetre MLV. image désigne une image d'un des deux
serpents (vert ou bleu).
*/
void afficher_corps_serp(Serpent *ser, MLV_Image *image);
/*
Cette fonction a pour paramètre l'adresse d'un monde mon et celle d'un
MLV_Image image. afficher_serpent affiche la queue du serpent pointé
par ser dans la fenetre MLV. image désigne une image d'un des deux
serpents (vert ou bleu).
*/
void afficher_queue_serp(Serpent *ser, MLV_Image *image);
/*
Cette fonction a pour paramètre l'adresse d'un monde mon et celle d'un
MLV_Image image. afficher_serpent affiche le serpent pointé par ser dans
la fenetre MLV à l'aide des fonctions de la forme afficher_X_serp.
image désigne une image d'un des deux serpents (vert ou bleu).
*/
void afficher_serpent(Serpent *ser, MLV_Image *image);
/*
Cette fonction a pour paramètre l'adresse d'un monde mon.
afficher_score affiche le score du premier serpent en mode un joueur,
et celui des deux serpents en mode deux joueurs.
*/
void afficher_score(Monde *mon);
/*
Cette fonction a pour paramètre l'adresse d'un monde mon.
afficher_monde affiche tout les éléments du monde pointé par mon dans
la fenetre MLV.
*/
void afficher_monde(Monde *mon);
/*
Cette fonction a pour paramètre un entier score.
Elle affiche le message de fin de partie dans la fenetre MLV, ainsi que le
score final du joueur.
*/
void dessine_fin_partie(int score);
/*
Cette fonction a pour paramètre un entier score.
Elle affiche le message de début de partie dans la fenetre MLV.
*/
void dessine_debut_partie();
/*
pause met en pause le jeu jusqu'à ce que la touche entrée soit pressée.
*/
void pause();
/*
dessine_pause dessine le message qui s'affiche pendant que le jeu est en pause.
*/
void dessine_pause();

#endif