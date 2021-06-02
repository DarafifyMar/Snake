#include "snake_graphique.h"

void afficher_quadrillage(Monde *mon) {
    int i, j;
    MLV_Image* image;

    assert(NULL != mon);

    image = MLV_load_image("images/case1.jpg");
    MLV_resize_image_with_proportions(image, TAILLE_CASE, TAILLE_CASE);

    for (j = 0; j < N; j++) {
        for (i = 0; i < M; i++)
            MLV_draw_image(image, i * TAILLE_CASE, j * TAILLE_CASE);
    }

    MLV_free_image(image);
}

void afficher_pomme(Pomme *pom) {
    MLV_Image* image;

    assert(NULL != pom);

    if (pom->type == POISON)
        image = MLV_load_image("images/pomme_poison.jpg");
    else if (pom->type == SUPER)
        image = MLV_load_image("images/pomme_super.jpg");
    else
        image = MLV_load_image("images/pomme_normal.jpg");

    MLV_resize_image_with_proportions(image, TAILLE_CASE, TAILLE_CASE);
    MLV_draw_image(image, pom->pos.x * TAILLE_CASE, pom->pos.y * TAILLE_CASE);
    MLV_free_image(image);
}

void afficher_score(Monde *mon) {
    char chaine[8];

    assert(NULL != mon);

    sprintf(chaine, "%d", mon->score);
    MLV_draw_text_box(0, HAUTEUR, 5 * TAILLE_CASE, 3 * TAILLE_CASE,
        chaine, 0, MLV_COLOR_SEAGREEN, MLV_COLOR_GREEN, MLV_COLOR_OLIVEDRAB,
        MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

void afficher_tete_serp(Serpent *ser, MLV_Image* image) {
    Case c;

    assert(NULL != ser);
    assert(NULL != image);

    c = ser->tab_serp[0];

    if (ser->dir == NORD) {
        MLV_draw_partial_image(image, 3 * TAILLE_CASE, 0, TAILLE_CASE, TAILLE_CASE,
            c.x * TAILLE_CASE, c.y * TAILLE_CASE);
    }
    else if (ser->dir == EST) {
        MLV_draw_partial_image(image, 4 * TAILLE_CASE, 0, TAILLE_CASE, TAILLE_CASE,
            c.x * TAILLE_CASE, c.y * TAILLE_CASE);
    }
    else if (ser->dir == SUD) {
        MLV_draw_partial_image(image, 4 * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE, TAILLE_CASE,
            c.x * TAILLE_CASE, c.y * TAILLE_CASE);
    }
    else {
        MLV_draw_partial_image(image, 3 * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE, TAILLE_CASE,
            c.x * TAILLE_CASE, c.y * TAILLE_CASE);
    }
}


void afficher_corps_serp(Serpent *ser, MLV_Image* image) {
    int i;
    Case prec, actuelle, suiv;

    assert(NULL != ser);
    assert(NULL != image);

    for (i = 1; i < ser->taille - 1; i++) {
        prec = ser->tab_serp[i - 1];
        actuelle = ser->tab_serp[i];
        suiv = ser->tab_serp[i + 1];

        if (prec.x < suiv.x && prec.y < suiv.y) {
            if (actuelle.y > prec.y)
                MLV_draw_partial_image(image, 0, TAILLE_CASE, TAILLE_CASE, TAILLE_CASE,
                    actuelle.x * TAILLE_CASE, actuelle.y * TAILLE_CASE);
            else
                MLV_draw_partial_image(image, 2 * TAILLE_CASE, 0, TAILLE_CASE, TAILLE_CASE,
                    actuelle.x * TAILLE_CASE, actuelle.y * TAILLE_CASE);
        }
        else if (prec.x < suiv.x && prec.y > suiv.y) {
            if (actuelle.x > prec.x)
                MLV_draw_partial_image(image, 2 * TAILLE_CASE, 2 * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE,
                    actuelle.x * TAILLE_CASE, actuelle.y * TAILLE_CASE);
            else
                MLV_draw_partial_image(image, 0, 0, TAILLE_CASE, TAILLE_CASE,
                    actuelle.x * TAILLE_CASE, actuelle.y * TAILLE_CASE);
        }
        else if (prec.x > suiv.x && prec.y < suiv.y) {
            if (actuelle.x < prec.x) 
                MLV_draw_partial_image(image, 0, 0, TAILLE_CASE, TAILLE_CASE,
                    actuelle.x * TAILLE_CASE, actuelle.y * TAILLE_CASE);
            else
                MLV_draw_partial_image(image, 2 * TAILLE_CASE, 2 * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE,
                    actuelle.x * TAILLE_CASE, actuelle.y * TAILLE_CASE);
        }
        else if (prec.x > suiv.x && prec.y > suiv.y) {
            if (actuelle.y < prec.y)
                MLV_draw_partial_image(image, 2 * TAILLE_CASE, 0, TAILLE_CASE, TAILLE_CASE,
                    actuelle.x * TAILLE_CASE, actuelle.y * TAILLE_CASE);
            else
                MLV_draw_partial_image(image, 0, TAILLE_CASE, TAILLE_CASE, TAILLE_CASE,
                    actuelle.x * TAILLE_CASE, actuelle.y * TAILLE_CASE);
        }
        else if (prec.x == suiv.x)
            MLV_draw_partial_image(image, 2 * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE, TAILLE_CASE,
                actuelle.x * TAILLE_CASE, actuelle.y * TAILLE_CASE);
        else
            MLV_draw_partial_image(image, TAILLE_CASE, 0, TAILLE_CASE, TAILLE_CASE,
                actuelle.x * TAILLE_CASE, actuelle.y * TAILLE_CASE);
    }
}

void afficher_queue_serp(Serpent *ser, MLV_Image* image) {
    Case prec, queue;

    queue = ser->tab_serp[ser->taille - 1];
    prec = ser->tab_serp[ser->taille - 2];

    assert(NULL != ser);
    assert(NULL != image);

    if (queue.x < prec.x) {
        MLV_draw_partial_image(image, 4 * TAILLE_CASE, 2 * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE,
            queue.x * TAILLE_CASE, queue.y * TAILLE_CASE);
    }
    else if (queue.x > prec.x) {
        MLV_draw_partial_image(image, 3 * TAILLE_CASE, 3 * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE,
            queue.x * TAILLE_CASE, queue.y * TAILLE_CASE);
    }
    else if (queue.y < prec.y) {
        MLV_draw_partial_image(image, 4 * TAILLE_CASE, 3 * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE,
            queue.x * TAILLE_CASE, queue.y * TAILLE_CASE);
    }
    else {
        MLV_draw_partial_image(image, 3 * TAILLE_CASE, 2 * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE,
            queue.x * TAILLE_CASE, queue.y * TAILLE_CASE);
    }
}

void afficher_serpent(Serpent *ser, MLV_Image* image) {
    assert(NULL != ser);
    assert(NULL != image);

    if (ser->taille >= 4) {
        MLV_resize_image_with_proportions(image, 5 * TAILLE_CASE, 4 * TAILLE_CASE);
        afficher_tete_serp(ser, image);
        afficher_corps_serp(ser, image);
        afficher_queue_serp(ser, image);
    }
}

void afficher_monde(Monde *mon) {
    int i;
    MLV_Image* serp;

    assert(NULL != mon);

    serp = MLV_load_image("images/snake.jpg");
    afficher_quadrillage(mon);
    for (i = 0; i < mon->nb_pommes; i++) {
        afficher_pomme(&(mon->tab_pommes[i]));
    }

    afficher_serpent(&(mon->serpent), serp);
    afficher_score(mon);

    MLV_free_image(serp);

}

void dessine_debut_partie() {
    MLV_draw_text_box(3 * LONGUEUR / 8, 3 * HAUTEUR / 8, LONGUEUR / 4, HAUTEUR / 4,
        "Appuyer sur une touche...", 0, MLV_COLOR_DODGERBLUE, MLV_COLOR_GREEN, MLV_COLOR_ROYAL_BLUE,
        MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

void dessine_fin_partie(int score) {
    char chaine[32];

    sprintf(chaine, "Perdu!\n Score : %d", score);
    MLV_draw_text_box(3 * LONGUEUR / 8, 3 * HAUTEUR / 8, LONGUEUR / 4, HAUTEUR / 4,
        chaine, 0, MLV_COLOR_DODGERBLUE, MLV_COLOR_GREEN, MLV_COLOR_ROYAL_BLUE,
        MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

void pause() {
    MLV_Keyboard_button touche;

    touche = MLV_KEYBOARD_NONE;
    dessine_pause();
    MLV_update_window();
    while (touche != MLV_KEYBOARD_SPACE)
        MLV_wait_keyboard(&touche, NULL, NULL);
}

void dessine_pause() {
    MLV_draw_text_box(3 * LONGUEUR / 8, 3 * HAUTEUR / 8, LONGUEUR / 4, HAUTEUR / 4,
        "Partie en pause.\nAppuyer sur la touche espace.", 0, MLV_COLOR_DODGERBLUE, MLV_COLOR_GREEN, MLV_COLOR_ROYAL_BLUE,
        MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}
