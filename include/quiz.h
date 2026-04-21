/**
 * @file quiz.h
 * @brief Quiz interactif : deviner un super-héros à partir de ses powerstats.
 *
 * Le quiz pose 5 questions par défaut.
 * Chaque bonne réponse rapporte 10 points.
 */

#ifndef QUIZ_H
#define QUIZ_H

#include "../include/cJSON.h"

/**
 * @brief Lance le quiz interactif.
 *        Tire des héros aléatoirement, affiche leurs stats et attend une réponse.
 *        Affiche le score final à la fin des questions.
 *
 * @param json Tableau cJSON contenant tous les héros.
 */
void handle_quiz(cJSON *json);

#endif /* QUIZ_H */
