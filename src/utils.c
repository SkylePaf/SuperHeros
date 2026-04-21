/**
 * @file utils.c
 * @brief Implémentation des fonctions utilitaires générales.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"
#include "../include/cJSON.h"

/* ------------------------------------------------------------------ */
/*  Lecture / Écriture de fichiers                                     */
/* ------------------------------------------------------------------ */

char *read_JSON_file(const char *file_name) {
    FILE *f = fopen(file_name, "rb");
    if (f == NULL) {
        printf("Error opening file !\n");
        return NULL;
    }

    /* Calcul de la taille du fichier */
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    /* Allocation et lecture */
    char *data = malloc(file_size + 1);
    fread(data, 1, file_size, f);
    fclose(f);

    data[file_size] = '\0'; /* Terminaison de la chaîne */
    return data;
}

void write_JSON_file(const char *file_name, cJSON *json) {
    char *string = cJSON_Print(json);

    FILE *f = fopen(file_name, "w");
    if (f == NULL) {
        printf("Error opening file !\n");
        free(string);
        return;
    }

    fprintf(f, "%s", string);
    fclose(f);
    free(string);
}

/* ------------------------------------------------------------------ */
/*  Outils divers                                                      */
/* ------------------------------------------------------------------ */

char *int_to_str(int nmb) {
    char *str = malloc(20 * sizeof(char));
    snprintf(str, 20, "%d", nmb);
    return str;
}

void wait_enter(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char *get_element_value(cJSON *element) {
    if (element == NULL) {
        return "Unknown";
    }
    if (cJSON_IsString(element)) {
        return element->valuestring;
    }
    if (cJSON_IsNumber(element)) {
        return int_to_str(element->valueint);
    }
    return "Unknown";
}
