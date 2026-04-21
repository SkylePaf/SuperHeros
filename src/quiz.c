/**
 * @file quiz.c
 * @brief Quiz : deviner le nom d'un super-héros à partir de ses powerstats.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#include "../include/quiz.h"
#include "../include/utils.h"
#include "../include/colors.h"
#include "../include/cJSON.h"

#define NB_QUESTIONS 5   /* Nombre de questions par partie */
#define POINTS_PER_WIN 10

void handle_quiz(cJSON *json) {
    srand(time(NULL)); /* Initialisation du générateur de nombres aléatoires */

    int nb_heroes   = cJSON_GetArraySize(json);
    int score       = 0;
    char answer[100];
    char *stats[] = {"intelligence", "strength", "speed", "durability", "power", "combat"};

    for (int q = 0; q < NB_QUESTIONS; q++) {

        /* Tirage d'un héros au hasard */
        int rand_index = rand() % nb_heroes;
        cJSON *hero    = cJSON_GetArrayItem(json, rand_index);
        char *name     = cJSON_GetObjectItem(hero, "name")->valuestring;
        cJSON *ps      = cJSON_GetObjectItem(hero, "powerstats");

        system("clear");
        printf(YELLOW_BOLD "\n[==========------- Question %d / %d -------==========]\n\n" RESET,
               q + 1, NB_QUESTIONS);
        printf(CYAN "     Powerstats of the mystery hero :\n\n" RESET);

        /* Affichage des 6 powerstats sans révéler le nom */
        for (int i = 0; i < 6; i++) {
            cJSON *v = cJSON_GetObjectItem(ps, stats[i]);
            printf(CYAN "     - %-15s : " RESET BLUE "%d\n" RESET,
                   stats[i], v ? v->valueint : -1);
        }

        printf("\n");
        printf(CYAN_BOLD "Who is this hero ?" RESET GREEN "\n>>> " RESET);
        scanf("%s", answer);
        wait_enter();

        /* Comparaison insensible à la casse */
        if (strcasecmp(answer, name) == 0) {
            printf(GREEN_BOLD "\n     Correct ! +%d points\n" RESET, POINTS_PER_WIN);
            score += POINTS_PER_WIN;
        } else {
            printf(RED "\n     Wrong ! The answer was : %s\n" RESET, name);
        }

        /* Option de quitter en cours de quiz */
        char choice;
        printf(GREEN "\nPress 'c' to continue or 'x' to quit." RESET GREEN "\n>>> " RESET);
        scanf("%c", &choice);
        wait_enter();

        if (choice == 'x' || choice == 'X') return;
    }

    /* Résultats finaux */
    system("clear");
    printf("\n");
    printf(YELLOW_BOLD "[==========------------Quiz Results------------==========]\n" RESET);
    printf(CYAN "\n     Your final score : " RESET BLUE_BOLD "%d / %d\n\n" RESET,
           score, NB_QUESTIONS * POINTS_PER_WIN);
    printf(YELLOW_BOLD "[========================================================]\n" RESET);
    printf(GREEN_BOLD "\nPress any key to leave." RESET);
    wait_enter();
}
