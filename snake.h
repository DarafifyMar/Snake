#ifndef __SNAKE__
#define __SNAKE__

#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <MLV/MLV_all.h>

#define M 64
#define N 32

typedef struct {
    int x;
    int y;
} Case;

typedef enum {
    NORD,
    SUD,
    EST,
    OUEST
} Direction;

typedef struct {
    Case tab_serp[N*M];
    Direction dir;
    int taille;
    int mort;
} Serpent;

typedef enum {
    NORMAL,
    SUPER,
    POISON
} TypeP;

typedef struct {
    Case pos;
    TypeP type;
} Pomme;

typedef struct {
    Serpent serpent;
    Pomme tab_pommes[N*M];
    int nb_pommes;
    int score;
} Monde;

/* Renvoie un entier entre 0 et l'entier max passé en paramètre. */
int randint(int max);

/*
Renvoie un TypeP de façon aléatoire selon la règle suivante :
- SUPER a "10% de chances" d'etre renvoyé,
- POISON a "10% de chances" d'etre renvoyé,
- NORMAL a "80% de chances" d'etre renvoyé. 
*/
TypeP genereType();

/*
pomme_gen_alea renvoie une Pomme dont les coordonnées et
le type sont choisis aléatoirement.
Les entiers n et m correspondent respectivement à la longueur et à
la hauteur maximum du monde dans laquelle la pomme doit etre contenue.
*/
Pomme pomme_gen_alea(int n, int m);

/*
recherche_pomme detecte si une Pomme est situee dans la case pointée par c.
Elle renvoie :
    - l'indice de cette pomme dans le monde mon si c'est le cas;
    - -1 sinon.
*/
int recherche_pomme(Monde mon, Case *c);

/*
case_occupee_serp a pour paramètres l'adresse d'un Serpent et celle d'une Case.
Elle renvoie :
    - 1 si la case pointee par c est occupée par le serpent pointé par ser
    - 0 sinon.
*/
int case_occupee_serp(Serpent *ser, Case *c);
/*
case_occupee_pomme a pour paramètres l'adresse d'un Serpent et celle d'une Case.
Elle renvoie :
    - 1 si la case pointee par c est occupée par une Pomme du Monde
    pointé par mon
    - 0 sinon.
*/
int case_occupee_pomme(Monde *mon, Case *c);
/*
case_occupee_poison a pour paramètres l'adresse d'un Serpent et celle d'une Case.
Elle renvoie :
    - 1 si la case pointee par c est occupée par une Pomme de type
    POISON du Monde pointé par ser,
    - 0 sinon.
*/
int case_occupee_poison(Monde *mon, Case *c);
/*
ajouter_pomme_monde ajoute une Pomme génerée aléatoirement dans le monde
pointé par mon.
*/
void ajouter_pomme_monde(Monde *mon);
/*
init_serpent renvoie un serpent qui sera au milieu de la fenetre dirigé vers l'ouest
*/
Serpent init_serpent();

/*
fonction qui initialise le monde avec en parametre le nombre de pommes voulu*/
Monde init_monde(int nb_pommes);
/*
case_suivante a pour paramètres un Serpent ser et l'adresse d'une case c.
Elle calcule les coordonnées de la case située devant le Serpent ser et
les stocke dans la Case pointée par c.
*/
void case_suivante(Serpent ser, Case *c);
/*
avance_serpent a pour paramètres l'adresse d'un Serpent ser.
Cette fonction fait avancer chacune des parties du corps du Serpent
d'une case selon sa direction.
*/
void avance_serpent(Serpent *ser);
/*
deplacer_serpent a pour paramètres l'adresse d'un monde mon
Cette fonction renvoie :
    - 1 et déplace le Serpent si il n'est pas entré en collision avec
    un autre élément du monde (bordure, autre serpent, pomme)
    - 0 et ne déplace PAS le Serpent sinon.
*/
int deplacer_serpent(Monde *mon);
/*
supprimer_pomme_monde a pour paramètres l'adresse mon d'un monde et un
entier indice_pomme. Cette fonction supprime la Pomme désignée par
indice_pomme du monde pointé par mon.
*/
void supprimer_pomme_monde(Monde *mon, int indice_pomme);
/*
manger_pomme_serpent a pour paramètres l'adresse mon d'un monde. Cette fonction renvoie 0 si la case devant le serpent
ne contient pas de pomme. Sinon manger_pomme_serpent renvoie 1 après
avoir augmenté la taille du Serpents
Le score est augmenté de 1 si la pomme mangée est de type NORMAL, et de
1 si la pomme est de type SUPER.
*/
int manger_pomme_serpent(Monde *mon);
/*
pomme_tout_poison a pour paramètres l'adresse mon d'un monde.
Cette fonction renvoie :
    - 1 si toutes les pommes du monde pointé par mon sont empoisonnées,
    - 0 sinon.
*/
int pomme_tout_poison(Monde *mon);
/*
mort_serpent a pour paramètres l'adresse mon d'un monde. Cette fonction vérifie l'état du serpent:
Cette fonction renvoie :
    - 1 si le serpent choisi va entrer en collision en continuant à avancer
    dans cette direction,
    - 0 sinon.
*/
int mort_serpent(Monde *mon);
/*
change_dir_serp a pour paramètres l'adresse mon d'un monde, un entier
choix_serp et un MLV_Keyboard_button touche.
Cette fonction modifie la direction (selon la valeur de touche).
*/
void change_dir_serp(Monde *mon, MLV_Keyboard_button touche);
#endif