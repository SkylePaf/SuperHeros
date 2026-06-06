# SuperHero DataBase

> Gérez, explorez et testez vos connaissances sur l'univers des super-héros.

**Recherche · Tri · Filtrage · Comparaison · Favoris · Quiz**  
Développé entièrement en C - sans framework, sans base de données externe.

*Projet de L1 réalisé avec **userremi0**.*

---

## Fonctionnalités

- **Affichage** — vue simplifiée ou détaillée de tous les héros de la base
- **Recherche** — par ID ou par nom (insensible à la casse)
- **Tri** — classement des héros selon n'importe quelle powerstat (intelligence, strength, speed…)
- **Filtrage multi-critères** — garder uniquement les héros dont une stat est ≥ ou ≤ à un seuil
- **Comparaison** — deux héros côte à côte, la meilleure stat mise en vert
- **Favoris** — ajout / suppression / sauvegarde persistante dans un fichier JSON
- **Quiz** — 5 questions, deviner le héros à partir de ses powerstats, score sur 50
- **Liens externes** — Wikipedia, SuperHeroDB et IMDb pour chaque héros

---

## Architecture

Aucun moteur. Aucune dépendance externe (sauf cJSON intégré au projet).

```
├── build/
│   ├── main                    # binaire Linux
│   └── main.exe                # binaire Windows
├── include/
│   ├── cJSON.h                 # parseur JSON léger
│   ├── colors.h                # macros ANSI pour l'affichage coloré
│   ├── utils.h                 # lecture/écriture de fichiers, helpers
│   ├── heroes.h                # affichage, recherche, comparaison, liens
│   ├── filter.h                # tri et filtrage
│   ├── favorites.h             # gestion des favoris
│   └── quiz.h                  # quiz interactif
├── json/
│   ├── DATA.json               # base de données des 16 héros
│   └── favorites.json          # favoris sauvegardés par l'utilisateur
├── src/
│   ├── main.c                  # point d'entrée, menu principal
│   ├── utils.c                 # fichiers, conversion, saisie
│   ├── heroes.c                # affichage, recherche, comparaison, liens
│   ├── filter.c                # tri, filtrage interactif
│   ├── favorites.c             # gestion des favoris
│   ├── quiz.c                  # quiz : deviner le héros
│   └── cJSON.c                 # parseur JSON
├── build.sh                    # compilation du projet
├── launch.sh                   # lancement du binaire
└── all.sh                      # build + launch
```

Le programme charge un fichier JSON contenant 16 super-héros avec leurs powerstats et apparence. Toutes les opérations (tri, filtrage, quiz) se font en mémoire à partir de ces données.

Un héros est défini comme une simple entrée JSON :

```json
{
  "id": 1,
  "name": "Superman",
  "powerstats": {
    "intelligence": 94,
    "strength": 100,
    "speed": 100,
    "durability": 100,
    "power": 100,
    "combat": 85
  },
  "appearance": {
    "gender": "Male",
    "race": "Kryptonian",
    "height": ["6'3", "191 cm"],
    "weight": ["225 lb", "101 kg"],
    "eyeColor": "Blue",
    "hairColor": "Black"
  }
}
```

Ajouter un héros = ajouter une entrée dans `DATA.json`. Le programme fait le reste.

---

## Menu

| Option | Fonction |
|--------|----------|
| (0) | Vue simplifiée de la base |
| (1) | Infos complètes par ID |
| (2) | Infos complètes par nom |
| (3) | Trier selon une powerstat |
| (4) | Filtrer les héros |
| (5) | Comparer deux héros |
| (6) | Gérer les favoris |
| (7) | Quiz : deviner le héros |
| (8) | Liens externes |
| (-1) | Quitter |

---

## Stack

`C` — uniquement la bibliothèque standard + [cJSON](https://github.com/DaveGamble/cJSON) (intégré).

Compilation avec `gcc` :
```bash
./build.sh
./launch.sh
```

*Le binaire se trouve dans `build/main` (Linux) ou `build/main.exe` (Windows).*

---

## Crédits

Code, design et données par **SkylePaf** et **userremi0**.  
Projet réalisé dans le cadre d'un TP de L1.
