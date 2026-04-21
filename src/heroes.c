/**
 * @file heroes.c
 * @brief Affichage, recherche et comparaison des super-héros.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "../include/heroes.h"
#include "../include/utils.h"
#include "../include/colors.h"
#include "../include/cJSON.h"

/* ------------------------------------------------------------------ */
/*  Affichage                                                          */
/* ------------------------------------------------------------------ */

void print_basic_info(cJSON *json) {
    system("cls");

    for (int i = 0; i < cJSON_GetArraySize(json); i++) {
        cJSON *hero       = cJSON_GetArrayItem(json, i);
        cJSON *name       = cJSON_GetObjectItem(hero, "name");
        cJSON *id         = cJSON_GetObjectItem(hero, "id");
        cJSON *appearance = cJSON_GetObjectItem(hero, "appearance");
        cJSON *gender     = cJSON_GetObjectItem(appearance, "gender");
        cJSON *race       = cJSON_GetObjectItem(appearance, "race");

        printf(YELLOW_BOLD "\n|========================================================|\n" RESET);
        printf(BLUE "    Hero - %d: \n\n" RESET, i);
        printf(CYAN "        - Name : " RESET BLUE "%s" RESET CYAN "\n", get_element_value(name));
        printf("        - id : "   RESET BLUE "%s" RESET CYAN "\n", get_element_value(id));
        printf("        - gender : "RESET BLUE "%s" RESET CYAN "\n", get_element_value(gender));
        printf("        - race : "  RESET BLUE "%s" RESET CYAN "\n" RESET, get_element_value(race));
        printf(YELLOW_BOLD "\n|========================================================|\n\n" RESET);
    }
}

void handle_basic_info_display(cJSON *json) {
    print_basic_info(json);
    printf(GREEN_BOLD "Press any key to leave." RESET);
    wait_enter();
}

void print_all_info(cJSON *hero) {
    /* --- Récupération des champs --- */
    cJSON *name   = cJSON_GetObjectItem(hero, "name");
    cJSON *id     = cJSON_GetObjectItem(hero, "id");
    cJSON *id_api = cJSON_GetObjectItem(hero, "id-api");
    cJSON *slug   = cJSON_GetObjectItem(hero, "slug");

    cJSON *powerstats  = cJSON_GetObjectItem(hero, "powerstats");
    cJSON *intelligence= cJSON_GetObjectItem(powerstats, "intelligence");
    cJSON *strength    = cJSON_GetObjectItem(powerstats, "strength");
    cJSON *speed       = cJSON_GetObjectItem(powerstats, "speed");
    cJSON *durability  = cJSON_GetObjectItem(powerstats, "durability");
    cJSON *power       = cJSON_GetObjectItem(powerstats, "power");
    cJSON *combat      = cJSON_GetObjectItem(powerstats, "combat");

    cJSON *appearance  = cJSON_GetObjectItem(hero, "appearance");
    cJSON *gender      = cJSON_GetObjectItem(appearance, "gender");
    cJSON *race        = cJSON_GetObjectItem(appearance, "race");
    cJSON *height      = cJSON_GetObjectItem(appearance, "height");
    cJSON *US_height   = cJSON_GetArrayItem(height, 0);
    cJSON *EU_height   = cJSON_GetArrayItem(height, 1);
    cJSON *weight      = cJSON_GetObjectItem(appearance, "weight");
    cJSON *US_weight   = cJSON_GetArrayItem(weight, 0);
    cJSON *EU_weight   = cJSON_GetArrayItem(weight, 1);
    cJSON *eyeColor    = cJSON_GetObjectItem(appearance, "eyeColor");
    cJSON *hairColor   = cJSON_GetObjectItem(appearance, "hairColor");

    /* --- Affichage --- */
    system("cls");
    printf("\n");

    printf(YELLOW_BOLD "[==========--------------Headers---------------==========]" RESET "\n");
    printf(CYAN "                                                          " "\n");
    printf(BLUE_BOLD "     Name : %s                      ID : %s           " RESET "\n",
           get_element_value(name), get_element_value(id));
    printf(CYAN "                                                          " "\n");
    printf("     - ID API : " RESET BLUE "%s" RESET CYAN "    ", get_element_value(id_api));
    printf("- SLUG : " RESET BLUE "%s" RESET CYAN "           \n", get_element_value(slug));
    printf("                                                          " RESET "\n");

    printf(YELLOW_BOLD "[==========-------------PowerStats-------------==========]\n");
    printf(CYAN "                                                          \n");
    printf("     - Intelligence : " RESET BLUE "%s" RESET CYAN "    ", get_element_value(intelligence));
    printf("- Strength : "  RESET BLUE "%s" RESET CYAN "\n", get_element_value(strength));
    printf("     - Speed : " RESET BLUE "%s" RESET CYAN "    ", get_element_value(speed));
    printf("- Durability : " RESET BLUE "%s" RESET CYAN "\n", get_element_value(durability));
    printf(CYAN "                                                          " RESET "\n");
    printf(CYAN "     - Power : " RESET BLUE "%s" RESET CYAN "    ", get_element_value(power));
    printf("- Combat : " RESET BLUE "%s" RESET CYAN "\n", get_element_value(combat));
    printf("                                                          " RESET "\n");

    printf(YELLOW_BOLD "[==========-------------Appearence-------------==========]\n");
    printf(CYAN "                                                          \n");
    printf("     - Gender : " RESET BLUE "%s" RESET CYAN "    ", get_element_value(gender));
    printf("- Race : " RESET BLUE "%s" RESET CYAN "\n", get_element_value(race));
    printf("     - Height :\n");
    printf("        -> US : " RESET BLUE "%s" RESET CYAN "    ", get_element_value(US_height));
    printf("-> EU : " RESET BLUE "%s" RESET CYAN "\n", get_element_value(EU_height));
    printf("     - Weight :\n");
    printf("        -> US : " RESET BLUE "%s" RESET CYAN "    ", get_element_value(US_weight));
    printf("-> EU : " RESET BLUE "%s" RESET CYAN "\n", get_element_value(EU_weight));
    printf("     - EyeColor : " RESET BLUE "%s" RESET CYAN "    ", get_element_value(eyeColor));
    printf("- HairColor : " RESET BLUE "%s" RESET CYAN "\n", get_element_value(hairColor));
    printf("                                                          " RESET "\n");
    printf(YELLOW_BOLD "[============-------------------------------=============]" RESET "\n");

    printf(GREEN_BOLD "Press any key to leave." RESET);
    wait_enter();
}

/* ------------------------------------------------------------------ */
/*  Recherche                                                          */
/* ------------------------------------------------------------------ */

int get_hero_by_ID(cJSON *json) {
    int id_asked = 0;

    system("cls");
    printf("\n\n");

    while (id_asked != -1) {
        printf(CYAN_BOLD "- Entrez un id ( -1 pour quitter ) :" RESET GREEN "\n>>> " RESET);
        scanf("%d", &id_asked);
        wait_enter();

        /* Parcours du tableau pour trouver l'id */
        for (int i = 0; i < cJSON_GetArraySize(json); i++) {
            cJSON *hero = cJSON_GetArrayItem(json, i);
            int id = cJSON_GetObjectItem(hero, "id")->valueint;

            if (id == id_asked) {
                print_all_info(hero);
                return 1;
            }
        }

        system("cls");
        printf(RED "ERROR : Hero at ID %d does not exist !\n\n" RESET, id_asked);
    }
    return 0;
}

int get_hero_by_name(cJSON *json) {
    char name_asked[100];

    system("cls");
    printf("\n\n");

    while (1) {
        printf(CYAN_BOLD "- Entrez un nom ( 'x' pour quitter ) :" RESET GREEN "\n>>> " RESET);
        scanf("%s", name_asked);
        wait_enter();

        if (strcmp(name_asked, "x") == 0) break;

        /* Comparaison insensible à la casse */
        for (int i = 0; i < cJSON_GetArraySize(json); i++) {
            cJSON *hero = cJSON_GetArrayItem(json, i);
            char *name  = cJSON_GetObjectItem(hero, "name")->valuestring;

            if (strcasecmp(name, name_asked) == 0) {
                print_all_info(hero);
                return 1;
            }
        }

        system("cls");
        printf(RED "ERROR : Hero '%s' does not exist !\n\n" RESET, name_asked);
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/*  Comparaison                                                        */
/* ------------------------------------------------------------------ */

void compare_heroes(cJSON *json) {
    int id1, id2;

    system("cls");
    printf("\n\n");

    printf(CYAN_BOLD "- Entrez l'ID du premier hero :" RESET GREEN "\n>>> " RESET);
    scanf("%d", &id1);
    wait_enter();

    printf(CYAN_BOLD "- Entrez l'ID du deuxieme hero :" RESET GREEN "\n>>> " RESET);
    scanf("%d", &id2);
    wait_enter();

    cJSON *hero1 = NULL;
    cJSON *hero2 = NULL;

    /* Recherche des deux héros par leur id */
    for (int i = 0; i < cJSON_GetArraySize(json); i++) {
        cJSON *hero = cJSON_GetArrayItem(json, i);
        int id = cJSON_GetObjectItem(hero, "id")->valueint;
        if (id == id1) hero1 = hero;
        if (id == id2) hero2 = hero;
    }

    if (hero1 == NULL || hero2 == NULL) {
        system("cls");
        printf(RED "\nERROR : One of the heroes does not exist !\n\n" RESET);
        printf(GREEN_BOLD "Press any key to leave." RESET);
        wait_enter();
        return;
    }

    char *name1 = cJSON_GetObjectItem(hero1, "name")->valuestring;
    char *name2 = cJSON_GetObjectItem(hero2, "name")->valuestring;
    cJSON *ps1  = cJSON_GetObjectItem(hero1, "powerstats");
    cJSON *ps2  = cJSON_GetObjectItem(hero2, "powerstats");

    char *stats[] = {"intelligence", "strength", "speed", "durability", "power", "combat"};

    system("cls");
    printf("\n");
    printf(YELLOW_BOLD "[==========-------------Comparison-------------==========]\n" RESET);
    printf(CYAN "     %-20s %-15s %-15s\n" RESET, "STAT", name1, name2);
    printf(YELLOW_BOLD "[========================================================]\n" RESET);

    for (int i = 0; i < 6; i++) {
        cJSON *v1 = cJSON_GetObjectItem(ps1, stats[i]);
        cJSON *v2 = cJSON_GetObjectItem(ps2, stats[i]);
        int val1 = (v1 != NULL) ? v1->valueint : -1;
        int val2 = (v2 != NULL) ? v2->valueint : -1;

        /* Coloration : vert pour le meilleur score */
        char *color1 = (val1 >= val2) ? GREEN_BOLD : RED;
        char *color2 = (val2 >= val1) ? GREEN_BOLD : RED;

        printf(CYAN "     %-20s " RESET, stats[i]);
        printf("%s%-15d" RESET, color1, val1);
        printf("%s%-15d\n" RESET, color2, val2);
    }

    printf(YELLOW_BOLD "[========================================================]\n" RESET);
    printf(GREEN_BOLD "\nPress any key to leave." RESET);
    wait_enter();
}

/* ------------------------------------------------------------------ */
/*  Liens externes                                                     */
/* ------------------------------------------------------------------ */

void handle_links(cJSON *json) {
    system("cls");
    printf("\n\n");

    while (1) {
        printf(CYAN_BOLD "- Entrez l'ID du hero ( -1 pour quitter ) :" RESET GREEN "\n>>> " RESET);
        int id_asked;
        scanf("%d", &id_asked);
        wait_enter();

        if (id_asked == -1) return;

        cJSON *found_hero = NULL;
        for (int i = 0; i < cJSON_GetArraySize(json); i++) {
            cJSON *hero = cJSON_GetArrayItem(json, i);
            if (cJSON_GetObjectItem(hero, "id")->valueint == id_asked) {
                found_hero = hero;
                break;
            }
        }

        if (found_hero == NULL) {
            system("cls");
            printf(RED "ERROR : Hero at ID %d does not exist !\n\n" RESET, id_asked);
            continue;
        }

        char *name = cJSON_GetObjectItem(found_hero, "name")->valuestring;
        char *slug = cJSON_GetObjectItem(found_hero, "slug")->valuestring;

        /* Remplacement des espaces par '_' pour l'URL Wikipedia */
        char wiki_name[100];
        strcpy(wiki_name, name);
        for (int i = 0; wiki_name[i] != '\0'; i++) {
            if (wiki_name[i] == ' ') wiki_name[i] = '_';
        }

        system("cls");
        printf("\n");
        printf(YELLOW_BOLD "[==========----------- Links for %s -----------==========]\n\n" RESET, name);
        printf(CYAN "     Wikipedia     : " RESET BLUE "https://en.wikipedia.org/wiki/%s\n" RESET, wiki_name);
        printf(CYAN "     SuperHero DB  : " RESET BLUE "https://www.superherodb.com/%s/\n" RESET, slug);
        printf(CYAN "     IMDb (search) : " RESET BLUE "https://www.imdb.com/find/?q=%s\n" RESET, wiki_name);
        printf("\n");
        printf(YELLOW_BOLD "[========================================================]\n" RESET);
        printf(GREEN_BOLD "\nPress any key to continue." RESET);
        wait_enter();

        system("cls");
        printf("\n\n");
    }
}

/* ------------------------------------------------------------------ */
/*  Animation de chargement   non-utilisée                            */
/* ------------------------------------------------------------------ */

void loader(void) {
    char *loading_message[] = {"Loading", "Loading.", "Loading..", "Loading..."};
    int count = 4;
    for (int i = 0; i < count; i++) {
        system("cls");
        printf("%s\n", loading_message[i]);
        fflush(stdout);
        sleep(1);
    }
}
