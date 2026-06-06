# SuperHero DataBase

> Manage, explore and test your knowledge of the superhero universe.

**Search · Sort · Filter · Compare · Favorites · Quiz**  
Built entirely in C — no framework, no external database.

*L1 project built with **userremi0**.*

---

## Features

- **Display** — simplified or detailed view of all heroes in the database
- **Search** — by ID or by name (case-insensitive)
- **Sort** — rank heroes by any powerstat (intelligence, strength, speed…)
- **Multi-criteria filter** — keep only heroes where a stat is ≥ or ≤ a threshold
- **Compare** — two heroes side by side, the best stat highlighted in green
- **Favorites** — add / remove / persistent save to a JSON file
- **Quiz** — 5 questions, guess the hero from powerstats, score out of 50
- **External links** — Wikipedia, SuperHeroDB and IMDb for each hero

---

## Architecture

No engine. No external dependencies (except cJSON bundled in the project).

```
├── build/
│   ├── main                    # Linux binary
│   └── main.exe                # Windows binary
├── include/
│   ├── cJSON.h                 # lightweight JSON parser
│   ├── colors.h                # ANSI macros for colored output
│   ├── utils.h                 # file read/write, helpers
│   ├── heroes.h                # display, search, comparison, links
│   ├── filter.h                # sorting and filtering
│   ├── favorites.h             # favorites management
│   └── quiz.h                  # interactive quiz
├── json/
│   ├── DATA.json               # 16-hero database
│   └── favorites.json          # user-saved favorites
├── src/
│   ├── main.c                  # entry point, main menu
│   ├── utils.c                 # files, conversion, input
│   ├── heroes.c                # display, search, comparison, links
│   ├── filter.c                # sorting, interactive filtering
│   ├── favorites.c             # favorites management
│   ├── quiz.c                  # quiz: guess the hero
│   └── cJSON.c                 # JSON parser
├── build.sh                    # project build
├── launch.sh                   # binary launcher
└── all.sh                      # build + launch
```

The program loads a JSON file containing 16 superheroes with their powerstats and appearance. All operations (sort, filter, quiz) are performed in-memory from this data.

A hero is defined as a simple JSON entry:

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

Add a hero = add an entry in `DATA.json`. The program handles the rest.

---

## Menu

| Option | Function |
|--------|----------|
| (0) | Simplified database view |
| (1) | Full info by ID |
| (2) | Full info by name |
| (3) | Sort by a powerstat |
| (4) | Filter heroes |
| (5) | Compare two heroes |
| (6) | Manage favorites |
| (7) | Quiz: guess the hero |
| (8) | External links |
| (-1) | Quit |

---

## Stack

`C` — standard library only + [cJSON](https://github.com/DaveGamble/cJSON) (bundled).

Build with `gcc`:
```bash
./build.sh
./launch.sh
```

*The binary is located in `build/main` (Linux) or `build/main.exe` (Windows).*

---

## Credits

Code, design and data by **SkylePaf** and **userremi0**.  
Project built as part of a L1 coursework.
