/**
 * @file utils.h
 * @brief Fonctions utilitaires générales du projet.
 *
 * Contient :
 *  - la lecture / écriture de fichiers JSON
 *  - la conversion int -> chaîne de caractères
 *  - la gestion de la saisie clavier
 *  - la récupération de la valeur d'un nœud cJSON
 */

#ifndef UTILS_H
#define UTILS_H

#include "../include/cJSON.h"

/**
 * @brief Lit tout le contenu d'un fichier et le renvoie sous forme de chaîne.
 *
 * @param file_name Chemin vers le fichier à lire.
 * @return char* Contenu du fichier (à libérer avec free()), ou NULL en cas d'erreur.
 */
char *read_JSON_file(const char *file_name);

/**
 * @brief Écrit un objet cJSON dans un fichier (format JSON lisible).
 *
 * @param file_name Chemin vers le fichier de destination.
 * @param json      Objet cJSON à sérialiser et écrire.
 */
void write_JSON_file(const char *file_name, cJSON *json);

/**
 * @brief Convertit un entier en chaîne de caractères allouée dynamiquement.
 *
 * @param nmb Entier à convertir.
 * @return char* Chaîne correspondante (à libérer avec free()).
 */
char *int_to_str(int nmb);

/**
 * @brief Vide le buffer d'entrée jusqu'au prochain '\n' ou EOF.
 *        Utile après un scanf() pour éviter les entrées parasites.
 */
void wait_enter(void);

/**
 * @brief Retourne la valeur textuelle d'un nœud cJSON (string ou int).
 *
 * @param element Nœud cJSON à lire.
 * @return char* Valeur sous forme de chaîne, ou "Unknown" si NULL.
 */
char *get_element_value(cJSON *element);

#endif /* UTILS_H */
