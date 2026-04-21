/**
 * @file main.c
 * @brief Point d'entrée du programme SuperHero DataBase.
 *
 * Charge les données JSON et affiche le menu principal en boucle.
 * Chaque option du menu délègue le travail à un module spécialisé.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/cJSON.h"
#include "../include/colors.h"
#include "../include/utils.h"
#include "../include/heroes.h"
#include "../include/filter.h"
#include "../include/favorites.h"
#include "../include/quiz.h"

#define DATA_FILE "./json/DATA.json"

/* ------------------------------------------------------------------ */
/*  Affichage du menu principal                                        */
/* ------------------------------------------------------------------ */

static void print_menu(void) {
    system("cls");   // "clear fontionne sur linux mais pas sur micrsoft : pour microsoft, il faut "cls".
    printf(YELLOW_BOLD "[==========------------------------------------==========]\n" RESET);
    printf(BLUE_BOLD "\n");
    printf("            You are in the SuperHero DATA-BASE.\n");
    printf("\n");
    printf("    Press a number to process the corresponding request\n");
    printf("\n" RESET);
    printf(YELLOW_BOLD "[========================================================]\n" RESET);
    printf(CYAN_BOLD "\n" RESET);
    printf(BLUE_BOLD "    (0)  :" RESET CYAN_BOLD " Get a simple-view of the current DATA-BASE\n"       RESET);
    printf(BLUE_BOLD "    (1)  :" RESET CYAN_BOLD " Get full info of an Hero with his ID\n"              RESET);
    printf(BLUE_BOLD "    (2)  :" RESET CYAN_BOLD " Get full info of an Hero with his name\n"            RESET);
    printf(BLUE_BOLD "    (3)  :" RESET CYAN_BOLD " Sort SuperHeroes according to a certain stat\n"     RESET);
    printf(BLUE_BOLD "    (4)  :" RESET CYAN_BOLD " Filter the SuperHeroes according to your likings\n" RESET);
    printf(BLUE_BOLD "    (5)  :" RESET CYAN_BOLD " Compare two SuperHeroes side by side\n"              RESET);
    printf(BLUE_BOLD "    (6)  :" RESET CYAN_BOLD " Manage your favorite SuperHeroes\n"                  RESET);
    printf(BLUE_BOLD "    (7)  :" RESET CYAN_BOLD " Quiz, Guess the SuperHero.\n"                        RESET);
    printf(BLUE_BOLD "    (8)  :" RESET CYAN_BOLD " Get links and references for a SuperHero\n"          RESET);
    printf(BLUE_BOLD "    (-1) :" RESET CYAN_BOLD " Quit\n\n");
    printf(YELLOW_BOLD "[==========------------------------------------==========]\n\n" RESET);
    printf(GREEN ">>> " RESET);
}

/* ------------------------------------------------------------------ */
/*  Main                                                               */
/* ------------------------------------------------------------------ */

int main(void) {
    /* Chargement de la base de données */
    char *data = read_JSON_file(DATA_FILE);
    if (data == NULL) return 1;

    cJSON *jsonData = cJSON_Parse(data);
    free(data);

    if (jsonData == NULL) {
        printf(RED "ERROR : Failed to parse JSON file !\n" RESET);
        return 1;
    }

    printf("Welcome to the SuperHero database !\n\n");
    sleep(1);

    int choix = 0;

    while (choix != -1) {
        print_menu();
        scanf("%d", &choix);
        wait_enter();

        switch (choix) {
            case 0:  handle_basic_info_display(jsonData); break;
            case 1:  get_hero_by_ID(jsonData);            break;
            case 2:  get_hero_by_name(jsonData);          break;
            case 3:  handle_sort_heros(jsonData);         break;
            case 4:  handle_filtering(jsonData);          break;
            case 5:  compare_heroes(jsonData);            break;
            case 6:  handle_favorites(jsonData);          break;
            case 7:  handle_quiz(jsonData);               break;
            case 8:  handle_links(jsonData);              break;
            default: break;
        }
    }

    cJSON_Delete(jsonData);
    return 0;
}
