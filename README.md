# Tamagotchi Terminal
COMP2113 / ENGG1340 Group Project — 2025-2026 Semester 2

## Team Members
| Person | Role | Files |
|--------|------|-------|
| Person 1 | Pet Core | pet.h / pet.cpp |
| Person 2 | Random Events | events.h / events.cpp |
| Person 3 | Player Actions | actions.h / actions.cpp |
| Person 4 | Items + Shop | items.h / items.cpp |
| Person 5 | File I/O | fileio.h / fileio.cpp |
| Person 6 | UI + Integration | ui.h / ui.cpp / main.cpp / Makefile |

## Description
A virtual pet that lives in your terminal. Raise it from egg to senior by feeding,
playing, and healing it. Stats decay in real time — even while the game is closed.

## Compilation
```
make
```
Or: `g++ -std=c++11 -Wall -o tamagotchi main.cpp pet.cpp events.cpp actions.cpp items.cpp fileio.cpp ui.cpp`

## Run
```
./tamagotchi
```

## Controls
| Key | Action |
|-----|--------|
| 1 | Feed pet |
| 2 | Play with pet |
| 3 | Sleep |
| 4 | Heal (medicine) |
| 5 | Shop |
| 6 | Inventory |
| 7 | Full status |
| 8 | Leaderboard |
| 9 | Save |
| 0 | Quit |

## Saved Files
- `savegame.txt` — current pet state + timestamp
- `deaths.txt` — all pet deaths
- `leaderboard.txt` — top 10 longest-lived pets

## Coding Requirements
| Requirement | Implementation |
|-------------|----------------|
| Random events | `rollEvent()` in events.cpp — probability tables per difficulty |
| Data structures | Pet struct, Item struct, LifeStage enum, std::vector |
| Dynamic memory | `std::vector<Item>` inventory grows/shrinks at runtime |
| File I/O | savegame.txt + real-time elapsed decay on load |
| Multiple files | 8 .h/.cpp pairs + main.cpp + Makefile |
| Difficulty levels | EASY/NORMAL/HARD scale drain rate, event chance, shop prices |

## Non-Standard Libraries
None — uses only C++11 standard library.
