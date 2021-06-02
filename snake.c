#include "snake.h"

int randint(int max) {
    assert(max >= 0);

    return random() % (max + 1);
}

TypeP genereType() {
    int i;

    i = randint(10);
    if (i == 1)
        return POISON;
    else if (i == 2)
        return SUPER;
    return NORMAL;
}

Pomme pomme_gen_alea(int m, int n) {
    Pomme pom;

    assert(m > 0);
    assert(n > 0);
    assert(m <= M);
    assert(n <= N);

    pom.pos.x = randint(m-1);
    pom.pos.y = randint(n-1);
    pom.type = genereType();

    return pom;
}

int case_occupee_serp(Serpent *ser, Case *c) {
    int i;

    assert(NULL != ser);
    assert(NULL != c);

    for (i = 0; i < ser->taille; i++) {
        if (ser->tab_serp[i].x == c->x && ser->tab_serp[i].y == c->y)
            return 1;
    }
    return 0;
}

int case_occupee_pomme(Monde *mon, Case *c) {
    int i;
    int nb_pommes;
    Pomme *tab_pommes;

    assert(NULL != mon);
    assert(NULL != c);

    nb_pommes = mon->nb_pommes;
    tab_pommes = mon->tab_pommes;

    for (i = 0; i < nb_pommes; i++) {
        if (tab_pommes[i].pos.x == c->x && tab_pommes[i].pos.y == c->y)
            return 1;
    }
    return 0;
}

int pomme_tout_poison(Monde *mon) {
    int i;
    int nb_pommes;
    Pomme *tab_pommes;

    assert(NULL != mon);

    nb_pommes = mon->nb_pommes;
    tab_pommes = mon->tab_pommes;

    for (i = 0; i < nb_pommes; i++) {
        if (tab_pommes[i].type != POISON)
            return 0;
    }
    return 1;
}

void ajouter_pomme_monde(Monde *mon) {
    Pomme pom;

    assert(NULL != mon);

    do {
        pom = pomme_gen_alea(M, N);
    } while (case_occupee_serp(&(mon->serpent), &(pom.pos)) == 1 || case_occupee_pomme(mon, &(pom.pos)) == 1);
    
    mon->tab_pommes[mon->nb_pommes] = pom;

    if (pomme_tout_poison(mon) == 1)
        mon->tab_pommes[mon->nb_pommes].type = NORMAL;
    
    mon->nb_pommes += 1;
}

Serpent init_serpent() {
    int i;
    Case tmp;
    Serpent serp;

    serp.taille = 4;
    serp.mort = 0;
    serp.dir = EST;
    for (i = 0; i < serp.taille; i++) {
            tmp.x = M / 2 - (i + 2);
            tmp.y = N / 2;
            serp.tab_serp[i] = tmp;
        }
    return serp;
}

Monde init_monde(int nb_pommes) {
    int i;
    Monde m;

    assert(nb_pommes >= 3);
    m.serpent = init_serpent();
    m.nb_pommes = 0;
    m.score = 0;
    for (i = 0; i < nb_pommes; i++)
        ajouter_pomme_monde(&m);
    return m;
}

void case_suivante(Serpent ser, Case *c) {
    assert(NULL != c);

    if (ser.dir == NORD) {
        c->x = ser.tab_serp[0].x;
        c->y = ser.tab_serp[0].y - 1;
    }
    else if (ser.dir == EST) {
        c->x = ser.tab_serp[0].x + 1;
        c->y = ser.tab_serp[0].y;
    }
    else if (ser.dir == SUD) {
        c->x = ser.tab_serp[0].x;
        c->y = ser.tab_serp[0].y + 1;
    }
    else {
        c->x = ser.tab_serp[0].x - 1;
        c->y = ser.tab_serp[0].y;
    }
}

void avance_serpent(Serpent *ser) {
    int i;
    Case c;

    assert(NULL != ser);

    case_suivante(*ser, &c);

    for (i = ser->taille - 1; i > 0; i--)
        ser->tab_serp[i] = ser->tab_serp[i - 1];

    ser->tab_serp[0].x = c.x;
    ser->tab_serp[0].y = c.y;
}

int deplacer_serpent(Monde *mon) {
    Case c;
    Serpent *ser;

    assert(NULL != mon);


    ser = &(mon->serpent);
    case_suivante(*ser, &c);
    if (case_occupee_serp(&(mon->serpent), &c) == 1 || case_occupee_pomme(mon, &c) == 1)
        return 0;

    avance_serpent(ser);
    return 1;
}

int recherche_pomme(Monde mon, Case *c) {
    int i;
    int taille;

    assert(NULL != c);

    taille = mon.nb_pommes;

    for (i = 0; i < taille; i++) {
        if (mon.tab_pommes[i].pos.x == c->x && mon.tab_pommes[i].pos.y == c->y)
            return i;
    }
    return -1;
}

void supprimer_pomme_monde(Monde *mon, int indice_pomme) {
    int i;

    assert(NULL != mon);
    assert(indice_pomme >= 0);

    for (i = indice_pomme; i < mon->nb_pommes; i++)
        mon->tab_pommes[i] = mon->tab_pommes[i + 1];
    mon->nb_pommes -= 1;
}

int manger_pomme_serpent(Monde *mon) {
    int indice_pomme;
    int *score;
    Case c;
    Serpent *ser;

    assert(NULL != mon);


    ser = &(mon->serpent);
    score = &(mon->score);

    case_suivante(*ser, &c);
    if (case_occupee_pomme(mon, &c) == 0)
        return 0;

    indice_pomme = recherche_pomme(*mon, &c);

    if (mon->tab_pommes[indice_pomme].type == SUPER)
        *score += 2;
    else
        *score += 1;

    supprimer_pomme_monde(mon, indice_pomme);

    ser->taille += 1;
    avance_serpent(ser);

    return 1;
}

int case_occupee_poison(Monde *mon, Case *c) {
    int indice_poison;

    assert(NULL != mon);
    assert(NULL != c);

    indice_poison = recherche_pomme(*mon, c);

    if (mon->tab_pommes[indice_poison].type == POISON)
        return 0;
    return 1;
}

int mort_serpent(Monde *mon) {
    Case c;
    Serpent *ser;

    assert(NULL != mon);
    ser = &(mon->serpent);

    if (ser->mort == 1)
        return 1;
    
    case_suivante(*ser, &c);
    if (c.x < 0 || c.x >= M || c.y < 0 || c.y >= N || case_occupee_poison(mon, &c) == 0) {
        ser->mort = 1;
        return 1;
    }
    if (case_occupee_serp(&(mon->serpent), &c) == 1) {
        ser->mort = 1;
        return 1;
    }
    return 0;
}

void change_dir_serp(Monde *mon, MLV_Keyboard_button touche) {
    Serpent *ser;

    assert(NULL != mon);
	ser = &(mon->serpent);
    if (touche == MLV_KEYBOARD_UP && ser->dir != SUD)
        ser->dir = NORD;
    else if (touche == MLV_KEYBOARD_RIGHT && ser->dir != OUEST)
        ser->dir = EST;
    else if (touche == MLV_KEYBOARD_DOWN && ser->dir != NORD)
        ser->dir = SUD;
    else if (touche == MLV_KEYBOARD_LEFT && ser->dir != EST)
        ser->dir = OUEST;
}