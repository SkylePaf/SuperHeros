/**
 * @file favorites.h
 * @brief Gestion de la liste des super-héros favoris.
 *
 * Les favoris sont sauvegardés dans ./json/favorites.json.
 * L'utilisateur peut ajouter ou retirer des héros de cette liste.
 */

#ifndef FAVORITES_H
#define FAVORITES_H

#include "../include/cJSON.h"

/**
 * @brief Charge le fichier favorites.json et renvoie son contenu sous forme de tableau cJSON.
 *        Si le fichier n'existe pas ou est invalide, renvoie un tableau vide.
 *
 * @return cJSON* Tableau cJSON des favoris (à libérer avec cJSON_Delete()).
 */
cJSON *load_favorites_json(void);

/**
 * @brief Menu interactif de gestion des favoris.
 *        Permet d'ajouter (1) ou retirer (2) des héros, et sauvegarde au retour (-1).
 *
 * @param json Tableau cJSON de tous les héros (pour vérifier les IDs).
 */
void handle_favorites(cJSON *json);

#endif /* FAVORITES_H */
