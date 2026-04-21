/**
 * @file filter.h
 * @brief Fonctions de tri et de filtrage des super-héros.
 *
 * Contient :
 *  - le tri d'un tableau d'entiers parallèles
 *  - le tri des héros selon une powerstat
 *  - l'affichage d'une liste de héros à partir de leurs IDs
 *  - le menu de tri interactif
 *  - la collecte des critères de filtrage saisis par l'utilisateur
 *  - l'application d'un filtre à la liste des IDs
 *  - le menu de filtrage interactif
 */

#ifndef FILTER_H
#define FILTER_H

#include "../include/cJSON.h"

/**
 * @brief Trie deux tableaux en parallèle : sort_guider guide l'ordre,
 *        following_arr suit le même réarrangement (tri décroissant).
 *
 * @param sort_guider  Tableau de référence (les valeurs qui dictent l'ordre).
 * @param following_arr Tableau qui suit le même réarrangement.
 * @param arr_length   Taille des deux tableaux.
 * @return int*        Nouveau tableau following_arr trié (à libérer avec free()).
 */
int *sort_int_arrays(int *sort_guider, int *following_arr, int arr_length);

/**
 * @brief Renvoie un tableau d'IDs de héros triés par ordre décroissant
 *        selon la valeur d'une powerstat donnée.
 *
 * @param json              Tableau cJSON des héros.
 * @param stat_name         Nom de la stat ("intelligence", "strength"…).
 * @param current_hero_count Nombre de héros dans le tableau.
 * @return int*             Tableau d'IDs triés (à libérer avec free()).
 */
int *sort_heros_acc_to_stat(cJSON *json, char *stat_name, int current_hero_count);

/**
 * @brief Affiche les héros dont les IDs sont dans ids_arr.
 *        Les héros avec l'id -1 sont ignorés (filtrés).
 *
 * @param ids_arr    Tableau des IDs à afficher.
 * @param size_of_arr Taille du tableau.
 * @param stat_name  Nom de la stat à mettre en avant dans l'affichage.
 * @param json       Tableau cJSON des héros.
 * @param filtered   1 si on affiche la valeur de stat_name, 0 pour l'id brut.
 */
void display_from_ids(int *ids_arr, int size_of_arr, char *stat_name, cJSON *json, int filtered);

/**
 * @brief Menu interactif : demande une stat et affiche les héros triés par celle-ci.
 *        Boucle jusqu'à ce que l'utilisateur entre 'x'.
 *
 * @param json Tableau cJSON des héros.
 */
void handle_sort_heros(cJSON *json);

/**
 * @brief Demande à l'utilisateur une stat, un seuil (min ou max) et une limite.
 *        Retourne un tableau de 3 chaînes : {stat, "minimum"/"maximum", valeur}.
 *
 * @param json Tableau cJSON des héros (utilisé pour l'affichage du menu).
 * @return char** Tableau de 3 chaînes allouées dynamiquement, ou NULL si annulé.
 */
char **get_filter(cJSON *json);

/**
 * @brief Applique un filtre sur le tableau de héros.
 *        Les héros ne respectant pas le critère reçoivent l'id -1.
 *
 * @param filter_infos Tableau {stat, "minimum"/"maximum", valeur_limite}.
 * @param hero_count   Nombre total de héros.
 * @param json         Tableau cJSON des héros.
 * @return int*        Tableau d'IDs filtrés (à libérer avec free()).
 */
int *filter_ids_arr(char **filter_infos, int hero_count, cJSON *json);

/**
 * @brief Menu interactif de filtrage multi-critères.
 *        Permet d'enchaîner plusieurs filtres jusqu'à ce que l'utilisateur quitte.
 *
 * @param json Tableau cJSON des héros.
 */
void handle_filtering(cJSON *json);

#endif /* FILTER_H */
