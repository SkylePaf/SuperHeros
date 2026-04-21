/**
 * @file filter.c
 * @brief Tri et filtrage des super-héros selon leurs powerstats.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/filter.h"
#include "../include/utils.h"
#include "../include/colors.h"
#include "../include/cJSON.h"

/* ------------------------------------------------------------------ */
/*  Tri                                                                */
/* ------------------------------------------------------------------ */

int *sort_int_arrays(int *sort_guider, int *following_arr, int arr_length) {
    /* Copies de travail pour ne pas modifier les tableaux originaux */
    int *sorted_arr1 = malloc(arr_length * sizeof(int));
    int *sorted_arr2 = malloc(arr_length * sizeof(int));
    memcpy(sorted_arr1, sort_guider,    arr_length * sizeof(int));
    memcpy(sorted_arr2, following_arr,  arr_length * sizeof(int));

    /* Tri par sélection décroissant sur sorted_arr1 (les valeurs de stat) */
    for (int i = 0; i < arr_length; i++) {
        int maxi    = sorted_arr1[i];
        int index_j = i;

        for (int j = i + 1; j < arr_length; j++) {
            if (sorted_arr1[j] > maxi) {
                maxi    = sorted_arr1[j];
                index_j = j;
            }
        }

        /* Échange dans les deux tableaux pour garder la correspondance */
        if (index_j != i) {
            int tmp         = sorted_arr1[i];
            sorted_arr1[i]  = sorted_arr1[index_j];
            sorted_arr1[index_j] = tmp;

            tmp              = sorted_arr2[i];
            sorted_arr2[i]   = sorted_arr2[index_j];
            sorted_arr2[index_j] = tmp;
        }
    }

    free(sorted_arr1);
    return sorted_arr2; /* sorted_arr2 contient les IDs dans le bon ordre */
}

int *sort_heros_acc_to_stat(cJSON *json, char *stat_name, int current_hero_count) {
    int *id_sorted   = malloc(current_hero_count * sizeof(int));
    int *stat_values = malloc(current_hero_count * sizeof(int));

    for (int i = 0; i < current_hero_count; i++) {
        cJSON *hero       = cJSON_GetArrayItem(json, i);
        cJSON *hero_id    = cJSON_GetObjectItem(hero, "id");
        cJSON *powerstats = cJSON_GetObjectItem(hero, "powerstats");

        id_sorted[i] = hero_id->valueint;

        if (powerstats == NULL) {
            stat_values[i] = -1;
            continue;
        }

        cJSON *stat_item   = cJSON_GetObjectItem(powerstats, stat_name);
        stat_values[i]     = (stat_item != NULL) ? stat_item->valueint : -1;
    }

    id_sorted = sort_int_arrays(stat_values, id_sorted, current_hero_count);
    free(stat_values);
    return id_sorted;
}

/* ------------------------------------------------------------------ */
/*  Affichage depuis un tableau d'IDs                                  */
/* ------------------------------------------------------------------ */

void display_from_ids(int *ids_arr, int size_of_arr, char *stat_name, cJSON *json, int filtered) {
    system("cls");

    for (int i = 0; i < size_of_arr; i++) {

        /* Recherche du héros correspondant à l'id */
        for (int j = 0; j < size_of_arr; j++) {
            cJSON *hero    = cJSON_GetArrayItem(json, j);
            cJSON *name    = cJSON_GetObjectItem(hero, "name");
            cJSON *hero_id = cJSON_GetObjectItem(hero, "id");

            if (ids_arr[i] == hero_id->valueint && ids_arr[i] != -1) {
                cJSON *powerstats  = cJSON_GetObjectItem(hero, "powerstats");
                cJSON *stat_value  = cJSON_GetObjectItem(powerstats, stat_name);

                /* En mode non-filtré, on affiche l'id à la place de la stat */
                if (filtered == 0) stat_value = hero_id;

                cJSON *intelligence = cJSON_GetObjectItem(powerstats, "intelligence");
                cJSON *strength     = cJSON_GetObjectItem(powerstats, "strength");
                cJSON *speed        = cJSON_GetObjectItem(powerstats, "speed");
                cJSON *durability   = cJSON_GetObjectItem(powerstats, "durability");
                cJSON *power        = cJSON_GetObjectItem(powerstats, "power");
                cJSON *combat       = cJSON_GetObjectItem(powerstats, "combat");

                printf(GREEN_BOLD "[#######################################################]\n" RESET);
                printf(GREEN_BOLD "[##==> " RESET YELLOW_BOLD "%d - with " RED "%s" RESET YELLOW " at " RED "%s" RESET YELLOW " we got ---->\n" RESET,
                       i, stat_name, get_element_value(stat_value));
                printf(GREEN_BOLD "[#######################################################]\n" RESET);
                printf("\n");
                printf(CYAN_BOLD "+------------------------------------------------------+\n" RESET);
                printf(YELLOW "[==> %s ->\n" RESET, get_element_value(name));
                printf(CYAN "        - id : "         RESET BLUE "%s" RESET CYAN "\n", get_element_value(hero_id));
                printf(CYAN_BOLD "+-----------------------POWERSTATS---------------------+\n" RESET);
                printf(CYAN "     - Intelligence : "  RESET BLUE "%s" RESET CYAN "    ", get_element_value(intelligence));
                printf("- Strength : "   RESET BLUE "%s" RESET CYAN "\n", get_element_value(strength));
                printf(CYAN "     - Speed : "         RESET BLUE "%s" RESET CYAN "    ", get_element_value(speed));
                printf("- Durability : " RESET BLUE "%s" RESET CYAN "\n", get_element_value(durability));
                printf(CYAN "     - Power : "         RESET BLUE "%s" RESET CYAN "    ", get_element_value(power));
                printf("- Combat : "     RESET BLUE "%s" RESET CYAN "\n", get_element_value(combat));
                printf(CYAN_BOLD "+------------------------------------------------------+\n\n" RESET);
                break;
            }
        }
    }
    printf("\n");
}

/* ------------------------------------------------------------------ */
/*  Menus interactifs                                                  */
/* ------------------------------------------------------------------ */

void handle_sort_heros(cJSON *json) {
    char choix[100];
    int nmb_of_heros = cJSON_GetArraySize(json);

    system("cls");
    printf("\n\n");

    while (1) {
        printf(BLUE_BOLD "Possibilites de power stats :\n");
        printf("    'intelligence', 'strength', 'speed', \n");
        printf("    'durability', 'power', 'combat', \n\n" RESET);
        printf(CYAN "- Entrez un power-stat ( 'x' pour quitter ) :" RESET GREEN "\n>>> " RESET);
        scanf("%s", choix);
        wait_enter();

        if (strcmp(choix, "x") == 0 || strcmp(choix, "X") == 0) return;

        int *sorted_list = sort_heros_acc_to_stat(json, choix, nmb_of_heros);
        display_from_ids(sorted_list, nmb_of_heros, choix, json, 1);
        free(sorted_list);

        printf(GREEN "Press any key to skip." RESET);
        wait_enter();
        system("cls");
    }
}

char **get_filter(cJSON *json) {
    (void)json; /* paramètre non utilisé ici, conservé pour cohérence d'interface */

    char power_stat[20];
    char mini_maxi[20];
    char power_limit[10];
    char *possibilities[] = {"minimum", "maximum"};

    char **filter_infos = malloc(3 * sizeof(char *));

    printf("\n");
    printf(GREEN_BOLD "<{=====#################################################################=====}>\n" RESET);
    printf(GREEN_BOLD "                                   Filters                                   \n" RESET);
    printf(GREEN_BOLD "<{=====#################################################################=====}>\n" RESET);
    printf("\n\n");
    printf(BLUE_BOLD "Possibilites de power stats :\n");
    printf("    'intelligence', 'strength', 'speed', \n");
    printf("    'durability', 'power', 'combat', \n\n" RESET);
    printf(CYAN "- Entrez un power-stat a filtrer ( 'x' pour quitter ) :" RESET GREEN "\n>>> " RESET);
    scanf("%s", power_stat);
    wait_enter();

    if (strcmp(power_stat, "x") == 0 || strcmp(power_stat, "X") == 0) {
        free(filter_infos);
        return NULL;
    }
    filter_infos[0] = strdup(power_stat);

    printf(CYAN "\n\n- Minimum (0)   -    Maximum (1) :\n" RESET);
    printf(GREEN ">>> " RESET);
    int index;
    scanf("%d", &index);
    wait_enter();

    strcpy(mini_maxi, possibilities[index]);
    filter_infos[1] = strdup(mini_maxi);

    printf(CYAN "\n\n - Write a number between 0 and 100 that cannot be exceed :\n" RESET);
    printf(GREEN ">>> " RESET);
    scanf("%s", power_limit);
    wait_enter();
    filter_infos[2] = strdup(power_limit);

    return filter_infos;
}

int *filter_ids_arr(char **filter_infos, int hero_count, cJSON *json) {
    int *ids_arr   = malloc(hero_count * sizeof(int));
    int limit      = atoi(filter_infos[2]);
    int is_minimum = strcmp(filter_infos[1], "minimum") == 0;

    for (int i = 0; i < hero_count; i++) {
        cJSON *hero           = cJSON_GetArrayItem(json, i);
        cJSON *hero_id        = cJSON_GetObjectItem(hero, "id");
        cJSON *powerstats     = cJSON_GetObjectItem(hero, "powerstats");
        cJSON *powerstat_item = cJSON_GetObjectItem(powerstats, filter_infos[0]);

        int val  = atoi(get_element_value(powerstat_item));
        int keep = is_minimum ? (val >= limit) : (val <= limit);

        ids_arr[i] = keep ? atoi(get_element_value(hero_id)) : -1;
    }
    return ids_arr;
}

void handle_filtering(cJSON *json) {
    int hero_count   = cJSON_GetArraySize(json);
    int *filtered_ids = malloc(hero_count * sizeof(int));

    /* Initialisation : tous les héros sont visibles */
    for (int i = 0; i < hero_count; i++) {
        filtered_ids[i] = i;
    }

    while (1) {
        display_from_ids(filtered_ids, hero_count, "id", json, 0);

        char **filter_infos = get_filter(json);
        if (filter_infos == NULL) {
            free(filtered_ids);
            return;
        }

        /* Application du filtre et remplacement de la liste */
        int *new_filtered = filter_ids_arr(filter_infos, hero_count, json);
        free(filtered_ids);
        filtered_ids = new_filtered;

        display_from_ids(filtered_ids, hero_count, filter_infos[0], json, 1);

        /* Libération des critères de filtre */
        free(filter_infos[0]);
        free(filter_infos[1]);
        free(filter_infos[2]);
        free(filter_infos);

        char choice;
        printf(CYAN "Press 'c' to continue and enter a new filter or press 'x' to quit." RESET GREEN "\n>>> " RESET);
        scanf("%c", &choice);
        wait_enter();

        if (choice == 'x' || choice == 'X') {
            free(filtered_ids);
            return;
        }
    }
}
