#include "snake.h"
#include "snake_graphique.h"

void jouer() {
    MLV_Keyboard_button touche;
    Monde m;

    m = init_monde(3);
    afficher_monde(&m);
    dessine_debut_partie();
    MLV_update_window();
    MLV_wait_keyboard(NULL, NULL, NULL);

    while (mort_serpent(&m) == 0) {
        if (deplacer_serpent(&m) == 0) {
            if (manger_pomme_serpent(&m) == 1)
                ajouter_pomme_monde(&m);
        }
        MLV_clear_window(MLV_COLOR_BLACK);
        afficher_monde(&m);
        MLV_update_window();
        touche = MLV_KEYBOARD_NONE;
        MLV_wait_keyboard_or_seconds(&touche, NULL, NULL, 1);
        change_dir_serp(&m, touche);
        if (touche == MLV_KEYBOARD_SPACE)
            pause();
    }
    dessine_fin_partie(m.score);

    MLV_update_window();
    MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, NULL, NULL);
}


int main() {
    srand(time(NULL));
    MLV_create_window("Serpent", "Serpent", LONGUEUR, HAUTEUR_FEN);
    jouer();
    MLV_free_window();

    return 0;
}