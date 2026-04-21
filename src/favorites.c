/**
 * @file favorites.c
 * @brief Gestion des super-héros favoris (ajout, suppression, sauvegarde).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/favorites.h"
#include "../include/utils.h"
#include "../include/colors.h"
#include "../include/cJSON.h"

#define FAVORITES_FILE "./json/favorites.json"

/* ------------------------------------------------------------------ */
/*  Chargement                                                         */
/* ------------------------------------------------------------------ */

cJSON *load_favorites_json(void) {
    FILE *f = fopen(FAVORITES_FILE, "r");
    if (f == NULL) {
        /* Fichier inexistant : on part d'un tableau vide */
        return cJSON_CreateArray();
    }

    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *data = malloc(file_size + 1);
    fread(data, 1, file_size, f);
    fclose(f);
    data[file_size] = '\0';

    cJSON *json = cJSON_Parse(data);
    free(data);

    if (json == NULL) return cJSON_CreateArray();
    return json;
}

/* ------------------------------------------------------------------ */
/*  Menu interactif                                                    */
/* ------------------------------------------------------------------ */

void handle_favorites(cJSON *json) {
    cJSON *fav_json = load_favorites_json();

    while (1) {
        system("clear");
        printf("\n");
        printf(YELLOW_BOLD "[==========-------------Favorites--------------==========]\n" RESET);
        printf(CYAN "\n     Your favorites :\n\n" RESET);

        int fav_count = cJSON_GetArraySize(fav_json);

        if (fav_count == 0) {
            printf(RED "     No favorites yet !\n" RESET);
        }

        /* Affichage de la liste des favoris */
        for (int i = 0; i < fav_count; i++) {
            cJSON *fav_hero = cJSON_GetArrayItem(fav_json, i);
            cJSON *name     = cJSON_GetObjectItem(fav_hero, "name");
            cJSON *id       = cJSON_GetObjectItem(fav_hero, "id");
            printf(BLUE "     [%d] %s\n" RESET, id->valueint, name->valuestring);
        }

        printf("\n");
        printf(YELLOW_BOLD "[========================================================]\n" RESET);
        printf(BLUE_BOLD "    (1)  : Add a hero to favorites\n" RESET);
        printf(BLUE_BOLD "    (2)  : Remove a hero from favorites\n" RESET);
        printf(BLUE_BOLD "    (-1) : Back\n" RESET);
        printf(GREEN "\n>>> " RESET);

        int choice;
        scanf("%d", &choice);
        wait_enter();

        /* --- Retour au menu principal : sauvegarde et sortie --- */
        if (choice == -1) {
            write_JSON_file(FAVORITES_FILE, fav_json);
            cJSON_Delete(fav_json);
            return;
        }

        /* --- Ajout d'un héros --- */
        if (choice == 1) {
            printf(CYAN "\n- Entrez l'ID du hero a ajouter :" RESET GREEN "\n>>> " RESET);
            int new_id;
            scanf("%d", &new_id);
            wait_enter();

            /* Recherche du héros dans la base principale */
            cJSON *hero_to_add = NULL;
            for (int i = 0; i < cJSON_GetArraySize(json); i++) {
                cJSON *hero = cJSON_GetArrayItem(json, i);
                if (cJSON_GetObjectItem(hero, "id")->valueint == new_id) {
                    hero_to_add = hero;
                    break;
                }
            }

            if (hero_to_add == NULL) {
                printf(RED "\nERROR : Hero with ID %d does not exist !\n" RESET, new_id);
                printf(GREEN "Press any key to continue." RESET);
                wait_enter();
                continue;
            }

            /* Vérification que le héros n'est pas déjà en favori */
            int already = 0;
            for (int i = 0; i < cJSON_GetArraySize(fav_json); i++) {
                cJSON *fav = cJSON_GetArrayItem(fav_json, i);
                if (cJSON_GetObjectItem(fav, "id")->valueint == new_id) {
                    already = 1;
                    break;
                }
            }

            if (!already) {
                cJSON_AddItemToArray(fav_json, cJSON_Duplicate(hero_to_add, 1));
                printf(GREEN "\nHero added to favorites.\n" RESET);
            } else {
                printf(YELLOW "\nHero is already in favorites !\n" RESET);
            }
            printf(GREEN "Press any key to continue." RESET);
            wait_enter();
        }

        /* --- Suppression d'un héros --- */
        if (choice == 2) {
            printf(CYAN "\n- Entrez l'ID du hero a retirer :" RESET GREEN "\n>>> " RESET);
            int rem_id;
            scanf("%d", &rem_id);
            wait_enter();

            int removed = 0;
            for (int i = 0; i < cJSON_GetArraySize(fav_json); i++) {
                cJSON *fav = cJSON_GetArrayItem(fav_json, i);
                if (cJSON_GetObjectItem(fav, "id")->valueint == rem_id) {
                    cJSON_DeleteItemFromArray(fav_json, i);
                    removed = 1;
                    break;
                }
            }

            if (removed) {
                printf(GREEN "\nHero removed from favorites.\n" RESET);
            } else {
                printf(RED "\nHero not found in favorites !\n" RESET);
            }
            printf(GREEN "Press any key to continue." RESET);
            wait_enter();
        }
    }
}
