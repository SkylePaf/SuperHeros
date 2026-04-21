/**
 * @file colors.h
 * @brief Macros de couleurs pour l'affichage dans le terminal (codes ANSI).
 *
 * Usage : printf(RED "Texte en rouge" RESET "\n");
 */

#ifndef COLORS_H
#define COLORS_H

/* Réinitialise la couleur à la valeur par défaut du terminal */
#define RESET       "\033[0m"

#define BLUE        "\e[0;32m"
#define BLUE_BOLD   "\e[1;32m"

#define CYAN        "\e[0;36m"
#define CYAN_BOLD   "\e[1;36m"

#define WHITE       "\e[0;37m\t"
#define WHITE_BOLD  "\e[1;37m"

#define YELLOW      "\e[0;33m"
#define YELLOW_BOLD "\e[1;33m"

#define RED         "\e[0;31m"
#define RED_BOLD    "\e[1;31m"

#define GREEN       "\e[0;34m"
#define GREEN_BOLD  "\e[1;34m"

#endif /* COLORS_H */
