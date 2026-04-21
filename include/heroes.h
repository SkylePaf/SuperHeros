/**
 * @file heroes.h
 * @brief Fonctions d'affichage, de recherche et de comparaison des super-héros.
 *
 * Contient :
 *  - l'affichage de la liste simplifiée ou détaillée des héros
 *  - la recherche par ID ou par nom
 *  - la comparaison côte à côte de deux héros
 *  - l'affichage des liens externes d'un héros
 *  - l'animation de chargement
 */

#ifndef HEROES_H
#define HEROES_H

#include "../include/cJSON.h"

/**
 * @brief Affiche la liste complète des héros avec leurs infos de base
 *        (nom, id, genre, race).
 *
 * @param json Tableau cJSON contenant tous les héros.
 */
void print_basic_info(cJSON *json);

/**
 * @brief Affiche la liste simplifiée puis attend une touche pour revenir au menu.
 *
 * @param json Tableau cJSON contenant tous les héros.
 */
void handle_basic_info_display(cJSON *json);

/**
 * @brief Affiche TOUTES les informations d'un héros (stats, apparence…)
 *        puis attend une touche pour revenir.
 *
 * @param hero Objet cJSON représentant un héros unique.
 */
void print_all_info(cJSON *hero);

/**
 * @brief Demande un ID à l'utilisateur et affiche les détails du héros correspondant.
 *        Boucle jusqu'à ce que l'utilisateur entre -1.
 *
 * @param json Tableau cJSON contenant tous les héros.
 * @return int 1 si un héros a été trouvé, 0 sinon.
 */
int get_hero_by_ID(cJSON *json);

/**
 * @brief Demande un nom à l'utilisateur et affiche les détails du héros correspondant.
 *        Boucle jusqu'à ce que l'utilisateur laisse le champ vide.
 *
 * @param json Tableau cJSON contenant tous les héros.
 * @return int 1 si un héros a été trouvé, 0 sinon.
 */
int get_hero_by_name(cJSON *json);

/**
 * @brief Demande deux IDs et affiche les powerstats des deux héros en parallèle.
 *        Le meilleur score de chaque stat est mis en vert.
 *
 * @param json Tableau cJSON contenant tous les héros.
 */
void compare_heroes(cJSON *json);

/**
 * @brief Demande un ID et affiche les liens Wikipedia, SuperHeroDB et IMDb du héros.
 *        Boucle jusqu'à ce que l'utilisateur entre -1.
 *
 * @param json Tableau cJSON contenant tous les héros.
 */
void handle_links(cJSON *json);

/**
 * @brief Animation de chargement (affiche "Loading..." sur 4 secondes).
 */
void loader(void);

#endif /* HEROES_H */
