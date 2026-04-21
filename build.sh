#!/bin/bash
# build.sh - Compile le projet SuperHero DataBase
#
# Usage :
#   chmod +x build.sh
#   ./build.sh
#
# Le binaire final est placé dans build/main

gcc -Wall -Wextra -g \
    src/main.c \
    src/utils.c \
    src/heroes.c \
    src/filter.c \
    src/favorites.c \
    src/quiz.c \
    src/cJSON.c \
    -I include \
    -o build/main

cd build
